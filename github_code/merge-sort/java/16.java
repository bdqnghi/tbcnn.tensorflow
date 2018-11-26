package profile.task.reducer;

import java.io.Serializable;

public class Sort implements Serializable {
	private int inMemorySegmentsLeftAfterShuffle;
	private int onDiskSegmentsLeftAfterShuffle;
	
	private InMemorySortMerge inMemorySortMerge; //first merge the in-memory segments in sort phase, doens't contain intermediate merge
	private MixSortMerge mixSortMerge; //then merge the in-memory segments and on-disk segments in sort phase
	private FinalSortMerge finalSortMerge; //finally merge the left in-memory segments and merged on-disk segments
	
	private long reduceInputRecords = 0;
	private long reduceInputBytes = 0;
	
	private long startMergeTimeMS;
	private long stopMergeTimeMS;
	
	//segments info after shuffle phase, and add them into sort phase
	public void setInMemorySegmentsLeftAfterShuffle (int inMemorySegmentsLeftAfterShuffle) {
		this.inMemorySegmentsLeftAfterShuffle = inMemorySegmentsLeftAfterShuffle;
	}
	
	public void addFinalSortMergeItem(long stopFinalSortMergeTimeMS,
			int inMemorySegmentsNum, long inMemBytes) {
		finalSortMerge = new FinalSortMerge();
		finalSortMerge.set(stopFinalSortMergeTimeMS, inMemorySegmentsNum, inMemBytes);
		
		reduceInputRecords += finalSortMerge.getRecords();
		//reduceInputBytes += finalSortMerge.getInMemorySegmentsSize();
		
	}

	public void addMixSortMergeItem(long stopMixSortMergeTimeMS,
			int inMemorySegmentsNum, long inMemorySegmentsSize,
			int onDiskSegmentsNum, long onDiskSegmentsSize) {
		if(mixSortMerge == null)
			mixSortMerge = new MixSortMerge();
		mixSortMerge.set(stopMixSortMergeTimeMS, inMemorySegmentsNum, inMemorySegmentsSize,
				onDiskSegmentsNum, onDiskSegmentsSize);
		
		reduceInputRecords += mixSortMerge.getInMemoryRecords() + mixSortMerge.getOnDiskRecords();
		//reduceInputBytes += mixSortMerge.getInMemorySegmentsSize() + mixSortMerge.getOnDiskSegmentsSize(); 
	}

	public void addIntermediateMergeInSortItem(String mergeLoc,
			long mergeTimeMS, int mergeSegmentsNum, int totalSegmentsNum,
			long writeRecords, long rawLengthInter, long compressedLengthInter) {
		if(mergeLoc.equals("MixSortMerge")) {
			if(mixSortMerge == null)
				mixSortMerge = new MixSortMerge();
			mixSortMerge.addIntermediateMergeItem(mergeTimeMS, mergeSegmentsNum, totalSegmentsNum,
					writeRecords, rawLengthInter, compressedLengthInter);
		}
			
	}

	public void addLastPassMergeInSortItem(String mergeLoc, long mergeTimeMS,
			int lastMergePassSegmentsNum, long lastMergePassTotalSize) {
		if(mergeLoc.equals("MixSortMerge")) {
			if(mixSortMerge == null)
				mixSortMerge = new MixSortMerge();
			mixSortMerge.addLastPassMergeItem(mergeTimeMS, lastMergePassSegmentsNum, lastMergePassTotalSize);
		}	
	}
	
	public void setOnDiskSegmentsLeftAfterShuffle (int onDiskSegmentsLeftAfterShuffle) {
		this.onDiskSegmentsLeftAfterShuffle = onDiskSegmentsLeftAfterShuffle;
	}
	
	//set merge info in sort phase
	public void setInMemorySortMergeItem(long stopInMemorySortMergeTimeMS,
			int segmentsNum, long records, long bytesBeforeMerge,
			long rawLength, long compressedLength) {
		inMemorySortMerge = new InMemorySortMerge(stopInMemorySortMergeTimeMS, segmentsNum, records, bytesBeforeMerge,
			rawLength, compressedLength);
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

	public void setMixSortMerge(MixSortMerge mixSortMerge) {
		this.mixSortMerge = mixSortMerge;
		
	}

	public void setFinalSortMerge(FinalSortMerge finalSortMerge) {
		this.finalSortMerge = finalSortMerge;
		
	}
	
	public long getReduceInputRecords() {
		return reduceInputRecords;
	}
	
	public long getReduceInputBytes() {
		return reduceInputBytes;
	}

	public void setReduceInputBytes(long reduceInputBytes) {
		this.reduceInputBytes = reduceInputBytes;
	}
	
	
}
