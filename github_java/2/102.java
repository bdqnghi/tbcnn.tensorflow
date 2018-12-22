package ds.avltree;

import java.util.Comparator;  

/*
 * ƽ����������
AVL�������ϻ���һ�ö����������������ص��ǣ�
1.����������һ�ö�����������
2.����ƽ��������ÿ���������������ĸ߶�֮��ľ���ֵ��ƽ�����ӣ����Ϊ1��
Ҳ����˵��AVL�����������Ǵ���ƽ�⹦�ܵĶ������������������������������������

���ҡ������ɾ����ƽ���������¶���O��log n����
���Ӻ�ɾ��������Ҫͨ��һ�λ�������ת������ƽ���������
 */

public class AvlTree<AnyType extends Comparable<? super AnyType>> {  
    private AvlNode<AnyType> root;  
    private Comparator<? super AnyType> cmp;   
    
    //AVL���Ľ���ʾ  
    private static class AvlNode<AnyType>{  
        AnyType element;  
        AvlNode<AnyType> left;  
        AvlNode<AnyType> right;  
        int height;       
        AvlNode(AnyType theElement){  
            this(theElement, null, null);  
        }         
        AvlNode(AnyType theElement, AvlNode<AnyType> lt, AvlNode<AnyType> rt){  
            element = theElement;  
            left = lt;  
            right = rt;  
            height = 0;  
        }  
    }  
  
    public AvlTree(){  
        root = null;  
    }     
    public void makeEmpty(){  
        root = null;  
    }     
    public boolean isEmpty(){  
        return root == null;          
    }     
    public void insert(AnyType element){  
        root = insert(element, root);             
    }     
    public boolean contains(AnyType x){  
        return contains(x, root);  
    }     
    public void remove(AnyType element){  
        root = remove(element, root);  
    } 
    
    public void setComparator(Comparator<? super AnyType> cmp) {
    	this.cmp = cmp;
    }
    //���û������cmp�� ����Comparable�ӿڵķ������бȽ�  
    //�й�������cmp�� ����Comparator�ӿڵķ������бȽ�   
    private int myCompare(AnyType lhs, AnyType rhs){  
        if(cmp != null)  
            return cmp.compare(lhs, rhs);  
        else  
            return ((Comparable)lhs).compareTo(rhs);  
    }  
    
    
    private boolean contains(AnyType x, AvlNode<AnyType> t){  
        //����  
        if(t == null)  
            return false;  
        //�����������  
        int compareResult = myCompare(x, t.element);  
        if(compareResult < 0)  
            return contains(x, t.left);  
        else if(compareResult > 0)  
            return contains(x, t.right);  
        else  
            return true;  
    }   
    
    private int height(AvlNode<AnyType> t){  
        return t == null ? -1 : t.height;  
    }     
    private AvlNode<AnyType> findMin(AvlNode<AnyType> t){  
        if(t == null)  
            return null;  
        if(t.left == null)  
            return t;  
        return findMin(t.left);  
    }     
    private AvlNode<AnyType> findMax(AvlNode<AnyType> t){  
        if(t == null)  
            return null;  
        if(t.right == null)  
            return t;  
        return findMax(t.right);  
    } 
    
    private AvlNode<AnyType> insert(AnyType x, AvlNode<AnyType> t){  
        if(t == null)  
            return new AvlNode<AnyType>(x, null, null);         
        int compareResult = myCompare(x, t.element);  
        if(compareResult < 0){  
            t.left = insert(x, t.left);  
            if(height(t.left)-height(t.right) == 2){  
                if(myCompare(x, t.left.element) < 0)     //�������    
                    t = rotateWithLeftChild(t);  
                else                                     //�������  
                    t = doubleWithLeftChild(t);  
            }  
        }else if(compareResult > 0){  
            t.right = insert(x, t.right);  
            if(height(t.right)-height(t.left) == 2){  
                if(myCompare(x, t.right.element) < 0)        //������� 
                    t = doubleWithRightChild(t);  
                else                                        //�������  
                    t = rotateWithRightChild(t);  
            }  
        }         
        //����hight 
        t.height = Math.max(height(t.left), height(t.right))+1;  
        return t;  
    } 
    
