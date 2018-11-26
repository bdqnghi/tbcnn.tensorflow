
public class FordFulkerson 
{
	private boolean[] marked;	//��ʣ���������Ƿ���ڴ�s��v��·��
	private FlowEdge[] edgeTo;	//��s��v�����·���ϵ����һ����
	private double value; 		//��ǰ�������
	
	public FordFulkerson(FlowNetwork G, int s, int t)
	{	//�ҳ���s��t����������G�������������
		while(hasAugmentingPath(G, s, t))
		{	//�������д��ڵ�����·��
			//���㵱ǰ��ƿ������
			double bottle = Double.POSITIVE_INFINITY;
			for(int v = t; v != s; v = edgeTo[v].other(v))
			{
				bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
			}
			//��������
			for(int v = t; v != s; v = edgeTo[v].other(v))
			{
				edgeTo[v].addResidualFlowTo(v, bottle);
			}
			value += bottle;
		}		
	}
	
	private boolean hasAugmentingPath(FlowNetwork G, int s, int t)
	{
		marked = new boolean[G.V()];	//���·����֪�Ķ���
		edgeTo = new FlowEdge[G.V()]; 	//·���ϵ����һ����
		Queue<Integer> q = new Queue<Integer>();
		
		marked[s] = true;	//������
		q.enqueue(s); 		//����������
		while(!q.isEmpty())
		{
			int v = q.dequeue();
			for(FlowEdge e : G.adj(v))
			{
				int w = e.other(v);
				if(e.residualCapacityTo(w) > 0 && !marked[w])
				{//(��ʣ��������)��������һ�����ӵ�һ��δ��ǵĶ���ı�
					edgeTo[w] = e;	//����·���ϵ����һ����
					marked[w] = true;	//���w����Ϊ·����������֪����
					q.enqueue(w);	//��������
				}
			}
		}
		return marked[t];
	}
	
	public double value()
	{
		return value;
	}
	
	public boolean inCut(int v)
	{
		return marked[v];
	}
	
	public static void main(String[] args)
	{
		FlowNetwork G = new FlowNetwork(6);
		int[] from = new int[]{0, 0, 1, 1, 2, 2, 3, 4};
		int[] to = new int[]{1, 2, 3, 4, 3, 4, 5, 5};
		double[] capacity = new double[]{2.0, 3.0, 3.0, 1.0, 1.0, 1.0, 2.0, 3.0};
		for(int i = 0; i < from.length; i++)
		{
			FlowEdge edge = new FlowEdge(from[i], to[i], capacity[i]);
			G.addEdge(edge);
		}		
		
		int s = 0, t = G.V() - 1;
		FordFulkerson maxflow = new FordFulkerson(G, s, t);
		System.out.println("Max flow from " + s + " to " + t);
		for(int v = 0; v < G.V(); v++)
		{
			for(FlowEdge e : G.adj(v))
			{
				if(v == e.from() && e.flow() > 0)
				{
					System.out.println(" " + e);
				}
			}
		}
		System.out.println("Max flow value = " + maxflow.value());
	}
}
