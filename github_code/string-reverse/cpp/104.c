class Solution1 {//ʹ��swap
public:
	string reverseString(string s) {
		int length = s.size();
		int start = 0;
		int end = length - 1;
		while (start < end) {
			swap(s[start], s[end]);
			start++;
			end--;
		}
		return s;
	}
};
class Solution {//������string
public:
	string reverseString(string s) {
		int length = s.size();
		int start = 0;
		int end = length - 1;
		string res;
		for (int i = length - 1; i >= 0; i--) {
			//	res += s[i];



			res.insert(res.end(), s[i]);
		}
		return res;
	}
};

class Solution {//�⺯��
public:
	string reverseString(string s) {
		reverse(s.begin(), s.end());
		return s;
	}
};

char* reverseString(char* s) {
	int len = strlen(s);
	char* res = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < len; i++) {
		res[len - i - 1] = *(s + i);
	}
	res[len] = '\0';
	return res;
}