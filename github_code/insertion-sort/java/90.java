// Arnold Beckmann, 19.10.2010 (Swansea)

/*
  File:  200910/Week01/Experiment.java
  Descr: Experiments with sorting algorithms on sorted inputs

  "Experiment_up N" calls the sorting algorithm N times with upwards
  sorted inputs; the statistics are output to standard output.
*/


class Experiment_up {

    protected static String program = "Experiment_up";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	//  this program requires one argument on the command line  
        if (args.length != 1) {
	    System.err.println(err + "Exactly one parameter is required, the number N of experiments.\n");
	    return;
	}

//	long end = System.currentTimeMillis()+2000;
//	while (System.currentTimeMillis() < end) {};

	int N = (Integer.valueOf(args[0]) ).intValue();
	System.out.println("\n#  Insertion-sort on sorted lists\n");

	System.out.println("  size executionTime\n");
	for (int i = 0; i <= N; i++) {
	    long[] A = Array_Generators.sorted_up(i);
	    Insertion_Sort.insertion_sort(A);
	}

    }

}



/*
  "Experiment_down N" calls the sorting algorithm N times with downwards
  sorted inputs; the statistics are output to standard output.
*/


class Experiment_down {

    protected static String program = "Experiment_down";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	//  this program requires one argument on the command line  
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



/*
  "Experiment_rand N" calls the sorting algorithm N times with randomly
  sorted inputs; the statistics are output to standard output.
*/


class Experiment_rand {

    protected static String program = "Experiment_rand";
    protected static String err = "ERROR[" + program + "]: ";

    public static void main(String[] args) {

	//  this program requires one argument on the command line  
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



/*

class ExecutionTimer {
  private static long start;
  private static long end;

  public static void start() {
    start = System.nanoTime();
  }

  public static void end() {
    end = System.nanoTime();
  }

  public static long duration(){
    return (end-start);
  }

  public static void reset() {
    start = 0;  
    end   = 0;
  }

}

*/