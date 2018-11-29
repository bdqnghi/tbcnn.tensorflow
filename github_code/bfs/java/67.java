package pacman;

import graph.*;
import java.util.ArrayList;
import java.util.HashMap;

public class NewAgent implements PacAgent, Constants {

    Node inicial;
    Node destino = Graph.nodes[26];
    BFS bfs, bfs2;
    HashMap<Integer,Integer> aux;
    int d1=0;
    int max = 0;

    boolean pri = false, sec = false, ter = false, cua = false, si = false;



    @Override
    public int move(GameState gs) {
        Graph.update();
        inicial = Graph.nodes[Graph.id_pacman];

        if(Graph.nearest_edible!=null) {
            try {
                if (Graph.id_pacman == Graph.nearest_edible.getId()) {
                    System.out.println("Me lo comi");
                }
                if(Graph.nodes[Graph.nearest_edible.getId()].getTop() != null)
                if(Graph.id_pacman == Graph.nodes[Graph.nearest_edible.getId()].getTop().getId()){
                    System.out.println("Me lo comi");
                }
                if(Graph.nodes[Graph.nearest_edible.getId()].getLeft() != null)
                if(Graph.id_pacman == Graph.nodes[Graph.nearest_edible.getId()].getLeft().getId()){
                    System.out.println("Me lo comi");
                }
                if(Graph.nodes[Graph.nearest_edible.getId()].getBottom() != null)
                if(Graph.id_pacman == Graph.nodes[Graph.nearest_edible.getId()].getBottom().getId()){
                    System.out.println("Me lo comi");
                }
                if(Graph.nodes[Graph.nearest_edible.getId()].getRight() != null)
                if(Graph.id_pacman == Graph.nodes[Graph.nearest_edible.getId()].getRight().getId()){
                    System.out.println("Me lo comi");
                }
            }catch (Exception e){

            }
//            int e = 0;
//            for (int i = 1; i < Graph.nodes.length; i++) {
//                if(Graph.nodes[i]!=null)
//                if(Graph.nodes[i].getElement()== -14408449){
//                    e++;
//                }
//
//                if(e > 0) {
//                    si = true;
//                    max = e;
//
//                }
//            }
//
//            if (si) {
//                //if (aux.get(Graph.id_pacman) == Graph.nearest_edible.getId()) {
//                if (e == 3 && pri == false) {
//                    System.out.println("Me comi uno");
//                    pri = true;
//                }
//
//                if (e == 2 && sec == false) {
//                    System.out.println("Me comi uno");
//                    sec = true;
//                }
//
//                if (e == 1 && ter == false) {
//                    System.out.println("Me comi uno");
//                    ter = true;
//                }
//
//                if (e == 0 && cua == false) {
//                    System.out.println("Me comi uno");
//                    cua = true;
//                }
//            }
        }
       /*bfs=new BFS(inicial,Graph.nodes[1]);
        if(inicial!=null) {
            return bfs.bfs().get(Graph.id_pacman);
        }*/
        if (inicial!=null){
            bfs=new BFS(inicial,Graph.nearest_ghost);
//            System.out.println("Cercano " + bfs.destino);

            if(bfs.destino != null && bfs.initial != null){
                if(Graph.pp2) {

                    //bfs = new BFS(inicial, Graph.nodes[Graph.pp[1]]);
                    //System.out.println("pp dif de 0");
                    if(inicial.getId()==598 ||inicial.getId()==624 ||inicial.getId()==650 || inicial.getId()==676 ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[702]);
                        if(Graph.nearest_ghost.getId()>702) d1=8;
                        else d1=4;
                        if (Graph.nearest_ghost.getDistancia() < d1) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[598]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                    if(inicial.getId()==754 ||inicial.getId()==728 ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[702]);
                        if(Graph.nearest_ghost.getId()<650) d1=5;
                        else d1=5;
                        if (Graph.nearest_ghost.getDistancia() < d1) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[754]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                }




                if(Graph.pp1) {

                    //bfs = new BFS(inicial, Graph.nodes[Graph.pp[1]]);
                    //System.out.println("pp dif de 0");

                    if(inicial.getId()==573 ||inicial.getId()==599 ||inicial.getId()==625 || inicial.getId()==651 ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[677]);
                        if(Graph.nearest_ghost.getId()<625) d1=5;
                        else d1=8;

                        if (Graph.nearest_ghost.getDistancia() < d1) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[573]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                    if(inicial.getId()==729 ||inicial.getId()==703 ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[677]);
                        if(Graph.nearest_ghost.getId()<625) d1=5;
                        else d1=5;
                        if (Graph.nearest_ghost.getDistancia() < d1) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[729]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                }



                if(Graph.pp4) {

                    //bfs = new BFS(inicial, Graph.nodes[Graph.pp[1]]);
                    //System.out.println("pp dif de 0");

                    if(inicial.getId()==1   ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[27]);
                        //if(Graph.nearest_ghost.getId()<625) d1=5;
                        //else d1=8;

                        if (Graph.nearest_ghost.getDistancia() < 5) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[1]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                    if(inicial.getId()==79 ||inicial.getId()==53 ){
                        //bfs.destino = Graph.nodes[702];
                        bfs = new BFS(inicial, Graph.nodes[27]);
                        if(Graph.nearest_ghost.getId()<53) d1=8;
                        else d1=5;
                        if (Graph.nearest_ghost.getDistancia() < d1) {
                            //System.out.println("dis al g");
                            aux = bfs.bfs();
                            if (aux != null)
                                return aux.get(Graph.id_pacman);
                            else
                                return 0;
                        }

                        bfs.destino=(Graph.nodes[79]);

                        aux = bfs.bfs();

                        if (aux != null) {

                            return aux.get(Graph.id_pacman);
                        }else
                            return 0;
                    }


                }



                if(bfs.bfs().size() > 5){

                    bfs=new BFS(inicial,Graph.nearest_pill);
                    aux = bfs.bfs();
                    if (aux!=null)
                        return aux.get(Graph.id_pacman);
                    else
                        return 0;
                }


                int min = 100;
                Node elegido = Graph.nearest_ghost;

                try {
                    bfs2 = new BFS(inicial, Graph.blinky);
                    aux = bfs2.bfs();

                    if (min > aux.size() && !Graph.blinky.equals(Graph.nearest_ghost)) {
                        elegido = Graph.blinky;
                    }
                } catch (Exception e) {

                }

                try {
                    bfs2 = new BFS(inicial, Graph.inky);
                    aux = bfs2.bfs();

                    if (min > aux.size() && !Graph.inky.equals(Graph.nearest_ghost)) {
                        elegido = Graph.inky;
                    }
                } catch (Exception e) {

                }

                try {
                    bfs2 = new BFS(inicial, Graph.pinky);
                    aux = bfs2.bfs();

                    if (min > aux.size() && !Graph.pinky.equals(Graph.nearest_ghost)) {
                        elegido = Graph.pinky;
                    }
                } catch (Exception e) {

                }

                try {
                    bfs2 = new BFS(inicial, Graph.sue);
                    aux = bfs2.bfs();

                    if (min > aux.size() && !Graph.sue.equals(Graph.nearest_ghost)) {
                        elegido = Graph.sue;
                    }
                } catch (Exception e) {

                }

                if (min > 8) {
                    if (bfs.destino.getPos().x <= bfs.initial.getPos().x && bfs.initial.getRight() != null) {
                        return 2;
                    }
                    if (bfs.destino.getPos().x >= bfs.initial.getPos().x && bfs.initial.getLeft() != null) {
                        return 4;
                    }
                    if (bfs.destino.getPos().y <= bfs.initial.getPos().y && bfs.initial.getBottom() != null) {
                        return 3;
                    }
                    if (bfs.destino.getPos().y >= bfs.initial.getPos().y && bfs.initial.getTop() != null) {
                        return 1;
                    }
                }

                ////////////////A
                if (elegido.getPos().x <= bfs.initial.getPos().x && elegido.getPos().x <= bfs.initial.getPos().x) {
                    if (bfs.initial.getRight() != null) {
                        return 2;
                    }
                    if ((elegido.getPos().y < bfs.initial.getPos().y && elegido.getPos().y > bfs.initial.getPos().y)
                            || (elegido.getPos().y > bfs.initial.getPos().y && elegido.getPos().y < bfs.initial.getPos().y)
                            && bfs.initial.getLeft() != null) {
                        return 4;
                    }
                    if ((elegido.getPos().y < bfs.initial.getPos().y && elegido.getPos().y < bfs.initial.getPos().y)
                            && bfs.initial.getBottom() != null) {
                        return 3;
                    }

                    if ((elegido.getPos().y > bfs.initial.getPos().y && elegido.getPos().y > bfs.initial.getPos().y)
                            && bfs.initial.getBottom() != null) {
                        return 1;
                    }

                    if (bfs.initial.getTop() != null) {
                        return 1;
                    }

                    if (bfs.initial.getLeft() != null) {
                        return 4;
                    }

                    if (bfs.initial.getRight() != null) {
                        return 2;
                    }

                    if (bfs.initial.getTop() != null) {
                        return 1;
                    }

                    if (bfs.initial.getBottom() != null) {
                        return 3;
                    }
                }

                //////////////////////B
                if (elegido.getPos().x >= bfs.initial.getPos().x && elegido.getPos().x >= bfs.initial.getPos().x) {
                    if (bfs2.initial.getLeft() != null) {
                        return 4;
                    }
                    if ((elegido.getPos().y < bfs.initial.getPos().y && elegido.getPos().y > bfs.initial.getPos().y)
                            || (elegido.getPos().y > bfs.initial.getPos().y && elegido.getPos().y < bfs.initial.getPos().y)
                            && bfs.initial.getRight() != null) {
                        return 2;
                    }
                    if ((elegido.getPos().y < bfs.initial.getPos().y && elegido.getPos().y < bfs.initial.getPos().y)
                            && bfs.initial.getBottom() != null) {
                        return 3;
                    }

                    if ((elegido.getPos().y > bfs.initial.getPos().y && elegido.getPos().y > bfs.initial.getPos().y)
                            && bfs.initial.getBottom() != null) {
                        return 1;
                    }

                    if (bfs.initial.getTop() != null) {
                        return 1;
                    }

                    if (bfs.initial.getLeft() != null) {
                        return 4;
                    }

                    if (bfs.initial.getRight() != null) {
                        return 2;
                    }

                    if (bfs.initial.getBottom() != null) {
                        return 3;
                    }
                }

                ////////////////C
                if (elegido.getPos().y <= bfs.initial.getPos().y && elegido.getPos().y <= bfs.initial.getPos().y) {
                    if (bfs.initial.getBottom() != null) {
                        return 3;
                    }
                    if (bfs.initial.getTop() != null) {
                        return 1;
                    }

                    if (bfs.initial.getLeft() != null) {
                        return 4;
                    }

                    if (bfs.initial.getRight() != null) {
                        return 2;
                    }

                }

                ////////////////D
                if (elegido.getPos().y >= bfs.initial.getPos().y && elegido.getPos().y >= bfs.initial.getPos().y) {
                    if (bfs.initial.getTop() != null) {
                        return 1;
                    }
                    if (bfs.initial.getBottom() != null) {
                        return 3;
                    }

                    if (bfs.initial.getLeft() != null) {
                        return 4;
                    }

                    if (bfs.initial.getRight() != null) {
                        return 2;
                    }

                }
                if(bfs.destino.getPos().x >= bfs.initial.getPos().x && bfs.initial.getLeft()!= null)
                    return LEFT;
                if(bfs.destino.getPos().y <= bfs.initial.getPos().y && bfs.initial.getBottom() != null)
                    return DOWN;
                if(bfs.destino.getPos().x <= bfs.initial.getPos().x && bfs.initial.getRight()!= null)
                    return RIGHT;
                if(bfs.destino.getPos().y >= bfs.initial.getPos().y && bfs.initial.getTop()!= null)
                    return UP;

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
