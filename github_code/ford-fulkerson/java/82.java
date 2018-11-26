package max_cut;

import funcat.edge;
import funcat.vertex;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

import FordFulkerson.FlowEdge;
import FordFulkerson.FlowNetwork;
import FordFulkerson.FordFulkerson;
//import max_cut.network;

public class Fordfulkerson {
	
	public ArrayList<vertex> min_cut(ArrayList<link> adj_list,ArrayList<link> org_adj_list)
	{
		//Stack<vertex> tmp=find_path(adj_list);
		 
		loop: while(true)
		{
			Stack<vertex> tmp=find_path(adj_list);
			if(tmp.empty())
			{
				//System.out.println("No path left!");
				break loop;
			}
			//System.out.println("Path length "+tmp.size()); 
			double r=compute_R(adj_list,tmp);
			augment(adj_list,org_adj_list,tmp,r);
		}
		return find_cut(adj_list);
	}
	
	public ArrayList<vertex> find_cut(ArrayList<link> adj_list)
	{
		Stack<vertex> st = new Stack<vertex>();
		ArrayList<vertex> reachable=new ArrayList<vertex>();
		st.add(adj_list.get(0).v);
		HashMap<vertex,vertex> visited=new HashMap<vertex,vertex>();
		visited.put(adj_list.get(0).v, null);
		 while(!st.empty())
		{
			vertex vtmp=st.pop();
			//System.out.println("Popped: "+vtmp.name);
			link ltmp=adj_list.get(vtmp.num);
			reachable.add(vtmp);
			for(edge etmp: ltmp.elist)
			{
				if(!visited.containsKey(etmp.v2)&&etmp.c>0)
				{
					st.add(etmp.v2);
					visited.put(etmp.v2,vtmp);
				}
			}
		}
		return reachable;
	}
	
	public Stack<vertex> find_path(ArrayList<link> adj_list)
	{
		Stack<vertex> tmp=new Stack<vertex>();
		Queue<vertex> q = new LinkedList<vertex>();
		q.add(adj_list.get(0).v);
		HashMap<vertex,vertex> visited=new HashMap<vertex,vertex>();
		visited.put(adj_list.get(0).v, null);
		main_loop: while(!q.isEmpty())
		{
			vertex vtmp=q.remove();
			//System.out.println(" vertex: "+vtmp.name);
			if(vtmp.num==1)
			{
				vertex v=vtmp;
				while(v!=null)
				{
					tmp.add(v);
					v=visited.get(v);
				}
				break main_loop;
			}
			link ltmp=adj_list.get(vtmp.num);
			loop: for(edge etmp: ltmp.elist)
			{
				if(!visited.containsKey(etmp.v2)&&etmp.c>0)
				{
					q.add(etmp.v2);
					visited.put(etmp.v2,vtmp);
					break loop;
				}
			}
		}
		return tmp;
	}

	public void augment(ArrayList<link> adj_list,ArrayList<link> org_adj_list,Stack<vertex> list,double r)
	{
		vertex v1=adj_list.get(0).v;
		// System.out.println("Augment value: "+r);
		 while(!list.empty())
		 {
			 vertex v2=list.pop();
			// System.out.println("\nAugment:: "+(v1.name)+" to "+(v2.name));
			 boolean flag=true;
			 edge eorg=get_edge(org_adj_list,v1,v2);
			 if(eorg!=null)
			 {
				 flag=true;
			 }
			 //System.out.println("  Original: v1- "+v1.num+" v2- "+v2.num);
			 edge e1=get_edge(adj_list,v1,v2);
			 edge e2=get_edge(adj_list,v2,v1);
			 //System.out.println("\nFound: ");
			// System.out.println("Forward:: "+(e1.v1.name)+" to "+(e1.v2.name)+" l: "+e1.l+" c: "+e1.c);
			// System.out.println("Backward:: "+(e2.v1.name)+" to "+(e2.v2.name)+" l: "+e2.l+" c: "+e2.c);
			 if(flag)
			 {
				 e1.c=e1.c-r;
				 e2.c=e2.c+r;
			 }
			 else if(!flag&&(e2.c-r)>=0)
			 {
				 e1.c=e1.c+r;
				 e2.c=e2.c-r;
			 }
			 if((e2.c-r)<0)
			 {
				 //System.out.println("Error:: "+(e1.v1.name)+" to "+(e1.v2.name)+" l: "+e1.l+" c: "+e1.c);
				 //System.out.println("Error:: "+(e2.v1.name)+" to "+(e2.v2.name)+" l: "+e2.l+" c: "+e2.c);
				 System.out.println("Error");
				 System.exit(0);
			 }
			 else
			 {
				 
			 }
			 v1=v2;
		 }
	}
	
