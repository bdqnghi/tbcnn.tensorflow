package LendingKart;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RodCutting {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T= Integer.parseInt(br.readLine());
        while(T-->0){
        	int N = Integer.parseInt(br.readLine());
        	int count=0;
        	while(true){
        		if(N==1){
        			break;
        		}
        		if(N%2==0){
        			N = N/2;
        		}
        		else{
        			count++;
        			N = (N-1)/2;
        			if(N==1)
        				break;
        			N = N-1;
        		}
        	}
        	System.out.println(count);
        }
	}
        
}
