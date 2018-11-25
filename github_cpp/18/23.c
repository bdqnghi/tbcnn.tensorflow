#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <functional>

using namespace std;

class RodCutting
{
public:
    struct Solution
    {
        int maxProfit = 0;
        int subSolution = 0;
        int discreteSolution = 0;
    };

    function<void(const vector<Solution>& s, int N)> printCompleteSolution;

    RodCutting()
    {       
        printCompleteSolution = [](const vector<Solution>& s, int N)
        {
            cout << "Full solution: ";

            if (s[N].discreteSolution != 0)
                cout << s[N].discreteSolution;

            int subSolution = s[N].subSolution;
            while (subSolution != 0)
            {
                cout << "->" << s[subSolution].discreteSolution;
                subSolution = s[subSolution].subSolution;
            }

            cout << endl;
        };
    }

    int maxProfitRecursive(const vector<int>& p, int N)
    {   
        if (N == 0 || N > p.size())        
            return 0;        

        int maxProfit = -1;
        for (int i = 1; i <= N; i++)
        {        
            maxProfit = max(maxProfit, p[i - 1] + maxProfitRecursive(p, N - i));
        }

        return maxProfit;
    }

    int maxProfitMemoization(const vector<int>& p, int N)
    {
        if (p.size() < N)
            return -1;

        vector<int> s(N + 1, -1);        
        return maxProfitMemoizationAux(p, s, N);
    }

    int maxProfitMemoizationAux(const vector<int>& p, vector<int>& s, int N)
    {   
        if (s[N] >= 0)   
        {
            return s[N];
        }

        int maxProfit = -1;
        if (N == 0)
        {
            maxProfit = 0;
        }
        else
        {
            for (int i = 1; i <= N; i++)
            {
                maxProfit = max(maxProfit, p[i - 1] + maxProfitMemoizationAux(p, s, N - i));
            }
        }

        s[N] = maxProfit;
        return maxProfit;
    }

    int maxProfitButtomUp(const vector<int>& p, int N)
    {
        if (p.size() < N)
            return -1;

        vector<int> s(N + 1, -1);
        s[0] = 0;

        for (int i = 1; i <= N; i++)
        {
             for (int j = 1; j <= i; j++)
             {
                 int localMaxProfit = p[j - 1] + s[i - j];

                 if (s[i] < localMaxProfit)
                 {
                      s[i] = localMaxProfit;
                 }   
             }
        }

        return s[N];
    }
    
    int maxProfitButtomUpFullSolution(const vector<int>& p, int N)
    {
        if (p.size() < N)
            return 0;
        
        vector<Solution> s;
        s.resize(N + 1);
        
         for (int i = 1; i <= N; i++)
         {
             for (int j = 1; j <= i; j++)
             {
                 int localMaxProfit = p[j - 1] + s[i - j].maxProfit;

                 if (s[i].maxProfit < localMaxProfit)
                 {
                     s[i].maxProfit = localMaxProfit;
                     s[i].subSolution = i - j;
                     s[i].discreteSolution = j;
                 }
             }
         }
            
        printCompleteSolution(s, N);
        return s[N].maxProfit;
    }

    void testRecursive()
    {
        {
            RodCutting b;
            vector<int> input{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
            cout << "Max profit -> " << b.maxProfitRecursive(input, 7) << endl;
        }
    }

    void testMemoization()
    {
        {
            RodCutting b;
            vector<int> input{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
            cout << "Max profit -> " << b.maxProfitMemoization(input, 7) << endl;
        }
    }

    void testButtomUp()
    {
        {
            RodCutting b;
            vector<int> input{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
            cout << "Max profit -> " << b.maxProfitButtomUp(input, 7) << endl;
        }
    }

    void testButtomUpFullSolution()
    {
        {
            RodCutting b;
            vector<int> input{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
            cout << "Max profit -> " << b.maxProfitButtomUpFullSolution(input, 7) << endl;
        }
    }
};


class StreetRobber
{
public:
    int rob(vector<int>& nums)
    {
        int N = nums.size();
        if (!N) return 0;

        vector<int> s;
        s.resize(N, 0);

        for (int i = 0; i < N; i++)
        {
            int prevPrevSolutionIndex = std::max(0, i - 2);
            int prevSolutionIndex = std::max(0, i - 1);
            int prevPrevSolutionValue = (i > 1 ? s[prevPrevSolutionIndex] : 0);
            if (prevPrevSolutionValue + nums[i] > s[prevSolutionIndex])
                s[i] = prevPrevSolutionValue + nums[i];
            else
                s[i] = s[prevSolutionIndex];
        }

        return s[N-1];

    }

    void testRobbery()
    {
        {
            StreetRobber r;
            vector<int> nums{ 1,2,3,4,5,6,7,8 };
            cout << "max profit of robbing -> " << r.rob(nums) << endl;
        }

        {
            StreetRobber r;
            vector<int> nums{ 1 };
            cout << "max profit of robbing -> " << r.rob(nums) << endl;
        }

        {
            StreetRobber r;
            vector<int> nums{ };
            cout << "max profit of robbing -> " << r.rob(nums) << endl;
        }

        {
            StreetRobber r;
            vector<int> nums{ 2,1 };
            cout << "max profit of robbing -> " << r.rob(nums) << endl;
        }
    }
};
    
