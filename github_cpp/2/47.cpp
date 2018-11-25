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





int C_NUM=1;
int memory_traffic=0;
int num_processors=0;
int memory_flush=0;

struct cache_params{
int SIZE,BLOCKSIZE,ASSOC,SET_NO,TAG_SIZE,INDEX_SIZE,BLOCK_OFFSET_BITS;
				int READS,READS_MISSES,WRITE,WRITES_MISSES,WRITE_BACKS;
				int SWAP_RATE,SWAP_NO;
				float SWAP_REQUEST,MISS_RATE;
				int intervention, invalidations;
				int bus_rdx,memory_flush,memory_trans;
				int someone,cache2cache;
				
};

vector<cache_params> cachep;
vector<cache_params> victimp;


class cache_set{
			public:
				
	
				vector<string> TAG;
				vector<bool> valid;
				vector<bool> dirty;
				vector<int> LRU;
				vector<int> state; 
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
vector<victim_cache> victim;


void caches_init()
{
	for(int i=0;i<num_processors;i++)
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
				cache[i].cacheset[j].state[k]=0;
			}
			
		}
	}

	
	
	
	}

string trace_address(string);
string hex2bin(string);
string bin2hex(string);
int bin2dec(string);
int read_request(string,int);
void write_request(string,int);
void write_request1(string,int);
int read_request1(string,int);
void write_request2(string,int);
int read_request2(string,int);

void write_request(string write_addr,int cache_no)
{
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	int dirty_replace;
	string rep_addr;
	int hit;
	
	cachep[cache_no].WRITE++;
	
	write_addr=hex2bin(write_addr);
	
	TAG=write_addr.substr(0,(write_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=write_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	
	TAG=bin2hex(TAG);
	INDEX1=bin2dec(INDEX);
	int victim_match_block;

	
	
	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].state.begin(),cache[cache_no].cacheset[INDEX1].state.end(),0)-cache[cache_no].cacheset[INDEX1].state.begin();
	if(assoc>=cache[cache_no].cacheset[INDEX1].state.size())  
	{
		unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) 
		{

			cachep[cache_no].WRITES_MISSES++;
			
			LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[LRU_replace];
			if(dirty_replace==2)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}

			

			cache[cache_no].cacheset[INDEX1].state[LRU_replace]=2; 
			cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;

			cachep[cache_no].bus_rdx++;
			
			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2||current_state==1) 
								{
									if(current_state==2)
										{
												cachep[i].WRITE_BACKS++;
												cachep[i].memory_flush++;
											}	
									
									
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;
									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;

								}	


							}

						}
				}
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[LRU_replace])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;
		

		}
		else 
		{
			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;

			if(cache[cache_no].cacheset[INDEX1].state[TAG_match]==1)
			{
				
				cachep[cache_no].someone++;
				cachep[cache_no].bus_rdx++;
				for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2||current_state==1) 
								{
									if(current_state==2)
											{
												cachep[i].WRITE_BACKS++;
												cachep[i].memory_flush++;
											}

									
									
									
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;
									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;


								}	


							}

						}
					}
						

			}
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
			cache[cache_no].cacheset[INDEX1].state[TAG_match]=2;

			


		}
	}
	else 
	{
		unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) 
		{

			cachep[cache_no].WRITES_MISSES++;
			
			

			
			cachep[cache_no].bus_rdx++;
			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2||current_state==1) 
								{
									if(current_state==2)
												{
												cachep[i].WRITE_BACKS++;
												cachep[i].memory_flush++;
											}

									
									
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;
									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;


								}	


							}

						}
				}

			cache[cache_no].cacheset[INDEX1].state[assoc]=2; 
			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;
		}	
		else 
		{
			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			if(cache[cache_no].cacheset[INDEX1].state[TAG_match]==1)
			{
				
				cachep[cache_no].someone++;
				cachep[cache_no].bus_rdx++;
				for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2||current_state==1) 
								{
									if(current_state==2)
											{
												cachep[i].WRITE_BACKS++;
												cachep[i].memory_flush++;
											}

									
									
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;
									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
								cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;

								}	


							}

						}
					}

			}
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
			cache[cache_no].cacheset[INDEX1].state[TAG_match]=2;	


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
	int dirty_replace;
	string rep_addr;
	int TAG_match=-1;
	int hit;
	
	
	read_addr=hex2bin(read_addr);
	TAG=read_addr.substr(0,(read_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=read_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	TAG=bin2hex(TAG);
	
	unsigned int victim_match_block;
	INDEX1=bin2dec(INDEX);

	

	
	
	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].state.begin(),cache[cache_no].cacheset[INDEX1].state.end(),0)-cache[cache_no].cacheset[INDEX1].state.begin();
	if(assoc>=cache[cache_no].cacheset[INDEX1].state.size())  
	{

		unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) 
		{

			cachep[cache_no].READS_MISSES++;
			

			LRU_replace=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[LRU_replace];
			if(dirty_replace==2)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}

			

			cache[cache_no].cacheset[INDEX1].state[LRU_replace]=1; 
			cache[cache_no].cacheset[INDEX1].TAG[LRU_replace]=TAG;
			

			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2) 
								{
									
									cachep[i].WRITE_BACKS++;
												
											
									cachep[i].memory_flush++;
									
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=1; 
									cachep[i].intervention++;
								


									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]<cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]++;

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=0;

								}	


							}


						}	



				}
			
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[LRU_replace])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[LRU_replace]=0;

		}
		
		else  
		{
			

			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
			

		}  


	}

	else 
	{
		
		unsigned int TAG_match=find(cache[cache_no].cacheset[INDEX1].TAG.begin(),cache[cache_no].cacheset[INDEX1].TAG.end(),TAG)-cache[cache_no].cacheset[INDEX1].TAG.begin();
		if(TAG_match>=cache[cache_no].cacheset[INDEX1].TAG.size()) 
		{
			cachep[cache_no].READS_MISSES++;
			
				for(int i=0;i<num_processors;i++)  
				{
						
						if(i!=cache_no)
						{
							
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2) 
								{
									cachep[i].WRITE_BACKS++;
									cachep[i].memory_flush++;
									
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=1; 
									cachep[i].intervention++;

									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]<cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]++;

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=0;

								}	


							}


						}	



				}

				cache[cache_no].cacheset[INDEX1].state[assoc]=1; 
				
				cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;

				for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	

				cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;




		}
		else 
		{
			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;

		}	





	}	





