import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class BTree {
    
    private BNode root;
    int t;
    public BTree(int t){
        this.t= t;
        this.root = null;
    }
    
    public File write(BNode node) throws IOException{
        String filePath = node.x[0];
        PrintWriter pw = new PrintWriter(new FileWriter(filePath));
        pw.println(node.isLeaf);
        pw.println(node.n);
        for(int i = 0; i < node.n; i++){
            pw.println(node.c[i]);
            pw.println(node.x[i]);
        }
        pw.print(node.c[node.n]);
        pw.close();
        return new File(filePath);
    }
    
    public BNode read(String filePath)throws IOException{
        BNode node = new BNode(this.t);
        BufferedReader br = new BufferedReader(new FileReader(filePath));
        
        node.isLeaf = ((br.readLine().equals("0"))? false:true);
        node.n = Integer.parseInt(br.readLine());
        for(int i = 0; i < node.n; i++){
            node.c[i] = br.readLine();
            node.x[i] = br.readLine();
        }
        node.c[node.n] = br.readLine();
        br.close();
        return node;
    }
    
    private class BNode{
        boolean isLeaf;
        int n;
        String[] x;
        String[] c;
        
        public BNode(int t){
            this.isLeaf = false;
            this.x = new String[2*t];
            this.c = new String[2*t];
            this.n = 0;
        }
    }
}