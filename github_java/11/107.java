import java.util.LinkedList;
public class radixsort{
static void distribute(LinkedList[] digits,int[] numbers,String digitype){
    int i;
    for ( i=0;i<50;i++){
        if(digitype.equals("ones")){
            digits[(numbers[i]%10)].addLast(numbers[i]);
            
        }
        else{
           digits[(numbers[i]/10)].addLast(numbers[i]); 
        }
    }
}
static void collect(LinkedList[] digits,int[] numbers){
    int p=0;
    for(int l=0;l<10;++l){
        while(!digits[l].isEmpty()){
            numbers[p++]=(int)digits[l].removeFirst();
            
        }
    }
}
static void display(int[] numbers){
    int k=0;
    for(int y=0;y < numbers.length;y++){
        System.out.println(numbers[y]+" ");
    }
}



    
    public static void main(String[] args){
        final int size=50;
        final int numqueues=10;
        LinkedList<Integer>[] digits=new LinkedList[numqueues];
        for (int i=0;i<numqueues;i++){
            digits[i]=new LinkedList();
        
        }
        int[] nums=new int[size];
        for(int i=0;i<size;i++){
            nums[i]=(int)(Math.random()*100);
            
        }
        display(nums);
        System.out.println();
        distribute(digits,nums,"ones");
        collect(digits,nums);
        display(nums);
        System.out.println();
        distribute(digits,nums,"tens");
        collect(digits,nums);
        display(nums);   
        
    }
}