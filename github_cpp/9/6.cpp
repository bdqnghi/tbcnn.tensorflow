



#ifndef PROJECT_STRINGREVERSE_H
#define PROJECT_STRINGREVERSE_H


class stringReverse {

};

void LeftShiftOne(char* s,int n){
    
    char t = s[0];
    for(int i=1;i<n;i++){
        s[i-1] = s[i];
    }
    s[n-1] = t;
}

void LeftRotateString_1(char* s,int n,int m){
    while(m--){
        LeftShiftOne(s,n);
    }
}

void ReverseString(char* s, int from, int to){
    while(from < to){
        char t = s[from];
        s[from++] = s[to];
        s[to--] = t;
    }
}

void LeftRotateString_2(char* s,int n,int m){
    m %= n ;
    ReverseString(s,0,m-1);
    ReverseString(s,m,n-1);
    ReverseString(s,0,n-1);
}

void ReverseWords(char* s,int n){
    ReverseString(s,0,n-1);

    int i=0,j=0;
    for(i=0,j=0;j<n;j++){
        if(j==n||s[j+1]==' '){
            ReverseString(s,i,j);
            i=j+2;
        }
    }
}


#endif 
