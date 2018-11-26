package com.company.amazon.BookKarumanchi.Algorithms.StringAlgorithms;

/**
 * Created by v-dsindhi on 2/5/16.
 */
public class stringreverse {
    private static boolean flag = true;// added a variable flag to check if we reverse the word or not.
    private static char[] ReverseSentence(char[] sentence)
    {
        //Given: "Hi my name is person!"
        //produce: "iH ym eman si !nosrep"

        if(sentence == null) return null;
        if(sentence.length == 1) return sentence;

        int startPosition=0;
        int counter = 0;
        int sentenceLength = sentence.length-1;

        //Solution handles any amount of spaces before, between words etc...

        while(counter <= sentenceLength)
        {
            if(sentence[counter] == ' ' && startPosition != -1 || sentenceLength == counter) //Have passed over a word so upon encountering a space or end of string reverse word
            {
                flag = !flag; // first time (odd position) we are not going to reverse!
                //swap from startPos to counter - 1
                //set start position to -1 and increment counter
                int begin = startPosition;

                int end;
                if(sentenceLength == counter)
                {
                    end = counter;
                }
                else
                    end = counter -1;
                char tmp;

                //Reverse characters
                while(end >= begin & flag){ //lets see whether we are going to reverse or not

                    tmp = sentence[begin];
                    sentence[begin] = sentence[end];
                    sentence[end] = tmp;

                    end--; begin++;

                }

                startPosition = -1; //flag used to indicate we have no encountered a character of a string


            }

            else if(sentence[counter] !=' ' && startPosition == -1) //first time you encounter a letter in a word set the start position
            {
                startPosition = counter;
            }

            counter++;
        }

        return sentence;
    }

    public static void main(String[] args) {
        String sentence = "whats the matter with kansas";
        char[] sentencechars = new char[sentence.length()];
        if(sentence!=null){
            sentencechars = sentence.toCharArray();
        }
        System.out.println(ReverseSentence(sentence.toCharArray()));
    }
}
