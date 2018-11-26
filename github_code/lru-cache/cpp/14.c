/*
*FILENAME   :   cache1.cc
*DESCRIPTION    :   cache Layer 1 design

*AUTHOR     :       Haopeng Liu        
*START DATE     :       9/15/2018
*	9/21/2018			update LRU -> hitUpdateLRU & missUpdateLRU
*/
#include "sim_cache.h"
#include <math.h>
#include <iostream> 
#include <iomanip>
using namespace std;


Cache1::Cache1 (unsigned long int block_size, unsigned long int l1_size, unsigned long int l1_assoc, unsigned long int vc_num_blocks, int l2Enable){
	blockSize = block_size;
	size = l1_size;
	assoc = l1_assoc;
	vc_blocks = vc_num_blocks;
	enable = l2Enable;
	//counter1 = { 0, 0, 0 , 0, 0, 0, 0 };

	/*all addresses are 32 bits*/
	unsigned long int bitAddress = 32;


	/*check if it is a fully-associative cache */
	if(assoc == (size/blockSize))
	{
		numSet = 1;
		bitIndex = 0;
	}
	else{
		numSet = (size/(blockSize * assoc));
		bitIndex = log2(numSet);
	}

	bitOffset = log2(blockSize);
	bitTag = bitAddress - bitOffset - bitIndex;

	/*victim cache
	*fully-associative & LRU
	*/

	/*a cache and its VC have the same BLOCKSIZE
	so bitOffset is same
	*/
	if(vc_blocks != 0)
		bitTagVC = bitAddress - bitOffset;

	/*initialize a 2D array for the cache structure*/
	//block_params cache[numSet][assoc];
	//initCache1();
	cache = new block_params *[numSet];
	for (int i = 0; i < numSet; i++) {
		cache[i] = new block_params[assoc];
		for (int j = 0; j < assoc; j++) {
			cache[i][j].valid = 0;
			cache[i][j].dirty = 0;
		}

	}


	/*initialize LRU*/
	//int lru[numSet][assoc];
	lru = new int *[numSet];
	for (int i = 0; i < numSet; i++) {
		lru[i] = new int[assoc];
		for (int j = 0; j < assoc; j++) {
			lru[i][j] = 0;
		}

	}
	
	//end initLRU();

	if(vc_blocks != 0){
		//initialize victim cache
		//block_params vc[vc_blocks];
		vc = new block_params[vc_blocks];
		for (int i = 0; i < vc_blocks; i++) {
			vc[i].valid = 0;
			vc[i].dirty = 0;
		}

		//int vc_lru[vc_blocks];
		vc_lru = new int[vc_blocks];
		for (int i = 0; i < vc_blocks; i++) {
			vc_lru[i] = 0;
		}
		
	}
	//initVC_LRU();

}

// /*initialize cache and enable every block*/
// void Cache::initCache1(){
// 	for(int i = 0; i < numSet; i++)
// 		for(int j = 0; j < assoc ; j++){
// 			cache[i][j].valid = 0;
// 		}

void Cache1::printCache() {
	cout << '\n';
	cout << "===== L1 contents =====" << endl;
	unsigned long int tempLRU;
	int tempDirty;
	int tempValid;
	unsigned long int tempTag;
	unsigned long int tempIndex;

	//sort every set according to lru: MRU -> LRU
	for(int m = 0; m < numSet; m++){
		for(int  n = assoc - 1; n > 0; n--){
			for(int k = n - 1; k >= 0; k--){
				if(lru[m][n] < lru[m][k]){
					tempLRU = lru[m][n];
					lru[m][n] = lru[m][k];
					lru[m][k] = tempLRU;

					tempTag = cache[m][n].tag;
					tempIndex = cache[m][n].index;
					tempDirty = cache[m][n].dirty;	
					tempValid = cache[m][n].valid;
	
					cache[m][n].tag = cache[m][k].tag;
					cache[m][n].index = cache[m][k].index;
					cache[m][n].dirty = cache[m][k].dirty;
					cache[m][n].valid = cache[m][k].valid;

					cache[m][k].tag = tempTag;
					cache[m][k].index = tempIndex;
					cache[m][k].dirty = tempDirty;
					cache[m][k].valid = tempValid;


				}
			}

		}
	}
	

	for (int i = 0; i < numSet; i++) {
		cout << "  set " << setw(3) << dec << i << ":   ";
		for (int j = 0; j < assoc; j++) {
			cout << hex << cache[i][j].tag;
			if (cache[i][j].dirty == 1)
				cout  << " D  ";
			else {
				cout << setw(4) << ' ';
			}
		}
		cout << '\n';
	}
	
}