    private AvlNode<AnyType> remove(AnyType x, AvlNode<AnyType> t){  
        if(t == null)  
            return null;  
        int compareResult = myCompare(x, t.element);  
        if(compareResult < 0){  
            t.left = remove(x, t.left);  
            //����֮����֤�������Ƿ�ƽ��  
            if(t.right != null){        //��������Ϊ�գ���һ����ƽ��ģ���ʱ�������൱�Ը��ڵ�������Ϊ1, ����ֻ�����������ǿ����  
                if(t.left == null){     //��������ɾ����Ϊ�գ�����Ҫ�ж�������  
                    if(height(t.right)-t.height == 2){  
                        AvlNode<AnyType> k = t.right;  
                        if(k.right != null){        //���������ڣ��������������ת  
                            System.out.println("-----------------------------------------------------------------------------11111");  
                            t = rotateWithRightChild(t);  
                        }else{                      //���������������˫��ת                 
                            System.out.println("-----------------------------------------------------------------------------22222");  
                            t = doubleWithRightChild(t);  
                        }  
                    }  
                }else{                  //�����ж����������ĸ߶Ȳ�  
                    //����������Ҳ���ܲ�ƽ�⣬����ƽ�����������ٿ�������  
                    AvlNode<AnyType> k = t.left;  
                    //ɾ������Ĭ��������������С�ڵ㲹ɾ���Ľڵ�  
                    //k���������߶Ȳ�����k��������  
                    if(k.right != null){  
                        if(height(k.left)-height(k.right) == 2){  
                            AvlNode<AnyType> m = k.left;  
                            if(m.left != null){     //���������ڣ��������������ת  
                                System.out.println("-----------------------------------------------------------------------------33333");  
                                k = rotateWithLeftChild(k);  
                            }else{                      //���������������˫��ת                 
                                System.out.println("-----------------------------------------------------------------------------44444");  
                                k = doubleWithLeftChild(k);                               
                            }  
                        }  
                    }else{  
                        if(height(k.left) - k.height ==2){  
                            AvlNode<AnyType> m = k.left;  
                            if(m.left != null){     //���������ڣ��������������ת  
                                System.out.println("-----------------------------------------------------------------------------hhhhh");  
                                k = rotateWithLeftChild(k);  
                            }else{                      //���������������˫��ת                 
                                System.out.println("-----------------------------------------------------------------------------iiiii");  
                                k = doubleWithLeftChild(k);  
                            }  
                        }  
                    }                     
                    if(height(t.right)-height(t.left) == 2){  
                        //����������һ����ƽ��ģ�����ʧ��Ļ�����ת���Խ������  
                        System.out.println("-----------------------------------------------------------------------------55555");  
                        t = rotateWithRightChild(t);  
                    }  
                }  
            }  
            //����֮�����heightֵ  
            t.height = Math.max(height(t.left), height(t.right))+1;  
        }else if(compareResult > 0){  
            t.right = remove(x, t.right);  
            //������֤�����Ƿ�ƽ��  
            if(t.left != null){         //��������Ϊ�գ���һ����ƽ��ģ���ʱ�������൱�Ը��ڵ�������Ϊ1  
                if(t.right == null){        //��������ɾ����Ϊ�գ���ֻ���ж�������  
                    if(height(t.left)-t.height ==2){  
                        AvlNode<AnyType> k = t.left;  
                        if(k.left != null){  
                            System.out.println("-----------------------------------------------------------------------------66666");  
                            t = rotateWithLeftChild(t);  
                        }else{  
                            System.out.println("-----------------------------------------------------------------------------77777");  
                            t = doubleWithLeftChild(t);  
                        }  
                    }                     
                }else{              //��������ɾ����ǿգ����ж����������ĸ߶Ȳ�  
                    //����������Ҳ���ܲ�ƽ�⣬����ƽ�����������ٿ�������  
                    AvlNode<AnyType> k = t.right;  
                    //ɾ������Ĭ��������������С�ڵ㣨���󣩲�ɾ���Ľڵ�  
                    //k���������߶Ȳ�����k��������                     
                    if(k.left != null){  
                        if(height(k.right)-height(k.left) == 2){  
                            AvlNode<AnyType> m = k.right;  
                            if(m.right != null){        //���������ڣ��������������ת  
                                System.out.println("-----------------------------------------------------------------------------88888");  
                                k = rotateWithRightChild(k);  
                            }else{                      //���������������˫��ת                 
                                System.out.println("-----------------------------------------------------------------------------99999");  
                                k = doubleWithRightChild(k);  
                            }  
                        }  
                    }else{  
                        if(height(k.right)-k.height == 2){  
                            AvlNode<AnyType> m = k.right;  
                            if(m.right != null){        //���������ڣ��������������ת  
                                System.out.println("-----------------------------------------------------------------------------aaaaa");  
                                k = rotateWithRightChild(k);  
                            }else{                      //���������������˫��ת                 
                                System.out.println("-----------------------------------------------------------------------------bbbbb");  
                                k = doubleWithRightChild(k);  
                            }  
                        }  
                    }                     
                    if(height(t.left) - height(t.right) == 2){  
                        //����������һ����ƽ��ģ�����ʧ��Ļ�����ת���Խ������  
                        System.out.println("-----------------------------------------------------------------------------ccccc");  
                        t = rotateWithLeftChild(t);           
                    }  
                }  
            }  
            //����֮�����heightֵ  
            t.height = Math.max(height(t.left), height(t.right))+1;  
        }else if(t.left != null && t.right != null){  
            //Ĭ����������������С���ݴ���ýڵ�����ݲ��ݹ��ɾ���Ǹ��ڵ�  
            t.element = findMin(t.right).element;  
            t.right = remove(t.element, t.right);             
            if(t.right == null){ //��������ɾ����Ϊ�գ���ֻ���ж�����������ĸ߶Ȳ�  
                if(height(t.left)-t.height ==2){  
                    AvlNode<AnyType> k = t.left;  
                    if(k.left != null){  
                        System.out.println("-----------------------------------------------------------------------------ddddd");  
                        t = rotateWithLeftChild(t);  
                    }else{  
                        System.out.println("-----------------------------------------------------------------------------eeeee");  
                        t = doubleWithLeftChild(t);  
                    }  
                }                     
            }else{ //��������ɾ����ǿգ����ж����������ĸ߶Ȳ�  
                //����������Ҳ���ܲ�ƽ�⣬����ƽ�����������ٿ�������  
                AvlNode<AnyType> k = t.right;  
                //ɾ������Ĭ��������������С�ڵ㣨���󣩲�ɾ���Ľڵ�  
                  
                if(k.left != null){  
                    if(height(k.right)-height(k.left) == 2){  
                        AvlNode<AnyType> m = k.right;  
                        if(m.right != null){        //���������ڣ��������������ת  
                            System.out.println("-----------------------------------------------------------------------------fffff");  
                            k = rotateWithRightChild(k);  
                        }else{                      //���������������˫��ת                 
                            System.out.println("-----------------------------------------------------------------------------ggggg");  
                            k = doubleWithRightChild(k);  
                        }  
                    }     
                }else{  
                    if(height(k.right)-k.height == 2){  
                        AvlNode<AnyType> m = k.right;  
                        if(m.right != null){        //���������ڣ��������������ת  
                            System.out.println("-----------------------------------------------------------------------------hhhhh");  
                            k = rotateWithRightChild(k);  
                        }else{                      //���������������˫��ת                 
                            System.out.println("-----------------------------------------------------------------------------iiiii");  
                            k = doubleWithRightChild(k);  
                        }  
                    }     
                }  
                //����������һ����ƽ��ģ�����ʧ��Ļ�����ת���Խ������  
                if(height(t.left) - height(t.right) == 2){  
                    System.out.println("-----------------------------------------------------------------------------jjjjj");  
                    t = rotateWithLeftChild(t);           
                }  
            }  
            //����֮�����heightֵ  
            t.height = Math.max(height(t.left), height(t.right))+1;  
        }else{  
            System.out.println("-----------------------------------------------------------------------------kkkkk");  
            t = (t.left != null)?t.left:t.right;          
        }  
        return t;         
    }          
    
