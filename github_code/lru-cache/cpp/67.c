#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<bitset>
#include<math.h>
#include<algorithm>
#include<cstddef> 
#include<iterator>


using namespace std;


//#define BLOCK_NUM 32
//#define TAGSIZE 16
//#define C_NUM 2
int C_NUM=2;
int memory_traffic=0;

struct cache_params{
int SIZE,BLOCKSIZE,ASSOC,SET_NO,TAG_SIZE,INDEX_SIZE,BLOCK_OFFSET_BITS;
				int READS,READS_MISSES,WRITE,WRITES_MISSES,WRITE_BACKS;
				int SWAP_RATE,SWAP_NO;
				float SWAP_REQUEST,MISS_RATE;
				
};

vector<cache_params> cachep;
cache_params victimp[2];

//class for a set in a cache
class cache_set{
			public:
				
	
				vector<string> TAG;
				vector<bool> valid;
				vector<bool> dirty;
				vector<int> LRU;
				vector<string> victim_TAG;
				
		
};

class cache_e{
		public:
				vector<cache_set> cacheset;
					
			};

class victim_cache{
			public:
					cache_set victimset;
};

  
vector<cache_e> cache;
victim_cache victim[2];


void caches_init()
{
	for(int i=0;i<C_NUM;i++)
	{
		for(int j=0;j<cachep[i].SET_NO;j++)
		{
			cache[i].cacheset[j].LRU[0]=0;
			for(int k=0;k<cachep[i].ASSOC;k++)
			{
				cache[i].cacheset[j].TAG[k]='x';
				cache[i].cacheset[j].LRU[k]=k;
				cache[i].cacheset[j].valid[k]=false;
				cache[i].cacheset[j].dirty[k]=false;
			}
			
		}
	}

	for (int i=0;i<victimp[0].ASSOC;i++)
	{

		victim[0].victimset.victim_TAG[i]='x';
		victim[0].victimset.LRU[i]=i;
		victim[0].victimset.valid[i]=false;
		victim[0].victimset.dirty[i]=false;
	}
	/*for(int i=0;i<C_NUM;i++)
	{
		for(int j=0;j<cachep[i].SET_NO;j++)
		{
			for(int k=0;k<cachep[i].ASSOC;k++)
			{
				cout<<cache[i].cacheset[j].TAG[k]<<cache[i].cacheset[j].LRU[k]<<cache[i].cacheset[j].valid[k]<<cache[i].cacheset[j].dirty[k]<<endl;
			} } }*/
	
	}

string trace_address(string);
string hex2bin(string);
string bin2hex(string);
int bin2dec(string);
int read_request(string,int);
void write_request(string,int);

