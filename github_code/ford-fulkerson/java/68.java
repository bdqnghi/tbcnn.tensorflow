
import model.FordFulkerson;
import model.Graph;

/**
 *
 * @author Dan Joel Canqui Aviles
 */
public class Main {

    public static void main(String[] args) {
        String simpleSource = "S->A,3->B,6\n"
                + "A->C,7->D,6\n"
                + "B->D,5->T,4\n"
                + "C->T,5\n"
                + "D->C,8\n"
                + "T\n";
        Graph graph = new Graph(simpleSource);
        FordFulkerson fordFulkerson = new FordFulkerson(graph);
        fordFulkerson.begin();
        System.out.println("La capacidad maxima de la red de transporte con un "
                + "solo origen y destino es: "
                + fordFulkerson.getMaxFlow());

        String multipleSources = "S1->A1,6\n"
                + "S2->A1,5->A2,7\n"
                + "S3->A3,6\n"
                + "A1->B1,8->B2,3\n"
                + "A2->B2,5\n"
                + "A3->B2,5->B3,4\n"
                + "B1->C1,7\n"
                + "B2->B1,3->C1,4->T2,10\n"
                + "B3->C2,7->C3,3\n"
                + "C1->T1,4->T2,3\n"
                + "C2->T3,5->T4,3\n"
                + "C3->T4,4\n"
                + "T1\n"
                + "T2\n"
                + "T3\n"
                + "T4\n";
        graph = new Graph(multipleSources);
        fordFulkerson = new FordFulkerson(graph);
        fordFulkerson.begin();
        System.out.println("La capacidad maxima de la red de transporte de "
                + "multiples origenes y destinos es: "
                + fordFulkerson.getMaxFlow());
    }
}
