import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 * This class is used to consume the message that the producer has
 * put into the message queue. The messages that are <= k edit-distance 
 * of the query word are printed back into a file. The other are ignored.
 * @author Devan Shah 100428864
 *
 */
public class ResultConsumer implements Runnable
{
    // Declare the outputFileName 
    String outputFileName ;
    
    /**
     * This constructor of the class is used to store the outputFileName 
     * as a global value to be used by run.
     * @param outputFileName
     */
    public ResultConsumer ( String outputFileName )
    {
        // Store the input on object creation in the global outputFileName variable.
        this.outputFileName = outputFileName ;
    }

    /**
     * This run function overrides the normal run function to perform the 
     * action of iterating through the messaging queue and sifting out
     * the lines that words that are k edit-distance from the query word
     */
    @Override
    public void run ()
    {
        // Declare the line object that will be retrieved from the messaging queue.
        Line currentLine ;
        
        try
        {
            // Construct the writer for the file
            PrintWriter fileWriter = new PrintWriter ( outputFileName ) ;
            
            /**
             *  Loop through the messaging queue until the end of file is found in the queue.
             *  While the loop iterates it pulls each of the Line objects from the messaging
             *  queue and stores it in currentLine, which is later used to check for edit
             *  distance before writing it to the output file.
             */
            while ( ( ( currentLine = Program.resultsMessagingQueue.takeMessage () ) != null ) && !currentLine.isEnd() )
            {
               // Get the line content from the Line objects
               String lineConetent = currentLine.content ;
               
               // Make sure that the user knows that the program is consuming stuff
               System.out.println ( "Result Consumer is Consuming: " + lineConetent ) ;
               
               fileWriter.println ( lineConetent ) ;
            }
            // Close the file 
            fileWriter.close () ;
        }
        // Catch the exception and provide the necessary information to the user.
        catch ( FileNotFoundException e ) { System.out.println ( "File Not Found Exception: " + e.getMessage () ) ; e.printStackTrace() ; }
    }
}
