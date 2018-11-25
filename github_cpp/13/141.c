




#include "Bubble.h"







Bubble::Bubble( sc_module_name name )

{
	
}







Bubble::~Bubble()
{
	
}







void Bubble::thread(void)
{
	

}







void Bubble::bubbleSort(unsigned int *ptr, int counter)
{
	
	unsigned int tmp = 0;
	
	for (int i = 1; i < counter; ++i){
		for (int j = 0; j < counter - i; ++j){
			if (ptr[j] > ptr[j + 1]){
				
				tmp = ptr[j];
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = tmp;
			}
	
		}
	}
	
	for (int i = 0; i < counter; i++)
		cout << ptr[i] << endl;
}
