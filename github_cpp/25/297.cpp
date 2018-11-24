#include <iostream>
#include <string.h>
using namespace std;

void DoPermute(char in[], char out[], int used[], int length, int recursLev)
{
    //base case
    if(recursLev == length) {
        printf("%s\n", out);
        return;
    }

    //Recursive Case
    for(int i = 0; i < length; i++) {
        if(used[i])  //If used, skip to next letter
            continue;

        out[recursLev] = in[i];  //Put current letter in output
        used[i] = 1;              //Mark this letter as used
        DoPermute(in, out, used, length, recursLev + 1);
        used[i] = 0;             //Unmark this letter
    }
}
int Permute(char inString[])
{
    int length, *used;
    char *out;
    length = strlen(inString);
    out = (char *)malloc(length + 1);

    if(!out)
        return 0; //Failed

    //so printf doesn't run past the end of the buffer
    out[length] = '\0';
    used = (int *)malloc(sizeof(int) * length);

    if(!used)
        return 0; //Failed

    //Start with no letters used, so zero array
    for(int i = 0; i < length; i++)
        used[i] = 0;

    DoPermute(inString, out, used, length, 0);
    free(out);
    free(used);
    return 1; //Success
}


int main()
{
    Permute("abcdefghijklmnopqrstuvwxyz");
    return 0;
}
