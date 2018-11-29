package com.arelikebrothers.learn.algorithm.base;

import com.arelikebrothers.learn.algorithm.Sort;
import com.arelikebrothers.learn.algorithm.aop.annotation.TimeCostLog;

import java.util.List;

import static com.arelikebrothers.learn.algorithm.util.SortUtil.needSwap;
import static java.util.Collections.swap;

public class Bubble implements Sort{
    @Override
    @TimeCostLog
    public void sort(List<? extends Comparable> list) {
        for (int i = list.size() - 1; i > 0 ; i--) {
            for (int j = 0; j < i; j++) {
                if (needSwap(list.get(j), list.get(j+1))) {
                    swap(list, j, j+1);
                }
            }
        }

    }


}

