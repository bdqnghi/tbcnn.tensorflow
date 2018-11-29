package ca.uwaterloo.esg.rvtool.SMIRF;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class BFS_Tree {
	
	private ArrayList<Node> vertices_bfs_tree;
	private Node root;
	private Queue<Node> q;
	private int k;
	private boolean no_k_length_flag;
	
	
	BFS_Tree(ArrayList<Node> vertices, Node s,int k)
	{
		vertices_bfs_tree = vertices;
		this.root = s;
		q = new LinkedList<Node>();
		this.k = k;
		no_k_length_flag = true;
		
	}
	
	public ArrayList<Node> getDFSTree()
	{
		Stack<Node> s = new Stack<Node>();
		ArrayList<Node> final_vertices_bfs_tree = new ArrayList<Node>();
		ArrayList<Node> sorted_final_vertices_bfs_tree = new ArrayList<Node>();
		int maximum_D_value=0;

		for(int i=0;i<vertices_bfs_tree.size();i++)
		{
			vertices_bfs_tree.get(i).setColor(0);
			vertices_bfs_tree.get(i).setD(Integer.MAX_VALUE);
			vertices_bfs_tree.get(i).initializeBfsChildren();
		}
		
		root.setD(0);
		s.push(root);

		while(!s.isEmpty()){
			Node tmp = s.pop();
			
			if(tmp.getColor()==0){
				tmp.setColor(1);
				if(tmp.getD()==k){
					tmp.setColor(2);
					continue;
				}
				else{
					s.push(tmp);
				}
				
				for(Node inciV:tmp.getChildren()){
					if(inciV.getColor()==0 || inciV.getColor()==2){
						inciV.setD(tmp.getD()+1);
						tmp.getBfsChildren().add(inciV);
						s.push(inciV);
						if((tmp.getD()+1) > maximum_D_value)
						{
							maximum_D_value = tmp.getD()+1;
						}
					}
				}
			}
			else if(tmp.getColor()==1){
				tmp.setColor(2);
			}
		}
		
		for(int i=0;i<vertices_bfs_tree.size();i++)
		{
			if(vertices_bfs_tree.get(i).getD()<=k)
			{				
					final_vertices_bfs_tree.add(vertices_bfs_tree.get(i));					
			}
		}

		for(int i=0;i<=maximum_D_value;i++)
		{
			for(int j=0;j<final_vertices_bfs_tree.size();j++)
			{
				if(final_vertices_bfs_tree.get(j).getD()==i)
				{
					sorted_final_vertices_bfs_tree.add(final_vertices_bfs_tree.get(j));
				}
			}
		}
		
		return sorted_final_vertices_bfs_tree;
	}
	
	public ArrayList<Node> getBFSTree()
	{
		Node u;
		int maximum_D_value=0;		
		ArrayList<Node> final_vertices_bfs_tree = new ArrayList<Node>();
		ArrayList<Node> sorted_final_vertices_bfs_tree = new ArrayList<Node>();
		Node temp;
		
		for(int i=0;i<vertices_bfs_tree.size();i++)
		{
			vertices_bfs_tree.get(i).setColor(0);
			vertices_bfs_tree.get(i).setD(Integer.MAX_VALUE);
		}
		
		root.setColor(1);
		root.setD(0);
		q.add(root);
		
		while(!q.isEmpty())
		{
		//	System.out.println("Inside BFS:"+counter++);
			u = q.remove();
			u.initializeBfsChildren();
			/*if(u.getD()>=k)
			{
				u.setColor(2);
				no_k_length_flag = false;
				continue;
			}*/
			for(int i=0;i<u.getChildren().size();i++)
			{
				if(u.getChildren().get(i).getColor()==0)
				{
					if(u.getD()==(k-1))
					{
						no_k_length_flag = false;
						u.getChildren().get(i).setColor(2);
						u.getChildren().get(i).setD(u.getD()+1);
						u.getBfsChildren().add(u.getChildren().get(i));
					}
					else
					{
						u.getChildren().get(i).setColor(1);
						u.getChildren().get(i).setD(u.getD()+1);					
						q.add(u.getChildren().get(i));
						u.getBfsChildren().add(u.getChildren().get(i));
						if((u.getD()+1)>maximum_D_value)
						{
							maximum_D_value = u.getD()+1;
						}
					}
				}
			}
			u.setColor(2);
		}
		
		//If the tree does not contain any paths of length greater or equal to k
		/*if(no_k_length_flag)
		{
			return final_vertices_bfs_tree;
		}*/
		
		//Removing Nodes that are not reachable from s
		/*for(int i=0;i<vertices_bfs_tree.size();i++)
		{
			if(vertices_bfs_tree.get(i).getColor()!=0)
			{				
					final_vertices_bfs_tree.add(vertices_bfs_tree.get(i));
			}
		}*/
		for(int i=0;i<vertices_bfs_tree.size();i++)
		{
			if(vertices_bfs_tree.get(i).getD()<=k)
			{				
					final_vertices_bfs_tree.add(vertices_bfs_tree.get(i));					
			}
		}
		
		
		//Adding the children of each to the BFSChildren arraynode for each node
		/*for(int i=0;i<final_vertices_bfs_tree.size();i++)
		{
			for(int j=0;j<final_vertices_bfs_tree.get(i).getChildren().size();j++)
			{
				if(final_vertices_bfs_tree.contains(final_vertices_bfs_tree.get(i).getChildren().get(j)))
				{
					//if((!final_vertices_bfs_tree.get(i).getBfsChildren().contains(final_vertices_bfs_tree.get(i).getChildren().get(j))))
					if(!cycle_detector.contains(final_vertices_bfs_tree.get(i).getChildren().get(j)))
					{
						final_vertices_bfs_tree.get(i).getBfsChildren().add(final_vertices_bfs_tree.get(i).getChildren().get(j));
						cycle_detector.add(final_vertices_bfs_tree.get(i).getChildren().get(j));
					}
				}
			}
		}*/
		
//		for(int i=0;i<final_vertices_bfs_tree.size();i++)
//		{
//			for(int j=0;j<final_vertices_bfs_tree.get(i).getChildren().size();j++)
//			{
//				if(final_vertices_bfs_tree.get(i).getChildren().get(j).getD() == (final_vertices_bfs_tree.get(i).getD()+1))
//				{
//					final_vertices_bfs_tree.get(i).getBfsChildren().add(final_vertices_bfs_tree.get(i).getChildren().get(j));
//				}
//			}
//		}
	
		StringBuffer temp_buffer;
		FileWriter writer;
		
		/*temp_buffer = new StringBuffer();
		temp_buffer.append("digraph{\n");
		//System.out.println("New Tree Before Removing Artificial Nodes");
		for(int j=0;j<final_vertices_bfs_tree.size();j++)
		{
			//System.out.println(vertices_bfs.get(j).toString());
			//System.out.println("BFS Children");
			for(int l=0;l<final_vertices_bfs_tree.get(j).getBfsChildren().size();l++)
			{
				if(!final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getArtificial())
					temp_buffer.append(final_vertices_bfs_tree.get(j).getID() + "->" + final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getID()+";\n");
				else
					temp_buffer.append(final_vertices_bfs_tree.get(j).getID() + "->" + final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getID()+" [color=red,style=dotted];\n");
				//System.out.println(vertices_bfs.get(j).getBfsChildren().get(l).toString());
				//System.out.println("^^^^^^^^^^^^^^^");
			}
		}
		temp_buffer.append("}\n");
		try {
			writer = new FileWriter(new File(s.getID()+"_insidebfs_before.dot"));
			writer.write(temp_buffer.toString());
			writer.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
	//	System.out.println("Crossed the Dot production");
		
		//Removing all paths that are less than length "sampling_period"
		/*	for(int i=0;i<final_vertices_bfs_tree.size();i++)
			{
				if(final_vertices_bfs_tree.get(i).getBfsChildren().isEmpty() && final_vertices_bfs_tree.get(i).getD()!=k)
				{
					final_vertices_bfs_tree.remove(i);
					i=0;
					for(int j=0;j<final_vertices_bfs_tree.size();j++)
					{
						for(int l=0;l<final_vertices_bfs_tree.get(j).getBfsChildren().size();l++)
						{
							if(!final_vertices_bfs_tree.contains(final_vertices_bfs_tree.get(j).getBfsChildren().get(l)))
							{
								final_vertices_bfs_tree.get(j).getBfsChildren().remove(l);
								l=0;
							}
						}
					}
					
				}
			}*/
		
			/*temp_buffer = new StringBuffer();
			temp_buffer.append("digraph{\n");
			//System.out.println("New Tree Before Removing Artificial Nodes");
			for(int j=0;j<final_vertices_bfs_tree.size();j++)
			{
				//System.out.println(vertices_bfs.get(j).toString());
				//System.out.println("BFS Children");
				for(int l=0;l<final_vertices_bfs_tree.get(j).getBfsChildren().size();l++)
				{
					if(!final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getArtificial())
						temp_buffer.append(final_vertices_bfs_tree.get(j).getID() + "->" + final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getID()+"\n");
					else
						temp_buffer.append(final_vertices_bfs_tree.get(j).getID() + "->" + final_vertices_bfs_tree.get(j).getBfsChildren().get(l).getID()+" [color=red,style=dotted];\n");
					//System.out.println(vertices_bfs.get(j).getBfsChildren().get(l).toString());
					//System.out.println("^^^^^^^^^^^^^^^");
				}
			}
			temp_buffer.append("}\n");
			try {
				writer = new FileWriter(new File(s.getID()+"_after.dot"));
				writer.write(temp_buffer.toString());
				writer.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
			
		//Sorting according to distance from the root "s"
	//	System.out.println("Before sorting");
		//counter=0;
		for(int i=0;i<=maximum_D_value;i++)
		{
			//System.out.println("Inside sorting"+i);
			for(int j=0;j<final_vertices_bfs_tree.size();j++)
			{
				if(final_vertices_bfs_tree.get(j).getD()==i)
				{
					sorted_final_vertices_bfs_tree.add(final_vertices_bfs_tree.get(j));
				}
			}
		}
		//System.out.println("End");
		
		return sorted_final_vertices_bfs_tree;
	}
	
}