void Cache1::printVC() {
	cout << '\n';
	cout << "===== VC contents =====" << endl;
	unsigned long int tempLRU;
	int tempDirty;
	int tempValid;
	unsigned long int tempTag;
	unsigned long int tempIndex;

	
	//sort every set according to lru: MRU -> LRU
	for(int  n = vc_blocks - 1; n > 0; n--){
		for(int k = n - 1; k >= 0; k--){
			if(vc_lru[n] < vc_lru[k]){
				tempLRU = vc_lru[n];
				vc_lru[n] = vc_lru[k];
				vc_lru[k] = tempLRU;

				tempTag = vc[n].tag;
				tempIndex = vc[n].index;
				tempDirty = vc[n].dirty;	
				tempValid = vc[n].valid;

				vc[n].tag = vc[k].tag;
				vc[n].index = vc[k].index;
				vc[n].dirty = vc[k].dirty;
				vc[n].valid = vc[k].valid;

				vc[k].tag = tempTag;
				vc[k].index = tempIndex;
				vc[k].dirty = tempDirty;
				vc[k].valid = tempValid;


			}
		}

	}



	cout << "  set   0:  ";


	for (int j = 0; j < vc_blocks; j++) {
		cout << hex << vc[j].tag;
		if (vc[j].dirty == 1)
			cout << " D  ";
		else {
			cout << setw(4) << ' ';
		}
	}

	cout << '\n';
}


/*initialize LRU*/
/*
void Cache1::initLRU(){
	int i;
	for (i = 0; i < numSet; i++)
		for(int j = 0; j < assoc ; j++){
			lru[i][j] = 0;
		}
}
*/

int Cache1::getLRU(unsigned long int index) {
	int tmpValue = lru[index][0];
	int tmpWay = 0;
	for (int i = 0; i < assoc - 1; i++) {
		if (tmpValue < lru[index][i + 1]) {
			tmpValue = lru[index][i + 1];
			tmpWay = i + 1;
		}
	}
	return tmpWay;
}



//update LRU
void Cache1::hitUpdateLRU(unsigned long int index, int numWay){
	int value = 0;
	value = lru[index][numWay];
	lru[index][numWay] = 0;
	for (int i = 0; i < assoc; i++) {
		if (i != numWay &&  lru[index][i] <= value && cache[index][i].valid) {
			lru[index][i]++;
		}
	}
}

void Cache1::missUpdateLRU(unsigned long int index, int numWay) {
	lru[index][numWay] = 0;
	for (int i = 0; i < assoc; i++) {
		if (i != numWay) {
			lru[index][i]++;
		}
	}
}
	

