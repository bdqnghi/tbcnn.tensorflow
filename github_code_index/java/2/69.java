/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/*
 * AVL��
 * ����BSTree������
 */

package dsa;

public class AVLTree extends BSTree implements Dictionary {
   /**************************** ���췽�� ****************************/
   public AVLTree() { super(); }
   public AVLTree(BinTreePosition r) { super(r); }
   public AVLTree(BinTreePosition r, Comparator c) { super(r, c); }

   /**************************** �ʵ䷽�������Ǹ���BSTree�� ****************************/
   //������Ŀ(key, value)�������ظ���Ŀ
   public Entry insert(Object key, Object value) {
      Entry e = super.insert(key, value);//���ø��෽����ɲ���
      root = rebalance(lastV.getParent(), root);//�Ӳ���ڵ�ĸ��׿�ʼ����ƽ�⻯
      return e;
   }

   //��ʵ��д�����keyΪ�ؼ������Ŀ����ժ�����е�һ�������أ����򣬷���null
   public Entry remove(Object key) {
      Entry e = super.remove(key);//���ø��෽�����ɾ��
      if (null != e) root = rebalance(lastV, root);//��ɾ���ڵ�ĸ��׿�ʼ����ƽ�⻯
      return e;
   }

   /**************************** �������� ****************************/
   //�ӽڵ�z��ʼ�����϶�������ƽ�⻯
   //���غ�root��Ϊƽ���ģ����ã����ĸ��ڵ�
   protected static BinTreePosition rebalance(BinTreePosition z, BinTreePosition r) {
      if (null == z) return r;
      while (true) {//��z��ʼ��������һ���z������
         if (!isBalanced(z))  rotate(z);//��z�ڵ�ʧȥƽ�⣬��ͨ����תʹ֮����ƽ��
         if (!z.hasParent())  return z;
         z = z.getParent();//��������丸��
      }//while
   }

   //�жϽڵ�v�Ƿ�ƽ��
   protected static boolean isBalanced(BinTreePosition v) {
      if (null == v) return true;
      int lH = (v.hasLChild()) ? (v.getLChild().getHeight()) : -1;
      int rH = (v.hasRChild()) ? (v.getRChild().getHeight()) : -1;
      int deltaH = lH - rH;
      return (-1 <= deltaH) && (deltaH <= 1);
   }

   //ͨ����ת��ʹ�ڵ�z��ƽ�����ӵľ���ֵ������1��֧��AVL����
   //�����µ�������
   public static BinTreePosition rotate(BinTreePosition z) {
      BinTreePosition   y = tallerChild(z);//ȡyΪz���ߵĺ���
      BinTreePosition   x = tallerChild(y);//ȡxΪy���ߵĺ���
      boolean cType = z.isLChild();//��¼��z�Ƿ�����
      BinTreePosition   p = z.getParent();//pΪz�ĸ���
      BinTreePosition   a, b, c;//�������ң������ڵ�
      BinTreePosition   t0, t1, t2, t3;//�������ң��Ŀ�����
      /******** ���·�������� ********/
      if (y.isLChild()) {//��y�����ӣ���
         c = z;   t3 = z.getRChild();
         if (x.isLChild()) {//��x������
            b = y;   t2 = y.getRChild();
            a = x;   t1 = x.getRChild();  t0 = (BSTreeNode)x.getLChild();
         } else {//��x���Һ���
            a = y;   t0 = y.getLChild();
            b = x;   t1 = x.getLChild();  t2 = (BSTreeNode)x.getRChild();
         }
      } else {//��y���Һ��ӣ���
         a = z;   t0 = z.getLChild();
         if (x.isRChild()) {//��x���Һ���
            b = y;   t1 = y.getLChild();
            c = x;   t2 = x.getLChild();  t3 = (BSTreeNode)x.getRChild();
         } else {//��x������
            c = y;   t3 = y.getRChild();
            b = x;   t1 = x.getLChild();  t2 = (BSTreeNode)x.getRChild();
         }
      }
      //ժ�������ڵ�
      z.secede();
      y.secede();
      x.secede();
      //ժ���Ŀ�����
      if (null != t0) t0.secede();
      if (null != t1) t1.secede();
      if (null != t2) t2.secede();
      if (null != t3) t3.secede();
      //��������
      a.attachL(t0); a.attachR(t1); b.attachL(a);
      c.attachL(t2); c.attachR(t3); b.attachR(c);
      //�������½���ԭ��
      if (null != p)
         if (cType)  p.attachL(b);
         else           p.attachR(b);
      return b;//�����µ�������
   }//rotate

   //���ؽڵ�p�ĺ����еĸ�����
   protected static BinTreePosition tallerChild(BinTreePosition v) {
      int   lH = v.hasLChild() ? v.getLChild().getHeight() : -1;
      int   rH = v.hasRChild() ? v.getRChild().getHeight() : -1;
      if (lH > rH)   return v.getLChild();
      if (lH < rH)   return v.getRChild();
      if (v.isLChild()) return v.getLChild();
      else                    return v.getRChild();
   }

   //���ؽڵ�p�ĺ����еĸ�����
   protected static BinTreePosition shorterChild(BinTreePosition v) {
      int   lH = v.hasLChild() ? v.getLChild().getHeight() : -1;
      int   rH = v.hasRChild() ? v.getRChild().getHeight() : -1;
      if (lH > rH)   return v.getRChild();
      if (lH < rH)   return v.getLChild();
      if (v.isLChild()) return v.getRChild();
      else                    return v.getLChild();
   }
}
