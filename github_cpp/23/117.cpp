



#ifndef TRABAJOPRACTICO2_MAINFLUJODEREDES_H
#define TRABAJOPRACTICO2_MAINFLUJODEREDES_H

#include <ctime>
#include "ParserNetworkFlow.h"
#include "FordFulkerson.h"
#include <time.h>

class MainFlujoDeRedes {
public:
    int A = 1000;
    int P = 1000;
    int COST_AREA = 1;
    int PROFIT_PROJECT = 1;
    string TEMPORAL_FILE = "./FlujoDeRedes/files/archivoTemporal.tmp";
    string CSV_FILE = "./FlujoDeRedes/files/times.csv";

    MainFlujoDeRedes() {
        std::srand(std::time(0));
    }

    std::vector<int> generateRestrictionListForProject(int size) {
        std::vector<int> restrictions;
        for (int i = 0; i < size; i++) {
            int r = (std::rand() % MainFlujoDeRedes::A) + 1;
            restrictions.push_back(r);
        }
        return restrictions;
    }

    void createFileRandom(int r) {
        ofstream outputFile(TEMPORAL_FILE.c_str());
        outputFile << MainFlujoDeRedes::A << std::endl;
        outputFile << MainFlujoDeRedes::P << std::endl;
        for (int i = 0; i < MainFlujoDeRedes::A; i++) {
            outputFile << MainFlujoDeRedes::COST_AREA << std::endl;
        }

        int perProjectRestrictionCount = (r / MainFlujoDeRedes::P);

        for (int i = 0; i < MainFlujoDeRedes::P; i++) {
            std::vector<int> restrictionRandomList = generateRestrictionListForProject(perProjectRestrictionCount);
            outputFile << MainFlujoDeRedes::PROFIT_PROJECT << " ";
            for (int j = 0; j < restrictionRandomList.size() - 1; j++) {
                outputFile << restrictionRandomList[j] << " ";
            }
            outputFile << restrictionRandomList[restrictionRandomList.size()-1] << std::endl;
        }

        outputFile.close();
    }

    void testExecutionTime() {

        ofstream outputFile(CSV_FILE.c_str());
        outputFile << "r,clocks" << std::endl;

        clock_t start_time;
        clock_t stop_time;

        int r = 1000;
        for (int i = 1; i <= 10; i++) {
            createFileRandom(r);
            ParserNetworkFlow parserNetworkFlow(TEMPORAL_FILE);
            FordFulkerson fordFulkerson(&parserNetworkFlow);
            start_time =  clock();
            fordFulkerson.maxFlow();
            stop_time = clock();
            outputFile << r << "," << stop_time - start_time << std::endl;
            r = r * 2;
        }

        outputFile.close();
    }

    void printVector(vector<int> v) {
        for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            int x = *it;
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }

    void printVectorDescription(ParserNetworkFlow& parserNetworkFlow, vector<int> v) {
        for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            int x = *it;
            std::cout << parserNetworkFlow.vertexMap[x].description << "\t";
        }
        std::cout << std::endl;
    }

    void runExample(string fileName) {
        std::cout << "-----" << std::endl;
        std::cout << ">Corrida del algoritmo sobre " << fileName << std::endl;
        ParserNetworkFlow parserNetworkFlow(fileName);
        FordFulkerson fordFulkerson(&parserNetworkFlow);

        fordFulkerson.maxFlow();

        std::cout << ">Conjuto S: " << std::endl;
        printVectorDescription(parserNetworkFlow, fordFulkerson.getSetS());

        std::cout << ">Conjunto T: " << std::endl;
        printVectorDescription(parserNetworkFlow, fordFulkerson.getSetT());

        std::cout << ">Projectos a realizar: " << std::endl;
        printVector(fordFulkerson.getProjects());

        std::cout << ">Areas a abonar: " << std::endl;
        printVector(fordFulkerson.getAreas());

        std::cout << ">Fin del algoritmo sobre " << fileName << std::endl;
        std::cout << "-----" << std::endl;
    }

    void run() {

        testExecutionTime();

        runExample("./FlujoDeRedes/files/trivialExample.txt");
        runExample("./FlujoDeRedes/files/trivialExample2.txt");
        runExample("./FlujoDeRedes/files/trivialExample3.txt");
        runExample("./FlujoDeRedes/files/trivialExample4.txt");
        runExample("./FlujoDeRedes/files/example1.txt");
        runExample("./FlujoDeRedes/files/example2.txt");
        runExample("./FlujoDeRedes/files/exampleInforme.txt");

    }
};

#endif 
