/**
* Problem Link: https://leetcode.com/problems/lru-cache/description/
*
* @author Ciel


*/
import java.util.LinkedHashMap;
public class LRUCache extends LinkedHashMap<Integer,Integer>{
  private int MaxCap =5;
  public LRUCache (int SIZE){
      super (SIZE,1.0f,true);
      this. MaxCap = SIZE;
  }
  
   public Integer get(Integer key){
        return this.getOrDefault(key,-1);   
   }
   
   public void set(Integer key,Integer value){
      //  if(this.containsKey(key)){//re-insert
        //    this.remove(key);
    //    }
        this.put(key,value);
   }
   
       @Override 
       protected boolean removeEldestEntry(Map.Entry eldest) {
            return size()> MaxCap;
       }
}











