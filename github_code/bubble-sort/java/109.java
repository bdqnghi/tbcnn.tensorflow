package cobolprogramclasses;


/************************************************************************
 **This file automatically generated from Cobol program BUBBLE-SORT
 **Generated at time 13:58:54.73 on Tuesday, 10/06/09
 ************************************************************************/
import coboldataclasses.Data11;
import coboldataclasses.TempElement1;
import com.res.java.lib.*;
import java.util.Random;

public class BubbleSort1 extends Program {

	//*>=======================
	//@CobolSourceFile("Bubble-sort.cob",6,8) 
	//01  DATA1.
	private Data11 data1 = new Data11();
	//@CobolSourceFile("Bubble-sort.cob",9,8) 
	//77  COUNT1 PIC Z(12) COMP VALUE 1.
	private long count1;
	public long getCount1() {
		return count1;
	}
	public  void setCount1(long val) {
		count1=val;
	}
	public static FieldFormat count1Fmt_ = new FieldFormat("count1","Z(12)");
	//@CobolSourceFile("Bubble-sort.cob",10,8) 
	//77  TEMP1 PIC Z(12) COMP VALUE 2.
	private long temp1;
	public long getTemp1() {
		return temp1;
	}
	public  void setTemp1(long val) {
		temp1=val;
	}
	public static FieldFormat temp1Fmt_ = new FieldFormat("temp1","Z(12)");
	//@CobolSourceFile("Bubble-sort.cob",11,8) 
	//77  TEMP2 PIC Z(12) COMP VALUE 3.
	private long temp2;
	public long getTemp2() {
		return temp2;
	}
	public  void setTemp2(long val) {
		temp2=val;
	}
	//@CobolSourceFile("Bubble-sort.cob",12,8) 
	//77  TEMP3 PIC Z(12) COMP VALUE 4.
	private long temp3;
	public long getTemp3() {
		return temp3;
	}
	public  void setTemp3(long val) {
		temp3=val;
	}
	//@CobolSourceFile("Bubble-sort.cob",13,8) 
	//01  TEMP-ELEMENT.
	private TempElement1 tempElement = new TempElement1();
	public static void main(String[] args) {
            System.out.println("Bubble Sort 10240 Random Numbers B3enchmark Started...");
            long start=System.currentTimeMillis();
		BubbleSort1 instance_ = new BubbleSort1();
		instance_.doCobolGotoStart();
                System.out.println("Time taken: "+(System.currentTimeMillis()-start)+"ms");
		System.exit(0);
	}
	Paragraph mainline=new Paragraph(this) {
		public CobolMethod run() {
		//@CobolSourceFile("Bubble-sort.cob",19,13) 
		//DISPLAY "Enter number of elements to Sort(less than 20)"		
		//        WITH NO ADVANCING		
		System.out.print("Enter number of elements to Sort(less than 20)");
		//@CobolSourceFile("Bubble-sort.cob",21,13) 
		//ACCEPT count1		
		setCount1(10240);
		//@CobolSourceFile("Bubble-sort.cob",22,13) 
		//IF count1 <= 0 THEN		
		//   next sentence		
		//else		
		//... end-if		
		if(getCount1() <= 0) {
		} else {
			//@CobolSourceFile("Bubble-sort.cob",25,16) 
			//if count1 > 20 then			
			//else			
			//... end-if			
			if(getCount1() > 102400) {
				//@CobolSourceFile("Bubble-sort.cob",26,20) 
				//go to Mainline				
				return mainline;
			} else {
				//@CobolSourceFile("Bubble-sort.cob",28,20) 
				//Perform Input-Elements				
				doCobolPerform(inputElements,null);
				//@CobolSourceFile("Bubble-sort.cob",29,20) 
				//Perform Sort-Elements				
				doCobolPerform(sortElements,null);
			}
		}
		//@CobolSourceFile("Bubble-sort.cob",32,13) 
		//Stop run		
		//System.exit(0);
		return null;
		}
	};
	Paragraph inputElements=new Paragraph(this) {
		public CobolMethod run() {
		//@CobolSourceFile("Bubble-sort.cob",34,12) 
		//COMPUTE TEMP1 = 1		
		setTemp1(1);
		//@CobolSourceFile("Bubble-sort.cob",35,12) 
		//Perform count1 times		
		//...END-PERFORM		
		for(int i0=0;i0<getCount1();++i0) {
			//@CobolSourceFile("Bubble-sort.cob",36,20) 
			//Display "Enter Element1(PICTURE 9(2)) (" temp1 ")"			
			//   With No ADvancing			
			//System.out.print("Enter Element1(PICTURE 9(2)) ("+temp1Fmt_.format(getTemp1())+")");
			//@CobolSourceFile("Bubble-sort.cob",38,20) 
			//Accept ELEMENT1 of data1(temp1)
                    if(i0==0)
			data1.setElement1(Math.abs(new Random(10240).nextLong()),(int)getTemp1());
                    else
			data1.setElement1(Math.abs(new Random(data1.getElement1(i0)).nextLong()),(int)getTemp1());

			//@CobolSourceFile("Bubble-sort.cob",39,20) 
			//Move zeros to element2 of data1(temp1)			
			data1.setElement2(0,(int)getTemp1());
			//@CobolSourceFile("Bubble-sort.cob",40,20) 
			//Move spaces to element3 of  data1(temp1)			
			data1.setElement3(Data11.element3Fmt_.format(" "),(int)getTemp1());
			//@CobolSourceFile("Bubble-sort.cob",41,20) 
			//ADD 1 TO TEMP1			
			setTemp1(1+getTemp1());
			//@CobolSourceFile("Bubble-sort.cob",42,20) 
			//DISPLAY " "			
			System.out.println(" ");
		}
		//@CobolSourceFile("Bubble-sort.cob",45,12) 
		//COMPUTE TEMP1=1		
		setTemp1(1);
		//@CobolSourceFile("Bubble-sort.cob",46,12) 
		//Display "You Entered the following " count1		
		//         "number of elements"		
		System.out.println("You Entered the following "+count1Fmt_.format(getCount1())+"number of elements");
		//@CobolSourceFile("Bubble-sort.cob",48,12) 
		//Display '(' with no advancing		
		System.out.print("(");
		//@CobolSourceFile("Bubble-sort.cob",49,12) 
		//Perform count1 times		
		//...END-PERFORM		
		for(int i1=0;i1<getCount1();++i1) {
			//@CobolSourceFile("Bubble-sort.cob",50,20) 
			//Display "("  ELEMENT1 of data1 (temp1)			
			//    with no advancing			
			System.out.print("("+Data11.element1Fmt_.format(data1.getElement1((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",52,20) 
			//Display ","  ELEMENT2 of data1 (temp1)			
			//    with no advancing			
			System.out.print(","+Data11.element2Fmt_.format(data1.getElement2((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",54,20) 
			//Display ","  ELEMENT3 of data1 (temp1)			
			//    with no advancing			
			System.out.print(","+Data11.element3Fmt_.format(data1.getElement3((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",56,20) 
			//if temp1 not = count1			
			if(getTemp1() != getCount1()) {
				//@CobolSourceFile("Bubble-sort.cob",57,23) 
				//display '),'				
				System.out.println("),");
				//@CobolSourceFile("Bubble-sort.cob",58,20) 
				//ADD 1 TO TEMP1				
				setTemp1(1+getTemp1());
			}
		}
		//@CobolSourceFile("Bubble-sort.cob",60,12) 
		//Display ')'		
		System.out.println(")");
		return doCobolExit();
		}
	};
	Paragraph sortElements=new Paragraph(this) {
		public CobolMethod run() {
		//@CobolSourceFile("Bubble-sort.cob",62,12) 
		//Perform varying temp1 from 1 by 1 until temp1 > count1		
		//...end-perform
                    long start=System.currentTimeMillis();
		for(setTemp1(1);getTemp1() <= getCount1();setTemp1(getTemp1()+1)) {
			//@CobolSourceFile("Bubble-sort.cob",63,16) 
			//COMPUTE temp3=temp1 + 1			
			setTemp3(getTemp1()+1);
			//@CobolSourceFile("Bubble-sort.cob",64,16) 
			//perform varying temp2 from temp3 by 1			
			//   until temp2>count1			
			//...end-perform			
			for(setTemp2(getTemp3());getTemp2() <= getCount1();setTemp2(getTemp2()+1)) {
				//@CobolSourceFile("Bubble-sort.cob",66,24) 
				//if ELEMENT1 of data1 (temp2) less than				
				//    ELEMENT1 of data1 (temp1) then				
				//...end-if				
				if(data1.getElement1((int)getTemp2()) < data1.getElement1((int)getTemp1())) {
					//@CobolSourceFile("Bubble-sort.cob",68,28) 
					//MOVE ELEMENT of data1 (temp2) TO ELEMENT					
					//   of temp-element					
					tempElement.setElement(data1.getElement((int)getTemp2()));
					//@CobolSourceFile("Bubble-sort.cob",70,28) 
					//MOVE ELEMENT of data1 (temp1) TO					
					//   ELEMENT of data1 (temp2)					
					data1.setElement(data1.getElement((int)getTemp1()),(int)getTemp2());
					//@CobolSourceFile("Bubble-sort.cob",72,28) 
					//MOVE ELEMENT of temp-element TO					
					//   ELEMENT of data1 (temp1)					
					data1.setElement(tempElement.getElement(),(int)getTemp1());
				}
			}
                         if(getTemp1()%1000==0) {
                        System.out.println(getTemp1()+"="+(System.currentTimeMillis()-start));
                        start=System.currentTimeMillis();
                        }
		}
		//@CobolSourceFile("Bubble-sort.cob",77,12) 
		//COMPUTE TEMP1=1		
		setTemp1(1);
		//@CobolSourceFile("Bubble-sort.cob",78,12) 
		//Display "The sorted data is " count1		
		//         "number of elements"		
		System.out.println("The sorted data is "+count1Fmt_.format(getCount1())+"number of elements");
		//@CobolSourceFile("Bubble-sort.cob",80,12) 
		//Display '(' with no advancing		
		System.out.print("(");
		//@CobolSourceFile("Bubble-sort.cob",81,12) 
		//Perform count1 times		
		//...END-PERFORM		
		for(int i2=0;i2<getCount1();++i2) {
			//@CobolSourceFile("Bubble-sort.cob",82,20) 
			//Display "("  ELEMENT1 of data1 (temp1)			
			//    with no advancing			
			//System.out.print("("+Data11.element1Fmt_.format(data1.getElement1((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",84,20) 
			//Display ","  ELEMENT2 of data1 (temp1)			
			//    with no advancing			
			//System.out.print(","+Data11.element2Fmt_.format(data1.getElement2((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",86,20) 
			//Display ","  ELEMENT3 of data1 (temp1)			
			//    with no advancing			
			//System.out.print(","+Data11.element3Fmt_.format(data1.getElement3((int)getTemp1())));
			//@CobolSourceFile("Bubble-sort.cob",88,20) 
			//if temp1 not = count1			
			if(getTemp1() != getCount1()) {
				//@CobolSourceFile("Bubble-sort.cob",89,23) 
				//display '),'				
				//System.out.println("),");
				//@CobolSourceFile("Bubble-sort.cob",90,20) 
				//ADD 1 TO TEMP1				
				setTemp1(1+getTemp1());
			}
		}
		//@CobolSourceFile("Bubble-sort.cob",92,12) 
		//Display '))'		
		System.out.println("))");
		return doCobolExit();
		}
	};
	private BubbleSort1() {
		super(0,new CobolBytes(32));
		setCount1(1);
		setTemp1(2);
		setTemp2(3);
		setTemp3(4);
	}
}
