#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "omp.h"
#include "math.h"
#include "time.h"

#include "LogDog.h"
#include "FileReader.h"
#include "OrderAlgorithmFactory.h"
#include "Merge.h"


#define SAMPLE_SIZE 1000




#define ONLYONCE 0
#define ALGN 1

bool isOrderCorrectly(int *vett, int vett_n)
{
    for(int i = 0; i < (vett_n - 1); i++)
    {
        if(vett[i] > vett[i+1]) return false;
    }

    return true;
}

void dispperc(int n, int max)
{
    int perc = ((double) n / max) * 100;
    printf("\rProgresso: %d%%", perc);
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    
    
    
    char *input_file = (char *) "../Merge-sort/big.in";
    
    

	
	LogDog::setOutputLevel(0);
    LogDog::printSpam((char *)"Inizializzazione conclusa con successo");
	
    
    int sel_n = 0;
    int sel[10];

    int oneexec = 0;
	
	for (int i = 0; i < argc; i++)
	{
		
		if(! strcmp(argv[i], "-i"))
		{
			input_file=argv[i+1];
            LogDog::printSpam((char *)"File in ingresso:");
			LogDog::printSpam(input_file);
		}


		
		if(! strcmp(argv[i], "-d"))
		{
			LogDog::setOutputLevel(atoi(argv[i+1]));
		}

        if(!strcmp(argv[i], "-a")){
            sel[0] = atoi ( argv[i+1]) ;
            oneexec = 1;
        }
	}

    if(ONLYONCE)
    {
        sel[0] = ALGN;
        sel_n=1;
        oneexec = 1;
    }

	
	FileReader *x = new FileReader(input_file);

	
    if(x->n_values < 100)
		LogDog::printInfo(LogDog::vectorToString(x->array, x->n_values));

	
	char s[60];
    sprintf(s, "[OMP] Numero di core: %d\n", omp_get_num_procs());
	LogDog::printInfo(s);

	

	
	OrderAlgorithmFactory *factory = new OrderAlgorithmFactory();
    Merge::setModes(G_MERGE_F, MEMCPY);

	bool exit = false;

	while(!exit)
	{
        if(! oneexec ){
            
            printf("Selezionare l'algoritmo da testare\n");
            for(int i = 0; i < factory->getCount(); i++) printf("%d - %s\n", i, factory->getName(i));
            printf("%d - Exit\n", factory->getCount());

            
            char buff[50];
            printf("Scelta: ");
            gets(buff);

            int i = 0;
            while(buff[i] != '\0') i++;
            if(i != 0)
            {
                buff[i] = ' ';
                buff[i + 1] = '\0';
            }

            sel_n = 0;

            int j = 0;
            char buff2[10];
            i = 0;
            while(buff[i] != '\0')
            {
                if(buff[i] != ' ')
                {
                    buff2[j] = buff[i];
                    j++;
                }
                else
                {
                    buff2[j] = '\0';
                    sel[sel_n] = atoi(buff2);

                    j = 0;
                    sel_n++;
                }

                i++;
            }

            
            printf("\n");
        }
        else
            exit=1;

        for(int i = 0; i < sel_n; i++)
        {
            
            OrderAlgorithm *algo = factory->get(sel[i]);

            printf("%s\n", factory->getName(sel[i]));

            
            int vett_n = x->n_values;

            
            int *vett = x->getArrayCopy();

            
            algo->execute(vett, vett_n);

            
            if(vett_n < 100)
            {
                char *s= LogDog::vectorToString(vett, vett_n);

                LogDog::printInfo((char *)"Vettore ordinato:");
                LogDog::printInfo(s);
                LogDog::printInfo((char *)"");
            }

            
            if(isOrderCorrectly(vett, vett_n)) LogDog::printInfo((char *)"Vettore ordinato correttamente");
            else LogDog::printError((char *)"Vettore ordinato incorrettamente");

            
            free(vett);

            
            if(ONLYONCE)
                return 0;

            
            double times[SAMPLE_SIZE];
            for(int i = 0; i < SAMPLE_SIZE; i++)
            {
                vett = x->getArrayCopy();
                LARGE_INTEGER start = LogDog::startTimer();
                algo->execute(vett, vett_n);
                double t = LogDog::endTimer2(start);

                times[i] = t;
                free(vett);
                dispperc(i, SAMPLE_SIZE);
            }
            
            printf("\r                                 \n");

            
            double sum = 0;
            for(int i = 0; i < SAMPLE_SIZE; i++) sum += times[i];
            double avgt = sum / SAMPLE_SIZE;

            
            sum = 0;
            for(int i = 0; i < SAMPLE_SIZE; i++) sum += pow((times[i] - avgt), 2);
            double devs = sum / (SAMPLE_SIZE - 1);
            devs = sqrt(devs);

            
            printf("Tempo medio impiegato al 95%% (%2.2f +/- %.2f)us\n\n", avgt, 1.96 * devs);

            if(sel[i] == factory->getCount())
            {
                exit = true;
                continue;
            }
        }
	}

	

	
	x->~FileReader();
	
	return 0;
}
