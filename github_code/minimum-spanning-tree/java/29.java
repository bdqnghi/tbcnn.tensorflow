/*
 * Created on 2010-6-24
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package Graph;

import Element.ElemItem;
import Heap.MaxHeap;
import NormalSort.ITEM;
import NormalSort.Sort;
import Set.UnionFind;
import Tree.LcRsTree;

/**
 * @author Wei LU
 *
 * ��С����������С֧����
 */
public class MinimumSpanningTree {
	//�������ͼ
	GraphLnk G;
	// V[i]��ʾi���������еĸ��ڵ�
	int V[];
	// D[i]��ʾV[i]��i�γɵıߵ�Ȩֵ
	double D[];
	// �õ���������������������
	LcRsTree mst;
	// ������ʽ
	EdgeElem[] R;
	
	//���캯��
	public MinimumSpanningTree(GraphLnk G){
		this.G = G;
		// ����G�Ľڵ�����������
		V = new int[G.get_nv()];
		D = new double[G.get_nv()];
		// ����������СΪG�ڵ�����1����1�����ڵ�
		mst = new LcRsTree(G.get_nv() + 1);
		// 
		R = new EdgeElem[G.get_ne()];
	}
	
	/*Prim�㷨�����ͼG����С������
	 * ����s����С������������
	 * ��������ʱV��D��mst�����¸�ֵ
	 */
	public void Prim(int s){
		if(s < 0) return;
		int nv = G.get_nv();
		// ��ʼ��
		for(int i = 0; i < nv; i++){
			D[i] = Integer.MAX_VALUE;
			V[i] = -2;
			G.setMark(i, 0);//0 -- ÿ��ӵ�����
		}
		
		// �����s�����ڵ�Ϊ-1������Ϊ0
		V[s] = -1;
		D[s] = 0;
		G.setMark(s, 1);
		//�������ӵ���������
		mst.addChild(0, s, new ElemItem<Double>(D[s]));

		/*�����ඥ�����ҵ��뵱ǰMST����Ķ���v����������ĸ��ڵ��
		 * ����v��ӵ�MST�С�����ͼ��Ȩֵ����ڽڵ�v�С�
		 * ѭ��������ֱ�����ж��㶼����һ��
		 */
		while(true){
			/*��ȡ�뵱ǰ����������ıߣ����յ�Ϊ����Ķ���
			 * �յ�Ϊ�������ĸ��ڵ�
			 */
			Edge E = Utilities.minNextEdge(G, V);
			//�����Ϊ�գ���������
			if(E == null) return;
			System.out.println(E.get_v1() + " -- " + E.get_v2() + " -- " + G.getEdgeWt(E));
			// E����㸳ֵ��V[E���յ�]
			V[E.get_v2()] = E.get_v1();
			// E��Ȩֵ��ֵ��D[E���յ�]
			D[E.get_v2()] = G.getEdgeWt(E);
			// E���յ㱻���ʹ���
			G.setMark(E.get_v2(), 1);
			// ����С����������ӱ�E��Ӧ����Ϣ
			mst.addChild(E.get_v1(), E.get_v2(),
					new ElemItem<Double>(D[E.get_v2()]));
		}
		
	}
	
	
	
