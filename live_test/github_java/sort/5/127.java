package bubbleSort;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Bubble {

	public static void main(String[] args) throws IOException {
		
		String CurLine = ""; 
		
		System.out.println("Enter a line of text (type 'sort' to sort): ");
		InputStreamReader converter = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(converter);

		ArrayList<Integer> toSort = new ArrayList<Integer>();
		while (!(CurLine.equals("sort"))){
			CurLine = in.readLine();
			if(!CurLine.equals("sort")){
				try{
					toSort.add(Integer.parseInt(CurLine));
				}catch(Exception e){
					System.out.println("Did you mean 'sort'? I can't sort strings.");
				}
				
			}else{
				
				boolean sorted = false;
				boolean verifySorted = false;
				while(!sorted&&!verifySorted){
					sorted = true;
					for(int i=0;i< toSort.size();i++){
						try{
							if(toSort.get(i) > toSort.get(i+1)){
								int temp = toSort.get(i+1);
								toSort.set(i+1, toSort.get(i));
								toSort.set(i, temp);
								sorted = false;
							}
						}catch(Exception e){}
						System.out.print(toSort.get(i)+ " ");
					}
					System.out.print('\n');
				}
			}
		}
	}

}
