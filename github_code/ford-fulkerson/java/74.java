package drivers;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

import domain.FordFulkerson;
import domain.Graf;

public class FordFulkersonDriver {

	/**
	 * El driver de mostra d'utilitzaci� de la clase i permet testejar el funcionament de la classe.
	 * Per fer-ho s'ha d'editar el fitxer de text test.ff:
	 * - El fitxer mostra la matriu de capacitats que defineix un graf:
	 * 		- El n�mero de fila es el node origen.
	 * 		- El n�mero de columna es el node dest�.
	 * 		- El valor (fila/columna) de la matriu es la capacitat asignada a l'aresta. 
	 * 
	 * @param args no s'utilitza
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		//Ejemplo de uso

		Graf<String> graf = new Graf<String>();
		
		//Afegim els nodes del graf
	  	graf.afegirNode("Node0");
		graf.afegirNode("Node1");
		graf.afegirNode("Node2");
		graf.afegirNode("Node3");
		graf.afegirNode("Node4");
		graf.afegirNode("Node5");
		
		//Es connecten els nodes i s'assignen capacitats i costos
		graf.conectarNodes(0, 1, 2, 5.0);
		graf.conectarNodes(0, 2, 3, 5.0);
		graf.conectarNodes(1, 3, 2, 5.0);
		graf.conectarNodes(1, 2, 3, 5.0);
		graf.conectarNodes(1, 4, 2, 5.0);
		graf.conectarNodes(2, 3, 3, 5.0);
		graf.conectarNodes(2, 4, 2, 5.0);
		graf.conectarNodes(3, 5, 3, 5.0);
		graf.conectarNodes(4, 5, 2, 5.0);
		
		//Es crea l'objecte FordFoulkerson
		FordFulkerson<String> algoritme = new FordFulkerson<String>();		
		
		// S'executa el algoritme de MaxFlow que retorna el graf residual
		Graf<String> grafResidual = algoritme.findMaxFlow(graf,0,5);
		//Just despr�s d'executar l'algoritme si es crida al m�tode getMaxFlow() retornar�
		//el MaxFlow de la �ltima execuci� del algoritme. 
		System.out.println("MaxFlow: "+algoritme.getMaxFlow());
		
		System.out.println("Graf residual: ");
		System.out.println(algoritme.printMatrix(grafResidual));
		
		
		/*//Ejecucion del fichero test.ff del mismo directorio donde esta la classe FordFoulkerson
		Scanner s = new Scanner(new File("test.ff"));
		String line = "";
		String[] nums;
		graf = new Graf<String>();
		int from = 0;
		int capacitat = 0;
		
		//El graf tindr� tants nodes com linies tingui el fitxer. (La matriu ha de ser per for�a sempre una matriu
		//quadrada!).
		while(s.hasNextLine()){
			s.nextLine();
			graf.afegirNode("Node "+from);
			from++;
		}
		from =0;
		s = new Scanner(new File("test.ff"));
		//Construim les connexions del graf
		while(s.hasNextLine()){
			line = s.nextLine();
			nums = line.split("\\t");
			for (int i = 0; i < nums.length; i++) {
				if(!nums[i].equalsIgnoreCase("0")){
					capacitat = Integer.parseInt(nums[i]);
					graf.conectarNodes(from, i, capacitat, 5.0);
				}
			}
			from++;
		}
		
		//Executem l'algoritme
		algoritme = new FordFulkerson<String>();
		grafResidual = algoritme.findMaxFlow(graf,0,5);
		//Just despr�s d'executar l'algoritme si es crida al m�tode getMaxFlow() retornar�
		//el MaxFlow de la �ltima execuci� del algoritme. 
		System.out.println("MaxFlow: "+algoritme.getMaxFlow());
		
		System.out.println("Graf residual: ");
		System.out.println(algoritme.printMatrix(grafResidual));*/
		
	}

}
