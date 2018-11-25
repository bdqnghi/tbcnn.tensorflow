



#ifndef INTERVIEW_CPP_STRINGUTILS_H
#define INTERVIEW_CPP_STRINGUTILS_H

namespace Algorithm {
	void Reverse(char *pBegin, char *pEnd) {
		if (pBegin == nullptr || pEnd == nullptr)
			return;

		while (pBegin < pEnd) {
			char temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
			pBegin++;
			pEnd--;
		}
	}



	void Permutation(char *pStr, char *pBegin) {
		if (*pBegin == '\0')
			printf("%s\n", *pStr);
		else {
			for (char *pCh = pBegin; *pCh != '\0'; ++pCh) {
				char temp = *pCh;
				*pCh = *pBegin;
				*pBegin = temp;

				Permutation(pStr, pBegin + 1);

				temp = *pCh;
				*pCh = *pBegin;
				*pBegin = temp;
			}
		}
	}

	void Permutation(char *pStr) {
		if (pStr == nullptr)
			return;
		Permutation(pStr, pStr);
	}

	void Test(char *pStr) {
		if (pStr == nullptr)
			printf("Test for nullptr.\n");
		else
			printf("Test for %s begins.\n", pStr);

		Permutation(pStr);
		printf("\n");
	}

	void test_main() {
		Test(nullptr);

		char string1[] = "";
		Test(string1);

		char string2[] = "a";
		

		char string3[] = "ab";
		Test(string3);

		char string4[] = "abc";

		Test(string4);
	}



	char *ReverseSentence(char *pData) {
		if (pData == nullptr)
			return nullptr;

		char *pBegin = pData;
		char *pEnd = pData;

		while (*pEnd != '\0')
			pEnd++;
		pEnd--;

		
		Reverse(pBegin, pEnd);

		
		pBegin = pEnd = pData;
		while (*pBegin != '\0') {
			if (*pBegin == ' ') {
				pBegin++;
				pEnd++;
			} else if (*pEnd == ' ' || *pEnd == '\0') {
				Reverse(pBegin, --pEnd);
				pBegin = ++pEnd;
			} else
				pEnd++;
		}
		return pData;
	}
}
#endif 
