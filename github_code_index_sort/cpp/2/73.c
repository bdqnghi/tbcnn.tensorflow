/*
 * (c) Copyright 2016 Hewlett Packard Enterprise Development LP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <glog/logging.h>
#include <cassert>
#include <iostream>
#include <vector>
#include "MapShuffleStoreManager.h"
#include "ReduceShuffleStoreWithStringKeys.h"
#include "ShuffleDataSharedMemoryReader.h"
#include "MergeSortReduceChannelWithStringKeys.h"

//note: we will need to have range checking later. 
ByteArrayKeyWithVariableLength::RetrievedMapBucket ReduceShuffleStoreWithStringKey::retrieve_mapbucket(int mapId){
  //CHECK(mapId <totalNumberOfPartitions);
  CHECK(mapId < reduceStatus.getSizeOfMapBuckets());
	
  ByteArrayKeyWithVariableLength::RetrievedMapBucket result(reducerId, mapId);

  MapBucket mapBucket= reduceStatus.bucket_for_mapid(mapId); 
  MergeSortReduceChannelWithStringKeys mergeSortReduceChannel (
                                          mapBucket, reducerId, totalNumberOfPartitions, kvBufferMgr);
  mergeSortReduceChannel.init(); 
 
  while (mergeSortReduceChannel.hasNext()) {
	 mergeSortReduceChannel.getNextKeyValuePair();
	 PositionInExtensibleByteBuffer keyValue = mergeSortReduceChannel.getCurrentKeyValue();
	 PositionInExtensibleByteBuffer valueValue = mergeSortReduceChannel.getCurrentValueValue();
	 int valueSize = mergeSortReduceChannel.getCurrentValueSize();

         //populate key's value
         unsigned char *keyValueInBuffer = (unsigned char*) malloc (keyValue.value_size);
         kvBufferMgr->retrieve(keyValue, keyValueInBuffer);
         
         result.keys.push_back(keyValueInBuffer);
         result.keySizes.push_back(keyValue.value_size);

	 //populate value's value
	 // void retrieve (const PositionInExtensibleByteBuffer &posBuffer, unsigned char *buffer);
	 unsigned char *valueValueInBuffer = (unsigned char*)malloc(valueValue.value_size);
	 kvBufferMgr->retrieve(valueValue, valueValueInBuffer);
	 result.values.push_back(valueValueInBuffer);
	 result.valueSizes.push_back(valueSize);
  }

  return result;
}

void ReduceShuffleStoreWithStringKey::free_retrieved_mapbucket(
                       ByteArrayKeyWithVariableLength::RetrievedMapBucket &mapBucket){
    //vector <PositionInExtensibleByteBuffer> values = mapBucket.get_values();
    //for (auto p =values.begin(); p!=values.end(); ++p) {
    //  free (*p);
    //}
    //defer to shutdown for the buffer manager. 
}

//for real key/value pair retrieval                                                                                                                                 
void ReduceShuffleStoreWithStringKey::init_mergesort_engine() {

  for (auto p = reduceStatus.mapBuckets.begin(); p != reduceStatus.mapBuckets.end(); ++p) {
    theMergeSortEngine.addMergeSortReduceChannel(*p);
  }

  theMergeSortEngine.init();

  engineInitialized=true;
}



//this is for testing purpose. 
ByteArrayKeyWithVariableLength::MergeSortedMapBucketsForTesting
           ReduceShuffleStoreWithStringKey::retrieve_mergesortedmapbuckets () {
  ByteArrayKeyWithVariableLength::MergeSortedMapBucketsForTesting result (reducerId);
  if (!engineInitialized) {
     init_mergesort_engine();
  }

  while (theMergeSortEngine.hasNext()) {
	  theMergeSortEngine.getNextKeyValuesPair();
	  PositionInExtensibleByteBuffer keyValue = theMergeSortEngine.getCurrentMergedKey();
	  result.keys.push_back(keyValue);
	  vector<PositionInExtensibleByteBuffer> &retrieved_values = theMergeSortEngine.getCurrentMergeValues();
	  vector<int> &retrieved_sizes = theMergeSortEngine.getCurrentMergeValueSizes();
	  result.kvaluesGroups.push_back(retrieved_values);
	  result.kvaluesGroupSizes.push_back(retrieved_sizes);
  }

  //NOTE: we will need to move shutdown of merge-sort engine into somewhere else. 
  //at this time, merge-sort engine uses malloc to hold the returned Value's value.
  //mergeSortEngine.shutdown(); 

  return result; 
}

//this is for the real key/value retrieval, with the maximum number of keys retrieved to be specified
//an empty holder is created first, and then gets filled in.
int ReduceShuffleStoreWithStringKey::retrieve_mergesortedmapbuckets (int max_number,
				  ByteArrayKeyWithVariableLength::MergeSortedMapBucketsForTesting& resultHolder) {

  //We should not reset the buffer manager any time to get the next batch of the key-values, as the merge-sort network
  //is not empty yet, and the pending elements in the merge-sort network rely on the buffer manager to store the values
  //resetting it invalidates the pending elements in the network.
  //this buffer reset has to go before init_mergesort_engine, as it uses buffer manager to retrieve the first element.
 
  //theMergeSortEngine.reset_buffermgr();

  if (!engineInitialized) {
     init_mergesort_engine();
  }

  int numberOfRetrievedKeys=0; 
  while (theMergeSortEngine.hasNext()) {
	  theMergeSortEngine.getNextKeyValuesPair();

	  PositionInExtensibleByteBuffer keyValue = theMergeSortEngine.getCurrentMergedKey();
	  resultHolder.keys.push_back(keyValue);
	  vector<PositionInExtensibleByteBuffer> &retrieved_values = theMergeSortEngine.getCurrentMergeValues();
	  vector<int> &retrieved_sizes = theMergeSortEngine.getCurrentMergeValueSizes();
	  resultHolder.kvaluesGroups.push_back(retrieved_values);
	  resultHolder.kvaluesGroupSizes.push_back(retrieved_sizes);

          numberOfRetrievedKeys++;
          if (numberOfRetrievedKeys == max_number) {
	     break;
	  }
  }

  return numberOfRetrievedKeys;

  //NOTE: we will need to move shutdown of merge-sort engine into somewhere else. 
  //at this time, merge-sort engine uses malloc to hold the returned Value's value.
  //mergeSortEngine.shutdown(); 

}


void ReduceShuffleStoreWithStringKey::stop(){
  //buffer manager is about DRAM. it will be cleaned up when the shuffle store is stoped.
  kvBufferMgr->free_buffers();
  delete kvBufferMgr; 
}

void ReduceShuffleStoreWithStringKey::shutdown(){
   //NOTE: we can not shutdown after retrieve_mergesortmapbuckets. as otherwise, 
   //it will release all of the allocated memory for the retrieved values. 

}
