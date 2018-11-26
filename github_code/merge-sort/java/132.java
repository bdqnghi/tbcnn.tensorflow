

/**
 *
 * @author omerfarukkoc
 * 2.Mayıs.2016
 */


import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.Arrays;
import java.util.Random;


public class MergeSortForkJoin extends RecursiveAction{
    
    private double[] mergeSortDizi;
    private int mergeSortBaslamaIndisi;
    private int mergeSortDiziUzunlugu;
    private int mergeSortId;
    
    public MergeSortForkJoin (double[] dizi, int BaslamaIndisi, int DiziUzunlugu, int Id) {
        mergeSortDizi = dizi;
        mergeSortBaslamaIndisi = BaslamaIndisi;
        mergeSortDiziUzunlugu = DiziUzunlugu;
        this.mergeSortId = Id;
        System.out.println("Thread ID: "+ Id +"   Baslama İndisi: "+BaslamaIndisi+"   Uzunluk: "+DiziUzunlugu);
    }
    
    protected void blockSizeSonrasiOtomatikSiralama() {
        Arrays.sort(mergeSortDizi, mergeSortBaslamaIndisi, mergeSortBaslamaIndisi + mergeSortDiziUzunlugu);
    }
    
    @Override
    protected void compute() 
    {
        if (mergeSortDiziUzunlugu <= blockSize) 
        {
            //System.out.println("BlockSize Değerinden Düşüldü, Dizi Otomatik Sıralanıyor");
            blockSizeSonrasiOtomatikSiralama();
            return;
        }

        int bolunenDiziUzunlugu = mergeSortDiziUzunlugu / 2;
        MergeSortForkJoin thread1 = new MergeSortForkJoin(mergeSortDizi, mergeSortBaslamaIndisi, bolunenDiziUzunlugu, 2*mergeSortId);
        MergeSortForkJoin thread2 = new MergeSortForkJoin(mergeSortDizi, mergeSortBaslamaIndisi + bolunenDiziUzunlugu, mergeSortDiziUzunlugu - bolunenDiziUzunlugu, 2*mergeSortId+1);
        
        invokeAll(thread1, thread2);
        mergeSort(thread1.mergeSortBaslamaIndisi, thread2.mergeSortBaslamaIndisi, thread2.mergeSortBaslamaIndisi+thread2.mergeSortDiziUzunlugu);
    }
    
    
    public static Random rand = new Random();
        
        
    public static int diziBoyutu = 1000000;
    
    public static int cekirdekSayisi =  Runtime.getRuntime().availableProcessors();
    protected static int blockSize = (int)Math.ceil(diziBoyutu/(double)cekirdekSayisi);
    
    public static double normalMergeSortDizisi[] = new double[diziBoyutu];
    public static double javaMergeSortDizisi[] = new double[diziBoyutu];
    
    public static long javaMergeSortBaslamaZamani ;
    public static long javaMergeSortBitisZamani ;
    public static long javaMergeSortGecenZaman ;
    
    public static long normalMergeSortBaslamaZamani ;
    public static long normalMergeSortBitisZamani ;
    public static long normalMergeSortGecenZaman ;
        
    public static double mergeSortGeciciDizi[] = new double[diziBoyutu];
    
    public static void main(String[] args) throws Exception 
    {
        rand.setSeed(123456789);
        dizileriRandomDoldur();
        
        System.out.println("Toplam Taranan Elemen Sayısı - Dizi Boyutu: " + diziBoyutu);
        System.out.println();
        System.out.println("Çalışan Çekirdek Sayısı: " + cekirdekSayisi);
        System.out.println();
        System.out.println("Dizi Boyutu: " + normalMergeSortDizisi.length);
        System.out.println();
        
        javaMergeSortBaslamaZamani = System.currentTimeMillis();
        Arrays.sort(javaMergeSortDizisi);
        javaMergeSortBitisZamani = System.currentTimeMillis();
        javaMergeSortGecenZaman = javaMergeSortBitisZamani - javaMergeSortBaslamaZamani;
        System.out.println("Java Kütüphanesinin Merge Sort İçin Geçen Zamanı: " + javaMergeSortGecenZaman + " ms");
        System.out.println();
        
        MergeSortForkJoin MSFJ = new MergeSortForkJoin(normalMergeSortDizisi, 0, diziBoyutu, 1);
        ForkJoinPool FJP = new ForkJoinPool();
        
        normalMergeSortBaslamaZamani = System.currentTimeMillis();
        FJP.invoke(MSFJ);
        normalMergeSortBitisZamani = System.currentTimeMillis();
        normalMergeSortGecenZaman = normalMergeSortBitisZamani - normalMergeSortBaslamaZamani;
        System.out.println();
        System.out.println("Normal Merge Sort İçin Geçen Zaman: " + normalMergeSortGecenZaman + " ms");
        
        diziSiralimi();
        
        System.out.println();
        
        
        //System.out.println(normalMergeSortDizisi[1]);
    
    }
    
    public static void mergeSort(int thread1Indis, int thread2Indis, int last)
    {
        
        /*
        System.out.println("th1 indis"+thread1Indis);
        System.out.println("th2 indis"+thread2Indis);
        System.out.println("sonindis"+last);
        System.out.println();
        */
        
        
        
        int indis1 = thread1Indis;
        int indis2 = thread2Indis;
        int indis3 = thread1Indis;
        while(indis1<thread2Indis && indis2<last){
            if(normalMergeSortDizisi[indis1] < normalMergeSortDizisi[indis2]){
                mergeSortGeciciDizi[indis3] = normalMergeSortDizisi[indis1];
                indis1++;
                indis3++;
            }else{
                mergeSortGeciciDizi[indis3] = normalMergeSortDizisi[indis2];
                indis2++;
                indis3++;
            }
        }
        
        while(indis1<thread2Indis){
            mergeSortGeciciDizi[indis3++] = normalMergeSortDizisi[indis1++];
        }
        
        while(indis2<last){
            mergeSortGeciciDizi[indis3++] = normalMergeSortDizisi[indis2++];
        }
        
        for (int i = thread1Indis; i < last; i++) {
            normalMergeSortDizisi[i] = mergeSortGeciciDizi[i];
        }
    }
    
    public static void dizileriRandomDoldur() 
    {
        for (int j = 0; j < diziBoyutu; j++) {
            double randomSayi = rand.nextDouble();
            normalMergeSortDizisi[j] = randomSayi;
            javaMergeSortDizisi[j] = randomSayi;
        }
    }
    
    public static void diziSiralimi() 
    {
        for (int j = 0; j < diziBoyutu-1; j++) {
            if(normalMergeSortDizisi[j] > normalMergeSortDizisi[j+1])
            {
                System.out.println();
                System.out.println("--Dizi Sıralı Değil !!!--");
                System.out.println("Sıralı Olmayan İndisler Ve Elemanları Aşağıdadır.");
                System.out.println("Dizi Sıralı Değil !!!");
                System.out.println(j+ ": "+ normalMergeSortDizisi[j]);
                System.out.println((j+1)+ ": "+ normalMergeSortDizisi[j+1]);
                return;
            }
        }
        System.out.println();
        System.out.println("--Dizi Sıralıdır--");
    }
}
