#include <iostream>
#include "cmn.cpp"

template <typename T>
void move(T *data,int idx,const size_t step){
	T value=*(data+idx);
	for(int jdx=idx-step;jdx>=0;jdx-=step){
		if(value<*(data+jdx)){
			*(data+jdx+step)=*(data+jdx);
			if(jdx<step){
				*(data+jdx)=value;
				break;
			}
		}
		else{
			*(data+jdx+step)=value;
				break;
		}
	}
}

template <typename T>
void sortSubData(T *data,const size_t cnt,const size_t startIdx,const size_t step){
	for(size_t idx=startIdx+step;idx<cnt;idx+=step){
		move(data,idx,step);
	}
}

template <typename T>
void sortRecurrence(T *data,const size_t cnt,size_t step=0){
	step=step==0?cnt/2:step;
	if(step>=1){
		step=step%2?step:step+1;
		for(size_t idx=0;idx<step;++idx){
			sortSubData(data,cnt,idx,step);
		}
		if(step!=1){
			sortRecurrence(data,cnt,step/2);
		}
	}
	// for(step=step==0?cnt/2:step;step>=1;step/=2){
	// 	step=step%2?step:step+1;
	// 	for(size_t idx=0;idx<step;++idx){
	// 		sortSubData(data,cnt,idx,step);
	// 	}
	// }
}

void testRecurrence(const size_t cnt,const size_t mod){
	using std::cout;
	using std::endl;

	int *data=getRandData(cnt,mod);
	cout << endl << "Insert Sort Recurrence:" << endl << "Befor Sorted:";
	showData(data,cnt);

	sortRecurrence(data,cnt);
	cout << endl << "After Sorted:";
	showData(data,cnt);

	cout << endl << endl;
	delete[] data;
}



template <typename T>
void sortSimple(T *data,const size_t cnt){
	//Decrice step
	for(size_t step=cnt/2;step>=1;step/=2){
		step=step%2?step:step+1;
		//std::cout << std::endl << " Step:" << step << std::endl;
		for(size_t idx=0;idx<step;++idx){
			//std::cout << "  Idx:" << idx << std::endl;
			for(size_t jdx=idx+step;jdx<cnt;jdx+=step){
				T value=*(data+jdx);
				for(int kdx=jdx-step;kdx>=0;kdx-=step){
					if(value<*(data+kdx)){
						*(data+kdx+step)=*(data+kdx);
						if(kdx<step){
							*(data+kdx)=value;
							break;
						}
					}
					else{
						*(data+kdx+step)=value;
						break;
					}
				}
				// std::cout << "   Jdx:" << jdx << " Data:" ;
				// showData(data,cnt,idx,step);
				// std::cout << std::endl;
			}
		}
		// std::cout << "After Sorted:";
		// showData(data,cnt);
		// std::cout << std::endl;
	}
}

void testSimple(const size_t cnt,const size_t mod){
	using std::cout;
	using std::endl;

	int *data=getRandData(cnt,mod);

	cout << endl << "Selec Sort Simple:" << endl << "Befor Sorted:";
	showData(data,cnt);

	sortSimple(data,cnt);
	cout << endl << "After Sorted:";
	showData(data,cnt);

	cout << endl << endl;
	delete[] data;
}

int main(int argc,char **argv){

	const size_t CNT=10;
	const size_t MOD=50;

	testSimple(CNT,MOD);
	testRecurrence(CNT,MOD);

	return 0;
}