void write_request(string write_addr,int cache_no)
{
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	bool dirty_replace;
	string rep_addr;
	int hit;
	
	cachep[cache_no].WRITE++;
	
	write_addr=hex2bin(write_addr);
	TAG=write_addr.substr(0,(write_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=write_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	
	TAG=bin2hex(TAG);
	INDEX1=bin2dec(INDEX);
	int victim_match_block;
	
	//assoc will give the block number of the valid bit, which is false
	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	if(assoc>=cache[cache_no].cacheset[INDEX1].valid.size())   //set is full
			{
				//find if address block already exist in cache
				unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
				if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size())  //Not in set& set is full																												 }
				{
						cachep[cache_no].WRITES_MISSES++;

						//Victim Implementation for Write begins

						if(victimp[cache_no].ASSOC!=0) //check if victim cache exist
						{

							victimp[cache_no].SWAP_RATE++;
							string victim_search;
							victim_search=write_addr.substr(0,(write_addr.length()-(cachep[cache_no].BLOCK_OFFSET_BITS)));
							//cout<<"       VICTIM is "<<endl;

							//cout<<victim_search<<endl;
							//cout<<bin2hex(victim_search)<<endl;

							victim_match_block=find(victim[cache_no].victimset.victim_TAG.begin(),victim[cache_no].victimset.victim_TAG.end(),bin2hex(victim_search))-victim[cache_no].victimset.victim_TAG.begin();
							unsigned int victim_assoc=find(victim[cache_no].victimset.valid.begin(),victim[cache_no].victimset.valid.end(),false)-victim[cache_no].victimset.valid.begin();
							
							if(victim_match_block>=victim[cache_no].victimset.victim_TAG.size()&&(victim_assoc>=victim[cache_no].victimset.valid.size())) //Not found in victim and victim is full
							{
								//find LRU, evict if not dirty, if dirty write to level 2

								unsigned int victim_LRU_replace=	distance(victim[cache_no].victimset.LRU.begin(),max_element(victim[cache_no].victimset.LRU.begin(),victim[cache_no].victimset.LRU.end()));
								bool victim_dirty_replace=victim[cache_no].victimset.dirty[victim_LRU_replace];
								

								if(victim_dirty_replace==true)
								{
									//cout<<"VICTIM LRU Dirty for write request to cache0"<<endl;
									
									string victim_write_back=hex2bin(victim[cache_no].victimset.victim_TAG[victim_LRU_replace]);
									victim_write_back.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');
									victim_write_back=victim_write_back.substr(victim_write_back.length()-32);
									victim_write_back=bin2hex(victim_write_back);

									victim[cache_no].victimset.dirty[victim_LRU_replace]==false;

									if(cache_no!=C_NUM-1)
									{

										cachep[cache_no].WRITE_BACKS++;
										write_request(victim_write_back,(cache_no+1));

									}

									else
									{
										cachep[cache_no].WRITE_BACKS++;
										memory_traffic++; //Last cache level, writing back to memory
									}	

								}	//write back to next level end here

								if(cache_no!=C_NUM-1)
								{

									hit=read_request(bin2hex(write_addr),(cache_no+1));
								}

								else
								{
									memory_traffic++;
								}	

								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								//finding LRU in cache level and sending it to victim

								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								victim_replace.append(INDEX);
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								victim_replace=bin2hex(victim_replace);
								victim[cache_no].victimset.victim_TAG[victim_LRU_replace]=victim_replace;
								victim[cache_no].victimset.dirty[victim_LRU_replace]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								victim[cache_no].victimset.LRU[victim_LRU_replace]=0;
								victim[cache_no].victimset.valid[victim_LRU_replace]=true;
								//Update victim LRU's

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)
								{
									if(victim[cache_no].victimset.valid[i]==true&&(i!=victim_LRU_replace))
											victim[cache_no].victimset.LRU[i]++;
								}	

								//Update L1 now

								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;

								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}		

								//L1 write back completed


							}

							else if (victim_match_block>=victim[cache_no].victimset.victim_TAG.size()&&(victim_assoc<victim[cache_no].victimset.valid.size()))
							{	//Not found, victim has space

								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								victim_replace.append(INDEX);
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								victim_replace=bin2hex(victim_replace);

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)  //updating LRU first for victim and then adding tag
								{
									if(victim[cache_no].victimset.valid[i]==true)
										victim[cache_no].victimset.LRU[i]++;
								}	
								victim[cache_no].victimset.victim_TAG[victim_assoc]=victim_replace;
								victim[cache_no].victimset.valid[victim_assoc]=true;
								victim[cache_no].victimset.dirty[victim_assoc]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								victim[cache_no].victimset.LRU[victim_assoc]=0;

								if(cache_no!=C_NUM-1)
								{

									hit=read_request(bin2hex(write_addr),(cache_no+1));
								}
								else
								{

									memory_traffic++;
								}	

								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;

								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}	




							}

							else //found in victim
							{
								//cout<<"Victim Hit  "<<TAG<<endl;
								victimp[cache_no].SWAP_NO++;
								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								victim_replace.append(INDEX);
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								victim_replace=bin2hex(victim_replace);
								//repalacing tag;
								string cache_replace=hex2bin(victim[cache_no].victimset.victim_TAG[victim_match_block]);
								cache_replace=cache_replace.substr(0,(cache_replace.length()-cachep[cache_no].INDEX_SIZE));
								cache_replace=bin2hex(cache_replace);
								string temp_var;
								victim[cache_no].victimset.victim_TAG[victim_match_block]=victim_replace;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=cache_replace;
								bool dirty_temp=victim[cache_no].victimset.dirty[victim_match_block];
								victim[cache_no].victimset.dirty[victim_match_block]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=true;

								//swapping completed, updating LRU

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)
								{
									if(victim[cache_no].victimset.valid[i]==true&&(victim[cache_no].victimset.LRU[i]<victim[cache_no].victimset.LRU[victim_match_block]))
											victim[cache_no].victimset.LRU[i]++;
								}	
								victim[cache_no].victimset.LRU[victim_match_block]=0;

								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;


								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}		

							} //found in victim ends

						}//victim_present condition ends


						else
						{	
						LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
						dirty_replace=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
						//cout<<"Write request,Set full,but dont have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
						if(dirty_replace==true)    //perform a write request to next level
 						   {
							/*if(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].length()==8)
								rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].substr(2)));
							else*/
							rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]));
							
							//cout<<rep_addr<<endl;
							rep_addr.append(INDEX);
							//cout<<' ' <<INDEX<<endl;
							
							rep_addr.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');//add random block bits
							
							
							rep_addr=rep_addr.substr(rep_addr.length()-32);
							rep_addr=bin2hex(rep_addr);
							//cout<<rep_addr<<endl;
				
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							//cout<<"performing write to next level coz dirty bit"<<endl;
							if(cache_no!=C_NUM-1)//check if it's not  the last cache
							{	
								cachep[cache_no].WRITE_BACKS++;
								write_request(rep_addr,(cache_no+1));    
							}
							else
							{	
								cachep[cache_no].WRITE_BACKS++;
								memory_traffic++;
							}	
							}
						
							if(cache_no!=C_NUM-1)//check if it's not the last cache
							{
							hit=read_request(bin2hex(write_addr),(cache_no+1));
							}
							
							else
							{
								memory_traffic++;
							}
					
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
							cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;
							for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
							{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
						
							}	
						}					
				
				}

				
				else   //In set, set is full
				{
					//cout<<"Write request,Set full,but have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
					cache[cache_no].cacheset[INDEX1].dirty[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
					for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if(cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
					
				cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;	
					
				}
				
				
				
				
				}	
	else  //set is not full
	{
		unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) //set is not full,and doesn't have the particular element
		{
			cachep[cache_no].WRITES_MISSES++;
			//cout<<"Write request,Set not full,but doesn't have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
			if(cache_no!=C_NUM-1)//check if it's the last cache
			{	
			//cout<<"reading from catch "<<cache_no+1<<endl;
				
			hit=read_request(bin2hex(write_addr),(cache_no+1));
			}
			
			else
			{
				memory_traffic++;
			}	
			cache[cache_no].cacheset[INDEX1].dirty[assoc]=true;
			cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
			{
				if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=assoc))
					cache[cache_no].cacheset[INDEX1].LRU[i]++;
			}	
		
				
		}		
		
		else //set is not full and have a particular element
		
		{
					//cout<<"Write request,Set not full,but have tag "<<bin2hex(write_addr)<<" Cache No : "<<cache_no<<endl;
					cache[cache_no].cacheset[INDEX1].dirty[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
					cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;	
					
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]==true))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
					cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;	
					
		}								 					 
	}						
}