	public double compute_R(ArrayList<link> adj_list,Stack<vertex> list)
	{
		Stack<vertex> tmp=new Stack<vertex>();
		vertex v1=list.pop();
		double min=Integer.MAX_VALUE;
		 while(!list.empty())
		 {
			 vertex v2=list.pop();
			 tmp.add(v2);
			 //System.out.println("Path:: "+(v1.name)+" to "+(v2.name));
			 edge e=get_edge(adj_list,v1,v2);
			 if(e.c<min)
			 {
				 min=e.c;
			 }
			 v1=v2;
		 }
		while(!tmp.empty())
		{
			list.push(tmp.pop());
		}
		return min;
	}
	
	public edge get_edge(ArrayList<link> adj_list,vertex v1,vertex v2)
	{
		ArrayList<edge> elist=adj_list.get(v1.num).elist;
		for(edge e: elist)
		{
			if(e.v1.num==v1.num&&e.v2.num==v2.num)
			{
				return e;
			}
		}
		return null;
	}
	
	public flow get_flow(ArrayList<link> adj_list,vertex v1,vertex v2)
	{
		ArrayList<flow> flist=adj_list.get(v1.num).flist;
		for(flow f: flist)
		{
			if(f.v1.num==v1.num&&f.v2.num==v2.num)
			{
				return f;
			}
		}
		return null;
	}
	
	public ArrayList<vertex> construct_r_graph(ArrayList<vertex> v_list,ArrayList<edge> e_list)
	{
		int curr=0,prev=-1;
		ArrayList<link> adj_list=new ArrayList<link>();
		ArrayList<link> org_adj_list=new ArrayList<link>();
		ArrayList<link> org_adj_list_incoming=new ArrayList<link>();
		ArrayList<link> org_adj_list_outgoing=new ArrayList<link>();
		ArrayList<link> flow_list=new ArrayList<link>();
		for(vertex v : v_list)
		{
			if(curr!=prev+1)
			{
				System.out.println("Error");
				System.exit(0);
			}
			if(v.num>0)
			{
				prev=curr;
				curr=v.num;
			}
			link ltmp1=new link(v);
			link ltmp2=new link(v);
			link ltmp3=new link(v);
			link ltmp4=new link(v);
			link ltmp5=new link(v);
			adj_list.add(ltmp1);
			org_adj_list.add(ltmp2);
			org_adj_list_incoming.add(ltmp3);
			org_adj_list_outgoing.add(ltmp4);
			flow_list.add(ltmp5);
		}
		for(edge e: e_list)
		{
			org_adj_list.get(e.v1.num).elist.add(e);
			org_adj_list_outgoing.get(e.v1.num).elist.add(e);
			org_adj_list_incoming.get(e.v2.num).elist.add(e);
		}
		// create new source and destination
		vertex ns=new vertex("new_source",1,0);
		vertex nt=new vertex("new_destination",1,1);
		ArrayList<vertex> nv_list=new ArrayList<vertex>();
		ArrayList<edge> ne_list=new ArrayList<edge>();
		nv_list.add(ns);
		nv_list.add(nt);
		for(vertex v: v_list)
		{
			vertex nv=new vertex("",1,v.num+2);
			nv_list.add(nv);
			double c=0;
			for(edge e: org_adj_list_incoming.get(v.num).elist)
			{
				c+=e.l;
			}
			ne_list.add(new edge(ns,nv,0,c));
			c=0;
			for(edge e: org_adj_list_outgoing.get(v.num).elist)
			{
				c+=e.l;
			}
			ne_list.add(new edge(nv,nt,0,c));
		}
		/*System.out.println("New vertices: ");
		for(vertex v: nv_list)
		{
			System.out.println(v.num);
		}*/
		
		for(edge e: e_list)
		{
			vertex v1=nv_list.get(e.v1.num+2);
			vertex v2=nv_list.get(e.v2.num+2);
			ne_list.add(new edge(v1,v2,0,e.c-e.l));
		}
		ne_list.add(new edge(nv_list.get(2),nv_list.get(3),0,9999999));
		ne_list.add(new edge(nv_list.get(3),nv_list.get(2),0,9999999));
		/*System.out.println("New edges: ");
		for(edge e: ne_list)
		{
			System.out.println(" From: "+e.v1.num+" to "+e.v2.num+" l: "+e.l+" c: "+e.c);
		}*/
		//System.out.println("Elist size: "+ne_list.size());
		FlowNetwork G = new FlowNetwork(nv_list, ne_list);
		FordFulkerson maxflow = new FordFulkerson(G, 0, 1);
		//System.out.println("Initial Flow: ");
		for (int v = 0; v < G.V(); v++) {
			for (FlowEdge e : G.adj(v)) {
				if ((v == e.from()) /*&& e.flow() > 0*/)
				{
					//System.out.println("From: "+(e.from())+" to "+(e.to())+" flow: "+e.flow());
					if(e.from()>1&&e.to()>1)
					{
						vertex v1=adj_list.get(e.from()-2).v;
						vertex v2=adj_list.get(e.to()-2).v;
						edge ex=get_edge(org_adj_list,org_adj_list.get(e.from()-2).v,org_adj_list.get(e.to()-2).v);
						if(ex!=null)
						{
							flow f=new flow(v1,v2,e.flow()+ex.l);
							flow_list.get(v1.num).flist.add(f);
						}
					}
				}
					//StdOut.println("   " + e);
					//dfsg[e.from()][e.to()]=e.capacity();
			}
		}
		//System.exit(0);
		 //System.out.println("Initial flow -- ");
		// ---- 
		for(edge e: e_list)
		{
			flow f=get_flow(flow_list,e.v1,e.v2);
			//System.out.println("From: "+(f.v1.name)+" to "+(f.v2.name)+":-- "+e.l+", "+e.c+", "+f.f+"  Also: "+e.v1.num+" to: "+e.v2.num);
			edge e1t=new edge(e.v1,e.v2,0,e.c-f.f);
			edge e2t=new edge(e.v2,e.v1,0,f.f-e.l);
			adj_list.get(e.v1.num).elist.add(e1t);
			adj_list.get(e.v2.num).elist.add(e2t);
		}
		//System.exit(0);
		//System.out.println("Finding Cut -->");
		return min_cut(adj_list,org_adj_list);
	}
	
