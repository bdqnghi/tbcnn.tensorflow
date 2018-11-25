

#include <glog/logging.h>
#include <cassert>
#include <iostream>
#include <vector>
#include "MapShuffleStoreManager.h"
#include "ReduceShuffleStoreWithStringKeys.h"
#include "ShuffleDataSharedMemoryReader.h"
#include "MergeSortReduceChannelWithStringKeys.h"


ByteArrayKeyWithVariableLength::RetrievedMapBucket ReduceShuffleStoreWithStringKey::retrieve_mapbucket(int mapId){
  
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

         
         unsigned char *keyValueInBuffer = (unsigned char*) malloc (keyValue.value_size);
         kvBufferMgr->retrieve(keyValue, keyValueInBuffer);
         
         result.keys.push_back(keyValueInBuffer);
         result.keySizes.push_back(keyValue.value_size);

	 
	 
	 unsigned char *valueValueInBuffer = (unsigned char*)malloc(valueValue.value_size);
	 kvBufferMgr->retrieve(valueValue, valueValueInBuffer);
	 result.values.push_back(valueValueInBuffer);
	 result.valueSizes.push_back(valueSize);
  }

  return result;
}

void ReduceShuffleStoreWithStringKey::free_retrieved_mapbucket(
                       ByteArrayKeyWithVariableLength::RetrievedMapBucket &mapBucket){
    
    
    
    
    
}


void ReduceShuffleStoreWithStringKey::init_mergesort_engine() {

  for (auto p = reduceStatus.mapBuckets.begin(); p != reduceStatus.mapBuckets.end(); ++p) {
    theMergeSortEngine.addMergeSortReduceChannel(*p);
  }

  theMergeSortEngine.init();

  engineInitialized=true;
}




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

  
  
  

  return result; 
}



int ReduceShuffleStoreWithStringKey::retrieve_mergesortedmapbuckets (int max_number,
				  ByteArrayKeyWithVariableLength::MergeSortedMapBucketsForTesting& resultHolder) {

  
  
  
  
 
  

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

  
  
  

}


void ReduceShuffleStoreWithStringKey::stop(){
  
  kvBufferMgr->free_buffers();
  delete kvBufferMgr; 
}

void ReduceShuffleStoreWithStringKey::shutdown(){
   
   

}
