/*
 This functions in this class takes two sequences and computes the normalized edit
 distance between them. The functions use only two rows so that the table
 does not need to be stored in memory.
 */

package lcsprogram;

/**
 *
 * @author Avinash
 */

public class editdistance {
         private  char[] top;
         private    char[] left;
         private    int[][] twoRow;
         private    int topLength;//length of the secondstring
         private    int leftLength;//length of the first string
            public editdistance(String s1,String s2)
            {
                 left=s1.toCharArray();
                 top=s2.toCharArray();
                 twoRow=new int[2][top.length+1];//two row table consiting of 2 rows and (toplength+1)columns
                 topLength=top.length;
                 leftLength=left.length;
            }


            
    public int  calculateEditDistance(){

        int i,j,col,count;
        //initilize the column
                
        for(col=0;col<topLength+1;col++)
        {
            twoRow[0][col]=col;
        }
                
        //start building the table using two rows

        for(count=1;count<=leftLength;count++)
        {
            twoRow[1][0]=count;//initialize the row
            for(col=1;col<topLength+1;col++)
            {
                if(top[col-1]==left[count-1])
                {
                    twoRow[1][col]=twoRow[0][col-1];
                }
                else{
                    if(twoRow[0][col]<=twoRow[1][col-1])
                    {
                        twoRow[1][col]=twoRow[0][col]+1;
                    }
                    if(twoRow[1][col-1]<twoRow[0][col])
                    {
                        twoRow[1][col]=twoRow[1][col-1]+1;
                    }
                }
            }//end of for loop of top length

         //now shift the lower row to upper row a
            for(col=0;col<topLength+1;col++)
            {
                twoRow[0][col]=twoRow[1][col];
            }

        }//end of forloop  left length
        
        //return the last elemnet of the table
        return(twoRow[1][topLength]);
   
 }//end of the calculate edit distance



public void normalizedEditDistance()
{
    int editDistance;
    double normalizedDistance;
    double length=topLength+leftLength;

    editDistance=calculateEditDistance();
    normalizedDistance=(length-editDistance)/length;
    System.out.println("The Normalized Edit Distance is :");
    System.out.printf("%.5f",normalizedDistance);
    System.out.println();


}//end of the normalized Edit distance



}//end of the class
