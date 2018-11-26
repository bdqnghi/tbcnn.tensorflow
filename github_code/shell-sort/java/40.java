//Autores: Jaime Clemente Carbonel y Oscar Portillo.

/*Sea la clase Automovil con los siguientes atributos
		- A-marca (String)
		- B-modelo (String)
		- C-cilindrada (int)
		- D-precio (int)
	A partir de aquí instanciaremos un vector de 5000 automóviles (objetos)
	Desarrollar la clase correspondiente para implementarlo con los siguientes métodos:
	- Método que se le pasa el vector y un tamaño n menor que 5000 y genera n automóviles aleatoriamente (lo
		usaremos para tener datos).
	- Método que se le pasa el vector de objetos y un letra (A,..,D) filtrada por supuesto, y ordena los objetos que
		existan en el vector (que no tienen por qué ser 5000) por el campo elegido donde cada letra representa el
		atributo correspondiente.
	- NOTA: para ordenar buscad un método de ordenación usad burbuja, inserción directa ó shell-sort este
		último es el más rápido de todos con diferencia.*/

import java.util.*;
public class Principal {
	public static void shellSortMarca(Automovil A[], int numAle){//pasamos el vector de objetos Automovil y el número aleatorio 
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ // Mientras se intercambie algún elemento
				cambios=false;
				for(j=salto; j< numAle; j++) // se da una pasada
					if((A[j-salto].getMarca().compareTo(A[j].getMarca()))>0){ // y si están desordenados
						aux=A[j]; // se reordenan
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; // y se marca como cambio.
					}
			}
		}
	}//shellSortMarca
	public static void shellSortModelo(Automovil A[], int numAle){//pasamos el vector de objetos Automovil y el número aleatorio
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ // Mientras se intercambie algún elemento
				cambios=false;
				for(j=salto; j< numAle; j++) // se da una pasada
					if((A[j-salto].getModelo().compareTo(A[j].getModelo()))>0){ // y si están desordenados
						aux=A[j]; // se reordenan
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; // y se marca como cambio.
					}
			}
		}
	}//shellSortModelo
	public static void shellSortPrecio(Automovil A[], int numAle){//pasamos el vector de objetos Automovil y el número aleatorio
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ // Mientras se intercambie algún elemento
				cambios=false;
				for(j=salto; j< numAle; j++) // se da una pasada
					if(A[j-salto].getPrecio()>A[j].getPrecio()){ // y si están desordenados
						aux=A[j]; // se reordenan
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; // y se marca como cambio.
					}
			}
		}
	}//shellSortPrecio
	public static void shellSortCilindrada(Automovil A[], int numAle){//pasamos el vector de objetos Automovil y el número aleatorio
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ // Mientras se intercambie algún elemento
				cambios=false;
				for(j=salto; j< numAle; j++) // se da una pasada
					if(A[j-salto].getCilindrada()>A[j].getCilindrada()){ // y si están desordenados
						aux=A[j]; // se reordenan
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; // y se marca como cambio.
					}
			}
		}
	}//shellSortCilindrada

	public static void main(String[] args) {
		Random azar = new Random();
		@SuppressWarnings("resource")
		Scanner teclado= new Scanner(System.in);
		String marcas[]={"Opel", "Ford", "Chevrolet", "Nissan", "Jaguar", "Renault", "Audi", "BMW", "Toyota", "Suzuki", "Citroen","Mini", "Jeep", "Mazda", "Mercedes", "Mitsubishi"};
		String modelos[]={"Modelo1", "Modelo2", "Modelo3", "Modelo4"};
		int cilindrada[]={100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};
		int precio;
		int numAleatorio, aleatorioMarcas, aleatorioModelos, aleatorioCilindrada, aleatorioPrecio, i;
		char opcionMenu;

		numAleatorio = azar.nextInt(5000)+1;//número aleatorio que usaré despues para crear x objetos de Automovil
		Automovil coche[]= new Automovil[5000];//busco en memoria el espacio para crear 5000 objetos de Automovil

		for(i=0;i<numAleatorio;i++){//creamos cada objeto de Automovil con valores aleatorios :)
			aleatorioMarcas=azar.nextInt(marcas.length);
			aleatorioModelos=azar.nextInt(modelos.length);
			aleatorioCilindrada=azar.nextInt(cilindrada.length);
			aleatorioPrecio=azar.nextInt(90000)+10000;
			precio=aleatorioPrecio;
			coche[i]=new Automovil(marcas[aleatorioMarcas],modelos[aleatorioModelos], cilindrada[aleatorioCilindrada], precio);//creo el objeto de Automovil con la posición i y le asigno sus valores aleatorios
		}

		opcionMenu='x';
		while(!(opcionMenu=='0')){//cuando me dan 0, salgo del menú y termina el programa :)
			System.out.println("Hay: "+numAleatorio+" Coches");//imprimo el número de coches creados
			System.out.println("Introduzca una de las siguientes opciones: ");
			System.out.println("A - Ordenar por marca.");
			System.out.println("B - Ordenar por modelo.");
			System.out.println("C - Ordenar por cilindrada.");
			System.out.println("D - Ordenar por precio.");
			System.out.println("0 - Salir.");
			opcionMenu=teclado.next().toUpperCase().charAt(0);//recojo el carácter como string, lo paso a mayúsculas y cojo sólo el primer carácter
			while(!(opcionMenu=='A'||opcionMenu=='B'||opcionMenu=='C'||opcionMenu=='D'||opcionMenu=='0')){//Obligo a que me den una opción correcta :)
				System.out.println("Introduzca CORRECTAMENTE una de las siguientes opciones: ");
				System.out.println("A - Ordenar por marca.");
				System.out.println("B - Ordenar por modelo.");
				System.out.println("C - Ordenar por cilindrada.");
				System.out.println("D - Ordenar por precio.");
				System.out.println("0 - Salir.");
				opcionMenu=teclado.next().toUpperCase().charAt(0);
			}//sigue el programa con una opción válida
			switch (opcionMenu){//seleccionamos la opción introducida en el menú, dependiendo de qué opcion se ha elegido irá a un case y cada case hará su método :)
			case 'A'://case A, ordena por marca
				shellSortMarca(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){//visualizamos todos los coches :)
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'B'://case B, ordena por modelo
				shellSortModelo(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){//visualizamos todos los coches :)
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'C'://case C, ordena por cilindrada
				shellSortCilindrada(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){//visualizamos todos los coches :)
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'D'://case D, ordena por precio
				shellSortPrecio(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){//visualizamos todos los coches :)
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			}
		}//finWhileMenu
	}//main

}//class