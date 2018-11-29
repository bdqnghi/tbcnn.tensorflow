/*1. Calculate the total number of moves required i.e. "pow(2, n)- 1" 
 * here n is number of disks.
2. If number of disks (i.e. n) is even then interchange destination 
   pole and auxiliary pole.
3. for i = 1 to total number of moves:
     if i%3 == 1:
	legal movement of top disk between source pole and 
        destination pole
     if i%3 == 2:
	legal movement top disk between source pole and 
        auxiliary pole	
     if i%3 == 0:
        legal movement top disk between auxiliary pole 
        and destination pole */
public class towerofhanoi {
	public void tower(BoundedStack src,int n){
		BoundedStack aux = new BoundedStack(n);
		BoundedStack dest = new BoundedStack(n);
		int nummoves = (int) (Math.pow(2, n)-1);
		
		for (int i=1;i<=nummoves;i++){
			System.out.println(i);
			if(i%3==1){
				if(dest.isEmpty()){
					dest.push(src.pop());
				}else if(src.isEmpty()){
					src.push(dest.pop());
				}
				else{
					if((Integer)src.peek() < (Integer)dest.peek()){ //transfer lesser number
						dest.push(src.pop());
					}
					else{
						src.push(dest.pop());
					}
				}
			}else if(i%3==2){
				if(aux.isEmpty()){
					aux.push(src.pop());
				}else if(src.isEmpty()){
					src.push(aux.pop());
				}else{
					if((Integer)src.peek() < (Integer)aux.peek()){
						aux.push(src.pop());
					}else{
						src.push(aux.pop());
					}
				}
			}else if(i%3==0){
				if(dest.isEmpty()){
					dest.push(aux.pop());
				}else if(aux.isEmpty()){
					aux.push(dest.pop());
				}else{
					if((Integer)aux.peek() < (Integer)dest.peek()){
						dest.push(aux.pop());
					}else{
						aux.push(dest.pop());
					}
				}
			}
		}
		System.out.println("Here");
		printstack(dest);
	}
	
	public void towereven(BoundedStack src,int n){
		BoundedStack aux = new BoundedStack(n);
		BoundedStack dest = new BoundedStack(n);
		int nummoves = (int) (Math.pow(2, n)-1);
		
		for (int i=1;i<=nummoves;i++){
			System.out.println(i);
			if(i%3==1){
				if(aux.isEmpty()){
					aux.push(src.pop());
				}else if(src.isEmpty()){
					src.push(aux.pop());
				}
				else{
					if((Integer)src.peek() < (Integer)aux.peek()){ //transfer lesser number
						aux.push(src.pop());
					}
					else{
						src.push(aux.pop());
					}
				}
			}else if(i%3==2){
				if(dest.isEmpty()){
					dest.push(src.pop());
				}else if(src.isEmpty()){
					src.push(dest.pop());
				}else{
					if((Integer)src.peek() < (Integer)dest.peek()){
						dest.push(src.pop());
					}else{
						src.push(dest.pop());
					}
				}
			}else if(i%3==0){
				if(dest.isEmpty()){
					dest.push(aux.pop());
				}else if(aux.isEmpty()){
					aux.push(dest.pop());
				}else{
					if((Integer)aux.peek() < (Integer)dest.peek()){
						dest.push(aux.pop());
					}else{
						aux.push(dest.pop());
					}
				}
			}
		}
		System.out.println("Here");
		printstack(aux);
	}
	
	public void printstack(BoundedStack dest){
		while(!dest.isEmpty()){
			System.out.print(dest.pop()+"-->");
		}
	}
  public static void main(String[] args){
	  towerofhanoi twr = new towerofhanoi();
	  int[] arr = {4,3,2,1};
	  BoundedStack src = new BoundedStack(arr.length);
	  for(int i=0;i<arr.length;i++){
		  src.push(arr[i]);
	  }
	  twr.tower(src,arr.length);
  }
}
