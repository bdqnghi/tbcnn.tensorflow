/*
 * levenshteindistance.cpp
 *
 *  Created on: 2011/01/24
 *      Author: H.Narazaki
 */

#include "levenshteindistance.h"
#include <android/log.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native levenshteindistance.cpp", __VA_ARGS__))

static jint calc(const jchar* text1_str, jsize text1_len, const jchar* text2_str, jsize text2_len);
static jint calcSub(const jchar* text1_str, const jsize text1_len, const jchar* text2_str, const jsize text2_len,
        int k, int y);
JNIEXPORT jint JNICALL Java_info_narazaki_android_lib_text_LevenshteinDistance_diff(JNIEnv *env, jclass cls,
        jstring text1, jstring text2) {
    const jchar* text1_str = env->GetStringChars(text1, NULL);
    const jsize text1_len = env->GetStringLength(text1);
    const jchar* text2_str = env->GetStringChars(text2, NULL);
    const jsize text2_len = env->GetStringLength(text2);

    jint result = calc(text1_str, text1_len, text2_str, text2_len);

    env->ReleaseStringChars(text2, text2_str);
    env->ReleaseStringChars(text1, text1_str);

    return result;
}

// An O(NP) Sequence Comparison Algorithm
// by http://research.janelia.org/myers/Papers/np_diff.pdf
jint calc(const jchar* text1_str, jsize text1_len, const jchar* text2_str, jsize text2_len) {
    if (text1_len > text2_len) {
        std::swap(text1_str, text2_str);
        std::swap(text1_len, text2_len);
    }

    jint k;
    jint p;

    jint offset = text1_len + 1;
    jint delta = text2_len - text1_len;

    jint* buf = static_cast<jint*> (std::malloc(sizeof(jint) * (text2_len * 2 + 3)));

    for (int i = 0; i < text1_len + text2_len + 3; i++) {
        buf[i] = -1;
    }

    for (p = 0; buf[delta + offset] != text2_len; p++) {
        for (k = -p; k < delta; k++) {
            buf[k + offset] = calcSub(text1_str, text1_len, text2_str, text2_len, k, std::max(buf[k - 1 + offset] + 1,
                    buf[k + 1 + offset]));
        }
        for (k = delta + p; k > delta; k--) {
            buf[k + offset] = calcSub(text1_str, text1_len, text2_str, text2_len, k, std::max(buf[k - 1 + offset] + 1,
                    buf[k + 1 + offset]));
        }
        buf[delta + offset] = calcSub(text1_str, text1_len, text2_str, text2_len, delta, std::max(buf[delta - 1
                + offset] + 1, buf[delta + 1 + offset]));
    }
    std::free(buf);

    return delta + (p - 1) * 2;
}

jint calcSub(const jchar* text1_str, const jsize text1_len, const jchar* text2_str, const jsize text2_len, jint k,
        jint y) {
    jint x = y - k;
    while (x < text1_len && y < text2_len && text1_str[x] == text2_str[y]) {
        x++;
        y++;
    }
    return y;
}

JNIEXPORT void JNICALL Java_info_narazaki_android_lib_text_LevenshteinDistance_initNative(JNIEnv *env, jclass cls) {

}

