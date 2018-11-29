http://www.careercup.com/question?id=6287528252407808

A k-palindrome is a string which transforms into a palindrome on removing at most k characters. 

Given a string S, and an interger K, print "YES" if S is a k-palindrome; otherwise print "NO". 
Constraints: 
S has at most 20,000 characters. 
0<=k<=30 

Sample Test Case#1: 
Input - abxa 1 
Output - YES 
Sample Test Case#2: 
Input - abdxa 1 
Output - No



The question asks if we can transform the given string S into its reverse deleting at most K letters. 
We could modify the traditional Edit-Distance algorithm, considering only deletions, and check if this edit distance is <= K. There is a problem though. S can have length = 20,000 and the Edit-Distance algorithm takes O(N^2). Which is too slow. 

(From here on, I'll assume you're familiar with the Edit-Distance algorithm and its DP matrix) 

However, we can take advantage of K. We are only interested *if* manage to delete K letters. This means that any position more than K positions away from the main diagonal is useless because its edit distance must exceed those K deletions. 

Since we are comparing the string with its reverse, we will do at most K deletions and K insertions (to make them equal). Thus, we need to check if the ModifiedEditDistance is <= 2*K 
Here's the code:
