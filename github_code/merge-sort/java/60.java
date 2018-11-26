package data.model.reducer;

import profile.task.reducer.FinalSortMerge;
import profile.task.reducer.InMemorySortMerge;
import profile.task.reducer.MixSortMerge;
import profile.task.reducer.Reduce;
import profile.task.reducer.Sort;

public class ReduceModel {

	public static Reduce computeReduce(Sort sort, IORatioModel ioRatio) {
		Reduce reduce = new Reduce();
		
		FinalSortMerge eFinalSortMerge = sort.getFinalSortMerge();
		MixSortMerge eMixSortMerge = sort.getMixSortMerge();
		InMemorySortMerge eInMemorySortMerge = sort.getInMemorySortMerge();
		
		assert(eFinalSortMerge != null || eMixSortMerge != null || eInMemorySortMerge != null);
		
		//long inputkeyNum = 0; //equals "Reduce input groups" normally
		long inputKeyValuePairsNum = 0; //equals "Reduce input records"
		long inputBytes = sort.getReduceInputBytes(); // equals rawLength after merge in Sort
		
		long outputKeyValuePairsNum; //equals "Reduce output records"
		long outputBytes; // depends on "HDFS_BYTES_WRITTEN" and dfs.replication
		
		if(eFinalSortMerge != null) {
			inputKeyValuePairsNum += eFinalSortMerge.getRecords();
			//inputBytes += eFinalSortMerge.getInMemorySegmentsSize();
		}
		
		if(eMixSortMerge != null) {
			inputKeyValuePairsNum += eMixSortMerge.getInMemoryRecords() + eMixSortMerge.getOnDiskRecords();
			//inputBytes += eMixSortMerge.getInMemorySegmentsSize() + eMixSortMerge.getOnDiskSegmentsSize();
		}
		
		if(eFinalSortMerge == null && eMixSortMerge == null && eInMemorySortMerge != null) {
			System.err.println("No MixSortMerge or FinalSortMerge exist!");
		}
		
		outputKeyValuePairsNum = (long) (ioRatio.getReduceRecordsIoRatio() * inputKeyValuePairsNum);
		outputBytes = (long) (ioRatio.getReduceBytesIoRatio() * inputBytes);
		
		reduce.setInputkeyNum(0);
		reduce.setInputKeyValuePairsNum(inputKeyValuePairsNum);
		reduce.setInputBytes(inputBytes);
		reduce.setOutputKeyValuePairsNum(outputKeyValuePairsNum);
		reduce.setOutputBytes(outputBytes);
		
		//System.out.println("[Reduce] <inputRecords = " + inputKeyValuePairsNum + ", inputBytes = " + inputBytes
		//		+ ", outputRecords = " + outputKeyValuePairsNum + ", outputBytes = " + outputBytes + ">");
		
		return reduce;
	}

}