	/*
	 * �������߶��е�Prim�㷨��
	 * ��Ҫ������С�ѽṹ����������֮ǰֻ��������ѣ��������ｫ�ѽڵ������ڱ�ʾ
	 * ��С��ϵ��Ԫ��ֵ���� -1���������������õ�Ч����С�ѣ�
	 * �ѽڵ�Ԫ��Ϊ EdgeElem��
	 */
	public void PrimPQ(int s){
		if(s < 0) return;
		// ͼ�����ͼ�߸���
		int nv = G.get_nv();
		int ne = G.get_ne();
		// �����Ϊ�ߵ�����
		MaxHeap H = new MaxHeap(ne);
		
		// ��ʼ��
		for(int i = 0; i < nv; i++){
			D[i] = Integer.MAX_VALUE;
			V[i] = -2;
			G.setMark(i, 0);//0 -- ÿ��ӵ�����
		}

		// �����s�����ڵ�Ϊ-1������Ϊ0
		V[s] = -1;
		D[s] = 0;
		G.setMark(s, 1);
		//�������ӵ���������
		mst.addChild(0, s, new ElemItem<Double>(D[s]));
		// ��ʼ���ѣ�������������ı߶���ӵ�����
		for(Edge E = G.firstEdge(s); G.isEdge(E); E = G.nextEdge(E)){
			D[E.get_v2()] = G.getEdgeWt(E);
			V[E.get_v2()] = s;
			H.insert(new ElemItem<EdgeElem>(new EdgeElem(E, -1 * G.getEdgeWt(E))));
		}
		
		// ���Ѷ�Ԫ��ɾȥ������
		int v = -1; EdgeElem PE = null;
		while(true){
			v = -1;
			// ����Ѳ�Ϊ��
			while(H.topVal() != null){
				// ɾ�������ضѶ�Ԫ��
				PE = (EdgeElem)(H.removeMax().elem);
				v = PE.get_v2();
				// ����Ѷ�Ԫ�ض�Ӧ�Ķ���û�б����ʣ����˳�ѭ��
				if(G.getMark(v) == 0) break;
				// �����ʾû���ҵ���һ������ӵ�MST�Ķ���
				else v = -1;
			}
			
			// ���û�пɼ�����ӵĶ����ˣ���������
			if(v == -1) return;
			
			// ���õ��ĶѶ�Ԫ�ض�Ӧ��������Ϊ���ʹ�
			G.setMark(v, 1);
			
			// ����С����������ӱ�E��Ӧ����Ϣ
			mst.addChild(PE.get_v1(), PE.get_v2(),
					new ElemItem<Double>(D[PE.get_v2()]));
			
			// ��������v�����ġ�δ�����ʵı���ӵ�����
			for(Edge w = G.firstEdge(v); G.isEdge(w); w = G.nextEdge(w)){
				if(G.getMark(w.get_v2()) == 0 && D[G.edge_v2(w)] > G.getEdgeWt(w)){
					D[G.edge_v2(w)] = G.getEdgeWt(w);
					V[G.edge_v2(w)] = v;
					H.insert(new ElemItem<EdgeElem>(new EdgeElem(w, -1 * G.getEdgeWt(w))));
				}
			}
			
		}
	}
	
	
	
	
	/*
	 * Krustral�㷨��ȡ��С֧������
	 */
	public void Krustral(){
		int nv = G.get_nv();
		int ne = G.get_ne();
		// ��ʼ��
		for(int i = 0; i < nv; i++){
			D[i] = Integer.MAX_VALUE;
			V[i] = -2;
			G.setMark(i, 0);//0 -- ÿ��ӵ�����
		}
		// ��ȡͼ�ϵ�ÿһ���ߣ������߰���Ȩֵ�ɴ�С����
		ITEM[] E = Utilities.GetEdgeSort(G);
		// ������ʽ�ĵȼ���
		UnionFind UF = new UnionFind(nv);
		// �����ص�EdgeElem����
		R = new EdgeElem[nv]; int r = 0;
		for(int i = 0, k = 1; i < ne && k < nv; i++){
			// ��ȡһ����
			EdgeElem pe = (EdgeElem)(E[i].getElem());
			int v1 = pe.get_v1();
			int v2 = pe.get_v2();
			// ��������ߵ��������㲻��ͬһ���ȼ�����
			if(UF.find(v1) != UF.find(v2)){
				// ������������ϲ���
				UF.union(v1, v2);
				// ������������ӵ�EdgeElem������
				R[r++] = pe;
				System.out.print(R[r - 1].get_v1() + " <- (" + 
						R[r - 1].get_wt() +
						") -> " + 
						R[r - 1].get_v2() + "\t|");
				System.out.println("\n=================");
			}
		}
	}
	
	/**
	 * Boruvka �㷨�����С֧����
	 **/
	public void Boruvka(){
		int nv = G.get_nv();
		int ne = G.get_ne();
		// ��ʼ��
		for(int i = 0; i < nv; i++){
			D[i] = Integer.MAX_VALUE;
			V[i] = -2;
			G.setMark(i, 0);//0 -- ÿ��ӵ�����
		}
		// ��ȡͼ�ϵ�ÿһ����
		EdgeElem[] E = Utilities.GetEdge(G);
		EdgeElem[] B = new EdgeElem[nv];
		// ������ʽ�ĵȼ���
		UnionFind UF = new UnionFind(nv);
		// �����ص�EdgeElem����
		R = new EdgeElem[nv]; int r = 0;
		int N = 0;
		// ȨֵΪ�����ı�
		EdgeElem _z = new EdgeElem(null, Integer.MAX_VALUE);
		// ��ÿһ������
		for(int e = ne; e != 0; e = N){
			int h, i, j;
			// Ȩֵ��ʼ��Ϊ oo
			for(int t = 0; t < nv; t++) B[t] = _z;
			// ��ÿһ����
			for(h = 0, N = 0; h < e; h++){
				EdgeElem pe = E[h];
				// ��ȡ�ߵ������յ�
				i = UF.find(pe.get_v1());
				j = UF.find(pe.get_v2());
				// �����յ������ͬһ���ȼ����У�����������ѭ��
				if(i == j) continue;
				// ����ÿ���ڵ���������֮������ڽ�����ı�
				if(pe.get_wt() < B[i].get_wt()) B[i] = pe;
				if(pe.get_wt() < B[j].get_wt()) B[j] = pe;
				// N��ʾ���ǵ�ǰ����������
				E[N++] = pe;
			}
			// ��MST��ÿ����
			for(h = 0; h < nv; h++){
				// B[h]�ǵ�h��������������֮����������ı�
				if(B[h] != _z)
					// ���B[h]�������յ㲻��ͬһ���ȼ�����
					if(UF.find(B[h].get_v1()) != UF.find(B[h].get_v2())){
						// �������յ���õ�ͬһ���ȼ�����
						UF.union(B[h].get_v1(), B[h].get_v2());
						// ������������ӵ�EdgeElem������
						R[r++] = B[h];
						System.out.print(R[r - 1].get_v1() + " <- (" + 
								R[r - 1].get_wt() +
								") -> " + 
								R[r - 1].get_v2() + "\t|");
					}
			}
			System.out.println("\n ======================================");
		}
	}
	
	
	
	
	
}
