
#include "bloom_inout.hpp"
using namespace std;


int main(int argc, char* argv[]) {
   vector<string> word_list;
   deque<string> outliers;
	bloom_inout inout;
	//LOAD WORD LIST
	if (!inout.load_word_list(argc,argv,word_list)) return 1;

	inout.generate_outliers(word_list,outliers);
	printf("Round\t   Queries\t   FPQ\t   IPFP\t           PFP\t            DPFP\n");

	//CONTADORES
	const double expected_fpp = 1.0 / word_list.size();
	unsigned int word_list_storage_size = 0;
	for (unsigned int i = 0; i < word_list.size(); ++i)
			word_list_storage_size += word_list[i].size();
	unsigned int random_seed = 0;
	unsigned int total_number_of_queries = 0;
	unsigned int max_false_positive_count = 0;
	unsigned int min_false_positive_count = numeric_limits<unsigned int>::max();
	unsigned int total_fp = 0;
	unsigned int total_zero_fp = 0;
	unsigned long long int bloom_filter_size = 0;
	unsigned int current_falsep = 0;
	//double pfp;
	static const unsigned int rounds = 1000;
	
   //INICIAMOS RONDA DE PRUEBAS CON UNA SEMILLA CONCRETA CADA VEZ
	while (random_seed < rounds) {
		bloom_parameters parameters(word_list.size(), expected_fpp, ++random_seed); //iniciar parametros
		bloom_filter filter(parameters); //iniciar filtro con parametros optimos
		filter.insert(word_list.begin(),word_list.end()); //insertar lista de palabras

		current_falsep = 0;
		//creacion de palabras que no estan en el diccionario
		for (deque<string>::iterator it = outliers.begin(); it != outliers.end(); ++it)
				if (filter.contains(*it)) ++current_falsep;
 
		total_number_of_queries += (outliers.size() + word_list.size());

		// Probabilidad obtenida de falsos positivos
		double pfp = current_falsep / (1.0 * outliers.size());

		//actualizamos minimo y maximo falsos positivos
		if (current_falsep < min_false_positive_count) min_false_positive_count = current_falsep;
		else if (current_falsep > max_false_positive_count) max_false_positive_count = current_falsep;

		total_fp += current_falsep;
		//si no ha habido falsos positivos sumamos 1 al contador
		if (current_falsep == 0) ++total_zero_fp;
		bloom_filter_size = filter.size();

		printf("%6llu\t%10llu\t%6d\t%8.7f\t%8.7f\t%9.3f%%\n",
				static_cast<unsigned long long>(random_seed),
				static_cast<unsigned long long>(total_number_of_queries),
				current_falsep, expected_fpp, pfp,
				(100.0 * pfp) / expected_fpp);
	}

   double average_fpc = (1.0 * total_fp) / rounds;
   double average_fpp = average_fpc / (outliers.size() + word_list.size());

   printf("Bloom Filter Statistics\n"
          "MinFPC: %d\tMaxFPC: %d\tAverageFPC: %8.5f\tAverageFPP: %9.8f Zero-FPC:%d\n"
          "Filter Size: %lluKB\tData Size: %dKB\n",
          min_false_positive_count,
          max_false_positive_count,
          average_fpc,
          average_fpp,
          total_zero_fp,
          bloom_filter_size / (8 * 1024),
          static_cast<unsigned int>(word_list_storage_size / 1024));
   return 0;
}

/*
      Terminology
      MinFPC : Minimum (smallest) False Positive Count
      MaxFPC : Maximum (largest) False Positive Count
      AverageFPC : Average False Positive Count
      AverageFPP : Average False Positive Probability

      FPQ  : False Positive Queries
      IPFP : Indicative (desired) False Positive Probability
      PFP  : Probability of a False Positive (based on the FPQ)
      DPFP : Difference as a percentage between IPFP and PFP
		}*/