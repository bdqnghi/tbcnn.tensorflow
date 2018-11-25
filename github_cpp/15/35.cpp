


#include <utility>
#include "matrixMultiplication.h"




void matrixMultiplication::writeOutputFile() {
    ofstream outF ("output.txt");
    if(outF.is_open()){
        for (int j = 0; j < sizeA[0]; ++j) {
            for (int i = 0; i < sizeB[1] ; ++i) {
                outF << result1[j][i] << " ";
            }
            outF << endl;
        }
    }
    outF << "END1  " <<t1 << " ms"<<endl;
    outF << "------------------------------"<<endl;
    for (int j = 0; j < sizeA[0]; ++j) {
        for (int i = 0; i < sizeB[1] ; ++i) {
            outF << result2[j][i] << " ";
        }
        outF << endl;
    }
    outF << "END2  " <<t2 << " ms" <<endl;

    outF.close();
}



void matrixMultiplication::readFileMult(string filename) {
    ifstream multF;
    
    multF.open(filename);
    if(multF.is_open()){ 
        string line;
        
        
        getline(multF, line);
        int temp;
        stringstream ss(line);
        while(ss >> temp ){
            sizeA.push_back(temp);
            
        }
        

        
        ss.clear();
        ss.str(string());
        for(int i =0; i < sizeA[0]; i++) {
            getline(multF, line);
            ss << line;
            vector<int> temV;
            while(ss >> temp){
                temV.push_back(temp);
                
            }
            a.push_back(temV);
            ss.clear();
            ss.str(string());
            
        }

        
        getline(multF,line);
        ss << line;
        while(ss >> temp ){
            sizeB.push_back(temp);
            
        }
        

        
        ss.clear();
        ss.str(string());
        for(int i =0; i < sizeB[0]; i++) {
            getline(multF, line);
            ss << line;
            vector<int> temV;
            while(ss >> temp){
                temV.push_back(temp);
                
            }
            b.push_back(temV);
            ss.clear();
            ss.str(string());
            
        }
    } else{
        ofstream outF ("output.txt");
        outF << "An error has occured while reading the input.";
        outF.close();
        exit(EXIT_SUCCESS);
    }

}




void* matrixMultiplication::computeAnElementHelper(void *args) {
    return ((matrixMultiplication *)args)->computeAnElement();
}


void* matrixMultiplication::computeARowHelper(void *args) {
    return ((matrixMultiplication *)args)->computeARow();
}



void* matrixMultiplication::computeARow() {
      
        int row = m1_row;
        
        vector<int> temp = a[row];
        
        for (int i = 0; i < sizeB[1]; ++i) {
            int sum = 0;
            for (int j = 0; j < sizeB[0]; ++j) {
                sum += temp[j] * b[j][i];
            }
            result2[row][i] = sum;
        }
        
        m1_row++;
       
     


}


void* matrixMultiplication::computeAnElement() {
       
        int row = m1_row;
        int col = m1_col;
        
        vector<int> temp = a[row];
        int sum = 0;
        
        
        for (int i = 0; i < sizeA[1]; ++i) {
            sum += temp[i]*b[i][col];
        }
        
        m1_col++;
        
        
        
        if(m1_col == sizeB[1]){
            m1_col = 0;
            m1_row++;
        }
      
      
        result1[row][col] = sum;
       
}


void matrixMultiplication::matrixMult1() {
        
        clock_t start = clock();
        
        m1_col = 0;
        
        
        m1_row = 0;
        
        int numOfThreads = sizeA[0]*sizeB[1];
        
        pthread_t threads[numOfThreads];
        
        result1 = vector<vector<int>>(static_cast<unsigned long>(sizeA[0]), vector<int>(
                    static_cast<unsigned long>(sizeB[1])));
        
        for (int i = 0; i < numOfThreads ; i++) {
                pthread_create(&threads[i], nullptr,&matrixMultiplication::computeAnElementHelper, this);
            }
        
        for (int i = 0; i < numOfThreads; i++)
                pthread_join(threads[i], nullptr);
        
            clock_t end = clock();
        
        t1 = double(end - start) / CLOCKS_PER_SEC*1000;

}

void matrixMultiplication::matrixMult2() {
    
        clock_t start = clock();
        
        
        m1_row = 0;
        
        int numOfThreads = sizeA[0];
        
        pthread_t threads[numOfThreads];
        
        result2 = vector<vector<int>>(static_cast<unsigned long>(sizeA[0]),
                                      vector<int>(static_cast<unsigned long>(sizeB[1])));
        
        for (int i = 0; i < numOfThreads ; i++) {
            pthread_create(&threads[i], nullptr,&matrixMultiplication::computeARowHelper, this);
        }
        
        for (int i = 0; i < numOfThreads; i++)
            pthread_join(threads[i], nullptr);
        
        clock_t end = clock();
        
        t2 = double(end - start) / CLOCKS_PER_SEC*1000;
}

void matrixMultiplication::begin(string filename) {
    this -> readFileMult(std::move(filename));
    if(sizeA[1] != sizeB[0]) {
        ofstream outF ("output.txt");
        outF << "Input is invalid!";
        outF.close();
        exit(EXIT_SUCCESS);
    }
    this -> matrixMult1();
    this -> matrixMult2();
    this -> writeOutputFile();
}
