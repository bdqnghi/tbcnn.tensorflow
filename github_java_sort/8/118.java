
class Quicksort extends Geracao {

	
   public Quicksort(){
      super();
   }


	
   public Quicksort(int tamanho){
      super(tamanho);
   }


	
	public static void quicksort() {
      quicksort(0, n-1);
   }

	
    private static void quicksort(int esq, int dir) {
        int i = esq, j = dir;
        int pivo = array[(dir+esq)/2];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(esq, j);
        if (i < dir)  quicksort(i, dir);
    }
 

	public static void main(String[] args) throws Exception {
      Quicksort quicksort = new Quicksort(10000000);
		quicksort.aleatorio();
		
		
		long comeco = now();
		quicksort.quicksort();
		long fim = now();

		
		System.out.println("Tempo para ordenar: " + (fim-comeco)/1000.0 + " s.");
	}
}
