



import java.util.*;
public class Principal {
	public static void shellSortMarca(Automovil A[], int numAle){
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ 
				cambios=false;
				for(j=salto; j< numAle; j++) 
					if((A[j-salto].getMarca().compareTo(A[j].getMarca()))>0){ 
						aux=A[j]; 
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; 
					}
			}
		}
	}
	public static void shellSortModelo(Automovil A[], int numAle){
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ 
				cambios=false;
				for(j=salto; j< numAle; j++) 
					if((A[j-salto].getModelo().compareTo(A[j].getModelo()))>0){ 
						aux=A[j]; 
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; 
					}
			}
		}
	}
	public static void shellSortPrecio(Automovil A[], int numAle){
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ 
				cambios=false;
				for(j=salto; j< numAle; j++) 
					if(A[j-salto].getPrecio()>A[j].getPrecio()){ 
						aux=A[j]; 
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; 
					}
			}
		}
	}
	public static void shellSortCilindrada(Automovil A[], int numAle){
		int salto, j;
		Automovil aux;
		boolean cambios;
		for(salto=numAle/2; salto!=0; salto/=2){
			cambios=true;
			while(cambios==true){ 
				cambios=false;
				for(j=salto; j< numAle; j++) 
					if(A[j-salto].getCilindrada()>A[j].getCilindrada()){ 
						aux=A[j]; 
						A[j]=A[j-salto];
						A[j-salto]=aux;
						cambios=true; 
					}
			}
		}
	}

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

		numAleatorio = azar.nextInt(5000)+1;
		Automovil coche[]= new Automovil[5000];

		for(i=0;i<numAleatorio;i++){
			aleatorioMarcas=azar.nextInt(marcas.length);
			aleatorioModelos=azar.nextInt(modelos.length);
			aleatorioCilindrada=azar.nextInt(cilindrada.length);
			aleatorioPrecio=azar.nextInt(90000)+10000;
			precio=aleatorioPrecio;
			coche[i]=new Automovil(marcas[aleatorioMarcas],modelos[aleatorioModelos], cilindrada[aleatorioCilindrada], precio);
		}

		opcionMenu='x';
		while(!(opcionMenu=='0')){
			System.out.println("Hay: "+numAleatorio+" Coches");
			System.out.println("Introduzca una de las siguientes opciones: ");
			System.out.println("A - Ordenar por marca.");
			System.out.println("B - Ordenar por modelo.");
			System.out.println("C - Ordenar por cilindrada.");
			System.out.println("D - Ordenar por precio.");
			System.out.println("0 - Salir.");
			opcionMenu=teclado.next().toUpperCase().charAt(0);
			while(!(opcionMenu=='A'||opcionMenu=='B'||opcionMenu=='C'||opcionMenu=='D'||opcionMenu=='0')){
				System.out.println("Introduzca CORRECTAMENTE una de las siguientes opciones: ");
				System.out.println("A - Ordenar por marca.");
				System.out.println("B - Ordenar por modelo.");
				System.out.println("C - Ordenar por cilindrada.");
				System.out.println("D - Ordenar por precio.");
				System.out.println("0 - Salir.");
				opcionMenu=teclado.next().toUpperCase().charAt(0);
			}
			switch (opcionMenu){
			case 'A':
				shellSortMarca(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'B':
				shellSortModelo(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'C':
				shellSortCilindrada(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			case 'D':
				shellSortPrecio(coche, numAleatorio);
				for(i=0;i<numAleatorio;i++){
					System.out.println(coche[i].getMarca()+" "+coche[i].getModelo()+" "+coche[i].getCilindrada()+"cc."+" "+coche[i].getPrecio()+"€");
				}
				break;
			}
		}
	}

}