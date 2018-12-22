import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;



public class HeapSort_Sort {
	public static void main(String[] args) throws IOException {
		
		Contact_Class contacts[] = new Contact_Class[]	
		{	
		new Contact_Class(1, "Illinois", "Joe", "Johnson"),
		new Contact_Class(3, "Ohio", "Michael", "Agombar"),
		new Contact_Class(4, "Alabama", "Woody", "Allen"),
		new Contact_Class(5, "Texas", "Tony", "Zelda"),
		new Contact_Class(2, "Peru", "Famous", "James")};
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		//Scanner reader = new Scanner(System.in);  // Reading from System.in
		while (true) {
			Boolean exitLoop = false;
		System.out.println("Sory by last name: [1]");
		System.out.println("Sory by state: [2]");
		System.out.println("Sory by age: [3]");
		System.out.println("Enter an option");
		String n = br.readLine();
		
		switch(n){
		
		case "1":
		case "2": 
		case "3":
			bubbleSort(contacts, n);
			printArray(contacts);
			System.out.println();
			
			break;
		case "0":
			exitLoop = true;
			break;
		default:
			System.out.println("Invalid Input");
		}
		if (exitLoop){
			break;
		}
		}
}
		private static void bubbleSort(Contact_Class contacts[], String n){
			int len = contacts.length;
			Contact_Class temp;
			
			for(int i=0; i < len; i++){
				for(int j=1; j < (len-i); j++){
					if ((n.equals("1") && (contacts[j-1].lastName.compareToIgnoreCase(contacts[j].lastName) >0)) ||
						(n.equals("2") && (contacts[j-1].state.compareToIgnoreCase(contacts[j].state) >0)) || 
						(n.equals("3") && (contacts[j-1].age > contacts[j].age))){
							temp = contacts[j -1];
							contacts[j-1] = contacts[j];
							contacts[j] = temp;
					}
				}
						
			}
	}

		private static void printArray(Contact_Class contacts[]){
			int len = contacts.length;
			for(int i=0; i < len; i++){
				System.out.format("%d, %s, %s, %s \n", contacts[i].age, contacts[i].state, contacts[i].firstName, contacts[i].lastName);
			}
		}
		
	}