return 1;
}
	
	
				
			

int main(int argc, char* argv[])
{
	if(argc!=7)
	{
		cout<<"Incorrect arguments, Exiting"<<endl;
		return 0;
	}
	else
		
	
		
		C_NUM=1;
		
		int protocol= atoi(argv[5]);
		num_processors=atoi(argv[4]);

		
		victimp.resize(num_processors);
		victim.resize(num_processors);
		cachep.resize(num_processors);
		
		for(unsigned int i=0;i<num_processors;i++)
		{
				
				cachep[i].BLOCKSIZE=atoi(argv[3]);
				cachep[i].SIZE=atoi(argv[1]);
				cachep[i].ASSOC=atoi(argv[2]);
				cachep[i].SET_NO=cachep[i].SIZE/(cachep[i].BLOCKSIZE*cachep[i].ASSOC);
				cachep[i].INDEX_SIZE=log2(cachep[i].SET_NO);
				cachep[i].BLOCK_OFFSET_BITS=log2 (cachep[i].BLOCKSIZE);
				cachep[i].READS=0;
				cachep[i].READS_MISSES=0;
				cachep[i].WRITE=0;
				cachep[i].WRITES_MISSES=0;
				cachep[i].WRITE_BACKS=0;
				cachep[i].intervention=0;
				cachep[i].invalidations=0;
				cachep[i].bus_rdx=0;
				cachep[i].memory_flush=0;
				cachep[i].memory_trans=0;
				cachep[i].cache2cache=0;
				victimp[i].SWAP_RATE=0;
				victimp[i].SWAP_NO=0;
				
				
		}
	

	for (int i=0;i<num_processors;i++)
	{	
		victimp[i].BLOCKSIZE=0;
		
		victimp[i].SET_NO=1;
		
		victimp[i].ASSOC=0;
		
		
	}	
	
		cache.resize(num_processors);
	
		for(unsigned int i=0;i<num_processors;i++)
		{
			
			cache[i].cacheset.resize(cachep[i].SET_NO);
			
		}
	
	
	for(unsigned int i=0;i<num_processors;i++)
	{
			for(unsigned int j=0;j<cachep[i].SET_NO;j++)
				{
					cache[i].cacheset[j].TAG.resize(cachep[i].ASSOC);  
					cache[i].cacheset[j].LRU.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].valid.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].dirty.resize(cachep[i].ASSOC);
					cache[i].cacheset[j].state.resize(cachep[i].ASSOC);
					
			    }
			}
	
	caches_init();
	int hit;
	ifstream trace_file(argv[6]);
	string linebuffer;
	string rw;
	int processor;
	int count=0;

	if(protocol==0)
	{	
	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
		
  		rw=linebuffer.substr(2,1);
  		string processor1=linebuffer.substr(0,1);
  		processor=atoi(processor1.c_str());
  		
		linebuffer=trace_address(linebuffer.substr(linebuffer.length()-8));

		if(rw[0]=='w')
		{
			count++;
			write_request(linebuffer,processor);
		}
		if(rw[0]=='r')
		{	
			count++;
			hit=read_request(linebuffer,processor);
			
		}
		
	}										 
	}	
	if(protocol==1)
	{	
	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
		
  		rw=linebuffer.substr(2,1);
  		string processor1=linebuffer.substr(0,1);
  		processor=atoi(processor1.c_str());
  		
		linebuffer=trace_address(linebuffer.substr(linebuffer.length()-8));

		if(rw[0]=='w')
		{
			count++;
			
			write_request1(linebuffer,processor);
		}
		if(rw[0]=='r')
		{	
			count++;
			
			hit=read_request1(linebuffer,processor);
			
		}
		
	}										 
	}

	if(protocol==2)
	{	
	while(trace_file && getline(trace_file, linebuffer)){
		
		if(linebuffer.length()==0) continue;
		
  		rw=linebuffer.substr(2,1);
  		string processor1=linebuffer.substr(0,1);
  		processor=atoi(processor1.c_str());
  		
		linebuffer=trace_address(linebuffer.substr(linebuffer.length()-8));

		if(rw[0]=='w')
		{
			count++;
			
			write_request2(linebuffer,processor);
		}
		if(rw[0]=='r')
		{	
			count++;
			
			hit=read_request2(linebuffer,processor);
			
		}
		
	}										 
	}

	
	printf("===== 506 Personal information =====\n");
	printf("Tushar Gupta\n");	
	printf("200108328\n");
	printf("ECE492 Students? NO\n");
	printf("===== 506 SMP Simulator configuration =====\n");
	printf("L1_SIZE:		%d\n",cachep[0].SIZE);
	printf("L1_ASSOC:		%d\n",cachep[0].ASSOC);
	printf("L1_BLOCKSIZE:		%d\n",cachep[0].BLOCKSIZE);
	printf("NUMBER OF PROCESSORS:	%d\n",num_processors);
	if(protocol == 0)
		printf("COHERENCE PROTOCOL:	MSI\n");
	else if(protocol == 1)
		printf("COHERENCE PROTOCOL:	MESI\n");
	else if(protocol == 2)
		printf("COHERENCE PROTOCOL:	Dragon\n");
	cout<<"TRACE FILE: "<<argv[6]<<endl;;

	
	



	
	for(unsigned int i=0;i<num_processors;i++)
	{
		cout<<"============ Simulation results (Cache "<<i<<") ============"<<endl;
		cout<<"01. number of reads: "<<cachep[i].READS<<endl;
		cout<<"02. number of read misses: "<<cachep[i].READS_MISSES<<endl;
		cout<<"03. number of writes: "<<cachep[i].WRITE<<endl;
		cout<<"04. number of write misses: "<<cachep[i].WRITES_MISSES<<endl;
		cout<<"05. total miss rate: "<<setprecision(2)<<fixed<<((float)cachep[i].READS_MISSES+(float)cachep[i].WRITES_MISSES)*(100)/((float)cachep[i].READS+(float)cachep[i].WRITE)<<"%"<<endl;
		cout<<"06. number of writebacks: "<<cachep[i].WRITE_BACKS<<endl;
		cout<<"07. number of cache-to-cache transfers: "<<cachep[i].cache2cache<<endl;
		cout<<"08. number of memory transactions: "<<cachep[i].someone+cachep[i].WRITE_BACKS+cachep[i].READS_MISSES+cachep[i].WRITES_MISSES-cachep[i].cache2cache<<endl;
		cout<<"09. number of interventions: "<<cachep[i].intervention<<endl;
		cout<<"10. number of invalidations: "<<cachep[i].invalidations<<endl;
		cout<<"11. number of flushes:  "<<cachep[i].memory_flush<<endl; 
		cout<<"12. number of BusRdX: "<<cachep[i].bus_rdx<<endl;
}
	
	return 0;
}


