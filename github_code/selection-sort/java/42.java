package selectionsort;

import java.util.ArrayList;
import java.util.List;

import logic.ForInstruction;
import logic.IfInstruction;
import logic.Instruction;
import logic.SortAlgorithm;
import logic.Step;
import logic.Util;

public class SelectionSort extends SortAlgorithm<SelectionSortState> {

	private int i;
	private int j;
	private int min;
	
	private static List<Instruction> allInstructions = new ArrayList<Instruction>();
	private static List<Instruction> instructions = new ArrayList<Instruction>();
	static
	{
		
		
		Instruction setMinInstruction = new Instruction("min = j");
		
		IfInstruction ifInstruction = new IfInstruction("a[j] < a[min]");
		ifInstruction.addCoreInstruction(setMinInstruction);
		
		ForInstruction innerForInstruction = new ForInstruction("j=i; j < a.length; j++");
		innerForInstruction.addCoreInstruction(ifInstruction);
		
		Instruction swapInstruction = new Instruction("Util.swap(a, i, min);");
		
		Instruction minInitializationInstruction = new Instruction("min = i");
		
		ForInstruction outerForInstruction = new ForInstruction("i=0;i<a.length;i++");
		outerForInstruction.addCoreInstruction(minInitializationInstruction);
		outerForInstruction.addCoreInstruction(innerForInstruction);
		outerForInstruction.addCoreInstruction(swapInstruction);
		
		SelectionSort.instructions.add(outerForInstruction);
		

		SelectionSort.allInstructions.add(outerForInstruction);
		SelectionSort.allInstructions.add(minInitializationInstruction);
		SelectionSort.allInstructions.add(innerForInstruction);
		SelectionSort.allInstructions.add(ifInstruction);
		SelectionSort.allInstructions.add(setMinInstruction);
		SelectionSort.allInstructions.add(swapInstruction);
	}
	


	@Override
	public List<Step<SelectionSortState>> run() {
		List<Step<SelectionSortState>> stepList = new ArrayList<Step<SelectionSortState>>();
		
		for(i=0;i<a.length;i++)
		{
			stepList.add(this.getStep(SelectionSort.allInstructions.get(0)));
			
			min = i;
			stepList.add(this.getStep(SelectionSort.allInstructions.get(1)));
			
			for(j=i; j < a.length; j++)
			{
				stepList.add(this.getStep(SelectionSort.allInstructions.get(2)));
				
				stepList.add(this.getStep(SelectionSort.allInstructions.get(3)));
				
				if(a[j] < a[min])
				{
					min = j;
					stepList.add(this.getStep(SelectionSort.allInstructions.get(4)));
				}
			}
			Util.swap(a, i, min);
			stepList.add(this.getStep(SelectionSort.allInstructions.get(5)));
		}
		
		return stepList;
	}

	@Override
	public SelectionSortState getState() {
		SelectionSortState selectionSortState = new SelectionSortState();
		selectionSortState.setArray(this.a.clone());
		selectionSortState.setI(this.i);
		selectionSortState.setJ(this.j);
		selectionSortState.setMin(this.min);
		
		return selectionSortState;
	}

	@Override
	public List<Instruction> getInstructions() {
		return SelectionSort.instructions;
	}
}
