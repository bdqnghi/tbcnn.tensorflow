package _01_Array.Finding_a_Number;


public class First_Missing_Positive {

    int firstMissingPositiveAnd0(int A[]) {
        int n = A.length;
        for (int i = 0; i < n; i++) {
            
            while (A[i] != i) {
                
                if (A[i] < 0 || A[i] >= n)
                    break;

                
                if(A[i]==A[A[i]])
                    break;
                
                int temp = A[i];
                A[i] = A[temp];
                A[temp] = temp;
            }
        }

        for (int i = 0; i < n; i++) {
            if (A[i] != i)
                return i;
        }

        return n;
    }






    
    

    public int firstMissingPositive2(int[] A) {
        int n = A.length;

        for (int i = 0; i < n; i++) {
            while (A[i] != i + 1) {
                if (A[i] <= 0 || A[i] >= n)
                    break;

                if(A[i]==A[A[i]-1])
                    break;

                int temp = A[i];
                A[i] = A[temp - 1];
                A[temp - 1] = temp;
            }
        }

        for (int i = 0; i < n; i++){
            if (A[i] != i + 1){
                return i + 1;
            }
        }

        return n + 1;
    }






























}
