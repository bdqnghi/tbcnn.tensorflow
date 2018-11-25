



















#include "Levenshtein.h"

#include <vector>
#include <algorithm>





const float SYM_CMP_REGIST = 0.5f;
const float SYM_CMP_PHON_G = 0.25f;
const float SYM_CMP_REGIST_AND_PHON_G = 0.15f;





template <typename _T>
_T min3(_T a1, _T a2, _T a3) {
	return std::min(a1, std::min(a2, a3));
}





template <typename CharT>
CharT _t_tolower(CharT c) {
	return std::tolower(c);
}

template <> wchar_t _t_tolower(wchar_t wc) {
	return std::towlower(wc);
}

template <typename CharT>
size_t _t_strlen(CharT *c) {
	return std::strlen(c);
}

template <> size_t _t_strlen(wchar_t *ws) {
	return std::wcslen(ws);
}

template <> size_t _t_strlen(const wchar_t *ws) {
	return std::wcslen(ws);
}

template <typename _Str_T>
float Levenshtein(_Str_T* s1, _Str_T* s2)
{
    size_t len1 = _t_strlen(s1);
	size_t len2 = _t_strlen(s2);

    if (!len1 || !len2) {
        return std::max(len1, len2);
        
    }

    
    std::vector<float> initMat;
    std::vector<std::vector<float>> mat;
    
    for (size_t i = 0; i <= len2; ++i)
        initMat.push_back((float)i);
    
    for (size_t i = 0; i <= len1; i++)
        mat.push_back(initMat);

    
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            if (s1[i - 1] != s2[j - 1]) {
                mat[i][j] = min3(mat[i][j - 1], mat[i - 1][j], mat[i - 1][j - 1]) + 1;

                
                _Str_T sym1 = s1[i - 1];
                _Str_T sym2 = s2[j - 1];
                _Str_T sym1low = _t_tolower(sym1);
				_Str_T sym2low = _t_tolower(sym2);

                if (sym1low == sym2low) {
                    
                    mat[i][j] -= SYM_CMP_REGIST;
                }
				else if (GetMetaphone(sym1) == GetMetaphone(sym2)) {
                    
                    mat[i][j] -= SYM_CMP_PHON_G;
                }
				else if (GetMetaphone(sym1low) == GetMetaphone(sym2low)) {
                    
                    mat[i][j] -= SYM_CMP_REGIST_AND_PHON_G;
                }
            }
            else
                mat[i][j] = mat[i - 1][j - 1];
        }
    }

    return mat[len1][len2];
}

template float Levenshtein<char>(char *, char *);
template float Levenshtein<const char>(const char *, const char *);
template float Levenshtein<wchar_t>(wchar_t *, wchar_t *);
template float Levenshtein<const wchar_t>(const wchar_t *, const wchar_t *);



wchar_t GetMetaphone(wchar_t wsym)
{
    switch (wsym) {
        case L'ё':
        case L'е':
        case L'э':
        case L'и':
            return L'и';
            

        case L'ю':
        case L'у':
            return L'у';
            

        case L'о':
        case L'я':
        case L'а':
            return L'а';
            

        case L'б':
        case L'п':
            return L'п';
            

        case L'з':
        case L'с':
            return L'с';
            

        case L'д':
        case L'т':
            return L'т';
            

        case L'в':
        case L'ф':
            return L'ф';
            
    }

    return wsym;
}






char GetMetaphone(char sym)
{
    return sym;
}





