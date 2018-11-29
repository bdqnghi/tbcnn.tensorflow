package mergesort.debug;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

import mergesort.MergeSortStage;
import mergesort.MergeSortUtils;
import mergesort.MergeSortStage.StageType;

public class DebugMergeSortParallel
{    
    @SuppressWarnings("serial")
	private class SortTask extends RecursiveTask<MergeSortStage>
    {
        private MergeSortStage divide_msr;
        private MergeSortStage merge_msr;
        private int[] array;
        
        public SortTask(int[] array)
        {
            this.array = array;
            this.divide_msr = new MergeSortStage(array);
        }
        
        public SortTask(int[] array, int task_id, MergeSortStage... previous_stages)
        {
            this(array, task_id, StageType.Divide, previous_stages);
        }
        
        public SortTask(int[] array, int task_id, StageType stage_type, MergeSortStage... previous_stages)
        {
            this.array = array;
            this.divide_msr = new MergeSortStage(array, stage_type, task_id, previous_stages);
        }
        
        /**
         * Ordina parallelamente l'array dato con MergeSort.
         * Anche l'operazione di Merge è eseguita parallelamente.
         */
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
                // Merge parte sinistra (in parallelo)
                SortTask right_ct = new SortTask(MergeSortUtils.take_half_right(array), -1, this.divide_msr);
                right_ct.fork();
                
                // Merge parte sinistra (su questo thread)
                SortTask left_ct = new SortTask(MergeSortUtils.take_half_left(array), this.divide_msr.getTaskID(), this.divide_msr);
                
                // Risultati dei mergesort sui sottoarray
                MergeSortStage left_msr = left_ct.compute();
                MergeSortStage right_msr = right_ct.join();
                
                // Unisco i risultati sul thread corrente in parallelo con altri thread
                MergeTaskResult mtr = new MergeTask(left_msr.getResult(), right_msr.getResult()).compute();
                array = mtr.array;
            	
                // Combino in tempi e imposto nel result l'array ordinato
                this.merge_msr = new MergeSortStage(array, StageType.Merge, this.divide_msr.getTaskID(), mtr.forks, left_msr, right_msr);
                
                return this.merge_msr; 
            }
        }        
    }
    
    private class MergeTaskResult
    {
    	public int forks;
    	public int[] array;
    	
    	public MergeTaskResult(int forks, int[] array)
    	{
    		this.forks = forks;
    		this.array = array;
    	}
    }
    
    @SuppressWarnings("serial")
	private class MergeTask extends RecursiveTask<MergeTaskResult>
    {
        private final int[] a;
        private final int[] b;
        private MergeTaskResult sub_a_result;
        private MergeTaskResult sub_b_result;
        
        public MergeTask (int[] array_left, int[] array_right)
        {
        	// Seleziona gli array "A" e "B" in base alla lunghezza
        	if( array_left.length >= array_right.length )
            {
            	this.a = array_left;
                this.b = array_right;
            }
            else
            {
            	this.a = array_right;
                this.b = array_left;
            }
        }
        
        /**
         * Esegue parallelamente l'operazione di Merge 
         * di due array ordinati in modo crescente.
         */
        @Override
        protected MergeTaskResult compute() 
        {
        	// Se A è vuoto, lo è anche B (A è l'array più grande)
        	if(this.a.length == 0)
        		return new MergeTaskResult(0, new int[] {});
        	
        	// Se B è vuoto ritorna A (sicuro non vuoto)
        	if(this.b.length == 0)
        		return new MergeTaskResult(0, this.a);
        	
        	// Se A ha solo 1 elemento, lo ha anche B (A è l'array più grande, e sò già che B non è vuoto)
        	if(this.a.length == 1)
        	{
        		if(this.a[0] <= this.b[0])
        			return new MergeTaskResult(0, new int[]{this.a[0], this.b[0]});
    			else
    				return new MergeTaskResult(0, new int[]{this.b[0], this.a[0]});
        	}
        	
        	// Applico il cutoff al merge (se necessario)
        	if( cutoff != 1 && (this.a.length+this.b.length) <= cutoff )
        		return new MergeTaskResult(0, MergeSortUtils.merge_two_sorted_array(this.a, this.b));
        	
        	// Trovo l'indice dell'elemento intermedio nell'array A
            int median = this.a.length / 2;
            
            // Cerco nell'array B il primo numero maggiore o uguale di A[median]
            int d = MergeSortUtils.search_split_point(this.a[median], this.b);
            
        	// Se la parte sinistra dell'array B è vuota
            if(d==0)
            {
            	// Esegue sulle 2 metà destre (in questo thread)
                MergeTask subB = new MergeTask
                (
            		Arrays.copyOfRange(this.a, median, this.a.length), 
                    Arrays.copyOfRange(this.b, d, this.b.length)
        		);
                
                sub_b_result = subB.compute();
                
            	// La parte destra è data dalle due parti destre, mentre la parte sinistra è data dalla sola parte sinistra di A
                return new MergeTaskResult(sub_b_result.forks, MergeSortUtils.merge_arrays(Arrays.copyOfRange(this.a, 0, median), sub_b_result.array));
            }
            
            // Se la parte destra dell'array B è vuota
            if(d==this.b.length)
            {
            	// Esegue sulle 2 metà siniste (in questo thread)
                MergeTask subA = new MergeTask
                (
                    Arrays.copyOfRange(this.a, 0, median), 
                    Arrays.copyOfRange(this.b, 0, d)
        		);
                
                sub_a_result = subA.compute();
                
                // La parte sinistra è data dalle due parti sinistre, mentre la parte destra è data dalla sola parte destra di A
                return new MergeTaskResult(sub_a_result.forks, MergeSortUtils.merge_arrays(sub_a_result.array, Arrays.copyOfRange(this.a, median, this.a.length)));
            }
            
            // Esegue sulle 2 metà siniste (in parallelo)
            MergeTask subA = new MergeTask
            (
                Arrays.copyOfRange(this.a, 0, median), 
                Arrays.copyOfRange(this.b, 0, d)
    		);
            subA.fork();
            
            // Esegue sulle 2 metà destre (in questo thread)
            MergeTask subB = new MergeTask
            (
                Arrays.copyOfRange(this.a, median, this.a.length), 
                Arrays.copyOfRange(this.b, d, this.b.length)
            );
            
            // Attende i risultati
            sub_b_result = subB.compute();
            sub_a_result = subA.join();
            
            // Fonde i due array risultanti
			return new MergeTaskResult(sub_a_result.forks + sub_b_result.forks + 1, MergeSortUtils.merge_arrays(sub_a_result.array, sub_b_result.array));
        }       
    }
    
	private volatile int cutoff;
    private final ForkJoinPool fj;
	
    public DebugMergeSortParallel()
	{
		this(1);
	}
    
	public DebugMergeSortParallel(int cutoff)
	{
		this.cutoff = cutoff;
		this.fj = new ForkJoinPool();
	}
	
    public MergeSortStage sort(int[] array)
    {
        MergeSortStage merge_result = null;
        SortTask ct = new SortTask(array);
            
        merge_result = fj.invoke(ct);
        merge_result.setEndStage();
        
        //necessaria pulizia forzata in caso di usi consecutivi della classe
        System.gc();
        
        return merge_result;
    }

}
