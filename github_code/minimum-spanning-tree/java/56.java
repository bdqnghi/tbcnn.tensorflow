package assignment;

import utilities.spanningtree.Edge;
import utilities.spanningtree.MinimumSpanningTree;
import utilities.spanningtree.Node;

import java.util.List;

public class NetSimplex {
    public static void main(String[] args) {
        problem2();
    }
    public static void problem2(){
        String balance = "1=12,2=7,3=3,4=-8,5=-14";
        NetSimplex netSimplex = new NetSimplex(
                "{(1,2)=2,(1,3)=3,(1,4)=4,(2,3)=4,(2,5)=3," +
                        "(3,4),(3,5)=5,(4,5)=6,(5,inf)=-inf}",
                balance);
        netSimplex.setRootedSpanningTree("{(1,3),(1,4),(2,3),(3,5),(5,inf)}", balance);
        netSimplex.doWork();
        netSimplex.print();
    }

    private void print() {
        List<Edge> mst = minimumSpanningTree.getMinimumSpanningTree();
        MinimumSpanningTree mstNS = new MinimumSpanningTree(stringValue(mst)).setBalance(balance);
        for(Edge e : mst)
            System.out.println(
                    (e.getEnd().getName().equals("inf")?"z   = "+ (flow(mstNS)-nodePotential(mstNS)):
                    "x"+e.getStart().getName()+e.getEnd().getName()+" = "+_flow(e.getEnd(),e.getStart(),0))
            );
    }

    private String stringValue(List<Edge> mst) {
        String s = "{";
        for(Edge e : mst)
            s+="("+e.getStart().getName()+","+e.getEnd().getName()+"="+e.getWeight()+"),";
        return s;
    }

    private String balance;
    /**
     * algorithm network simplex;
     * begin
     *  determine an initial feasible tree structure(T,L,U);
     *  let x be the flow and pi be the node potentials associated with this tree structure;
     *  while some nontree arc violates the optimality conditions do
     *  begin
     *      select an entering arc (k,l) violating its optimality condition;
     *      add arc (k,l) to the tree and determine the leaving arc (p,q);
     *      perform a tree update and update the solutions x and pi;
     *  end;
     * end;
     */
    private MinimumSpanningTree minimumSpanningTree, rootedSpanningTree;
    public NetSimplex(String flowNetwork, String balance){
        this.balance = balance;
        minimumSpanningTree = new MinimumSpanningTree(flowNetwork)
                .setBalance(balance);
    }

    public void setRootedSpanningTree(String spanningTree, String balance) {
        this.rootedSpanningTree = new MinimumSpanningTree(spanningTree).setBalance(balance);
    }

    public void doWork(){
        double f = flow(rootedSpanningTree),
                np = nodePotential(rootedSpanningTree);
    }

    private double nodePotential(MinimumSpanningTree spanningTree) {
        Node rootNode = spanningTree.getNodes().get(minimumSpanningTree.getRootNode().getName()),
                endNode = spanningTree.getNodes().get(minimumSpanningTree.getEndNode().getFromEdges().get(0).getStart().getName());
        return _nodePotential(endNode,rootNode,0);
    }

    private double _nodePotential(Node endNode, Node rootNode, int i) {
        for(Edge e : rootNode.getToEdges()){
            if(e.getEnd().equals(endNode))
                i+=(int)(e.getEnd().getBalance()+e.getWeight());
            else
                i+=_nodePotential(endNode,e.getEnd(),(int)(e.getEnd().getBalance()+e.getWeight()));
        }
        return i;
    }

    /**
     * Compute the flow by starting at the end nodes of the tree and working towards the root
     * @param spanningTree
     * @return
     */
    private double flow(MinimumSpanningTree spanningTree) {
        Node rootNode = spanningTree.getNodes().get(minimumSpanningTree.getRootNode().getName()),
            endNode = spanningTree.getNodes().get(minimumSpanningTree.getEndNode().getFromEdges().get(0).getStart().getName());
        return _flow(endNode,rootNode,0);
    }

    private int _flow(Node endNode, Node rootNode, int v) {
        for(Edge n : endNode.getFromEdges()) {
            if (n.getStart().equals(rootNode))
                v += (int) (n.getStart().getBalance()+ n.getWeight());
            else
                v += _flow(n.getStart(), rootNode, (int) (n.getStart().getBalance()+ n.getWeight()));
        }
        return v;
    }
}
