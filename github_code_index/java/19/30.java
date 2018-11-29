
public class bucketsort {

	public static void Bucketsort(int[] src, int[] dst, int len, int range) {
	    /** �l���Ƃ̏o���� */
	    int[] count = new int[range];
	    /** �\�[�g��z��ɂ�����l���Ƃ̊J�n�ʒu */
	    int[] offset = new int[range];
	    /** ���[�v����p */
	    int i;
	 
	    /* �o���񐔂𐔂��� */ 
	    for (i = 0; i < len; i++)
	        count[src[i]]++;
	    /* �J�n�ʒu�v�Z */
	    offset[0] = 0;
	    for (i = 1; i < range; i++)
	        offset[i] = offset[i-1] + count[i-1];
	    /* �\�[�g���� */
	    for (i = 0; i < len; i++) {
	        int target = src[i];
	        dst[offset[target]] = target;
	        offset[target]++;
	    }
	    for(i = 0; i < len; i++){
	    	System.out.print(dst[i]);
	    }
	}

	
	public static void main(String[] args) {
		int[] src = {1,2,5,4,6,9,7,8,2,0};
		int[] dst = new int[10];
		int len = src.length;
		int range = 10;
		
		Bucketsort(src, dst, len, range);
	}

}
