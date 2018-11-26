//
// Created by sohayla on 01/11/18.
//
#include <utility>
#include "matrixMultiplication.h"
/**
 * this class contains the functions neccessary for doing multi-threaded matrix multiplication
 * it follows two procedures and compare their elapsed time
 * the first procedure creates a thread to compute each element in the result matrix
 * the second procedure creates a thread tp compute each row in the result matrix
 */


/**
 * writing into output file
 * file is output.txt
 */
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

/**
 * reads two matrices and thier sizes from a file
 * @param filename name of the file to read from
 */

void matrixMultiplication::readFileMult(string filename) {
    ifstream multF;
    //open the file
    multF.open(filename);
    if(multF.is_open()){ // check if file has opened successfully
        string line;
        //get first line in file, which is
        //the size of the first matrix
        getline(multF, line);
        int temp;
        stringstream ss(line);
        while(ss >> temp ){
            sizeA.push_back(temp);
            // cout << temp ;
        }
        //  cout << endl;

        //read the first matrix elements
        ss.clear();
        ss.str(string());
        for(int i =0; i < sizeA[0]; i++) {
            getline(multF, line);
            ss << line;
            vector<int> temV;
            while(ss >> temp){
                temV.push_back(temp);
                //        cout << temp ;
            }
            a.push_back(temV);
            ss.clear();
            ss.str(string());
            //  cout << endl;
        }

        //get the size of the second matrix
        getline(multF,line);
        ss << line;
        while(ss >> temp ){
            sizeB.push_back(temp);
            //  cout<<temp ;
        }
        //cout << endl;

        //get the elements of the second matrix
        ss.clear();
        ss.str(string());
        for(int i =0; i < sizeB[0]; i++) {
            getline(multF, line);
            ss << line;
            vector<int> temV;
            while(ss >> temp){
                temV.push_back(temp);
                //   cout << temp;
            }
            b.push_back(temV);
            ss.clear();
            ss.str(string());
            //   cout << endl;
        }
    } else{
        ofstream outF ("output.txt");
        outF << "An error has occured while reading the input.";
        outF.close();
        exit(EXIT_SUCCESS);
    }

}


/**
 * used as a bridge between threads, which is passed
 * to as a parameter, and the code to compute an element in the array
 * @param args holds the parameters passed to the computing function
 * @return thread results
 */

void* matrixMultiplication::computeAnElementHelper(void *args) {
    return ((matrixMultiplication *)args)->computeAnElement();
}

/**
 * used as a bridge between threads, which is passed
 * to as a parameter, and the code to compute a row in the array
 * @param args holds the parameters passed to the computing function
 * @return thread results
 */
void* matrixMultiplication::computeARowHelper(void *args) {
    return ((matrixMultiplication *)args)->computeARow();
}

/**
 * compute each row in the result matrix
 * each thread access it one time
 * @return
 */

void* matrixMultiplication::computeARow() {
      //  c.lock();
        int row = m1_row;
        //gets a row from first matrix
        vector<int> temp = a[row];
        // compute a row in the result matrix
        for (int i = 0; i < sizeB[1]; ++i) {
            int sum = 0;
            for (int j = 0; j < sizeB[0]; ++j) {
                sum += temp[j] * b[j][i];
            }
            result2[row][i] = sum;
        }
        //incrementing row index
        m1_row++;
       // cout << "row " << row << endl;
     //   c.unlock();


}

/**
 * compute each element in the result matrix
 * each thread access it one time
 * @return
 */
void* matrixMultiplication::computeAnElement() {
       // c.lock();
        int row = m1_row;
        int col = m1_col;
        //gets a the row from the first matrix
        vector<int> temp = a[row];
        int sum = 0;
        //multiply the row from first matrix with the
        //column from the second matrix
        for (int i = 0; i < sizeA[1]; ++i) {
            sum += temp[i]*b[i][col];
        }
        //increment the column index
        m1_col++;
        //if column index reached is out of bounds
        //then we need to increment the row index
        //and re-inetialise the column index to 0
        if(m1_col == sizeB[1]){
            m1_col = 0;
            m1_row++;
        }
      //  cout << "at row " << row<< " and col " << col << "==" << sum<< endl;
      //put the element in the result matrix
        result1[row][col] = sum;
       // c.unlock();
}

/**
 * first procedure for computing the result matrix
 * it creates a new thread to compute each element in the array
 * number of threads created is equal to the number of rows in
 * the first matrix multiplied by the number of coloumns in the
 * second matrix
 */
void matrixMultiplication::matrixMult1() {
        //get the current time in milliseconds
        clock_t start = clock();
        //the index of the column for the element currently being calculated
        m1_col = 0;
        //the index of the row for the element currently being calculated
        //and also as an index for rows in the first matrix
        m1_row = 0;
        //total number of threads
        int numOfThreads = sizeA[0]*sizeB[1];
        //an array of threads
        pthread_t threads[numOfThreads];
        //allocating the size for the result matrix
        result1 = vector<vector<int>>(static_cast<unsigned long>(sizeA[0]), vector<int>(
                    static_cast<unsigned long>(sizeB[1])));
        //create all the threads
        for (int i = 0; i < numOfThreads ; i++) {
                pthread_create(&threads[i], nullptr,&matrixMultiplication::computeAnElementHelper, this);
            }
        //join all the threads created
        for (int i = 0; i < numOfThreads; i++)
                pthread_join(threads[i], nullptr);
        //current time after the execution
            clock_t end = clock();
        //elapsed time in milliseconds
        t1 = double(end - start) / CLOCKS_PER_SEC*1000;

}
/**
 * second procedure for computing the result matrix
 * it creates a new thread to compute each row in the array
 * number of threads created is equal to the number of rows in
 * the first matrix
 */
void matrixMultiplication::matrixMult2() {
    //get the current time in milliseconds
        clock_t start = clock();
        //the index of the row currently being calculated
        //and also as an index for rows in the first matrix
        m1_row = 0;
        //total number of threads needed
        int numOfThreads = sizeA[0];
        //an array of threads
        pthread_t threads[numOfThreads];
        //allocating the size for the result matrix
        result2 = vector<vector<int>>(static_cast<unsigned long>(sizeA[0]),
                                      vector<int>(static_cast<unsigned long>(sizeB[1])));
        //create all the threads
        for (int i = 0; i < numOfThreads ; i++) {
            pthread_create(&threads[i], nullptr,&matrixMultiplication::computeARowHelper, this);
        }
        //join all the threads created
        for (int i = 0; i < numOfThreads; i++)
            pthread_join(threads[i], nullptr);
        //current time after the execution
        clock_t end = clock();
        //elapsed time in milliseconds
        t2 = double(end - start) / CLOCKS_PER_SEC*1000;
}
/**
 * for begining the computation of the result matrix
 * from the two procedures
 * the only public function in the class
 * @param filename the name of the input file
 */
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
