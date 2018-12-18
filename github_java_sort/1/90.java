




class Experiment_up {

    protected static String program = "Experiment_up";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	
        if (args.length != 1) {
	    System.err.println(err + "Exactly one parameter is required, the number N of experiments.\n");
	    return;
	}




	int N = (Integer.valueOf(args[0]) ).intValue();
	System.out.println("\n#  Insertion-sort on sorted lists\n");

	System.out.println("  size executionTime\n");
	for (int i = 0; i <= N; i++) {
	    long[] A = Array_Generators.sorted_up(i);
	    Insertion_Sort.insertion_sort(A);
	}

    }

}






class Experiment_down {

    protected static String program = "Experiment_down";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	
        if (args.length != 1) {
	    System.err.println(err + "Exactly one parameter is required, the number N of experiments.\n");
	    return;
	}

	int N = (Integer.valueOf(args[0]) ).intValue();
	System.out.println("\n#  Insertion-sort on reverse sorted lists\n");

	System.out.println("  size executionTime\n");
	for (int i = 0; i <= N; i++) {
	    long[] A = Array_Generators.sorted_down(i);
	    Insertion_Sort.insertion_sort(A);
	}

    }

}






class Experiment_rand {

    protected static String program = "Experiment_rand";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	
        if (args.length != 1) {
	    System.err.println(err + "Exactly one parameter is required, the number N of experiments.\n");
	    return;
	}

	int N = (Integer.valueOf(args[0]) ).intValue();
	System.out.println("\n#  Insertion-sort on random lists\n");

	System.out.println("  size executionTime\n");
	for (int i = 0; i <= N; i++) {
	    long[] A = Array_Generators.sorted_rand(i);
	    Insertion_Sort.insertion_sort(A);
	}

    }

}



