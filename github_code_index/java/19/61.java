//BitSet
public class Solution {
    public int firstMissingPositive(int[] nums) {
        if(nums == null || nums.length == 0) return 1;

        BitSet bs = new BitSet();
        for(int n : nums){
            if( n <= 0) continue;
            bs.set(n, true);
        }

        for(int i = 1; i < Integer.MAX_VALUE; i++){
            if(!bs.get(i)) return i;
        }
        
        return Integer.MAX_VALUE;
    }
}

//Bucket-Sort
public class Solution {
    public int firstMissingPositive(int[] nums) {
        if(nums == null || nums.length == 0) return 1;

        for(int i = 0; i < nums.length; i++){
            while(nums[i] != i + 1){
                if(nums[i] <= 0 || nums[i] > nums.length || nums[i] == nums[ nums[i] - 1 ]){
                    break;
                }
                int tmp = nums[i];
                nums[i] = nums[tmp - 1];
                nums[tmp - 1] = tmp;
            }
        }
        for(int i = 0; i < nums.length; i++){
            if(nums[i] != i + 1){
                return i + 1;
            }
        }
        return nums.length + 1;
    }
}