void write_request1(string write_addr,int cache_no)
{
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	int dirty_replace;
	string rep_addr;
	int hit;
	
	cachep[cache_no].WRITE++;
	
	write_addr=hex2bin(write_addr);
	
	TAG=write_addr.substr(0,(write_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=write_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	int TAG_match=-1;
	TAG=bin2hex(TAG);
	INDEX1=bin2dec(INDEX);
	int victim_match_block;

	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].state.begin(),cache[cache_no].cacheset[INDEX1].state.end(),0)-cache[cache_no].cacheset[INDEX1].state.begin();
	
	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].state[i]!=0)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}

	
	if(TAG_match!=-1)
	{
		
		
		int get_state=cache[cache_no].cacheset[INDEX1].state[TAG_match];

		if(get_state==1)
		{
			
			
			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{
								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==1) 
								{

									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;

								for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;	



								}
							}
						}
					}			
		}	


			cache[cache_no].cacheset[INDEX1].state[TAG_match]=2; 
			
			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;


	}
else
	{

		
		cachep[cache_no].WRITES_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].state.size()) 
		{
			assoc=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[assoc];
			if(dirty_replace==2)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}
			cache[cache_no].cacheset[INDEX1].TAG[assoc]='x';
			cache[cache_no].cacheset[INDEX1].state[assoc]=0;		

		}
		int other_copy=0;
		cachep[cache_no].bus_rdx++;
		for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{

								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								if(current_state==2||current_state==1||current_state==3) 
								{
									if(current_state==2)
										{
												cachep[i].WRITE_BACKS++;
												cachep[i].memory_flush++;
										}	
									
									
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]='x';
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									cachep[i].invalidations++;
									other_copy=1;
									
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]>cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]--;
											

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=cachep[i].ASSOC-1;

								}	


							}

						}
				}
	if(other_copy==1)
		cachep[cache_no].cache2cache++;

	cache[cache_no].cacheset[INDEX1].state[assoc]=2; 

	cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;

	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	

	cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;

	}


}





