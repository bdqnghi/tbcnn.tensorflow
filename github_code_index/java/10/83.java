import java.io.*;
public class Bubblesort 
{
    int a;
     int b[]=new int[a+1];
    void Sort()throws IOException
    {
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Type the number of elements to sort: ");
        a =Integer.parseInt(br.readLine());
        System.out.print("Type the Elements : ");
       
        for (int i = 0; i < a; i++)
            b[i] = Integer.parseInt(br.readLine()); 
        b[a]=0;
        System.out.println();
        System.out.println("\tUnsorted Elements");
        for (int i = 0; i < a; i++)
            System.out.print(b[i]+" ");
        System.out.println();
        System.out.println("\tUsing Bubble Sort");
        for(int j=0;j<a;j++){
        for(int i=1;i<=a;i++)
        {
            if(b[i]>b[i-1])
            {
                int te=b[i];
                b[i]=b[i-1];
                b[i-1]=te;
            }
        }
        }
        for(int i=0;i<a;i++)
        {
            System.out.print(b[i]+" ");
        }
    }
}