int read_request(string read_addr,int cache_no)
{
	
	cachep[cache_no].READS++;	
	
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	bool dirty_replace;
	string rep_addr;
	int TAG_match=-1;
	int hit;
	
	
	read_addr=hex2bin(read_addr);
	TAG=read_addr.substr(0,(read_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=read_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	TAG=bin2hex(TAG);
	
	unsigned int victim_match_block;
	INDEX1=bin2dec(INDEX);
	
	//assoc will give the block number of the valid bit, which is false
	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	
	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].valid[i]==true)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}
	
	if(TAG_match!=-1)  //Tag match
	{
		//cout<<"Read request,Tag Match, Set may or may not be empty  "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;
		cache[cache_no].cacheset[INDEX1].valid[TAG_match]=true;
		cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
		for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]==true))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
		cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
		
		return 1; //it's a hit
	}
	
	
	else//tag doesn't match
	{
	
		cachep[cache_no].READS_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].valid.size())//set is full & tag doesn'match->check in victim
				{
						if(victimp[cache_no].ASSOC!=0) //check if victim cache exist
						{
							victimp[cache_no].SWAP_RATE++;
							//cout<<"Entering victim"<<endl;
							string victim_search;
							victim_search=read_addr.substr(0,(read_addr.length()-(cachep[cache_no].BLOCK_OFFSET_BITS)));
							//cout<<"       VICTIM is "<<endl;

							//cout<<victim_search<<endl;
							//cout<<bin2hex(victim_search)<<endl;

							victim_match_block=find(victim[cache_no].victimset.victim_TAG.begin(),victim[cache_no].victimset.victim_TAG.end(),bin2hex(victim_search))-victim[cache_no].victimset.victim_TAG.begin();
							//cout<<"victim match"<<victim_match_block<<endl;
							//cout<<"Victim size"<<victim[cache_no].victimset.victim_TAG.size()<<endl;


							unsigned int victim_assoc=find(victim[cache_no].victimset.valid.begin(),victim[cache_no].victimset.valid.end(),false)-victim[cache_no].victimset.valid.begin();
							//cout<<"Victim_First_invalid="<<victim_assoc<<endl;
							//cout<<"Victim match block "<<victim_match_block<<endl;
							if(victim_match_block>=victim[cache_no].victimset.victim_TAG.size()&&(victim_assoc>=victim[cache_no].victimset.valid.size())) //Not found in victim
							{
								
								//find LRU, evict if not dirty, if dirty write to level 2
								
								unsigned int victim_LRU_replace=	distance(victim[cache_no].victimset.LRU.begin(),(max_element(victim[cache_no].victimset.LRU.begin(),victim[cache_no].victimset.LRU.end())));
								//cout<<"victim Lru "<<victim[0].victimset.victim_TAG[0]<<endl;
								bool victim_dirty_replace=victim[cache_no].victimset.dirty[victim_LRU_replace];
								
								//cout<<"victim dirty working"<<endl;
								if(victim_dirty_replace==true)
								{
									//cout<<"VICTIM LRU Dirty for write request to cache0"<<endl;
									
									string victim_write_back=hex2bin(victim[cache_no].victimset.victim_TAG[victim_LRU_replace]);
									victim_write_back.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');
									victim_write_back=victim_write_back.substr(victim_write_back.length()-32);
									victim_write_back=bin2hex(victim_write_back);

									victim[cache_no].victimset.dirty[victim_LRU_replace]==false;

									if(cache_no!=C_NUM-1) //if it's not the last cache 
									{

										cachep[cache_no].WRITE_BACKS++;
										write_request(victim_write_back,(cache_no+1));

									}

									else
									{
										cachep[cache_no].WRITE_BACKS++;
										memory_traffic++; //Last cache level, writing back to memory
									}	

								}	//write back to next level end here

								if(cache_no!=C_NUM-1)
								{

									hit=read_request(bin2hex(read_addr),(cache_no+1));
								}

								else
								{
									memory_traffic++;
								}	

								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								//finding LRU in cache level and sending it to victim

								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								victim_replace.append(INDEX);
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								victim_replace=bin2hex(victim_replace);
								victim[cache_no].victimset.victim_TAG[victim_LRU_replace]=victim_replace;
								victim[cache_no].victimset.dirty[victim_LRU_replace]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								victim[cache_no].victimset.LRU[victim_LRU_replace]=0;
								victim[cache_no].victimset.valid[victim_LRU_replace]=true;
								//Update victim LRU's

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)
								{
									if(victim[cache_no].victimset.valid[i]==true&&(i!=victim_LRU_replace))
											victim[cache_no].victimset.LRU[i]++;
								}	

								//Update L1 now

								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
								cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;

								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}		

								//L1 write back completed


							}



							else if (victim_match_block>=victim[cache_no].victimset.victim_TAG.size()&&(victim_assoc<victim[cache_no].victimset.valid.size()))
							{	//Not found, victim has space

								//cout<<"Not found and victim has space"<<endl;
								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								//cout<<"Victim_repalce"<<victim_replace<<endl;
								victim_replace.append(INDEX);
								//cout<<"Victim_repalce"<<victim_replace<<endl;
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								//cout<<"Victim_repalce"<<victim_replace<<endl;
								victim_replace=bin2hex(victim_replace);
								//cout<<"Victim_repalce"<<victim_replace<<endl;

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)  //updating LRU first for victim and then adding tag
								{
									if(victim[cache_no].victimset.valid[i]==true)
										victim[cache_no].victimset.LRU[i]++;
								}	
								victim[cache_no].victimset.victim_TAG[victim_assoc]=victim_replace;
								victim[cache_no].victimset.valid[victim_assoc]=true;
								victim[cache_no].victimset.dirty[victim_assoc]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								victim[cache_no].victimset.LRU[victim_assoc]=0;

								if(cache_no!=C_NUM-1)
								{

									hit=read_request(bin2hex(read_addr),(cache_no+1));
								}
								else
								{

									memory_traffic++;
								}	

								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
								cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;

								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}	




							}

							else //found in victim
							{
								victimp[cache_no].SWAP_NO++;
								LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
								string victim_replace=hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]);
								victim_replace.append(INDEX);
								victim_replace=victim_replace.substr(victim_replace.length()-32);
								victim_replace=bin2hex(victim_replace);

								//repalacing tag;
								string cache_replace=hex2bin(victim[cache_no].victimset.victim_TAG[victim_match_block]);
								cache_replace=cache_replace.substr(0,(cache_replace.length()-cachep[cache_no].INDEX_SIZE));
								cache_replace=bin2hex(cache_replace);
								string temp_var;
								victim[cache_no].victimset.victim_TAG[victim_match_block]=victim_replace;
								cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=cache_replace;
								bool dirty_temp=victim[cache_no].victimset.dirty[victim_match_block];
								victim[cache_no].victimset.dirty[victim_match_block]=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
								cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=dirty_temp;

								//swapping completed, updating LRU

								for(unsigned int i=0;i<victim[cache_no].victimset.LRU.size();i++)
								{
									if(victim[cache_no].victimset.valid[i]==true&&(victim[cache_no].victimset.LRU[i]<victim[cache_no].victimset.LRU[victim_match_block]))
											victim[cache_no].victimset.LRU[i]++;
								}	
								victim[cache_no].victimset.LRU[victim_match_block]=0;

								cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;


								for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
								{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
								}		

							} //found in victim ends

						}


						else
						{	

						//cout<<"Read request,Tag No Match, Set full "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;
						LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
						dirty_replace=cache[cache_no].cacheset[INDEX1].dirty[LRU_replace];
						
						if(dirty_replace==true)    //perform a write request to next level
 						   {
							//if(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].length()==8)
							//rep_addr.append((cache[cache_no].cacheset[INDEX1].TAG[LRU_replace].substr(2)));
						         //}						
							//else
							rep_addr.append(hex2bin(cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]));				
							//cout<<hex2bin(rep_addr)<<endl;
							
					        rep_addr.append(INDEX);
							
							//cout<<"   "<<INDEX<<endl;
							rep_addr.append(cachep[cache_no].BLOCK_OFFSET_BITS,'0');//add random block bits
							rep_addr=rep_addr.substr(rep_addr.length()-32);
							//cout<<rep_addr<<endl;
							rep_addr=bin2hex(rep_addr);
							//cout<<rep_addr<<endl;
							
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							if(cache_no!=C_NUM-1)//check if it's the last cache
							{
								cachep[cache_no].WRITE_BACKS++;
								write_request(rep_addr,(cache_no+1));
							}
							else
							{
								cachep[cache_no].WRITE_BACKS++;
								memory_traffic++;
							}
						    }
							
							if(cache_no!=C_NUM-1)
							{//check if it's not the last cache
							
							hit=read_request(bin2hex(read_addr), (cache_no+1));
							}
							else
							{
								memory_traffic++;
							}	
							cache[cache_no].cacheset[INDEX1].dirty[LRU_replace]=false;
							cache[cache_no].cacheset[INDEX1].valid[LRU_replace]=true;
							cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
							cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;
							for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
							{
								if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=LRU_replace))
								{
									cache[cache_no].cacheset[INDEX1].LRU[i]++;
								}	
							}
						}
				return 1;		
		    } 
		else //tag doesn't match and there is space
			{
					//cout<<"Read request,Tag No Match, Set Space "<<bin2hex(read_addr)<<" Cache No : "<<cache_no<<endl;	
				if(cache_no!=C_NUM-1)//check if it's the last cache
					{	
						//cout<<"Sending read request "<<endl;
						hit=read_request(bin2hex(read_addr),(cache_no+1));
					}
				else
				{
					memory_traffic++;
				}
			
					cache[cache_no].cacheset[INDEX1].dirty[assoc]=false;
					cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
					cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
					cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
			{
				if(cache[cache_no].cacheset[INDEX1].valid[i]==true&&(i!=assoc))
					cache[cache_no].cacheset[INDEX1].LRU[i]++;
			}	
				
		
		
	
		return 1;
		
		}
		
	
}
}
	
	
				
			