int read_request1(string read_addr,int cache_no)
{
	
	cachep[cache_no].READS++;	
	
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	int dirty_replace;
	string rep_addr;
	int TAG_match=-1;
	int hit;
	
	
	read_addr=hex2bin(read_addr);
	TAG=read_addr.substr(0,(read_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=read_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	TAG=bin2hex(TAG);
	
	unsigned int victim_match_block;
	INDEX1=bin2dec(INDEX);

	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].state.begin(),cache[cache_no].cacheset[INDEX1].state.end(),0)-cache[cache_no].cacheset[INDEX1].state.begin();
	
	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].state[i]!=0)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}

	if(TAG_match!=-1) 
	{
		

		
		
		cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].state[i]!=0))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
		cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;

	}

	else 
	{
		
		cachep[cache_no].READS_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].state.size()) 
		{
			assoc=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[assoc];
			if(dirty_replace==2)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}
			cache[cache_no].cacheset[INDEX1].TAG[assoc]='x';
			cache[cache_no].cacheset[INDEX1].state[assoc]=0;	
		}

		int lru_u=0;
		int proc_copy=0;
		
		for(int i=0;i<num_processors;i++)  
				{
						
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{
								
								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								
								if(current_state==2 || (current_state==3 || current_state==1))
								{
										if(current_state==2)
										{
											cachep[i].WRITE_BACKS++;
											cachep[i].memory_flush++;

										}
									cache[i].cacheset[INDEX1].TAG[TAG_match_processor]=TAG;	
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=1; 


									if(current_state==2 || current_state ==3)
									{	

										cachep[i].intervention++;
									}	
									proc_copy=1;
									if(0)
									{	
									for (unsigned int j=0;j<cache[i].cacheset[INDEX1].LRU.size();j++)
									{
										if((cache[i].cacheset[INDEX1].state[j]!=0)&&(cache[i].cacheset[INDEX1].LRU[j]<cache[i].cacheset[INDEX1].LRU[TAG_match_processor]))
										{
											cache[i].cacheset[INDEX1].LRU[j]++;

										}

									}
									cache[i].cacheset[INDEX1].LRU[TAG_match_processor]=0;
									if(current_state==1)
									     		lru_u=1;
								}	

								}	




							}
						}
				}	

			if(proc_copy==1)
				{	cache[cache_no].cacheset[INDEX1].state[assoc]=1; 
					cachep[cache_no].cache2cache++;
					}
			if(proc_copy==0) {
					cache[cache_no].cacheset[INDEX1].state[assoc]=3;  }	
			


			

			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].state[i]!=0)&&(cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc]))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	

			cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;



	}


