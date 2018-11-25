



#include "ArrraysProblem2.h"


void ArraysProblem2::problem2() {
    char word1[] = { 's', 'o', 'm', 'e', 'S', 't','r','i','n','g','\0' };
    char word2[] = { 'S', 't','r','i','n','g','\0' };
    char word3[] = { 's', 'o', 'm', 'e','\0' };
    char word4[] = { 's', 'o', 'n','\0' };
    char word5[] = { 's','\0' };
    char word6[] = { '\0' };

    printReverseStringTestV1(word1);
    printReverseStringTestV1(word2);
    printReverseStringTestV1(word3);
    printReverseStringTestV1(word4);
    printReverseStringTestV1(word5);
    printReverseStringTestV1(word6);

    printf("\n");

    printReverseStringTestV2(word1);
    printReverseStringTestV2(word2);
    printReverseStringTestV2(word3);
    printReverseStringTestV2(word4);
    printReverseStringTestV2(word5);
    printReverseStringTestV2(word6);
}


void ArraysProblem2::reverseStringV1 (char* const str){
    int stringLength = 0;
    int reverseIterator = 0;
    char temp;

    
    while (str[stringLength] != NULL){
        stringLength++;
    }

    
    
    if(stringLength > 1){
        reverseIterator = stringLength-1;

        for(int i=0; i<=stringLength/2; i++){

            if(i <= (reverseIterator - i)){
                temp = str[i];
                str[i] = str[reverseIterator - i];
                str[reverseIterator - i] = temp;
            }
        }
    }
}


void ArraysProblem2::reverseStringV2 (char* const str){
    std::queue<char> strReverseQueue;

    
    if(str[0] != NULL && str[1] != NULL){
        int strIterator = 0;
        reverseStringRecurse(str, strIterator, strReverseQueue);
    }
}

void ArraysProblem2::reverseStringRecurse (char* const str, int strIterator, CharQueue &strReverseQueue){

    
    
    if(str[strIterator+1] != NULL){
        strReverseQueue.push(str[strIterator]);
        strIterator++;
        reverseStringRecurse(str, strIterator, strReverseQueue);
        strIterator--;
    }
    else {
        strReverseQueue.push(str[strIterator]);
    }

    str[strIterator]= strReverseQueue.front();
    strReverseQueue.pop();
}

void ArraysProblem2::printReverseStringTestV1(char* const tempString){
    printf("Problem2 test string: %s  ... ", tempString);
    reverseStringV1(tempString);
    printf("Reverse Version 1: %s\n", tempString);
}

void ArraysProblem2::printReverseStringTestV2(char* const tempString){
    printf("Problem2 test string: %s  ... ", tempString);
    reverseStringV2(tempString);
    printf("Reverse Version 2: %s\n", tempString);
}