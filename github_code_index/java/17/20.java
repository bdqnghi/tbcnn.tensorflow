import java.util.Scanner;
import java.util.Vector;

public class ConsoleControl 
{
	public static void welcome()
	{
		final int RB_TREE = 1;
		final int P_TREE = 2;
		final int ROBDD = 3;
		
		int intTree;
		int intInput;
		
		int intInputCharacter;
		int strInputCharacter;
		
		
		
		boolean boolInputComplete = false;
		boolean boolOutputComplete = false;
		
		boolean boolInput = false;
		boolean boolDelete = false;
		
		
		Scanner scanner = new Scanner(System.in);
	    System.out.println("Bitte Struktur ausw�hlen: ");
	    System.out.print("Red-Black-Tree: 1 , Patricia-Tree: 2 , ROBDD: 3 :");
	    
	    intTree = Integer.parseInt(scanner.nextLine());
	   
	    if ( intTree == RB_TREE  )
	    {
	    	Vector<Integer> vecIntInput = new Vector<>(1, 1);
	    	
	    	RedBlackTree<Integer, Integer> RBTree = new RedBlackTree<>();
	    	
	    	while (!boolInputComplete)
	    	{
	    		 System.out.println("Einf�gen: 1 , L�schen: 2 , Zufallszahlen(1-1000): 3  , Ausgabe: 0 : ");
	    		 intInput = Integer.parseInt(scanner.nextLine());
	    		 
	    		 switch (intInput) 
	    		 {
	    		 	case 1: 
	    		 		System.out.print("Zahl zum Einf�gen:  ");
	    		 		intInput = Integer.parseInt(scanner.nextLine());
	    		 		RBTree.insert(intInput, intInput);
	    		 		break;
					
	    		 	case 2: 
						System.out.print("Zahl zum L�schen:  ");
						intInput = Integer.parseInt(scanner.nextLine());
						RBTree.remove(intInput);
						break;
	    		 	case 3: 
	    		 		
	    		 		System.out.print("Anzahl der Zahlen:  ");
						intInput = Integer.parseInt(scanner.nextLine());
						 
						for (int i = 0 ; i < intInput ; i++ )
						{
							Integer intRandom = (int)(Math.random() * 1000) ;
							vecIntInput.add(intRandom);
							boolInputComplete = true;

						}
						
						break;
	    		 	case 0: 
	    		 		boolInputComplete = true;
						break;
				
	    		 }
	    	 
	    		 
	    	}
	    	System.out.println("Folgende Zahlen sind eingef�gt: ");
	    	for (Integer integer : vecIntInput) 
	    	{
	    		RBTree.insert(integer, integer);
				System.out.print(integer + " ");
			}
	    	System.out.println();
	    	
	    	while (!boolOutputComplete)
	    	{
	    		System.out.println("Ansicht w�hlen: ");
		    	System.out.print("Rot-Schwarz-Baum: 1 , TopDown 234: 2 , Baum modifizieren: 5 , Neustart: 0 : ");
	   		 	intInput = Integer.parseInt(scanner.nextLine());
	   		 	
	   		 	switch (intInput) 
	   		 	{
				 	case 1: 
				 		WriteUDGFile.createUDGFile(RedBlack2UDraw(RBTree), "RBTree", "Keine Ahnung");
				 		System.out.println(RedBlack2UDraw(RBTree));
				 		break;
					
				 	case 2: 
				 		WriteUDGFile.createUDGFile(topDown234ToUDraw(RBTree), "TD234Tree", "Keine Ahnung");
				 		System.out.println(topDown234ToUDraw(RBTree));
						break;
				 	case 5: 
				 		boolInputComplete = true;
						break;
				 	case 0: 
				 		welcome();
						break;
				 	case 9: 
				 		boolOutputComplete = true;
						break;
	   		 	}    		
	    	}
	    	
	    }
	}
	

}