return 1;


}	

void write_request2(string write_addr,int cache_no)
{
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	int dirty_replace;
	string rep_addr;
	int hit;
	
	cachep[cache_no].WRITE++;
	
	write_addr=hex2bin(write_addr);
	
	TAG=write_addr.substr(0,(write_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=write_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	int TAG_match=-1;
	TAG=bin2hex(TAG);
	INDEX1=bin2dec(INDEX);
	int victim_match_block;

	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	
	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].valid[i]!=false)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}

	if(TAG_match!=-1) 
	{
		int get_state=cache[cache_no].cacheset[INDEX1].state[TAG_match];

		
		if(get_state==2 || get_state==3)
		{

			cache[cache_no].cacheset[INDEX1].state[TAG_match]=2;
			cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]!=false))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;
		}

		if (get_state==0 || get_state ==1)
		{
			
			int proc_copy=0;
			
			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{
								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								proc_copy=1;

								if(current_state==1 || current_state==0) 
								{

									
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									

								



								}
							}
						}
				}	

			if(proc_copy==1)
			{
				cache[cache_no].cacheset[INDEX1].state[TAG_match]=1;
				cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;

			}
			if(proc_copy==0)
			{
				cache[cache_no].cacheset[INDEX1].state[TAG_match]=2;
				cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			}	

			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]!=false))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
			cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;

		


		}	



	}

	else 
	{
		cachep[cache_no].WRITES_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].state.size()) 
		{
			assoc=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[assoc];
			cache[cache_no].cacheset[INDEX1].valid[assoc]=false;
			if(dirty_replace==2 || dirty_replace==1)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}
		}
		int proc_copy=0;
		
		for(int i=0;i<num_processors;i++)
		{
			if(i!=cache_no)
			{

				int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
				if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size())
				{
					int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								
								if(current_state==3 || current_state==0) 
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0; 
										
								if(current_state==1 || current_state==2)
										{
											
											
											cachep[i].memory_flush++;
											cache[i].cacheset[INDEX1].state[TAG_match_processor]=1; 

										}
									
								if(current_state==2 || current_state==3)
										cachep[i].intervention++;

								cache[i].cacheset[INDEX1].TAG[TAG_match_processor]=TAG;	
					

					proc_copy=1;


				}	
			


			}

		}
		if(proc_copy==1)
		{
			cache[cache_no].cacheset[INDEX1].state[assoc]=1;
			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
			

			for(int i=0;i<num_processors;i++)  
				{
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{
								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								proc_copy=1;

								if(current_state==1 || current_state==0) 
								{
									
									
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0;
									

								



								}
							}
						}
				}	

		}

		if(proc_copy==0)
		{

			cache[cache_no].cacheset[INDEX1].state[assoc]=2;
			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
		}	

		for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc])&&(cache[cache_no].cacheset[INDEX1].valid[i]!=false))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
		cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;



	}	

}



