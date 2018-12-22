package project;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;

/**
 * DEFINITION OF REDBLACKTREE HASH TABLE
 * @author DAWEI JIA
 *
 * @param <T>
 * @param <V>
 */
public class RedBlackHash<T extends Comparable,V> {
	
	private int size;      //size of hash table
	
	private RedBlackTree[] rbHash;
	
	/*the constructor method*/
	public RedBlackHash(){
		
	}
	public RedBlackHash(int size){
		
		if(size%2==0){
			this.size=size+1;
		}else{
			this.size=size;
		}
		this.rbHash=new RedBlackTree[this.size];
		for(int i=0;i<this.size;i++){
			rbHash[i]=new RedBlackTree();
		}
	}
	/**
	 * class attribute getter
	 * @return szie
	 */
	public int getSize() {
		return size;
	}
	/**
	 * class attribute setter
	 * @param size
	 */
	public void setSize(int size) {
		this.size = size;
	}
	/**
	 * class attribute getter
	 * @return rbHash
	 */
	public RedBlackTree[] getRbHash() {
		return rbHash;
	}
	/**
	 * class attribute setter
	 * @param rbHash
	 */
	public void setRbHash(RedBlackTree[] rbHash) {
		this.rbHash = rbHash;
	}
	/**
	 * class that get hash code for key
	 * @param key
	 * @return keyIndex
	 */
	public int hashTable(T key){
		
		int keyIndex=key.hashCode()%this.size;
		
		return keyIndex;
	}
	/**
	 * class that search a key in a proper RedBlackTree
	 * @param key
	 */
	public void InsertIntoRedBlackTree(T key,V value){
		
		int keyIndex;
		keyIndex=this.hashTable(key);
		//System.out.println("start to insert: ("+key+","+value+")");
		rbHash[keyIndex].insertPair(key, value);
		
	}
	/**
	 * class that search a key in a proper RedBlackTree
	 * @param key
	 */
	public void SearchInRedBlackTree(T key){
		
		int keyIndex;
		keyIndex=this.hashTable(key);
		rbHash[keyIndex].searchPair(key);
		
	}
	/**
	 * RedBlackHash_inorder.out
	 */
	public void printInOrder(){
		try{
			FileWriter fw=new FileWriter("RedBlackHash_inorder.out");
			for(int i=0;i<this.size;i++){
				
				Iterator p=rbHash[i].values().iterator();
				String str=new String();
				while(p.hasNext()){
					str=""+p.next();
					fw.write(str);
					fw.write(",");
					//System.out.print(str+",");
				}
			}
			fw.close();
		}catch(IOException e){}
		
	}
	/**
	 * RedBlackHash_postorder.out
	 */
	public void printPostOrder(){
		System.out.println();
		try{
			FileWriter fw=new FileWriter("RedBlackHash_postorder.out");
			for(int i=size-1;i>=0;i--){
               
				//get the reverse order of key in the TreeMap
				TreeMap postorder=new TreeMap(Collections.reverseOrder());
				Iterator p= rbHash[i].keySet().iterator();
				while(p.hasNext()){
					T key=(T) p.next();
					V value=(V)rbHash[i].get(key);
					postorder.put(key,value);
				}
				//output values
				Iterator p1=postorder.values().iterator();
				String str=new String();
				while(p1.hasNext()){
					str=""+p1.next();
					fw.write(str);
					fw.write(",");
					//System.out.print(str+",");
				}
			}
			fw.close();
		}catch(IOException e){}
		
	}
	

}
