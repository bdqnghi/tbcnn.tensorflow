package example;


	
	import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Calendar;
import java.util.Comparator;
import java.util.List;

import com.google.code.externalsorting.ExternalSort;

import twitter4j.IDs;
import twitter4j.Paging;
import twitter4j.ResponseList;
import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.User;

	public class BreadthFirstSearch {

		private String previousfilename="";
		private String filename;
		public ConfigurationVariables confv;
		private BufferedWriter bwnodes;
		public File nodestosave;
		public BreadthFirstSearch(){
			
			this.confv= new ConfigurationVariables();
			int maxBreadth=2;
			    try {

			    	TwitterInstanceCreator tic=new TwitterInstanceCreator();
			        Paging paging = new Paging(1, 1);
			        long[] ids;
			        Integer counter=1;
			        
				        File alreadychecked=new File("checked.txt");
				        
				            File queue=new File("queue.txt");
				            File futurequeue=new File("futurequeue.txt");
							FileWriter fw = new FileWriter(futurequeue.getAbsoluteFile(),true);
							BufferedWriter bw = new BufferedWriter(fw);
							
				            this.nodestosave=new File("nodestosave.txt");
							FileWriter fwnodes = new FileWriter(this.nodestosave.getAbsoluteFile(),true);
							this.bwnodes = new BufferedWriter(fwnodes);
							
				        	String line;
			    	    	BufferedReader br = new BufferedReader(new FileReader(queue));
			    	    	int iterationnumber=0;
			    	    	
			        	while((line=br.readLine())!=null)
			        	{
			        		this.updateFileToSave();
			        		System.out.println("Iteration number"+iterationnumber);
					     Twitter twitter = tic.getinstance("user followers");
				        try
				        {ids = twitter.getFollowersIDs(Long.parseLong(line), -1).getIDs();
				       
				        	
				        
				        for(int i=0;i<ids.length;i++)
				        {
				        	
				        	System.out.println(i+"	"+line+"	"+ids[i]);
				        	this.bwnodes.write(line+","+ids[i]+"\n");
				        	bw.write(String.valueOf(ids[i])+"\n");
				        }
				        }catch(TwitterException e){
				        System.out.println(e.getErrorMessage());
				        }
				        bw.flush();
			        	}
			        	
			        	 bw.close();
			        	 fw.close();
			        	 br.close();
			             
			             
			        	System.out.println("Sorting future queue");
			        	sort(futurequeue);
			        	System.out.println("doing the unique thing");
			        	uniqueCheckedAndUnchecked(alreadychecked,futurequeue);
			        	System.out.println("Deleting queue");
			        	queue.delete();
			        	futurequeue.renameTo(new File("queue.txt"));
				        
			            
			        

				            
			        
			    } catch (Exception e) {
			        e.printStackTrace();
			    }
			
		}
		public static void uniqueCheckedAndUnchecked(File checkedlist,File tochecklist)
		{
			try{
				File file = new File("tochecknotinchecked.txt");
				FileWriter fw = new FileWriter(file.getAbsoluteFile(),true);
				File filecheckednew = new File("checkednew.txt");
				FileWriter fwchn = new FileWriter(filecheckednew.getAbsoluteFile(),true);
				BufferedWriter bw = new BufferedWriter(fw);
				BufferedWriter bwchn = new BufferedWriter(fwchn);
	    	BufferedReader br = new BufferedReader(new FileReader(checkedlist));
	    	BufferedReader br2 = new BufferedReader(new FileReader(tochecklist));
	    	String line=br.readLine();
	    	String line2=br2.readLine();
	    	Long n1,n2;
	        while (true) {
	//        System.out.println(line+"   "+line2);
	        if(line==null&&line2==null){break;}
	       if(line==null){
	    	   System.out.println("line null moving line2");
	           n2=Long.parseLong(line2);
	 //   	   System.out.println(n2);
	    	   bw.write(n2+"\n");
	    	   bwchn.write(n2+"\n");
	    	   line2=br2.readLine();
	    	   
	    	   
	    	   }else{
	        n1=Long.parseLong(line);
	        n2=Long.parseLong(line2);

	        if(n1.equals(n2)){
	//	    	   System.out.println("equal, moving both");
	        line=br.readLine();
	        line2=br2.readLine();
	        bwchn.write(n1+"\n");
	        }
	        if(n1<n2)
	        {
//		    	System.out.println("n1 smaller, moving n1");
	        	bwchn.write(n1+"\n");
	        	line=br.readLine();
	        }
	        if(n1>n2){
	//	    	   System.out.println("n2 smaller, moving n2");
	        	bwchn.write(n2+"\n");
	        	System.out.println(n2);
	        	line2=br2.readLine();
	        	bw.write(n2+"\n");
	        }
	    	}
	        }

        	System.out.println("flush");
	        bw.flush();
	        bw.close();

        	System.out.println("flush");
	        bwchn.flush();
	        bwchn.close();

        	System.out.println("close");
	        br.close();
	        br2.close();

        	System.out.println("names");
	        String checkedfilename=checkedlist.getName();
	        String uncheckedfilename=tochecklist.getName();

        	System.out.println("delete");
	        tochecklist.delete();
	        checkedlist.delete();

        	System.out.println("rename");
	        file.renameTo(new File(uncheckedfilename));
	        filecheckednew.renameTo(new File(checkedfilename));

        	System.out.println("done");
			}catch (Exception e){e.printStackTrace();}
	        
		}
public static File sort(File filetosort)
{
	File tempfile=new File("temporalsort");
	/// Declaring external sort variables and comparator
	ExternalSort es=new ExternalSort();
	// TODO Auto-generated method stub
	 Comparator<String> comparator = new Comparator<String>() {
         public int compare(String r1, String r2){
             if(Long.parseLong(r1)>Long.parseLong(r2)){
            	 return(1);
             }else 
        	 return 0;
                 }
         };
         try {
         List<File> listf = es.sortInBatch(filetosort, comparator);
			es.mergeSortedFiles(listf, tempfile, comparator);
			String filename=filetosort.getName();

			filetosort.delete();
			tempfile.renameTo(new File(filename));
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
         return tempfile;
}
public void updateFileToSave(){

	Calendar time = Calendar.getInstance();
        // 	filename=Calendar.YEAR+"-"+Calendar.MONTH+" "+Calendar.DAY_OF_MONTH+" "+Calendar.HOUR_OF_DAY;
            this.filename="NODES_"+time.get(Calendar.YEAR)+"-"+time.get(Calendar.MONTH)+"-"+time.get(Calendar.DATE)+"-"+time.get(Calendar.HOUR_OF_DAY);
            System.out.println("filename changed to "+this.filename);
         
         if(this.filename.equals(this.previousfilename))
         {
        	 System.out.println(this.previousfilename+"filename same to "+this.filename);
         }else{
        	 if(!this.previousfilename.isEmpty()){
        		 System.out.println(this.previousfilename+"Moving "+this.filename);
        		 File filetomove=new File(confv.getTempTweetDir("nodes")+this.previousfilename+".txt");		       	        		 
        		
        		 try {
				this.bwnodes.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        		System.out.println(this.filename+this.previousfilename+" movi!! "+filetomove.length());
        	 filetomove.renameTo(new File(confv.getFinalTweetDir("nodes")+this.previousfilename+".txt"));
   
        	 }
        	 System.out.println(this.filename+this.previousfilename);
        	 this.previousfilename=this.filename;
         }
         System.out.println(confv.getTempTweetDir("nodes")+this.filename);
         this.nodestosave= new File(confv.getTempTweetDir("nodes")+this.filename+".txt");
}
}
