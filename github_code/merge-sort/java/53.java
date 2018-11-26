package profile.reducer;

import java.io.Serializable;

public class Sort implements Serializable {
  
    private static final long serialVersionUID = -2666953270300858669L;

    private InMemorySortMerge inMemorySortMerge; // Segments in [ShuffleBound - ReduceBuffer] ==> onDiskSeg
    						 // && if(count(onDiskSegs) < io.sort.factor)
    
    private MixSortMerge mixSortMerge; // Segments in ShuffleBound (not merged in InMemorySortMerge) + onDiskSegs ==> logical big segment
    					
    private FinalSortMerge finalSortMerge; // Segments in ReduceBuffer + onDiskSeg(s) ==> logical big segment


    public void setInMemorySortMerge(
	    int segmentsNum, 
	    long records, 
	    long bytesBeforeMerge,
	    long rawLength, 
	    long compressedLength) {
	
	inMemorySortMerge = new InMemorySortMerge(segmentsNum, records, 
		bytesBeforeMerge, rawLength, compressedLength);
    }
    
    public void setFinalSortMerge(int inMemSegsNum, long inMemBytes, String[] taskIds) {
	
	int[] segMapperIds = new int[taskIds.length];
	for(int i = 0; i < segMapperIds.length; i++)
	    segMapperIds[i] = Integer.parseInt(taskIds[i]);
	
	finalSortMerge = new FinalSortMerge(inMemSegsNum, inMemBytes, segMapperIds);
    }

    public void setMixSortMerge(
	    int inMemSegsNum, 
	    long inMemSegsBytes,
	    int onDiskSegsNum, 
	    long onDiskSegsBytes) {
	
	mixSortMerge = new MixSortMerge(inMemSegsNum, inMemSegsBytes, onDiskSegsNum, onDiskSegsBytes);
    }

    public InMemorySortMerge getInMemorySortMerge() {
        return inMemorySortMerge;
    }

    public MixSortMerge getMixSortMerge() {
        return mixSortMerge;
    }

    public FinalSortMerge getFinalSortMerge() {
        return finalSortMerge;
    }

    public String toString() {
	StringBuilder sb = new StringBuilder();
	
	if(inMemorySortMerge != null)
	    sb.append("[InMemSortMerge] " + "num = " + inMemorySortMerge.getSegmentsNum()
		    + ", records = " + inMemorySortMerge.getRecords() + ", bytes = " 
		    + inMemorySortMerge.getBytesBeforeMerge() + " | " + inMemorySortMerge.getRawLength() + "\n");
	
	if(mixSortMerge != null)
	    sb.append("[MixSortMerge] " + "InMemSegsNum = " + mixSortMerge.getInMemSegsNum() + ", InMemSegsBytes = "
		    + mixSortMerge.getInMemSegsBytes() + ", OnDiskSegsNum = " + mixSortMerge.getOnDiskSegsNum()
		    + ", OnDiskSegsBytes = " + mixSortMerge.getOnDiskSegsBytes() + "\n");
	
	if(finalSortMerge != null) {
	    sb.append("[FinalSortMerge] " + "InMemSegsNum = " + finalSortMerge.getInMemSegsNum() + ", InMemSegsBytes = " 
		    + finalSortMerge.getInMemSegsBytes() + "\n");
	    sb.append("[SegsInReduceBuffer] " + finalSortMerge.getSegIdsToString() + "\n");
	}
	
	return sb.toString();
    }
    
}
