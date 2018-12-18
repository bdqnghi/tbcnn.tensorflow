import java.io.Serializable;
import streamit.library.*;
import streamit.library.io.*;
import streamit.misc.StreamItRandom;
class Complex extends Structure implements Serializable {
  float real;
  float imag;
}
class RandomSource extends Filter 
{
  public static RandomSource __construct()
  {
    RandomSource __obj = new RandomSource();
    return __obj;
  }
  protected void callInit()
  {
    init();
  }
  int seed; 
  public void work() { 
    outputChannel.pushInt(seed); 
    seed = (((65793 * seed) + 4282663) % 8388608); 
  }
  public void init() { 
    seed = 0; 
    setIOTypes(Void.TYPE, Integer.TYPE); 
    addSteadyPhase(0, 0, 1, "work"); 
  }
}
class SortPipe extends Pipeline 
{
  private int __param_SIZE;
  private int __param_MAX_VALUE;
  public static SortPipe __construct(int SIZE, int MAX_VALUE)
  {
    SortPipe __obj = new SortPipe();
    __obj.__param_SIZE = SIZE;
    __obj.__param_MAX_VALUE = MAX_VALUE;
    return __obj;
  }
  protected void callInit()
  {
    init(__param_SIZE, __param_MAX_VALUE);
  }
  public void init(final int SIZE, final int MAX_VALUE) { 
    for (int i = 1; (i < MAX_VALUE); i = (i * 2)) { 
      add(Sort.__construct(SIZE, i)); 
    }; 
  }
}
class Sort extends Filter 
{
  private int __param__param_SIZE;
  private int __param__param_radix;
  public static Sort __construct(int _param_SIZE, int _param_radix)
  {
    Sort __obj = new Sort();
    __obj.__param__param_SIZE = _param_SIZE;
    __obj.__param__param_radix = _param_radix;
    return __obj;
  }
  protected void callInit()
  {
    init(__param__param_SIZE, __param__param_radix);
  }
  int SIZE; 
  int radix; 
  public void work() { 
    int[] ordering = new int[SIZE]; 
    int j = 0; 
    for (int i = 0; (i < SIZE); i++) { 
      int current; 
      current = inputChannel.popInt(); 
      if (((current & radix) == 0)) { 
        outputChannel.pushInt(current); 
      } else { 
        ordering[j] = current; 
        j = (j + 1); 
      } 
    }; 
    for (int i = 0; (i < j); i++) { 
      outputChannel.pushInt(ordering[i]); 
    }; 
  }
  public void init(final int _param_SIZE, final int _param_radix) { 
    SIZE = _param_SIZE; 
    radix = _param_radix; 
    setIOTypes(Integer.TYPE, Integer.TYPE); 
    addSteadyPhase(SIZE, SIZE, SIZE, "work"); 
  }
}
class IntSource extends Filter 
{
  private int __param__param_SIZE;
  public static IntSource __construct(int _param_SIZE)
  {
    IntSource __obj = new IntSource();
    __obj.__param__param_SIZE = _param_SIZE;
    return __obj;
  }
  protected void callInit()
  {
    init(__param__param_SIZE);
  }
  int[] data; 
  int index; 
  int SIZE; 
  public void work() { 
    outputChannel.pushInt(data[index++]); 
    if ((index == SIZE)) { 
      index = 0; 
    } 
  }
  public void init(final int _param_SIZE) { 
    SIZE = _param_SIZE; 
    data = new int[SIZE]; 
    index = 0; 
    setIOTypes(Void.TYPE, Integer.TYPE); 
    addSteadyPhase(0, 0, 1, "work"); 
    data[0] = 503; 
    data[1] = 87; 
    data[2] = 512; 
    data[3] = 61; 
    data[4] = 908; 
    data[5] = 170; 
    data[6] = 897; 
    data[7] = 275; 
    data[8] = 653; 
    data[9] = 426; 
    data[10] = 154; 
    data[11] = 509; 
    data[12] = 612; 
    data[13] = 677; 
    data[14] = 765; 
    data[15] = 703; 
  }
}
class IntPrinter extends Filter 
{
  public static IntPrinter __construct()
  {
    IntPrinter __obj = new IntPrinter();
    return __obj;
  }
  protected void callInit()
  {
    init();
  }
  int x; 
  public void work() { 
    x = inputChannel.popInt(); 
    System.out.println(x); 
  }
  public void init() { 
    setIOTypes(Integer.TYPE, Void.TYPE); 
    addSteadyPhase(1, 1, 0, "work"); 
  }
}
public class RadixSort extends StreamItPipeline 
{
  public void init() { 
    int SIZE = 16; 
    int MAX_VALUE = 2048; 
    add(RandomSource.__construct()); 
    add(SortPipe.__construct(SIZE, MAX_VALUE)); 
    add(IntPrinter.__construct()); 
  }
  public static void main(String[] args) {
    RadixSort program = new RadixSort();
    program.run(args);
    FileWriter.closeAll();
  }
}
