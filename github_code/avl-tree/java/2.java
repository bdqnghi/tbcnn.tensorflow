// Main.java
// Rye Programming Language
// Jacob Paisley
//TODO: Implement lambda expressions
//TODO: Implement functions as a first class object
//TODO: Implement AVL-tree dictionary
//TODO: Implement the Sieve of Eratosthenes
public class Main {
    protected static int lineNumber = 1;
    protected static void runFile(String filename) {
        Parser p = new Parser(filename);
        try {
          Lexeme lexTree = p.parseRecursive();
          Evaluator e = new Evaluator(lexTree);
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    private static void printFile(String filename) {
      FileScanner f = new FileScanner(filename);
    }

    public static void main(String[] args) {
        String filename = args[0];
        String flag = "-x";

        if(args.length == 2){
          flag = args[1];
        }

        if(flag.contains("r")){
          printFile(filename);
        }

        if(flag.contains("x")){
          runFile(filename);
        }
    }
}
