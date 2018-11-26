/**
 * class Ej3
 * @author Gianluca Scolaro
 * @author Eduardo Lalor
 * @since  5/9/17.
 */
public class Ej3 implements Exercise3{

    public double[] exerciseAI(double[][] matrixA, double[] vectorX, Calculator calculator){
        int n = matrixA.length;
        int m = matrixA[0].length;
        double[] result = new double[n];
        if(m==vectorX.length){
            for (int i=0; i<n;i++){
                result[i]=0;
                for (int j=i;j<m;j++){
                    result[i] = calculator.sum(result[i],calculator.multiplication(matrixA[i][j],vectorX[j]));
                }
            }
        }
        return result;
    }

    public double[][] exerciseAII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if ((matrixA.length != matrixB.length) || (matrixA[0].length != matrixB[0].length)){
            throw new RuntimeException(); //check if there is a more elegant solution
        }
        double[][] sum = new double[matrixA.length][matrixA[0].length];
        for (int i=0; i<matrixA.length; i++){
            for (int j=i; j<matrixA[i].length; j++){
                //sum[i][j] = matrixA[i][j] + matrixB[i][j];//use calc
                sum[i][j] = calculator.sum(matrixA[i][j], matrixB[i][j]);
            }
        }
        return sum;
    }

    public double[][] exerciseAIII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if (matrixA[0].length != matrixB.length){
            throw new RuntimeException();
        }
        double[][] multiplication = new double[matrixA.length][matrixB[0].length];
        for (int i=0; i<multiplication.length; i++){
            for (int j=0; j<multiplication[i].length; j++){
                double result = 0;
                for (int k=i; k<=j; k++){
                    //result += matrixA[i][k] * matrixB[k][j];
                    double product = calculator.multiplication(matrixA[i][k], matrixB[k][j]);
                    result = calculator.sum(result, product);
                }
                multiplication[i][j] = result;
            }
        }
        return multiplication;
    }

    public double[] exerciseBI(double[][] matrixA, double[] vectorX, Calculator calculator){
        int n = matrixA.length;
        int m = matrixA[0].length;
        double[] result = new double[n];
        if(m==vectorX.length && n==m){//has to be squared
            result[0]=0;
            for (int j=0;j<m;j++){
                //result[0]+= matrixA[0][j] * vectorX[j];
                result[0] = calculator.sum(result[0],calculator.multiplication(matrixA[0][j],vectorX[j]));
            }
            for (int i=1; i<n;i++){
                result[i]=0;
                for (int j=0;j<m;j++){
                    //System.out.println(matrix[i][j] * vector[j]);
                    //result[i] += matrixA[i][j] * vectorX[j];
                    result[i] = calculator.sum(result[i],calculator.multiplication(matrixA[i][j],vectorX[j]));
                }
            }
        }
        return result;
    }

    public double[][] exerciseBII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if ((matrixA.length != matrixB.length) || (matrixA[0].length != matrixB[0].length)){
            throw new RuntimeException();
        }
        double[][] result = new double[matrixA.length][matrixA[0].length];
        for (int i=0; i<matrixA[0].length; i++){
            result[0][i] = calculator.sum(matrixA[0][i], matrixB[0][i]);
        }
        for (int i=1; i<matrixA.length; i++){
            for (int j=i-1; j<matrixA[0].length; j++){
                result[i][j] = calculator.sum(matrixA[i][j], matrixB[i][j]);
            }
        }
        return result;
    }

    public double[][] exerciseBIII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if (matrixA[0].length != matrixB.length){
            throw new RuntimeException();
        }
        double[][] multiplication = new double[matrixA.length][matrixB[0].length];
        for (int i=0,l=1; i<multiplication.length; i++){
            for (int j=0; j<multiplication[i].length; j++){
                double result = 0;
                for (int k=l-1; k<=j+1 && k!=matrixB[0].length; k++){
                    //if (k<0) k=0; //fixes first run
                    //if (k==matrixB[0].length) k= matrixB[0].length-1;
                    //result += matrixA[i][k] * matrixB[k][j];
                    double product = calculator.multiplication(matrixA[i][k], matrixB[k][j]);
                    result = calculator.sum(result, product);
                }
                multiplication[i][j] = result;
            }
            l=i+1;
        }
        return multiplication;
    }

    public double[] exerciseCI(double[][] matrixA, double[] vectorX, Calculator calculator){
        int n = matrixA.length;
        int m = matrixA[0].length;
        double[] multiplication = new double[n];
        if(m==vectorX.length && n==m){//has to be squared
            for (int i=0; i<=1;i++){
                double result = 0;
                for (int k=0; k<=i+1; k++){
                    double product = calculator.multiplication(matrixA[i][k], vectorX[k]);
                    result = calculator.sum(result, product);
                }
                multiplication[i]=result;
            }
            for (int i=2; i<n;i++){
                double result = 0;
                for (int k=i-1; k<=i+1 && k<m; k++){
                    double product = calculator.multiplication(matrixA[i][k], vectorX[k]);
                    result = calculator.sum(result, product);
                }
                multiplication[i]=result;
            }
        }
        return multiplication;
    }

    public double[][] exerciseCII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if ((matrixA.length != matrixB.length) || (matrixA[0].length != matrixB[0].length)){
            throw new RuntimeException();
        }
        double[][] result = new double[matrixA.length][matrixA[0].length];
        for (int i=0,l=1; i<matrixA.length; i++){
            for (int j=l-1; j<=1+i && j<matrixA[0].length; j++){
                result[i][j] = calculator.sum(matrixA[i][j], matrixB[i][j]);
            }
            l = i+1;
        }
        return result;
    }

    public double[][] exerciseCIII(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if (matrixA[0].length != matrixB.length){
            throw new RuntimeException();
        }
        double[][] multiplication = new double[matrixA.length][matrixB[0].length];
        for (int i=0; i<multiplication.length; i++){
            for (int j=0; j<multiplication[0].length; j++){ //changed index i to 0
                double result = 0;
                for (int k= Math.max(0, Math.max(j-1, i-1)); k<=i+1 && k<=j+1 && k<matrixA[0].length; k++){
                    double product = calculator.multiplication(matrixA[i][k], matrixB[k][j]);
                    result = calculator.sum(result, product);
                }
                multiplication[i][j] = result;
            }
        }
        return multiplication;
    }

    public double[] exerciseDI(double[][] matrixA, int k1A, int k2A, double[] vectorX, Calculator calculator){
        int n = matrixA.length;
        int m = matrixA[0].length;
        double[] multiplication = new double[n];
        if(m==vectorX.length && n==m){
            for (int i=0; i<n; i++){
                double result = 0;
                for (int k= Math.max(0, i-k1A); k<=i+k2A && k<=matrixA[0].length-1; k++){
                    double product = calculator.multiplication(matrixA[i][k], vectorX[k]);
                    result = calculator.sum(result, product);
                }
                multiplication[i] = result;
            }
        }
        return multiplication;
    }

    public double[][] exerciseDII(double[][] matrixA, int k1A, int k2A, double[][] matrixB, int k1B, int k2B, Calculator calculator){
        if ((matrixA.length != matrixB.length) || (matrixA[0].length != matrixB[0].length)){
            throw new RuntimeException();
        }
        double[][] result = new double[matrixA.length][matrixA[0].length];
        for (int i=0; i<result.length; i++){
            for (int k= Math.max(0, Math.min(i-k2B, i-k1A)); k<=Math.max(i+k2A, i+k1B) && k<matrixA[0].length; k++){
                result[i][k] = calculator.sum(matrixA[i][k], matrixB[i][k]);
            }
        }
        return result;
    }

    public double[][] exerciseDIII(double[][] matrixA, int k1A, int k2A, double[][] matrixB, int k1B, int k2B, Calculator calculator){
        if (matrixA[0].length != matrixB.length){
            throw new RuntimeException();
        }
        double[][] multiplication = new double[matrixA.length][matrixB[0].length];
        for (int i=0; i<multiplication.length; i++){
            for (int j=0; j<multiplication[0].length; j++){ //changed index i to 0
                double result = 0;
                for (int k= Math.max(0, Math.max(j-k2B, i-k1A)); k<=i+k2A && k<=j+k1B && k<matrixA[0].length; k++){
                    double product = calculator.multiplication(matrixA[i][k], matrixB[k][j]);
                    result = calculator.sum(result, product);
                }
                multiplication[i][j] = result;
            }
        }
        return multiplication;
    }

    public double[][] exerciseE(double[][] matrixA, double[][] matrixB, Calculator calculator){
        if (matrixA[0].length != matrixB.length){
            throw new RuntimeException();
        }
        double[][] multiplication = new double[matrixA.length][matrixB[0].length];
        for (int i=0; i<multiplication.length; i++){
            for (int j=0; j<multiplication[i].length; j++){
                double result = 0;
                for (int k=0; k<=i && k<=j && k<matrixB[0].length; k++){
                    double product = calculator.multiplication(matrixA[i][k], matrixB[k][j]);
                    result = calculator.sum(result, product);
                }
                multiplication[i][j] = result;
            }
        }
        return multiplication;
    }
}
