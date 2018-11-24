#include "KnuthMorrisPratt.h"

using namespace StringMatching;

KnuthMorrisPratt::KnuthMorrisPratt(std::string::iterator textBeg, std::string::iterator textEnd,
                                   std::string::iterator patternBeg, std::string::iterator patternEnd)
    : m_textCur(textBeg), m_textEnd(textEnd), m_patternBeg(patternBeg), m_patternEnd(patternEnd)
    , m_patternLength(patternEnd - patternBeg)
    , m_charsMatched(0)
{
    computePrefix();
}


std::string::iterator KnuthMorrisPratt::nextMatch()
{
    while(m_textCur != m_textEnd)
    {
        while(m_charsMatched > 0 && m_patternBeg[m_charsMatched] != *m_textCur)
        {//символ не совпадает, вернёмся к предыдущей длине префикса
            m_charsMatched = m_prefix.at(m_charsMatched-1);
        }
        if(m_patternBeg[m_charsMatched] == *m_textCur)
        {//символ совпал, увеличим чмсло совпавших символов
            ++m_charsMatched;
        }
        ++m_textCur;
        if(m_charsMatched == m_patternLength)
        {//шаблон обнаружен, число совпавших символов для следующего поиска равно длинне маскимального префикса
         //шаблона, которыя является так же суффиксом шаблона
            m_charsMatched = m_prefix.at(m_patternLength-1);
            return m_textCur-m_patternLength;
        }
    }
    return m_textEnd;
}

void KnuthMorrisPratt::computePrefix()
{
    m_prefix.resize(m_patternLength);
    m_prefix.at(0) = 0;
    int curPrefixLength = 0;

    for(auto patternI = m_patternBeg+1; patternI != m_patternEnd; ++patternI)
    {
        while(curPrefixLength > 0 && m_patternBeg[curPrefixLength] != *patternI)
        {//если длина текущего префикса не равна нулю, а последний симов текуюшего префикса
         //не равен последнему симовлу текущей части шаблона, возвращаемся к предыдущему префиксу
            curPrefixLength = m_prefix.at(curPrefixLength-1);
        }
        if(m_patternBeg[curPrefixLength] == *patternI)
        {//если последний символ префикса равен посделнему символу части шаблона, увеличим длину префикса
            ++curPrefixLength;
        }
        m_prefix.at(patternI - m_patternBeg) = curPrefixLength;
    }
}
