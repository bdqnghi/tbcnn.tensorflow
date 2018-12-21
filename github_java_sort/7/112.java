

class Shellsort extends Geracao {

   
   public Shellsort(){
      super();
   }


   
   public Shellsort(int tamanho){
      super(tamanho);
   }


   
   public static void shellsort() {
      int h = 1;

      do { h = (h * 3) + 1; } while (h < n);

      do {
         h /= 3;
         for(int cor = 0; cor < h; cor++){
            insercaoPorCor(cor, h);
         }
      } while (h != 1);
   }


   
   public static void insercaoPorCor(int cor, int h){
      for (int i = (h + cor); i < n; i+=h) {
         int tmp = array[i];
         int j = i - h;
         while ((j >= 0) && (array[j] > tmp)) {
            array[j + h] = array[j];
            j-=h;
         }
         array[j + h] = tmp;
      }
   }


   public static void main(String[] args) {
      Shellsort shellsort = new Shellsort(100000000);
      shellsort.aleatorio();
      

      long comeco = now();
      shellsort.shellsort();
      long fim = now();

      
      System.out.println("Tempo para ordenar: " + (fim-comeco)/1000.0 + " s.");
   }
}
