package unidad1_alumnos;

import java.util.Scanner;

public class Principal {
	
	private Alumnos[] a;
	private int n, opc;
	private String numControl;
	private IngresarAlumnos ia = new IngresarAlumnos();
	private BusqSecuencial bs = new BusqSecuencial();
	private BuscBin bb = new BuscBin();
	private Burbuja bj = new Burbuja();
	private Quicksort qs = new Quicksort();
	private Mergesort ms = new Mergesort();
	private Shellsort ss = new Shellsort();
	
	public void imprimir(Alumnos [] a){
		for(int i=0; i< a.length;i++){
			System.out.println(a[i].toString()+"\n");
		}
		
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Scanner leer = new Scanner(System.in);
		Principal p = new Principal();
		
		System.out.print("Tama�o del arreglo: ");
		p.n = leer.nextInt();
		
		p.a = new Alumnos[p.n];
		
		p.ia.ingresar(p.n, p.a);
		
		p.opc = 0;
		
		while(p.opc!=8){
			System.out.println("----------- MENU DE OPCIONES -----------");
			System.out.println("\t1. B�squeda secuencial"
					+ "\n\t2. B�squeda binaria"
					+ "\n\t3. Ordenamiento BubbleSort"
					+ "\n\t4. Ordenamiento QuickSort"
					+ "\n\t5. Ordenamiento MergeSort"
					+ "\n\t6. Ordenamiento Shell-Sort"
					+ "\n\t7. Imprimir base de datos"
					+ "\n\t8. Salir"
					+ "\nSeleccione una opcion del menu:");
			
			p.opc = leer.nextInt();			
			
			switch (p.opc) {
				case 1:
					System.out.print("Ingresa el numero de control a buscar: ");
					p.numControl = leer.next();
					
					if(p.bs.buscar(p.numControl, p.a))
						System.out.println("Dato encontrado");
					else
						System.out.println("No existe el dato buscado");
					
					break;
					
				case 2:					
					System.out.print("Ingresa el numero de control a buscar: ");
					p.numControl = leer.next();
					
					if(p.bb.buscar(p.a, 0, p.a.length-1, p.numControl))

						System.out.println("Dato encontrado");
					else
						System.out.println("No existe el dato buscado");
					break;
				case 3: 
					/*System.out.println("Arreglo original: ");
					p.imprimir(p.a);
					
					System.out.println("--------------------------------");*/
					if(p.bj.ordenarB(p.a)){
						System.out.println("El arreglo fue ordenado");
						//p.imprimir(p.a);
					} else 
						System.out.println("El arreglo no fue ordenado");
					
					break;
				case 4:
					if(p.qs.ordenar(p.a, 0, p.a.length-1))
						System.out.println("El arreglo fue ordenado");
					else
						System.out.println("El arreglo no fue ordenado");
					break;
				case 5:
					if(p.ms.separar(p.a, 0, p.a.length-1))
						System.out.println("El arreglo fue ordenado");
					else
						System.out.println("El arreglo no fue ordenado");
					break;
				case 6:
					if(p.ss.ordenar(p.a))
						System.out.println("El arreglo fue ordenado");
					else
						System.out.println("El arreglo no fue ordenado");
					break;
				case 7:
					p.imprimir(p.a);
					break;
				case 8:
					System.out.println("Adios :3");
					break;
				default:
					System.out.println("Selecciona una opcion correcta");
			}
		}
		
		
		
		
		/*System.out.println(p.a[0]);
		System.out.println(p.a[1]);
		System.out.println(p.a[0].compareTo(p.a[1]));
		System.out.println(p.a[1].compareTo(p.a[0]));*/
	}

}
