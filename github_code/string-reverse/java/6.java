package com.base.algorithm;

/**
 * Created by dong on 2016/6/27.
 */
public class StringReverse {

    /**
     *   try to reverse a string , such as 'This is     the new beginning."
     */

    private String word;

    private int length;

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public String reverse(){
        for(int i = 0; i < length; i++){
            System.out.print(word.charAt(length - 1 - i));
        }
        return word;
    }

    public static void main(String[] args){
        String word = "This is     the new beginning.";
        StringReverse stringReverse = new StringReverse();
        stringReverse.setWord(word);
        stringReverse.setLength(word.length());
        stringReverse.reverse();
    }
}
