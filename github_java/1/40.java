import java.util.ArrayList;
import java.util.LinkedList;

public class breadthfirstsearch {
    void addEdge1(ArrayList<LinkedList<Integer>> arrL,int s,int d)
    {
        arrL.get(s).add(d);
        arrL.get(d).add(s);
    }
    void bfs(ArrayList<LinkedList<Integer>> a,boolean visited[],int s)
    {
        LinkedList<Integer> q=new LinkedList<>();
        q.add(s);
        visited[s]=true;
        while(q.size()!=0)
        {
            int index=q.poll();
            System.out.println(index);
            for(int i=0;i<a.get(index).size();i++)
            {
                int x=a.get(index).get(i);
                if(visited[x]==false)
                {
                    q.add(x);
                    visited[x]=true;
                }
          rc  }
         
        }
    }
    public static void main(String[] args)
    {
        ArrayList<LinkedList<Integer>> arrp=new ArrayList<LinkedList<Integer>>();
        for(int i=0;i<6;i++)
           arrp.add(new LinkedList<>());
        breadthfirstsearch o=new breadthfirstsearch();
        o.addEdge1(arrp, 0, 1);
        o.addEdge1(arrp, 0, 2);
        o.addEdge1(arrp, 1, 3);
        o.addEdge1(arrp, 1, 4);
        o.addEdge1(arrp, 3, 4);
        o.addEdge1(arrp, 3, 5);
        o.addEdge1(arrp, 4, 2);
        o.addEdge1(arrp, 4, 1);
        o.addEdge1(arrp, 4, 5);
        o.addEdge1(arrp, 5, 4);
        boolean[] visited=new boolean[6];
        for(int i=0;i<6;i++)
            visited[i]=false;
        o.bfs(arrp, visited, 0);
       
        
    }
    
}
