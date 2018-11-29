package pacman;

import graph.BFS;
import graph.Graph;
import graph.Node;

import java.util.HashMap;

public class NewAgent1 implements PacAgent, Constants {

    Node inicial;
    Node destino = Graph.nodes[26];
    BFS bfs;
    HashMap<Integer,Integer> aux;





    @Override
    public int move(GameState gs) {
        Graph.update();

        inicial = Graph.nodes[Graph.id_pacman];

        if (inicial!=null){
            bfs=new BFS(inicial,Graph.nearest_ghost);
//            System.out.println("Cercano " + bfs.destino);
            
            if(bfs.destino != null && bfs.initial != null){
                if(bfs.bfs().size() > 5){
                    if(Graph.pp[0]>=0) {
                        //System.out.println("pp dif de 0");
                        bfs = new BFS(inicial, Graph.nodes[Graph.pp[0]]);
                        if (bfs.bfs().size() < 6) {
                            //System.out.println("dis menor a 4");
                            //System.out.println(Graph.nearest_ghost.getDistancia());
                            if (Graph.nearest_ghost.getDistancia() < 5) {
                                //System.out.println("dis al g");
                                aux = bfs.bfs();
                                if (aux != null)
                                    return aux.get(Graph.id_pacman);
                                else
                                    return 0;
                            }
                            bfs = new BFS(inicial, Graph.nodes[573]);
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }
                    }
                    bfs=new BFS(inicial,Graph.nearest_pill);
                    aux = bfs.bfs();
                    if (aux!=null)
                        return aux.get(Graph.id_pacman);
                    else
                        return 0;
                }
                if(bfs.destino.getPos().x <= bfs.initial.getPos().x && bfs.initial.getRight()!= null)
                    return RIGHT;
                if(bfs.destino.getPos().y >= bfs.initial.getPos().y && bfs.initial.getTop()!= null)
                    return UP;
                if(bfs.destino.getPos().x >= bfs.initial.getPos().x && bfs.initial.getLeft()!= null)
                    return LEFT;
                if(bfs.destino.getPos().y <= bfs.initial.getPos().y && bfs.initial.getBottom() != null)
                    return DOWN;
            }
        }
        try {
            if(Graph.nearest_edible.getDistancia()<11) {
                bfs = new BFS(inicial, Graph.nearest_edible);
                aux = bfs.bfs();
                return aux.get(Graph.id_pacman);
            }
            else{
                bfs = new BFS(inicial, Graph.nearest_pill);
                aux = bfs.bfs();
                return aux.get(Graph.id_pacman);
            }

        }catch (Exception e) {}

        return 0;
    }
}
