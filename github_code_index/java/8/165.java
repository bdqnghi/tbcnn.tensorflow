package menon.cs6890.assignment5;

public class LevenshteinEditDistanceTableElement {
	
	private LevenshteinEditDistanceTableElement minimumEditDistanceFromSameSource;
	private LevenshteinEditDistanceTableElement minimumEditDistanceFromSameTarget;
	private LevenshteinEditDistanceTableElement minimumEditDistanceFromDiagonal;
	private int alignmentCost;
	private int sourceStringOffset;
	private int targetStringOffset;
	
	/**
	 * Constructor
	 * 
	 * @param minimumEditDistanceFromSameSource
	 * @param minimumEditDistanceFromSameTarget
	 * @param minimumEditDistanceFromDiagonal
	 * @param alignmentCost
	 * @param sourceStringOffset
	 * @param targetStringOffset
	 */
	public LevenshteinEditDistanceTableElement(LevenshteinEditDistanceTableElement minimumEditDistanceFromSameSource,
			                                   LevenshteinEditDistanceTableElement minimumEditDistanceFromSameTarget,
			                                   LevenshteinEditDistanceTableElement minimumEditDistanceFromDiagonal,
			                                   int alignmentCost,
			                                   int sourceStringOffset,
			                                   int targetStringOffset) {
		
		if (alignmentCost < 0 || sourceStringOffset < 0 || targetStringOffset < 0) {
			throw new IllegalArgumentException("Negative values not allowed");
		}
		
		this.minimumEditDistanceFromSameSource = minimumEditDistanceFromSameSource;
		this.minimumEditDistanceFromSameTarget = minimumEditDistanceFromSameTarget;
		this.minimumEditDistanceFromDiagonal = minimumEditDistanceFromDiagonal;
		this.alignmentCost = alignmentCost;
		this.sourceStringOffset = sourceStringOffset;
		this.targetStringOffset = targetStringOffset;
	}
	
	
	/**
	 * @return the back trace element - the element with the least cost
	 */
	public LevenshteinEditDistanceTableElement getBackTraceElement() {
		
		LevenshteinEditDistanceTableElement returnValue = null;
		
		LevenshteinEditDistanceTableElement backTraceElement1 = this.minimumEditDistanceFromSameSource != null ? this.minimumEditDistanceFromSameSource : null;
		LevenshteinEditDistanceTableElement backTraceElement2 = this.minimumEditDistanceFromSameTarget != null ? this.minimumEditDistanceFromSameTarget : null;
		LevenshteinEditDistanceTableElement backTraceElement3 = this.minimumEditDistanceFromDiagonal != null ? this.minimumEditDistanceFromDiagonal : null;
		
		if (backTraceElement1 != null) {
			returnValue = backTraceElement1;
		}
		
		if (backTraceElement2 != null) {
			if (returnValue != null) {
				if (backTraceElement2.getAlignmentCost() < returnValue.getAlignmentCost()) {
					returnValue = backTraceElement2;
				}
			} else {
				returnValue = backTraceElement2;
			}
		}
		
		if (backTraceElement3 != null) {
			if (returnValue != null) {
				if (backTraceElement3.getAlignmentCost() < returnValue.getAlignmentCost()) {
					returnValue = backTraceElement3;
				}
			} else {
				returnValue = backTraceElement3;
			}
		}
		
		return returnValue;
				
	}
	

	public LevenshteinEditDistanceTableElement getMinimumEditDistanceFromSameSource() {
		return minimumEditDistanceFromSameSource;
	}


	public void setMinimumEditDistanceFromSameSource(
			LevenshteinEditDistanceTableElement minimumEditDistanceFromSameSource) {
		this.minimumEditDistanceFromSameSource = minimumEditDistanceFromSameSource;
	}


	public LevenshteinEditDistanceTableElement getMinimumEditDistanceFromSameTarget() {
		return minimumEditDistanceFromSameTarget;
	}


	public void setMinimumEditDistanceFromSameTarget(
			LevenshteinEditDistanceTableElement minimumEditDistanceFromSameTarget) {
		this.minimumEditDistanceFromSameTarget = minimumEditDistanceFromSameTarget;
	}


	public LevenshteinEditDistanceTableElement getMinimumEditDistanceFromDiagonal() {
		return minimumEditDistanceFromDiagonal;
	}


	public void setMinimumEditDistanceFromDiagonal(
			LevenshteinEditDistanceTableElement minimumEditDistanceFromDiagonal) {
		this.minimumEditDistanceFromDiagonal = minimumEditDistanceFromDiagonal;
	}
	
	public int getAlignmentCost() {
		return alignmentCost;
	}
	public void setAlignmentCost(int alignmentCost) {
		this.alignmentCost = alignmentCost;
	}
	public int getSourceStringOffset() {
		return sourceStringOffset;
	}
	public void setSourceStringOffset(int sourceStringOffset) {
		this.sourceStringOffset = sourceStringOffset;
	}
	public int getTargetStringOffset() {
		return targetStringOffset;
	}
	public void setTargetStringOffset(int targetStringOffset) {
		this.targetStringOffset = targetStringOffset;
	}
	
}