    //�����������ת  
    private AvlNode<AnyType> rotateWithLeftChild(AvlNode<AnyType> k2){  
        AvlNode<AnyType> k1 = k2.left;  
        k2.left = k1.right;       
        k1.right = k2;        
        k2.height = Math.max(height(k2.left), height(k2.right)) + 1;  
        k1.height = Math.max(height(k1.left), k2.height) + 1;         
        return k1;      //�����µĸ�  
    }  
    
    //�����������ת  
    private AvlNode<AnyType> rotateWithRightChild(AvlNode<AnyType> k2){  
        AvlNode<AnyType> k1 = k2.right;  
        k2.right = k1.left;  
        k1.left = k2;         
        k2.height = Math.max(height(k2.left), height(k2.right)) + 1;  
        k1.height = Math.max(height(k1.right), k2.height) + 1;        
        return k1;      //�����µĸ�   
    }     
    
    //�������  
    private AvlNode<AnyType> doubleWithLeftChild(AvlNode<AnyType> k3){        
        try{  
            k3.left = rotateWithRightChild(k3.left);  
        }catch(NullPointerException e){  
            System.out.println("k.left.rightΪ��"+k3.left.right);  
            throw e;  
        }  
        return rotateWithLeftChild(k3);       
    } 
    
    //�������  
    private AvlNode<AnyType> doubleWithRightChild(AvlNode<AnyType> k3){  
        try{  
            k3.right = rotateWithLeftChild(k3.right);  
        }catch(NullPointerException e){  
            System.out.println("k.right.leftΪ��"+k3.right.left);  
            throw e;  
        }         
        return rotateWithRightChild(k3);  
    }  
} 