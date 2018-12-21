import java.util.Scanner;

class list
{
    static int[] array;
    static int index;
    static int size;
    list(int s)
    {
        array=new int[s];
        size=s; index=-1;
    }

    public static boolean empty()
    {
        if(index==-1)
        return true;
        return false;
    }

    public static boolean full()
    {
        if(index==size-1)
        return true;
        return false;
    }

    public static void append(int value)
    {array[++index]=value;}

    public static void bubblesort()
    {
        int temp;
        for(int i=0;i<=index-1;i++)
        for(int j=0;j<=index-1-i;j++)
        if(array[j]>array[j+1])
        {
            temp=array[j];
            array[j]=array[j+1];
            array[j+1]=temp;
        }
    }

    public static void display()
    {
        for(int i=0;i<=index;i++)
        System.out.print(array[i]+", ");
    }

    static Scanner read=new Scanner(System.in);
    public static void main(String[] args)
    {
        int ch,value;
        list lst=new list(5);
        do
        {
            System.out.print("\n 1. Append ");
            System.out.print("\n 2. Bubble Sort ");
            System.out.print("\n 3. Display ");
            System.out.print("\n 4. End Program ");
            System.out.print("\n\n Enter>>");
            ch=read.nextInt(); switch(ch)
            {
                case 1 :
                if(lst.full()==false)
                {
                    System.out.print("\n Enter a value : ");
                    value=read.nextInt(); lst.append(value);
                }
                else
                System.out.print("\n Array is full\n");
                break;

                case 2 :
                System.out.print("\n List is : ");
                if(empty()!=true)
                {
                    lst.bubblesort();
                    lst.display();
                }
                else System.out.print("empty!");
                break;

                case 3 :
                System.out.print("\n List is : ");
                if(empty()!=true) lst.display();
                else System.out.print("empty!");
                break;
            }
            System.out.println();
        }while(ch!=4);
    }
}
