package D_Tree;

import java.util.*;

/**
 * Created by qilianshan on 17/9/7.
 */
public class B_TreeSet<T> extends AbstractSet<T> {
    private BinaryNode root;

    private int size;

    private Comparator<? super T> cmp;

    public B_TreeSet()
    {
        this(null);
    }

    //可以声明一个泛型comparator，其中comparator中的类型是T的超类

    public B_TreeSet(Comparator<? super T> c)
    {
        root=null;cmp=c;size=0;
    }

    private int myCompare(T lhs,T rhs)
    {
        if(cmp!=null)
            //在这里可以看到comparator的使用，由于使用的是cmp，cmp一定会约束传入值是comparator中?的子类，
            //所以构造函数在接受comparator时，要求comparator内必须是super于T的
            return cmp.compare(lhs,rhs);
        else
            return ((Comparable)lhs).compareTo(rhs);
    }

    public void insert(T Element)
    {
        if(root==null){
            root=new BinaryNode(Element,null,null,null);
            return;
        }
        insert(Element,root,null);
    }

    private BinaryNode<T> insert(T Element,BinaryNode<T> node,BinaryNode<T> parent)
    {
        BinaryNode<T> t=node;
        if(t==null){
            t=new BinaryNode<T>(Element,null,null,parent);
            size++;
        }else if(myCompare(Element,node.element)==1){
            //大于的话在右子树插入
            node.right=insert(Element,node.right,node);
        }else if(myCompare(Element,node.element)==-1){
            //小于的话在左子树插入
            node.left=insert(Element,node.left,node);
        }
        return t;
    }

    public boolean remove(Object Element)
    {
        if(root==null)
        {
            throw new NoSuchElementException();
        }
        root=removeL((T) Element, root);
        return true;
    }

    private BinaryNode<T> removeR(T x,BinaryNode<T> t)
    {
        if(t==null)
            return t;
        int compareResult=myCompare(x, t.element);

        if(compareResult<0)
            t.left=removeR(x, t.left);
        else if(compareResult>0)
            t.right=removeR(x, t.right);
        else if(t.left!=null && t.right!=null)
        {
            //如果左右子树都不为零，在右子树中找到最小的节点替换上来，然后将右子树的对应节点删除
            t.element=findMin(t.right).element;
            t.right=removeR(t.element, t.right);
        }
        else
            //一个子节点的情况下，有左用做，有右用右
            t=(t.left!=null)?t.left:t.right;
        return t;
    }

    private BinaryNode<T> removeL(T x,BinaryNode<T> t)
    {
        if(t==null)
            return t;
        int compareResult=myCompare(x,t.element);

        if(compareResult<0)
            t.left=removeL(x, t.left);
        else if(compareResult>0)
            t.right=removeL(x, t.right);
        else if(t.left!=null && t.right!=null)
        {
            //如果左右子树都不为零，在右子树中找到最小的节点替换上来，然后将右子树的对应节点删除
            t.element=findMax(t.left).element;
            t.left=removeL(t.element, t.left);
        }
        else
            //一个子节点的情况下，有左用做，有右用右
            t=(t.left!=null)?t.left:t.right;
        return t;
    }

    private BinaryNode<T> removeLRR(T x,BinaryNode<T> t,boolean leftOrRight)
    {
        if(t==null)
            return t;
        int compareResult=myCompare(x,t.element);

        if(compareResult<0)
            t.left=removeLRR(x, t.left,!leftOrRight);
        else if(compareResult>0)
            t.right=removeLRR(x, t.right,!leftOrRight);
        else if(t.left!=null && t.right!=null)
        {
            if(leftOrRight){
                t.element=findMax(t.left).element;
                t.left=removeLRR(t.element,t.left,!leftOrRight);
            }else{
                t.element=findMin(t.right).element;
                t.right=removeLRR(t.element,t.right,!leftOrRight);
            }
            //如果左右子树都不为零，在右子树中找到最小的节点替换上来，然后将右子树的对应节点删除

        }
        else
            //一个子节点的情况下，有左用做，有右用右
            t=(t.left!=null)?t.left:t.right;
        return t;
    }

    private BinaryNode<T> removeLRA(T x,BinaryNode<T> t)
    {
        if(t==null)
            return t;
        int compareResult=myCompare(x,t.element);

        if(compareResult<0)
            t.left=removeLRA(x, t.left);
        else if(compareResult>0)
            t.right=removeLRA(x, t.right);
        else if(t.left!=null && t.right!=null)
        {
            if(Math.random()>=0.5){
                t.element=findMax(t.left).element;
                t.left=removeLRA(t.element,t.left);
            }else{
                t.element=findMin(t.right).element;
                t.right=removeLRA(t.element,t.right);
            }
        }
        else
            //一个子节点的情况下，有左用做，有右用右
            t=(t.left!=null)?t.left:t.right;
        return t;
    }

    public String printTree()
    {
        Iterator<T> it=this.iterator();
        String str="";
        while (it.hasNext())
        {
            str=str+it.next()+' ';
        }
        return str;
    }

    private BinaryNode<T> getNode(T Element,BinaryNode<T> root)
    {

        if(root.element==Element){
            return root;
        }else{
            root=null;
            BinaryNode<T> left=getNode(Element,root.left);
            if(left!=null){
                root=left;
            }
            BinaryNode<T> right=getNode(Element,root.right);
            if(right!=null){
                root=right;
            }
        }
        return root;
    }

    private BinaryNode<T> findMin(BinaryNode<T> t){
        if(t!=null)
            while (t.left!=null)
                t=t.left;
        return t;
    }

    private BinaryNode<T> findMax(BinaryNode<T> t){
        if(t!=null)
            while(t.right!=null)
                t=t.right;
        return t;
    }

    @Override
    public Iterator iterator() {
        return new B_Iterator();
    }

    private class B_Iterator<T> implements Iterator<T>
    {
        BinaryNode<T> currentNode;
        private Stack<BinaryNode<T>> s=new Stack<BinaryNode<T>>();

        public B_Iterator(){
            currentNode=root;
            while(currentNode!=null){
                s.push(currentNode);
                currentNode=currentNode.left;
            }
        }
        public boolean hasNext() {
            return !s.empty();
        }

        public T next() {
            BinaryNode<T> n=s.pop();
            T res=n.element;
            if(n.right!=null)
            {
                n=n.right;
                while (n!=null){
                    s.push(n);
                    n=n.left;
                }
            }
            return res;
        }

        public void remove() {

        }
    }

    @Override
    public int size() {
        return size;
    }

    private static class BinaryNode<T>
    {
        T element;
        BinaryNode<T> left;
        BinaryNode<T> right;
        BinaryNode<T> parent;
        //找到剩下的元素中最大的元素
        //找到剩下的元素中，最小的元素
        BinaryNode<T> nextMin;
        BinaryNode<T> nextMax;
        BinaryNode(T Element)
        {
            this(Element,null,null,null);
        }
        BinaryNode(T Element,BinaryNode<T> lt,BinaryNode<T> rt,BinaryNode<T> pt)
        {
            element=Element;
            left=lt;
            right=rt;
            parent=pt;
            //最大
            BinaryNode p=this;
            while(p!=null){
                p=p.parent;
            }
            while (p!=null){
                p=p.right;
            }
            this.nextMax=p;
            //下一个最小的位置
            this.nextMin=parent;
        }
    }

}
