package hw4;

public class Main {

	public static void main(String[] args) {
		
		Frame Throwable = new Frame("Throwable");
		Frame Exception = new Frame("Exception", Throwable);
		Frame Error = new Frame("Error", Throwable);
		Frame RuntimeException = new Frame("RuntimeException", Exception);
		Frame IOException = new Frame("IOException", Exception);
		Frame AWTError = new Frame("AWTError", Error);
		Frame ThreadDeath = new Frame("ThreadDeath", Error);
		Frame OutOfMemoryError = new Frame("OutOfMemoryError", Error);
		Frame ArrayIndexOutOfBoundsException = new Frame("ArrayIndexOutOfBoundsException", RuntimeException);
		Frame InputMismatchException = new Frame("InputMismatchException", RuntimeException);
		Frame ClassCastException = new Frame("ClassCastException", RuntimeException);
		Frame NullPointerException = new Frame("NullPointerException", RuntimeException);
		Frame ArithmeticException = new Frame("ArithmeticException", RuntimeException);

		TopologicalSort TP = new TopologicalSort(ClassCastException);
		System.out.println("Output for Test Data #1 & Leaf: ClassCastException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(ArrayIndexOutOfBoundsException);
		System.out.println("Output for Test Data #1 & Leaf: ArrayIndexOutOfBoundsException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(NullPointerException);
		System.out.println("Output for Test Data #1 & Leaf: NullPointerException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(InputMismatchException);
		System.out.println("Output for Test Data #1 & Leaf: InputMismatchException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(ArithmeticException);
		System.out.println("Output for Test Data #1 & Leaf: ArithmeticException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(IOException);
		System.out.println("Output for Test Data #1 & Leaf: IOException");

		for(Frame F : TP.precedenceList)
			System.out.println(F);

		TP = new TopologicalSort(AWTError);
		System.out.println("Output for Test Data #1 & Leaf: AWTError");

		for(Frame F : TP.precedenceList)
			System.out.println(F);

		TP = new TopologicalSort(ThreadDeath);
		System.out.println("Output for Test Data #1 & Leaf: ThreadDeath");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		TP = new TopologicalSort(OutOfMemoryError);
		System.out.println("Output for Test Data #1 & Leaf: OutOfMemoryError");

		for(Frame F : TP.precedenceList)
			System.out.println(F);
		
		System.out.println("-------------------");
		
		Frame ios = new Frame("ios");
		Frame istream = new Frame("istream", ios);
		Frame ostream = new Frame("ostream", ios);
		Frame ifstream = new Frame("ifstream", istream);
		Frame iostream = new Frame("iostream", istream, ostream);
		Frame ofstream = new Frame("ofstream", ostream);
		Frame fstream = new Frame("fstream", iostream);
		
		TopologicalSort TP2 = new TopologicalSort(ifstream);
		System.out.println("Output for Test Data #2 & Leaf: ifstream");

		for(Frame F : TP2.precedenceList)
			System.out.println(F);
		
		TP2 = new TopologicalSort(ofstream);
		System.out.println("Output for Test Data #2 & Leaf: ofstream");

		for(Frame F : TP2.precedenceList)
			System.out.println(F);
		
		TP2 = new TopologicalSort(fstream);
		System.out.println("Output for Test Data #2 & Leaf: fstream");

		for(Frame F : TP2.precedenceList)
			System.out.println(F);
		
		System.out.println("-------------------");

		Frame Employee = new Frame("Employee");
		Frame TemporaryEmployee = new Frame("TemporaryEmployee", Employee);
		Frame Consultant = new Frame("Consultant", TemporaryEmployee);
		Frame Manager = new Frame("Manager", Employee);
		Frame ConsultantManager = new Frame("ConsultantManager", Consultant, Manager);
		Frame PermanentEmployee = new Frame("PermanentEmployee", Employee);		
		Frame PermanentManager = new Frame("PermanentManager", Manager, PermanentEmployee);
		Frame Director = new Frame("Director", Manager);
		
		TopologicalSort TP3 = new TopologicalSort(ConsultantManager);
		System.out.println("Output for Test Data #3 & Leaf: ConsultantManager");

		for(Frame F : TP3.precedenceList)
			System.out.println(F);
		
		TP3 = new TopologicalSort(PermanentManager);
		System.out.println("Output for Test Data #3 & Leaf: PermanentManager");

		for(Frame F : TP3.precedenceList)
			System.out.println(F);
		
		TP3 = new TopologicalSort(Director);
		System.out.println("Output for Test Data #3 & Leaf: Director");

		for(Frame F : TP3.precedenceList)
			System.out.println(F);
		
	}

}
