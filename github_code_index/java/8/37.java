/*
 * chsi
 * Created on 2017-09-28
 */
package com.zyl.similarity;

import org.apache.commons.lang.StringUtils;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * 计算字符串的相似度
 *
 * @author zhuyl <a href="mailto:zhuyl@chsi.com.cn">zhu Youliang</a>
 * @version $Id$
 */
public class Levenshteindistance {
    /**
     * 计算字符串的相似度
     *
     * @param str1 字符串1
     * @param str2 字符串2
     * @return 相似度
     */
    public static float similarity(String str1, String str2) {
        long startTime = System.currentTimeMillis();
        if ( StringUtils.isBlank(str1) && StringUtils.isBlank(str2) ) {
            return 1;
        }
        float str1Length = StringUtils.isBlank(str1) ? 0 : str1.length();
        float str2Length = StringUtils.isBlank(str2) ? 0 : str2.length();
        float result = 1 - distance(str1, str2) / Math.max(str1Length, str2Length);
        long endTime = System.currentTimeMillis();
        System.out.println("levenshteindistance比对耗时：" + (endTime - startTime));
        return result;
    }

    private static int distance(String str1, String str2) {
        if ( StringUtils.isBlank(str1) ) {
            return str2.length();
        }
        if ( StringUtils.isBlank(str2) ) {
            return str1.length();
        }
        int str1Length = str1.length();
        int str2Length = str2.length();
        int[][] d = new int[str1Length + 1][str2Length + 1];
        for ( int index = 0; index <= str1Length; index++ ) {
            d[index][0] = index;
        }
        for ( int index = 0; index <= str2Length; index++ ) {
            d[0][index] = index;
        }

        int tmp;
        for ( int i = 1; i <= str1Length; i++ ) {
            char char1 = str1.charAt(i - 1);
            for ( int j = 1; j <= str2Length; j++ ) {
                char char2 = str2.charAt(j - 1);
                tmp = char1 == char2 ? 0 : 1;
                d[i][j] = minimum(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + tmp);
            }
        }
        return d[str1Length][str2Length];
    }

    private static int minimum(Integer... numbers) {
        if ( numbers.length == 0 ) {
            return numbers[0];
        }
        List<Integer> tmpList = Arrays.asList(numbers);
        Collections.sort(tmpList);
        return tmpList.get(0);
    }
}