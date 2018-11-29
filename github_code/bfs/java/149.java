import javax.swing.*;
import java.io.File;
import java.util.Scanner;

/**
 * Created by Weston Ford on 2/12/2016.
 *
 *
 * HEY! LOOK! READ THIS!
 *
 * One of the things I've never been able to figure out
 * is how to easily take a file as user input.
 *
 * The two ways to have a file read by this program are:
 *
 * 1) Paste the XML directly into test.txt (replacing the current contents).
 *
 * 2) Change String sourcePath in the code below to the filepath of the desired file.
 *
 * Unfortunately I haven't tested this program on anything other than the sample XML
 * provided in the homework PDF so I don't know whether or not the program will properly
 * interpret all input of the appropriate format or if the tree drawing kit fails on some
 * types of trees.
 *
 * Everything here was created by me. The framework was based upon another assignment
 * I had completed for Dr. Gayler's Concepts of Programming Languages course
 * (an interpreter for a limited version of the language Lua which I had written in Java).
 *
 * The only outside resources referenced are forum and blog posts pertaining to the syntax for
 * Java 2D graphics and RegEx.
 *
 *
 */


public class Interpreter {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        JFrame f = new JFrame();
        String search = "";
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Enter file path to text file containing xml code
        String sourcePath = "C:\\Users\\Bruce Houdini\\IdeaProjects\\XMLDecisionTree\\src\\test";

        System.out.println("For Breadth-First-Search type \"BFS\". For Depth-First-Search type \"DFS\". Type end program type \"quit\".");
        String control = in.nextLine();

        while (!control.equals("quit")) {

            Parser tree = new Parser(new File(sourcePath));
            tree.parse();

            int screenw, screenh;
            int recw, rech;
            screenw = 1200;
            screenh = 900;
            recw = 100;
            rech = 40;
            TreeVisualizer viz = new TreeVisualizer(screenw, screenh, recw, rech);


            viz.buildNodeList(tree.getRoot());
            viz.generateOffsets();

            //I decided to use the system clock to determine the "random" component of the searches.
            //But for some reason the results don't seem to be as "random" as they should be.
            if(control.equals("BFS")) {
                System.out.println("Behavior: ");
                search = in.nextLine();
                System.out.println("Searching for: " + search);
                tree.BFS(tree.getRoot(), search);
            }
            else if(control.equals("DFS")) {
                System.out.println("Behavior: ");
                search = in.nextLine();
                System.out.println("Searching for: " + search);
                tree.DFS(tree.getRoot(), search);
            }
            else
                System.out.println("Invalid Selection: BFS, DFS, quit");


            //f.getContentPane().setBackground(new Color(39, 40, 34));
            //f.setOpacity(0.5f);
            f.getContentPane().add(viz);
            f.setSize(viz.getPanelWidth(), viz.getPanelHeight());
            f.setLocationRelativeTo(null);
            f.setVisible(true);

            System.out.println("For Breadth-First-Search type \"BFS\". For Depth-First-Search type \"DFS\". Type end program type \"quit\".");
            control = in.nextLine();
        }

    }
}
