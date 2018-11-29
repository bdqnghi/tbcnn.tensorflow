import java.util.*;

public class B_Tree {
    private Node root;
    private final int row;
    private final Comparator comparator;
    private final int size;

    public B_Tree(int row,Comparator comparator){
        this.size = 2*row-1;
        this.row = row;
        this.comparator = comparator;
        root = new Node(2*row-1);
    }

    public Node getRoot(){
        return root;
    }

    public boolean insert(Object item){
        if(root.getItemsNumber()==0) {

            root.setItemsNumber(root.getItemsNumber()+1);
            return root.getItemArray().add(item);
        }
        else {
            return insert(item, root) != null;
        }
    }

    private Node insert(Object item,Node node) {
        boolean added = false;
        int i= 0;
        while(i<node.getItemsNumber()){
            if(comparator.compare(node.getItemArray().get(i),item)==0)
                return null;
            if(comparator.compare(node.getItemArray().get(i),item)>0){
                if(node.isLeaf()) {
                    int comp = 0;

                    node.getItemArray().add(i, item);
                    added = true;
                    node.setItemsNumber(node.getItemsNumber()+1);
                    if(node.isOversized()){
                        splitChild(node);
                    }

                }
                else
                    return insert(item,node.getChildArray().get(i));


            }
            else
            {
                int comp = 0;
                    while(i<node.getItemsNumber() && (comp= comparator.compare(node.getItemArray().get(i),item))<0)
                        i++;
                if(node.isLeaf()) {
                    node.getItemArray().add(i, item);
                    Collections.sort(node.getItemArray(),comparator);
                    node.setItemsNumber(node.getItemsNumber() + 1);
                    if (node.isOversized()) {
                        splitChild(node);
                    }
                }

                else {
                    return insert(item, node.getChildArray().get(i));
                }
            }

         }
         if(!added){
            return insert(item,node.getChildArray().get(i+1));
         }

        return node;
    }

    public boolean search(Object key){
        return search(root,key)!=null;
    }


    public void splitChild(Node node){
        if(node.equals(root)){
            int mid = node.getItemsNumber()/2;
            ArrayList first = new ArrayList();
            for(int i=0;i<mid;i++)
                first.add(node.getItemArray().get(i));
            ArrayList second = new ArrayList();
            for(int i=mid+1;i<node.getItemsNumber();i++)
                second.add(node.getItemArray().get(i));

            Node node1 = new Node(size);
            node1.setItemArray(first);
            Node node2 = new Node(size);
            node2.setItemArray(second);
            if(node.getChildArray().size()!=0)
            {
                int midChild = node.getChildArray().size()/2;
                ArrayList<Node> firstArray = new ArrayList<>();
                ArrayList <Node> secondArray = new ArrayList<>();
                for(int i=0;i<=midChild;i++) {

                        firstArray.add(node.getChildArray().get(i));
                        node.getChildArray().get(i).setParent(node1);
                    }


                for(int i = midChild+1;i<node.getChildArray().size();i++) {
                        secondArray.add(node.getChildArray().get(i));
                        node.getChildArray().get(i).setParent(node2);

                }
                node1.setChildArray(firstArray);
                node1.setLeaf(false);
                node2.setChildArray(secondArray);
                node2.setLeaf(false);
            }

            Object midValue = node.getItemArray().get(mid);
            root = new Node(size);
            root.setLeaf(false);
            root.getItemArray().add(midValue);
            root.setItemsNumber(1);
            ArrayList<Node> newChildren = new ArrayList<>();
            newChildren.add(node1);
            newChildren.add(node2);
            root.setChildArray(newChildren);
            node1.setItemsNumber(first.size());
            node2.setItemsNumber(second.size());
            node1.setParent(root);
            node2.setParent(root);


        }
        else {
                int mid = node.getItemsNumber() / 2;
                Object key = node.getItemArray().get(mid);
                int i = 0;
                Node parent = node.getParent();

                int comp = 0;
                while (i < parent.getItemsNumber() && (comp = comparator.compare(key, parent.getItemArray().get(i))) > 0) {
                    i++;
                }
                parent.getItemArray().add(i, key);
                ArrayList first = new ArrayList();
                ArrayList second = new ArrayList();
                for (int j = 0; j < mid; j++)
                    first.add(node.getItemArray().get(j));
                for (int j = mid + 1; j < node.getItemsNumber(); j++)
                    second.add(node.getItemArray().get(j));

                Node node1 = new Node(size);
                node1.setItemArray(first);
                Node node2 = new Node(size);
                node2.setItemArray(second);
                node1.setParent(node.getParent());
                node1.setItemsNumber(first.size());
                node2.setItemsNumber(second.size());
                node2.setParent(node.getParent());

                parent.getChildArray().set(parent.getChildArray().indexOf(node), node1);

                parent.getChildArray().add(parent.getChildArray().indexOf(node1)+1,node2);
                parent.setItemsNumber(parent.getItemsNumber() + 1);

                if (node.getChildArray().size() != 0) {
                    int midChild = node.getChildArray().size() / 2;
                    ArrayList<Node> firstArray = new ArrayList<>();
                    ArrayList<Node> secondArray = new ArrayList<>();
                    for(int j=0;j<=midChild;j++) {
                        if(comparator.compare(node.getChildArray().get(j).getItemArray().get(node.getChildArray().get(j).getItemsNumber()-1),node.getParent().getItemArray().get(0))<0) {
                            firstArray.add(node.getChildArray().get(j));
                            node.getChildArray().get(j).setParent(node1);
                        }
                        else{
                            secondArray.add(node.getChildArray().get(j));
                            node.getChildArray().get(j).setParent(node2);
                        }

                    }
                    for(int j = midChild+1;j<node.getChildArray().size();j++) {
                        if (comparator.compare(node.getChildArray().get(j).getItemArray().get(node.getChildArray().get(j).getItemsNumber() - 1), node.getParent().getItemArray().get(0)) < 0) {
                            firstArray.add(node.getChildArray().get(j));
                            node.getChildArray().get(j).setParent(node1);
                        } else {
                            secondArray.add(node.getChildArray().get(j));
                            node.getChildArray().get(j).setParent(node2);

                        }
                    }
                        node1.setChildArray(firstArray);
                        node1.setLeaf(false);
                        node2.setChildArray(secondArray);
                        node2.setLeaf(false);

                }
                if (parent.isLeaf())
                    parent.setLeaf(false);
                if (parent.isOversized())
                    splitChild(parent);
            }
    }

    private Node search(Node node, Object key){
        int i = 0;
        while(i<node.getItemsNumber()) {
            if (comparator.compare(node.getItemArray().get(i), key) == 0)
                return node;
            else if (comparator.compare(node.getItemArray().get(i), key) > 0) {
                return search((Node) node.getChildArray().get(i), key);
            } else {
                i++;
            }
        }
        if(i>=node.getChildArray().size())
            return search(node.getChildArray().get(i+1),key);
        return null;
    }

    private void print(Node node){
        System.out.println(node);
        for(Node temp :node.getChildArray())
            print(temp);
    }

    public void print(){
        print(root);
    }


}
