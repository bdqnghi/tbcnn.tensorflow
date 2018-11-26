package graph;

import datastructure.BinaryHeap;
import datastructure.DisjSets;

// ��С������
public class MinimumSpanningTree extends UndirectedGraph {

	public static void main(String[] args) {
		MinimumSpanningTree demo = new MinimumSpanningTree(7);
		demo.init("resources/UDG.txt", true);
		System.out.println("Prim�㷨������С��������");
		demo.Prim();
		demo.print();
		System.out.println("kruskal�㷨������С��������");
		demo.kruskal();
	}
	
	protected MinimumSpanningTree(int size) {
		super(size);
	}
	
	// �ʺϳ���ͼ������ͼ���ڽӾ����ʾ
	// �˴���Ȼ���ڽӱ�������
	public void Prim() {
		for (int i = 0; i < NUM_VERTICES;i ++) {
			graph[i].known = false;
			graph[i].dist = INFINITY;
			graph[i].path = null;
		}
		
		graph[0].dist = 0;
		
		for ( ; ; ) {
			Vertex v = findSmall();
			if (v.name == null)
				break;
			v.known = true;
			
			for (int i = 0; i < v.adj.size(); i++) {
				Vertex w = v.adj.get(i).next;
				if (!w.known && v.adj.get(i).weight < w.dist) {
					w.dist = v.adj.get(i).weight;
					w.path = v;
				}
			}
			
		}
	}

	// �ʺ�ϡ��ͼ
	public void kruskal() {
		int edgesAccepted = 0;
		DisjSets ds = new DisjSets(NUM_VERTICES);
		BinaryHeap<MyEdge> pq = new BinaryHeap<>(getEdges());
		MyEdge e;
		Vertex u, v;
		MyEdge[] result = new MyEdge[NUM_VERTICES-1];
		
		while (edgesAccepted < NUM_VERTICES - 1) {
			e = pq.deleteMin(); // Edge e = (u,v)
			u = e.cur;
			v = e.next;
			int us = ds.find(u.topNum-1);
			int vs = ds.find(v.topNum-1);
			if (us != vs) {
				result[edgesAccepted++] = e;
				ds.union(us, vs);
			}
		}
		
		for (int i = 0; i < result.length; i++)
			System.out.println(result[i].cur.name + "--" + result[i].next.name);
	}
	
	// ��ӡ��С������
	public void print() {
		for (int i = 0; i < NUM_VERTICES; i++)
			if (graph[i].path != null)
				System.out.println(graph[i].name + "--" + graph[i].path.name);
	}
	
}
