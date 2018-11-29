
/**
 * editdistance
 */
public class editdistance
{
    public editdistance(){
    };
    public static int getDistance(String strA, String strB)
    {
        int distance =-1;
        if(null==strA || null ==strB || strA.isEmpty()||strB.isEmpty())
        {
            return distance;
        }
        if(strA.equals(strB))
        {
            return 0;
        }
        System.out.println("The First String: "+strA);
        System.out.println("The Second String: "+strB);
        int lengthA=strA.length();
        int lengthB=strB.length();
        int length= Math.max(lengthA, lengthB);
        int array[][]=new int[lengthA+1][lengthB+1];
        for(int i=0;i<=lengthA;i++)
        {
            array[i][0]=i;
        }
         for(int j=0;j<=lengthB;j++)
        {
            array[0][j]=j;
        }
        for(int i=1;i<=lengthA;i++)
        {
            for(int j=1;j<=lengthB;j++)
            {
                if(strA.charAt(i-1)==strB.charAt(j-1))
                {
                    array[i][j]=array[i-1][j-1];
                }else{
                array[i][j]=Math.min(array[i-1][j-1]+1,
                Math.min(array[i][j-1]+1,array[i-1][j]+1));
            }
            }
        }
        System.out.println("Transfer Matrix:");

        for(int i=0;i<=lengthA;i++)
        {
            for(int j=0;j<=lengthB;j++)
            {  
                System.out.print(array[i][j]+"\t");
            }
            System.out.println();
        }
        return array[lengthA][lengthB];
    }
}
