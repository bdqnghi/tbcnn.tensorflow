import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

 public class Control {
 String[] tempstr;
	void Control(){
		
	}
	
	//read a file and record it
	String[] readFile(File file)throws IOException{
		String temp="";
		BufferedInputStream bis=new BufferedInputStream(new FileInputStream(file));
		byte b[]=new byte[1024*1024];
		int length=bis.read(b);  
		temp=new String(b,0,length);
		bis.close();  
		tempstr=temp.split("\n");
		return tempstr;
	}
	
	
	/*Red-Black-Tree*/
	
	//Check if a specific word is existing in the RBT
	public boolean RBT_isExist(RBTree tree,String key){
		if(tree.getRoot()!=null){
			RBTnode search=tree.search(tree.getRoot(), key);
		    if((search==null)||(!search.getKey().equals("-"))){
			     return true;
	 	}
		    else {
			    return false;
		    }
		}
		else{
			return false;
		}
	}
	
	
	//insert the word and its meaning into the RBT
	public void insert_RBT(RBTree tree,String key,String value){
		if(!RBT_isExist(tree,key)){
			tree.insert(new RBTnode(key,value));
		}
		else{
		}
	}
	
	
	//delete a specific word
	public void del_RBT(RBTree tree,String key){
		if(RBT_isExist(tree,key)){
			tree.delete(tree.search(tree.getRoot(), key));
		}
		else{
			
		}
	}
	
	//initialize the RBT
	public 	void init_RBT(RBTree tree){
		String[] RBTstr = null;
		try {
			RBTstr=readFile(new File("1_initial.txt"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	  
		for(int i=1;i<RBTstr.length-1;i+=2){
		
			String key=RBTstr[i];
			RBTstr[i]=key.substring(0,key.indexOf("\r"));
			key=RBTstr[i];
			String value=RBTstr[i+1];
			RBTstr[i+1]=value.substring(0,value.indexOf("\r"));
			value=RBTstr[i+1];
			if(!RBT_isExist(tree,key)){
				insert_RBT(tree,key,value);
			}
			else{
			
			}
			
		}
	
	}
	
	
	//give the Chinese meaning of the given word
	public String RBT_translate(RBTree tree,String key){
		    RBTnode s=tree.search(tree.getRoot(), key);
			
			if((s==null)||(!s.getKey().equals("-"))){
				String value=s.getValue();
				return value;
			}
			else{
				return "【RBT Dictionary】: 老子也不知道这是啥玩意儿";
			}
		
		
	}
	
	
	
	
	/*B-Tree*/
	
	
	//Check if a specific word is existing in the BT
	public boolean BT_isExist(BTree btree,String key){
		if(btree.getRoot()!=null){
			Bpair search=btree.search(btree.getRoot(), key);
		    BTnode N=search.getPNode(search);
		    if(N!=null){
		    	return true;
		    }
		    else{
		    	return false;
		    }
		}
		else{
			return false;
		}
	}
	
	
	//insert a word and its meaning into the BT
	public void insert_BT(BTree btree,String key,String value){
		if(!BT_isExist(btree,key)){
			btree.insert(btree, key, value);
		}
		else{
		}
	}
	
	//initialize the BT
	 public void init_BT(BTree btree){
			String[] BTstr=null;
			try {
				BTstr=readFile(new File("1_initial.txt"));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for(int i=1;i<BTstr.length-1;i+=2){
				String key=BTstr[i];
				BTstr[i]=key.substring(0,key.indexOf("\r"));
				key=BTstr[i];
				String value=BTstr[i+1];
				BTstr[i+1]=value.substring(0,value.indexOf("\r"));
				value=BTstr[i+1];
				if(!BT_isExist(btree,key)){
					insert_BT(btree,key,value);
				}
				else{
		
				}
				
			}
			
		}
	
	 
	 //give the Chinese meaning of the given word
	public String BT_translate(BTree btree,String key){
		Bpair search=btree.search(btree.getRoot(), key);
	    BTnode N=search.getPNode(search);
	    if(N!=null){
			return N.getValue(search.getPIndex(search));
		}
		else{
			return "【BT Dictionary】: 老子也不知道这是啥玩意儿";
		}
	
}
	
}
