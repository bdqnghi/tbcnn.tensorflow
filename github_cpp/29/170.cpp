
#include "bloom_inout.hpp"
using namespace std;


int main(int argc, char* argv[]) {
   vector<unsigned int> word_list;
	bloom_inout inout;
	//LOAD WORD LIST
	if (!inout.load_word_list(argc,argv,word_list)) return 1;
	const double expected_fpp = 1.0 / word_list.size();
	unsigned int random_seed = 0;
	cout << "fichero size: " << word_list.size() << endl;
	bloom_parameters parameters(word_list.size(), expected_fpp, ++random_seed); //iniciar parametros
		bloom_filter filter(parameters); //iniciar filtro con parametros optimos
		filter.insert(word_list.begin(),word_list.end()); //insertar lista de palabras

		//COMPROBAMOS SI ALGUNA PALABRA DE LAS INEXISTENTES, 
		//LA DETECTA COMO EXISTENTE, PARA CONTARLA COMO FALSO POSITIVO
		//current_falsep = filter.contains(outliers.begin(), outliers.end());

   return 0;
}



