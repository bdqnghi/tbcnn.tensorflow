//
//  StringEditDistance.cpp
//  AlgorithmC++
//
//  Created by 김윤철 on 2016. 4. 20..
//  Copyright © 2016년 bolastudy. All rights reserved.
//

#include "StringEditDistance.hpp"


/*
 스트링 편집 거리 구하기 알고리즘
 두 문자열을 같게 만들기 위한 최소 연산의 수가 편집 거리이다.
 레반슈타인 알고리즘을 사용하였다. 만약 더 공부하고 싶다면 링크와 원노트, 알고리즘 책 참고.
 
 삽입, 삭제, 대치 연산의 비용은 모두 1이라고 가정한다. 단순함을 위함.
 나중에 이들이 다른 경우에 대해서도 만들어보자.
 */

int stringEditDistance(string s, string t) {
    
    //동적 알고리즘을 사용함. 메모이제이션! 최적의 편집거리가 저장됨.
    //배열 생성이 안됨....
    int editDistance[s.length() + 1][t.length() + 1];
    
    //편집거리 표 초기화
    editDistance[0][0] = 0;
    
    for(int i = 1; i <= s.length(); i++) {
        editDistance[0][i] = i;
    }
    
    //editDistance[0][0]은 위에서 이미 0으로 초기화되어 있으므로 건드리지 않는다.
    for(int i = 1; i <= t.length(); i++) {
        editDistance[i][0] = i;
    }
    
    //레반슈타인 알고리즘을 사용한다.
    for(int i = 1; i <= s.length(); i++) {
        for(int j = 1; j <= t.length(); j++) {
           
            //만약 문자열의 두 문자가 같다면 그를 위한 추가 연산은 없다. 그러니, 이전까지 연산을 거친 문자열의 최소 편집거리만 가져온다.
            if(s.at(i-1) == t.at(j-1)) {
                editDistance[i][j] = min(min(editDistance[i-1][j-1], editDistance[i][j-1]), editDistance[i-1][j]);
            }
            else {
            //다르다면, 문자열을 같게 만들기 위해 삽입, 삭제, 대치 연산 중 가장 비용이 작은 연산을 택한다. 그런데, 여기는 모든 연산의 비용이 1로 통일이므로 이전의 최소 편집거리에 1만 더한다.
            editDistance[i][j] = min(min(editDistance[i-1][j-1], editDistance[i][j-1]), editDistance[i-1][j]) + 1;
            }
        }
    }
    

    
    //최적 편집거리를 반환한다.
    return editDistance[s.length()][t.length()];
}

void stringEditDistanceTest() {
    
    string s;
    string t;
    
    
    cin >> s;
    cin >> t;
    
    cout << stringEditDistance(s, t) << endl;
}