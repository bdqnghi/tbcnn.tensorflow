/*
 @Date    : 2018-08-14 22:05:55
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
希尔排序
 */

#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include "Insertion_sort.h"
#include <cmath>
#include "../../Vector/Vector.h"

namespace CZ
{
    using Rank_shell_sort = long long;

    namespace ShellSort
    {
        Vector<Rank_shell_sort> deltaSeq;

        void produce_Sedgewick_seq(Rank_shell_sort N)
        {
            Rank_shell_sort delta = 1;
            for (Rank_shell_sort i = 0;; ++i)
            {
                delta = 9 * pow(4, i) - 9 * pow(2, i) + 1;
                if (N <= delta)
                {
                    break;
                }
                deltaSeq.push_back(delta);
            }
            return;
        }

        void produce_Pratt_seq(Rank_shell_sort N)
        {
            Rank_shell_sort delta = 1;
            for (Rank_shell_sort i = 0;; ++i)
            {
                for (Rank_shell_sort j = 0; j <= i; ++j)
                {
                    delta = pow(2, i) * pow(3, j);
                    if (N <= delta)
                    {
                        break;
                    }
                    deltaSeq.push_back(delta);
                }
                if (N <= delta)
                {
                    break;
                }
            }
            return;
        }

        void produce_Papernov_Stasevic_seq(Rank_shell_sort N)
        {
            Rank_shell_sort delta = 1;
            for (Rank_shell_sort i = 1;; ++i)
            {
                delta = pow(2, i) - 1;
                if (N <= delta)
                {
                    break;
                }
                deltaSeq.push_back(delta);
            }
            return;
        }

        void produce_Shell_seq(Rank_shell_sort N)
        {
            Rank_shell_sort delta = 1;
            for (Rank_shell_sort i = 0;; ++i)
            {
                delta = pow(2, i);
                if (N <= delta)
                {
                    break;
                }
                deltaSeq.push_back(delta);
            }
            return;
        }
    }

    template <typename It, typename Cmp>
    void Shell_sort(It begin, Rank_shell_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        switch (version)
        {
            // 不同版本的增量序列
            case 0 : ShellSort::produce_Sedgewick_seq(N); break;
            case 1 : ShellSort::produce_Pratt_seq(N); break;
            case 2 : ShellSort::produce_Papernov_Stasevic_seq(N); break;
            case 3 : ShellSort::produce_Shell_seq(N); break;
        }

        for (Rank_shell_sort i = ShellSort::deltaSeq.size() - 1; -1 < i; --i)
        {
            for (Rank_shell_sort j = 0; j < ShellSort::deltaSeq[i]; ++j)
            {
                Insertion_sort(begin+j, N-j, ShellSort::deltaSeq[i], cmp, 0);
            }
        }
        return;
    }
} // CZ

#endif // SHELL_SORT_H


