// KMP算法是一种快速的模式匹配算法。
// http://blog.csdn.net/v_july_v/article/details/7041827/

int ViolentMatch(char *s, char *p) {
    //s是文本串，p是模式串
    int sLen = strlen(s);
    int pLen = strlen(p);
    int i = 0;
    int j = 0;
    while (i < sLen && j < pLen) {
        if (s[i] == p[j]) {
            //如果当前字符匹配成功，即s[i]==p[i]，则i++,j++
            i++;
            j++;
        } else {//如果当前字符匹配失败，s[i]!=p[i]
            i = i - j + 1;
            j = 0;
        }
    }
    //匹配成功，返回模式串p在文本串s中的位置，否则返回-1
    if (j == pLen)
        return i - j;
    else
        return -1;
}

int KmpSearch(char *s, char *p) {
    int i = 0;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    while (i < sLen && j < pLen) {
        //如果j = -1，或当前字符匹配成功即s[i]==p[j]，令i++，j++
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            //如果j != -1，且当前字符匹配失败即s[i]!=p[j]，则令i不变，j=next[j]
            //next[j]即j对应的next值
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;//相匹配的开始位置
    else
        return -1;//不能匹配
}

void GetNext(char *p, int next[]) {
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1) {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k]) {
            ++k;
            ++j;
            next[j] = k;
        } else {// if k!=-1 && p[j]!=p[k]
            k = next[k];
        }
    }
}

//优化后的next数组求法
void GetNextval(char *p, int next[]) {
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1) {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k]) {
            ++j;
            ++k;
            //以下是与之前next数组的求法不同之处
        }
    }
}