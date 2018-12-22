import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Vector;

import com.interval.IntervalNode;
import com.interval.IntervalTree;
import com.lastzout.LastzOutputParser;
import com.redblack.*;

class RedBlackMain {
	
	private RedBlackTree redBlackTree;
	private IntervalTree intervalTree;
	
	public RedBlackMain() {
		redBlackTree = new RedBlackTree();
		intervalTree = new IntervalTree();
	}
	
	public void insertNewRBNode(int key) {
		redBlackTree.insert(new RedBlackNode(key));
	}
	
	public void insertNewIntvNode(int low, int high) {
		intervalTree.insert(new IntervalNode(low, high));
	}
	
	//TODO: print inorder traversal of tree
	public void rbInorder() {
		redBlackTree.inorderTreeWalk(redBlackTree.getRoot());
	}
	
	public void rbLevelOrder() {
		redBlackTree.levelOrderWalk(redBlackTree.getRoot());
	}
	
	public void intervalInorder() {
		intervalTree.inorderTreeWalk(intervalTree.getRoot());
	}
	
	public void intervalLevelOrder() {
		intervalTree.levelOrderWalk(intervalTree.getRoot());
	}
	
	public void queryOverlapInterval(int low, int high) {
		IntervalNode result = intervalTree.intervalSearch(
													new IntervalNode(low, high));
		if (result != intervalTree.getLeaf()) {
			System.out.println(result.getKey() +"\t"
								+ (result).getHigh() + "\t"
								+ (result).getMaxHi() + "\t"
								+ result.getColor() + "\t"
								+ intervalTree.getBlackHeight(result)
								);
		} else {
			System.out.println("no results found");
		}
	}
	
	public void printMergedWalk() {
		Vector<IntervalNode> mergedWalkNodeStack = new Vector<IntervalNode>();
		intervalTree.inOrderMergedWalk((IntervalNode) intervalTree.getRoot(), 
										mergedWalkNodeStack);
		for (IntervalNode  intervalNode : mergedWalkNodeStack) {
			System.out.println(intervalNode.getLow() + ", " 
								+ intervalNode.getHigh());
		}
	}
	
	public void countGaps(int start, int end) {
		int gapCount = intervalTree.countGaps(start, end);
		System.out.println("Number of gaps: " + gapCount);
	}
	
	public void processFile(String fileName) {
		LastzOutputParser lastzOutputParser = new LastzOutputParser(fileName,
															4, 5, 6, 3	);
		lastzOutputParser.parse();
		//lastzOutputParser.printMergedWalk();
		
		for (String scaffold : lastzOutputParser.getScaffolds()) {
			System.out.print(scaffold+", ");
		}
		System.out.println("");
		System.out.println("ref. scaffold size : "
							+ lastzOutputParser.getReferenceScaffoldSize());
		System.out.println("Gaps count: "+lastzOutputParser.countGaps());
	}
	
	public void processDir(String dirname, String outputFileName) {
		
		File dir = new File(dirname);
		File[] files = dir.listFiles();
		
		LastzOutputParser lastzOutputParser = null;
		
		FileOutputStream fos = null;
		BufferedOutputStream bos = null;
		try {
			fos = new FileOutputStream(outputFileName);
			bos = new BufferedOutputStream(fos);
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		try {
			bos.write(("Name\tSize\tGaps\tPcMapped\tNumScaff\n").getBytes());
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		String tempName = "";
		String size = "";
		String countgaps = "";
		String mappedPc ="";
		String numScaffolds = "";
		
		for (File file : files) {
			if (file.getAbsolutePath().endsWith("fasta.out")) {
				try {
					lastzOutputParser = new LastzOutputParser(file.getCanonicalPath(),
																4, 5, 6, 3	);
					lastzOutputParser.parse();
					
					//bos.write(("\n" + file.getName()).getBytes());
					//bos.write(("\nref. scaffold size : "
					//			+ lastzOutputParser.getReferenceScaffoldSize()).getBytes());
					//bos.write(("\nGaps count: "+lastzOutputParser.countGaps()).getBytes());
					
					tempName = file.getName().substring(0, 8);
					size = lastzOutputParser.getReferenceScaffoldSize() + "";
					countgaps = lastzOutputParser.countGaps() +"";
					
					
					float mapped_pc = 0;
					if (lastzOutputParser.getReferenceScaffoldSize() > 0) {
						mapped_pc  = 100 * (((float)(lastzOutputParser.getReferenceScaffoldSize() 
								- lastzOutputParser.countGaps()) )
								/ lastzOutputParser.getReferenceScaffoldSize());
					}
					
					mappedPc = mapped_pc +"";
					numScaffolds = "" + lastzOutputParser.getScaffolds().size();
					//bos.write(("\nScaffold % mapped: "+ mapped_pc).getBytes());
					//bos.write(("\nScaffold mapped: ").getBytes());
					/*for (String scaffold : lastzOutputParser.getScaffolds()) {
						bos.write((scaffold+", ").getBytes());
					}*/
					//bos.write(("\n*******************************\n").getBytes());
					bos.write((tempName+"\t"+size+"\t"+countgaps+"\t"+mappedPc+
								"\t"+numScaffolds+"\n").getBytes());
					bos.flush();
					/*System.out.println(file.getName());
					System.out.println("ref. scaffold size : "
							+ lastzOutputParser.getReferenceScaffoldSize());
					System.out.println("Gaps count: "+lastzOutputParser.countGaps());
					System.out.print("Scaffold mapped: ");
					for (String scaffold : lastzOutputParser.getScaffolds()) {
						System.out.print(scaffold+", ");
					}
					System.out.println("\n**************************************\n");*/
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				
			}
		}
		
		if (bos != null) {
			try {
				bos.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if (fos != null) {
			try {
				fos.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
	
	public static void main(String[] args) {
		
		RedBlackMain obj = new RedBlackMain();
		
		int sampl[] = {1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		
		for (int i = 0; i < sampl.length; i++) {
			obj.insertNewRBNode(sampl[i]);
		}
		
		//print inorder traversal
		//obj.rbInorder();
		//System.out.println("*********************");
		//obj.rbLevelOrder();
		
		//interval ops
		obj.insertNewIntvNode(1, 5);
		obj.insertNewIntvNode(8, 15);
		obj.insertNewIntvNode(16, 18);
		obj.insertNewIntvNode(16, 29);
		obj.insertNewIntvNode(22, 28);
		obj.insertNewIntvNode(27, 32);
		obj.insertNewIntvNode(36, 39);
		obj.insertNewIntvNode(39, 49);
		System.out.println("**********interval inorder***********");
		obj.intervalInorder();
		System.out.println("**********interval levelorder***********");
		obj.intervalLevelOrder();
		System.out.println("**********query overlap*************");
		obj.queryOverlapInterval(21, 23);
		System.out.println("**********merged walk **********");
		obj.printMergedWalk();
		System.out.println("*********gap counts************");
		obj.countGaps(0, 52);
		System.out.println("******** processfiles ***********");
		//obj.processFile("/Users/mohit/Documents/spring12/hugroup/koronis/tempheadoput.txt");
		//obj.processFile("/Users/mohit/Documents/spring12/hugroup/koronis/2012Mar15Strict500/CGS00001.fasta.out");
		obj.processDir("/Users/mohit/Documents/spring12/hugroup/koronis/2012Mar15Strict500/", 
						"/Users/mohit/Documents/spring12/hugroup/allOutStats.txt");
	}
	
}