int read_request2(string read_addr,int cache_no)
{
	
	cachep[cache_no].READS++;	
	
	string TAG;
	string INDEX;
	int INDEX1;
	unsigned int LRU_replace;
	int dirty_replace;
	string rep_addr;
	int TAG_match=-1;
	int hit;
	
	
	read_addr=hex2bin(read_addr);
	TAG=read_addr.substr(0,(read_addr.length()-cachep[cache_no].INDEX_SIZE-cachep[cache_no].BLOCK_OFFSET_BITS));
	INDEX=read_addr.substr(TAG.length(),cachep[cache_no].INDEX_SIZE);
	TAG=bin2hex(TAG);
	
	unsigned int victim_match_block;
	INDEX1=bin2dec(INDEX);

	unsigned int assoc=find(cache[cache_no].cacheset[INDEX1].valid.begin(),cache[cache_no].cacheset[INDEX1].valid.end(),false)-cache[cache_no].cacheset[INDEX1].valid.begin();
	
	for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
	{
		if((cache[cache_no].cacheset[INDEX1].valid[i]!=false)&&(TAG==cache[cache_no].cacheset[INDEX1].TAG[i]))
		   {
			TAG_match=i;
			 break;
		   } 
	}

	if(TAG_match!=-1) 
	{
		

		
		
		cache[cache_no].cacheset[INDEX1].TAG[TAG_match]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[TAG_match])&&(cache[cache_no].cacheset[INDEX1].valid[i]!=false))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	
		cache[cache_no].cacheset[INDEX1].LRU[TAG_match]=0;

	}

	else
	{
		cachep[cache_no].READS_MISSES++;
		if(assoc>=cache[cache_no].cacheset[INDEX1].state.size()) 
		{
			assoc=distance(cache[cache_no].cacheset[INDEX1].LRU.begin(),max_element(cache[cache_no].cacheset[INDEX1].LRU.begin(),cache[cache_no].cacheset[INDEX1].LRU.end()));
			dirty_replace=cache[cache_no].cacheset[INDEX1].state[assoc];
			cache[cache_no].cacheset[INDEX1].valid[assoc]=false;
			if(dirty_replace==2 || dirty_replace==1)  
				{
					cachep[cache_no].WRITE_BACKS++; 

				}
			
		}

		int lru_u=0;
		int proc_copy=0;
		
		for(int i=0;i<num_processors;i++)  
				{
						
						if(i!=cache_no)
						{
							int TAG_match_processor=find(cache[i].cacheset[INDEX1].TAG.begin(),cache[i].cacheset[INDEX1].TAG.end(),TAG)-cache[i].cacheset[INDEX1].TAG.begin();
							if(TAG_match_processor<cache[i].cacheset[INDEX1].TAG.size()) 
							{
								
								int current_state=cache[i].cacheset[INDEX1].state[TAG_match_processor];
								
								if(current_state==3 || current_state==0) 
									cache[i].cacheset[INDEX1].state[TAG_match_processor]=0; 
										
								if(current_state==1 || current_state==2)
										{
											
											
											cachep[i].memory_flush++;
											cache[i].cacheset[INDEX1].state[TAG_match_processor]=1; 

										}

								if(current_state==2 || current_state==3)
										cachep[i].intervention++;	

								cache[i].cacheset[INDEX1].TAG[TAG_match_processor]=TAG;	
									
								proc_copy=1;
									

									




							}
						}
				}	

			if(proc_copy==1)
				{	cache[cache_no].cacheset[INDEX1].state[assoc]=0; 
					cache[cache_no].cacheset[INDEX1].valid[assoc]=true;
					
				}

			if(proc_copy==0) {
					cache[cache_no].cacheset[INDEX1].state[assoc]=3; 
					cache[cache_no].cacheset[INDEX1].valid[assoc]=true; }	
			


			

			cache[cache_no].cacheset[INDEX1].TAG[assoc]=TAG;
			for(unsigned int i=0;i<cache[cache_no].cacheset[INDEX1].LRU.size();i++)
					{
						if((cache[cache_no].cacheset[INDEX1].LRU[i]<cache[cache_no].cacheset[INDEX1].LRU[assoc])&&(cache[cache_no].cacheset[INDEX1].valid[i]!=false))
							cache[cache_no].cacheset[INDEX1].LRU[i]++;
					}	

			cache[cache_no].cacheset[INDEX1].LRU[assoc]=0;



	}


return 1;

}	




string trace_address(string line_elem)
{
	
	
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
	
	long long int addre_bin;
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
	
	return address_hex.str();
}


int bin2dec(string addre_binary)
{
	unsigned int value;
	
	bitset<64> set(addre_binary);
	value=set.to_ulong();
	return value;
}




		
	
	


				
				
				
