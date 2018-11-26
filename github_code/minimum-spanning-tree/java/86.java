package dataStructuresProblems;


//最小生成树，最短总距离
public class MinimumSpanningTree {
	public static void main(String[] args) {
		GraphMatrix gm = createGraph();
		OutGraph(gm);
		primGraph(gm);
	}
	static final int USED=0;
	static final int NoL=-1;
	//最小生成树算法
	/*Prim算法简述：
		1).输入：一个加权连通图，其中顶点集合为V，边集合为E；
		2).初始化：Vnew= {x}，其中x为集合V中的任一节点（起始点），Enew= {},为空；
		3).重复下列操作，直到Vnew= V：
		a.在集合E中选取权值最小的边<u, v>，其中u为集合Vnew中的元素，而v不在Vnew集合当中，并且v∈V（如果存在有多条满足前述条件即具有相同权值的边，则可任意选取其中之一）；
		b.将v加入集合Vnew中，将<u, v>边加入集合Enew中；
		4).输出：使用集合Vnew和Enew来描述所得到的最小生成树。
	 * */
	public static void primGraph(GraphMatrix gm){
		int i,j,k,min,sum=0;
		int[] weight = new int[GraphMatrix.MaxNum];//邻接矩阵某一行的权值
		char[] vtempx = new char[GraphMatrix.MaxNum];//邻接矩阵某一行的临时顶点信息
		//
		//找到所有与第一个顶点连通的的点
		for(i = 1;i<gm.VertexNum;i++){
			weight[i] = gm.EdgeWeight[0][i];
			if(weight[i]==GraphMatrix.MaxValue){
				vtempx[i] = (char)NoL;
			}else{
				vtempx[i] = gm.Vertex[0];//第一个顶点
			}
		}
		vtempx[0] = USED;
		weight[0] = GraphMatrix.MaxValue;
		
		for(i=1;i<gm.VertexNum;i++){
			min=weight[0];
			k=i;
			//找到当前行最小的权值，及其下标
			for(j=1;j<gm.VertexNum;j++){
				if(weight[j]<min && vtempx[j]>0){
					min=weight[j];
					k=j;
				}
			}
			sum += min;
			System.out.printf("(%c,%c),",vtempx[k],gm.Vertex[k]);
			//把访问过的顶点做标记，权值写成最大
			vtempx[k]=USED;
			weight[k]=GraphMatrix.MaxValue;
			//把下一个点和未访问的点之间的权值 以及 连通情况存进数组
			//找到具有更小权值的未使用边
			//vtempx[i] != 0 意味着没有被访问过
			for(j=0;j<gm.VertexNum;j++){
				if(gm.EdgeWeight[k][j]<weight[j] && vtempx[j] != 0){
					vtempx[j]=gm.Vertex[k];
					weight[j]=gm.EdgeWeight[k][j];
				}
			}
		}
		System.out.println("最小生成树的总权值为："+sum);
	}
	//生成一个无向带权图
	public static GraphMatrix createGraph(){
		GraphMatrix gm = new GraphMatrix();
		//生成5个顶点，六条边的图
		gm.GType = 0;
		
		gm.EdgeNum = 6;
		//这里初始化只能用new
		gm.Vertex = new char[]{'a','b','c','d','e'};
		gm.VertexNum = gm.Vertex.length;
		gm.EdgeWeight[0][1] = 2;
		gm.EdgeWeight[0][2] = 5;
		gm.EdgeWeight[0][4] = 3;
		gm.EdgeWeight[1][3] = 4;
		gm.EdgeWeight[2][4] = 5;
		gm.EdgeWeight[3][4] = 2;
		if(gm.GType == 0){
			for(int i = 0;i<gm.VertexNum;i++){
				for(int j = 0;j<gm.VertexNum;j++){
					if(i<j){
						gm.EdgeWeight[j][i] = gm.EdgeWeight[i][j];
					}
				}
			}
		}
		for(int i = 0;i<gm.VertexNum;i++){
			for(int j = 0;j<gm.VertexNum;j++){
				if(gm.EdgeWeight[i][j]==0){
					gm.EdgeWeight[i][j]=GraphMatrix.MaxValue;
				}
			}
		}
		return gm;
	}
	//输出邻接矩阵
	public static void OutGraph(GraphMatrix gm){
		System.out.println("该图的邻接矩阵数据如下：");
		int i,j;
		for(j=0;j<gm.VertexNum;j++){
			System.out.printf("\t%c",gm.Vertex[j]);//在第一行输出顶点信息
		}
		System.out.printf("\n");
		for(i=0;i<gm.VertexNum;i++){
			System.out.printf("%c",gm.Vertex[i]);
			for(j=0;j<gm.VertexNum;j++){
				if(gm.EdgeWeight[i][j]==GraphMatrix.MaxValue){
					System.out.printf("\tZ");//以Z表示无穷大
				}else{
					System.out.printf("\t%d",gm.EdgeWeight[i][j]);//输出边的权值
				}
			}
			System.out.println();
		}
	}
}

class GraphMatrix{
	static final int MaxNum = 20;//图的最大顶点数
	static final int MaxValue = 65535;
	char[] Vertex;
	int GType;//0:无向图 1:有向图
	int VertexNum;//顶点个数
	int EdgeNum;//边的个数
	int[][] EdgeWeight = new int[MaxNum][MaxNum];//保存边的权
	int[] isTrav = new int[MaxNum];//遍历标志
}