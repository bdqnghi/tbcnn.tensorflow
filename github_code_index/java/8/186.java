import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 * This class is used to consume the message that the producer has
 * put into the message queue. The messages that are <= k edit-distance 
 * of the query word are printed back into a file. The other are ignored.
 * @author Devan Shah 100428864
 *
 */
public class LineConsumer implements Runnable
{
    // Declare the outputFileName 
    String outputFileName ;
    
    /**
     * This constructor of the class is used to store the outputFileName 
     * as a global value to be used by run.
     * @param outputFileName
     */
    public LineConsumer ( String outputFileName )
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
            while ( ( ( currentLine = Program.messagingQueue.takeMessage () ) != null ) && !currentLine.isEnd() )
            {
                // Get the line content from the Line objects
                String lineConetent = currentLine.content ;
                
                // Using the line content grab the words from the line and store them in a words array
                String [] words = Util.words ( lineConetent ) ;
                
                // Loop through all the words in the words array to check the edit distance from the query word
                for ( int i = 0; i < words.length; i++ )
                {
                    // Get the edit distance using the query word
                    int editDistance = Util.editDistance ( Program.queryWord,  words[i] ) ;
                    
                    /**
                     *  Only write to the outputFile if the edit distance is less then or equal to the 
                     *  edit distance threshold that is provided by the user.
                     */
                    if ( editDistance <= Program.editDistanceThreshold )
                    {
                        // Make sure that the user knows that the program is consuming stuff
                        System.out.println ( "Line Consumer is Consuming: " + lineConetent ) ;
                        
                        /**
                         *  Write the line to the file since we found a single word that is k 
                         *  edit distance from the query word in the line.
                         */
                        fileWriter.println ( lineConetent ) ;
                        break ; // Stop looking for more words, we only need one.
                    }
                }
            }
            // Close the file 
            fileWriter.close () ;
        }
        // Catch the exception and provide the necessary information to the user.
        catch ( FileNotFoundException e ) { System.out.println ( "File Not Found Exception: " + e.getMessage () ) ; e.printStackTrace() ; }
    }
}