int main(int argc, char* argv[])
{
	if(argc!=8)
	{
		cout<<"Incorrect arguments, Exiting"<<endl;
		return 0;
	}
	else
		//cout<<"No of arguments is "<<argc<<endl;
	
		if(atoi(argv[5])==0)
		   C_NUM=1;
		
		victimp[0].BLOCKSIZE=atoi(argv[1]);
		victimp[1].BLOCKSIZE=0;
		
		
		cachep.resize(C_NUM);
		
		for(unsigned int i=0;i<C_NUM;i++)
		{
				
				cachep[i].BLOCKSIZE=atoi(argv[1]);
				cachep[i].SIZE=atoi(argv[(3*i)+2]);
				cachep[i].ASSOC=atoi(argv[(3*i)+3]);
				cachep[i].SET_NO=cachep[i].SIZE/(cachep[i].BLOCKSIZE*cachep[i].ASSOC);
				cachep[i].INDEX_SIZE=log2(cachep[i].SET_NO);
				cachep[i].BLOCK_OFFSET_BITS=log2 (cachep[i].BLOCKSIZE);
				cachep[i].READS=0;
				cachep[i].READS_MISSES=0;
				cachep[i].WRITE=0;
				cachep[i].WRITES_MISSES=0;
				cachep[i].WRITE_BACKS=0;
				victimp[i].SWAP_RATE=0;
				victimp[i].SWAP_NO=0;
				
				
		}
	//Manually VICTIM initialization

		victimp[0].BLOCKSIZE=atoi(argv[1]);
		victimp[1].BLOCKSIZE=0;
		victimp[0].SET_NO=1;
		victimp[1].SET_NO=0;
		victimp[0].ASSOC=atoi(argv[4]);
		victimp[1].ASSOC=0;
		victim[0].victimset.victim_TAG.resize(victimp[0].ASSOC);
		victim[0].victimset.LRU.resize(victimp[0].ASSOC);
		victim[0].victimset.dirty.resize(victimp[0].ASSOC);
		victim[0].victimset.valid.resize(victimp[0].ASSOC);

	//VIctim Initialization ended	
		
		cout<<"===== Simulator configuration ====="<<endl;
		
		cout<<"BLOCKSIZE:"<<setw(15)<<argv[1]<<endl;
		cout<<"L1_SIZE:"<<setw(19)<<argv[2]<<endl;;
		cout<<"L1_ASSOC:"<<setw(15)<<argv[3]<<endl;
		cout<<"VC_NUM_BLOCKS:"<<setw(11)<<argv[4]<<endl;
		cout<<"L2_SIZE:"<<setw(19)<<argv[5]<<endl;
		cout<<"L2_ASSOC:"<<setw(15)<<argv[6]<<endl;
		cout<<"trace_file:"<<setw(25)<<argv[7]<<endl;
		

			
		
		
	
		cache.resize(C_NUM);
	
		for(unsigned int i=0;i<C_NUM;i++)
		{
			//cout<<cachep[i].SET_NO<<endl;
			cache[i].cacheset.resize(cachep[i].SET_NO);
			
		}
	
	
	for(unsigned int i=0;i<C_NUM;i++)
	{
			for(unsigned int j=0;j<cachep[i].SET_NO;j++)
				{
					cache[i].cacheset[j].TAG.resize(cachep[i].ASSOC);  
					cache[i].cacheset[j].LRU.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].valid.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].dirty.resize(cachep[i].ASSOC);
					//cout<<cache[i].cacheset[j].LRU.size()<<endl;
			    }
			}
	
	caches_init();
	int hit;
	ifstream trace_file(argv[7]);
	string linebuffer;
	string rw;
	int count=0;

	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
  		rw=linebuffer.substr(0,1);
		linebuffer=trace_address(linebuffer.substr(2));
		if(rw[0]=='w')
		{
			count++;
			//cout<<"Iteration number= "<<count;
			//cout<<"Sending write request to cache0 for Address "<<linebuffer<<endl;
			
			write_request(linebuffer,0);
		}
		if(rw[0]=='r')
		{	
			count++;
			//cout<<"Iteration number= "<<count;
			//cout<<"Sending read request to cache0 for Address "<<linebuffer<<endl;
			
			hit=read_request(linebuffer,0);

		}
		//write_request(linebuffer,1);
		
		
		//cout<<linebuffer<<endl;
	}										 
										 
	//cout<<"Hi";
	//cout<<"Victim=   "; 
	//int z=find(victim[0].victimset.LRU.begin(),victim[0].victimset.LRU.end(),2)-victim[0].victimset.LRU.begin();
	//cout<<victim[0].victimset.LRU[5]<<endl;


	
	



	


	for(unsigned int i=0;i<C_NUM;i++)
	{
		cout<<endl;
		cout<<"===== L"<<i+1<<" contents ====="<<endl;
		for(unsigned int j=0;j<cachep[i].SET_NO;j++)
		{
			cout<<" SET   "<<j<<":   ";
			for(unsigned int k=0;k<cachep[i].ASSOC;k++)
			{
				
				unsigned int z=find(cache[i].cacheset[j].LRU.begin(),cache[i].cacheset[j].LRU.end(),k)-cache[i].cacheset[j].LRU.begin();
				if(cache[i].cacheset[j].valid[z]==true)
				{	
				
				cout<<"    "<<cache[i].cacheset[j].TAG[z];
				if(cache[i].cacheset[j].dirty[z]==true)
					cout<<"  D";
				}
			} 
			cout<<endl;
			
		} 


		if(victimp[i].ASSOC != 0)
		{
			cout<<endl<<"===== VC contents ====="<<endl;
			cout<<" SET 0: ";
			for(unsigned int i=0;i<victimp[0].ASSOC;i++)
			{
				unsigned int z=find(victim[0].victimset.LRU.begin(),victim[0].victimset.LRU.end(),i)-victim[0].victimset.LRU.begin();
				if (victim[0].victimset.valid[z]==true)
				{	

				cout<<"  "<<victim[0].victimset.victim_TAG[z];
				if(victim[0].victimset.dirty[z]==true)
					cout<< " D"<<setw(3);
				}			
			}

			cout<<endl;


		}

	}
	
	victimp[0].SWAP_REQUEST=(float)victimp[0].SWAP_RATE/((float)cachep[0].READS+(float)cachep[0].WRITE);
	cachep[0].MISS_RATE=((float)cachep[0].READS_MISSES+(float)cachep[0].WRITES_MISSES-(float)victimp[0].SWAP_NO)/((float)cachep[0].READS+(float)cachep[0].WRITE);
	if(C_NUM==2)
	{
		cachep[1].MISS_RATE=((float)cachep[1].READS_MISSES)/((float)cachep[1].READS);
	}
	char ch ='a';
	cout<<endl<<"===== Simulation results ====="<<endl;
	
		
		cout<<ch++<<". "<<"number of L1 reads:"<<setw(16)<<cachep[0].READS<<endl;
		cout<<ch++<<". number of L1 read misses:"<<setw(9)<<cachep[0].READS_MISSES<<endl;
		cout<<ch++<<". number of L1 writes:"<<setw(15)<<cachep[0].WRITE<<endl;
		cout<<ch++<<". number of L1 write misses:"<<setw(8)<<cachep[0].WRITES_MISSES<<endl;
		cout<<ch++<<". number of swap requests:"<<setw(12)<<victimp[0].SWAP_RATE<<endl;
		cout<<ch++<<". swap request rate:"<<setw(18)<<setprecision(4)<<fixed<<victimp[0].SWAP_REQUEST<<endl;
		cout<<ch++<<". number of swaps:"<<setw(18)<<victimp[0].SWAP_NO<<endl;
		cout<<ch++<<". combined L1+VC miss rate:"<<setw(8)<<setprecision(4)<<fixed<<cachep[0].MISS_RATE<<endl;
		cout<<ch++<<". number writebacks from L1/VC:"<<setw(5)<<cachep[0].WRITE_BACKS<<endl;  
	if(C_NUM==2)
	{
		cout<<ch++<<". "<<"number of L2 reads:"<<setw(16)<<cachep[1].READS<<endl;
		cout<<ch++<<". number of L2 read misses:"<<setw(9)<<cachep[1].READS_MISSES<<endl;
		cout<<ch++<<". number of L2 writes:"<<setw(15)<<cachep[1].WRITE<<endl;
		cout<<ch++<<". number of L2 write misses:"<<setw(8)<<cachep[1].WRITES_MISSES<<endl;
		cout<<ch++<<". L2 miss rate:"<<setw(22)<<setprecision(4)<<fixed<<cachep[1].MISS_RATE<<endl;
		cout<<ch++<<". number of writebacks from L2:"<<setw(5)<<cachep[1].WRITE_BACKS<<endl;
		

		
	}

	else

		{
		cout<<ch++<<". "<<"number of L2 reads:"<<setw(16)<<"0"<<endl;
		cout<<ch++<<". number of L2 read misses:"<<setw(9)<<"0"<<endl;
		cout<<ch++<<". number of L2 writes:"<<setw(15)<<"0"<<endl;
		cout<<ch++<<". number of L2 write misses:"<<setw(8)<<"0"<<endl;
		cout<<ch++<<". L2 miss rate:"<<setw(22)<<"0.0000"<<endl;
		cout<<ch++<<". number of writebacks from L2:"<<setw(5)<<"0"<<endl;
		

		}	
	cout<<ch++<<". total memory traffic: "<<memory_traffic<<endl;
	
	return 0;
}

string trace_address(string line_elem)
{
	//int len;
	//len=line_elem.length();
	string addre=line_elem;
	string addre_new;
	if(addre.length()<8)
	{
		addre_new.append(8-(addre.length()),'0');
		addre_new.append(addre);
		return addre_new;
	}
	else
		return addre;
}

string hex2bin(string addre_hex)
{
	
	int addre_bin;
	istringstream st(addre_hex);
	st>>hex>>addre_bin;;
	
	bitset<32> bits(addre_bin);
	
	string address_binary(bits.to_string());
	return address_binary;
	
}	

string bin2hex(string addre_binary)
{
	bitset<32> set(addre_binary);
	stringstream address_hex;
	string address_hex1;
	address_hex << hex<< set.to_ulong();
	//address_hex1=trace_address(address_hex.str());
	return address_hex.str();
}


int bin2dec(string addre_binary)
{
	unsigned int value;
	//value=stoull(addre_binary,0,2);
	bitset<64> set(addre_binary);
	value=set.to_ulong();
	return value;
}
		
	
	


				
				
				
