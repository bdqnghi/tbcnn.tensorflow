/**
 * @author JUNGHYUN KIM
 * @version 1.0
 */

import java.util.ArrayList;
import java.util.NoSuchElementException;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;


public class AVLStudentKIM {
    private static final int TIMEOUT = 200;
    private AVL<Integer> avlTree;

    @Before
    public void setup() {
        avlTree = new AVL<>();
    }
    //1
    @Test(timeout = TIMEOUT)
    public void ConstructorTest_null() {
        assertNull(avlTree.getRoot());
        assertEquals(0, avlTree.size());
    }
    //2
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void add_illegal() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.add(null);
    }
    //3
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void remove_illegal() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.remove(null);
    }
    //4
    @Test(timeout = TIMEOUT, expected = java.util.NoSuchElementException.class)
    public void remove_not_found() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.remove(2);
    }
    //5
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void get_illegal() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.get(null);
    }
    //6
    @Test(timeout = TIMEOUT, expected = java.util.NoSuchElementException.class)
    public void get_not_found() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.get(2);
    }
    //7
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void contains_illegal() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        avlTree.contains(null);
    }
    //8
    @Test(timeout = TIMEOUT)
    public void contains_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(0);
        avlTree.add(3);
        assertTrue(avlTree.contains(0));
        assertTrue(avlTree.contains(3));
        assertFalse(avlTree.contains(2));
    }
    //9
    @Test(timeout = TIMEOUT)
    public void size_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        for(int i = 0; i < 100; i++) {
            for(int j = 1; j <= 3; j++) {
                avlTree.add(i);
            }
        }
        assertEquals((Integer) 100, (Integer) avlTree.size());
    }
    //10
    @Test(timeout = TIMEOUT)
    public void size_test_with_remove() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        for(int i = 0; i < 100; i++) {
            for(int j = 1; j <= 3; j++) {
                avlTree.add(i);
            }
        }
        for(int i = 1; i < 100; i += 2) {
            avlTree.remove(i);
        }
        assertEquals((Integer)50, (Integer)avlTree.size());
    }
    //11
    @Test(timeout = TIMEOUT)
    public void clear_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.clear();
        assertEquals(null, avlTree.getRoot());
        assertEquals((Integer)0, (Integer) avlTree.size());
    }
    //12
    @Test(timeout = TIMEOUT, expected = java.util.NoSuchElementException.class)
    public void repetition_check_1() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        for(int i = 0; i < 100; i++) {
            for(int j = 1; j <= 3; j++) {
                avlTree.add(i);
            }
        }
        avlTree.remove(31);
        avlTree.remove(31);
    }
    //13
    @Test(timeout = TIMEOUT)
    public void case13() {
        //left-left-only
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(5);
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getHeight());

        avlTree.add(4);
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer)4, (Integer)avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());

        avlTree.add(3);
        assertEquals((Integer)4, (Integer)avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer)3, (Integer)avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        avlTree.add(2);
        assertEquals((Integer)4, (Integer)avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());
        assertEquals((Integer)3, (Integer)avlTree.getRoot().getLeft().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer)2, (Integer)avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        avlTree.add(1);
        assertEquals((Integer)4, (Integer)avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());
        assertEquals((Integer)2, (Integer)avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer)1, (Integer)avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());
        assertEquals((Integer)3, (Integer)avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        assertEquals(2, avlTree.height());
        assertEquals(5, avlTree.size());
    }
    //14
    @Test(timeout = TIMEOUT)
    public void case14() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(5);
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getHeight());
        assertEquals(1, avlTree.size());

        avlTree.add(4);
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer) 4, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());
        assertEquals(2, avlTree.size());

        avlTree.add(3);
        assertEquals((Integer) 4, (Integer) avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer) 3, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());
        assertEquals(3, avlTree.size());

        avlTree.add(2);
        assertEquals((Integer) 4, (Integer) avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());
        assertEquals((Integer) 3, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer) 2, (Integer) avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());
        assertEquals(4, avlTree.size());

        avlTree.add(1);
        assertEquals((Integer) 4, (Integer) avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());
        assertEquals((Integer) 2, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer) 1, (Integer) avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());
        assertEquals((Integer) 3, (Integer) avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());
        assertEquals((Integer)5, (Integer)avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        assertEquals(2, avlTree.height());
        assertEquals(5, avlTree.size());

        avlTree.remove(2);

        assertEquals(4, avlTree.size());
        assertEquals((Integer) 4, (Integer) avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());
        assertEquals((Integer) 1, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer) 3, (Integer) avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        avlTree.remove(4);

        assertEquals(3, avlTree.size());
        assertEquals((Integer) 3, (Integer) avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer) 1, (Integer) avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        avlTree.remove(3);

        assertEquals(2, avlTree.size());
        assertEquals((Integer) 1, (Integer) avlTree.getRoot().getData());
        assertEquals(-1, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());
        assertEquals((Integer) 5, (Integer) avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

        avlTree.remove(5);

        assertEquals(1, avlTree.size());
        assertEquals((Integer) 1, (Integer) avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getHeight());

        avlTree.remove(1);
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
    }
    //15
    @Test(timeout = TIMEOUT)
    public void case15() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());
        avlTree.add(4);
        avlTree.add(2);
        avlTree.add(6);
        avlTree.add(5);
        avlTree.add(7);
        avlTree.add(3);

        assertEquals((Integer) 4, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());

        assertEquals((Integer) 2, avlTree.getRoot().getLeft().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 3, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());

        assertEquals((Integer) 6, avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer) 5, avlTree.getRoot().getRight().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getRight().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getLeft().getHeight());

        assertEquals((Integer) 7, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());

        avlTree.add(1);

    }
    //16
    @Test(timeout = TIMEOUT)
    public void case16() {
        //left-right
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(4);
        avlTree.add(2);
        avlTree.add(3);

        assertEquals((Integer) 3, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());

        assertEquals((Integer) 2, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer)4, avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

    }

    //17
    @Test(timeout = TIMEOUT)
    public void case17() {
        //right-right
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(5);
        avlTree.add(6);
        avlTree.add(7);

        assertEquals((Integer) 6, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());

        assertEquals((Integer) 5, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer)7, avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

    }
    //18
    @Test(timeout = TIMEOUT)
    public void case18() {
        //right-left
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(6);
        avlTree.add(8);
        avlTree.add(7);

        assertEquals((Integer) 7, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getHeight());

        assertEquals((Integer) 6, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer)8, avlTree.getRoot().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getHeight());

    }

    //19
    @Test(timeout = TIMEOUT)
    public void case19() {
        //right-right(remove)
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(25);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(12);
        avlTree.add(27);
        avlTree.add(30);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(3, avlTree.getRoot().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 12, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 27, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getRight().getHeight());

        assertEquals((Integer) 30, avlTree.getRoot().getLeft().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getRight().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer)85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());

        avlTree.remove(12);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());

        assertEquals((Integer) 27, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 30, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer)85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());
    }
    //20
    @Test(timeout = TIMEOUT)
    public void case20() {
        //right-left(remove)
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(25);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(12);
        avlTree.add(27);
        avlTree.add(26);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(3, avlTree.getRoot().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 12, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 27, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getRight().getHeight());

        assertEquals((Integer) 26, avlTree.getRoot().getLeft().getRight().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getLeft().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer) 85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());

        avlTree.remove(12);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());

        assertEquals((Integer) 26, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 27, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer)85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());
    }
    //21
    @Test(timeout = TIMEOUT)
    public void case21() {
        //left-left(remove)
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(25);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(26);
        avlTree.add(23);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(3, avlTree.getRoot().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 24, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 23, avlTree.getRoot().getLeft().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getLeft().getHeight());

        assertEquals((Integer) 26, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());

        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer) 85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());

        avlTree.remove(26);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());

        assertEquals((Integer) 24, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 23, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer)85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());
    }
    //22
    @Test(timeout = TIMEOUT)
    public void case22() {
        //left-right(remove)
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(26);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(27);
        avlTree.add(25);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(1, avlTree.getRoot().getBalanceFactor());
        assertEquals(3, avlTree.getRoot().getHeight());

        assertEquals((Integer) 26, avlTree.getRoot().getLeft().getData());
        assertEquals(1, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 24, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(-1, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getRight().getHeight());

        assertEquals((Integer) 27, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());

        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer) 85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());

        avlTree.remove(27);

        assertEquals((Integer) 50, avlTree.getRoot().getData());
        assertEquals(0, avlTree.getRoot().getBalanceFactor());
        assertEquals(2, avlTree.getRoot().getHeight());

        assertEquals((Integer) 25, avlTree.getRoot().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getLeft().getHeight());

        assertEquals((Integer) 24, avlTree.getRoot().getLeft().getLeft().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getLeft().getHeight());

        assertEquals((Integer) 26, avlTree.getRoot().getLeft().getRight().getData());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getLeft().getRight().getHeight());


        assertEquals((Integer)75, avlTree.getRoot().getRight().getData());
        assertEquals(-1, avlTree.getRoot().getRight().getBalanceFactor());
        assertEquals(1, avlTree.getRoot().getRight().getHeight());

        assertEquals((Integer)85, avlTree.getRoot().getRight().getRight().getData());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getBalanceFactor());
        assertEquals(0, avlTree.getRoot().getRight().getRight().getHeight());
    }
    //23
    @Test(timeout = TIMEOUT, expected = IllegalArgumentException.class)
    public void depth_illegal() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(26);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(27);
        avlTree.add(25);
        avlTree.remove(27);
        avlTree.depth(null);
    }
    //24
    @Test(timeout = TIMEOUT, expected = java.util.NoSuchElementException.class)
    public void depth_not_found() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(26);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(27);
        avlTree.add(25);
        avlTree.remove(27);
        avlTree.depth(27);
    }
    //25
    @Test(timeout = TIMEOUT)
    public void depth_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(26);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(27);
        avlTree.add(25);
        avlTree.remove(27);
        assertEquals(1, avlTree.depth(50));
        assertEquals(2, avlTree.depth(25));
        assertEquals(3, avlTree.depth(24));
        assertEquals(3, avlTree.depth(26));
        assertEquals(2, avlTree.depth(75));
        assertEquals(3, avlTree.depth(85));
    }
    //26
    @Test(timeout = TIMEOUT)
    public void height_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(50);
        avlTree.add(26);
        avlTree.add(75);
        avlTree.add(85);
        avlTree.add(24);
        avlTree.add(27);
        avlTree.add(25);
        assertEquals(3, avlTree.height());
        avlTree.remove(27);
        assertEquals(2, avlTree.height());
    }

    //27
    @Test(timeout = TIMEOUT)
    public void pre_order_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(46);
        avlTree.add(34);
        avlTree.add(57);
        avlTree.add(44);
        avlTree.add(87);
        avlTree.add(53);
        avlTree.add(22);
        avlTree.add(8);
        avlTree.add(86);
        avlTree.add(1);
        assertEquals(3, avlTree.height());

        ArrayList<Integer> arr = new ArrayList<>();
        arr.add(46);
        arr.add(34);
        arr.add(8);
        arr.add(1);
        arr.add(22);
        arr.add(44);
        arr.add(57);
        arr.add(53);
        arr.add(87);
        arr.add(86);
        assertEquals(arr, avlTree.preorder());

        avlTree.remove(34);
        avlTree.remove(44);

        ArrayList<Integer> arr2 = new ArrayList<>();
        arr2.add(46);
        arr2.add(8);
        arr2.add(1);
        arr2.add(22);
        arr2.add(57);
        arr2.add(53);
        arr2.add(87);
        arr2.add(86);
        assertEquals(arr2, avlTree.preorder());
    }

    //28
    @Test(timeout = TIMEOUT)
    public void in_order_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(46);
        avlTree.add(34);
        avlTree.add(57);
        avlTree.add(44);
        avlTree.add(87);
        avlTree.add(53);
        avlTree.add(22);
        avlTree.add(8);
        avlTree.add(86);
        avlTree.add(1);
        assertEquals(3, avlTree.height());

        ArrayList<Integer> arr = new ArrayList<>();
        arr.add(1);
        arr.add(8);
        arr.add(22);
        arr.add(34);
        arr.add(44);
        arr.add(46);
        arr.add(53);
        arr.add(57);
        arr.add(86);
        arr.add(87);
        assertEquals(arr, avlTree.inorder());

        avlTree.remove(34);
        avlTree.remove(44);

        ArrayList<Integer> arr2 = new ArrayList<>();
        arr2.add(1);
        arr2.add(8);
        arr2.add(22);
        arr2.add(46);
        arr2.add(53);
        arr2.add(57);
        arr2.add(86);
        arr2.add(87);
        assertEquals(arr2, avlTree.inorder());
    }

    //29
    @Test(timeout = TIMEOUT)
    public void post_order_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(46);
        avlTree.add(34);
        avlTree.add(57);
        avlTree.add(44);
        avlTree.add(87);
        avlTree.add(53);
        avlTree.add(22);
        avlTree.add(8);
        avlTree.add(86);
        avlTree.add(1);
        assertEquals(3, avlTree.height());

        ArrayList<Integer> arr = new ArrayList<>();
        arr.add(1);
        arr.add(22);
        arr.add(8);
        arr.add(44);
        arr.add(34);
        arr.add(53);
        arr.add(86);
        arr.add(87);
        arr.add(57);
        arr.add(46);
        assertEquals(arr, avlTree.postorder());

        avlTree.remove(34);
        avlTree.remove(44);

        ArrayList<Integer> arr2 = new ArrayList<>();
        arr2.add(1);
        arr2.add(22);
        arr2.add(8);
        arr2.add(53);
        arr2.add(86);
        arr2.add(87);
        arr2.add(57);
        arr2.add(46);
        assertEquals(arr2, avlTree.postorder());
    }
    //30
    @Test(timeout = TIMEOUT)
    public void bfs_test() {
        assertEquals(0, avlTree.size());
        assertEquals(-1, avlTree.height());

        avlTree.add(46);
        avlTree.add(34);
        avlTree.add(57);
        avlTree.add(44);
        avlTree.add(87);
        avlTree.add(53);
        avlTree.add(22);
        avlTree.add(8);
        avlTree.add(86);
        avlTree.add(1);
        assertEquals(3, avlTree.height());

        ArrayList<Integer> arr = new ArrayList<>();
        arr.add(46);
        arr.add(34);
        arr.add(57);
        arr.add(8);
        arr.add(44);
        arr.add(53);
        arr.add(87);
        arr.add(1);
        arr.add(22);
        arr.add(86);
        assertEquals(arr, avlTree.levelorder());

        avlTree.remove(34);
        avlTree.remove(44);

        ArrayList<Integer> arr2 = new ArrayList<>();
        arr2.add(46);
        arr2.add(8);
        arr2.add(57);
        arr2.add(1);
        arr2.add(22);
        arr2.add(53);
        arr2.add(87);
        arr2.add(86);
        assertEquals(arr2, avlTree.levelorder());
    }
    /*
    ����(��)
     */
}