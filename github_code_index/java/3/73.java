class TowerOfHanoi {
   static void Hanoi(int size, String source, String destination, String transit) {
      if (size == 1) {
         System.out.println("Move from " + source + " to " + destination);
      } else {
         Hanoi(size-1, source, transit, destination);
         System.out.println("Move from " + source + " to " + destination);
         Hanoi(size-1, transit, destination, source);
      }
   }

   public static void main(String[] args) {
      if (args.length != 0) {
         int size = Integer.parseInt(args[0]);
         Hanoi(size, "source", "destination", "transit");
      }
   }
}
