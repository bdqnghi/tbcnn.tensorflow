//
// Created by ning on 2018/5/26.
//

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

// 字符串排列    --- 递归
/*
 * 面试38：输入一个字符串，打印出该字符串中字符的所有排列
 */
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
		// Test(string2);

		char string3[] = "ab";
		Test(string3);

		char string4[] = "abc";
// 指针有问题
		Test(string4);
	}

// 反转字符串
/*
 * 面试58：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变
 * 翻转两次 2O(n)
 * */
	char *ReverseSentence(char *pData) {
		if (pData == nullptr)
			return nullptr;

		char *pBegin = pData;
		char *pEnd = pData;

		while (*pEnd != '\0')
			pEnd++;
		pEnd--;

		// 翻转句子
		Reverse(pBegin, pEnd);

		// 翻转句子中的每一个单词
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
#endif //INTERVIEW_CPP_STRINGUTILS_H
