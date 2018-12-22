import java.util.*;

public class B_Tree
{

	private int max_size = 2;
	private Node root = null;
	static int depth = 0;
	
	
	public void set_Tree(int size)
	{
		this.max_size = size;
		if (root == null)
			root = new Node(max_size);
		depth = 1;
		System.out.println("Set complite");
	}

	public Node search(String key, char command)
	{
		int k = Integer.parseInt(key);
		
		Node tmp = root;
		
		for (int i = 1; i <= depth; i++)
		{
			if(i!=depth) // depth�� �����ϱ� ���� ���� ���� ��� indexed array �̴�.
			{	
				for(int j=0;j<tmp.size;j++)
					if(k <= tmp.index[j].key)
					{
						tmp = tmp.index[j];
						break;
					}
			}
			else// root�� ���� depth�� �������� �� �ڸ��� ã����
			{
				if(command == 's')
				{
					for(int j=0;j<tmp.size;j++)
						if(tmp.index[j].key == k)
						{
								System.out.println("\n" + tmp.index[j].key+
												   ", " + tmp.index[j].value);
								return tmp;
						}
						else if(tmp.index[j].key > k)
						{
							System.out.println("NOT FOUND");
							return null;
						}
						 
				}
				else
				{
					return tmp;
				}
			}
		}
		return tmp;
	}
	
	public void split(Node n)
	{
		int num = (max_size+1)/2;
		Node New_Node = new Node(max_size);
		
		for(int i=0;i<max_size/2;i++)
		{
			New_Node.index[i] = n.index[num+i];
			n.index[num+i] = null;
		}
		n.size = num;
		New_Node.size = max_size/2;
		
		if(n.parents != null)
		{
			n.parents.insert(New_Node);
			if(n.parents.size>max_size)
				split(n.parents);
		}
		else//parents�� ������ root ����̹Ƿ� ���ο� root�� �Ҵ�������Ѵ�.
		{
			Node New_root = new Node(max_size);
			New_root.index[0]=n;
			New_root.index[1]=New_Node;
			New_root.size=2;
			root = New_root;
			depth++;
		}
	}
	public void insert(String key, String data)
	{
		int k = Integer.parseInt(key);
		int dt = Integer.parseInt(data);
		
		Node tmp = search(key,'i');
		
		tmp.insert(k, dt);
		
		if(tmp.size > max_size)
			split(tmp);
	}

	public void erase(Node n)
	{
		Node tmp = n.parents;
		tmp.delete(n);
		if(tmp.size == 0 && tmp.parents !=null)
			erase(tmp.parents);
	}
	public void Delete(String key)
	{
		int k = Integer.parseInt(key);
		
		Node tmp = search(key,'d');
		
		tmp.delete(k);
		
		if(tmp.size == 0 && tmp.parents != null)
			erase(tmp);
	}

	public void print()
	{
		Queue<Node> a = new LinkedList<Node>();
		a.add(root);
		
		for(int i=0;i<depth;i++)
		{
			int t = a.size();
			for(int k=0;k<t;k++)
			{
				Node n = a.poll();
				if(n == null) continue;
			
				for(int j=0;j<n.size;j++)
				{
					a.add(n.index[j]);
					System.out.print(n.key+" ");
				}
				System.out.print("|");
			}
			System.out.println();
		}
	}
}