//-----------------------Cache L1-----------------------
void Cache1::function(char rw, unsigned long int address, Cache2 &L2)
{
	int hit = 0;
	int foundBlock = 0;
	unsigned long int wayFound;
	unsigned long int mask = 1;
	unsigned long int tagAndIndex = (address >> bitOffset);
	unsigned long int evictBlockAddress;

	//index value
	if (rw == 'r') {
		if (assoc == (size / blockSize))
		{
			index = 0;
		}
		else {
			mask = (mask << bitIndex) - 1;
			index = mask & tagAndIndex;
		}
	

		//tag value
		tag = address >> (bitOffset + bitIndex);

		//increase counter
		counter1.readCounter++;

		//search cache;
		for (int i = 0; i < assoc; i++) {
			//hit?
			if ((cache[index][i].valid == 1) && (cache[index][i].tag == tag)) {
				hit = 1;
				wayFound = i;
				break;
			}
			//else hit = 0;

		}
		//update LRU
		if (hit == 1) {
			hitUpdateLRU(index, wayFound);

		}
		else {
			//increase readMissCounter
			counter1.readMissCounter++;

			//finding invalid block
			for (int i = 0; i < assoc; i++) {
				if (cache[index][i].valid == 0) {
					foundBlock = 1;
					wayFound = i;
					break;
				}
				else {
					foundBlock = 0;
				}
			}

			//found invalid block <- requested block
			if (foundBlock == 1) {

				//read -> L2

				if(enable == 1)
					L2.function('r', address);

				cache[index][wayFound].tag = tag;
				cache[index][wayFound].valid = 1;
				cache[index][wayFound].dirty = 0;
				cache[index][wayFound].index = index;
				//update LRU
				missUpdateLRU(index, wayFound);



			}
			//check VC
			else if (vc_blocks != 0) {
				int vcFound;
				int blockNum;
				unsigned long int tempAddress;
				int tempDirty;


				int vcHit;
				int vcWayFound;

				//search vc;
				unsigned long int vcTag;
				
				counter1.swapRequest++;

				vcTag = address >> bitOffset;
				for (int i = 0; i < vc_blocks; i++) {
					//hit?
					//hit!

					if ((vc[i].valid == 1) && (vc[i].tag == vcTag)) {
						vcHit = 1;
						vcWayFound = i;
						break;
					}
					else
						vcHit = 0;
				}

				//get which block
				blockNum = getLRU(index);

				if (vcHit == 1) {

					counter1.swaps++;

					evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);

					//store evictBlockAddress -> tempAddress
					tempAddress = evictBlockAddress;
					tempDirty = cache[index][blockNum].dirty;

					//vc -> L1
					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = vc[vcWayFound].dirty;
					cache[index][blockNum].valid = 1;

					//tempAddress -> vc
					vc[vcWayFound].tag = tempAddress >> bitOffset;
					vc[vcWayFound].index = 0;
					vc[vcWayFound].valid = 1;
					vc[vcWayFound].dirty = tempDirty;

					//update cache LRU and vc LRU
					missUpdateLRU(index, blockNum);
					hitUpdateVC_LRU(vcWayFound);
				}
				else if (vcHit == 0) {
					
					//check invalid block
					int invalidExist;
					for (int i = 0; i < vc_blocks; i++) {
						if (vc[i].valid == 0) {
							vcWayFound = i;
							invalidExist = 1;
							break;
						}
						else
							invalidExist = 0;
					}
					if (invalidExist != 0) {
						if (enable == 1) {
							L2.function('r', address);
						}

						//blockNum = getLRU(index);
						evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);
						tempDirty = cache[index][blockNum].dirty;

						cache[index][blockNum].tag = tag;
						cache[index][blockNum].index = index;
						cache[index][blockNum].dirty = 0;
						cache[index][blockNum].valid = 1;

						//evictBlockAddress -> vc
						vc[vcWayFound].tag = evictBlockAddress >> bitOffset;
						vc[vcWayFound].index = 0;
						vc[vcWayFound].valid = 1;
						vc[vcWayFound].dirty = tempDirty;

						//update cache LRU and vc LRU
						missUpdateLRU(index, blockNum);
						missUpdateVC_LRU(vcWayFound);
					}
					//vc is full
					//single out a vc block
					//!!!check dirty bits; if dirty = 0 -> dump it; if dirty = 1 -> L2
					else {
						int vcBlockNum;
						evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);
						//cout << hex << evictBlockAddress << endl;
						vcBlockNum = getVC_LRU();
						if (vc[vcBlockNum].dirty == 1) {
							unsigned long int wbAddress;

							wbAddress = vc[vcBlockNum].tag << bitOffset;
							counter1.writeBack++;
							if (enable == 1) {
								L2.function('w', wbAddress);


								//write back to L2
							}
							if (enable == 1) {
								L2.function('r', address);
	

							}

							vc[vcBlockNum].tag = evictBlockAddress >> bitOffset;
							vc[vcBlockNum].index = 0;
							vc[vcBlockNum].dirty = cache[index][blockNum].dirty;
							vc[vcBlockNum].valid = 1;

							missUpdateVC_LRU(vcBlockNum);

							cache[index][blockNum].tag = tag;
							cache[index][blockNum].index = index;
							cache[index][blockNum].dirty = 0;
							cache[index][blockNum].valid = 1;

							missUpdateLRU(index, blockNum);
						}
						else {
							if (enable == 1) {
								L2.function('r', address);
	

							}

							vc[vcBlockNum].tag = evictBlockAddress >> bitOffset;
							vc[vcBlockNum].index = 0;
							vc[vcBlockNum].dirty = cache[index][blockNum].dirty;
							vc[vcBlockNum].valid = 1;

							missUpdateVC_LRU(vcBlockNum);

							cache[index][blockNum].tag = tag;
							cache[index][blockNum].index = index;
							cache[index][blockNum].dirty = 0;
							cache[index][blockNum].valid = 1;

							missUpdateLRU(index, blockNum);
						}
					}
				}
			}
			//vc_blocks = 0
			else {
							
				int blockNum = getLRU(index);
				if (cache[index][blockNum].dirty == 0) {
					
					if (enable == 1) {
						L2.function('r', address);

					}
					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = 0;
					cache[index][blockNum].valid = 1;


					missUpdateLRU(index, blockNum);
				}
				else
				{
					unsigned long int wbAddress;
					wbAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);

					counter1.writeBack++;	
				
					if (enable == 1) {
						L2.function('w', wbAddress);


						L2.function('r', address);

					}

					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = 0;
					cache[index][blockNum].valid = 1;

					missUpdateLRU(index, blockNum);
				}
			}
		}
	}
	// wirte request
	else{
		if (assoc == (size / blockSize))
		{
			index = 0;
		}
		else {
			mask = (mask << bitIndex) - 1;
			index = mask & tagAndIndex;
			//cout << index << endl;
		}
	

		//tag value
		tag = address >> (bitOffset + bitIndex);
		//cout << tag << endl;

		//increase writeCounter
		counter1.writeCounter++;

		//search cache;
		for (int i = 0; i < assoc; i++) {
			//hit?
			if ((cache[index][i].valid == 1) && (cache[index][i].tag == tag)) {
				hit = 1;
				wayFound = i;
				break;
			}
			//else hit = 0;

		}
		//update LRU
		if (hit == 1) {
			cache[index][wayFound].dirty = 1;
			hitUpdateLRU(index, wayFound);
			
		}
		else {
			//increase writeMissCounter
			counter1.writeMissCounter++;

			//finding invalid block
			for (int i = 0; i < assoc; i++) {
				if (cache[index][i].valid == 0) {
					foundBlock = 1;
					wayFound = i;
					break;
				}
				else {
					foundBlock = 0;
				}
			}

			//found invalid block <- requested block
			if (foundBlock == 1) {

				//read -> L2
				
				if(enable == 1){
					L2.function('r', address);
					

				}
					
				cache[index][wayFound].tag = tag;
				cache[index][wayFound].valid = 1;
				cache[index][wayFound].dirty = 1;
				cache[index][wayFound].index = index;
				
				//update LRU
				missUpdateLRU(index, wayFound);

			}
			//check VC
			else if (vc_blocks != 0) {
				int vcFound;
				int blockNum;
				unsigned long int tempAddress;
				int tempDirty;


				int vcHit;
				int vcWayFound;

				//search vc;
				unsigned long int vcTag;

				counter1.swapRequest++;

				vcTag = address >> bitOffset;
				for (int i = 0; i < vc_blocks; i++) {
					//hit?
					//hit!

					if ((vc[i].valid == 1) && (vc[i].tag == vcTag)) {
						vcHit = 1;
						vcWayFound = i;
						break;
					}
					else
						vcHit = 0;
				}

				//get which block
				blockNum = getLRU(index);

				if (vcHit == 1) {
					
					counter1.swaps++;

					evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);

					//store evictBlockAddress -> tempAddress
					tempAddress = evictBlockAddress;
					tempDirty = cache[index][blockNum].dirty;

					// L1
					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = 1;
					cache[index][blockNum].valid = 1;

					//tempAddress -> vc
					vc[vcWayFound].tag = tempAddress >> bitOffset;
					vc[vcWayFound].index = 0;
					vc[vcWayFound].valid = 1;
					vc[vcWayFound].dirty = tempDirty;

					//update cache LRU and vc LRU
					missUpdateLRU(index, blockNum);
					hitUpdateVC_LRU(vcWayFound);
				}
				else if (vcHit == 0) {
					//check invalid block
					int invalidExist;
					//read L2
				
					for (int i = 0; i < vc_blocks; i++) {
						if (vc[i].valid == 0) {
							vcWayFound = i;
							invalidExist = 1;
							break;
						}
						else
							invalidExist = 0;
					}
					if (invalidExist != 0) {
						if (enable == 1) {
							L2.function('r', address);

						}
						//blockNum = getLRU(index);
						evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);
						tempDirty = cache[index][blockNum].dirty;

						cache[index][blockNum].tag = tag;
						cache[index][blockNum].index = index;
						cache[index][blockNum].dirty = 1;
						cache[index][blockNum].valid = 1;

						//evictBlockAddress -> vc
						vc[vcWayFound].tag = evictBlockAddress >> bitOffset;
						vc[vcWayFound].index = 0;
						vc[vcWayFound].valid = 1;
						vc[vcWayFound].dirty = tempDirty;

						//update cache LRU and vc LRU
						missUpdateLRU(index, blockNum);
						missUpdateVC_LRU(vcWayFound);
					}
					//vc is full
					//single out a vc block
					//!!!check dirty bits; 
					//?if dirty = 0 -> dump it; if dirty = 1 -> L2
					else {
						int vcBlockNum;
						evictBlockAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);
						vcBlockNum = getVC_LRU();
						if (vc[vcBlockNum].dirty == 1) {
							unsigned long int wbAddress;

							wbAddress = vc[vcBlockNum].tag << bitOffset;

							counter1.writeBack++;
							if (enable == 1) {
								L2.function('w', wbAddress);
								//write back to L2
								L2.function('r', address);
								


							}


							vc[vcBlockNum].tag = evictBlockAddress >> bitOffset;
							vc[vcBlockNum].index = 0;
							vc[vcBlockNum].dirty = cache[index][blockNum].dirty;
							vc[vcBlockNum].valid = 1;

							missUpdateVC_LRU(vcBlockNum);

							cache[index][blockNum].tag = tag;
							cache[index][blockNum].index = index;
							cache[index][blockNum].dirty = 1;
							cache[index][blockNum].valid = 1;

							missUpdateLRU(index, blockNum);
						}
						else {
							if (enable == 1) {
								L2.function('r', address);
								

							}
							vc[vcBlockNum].tag = evictBlockAddress >> bitOffset;
							vc[vcBlockNum].index = 0;
							vc[vcBlockNum].dirty = cache[index][blockNum].dirty;
							vc[vcBlockNum].valid = 1;

							missUpdateVC_LRU(vcBlockNum);

							cache[index][blockNum].tag = tag;
							cache[index][blockNum].index = index;
							cache[index][blockNum].dirty = 1;
							cache[index][blockNum].valid = 1;
							

							missUpdateLRU(index, blockNum);
						}
					}
				}
			}
			//vc_blocks = 0
			else {
				int blockNum = getLRU(index);
				if (cache[index][blockNum].dirty == 0) {
					if (enable == 1) {
						L2.function('r', address);
						

						}
					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = 1;
					cache[index][blockNum].valid = 1;


					missUpdateLRU(index, blockNum);
				}
				else {
					//wb->L2
					unsigned long int wbAddress;
					wbAddress = (cache[index][blockNum].tag << (bitIndex + bitOffset) | cache[index][blockNum].index << bitOffset);
					
					counter1.writeBack++;
					if (enable == 1) {						
						L2.function('w', wbAddress);
						
				
						L2.function('r', address);
						

					}

					cache[index][blockNum].tag = tag;
					cache[index][blockNum].index = index;
					cache[index][blockNum].dirty = 1;
					cache[index][blockNum].valid = 1;

					missUpdateLRU(index, blockNum);

									}
			}
		}
	}


}


