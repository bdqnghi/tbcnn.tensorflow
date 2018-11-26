/*
Description:
Task
Given a string str, reverse it omitting all non-alphabetic characters.

Example
For str = "krishan", the output should be "nahsirk".

For str = "ultr53o?n", the output should be "nortlu".

Input/Output
[input] string str

A string consists of lowercase latin letters, digits and symbols.

[output] a string
*/

#include <iostream>
#include <random>

using namespace std;

static default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

static const string alpha    = "abcdefghijklmnopqrstuvwxyz",
                    nonAlpha = "0123456789_ !@#$%^&*_(),.?|{}[]-=+\\/";
static auto rand3to50        = bind(uniform_int_distribution<int>(3, 50),                generator),
            rand10000        = bind(uniform_int_distribution<int>(0, 9999),              generator),
            randAlpha        = bind(uniform_int_distribution<int>(0, alpha.size()-1),    generator),
            randNonAlpha     = bind(uniform_int_distribution<int>(0, nonAlpha.size()-1), generator);
static auto randomAlpha      = [](){return alpha[randAlpha()];};
static auto randomNonAlpha   = [](){return nonAlpha[randNonAlpha()];};

string reverse_letter(const std::string &str)
{
    std::string copy(str.rbegin(), str.rend());
    copy.erase(std::remove_if(copy.begin(), copy.end(), [](char c) { return !isalpha(c); } ), copy.end());
    return copy;
}

Describe(solution_test)
{
    It(basic_tests)
    {
        doTest("krishan", "nahsirk");
        doTest("ultr53o?n", "nortlu");
        doTest("ab23c", "cba");
        doTest("krish21an", "nahsirk");
    }
    It(random_tests)
    {
        for (int trial = 1; trial <= 100; trial++)
        {
            string str, exp;
            for (int n = rand3to50(); n--;)
            {
                str.push_back(randomAlpha());
                exp.push_back(str.back());
                if ( rand10000() % 3 == 0 ) str.push_back(randomNonAlpha());
            }
            reverse(str.begin(), str.end());
            cout << "<font face='sans-serif' color='#00cc00' size=2><b>Testing for:</b></font>"
                    "<font face='sans-serif' color='#eeee00' size=2>\nstr = \""
                 << str <<"\"</font>" << endl;
            doTest(str, exp);
        }
    }
    void doTest(const std::string &str, const std::string &expected)
    {
        Assert::That(reverse_letter(str), Equals(expected));
    }
};
