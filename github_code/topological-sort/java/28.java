import java.util.*;
import java.io.*;
class TOPOLOGICALSORT
{
    public static void main(String[]args)
    {
        InputReader1 sc = new InputReader1(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        int inDegree [] = new int [ N+1 ];
        Map<Integer,ArrayList<Integer>> map = new HashMap<Integer,ArrayList<Integer>>();
        StringBuilder s = new StringBuilder();
        while( M -- > 0 )
        {
            int x = sc.nextInt();
            int y = sc.nextInt();
            inDegree[y]++;
            if(map.containsKey(x))
                map.get(x).add(y);
            else
            {
                map.put(x,new ArrayList<Integer>());
                map.get(x).add(y);
            }
            if(map.containsKey(y)==false)
            map.put(y , new ArrayList<Integer>());
        }
        for(int i = 1 ; i <= N ; i++)
        if(map.containsKey(i)==false)
        map.put(i,new ArrayList<Integer>());
        
        PriorityQueue<Item> pq = new PriorityQueue<Item>();
        for(int i=1;i<=N;i++)
        {
            if(inDegree[i]==0)
                pq.add(new Item(i));
        }
        Queue<Integer>q = new LinkedList<Integer>();
        while(!pq.isEmpty())
        {
            int node = pq.poll().node;
            int size = map.get(node).size();
            q.add(node);
            for(int i=0 ; i<size ; i++)
            {
                int next = map.get(node).get(i);
                inDegree[next]--;
                if(inDegree[next]==0)
                    pq.add(new Item(next));
            }
        }
        if(q.size() != N)
            System.out.println("Sandro fails.");
        else
        {
            while(!q.isEmpty())
            {
                int v = q.poll();
                s.append(v+" ");
            }
            System.out.println(s);
        }
    }
}
class Item implements Comparable <Item>
{
    int node;
    public Item(int node)
    {
        this.node=node;
    }

    public int compareTo( Item o )
    {
        return this.node - o.node;
    }
}	
class InputReader1 
{

    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public InputReader1(InputStream stream) {
        this.stream = stream;
    }

    public int read() {
        if (numChars == -1)
            throw new InputMismatchException();
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0)
                return -1;
        }
        return buf[curChar++];
    }

    public int nextInt() {
        int c = read();
        while (isSpaceChar(c))
            c = read();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9')
                throw new InputMismatchException();
            res *= 10;
            res += c & 15;
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public long nextLong() {
        int c = read();
        while (isSpaceChar(c))
            c = read();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        long res = 0;
        do {
            if (c < '0' || c > '9')
                throw new InputMismatchException();
            res *= 10;
            res += c & 15;
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public String next() {
        int c = read();
        while (isSpaceChar(c))
            c = read();
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isSpaceChar(c));
        return res.toString();
    }

    public String nextLine() {
        int c = read();
        //while (c != '\n' && c != '\r' && c != '\t' && c != -1)
        //c = read();
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (c != '\n' && c != '\r' && c != '\t' && c != -1);
        return res.toString();
    }

    public static boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }

}

