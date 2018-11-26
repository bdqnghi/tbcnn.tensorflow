package OptimizedFlow;

import ADTGraph.Graph;
import ADTGraph.Vertex;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

import static ADTGraph.Graph.importG;
import static ADTGraph.Vertex.createV;
import static OptimizedFlow.maxflow.*;

/**
 * @author Florian Dannenberg, Igor Arkhipov
 */
public class benchmark {
    /*===================================
      CONFIG
     ====================================*/
    private static final String BENCHMARK_RESULT = "benchmark_flow.csv";
    private static final String DELIMETER = ";";

    // Graph Namen zum Importieren
    private static final String IMPORTLIST[] = { "graph_03", "graph_06",
            "graph_07", "graph_08", "graph_09", "graph_13", "graph_14" };
    // Startpunkte der Suche
    private static final String SOURCELIST[] = { "s", "v1",
            "v4", "Rostock", "Quelle", "var.mount", "sysinit.target" };
    // Endpunkte der Suche
    private static final String TARGETLIST[] = { "v", "v9",
            "v2", "München", "Senke", "umount.target", "shutdown.target" };

    /**
     * Die Methode führt unterschiedliche Messungen in
     * Bezug auf Ford-Fulkerson und Edmonds-Karp Algorithmen aus
     * und zählt die Laufzeit und die Zugriffe auf den unterliegenden Graphen.
     */
    public static void main(String args[]) {
        StringBuilder tempResult = new StringBuilder();
        tempResult.append("Graph Name" + DELIMETER +
                "Algorithmus" + DELIMETER +
                "Laufzeit" + DELIMETER +
                "Anzahl der Zugriffe" + DELIMETER + "\n");

        for (int i = 0; i < IMPORTLIST.length; i++) {
            Graph g = importG(IMPORTLIST[i]);
            Vertex source = createV(SOURCELIST[i]);
            Vertex target = createV(TARGETLIST[i]);

            tempResult.append(IMPORTLIST[i] + DELIMETER);
            tempResult.append("Ford-Fulkerson" + DELIMETER);
            // Messungen der Laufzeit des Algorithmus
            tempResult.append(findMaxFlowRtm(g, source, target, maxflow.BY.FF) + DELIMETER);
            // Messungen der Zugriffe auf den unterliegenden Graphen während des jeweiligen Algorithmus
            tempResult.append(findMaxFlowAcc(g, source, target, maxflow.BY.FF) + DELIMETER + "\n");

            tempResult.append(IMPORTLIST[i] + DELIMETER);
            tempResult.append("Edmonds-Karp" + DELIMETER);
            // Messungen der Laufzeit des Algorithmus
            System.out.println(i);
            tempResult.append(findMaxFlowRtm(g, source, target, maxflow.BY.EK) + DELIMETER);
            // Messungen der Zugriffe auf den unterliegenden Graphen während des jeweiligen Algorithmus
            tempResult.append(findMaxFlowAcc(g, source, target, maxflow.BY.EK) + DELIMETER + "\n");
        }

        try {
            Files.write(Paths.get(BENCHMARK_RESULT), tempResult.toString().getBytes());
        } catch (IOException e) { e.printStackTrace(); }
    }
}
