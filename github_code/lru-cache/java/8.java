package SimCache;

/**
 *
 * @author guillem
 */

public class LRUCache extends memoryCache{
    
    
    public LRUCache(){
        
        this(4);
        
    }
    
    public LRUCache(int blocks){
        
        this.memBlocks= blocks;
        this.numberMises = 0;
        
        
        
    }
   
    @Override
    boolean hitBlock(Object block){
        
        this.CacheBlocks.remove(block);
        this.CacheBlocks.add(block);
        
        return true;
    }

    @Override
    boolean missBlock(Object block) {
        
        if (this.CacheBlocks.size()<this.getNumBlock()){
            
            this.CacheBlocks.add(block);
        
        }else{
            
            this.CacheBlocks.remove(0);
            this.CacheBlocks.add(block);
        
        }
        
        this.numberMises++;
        return false;
    }

   
}
