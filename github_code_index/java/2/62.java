package models;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;

import collections.AVLTree;
import library.Book;
import library.DVD;
import library.Media;

/**
 *	LibraryModel
 *
 * 	A model for storing and accessing library-objects.
 * 	@author Philip Ekholm
 * 	@date 2017-04-01 12:13
 */

public class LibraryModel {
	private AVLTree<String, Media> mediaTree = new AVLTree<String, Media>();
	
	/**
	 *	Default constructor for libraryModel.
	 *
	 *	@param filePathMedia filePath to be entered for Media.txt
	 */
	
	public LibraryModel(String filePathMedia){
		try{
			LibraryModel.readMediaEntries(mediaTree, filePathMedia);
		}
		catch(FileNotFoundException e1){
			System.out.println("The file Media.txt could not be found at: " + filePathMedia);
			e1.printStackTrace();
		}
		catch(IOException e2){
			e2.printStackTrace();
		}
	}
	
	/**
	 * 	Return an iterator instance containing media-objects
	 * 
	 * 	@return iterator instance with media-objects
	 */
	
	public Iterator<Media> iterator(){
		return mediaTree.iterator();
	}
	
	/**
	 *	Check if item can be found in the model.
	 *
	 *	@param key the id of the media.
	 *	@return true if found.
	 */
	
	public boolean contains(String key){
		return mediaTree.contains(key);
	}
	
	/**
	 *	Retrieve a media-item.
	 *
	 *	@param key the id of the media.
	 *	@return the media if found, otherwise null.
	 */
	
	public Media get(String key){
		return mediaTree.get(key);
	}
	
	/**
	* Read all the Media-entries into one AVL-tree structure.
	*/
	
	public static void readMediaEntries(AVLTree<String, Media> tree, String filePath) throws FileNotFoundException, IOException{
		try(BufferedReader br = new BufferedReader(new FileReader(filePath))) {
			String line = br.readLine();
			while (line != null) {
				String[] details = line.split(";");
				
				if(details[0].equals("Dvd")){
					String[] actors = new String[details.length - 4];
					for(int i = 4; i < details.length; i++){
						actors[i - 4] = details[i];
					}
					DVD d = new DVD(details[1],
					Integer.parseInt(details[3]), details[2], actors);
					tree.put(d.getId(), d);
				}
				else if(details[0].equals("Bok")){
					Book b = new Book(details[1], Integer.parseInt(details[4]), details[2], details[3]);
					tree.put(b.getId(), b);
				}
				line = br.readLine();
			}
		}
	}
}








