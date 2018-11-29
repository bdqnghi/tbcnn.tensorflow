package Edit_Distance;

public class Question {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	
	/**
	 * https://oj.leetcode.com/problems/edit-distance/
	 * Given two words word1 and word2, find the minimum number of steps
	 * required to convert word1 to word2. (each operation is counted as 1
	 * step.)
	 * 
	 * You have the following 3 operations permitted on a word:
	 * a) Insert a character 
	 * b) Delete a character 
	 * c) Replace a character
	 */
	
	//http://www.ninechapter.com/solutions/edit-distance/
	//【注】可以知道insert和delete达到的效果是一样的。所以这里为了简化，我们只保留“删”和“换”两个操作。
	//1.state: result[i][j]代表word1的前i个字符，配上word2的前j个字符，最少需要几次编辑能让他们相等。
	//2.function: 当word1[i] == word2[j]， result[i][j] = result[i - 1][j - 1]
	//			    	（在word1[i] == word2[j]的情况下，不需要重新编辑，就可以使word1的前i位和word2的前j位再次相等。）
	//			      当word1[i] != word2[j]， result[i] = min(result[i - 1][j - 1] + 1 , result[i - 1][j] + 1, result[i][j - 1] + 1) 
	//					（以上三种方式都能在word1[i] != word2[j]的情况下，经过相应的编辑，重新使word1的前i位和word2的前j位再次相等。选三个中最小的。）
	//			【注】具体的： result[i - 1][j - 1] + 1: word1的前i-1和word2的前j-1已经edit好的情况下，再加1步把word1的第i个replace成word2的第j个，就可以使word1和word2相等 
	//						result[i - 1][j] + 1: word1的前i-1和word2的前j已经edit好的情况下，再加1步把word2的第j个删去，就可以使word1和word2相等 
	//						result[i][j - 1] + 1)： word1的前i-1和word2的前j已经edit好的情况下，再加1步把word1的第i个删去，就可以使word1和word2相等 
	//3.initialize: result[0][j] = j; // 把word2的前j个全删去，就可以使word1和word2相等 
	//				result[i][0] = i; // 把word1的前i个全删去，就可以使word1和word2相等 
	//4.answer: result[A.length][B.length];
	//【注】result[][]和A，B有位差
	
	public int minDistance(String word1, String word2) {
		if (word1 == null || word2 == null) {
			return 0;
		}
		int[][] result = new int[word1.length() + 1][word2.length() + 1];
		for (int i = 0; i <= word1.length(); i++) {
			for (int j = 0; j <= word2.length(); j++) {
				if (i == 0) { //初始化第一行
					result[0][j] = j;
				} else if (j == 0) { //初始化第一列
					result[i][0] = i;
				} else if (word1.charAt(i - 1) == word2.charAt(j - 1)) { //result[][]和A，B有位差
					result[i][j] = result[i - 1][j - 1];
				} else {
					result[i][j] = Math.min(result[i - 1][j - 1], Math.min(result[i - 1][j], result[i][j - 1])) + 1;
				}
			}
		}
		return result[word1.length()][word2.length()];
	}
	
	
	//http://blog.csdn.net/linhuanmars/article/details/24213795
	//http://huntfor.iteye.com/blog/2077940
    public int minDistance2(String word1, String word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        if(len1 == 0){
        	return len2;
        }
        if(len2 == 0){
        	return len1;
        }
        int minLen = Math.min(len1, len2);
        int maxLen = Math.max(len1, len2);
        String minWord = len2 > len1 ? word1 : word2;
        String maxWord = len2 > len1 ? word2 : word1;
        int[] result = new int[minLen + 1];
        //initialize result array;
        for(int i=0; i< result.length;i++){
        	result[i] = i;
        }
        for(int i=0;i<maxLen;i++){
        	int[] newResult = new int[minLen+1];
        	newResult[0] = i+1;//why not =i?..
        	for (int j=0;j<minLen;j++){
        		if(maxWord.charAt(i) == minWord.charAt(j)){
        			newResult[j+1] = result[j];
        		}else{
        			newResult[j+1] = Math.min(result[j+1], Math.min(result[j], newResult[j])) +1;
        		}
        	}
        	result = newResult;
        }
        return result[minLen];
    }
    

}
