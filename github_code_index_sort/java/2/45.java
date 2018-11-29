package mergesort.debug;

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

import mergesort.MergeSortStage;
import mergesort.MergeSortUtils;
import mergesort.MergeSortStage.StageType;

public class DebugMergeSortSemiParallel
{
	@SuppressWarnings("serial")
	class MergeSortThread extends RecursiveTask<MergeSortStage>
    {
        private MergeSortStage divide_msr;
        private MergeSortStage merge_msr;
        private int[] array;
        
        public MergeSortThread(int[] array)
        {
            this.array = array;
            this.divide_msr = new MergeSortStage(array);
        }
        
        public MergeSortThread(int[] array, int task_id, MergeSortStage... previous_stages)
        {
            this(array, task_id, StageType.Divide, previous_stages);
        }
        
        public MergeSortThread(int[] array, int task_id, StageType stage_type, MergeSortStage... previous_stages)
        {
            this.array = array;
            this.divide_msr = new MergeSortStage(array, stage_type, task_id, previous_stages);
        }
        
        @Override
        protected MergeSortStage compute()
        {
            if(array.length <= cutoff)
            {
            	// Ordino l'array direttamente
            	if(cutoff > 1)
                	this.divide_msr.directSort();
                
                return this.divide_msr;
            }
            else
            {                            
                //creo e avvio su un altro thread il merge della parte sinistra
                MergeSortThread right_msst = new MergeSortThread(MergeSortUtils.take_half_right(array), -1, this.divide_msr);
                right_msst.fork();
                
                //creo e avvio su questo thread il merge della parte destra                
                MergeSortThread left_msst = new MergeSortThread(MergeSortUtils.take_half_left(array), this.divide_msr.getTaskID(), this.divide_msr);
                
                //risultati dei mergesort sui sottoarray
                MergeSortStage left_msr = left_msst.compute();
                MergeSortStage right_msr = right_msst.join();
                
                //unisco i risultati sul thread corrente                    
                array = MergeSortUtils.merge_two_sorted_array(left_msr.getResult(), right_msr.getResult());               
                
                //combino in tempi e imposto nel result l'array ordinato
                this.merge_msr = new MergeSortStage(array, StageType.Merge, this.divide_msr.getTaskID(), left_msr, right_msr);
                
                return this.merge_msr;  
            }   
        }        
    }
    
	private volatile int cutoff;
    private final ForkJoinPool fj;
	
    public DebugMergeSortSemiParallel()
	{
        this(1);
	}
    
	public DebugMergeSortSemiParallel(int cutoff)
	{
		this.cutoff = cutoff;
		this.fj = new ForkJoinPool();
	}
	
    public MergeSortStage sort(int[] array)
    {
        MergeSortStage merge_result = null;
        MergeSortThread msst = new MergeSortThread(array);
        
        merge_result = fj.invoke(msst);

        merge_result.setEndStage();
        
        return merge_result;
    }
}
