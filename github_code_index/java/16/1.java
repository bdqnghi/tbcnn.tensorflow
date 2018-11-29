package algo;

import com.euler.utils.FileUtilsEuler;
import com.euler.utils.sorting.QuickSort;
import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;

public class QuickSortNumber {

    private int[] numbers;

    @Test
    public void doTestFinal() throws IOException {
        init();
        FileUtilsEuler.fileName = "d:/temp/algo2.txt";
        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotFirst(0, QuickSort.result.length - 1);
        System.out.println("First " + QuickSort.countFirst);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotLastTest(0, QuickSort.result.length - 1);
        System.out.println("Last " + QuickSort.countLast);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotMediana(0, QuickSort.result.length - 1);
        System.out.println("Mediana " + QuickSort.countMedium);
    }

    //	@Test
    public void doTest3() throws IOException {
        init();
        FileUtilsEuler.fileName = "d:/temp/Samples/array3.txt";
        numbers = FileUtilsEuler.readFileList();
//		numbers = new int[]{2,3,4,5,6,8,1,7};
        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotFirst(0, numbers.length - 1);


        Assert.assertEquals(QuickSort.countFirst, 576);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotLastTest(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countLast, 669);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotMediana(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countMedium, 636);
        for (int i = 1; i < QuickSort.result.length; i++) {
            if (QuickSort.result[i - 1] > QuickSort.result[i]) {
                System.out.println("ERROR");
            }
        }


    }

    //	@Test
    public void doTest0() throws IOException {
        init();
        FileUtilsEuler.fileName = "d:/temp/Samples/array0.txt";
        numbers = FileUtilsEuler.readFileList();
//		numbers = new int[]{2,3,4,5,6,8,1,7};
        QuickSort.result = numbers;
        QuickSort.splitPivotFirst(0, numbers.length - 1);


        Assert.assertEquals(QuickSort.countFirst, 64);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotLastTest(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countLast, 60);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotMediana(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countMedium, 55);


    }

    //	@Test
    public void doTest1() throws IOException {
        init();
        FileUtilsEuler.fileName = "d:/temp/Samples/array1.txt";
        numbers = FileUtilsEuler.readFileList();
//		numbers = new int[]{2,3,4,5,6,8,1,7};
        QuickSort.result = numbers;
        QuickSort.splitPivotFirst(0, numbers.length - 1);


        Assert.assertEquals(QuickSort.countFirst, 253);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotLastTest(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countLast, 253);

        QuickSort.result = FileUtilsEuler.readFileList();
        QuickSort.splitPivotMediana(0, numbers.length - 1);
        Assert.assertEquals(QuickSort.countMedium, 66);


    }

    //	@Test
    public void doTestMediana() {
        int[] input = new int[20];
        Assert.assertEquals(QuickSort.getMediana(0, input.length - 1), 9);
        input = new int[5];
        Assert.assertEquals(QuickSort.getMediana(0, input.length - 1), 2);

        input = new int[2];
        Assert.assertEquals(QuickSort.getMediana(0, input.length - 1), 0);

        input = new int[3];
        Assert.assertEquals(QuickSort.getMediana(0, input.length - 1), 1);

        input = new int[9];
        Assert.assertEquals(QuickSort.getMediana(0, input.length - 1), 4);
    }

    public void init() {
        QuickSort.countFirst = 0;
        QuickSort.countLast = 0;
        QuickSort.countMedium = 0;
        QuickSort.result = new int[]{};
    }
}