	public static void main(String[] args)
	{
		Fordfulkerson f=new Fordfulkerson(); 
		vertex[] v=new vertex[6];
		/*for(int i=0;i<6;i++)
		{
			v[i]=new vertex("",1,i);
		}*/
		v[0]=new vertex("s",1,0);
		v[1]=new vertex("t",1,1);
		v[2]=new vertex("w",1,2);
		v[3]=new vertex("x",1,3);
		v[4]=new vertex("y",1,4);
		v[5]=new vertex("z",1,5);
		edge[] e=new edge[8];
		e[0]=new edge(v[1],v[2],1,3);
		e[1]=new edge(v[1],v[4],0,10);
		e[2]=new edge(v[2],v[3],5,7);
		e[3]=new edge(v[4],v[5],2,8);
		e[4]=new edge(v[3],v[0],1,5);
		e[5]=new edge(v[5],v[0],1,6);
		e[6]=new edge(v[3],v[4],1,3);
		e[7]=new edge(v[5],v[2],2,4);
		ArrayList<vertex> vlist=new ArrayList<vertex>();
		ArrayList<edge> elist=new ArrayList<edge>();
		for(vertex vi: v)
		{
			vlist.add(vi);
		}
		Collections.swap(vlist, 0, 1);
		vlist.get(0).num=0;
		vlist.get(1).num=1;
		vlist.get(0).name="s";
		vlist.get(1).name="t";
		for(edge ei: e)
		{
			elist.add(ei);
		}
		
		for(vertex vi : f.construct_r_graph(vlist,elist))
		{
			System.out.println(vi.name);
		}
	}

}

class link {
	vertex v;
	ArrayList<edge> elist=new ArrayList<edge>();
	ArrayList<flow> flist=new ArrayList<flow>();
	public link(vertex v)
	{
		this.v=v;
	}
}

class flow {
	vertex v1,v2;
	double f=0;
	public flow(vertex v1,vertex v2,double f)
	{
		this.v1=v1;
		this.v2=v2;
		this.f=f;
	}
}