/*
void Cache1::initVC_LRU(){
	for(int i = 0; i < vc_blocks; i++){
		vc_lru[i] = 0;
	}

}
*/

void Cache1::missUpdateVC_LRU(int numWay) {
	vc_lru[numWay] = 0;
	for (int i = 0; i < vc_blocks; i++) {
		if (i != numWay && vc[i].valid)		
			vc_lru[i]++;
	}	
}


void Cache1::hitUpdateVC_LRU(int numWay) {
	int value = 0;
	value = vc_lru[numWay];
	vc_lru[numWay] = 0;
	for (int i = 0; i < vc_blocks; i++)
	{
		if (i != numWay && vc_lru[i] <= value && vc[i].valid) {
			vc_lru[i]++;
		}
	}
}

int Cache1::getVC_LRU() {
	int tmpValue = vc_lru[0];
	int tmpWay = 0;
	for (int i = 0; i < vc_blocks - 1; i++) {
		if (tmpValue < vc_lru[i + 1]) {
			tmpValue = vc_lru[i + 1];
			tmpWay = i + 1;
		}
	}
	return tmpWay;
	
}
void Cache1::printCounter(){
	//double swapRequestRate;
	double swapRequestRate = double (counter1.swapRequest) / (counter1.readCounter + counter1.writeCounter);

	//double missRate;
	double missRate = double (counter1.readMissCounter + counter1.writeMissCounter - counter1.swaps) / (counter1.readCounter + counter1.writeCounter);

	cout << '\n';
	cout << "===== Simulation results =====" << endl;
	cout << "  a. number of L1 reads:" << setw(28) << dec << counter1.readCounter << endl;
	cout << "  b. number of L1 read misses:" << setw(22) << dec << counter1.readMissCounter << endl;
	cout << "  c. number of L1 writes:" << setw(27) << dec << counter1.writeCounter << endl;
	cout << "  d. number of L1 write misses:" << setw(21) << dec << counter1.writeMissCounter << endl;
	cout << "  e. number of swap requests:" << setw(23) << dec << counter1.swapRequest << endl;	
	cout << "  f. swap request rate:" << setw(29) << fixed << setprecision(4) << swapRequestRate << endl;
	cout << "  g. number of swaps:" << setw(31) << dec << counter1.swaps << endl;
	cout << "  h. combined L1+VC miss rate:" << setw(22) << fixed << setprecision(4) << missRate << endl;
	cout << "  i. number writebacks from L1/VC:" << setw(18) << dec << counter1.writeBack << endl;


}
