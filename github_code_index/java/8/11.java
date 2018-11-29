package org.c4i.util;

/**
 * @author Arvid Halma
 * @version 10-12-2017 - 20:03
 */
public class StringUtilDemo {
    public static void main(String[] args) {

        System.out.println("Distance");
        System.out.println("StringUtil.levenshteinDistance(\"abc\", \"def\") = " + StringUtil.levenshteinDistance("abc", "def"));
        System.out.println("StringUtil.levenshteinDistance(\"abc\", \"abc\") = " + StringUtil.levenshteinDistance("abc", "abc"));
        System.out.println("StringUtil.levenshteinDistance(\"abc\", \"bc\") = " + StringUtil.levenshteinDistance("abc", "bc"));
        System.out.println("StringUtil.levenshteinDistance(\"bc\", \"abc\") = " + StringUtil.levenshteinDistance("bc", "abc"));


        System.out.println("Similarity");
        System.out.println("StringUtil.levenshteinSimilarity(\"abc\", \"b\") = " + StringUtil.levenshteinSimilarity("abc", "b"));
        System.out.println("StringUtil.levenshteinSimilarity(\"b\", \"abc\") = " + StringUtil.levenshteinSimilarity("b", "abc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"b\", \"b\") = " + StringUtil.levenshteinSimilarity("b", "b"));
        System.out.println("StringUtil.levenshteinSimilarity(\"abc\", \"def\") = " + StringUtil.levenshteinSimilarity("abc", "def"));
        System.out.println("StringUtil.levenshteinSimilarity(\"abc\", \"abc\") = " + StringUtil.levenshteinSimilarity("abc", "abc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"abc\", \"bc\") = " + StringUtil.levenshteinSimilarity("abc", "bc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"bc\", \"abc\") = " + StringUtil.levenshteinSimilarity("bc", "abc"));

        System.out.println("StringUtil.levenshteinSimilarity(\"aabbcc\", \"def\") = " + StringUtil.levenshteinSimilarity("aabbcc", "def"));
        System.out.println("StringUtil.levenshteinSimilarity(\"aabbcc\", \"aabbcc\") = " + StringUtil.levenshteinSimilarity("aabbcc", "aabbcc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"aabbcc\", \"bbcc\") = " + StringUtil.levenshteinSimilarity("aabbcc", "bbcc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"bbcc\", \"aabbcc\") = " + StringUtil.levenshteinSimilarity("bbcc", "aabbcc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"bbcc\", \"aabbcccccccccccccc\") = " + StringUtil.levenshteinSimilarity("bbcc", "aabbcccccccccccccc"));

        System.out.println("StringUtil.levenshteinSimilarity(\"aabbcc\", \"aacc\") = " + StringUtil.levenshteinSimilarity("aabbcc", "aacc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"aacc\", \"aabbcc\") = " + StringUtil.levenshteinSimilarity("aacc", "aabbcc"));
        System.out.println("StringUtil.levenshteinSimilarity(\"aacc\", \"aabbcccccccccccccc\") = " + StringUtil.levenshteinSimilarity("aacc", "aabbcccccccccccccc"));
    }
}
