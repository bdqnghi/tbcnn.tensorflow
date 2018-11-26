#include <iostream>
#import <seqan/basic.h>
#import <seqan/find.h>
#import <seqan/modifier.h>
#import <seqan/file.h>
#import <seqan/sequence.h>

using namespace seqan;


template <typename TAlgorithm>
void printAllOccs(String<char>& haystack, 
                  String<char>& needle)
{
    Finder<String<char> > finder(haystack);
    Pattern<String<char>, TAlgorithm> pattern(needle);
    while (find(finder, pattern)) 
    {
        ::std::cout << position(finder) << ", ";
    }
    ::std::cout << ::std::endl;
}


void testFunction(const char* tmpl,const char *primer)
{
    std::cout<<"Occurrences"<<std::endl;
    String<char> haystack(tmpl);//="send more money";
    String<char> needle(primer);//="mo";
    printAllOccs<ShiftOr>(haystack,needle);
}

bool amplify(const char* tmpl,const char* primer1,const char* primer2,char* amplicon)
{
    String<char> templateString(tmpl);
    // duplicate once to avoid end overlap effects
    append(templateString,templateString);
    String<char> primerString1(primer1),primerString2(primer2);
    Finder<String<char> > finder(templateString);
    Pattern<String<char>,ShiftOr> pattern1(primerString1),pattern2(primerString2);

    String<char> forwardPrimer,reversePrimer;

    if(find(finder,pattern1)){
        forwardPrimer=primerString1;
        reversePrimer=primerString2;}
    else{
        clear(finder);
        if(find(finder,pattern2)){
        forwardPrimer=primerString2;
        reversePrimer=primerString1;
        }
        else
            return false; // failure
    }

    //reversePrimer.reverseComplement();
    //reverseComplement(reversePrimer); // in place?
    ModifiedString<ModifiedString<String<char>, ModComplementDna>,ModReverse> reversePrimerReverseComplementString(reversePrimer);
    String<char> filtered(reversePrimerReverseComplementString);
    //String<char> reversed(toCString(String<char>ReverseComplement(reversePrimer)));
    //Pattern<String<char>,ShiftOr> reversePrimerReverseComplementPattern(String<char>ReverseComplement(reversePrimer));//reversePrimerReverseComplementString);
    Pattern<String<char>,ShiftOr> reversePrimerReverseComplementPattern(filtered);

    int startIndex=position(finder);
    clear(finder);
    int finalIndex=0;
    while(finalIndex<=startIndex && find(finder,reversePrimerReverseComplementPattern)){
        finalIndex=position(finder)+length(reversePrimer);
    }
    if(finalIndex>startIndex){
        strncpy(amplicon,toCString(infix(templateString,startIndex,finalIndex)),finalIndex-startIndex+1);
        return true;
    }
    return false;
}

void readFasta(const char *fasta_file,char *sequence_tag_buffer,char *sequence_buffer)
{
    std::fstream fstrm;
    fstrm.open(fasta_file,std::ios_base::in | std::ios_base::binary);
    String<char> fasta_tag;
    readMeta(fstrm,fasta_tag,Fasta());
    strcpy(sequence_tag_buffer,toCString(fasta_tag));
    String<char> fasta_seq;
    read(fstrm,fasta_seq,Fasta());
    strcpy(sequence_buffer,toCString(fasta_seq));
    fstrm.close();
}
