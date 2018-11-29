import java.io.*;
import java.math.*;
import java.util.*;
class j
{
        private int DEFAULT_LENGTH = 100009;
	    private int[] _currentRow;
        private int[] _previousRow;
        private int[] _transpositionRow;
  
        /// <summary>
        /// 
        /// </summary>
        /// <param name="maxLength"></param>
        public j(int maxLength)
        {
            _currentRow = new int[maxLength + 1];
            _previousRow = new int[maxLength + 1];
            _transpositionRow = new int[maxLength + 1];
        }
 
        /// <summary>
        /// Damerau-Levenshtein distance is computed in asymptotic time O((max + 1) * min(first.length(), second.length()))
        /// </summary>
        /// <param name="first"></param>
        /// <param name="second"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public int GetDistance(String first, String second, int max,int del,int rep)
        {
            int firstLength = first.length();
            int secondLength = second.length();
 
            if (firstLength == 0)
                return secondLength*del;
 
            if (secondLength == 0) 
				return firstLength*del;
 
            if (firstLength > secondLength)
            {
                String tmp = first;
                first = second;
                second = tmp;
                firstLength = secondLength;
                secondLength = second.length();
            }
 
            if (max < 0) 
			max = secondLength;
            if (secondLength - firstLength > max) return -1;
 
            if (firstLength > _currentRow.length)
            {
                _currentRow = new int[firstLength + 1];
                _previousRow = new int[firstLength + 1];
                _transpositionRow = new int[firstLength + 1];
            }
 
            for (int i = 0; i <= firstLength; i++)
                _previousRow[i] = i;
 
            char lastSecondCh = (char) 0;
            for (int i = 1; i <= secondLength; i++)
            {
                char secondCh = second.charAt(i - 1);
                _currentRow[0] = i;
 
                // Compute only diagonal stripe of width 2 * (max + 1)
                int from = Math.max(i - max - 1, 1);
                int to = Math.min(i + max + 1, firstLength);
 
                char lastFirstCh = (char) 0;
                for (int j = from; j <= to; j++)
                {
                    char firstCh = first.charAt(j - 1);
 
                    // Compute minimal cost of state change to current state from previous states of deletion, insertion and swapping 
                    int cost = firstCh == secondCh ? 0 : rep;
                    int value = Math.min(Math.min(_currentRow[j - 1] + del, _previousRow[j] + del), _previousRow[j - 1] + cost);
 
                    // If there was transposition, take in account its cost 
                    if (firstCh == lastSecondCh && secondCh == lastFirstCh)
                        value = Math.min(value, _transpositionRow[j - 2] + cost);
 
                    _currentRow[j] = value;
                    lastFirstCh = firstCh;
                }
                lastSecondCh = secondCh;
 
                int[] tempRow = _transpositionRow;
                _transpositionRow = _previousRow;
                _previousRow = _currentRow;
                _currentRow = tempRow;
            }
 
            return _previousRow[firstLength];
        }
public static void main(String a[])throws IOException
{
int j=0,i=0;
BufferedReader b=new BufferedReader(new InputStreamReader(System.in));
j obj=new j(100009);
String s=b.readLine();
String t=b.readLine();
String tem=b.readLine();
StringTokenizer c=new StringTokenizer(tem);
int del=Integer.parseInt(c.nextToken());
int rep=Integer.parseInt(c.nextToken());
int maxm=Integer.parseInt(c.nextToken());
System.out.println(obj.GetDistance(s,t,maxm,del,rep));


 
}
}