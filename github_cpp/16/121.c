







#include "vo/common_types.hpp"
#include "vo/dni.hpp"
#include "vo/insercion.hpp"
#include "vo/burbuja.hpp"
#include "vo/heap_sort.hpp"
#include "vo/quicksort.hpp"
#include "vo/shellsort.hpp"

using namespace std;

int main() {
	int opcion = 0, tam_vec = 0, modo = 0;
	double alfa = 0.0;

	cout << "*" << setfill('-') << setw(57) << "*" << endl;
	cout << "| PRACTICA 5: IMPLEMENTACIÓN DE MÉTODOS DE ORDENACIÓN" << setfill(' ') << setw(5) << "|" << endl;
	cout << "| Autor: David Dorta Acosta" << setfill(' ') << setw (31) << "|" << endl;
	cout << "| email: alu0100851236@ull.edu.es" << setfill(' ') << setw(25) << "|" << endl;
	cout << "| fecha entrega: 18 abril 2018" << setfill(' ') << setw(28) << "|" << endl;
	cout << "*" << setfill('-') << setw(57) << "*" << endl << endl;

    do{
    		cout << endl << "*" << setfill('-') << setw(26) << "*" << endl;
    		cout << "|  MODOS DE UTILIZACIÓN" << setfill(' ') << setw (4) << "|" << endl;
    		cout << "| ----------------------- |" << endl;
    		cout << "|  1. Modo Demostración" << setfill(' ') << setw (4) << "|" << endl;
    		cout << "|  2. Modo Estadística" << setfill(' ') << setw (5) << "|" << endl;
    		cout << "|  0. Salir" << setfill(' ') << setw (16) << "|" << endl;
    		cout << "*" << setfill('-') << setw(26) << "*" << endl;

    		cout << "Seleccione un modo de utilización: ";
    		cin >> modo;

    			switch(modo){

    				case 1:
    				{
    					cout << "Tamaño del vector a ordenar: ";
    					cin >> tam_vec;

    					

    					Insercion<DNI> vector_insercion(tam_vec);
    					Burbuja<DNI> vector_burbuja(tam_vec);
    					Heap_Sort<DNI> vector_heap_sort(tam_vec);
    					QuickSort<DNI> vector_quicksort(tam_vec);
    					ShellSort<DNI> vector_shellsort(tam_vec);


    					do{
    						cout << endl << "  *" << setfill('=') << setw(24) << "*" << endl;
    						cout << "  ||  MODO DEMOSTRACIÓN" << setfill(' ') << setw(4) << "||" << endl;
    						cout << "  || ------------------- ||" << endl;
    						cout << "  ||  1. Inserción" << setfill(' ') << setw(9) << "||" << endl;
    						cout << "  ||  2. Burbuja" << setfill(' ') << setw(11) << "||" << endl;
    						cout << "  ||  3. Heap Sort" << setfill(' ') << setw(9) << "||" << endl;
    						cout << "  ||  4. QuickSort" << setfill(' ') << setw(9) << "||" << endl;
    						cout << "  ||  5. ShellSort" << setfill(' ') << setw(9) << "||" << endl;
    						cout << "  ||  0. Salir" << setfill(' ') << setw(13) << "||" << endl;
    						cout << "  *" << setfill('=') << setw(24) << "*" << endl;

    						cout << "  Seleccione una opción: ";
    						cin >> opcion;

    						switch(opcion){
    							case 1:
    								{
    									
    									char opt = 'X';
    									cout << "  # ¿Generar banco de DNI manualmente? (S,s) | (N,n): ";
    									cin >> opt;

    									if ((opt == 'S') or (opt == 's'))
    									{
    										int dni_aux = 0;
    										char letra = ' ';
    										string nombre = " ";

    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;

    											cout << endl << "  # Registro número " << i << endl;
    											cout << "   > Inserte el DNI: ";
    											cin >> dni_aux;

    											cout << "   > Inserte la letra del DNI: ";
    											cin >> letra;

    											cout << "   > Inserte el nombre: ";
    											cin >> nombre;

    											tmp_dni.setDni(dni_aux, letra, nombre);

    											vector_insercion.setDato(tmp_dni, i);
    										}
    									}
    									else if ((opt == 'N') or (opt == 'n'))
    									{
    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;
    										    vector_insercion.setDato(tmp_dni, i);
    										}
    									}

    									cout << endl << "  |" << setfill('=') << setw((tam_vec * 10) / 2) << " INSERCIÓN " << setfill('=') << setw((tam_vec * 10) / 2) << "=|" << endl;
    									cout << "  | VECTOR GENERADO:" << endl;
    									vector_insercion.mostrar();

    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;
    									vector_insercion.ordenar(true);
    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;

    									cout << "  | VECTOR ORDENADO:" << endl;
    									vector_insercion.mostrar();
    									break;
    								}

    							case 2:
    								{
    									
    									char opt = 'X';
    									cout << "  # ¿Generar banco de DNI manualmente? (S,s) | (N,n): ";
    									cin >> opt;

    									if ((opt == 'S') or (opt == 's'))
    									{
    										int dni_aux = 0;
    										char letra = ' ';
    										string nombre = " ";

    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;

    											cout << endl << "  # Registro número " << i << endl;
    											cout << "   > Inserte el DNI: ";
    											cin >> dni_aux;

    											cout << "   > Inserte la letra del DNI: ";
    											cin >> letra;

    											cout << "   > Inserte el nombre: ";
    											cin >> nombre;

    											tmp_dni.setDni(dni_aux, letra, nombre);

    											vector_burbuja.setDato(tmp_dni, i);
    										}
    									}
    									else if ((opt == 'N') or (opt == 'n'))
    									{
    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;
    											vector_burbuja.setDato(tmp_dni, i);
    										}
    									}

    									cout << endl << "  |" << setfill('=') << setw((tam_vec * 10) / 2) << " BURBUJA " << setfill('=') << setw((tam_vec * 10) / 2) << "=|" << endl;
    									cout << "  | VECTOR GENERADO:" << endl;
    									vector_burbuja.mostrar();

    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;
    									vector_burbuja.ordenar(true);
    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;

    									cout << "  | VECTOR ORDENADO:" << endl;
    									vector_burbuja.mostrar();
    									break;
    								}

    							case 3:
    								{
    									
    									char opt = 'X';
    									cout << "  # ¿Generar banco de DNI manualmente? (S,s) | (N,n): ";
    									cin >> opt;

    									if ((opt == 'S') or (opt == 's'))
    									{
    										int dni_aux = 0;
    										char letra = ' ';
    										string nombre = " ";

    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;

    											cout << endl << "  # Registro número " << i << endl;
    											cout << "   > Inserte el DNI: ";
    											cin >> dni_aux;

    											cout << "   > Inserte la letra del DNI: ";
    											cin >> letra;

    											cout << "   > Inserte el nombre: ";
    											cin >> nombre;

    											tmp_dni.setDni(dni_aux, letra, nombre);

    											vector_heap_sort.setDato(tmp_dni, i);
    										}
    									}
    									else if ((opt == 'N') or (opt == 'n'))
    									{
    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;
    											vector_heap_sort.setDato(tmp_dni, i);
    										}
    									}

    									cout << endl << "  |" << setfill('=') << setw((tam_vec * 10) / 2) << " HEAP SORT " << setfill('=') << setw((tam_vec * 10) / 2) << "=|" << endl;
    									cout << "  | VECTOR GENERADO:" << endl;
    									vector_heap_sort.mostrar();

    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;
    									vector_heap_sort.ordenar(true);
    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;

    									cout << "  | VECTOR ORDENADO:" << endl;
    									vector_heap_sort.mostrar();
    									break;
    								}

    							case 4:
    								{
    									
    									char opt = 'X';
    									cout << "  # ¿Generar banco de DNI manualmente? (S,s) | (N,n): ";
    									cin >> opt;

    									if ((opt == 'S') or (opt == 's'))
    									{
    										int dni_aux = 0;
    										char letra = ' ';
    										string nombre = " ";

    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;

    											cout << endl << "  # Registro número " << i << endl;
    											cout << "   > Inserte el DNI: ";
    											cin >> dni_aux;

    											cout << "   > Inserte la letra del DNI: ";
    											cin >> letra;

    											cout << "   > Inserte el nombre: ";
    											cin >> nombre;

    											tmp_dni.setDni(dni_aux, letra, nombre);

    											vector_quicksort.setDato(tmp_dni, i);
    										}
    									}
    									else if ((opt == 'N') or (opt == 'n'))
    									{
    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;
    											vector_quicksort.setDato(tmp_dni, i);
    										}
    									}

    									cout << endl << "  |" << setfill('=') << setw((tam_vec * 10) / 2) << " QUICKSORT " << setfill('=') << setw((tam_vec * 10) / 2) << "=|" << endl;
    									cout << "  | VECTOR GENERADO:" << endl;
    									vector_quicksort.mostrar();

    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;
    									vector_quicksort.ordenar(0, tam_vec - 1, true);
    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;

    									cout << "  | VECTOR ORDENADO:" << endl;
    									vector_quicksort.mostrar();
    									break;
    								}

    							case 5:
    								{
    									
    									char opt = 'X';

    									cout << "# Introduzca el valor de alfa (0 < alfa < 1)" << endl;
    									cin >> alfa;

    									cout << "  # ¿Generar banco de DNI manualmente? (S,s) | (N,n): ";
    									cin >> opt;

    									if ((opt == 'S') or (opt == 's'))
    									{
    										int dni_aux = 0;
    										char letra = ' ';
    										string nombre = " ";

    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;

    											cout << endl << "  # Registro número " << i << endl;
    											cout << "   > Inserte el DNI: ";
    											cin >> dni_aux;

    											cout << "   > Inserte la letra del DNI: ";
    											cin >> letra;

    											cout << "   > Inserte el nombre: ";
    											cin >> nombre;

    											tmp_dni.setDni(dni_aux, letra, nombre);

    											vector_shellsort.setDato(tmp_dni, i);
    										}
    									}
    									else if ((opt == 'N') or (opt == 'n'))
    									{
    										for(int i = 0 ; i < tam_vec ; i++)
    										{
    											DNI tmp_dni;
    											vector_shellsort.setDato(tmp_dni, i);
    										}
    									}

    									cout << endl << "  |" << setfill('=') << setw((tam_vec * 10) / 2) << " SHELLSORT " << setfill('=') << setw((tam_vec * 10) / 2) << "=|" << endl;
    									cout << "  | VECTOR GENERADO:" << endl;
    									vector_shellsort.mostrar();

    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;
    									vector_shellsort.ordenar(alfa, true);
    									cout << "  |" << setfill('-') << setw(tam_vec * 10) << "-|" << endl;

    									cout << "  | VECTOR ORDENADO:" << endl;
    									vector_shellsort.mostrar();
    									break;
    								}
    						}
    					} while (opcion != 0);
    					break;
    				}

    				case 2:
    				{
    					int nPruebas;

    					cout << endl << "  *" << setfill('=') << setw(24) << "*" << endl;
    					cout << "  ||  MODO ESTADÍSTICA" << setfill(' ') << setw(5) << "||" << endl;
    					cout << "  *" << setfill('=') << setw(24) << "*" << endl;

    					cout << "  # Tamaño del vector a ordenar: ";
    					cin >> tam_vec;

    					cout << "  # Introduce el número de pruebas a realizar: ";
    					cin >> nPruebas;

    					cout << "  # Introduzca el valor de alfa (0 < alfa < 1): ";
    					cin >> alfa;

    					
    					int max_insercion	= 0, min_insercion	= 2147483647, suma_insercion	= 0, media_insercion	= 0;
    					int max_burbuja 	  	= 0, min_burbuja		= 2147483647, suma_burbuja 	= 0, media_burbuja	= 0;
    					int max_heap_sort	= 0, min_heap_sort 	= 2147483647, suma_heap_sort	= 0, media_heap_sort	= 0;
    					int max_quicksort 	= 0, min_quicksort 	= 2147483647, suma_quicksort	= 0, media_quicksort	= 0;
    					int max_shellsort 	= 0, min_shellsort 	= 2147483647, suma_shellsort	= 0, media_shellsort	= 0;

    					

    					Insercion<DNI> vector_insercion_est(tam_vec);
    					Burbuja<DNI> vector_burbuja_est(tam_vec);
    					Heap_Sort<DNI> vector_heap_sort_est(tam_vec);
    					QuickSort<DNI> vector_quicksort_est(tam_vec);
    					ShellSort<DNI> vector_shellsort_est(tam_vec);

    					
    					for(int p = 0 ; p < nPruebas ; p++)
    					{
    						
    						for(int i = 0 ; i < tam_vec ; i++)
    						{
        						DNI tmp_dni;
        						vector_insercion_est.setDato(tmp_dni.getDni(), i);
        						vector_burbuja_est.setDato(tmp_dni.getDni(), i);
        						vector_heap_sort_est.setDato(tmp_dni.getDni(), i);
        						vector_quicksort_est.setDato(tmp_dni.getDni(), i);
        						vector_shellsort_est.setDato(tmp_dni.getDni(), i);
    						}

    						
    						vector_insercion_est.ordenar(false);

    						
    						if (vector_insercion_est.getComparaciones() > max_insercion)
    							max_insercion = vector_insercion_est.getComparaciones();

    						
    						if (vector_insercion_est.getComparaciones() < min_insercion)
    							min_insercion = vector_insercion_est.getComparaciones();

    						suma_insercion += vector_insercion_est.getComparaciones();

    						

    						
    						vector_burbuja_est.ordenar(false);

    						
    						if (vector_burbuja_est.getComparaciones() > max_burbuja)
    							max_burbuja = vector_burbuja_est.getComparaciones();

    						
    						if (vector_burbuja_est.getComparaciones() < min_burbuja)
    							min_burbuja = vector_burbuja_est.getComparaciones();

    						suma_burbuja += vector_burbuja_est.getComparaciones();

    						

    						
    						vector_heap_sort_est.ordenar(false);

    						
    						if (vector_heap_sort_est.getComparaciones() > max_heap_sort)
    							max_heap_sort = vector_heap_sort_est.getComparaciones();

    						
    						if (vector_heap_sort_est.getComparaciones() < min_heap_sort)
    							min_heap_sort = vector_heap_sort_est.getComparaciones();

    						suma_heap_sort += vector_heap_sort_est.getComparaciones();

    						

    						
    						vector_quicksort_est.ordenar(0, tam_vec - 1, false);

    						
    						if (vector_quicksort_est.getComparaciones() > max_quicksort)
    							max_quicksort = vector_quicksort_est.getComparaciones();

    						
    						if (vector_quicksort_est.getComparaciones() < min_quicksort)
    							min_quicksort = vector_quicksort_est.getComparaciones();

    						suma_quicksort += vector_quicksort_est.getComparaciones();

    						

    						
    						vector_shellsort_est.ordenar(alfa, false);

    						
    						if (vector_shellsort_est.getComparaciones() > max_shellsort)
    							max_shellsort = vector_shellsort_est.getComparaciones();

    						
    						if (vector_shellsort_est.getComparaciones() < min_shellsort)
    							min_shellsort = vector_shellsort_est.getComparaciones();

    						suma_shellsort += vector_shellsort_est.getComparaciones();

    						

    					} 


    					
    					media_insercion = suma_insercion / nPruebas;
    					media_burbuja = suma_burbuja / nPruebas;
    					media_heap_sort = suma_heap_sort / nPruebas;
    					media_quicksort = suma_quicksort / nPruebas;
    					media_shellsort = suma_shellsort / nPruebas;

    					
    					int a_m = 8;

    					cout << endl << endl << setfill(' ') << setw(45) << "--- NÚMERO DE COMPARACIONES ---" << endl;
    					cout << setfill(' ') << setw(20) << "Mínimo" << setfill(' ') << setw(5) << " | " << setfill(' ') << setw(9) << "Medio" << setfill(' ') << setw(7) << " | " << setfill(' ') << setw(10) << "Máximo" << endl;
    					cout << "INSERCIÓN: " << setfill(' ') << setw(5) << min_insercion << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << media_insercion << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << max_insercion << endl;
    					cout << "BURBUJA  : " << setfill(' ') << setw(5) << min_burbuja   << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << media_burbuja   << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << max_burbuja << endl;
    					cout << "HEAP SORT: " << setfill(' ') << setw(5) << min_heap_sort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << media_heap_sort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << max_heap_sort << endl;
    					cout << "QUICKSORT: " << setfill(' ') << setw(5) << min_quicksort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << media_quicksort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << max_quicksort << endl;
    					cout << "SHELLSORT: " << setfill(' ') << setw(5) << min_shellsort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << media_shellsort << setfill(' ') << setw(a_m) << " | " << setfill(' ') << setw(a_m) << max_shellsort << endl;

    					break;
    				}
    			}
    } while (modo != 0);




	return 0;
}
