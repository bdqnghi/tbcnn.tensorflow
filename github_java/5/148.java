package Number_4;

import edu.princeton.cs.algs4.In;

/**
 * P339 �������������DFS�� 
 * �������һ������ʱ�� 
 *  1���������Ϊ�ѷ��ʣ� 
 *  2���ݹ�ط���������û�б���ǹ����ھӶ���
 * ���ͼ����ͨ��count=G.V,��count��������ͼ�Ķ�����
 * 
 * @author he
 *args[0]:tinyCG.txt
 *args[1]:0
 */
public class DepthFirstSearch {
	private boolean[] marked;// ��¼�����Ƿ񱻱��
	private int count;// ��ǹ��Ķ�������

	// sΪ���
	public DepthFirstSearch(Graph G, int s) {
		marked = new boolean[G.V()];
		dfs(G, s);
	}

	//����ÿ���ߺ�ÿ������
	public void dfs(Graph G, int s) {
		marked[s] = true;
		count++;
		for (int w : G.adj(s))
			// ���δ�����,�ݹ�
			if (!marked(w))
				dfs(G, w);
	}

	// �ж�v�Ƿ񱻱�ǹ�
	public boolean marked(int v) {
		return marked[v];
	}

	// �����Ѿ�����ǵĶ�������
	public int count() {
		return count;
	}

	public static void main(String[] args) {

		Graph G = new Graph(new In(args[0]));
		int s = Integer.valueOf(args[1]);// ���
		DepthFirstSearch dfs = new DepthFirstSearch(G, s);
		System.out.println(G.V());
		System.out.println(dfs.count);
		System.out.println("����ͼG�Ƿ���ͨ�� " + (dfs.count == G.V()));
	}

}
