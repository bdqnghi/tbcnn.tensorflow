import java.util.*;

class Vertex{
    HashMap<Integer, Integer> sosedi;
    Vertex(){
        sosedi = new HashMap<>();
    }
}

public class Main {
    private static int findmin(int S, int T, HashMap<Integer, Integer> parentMap, Vertex[] ver){
        int min = Integer.MAX_VALUE;
        int current = T;
        while(current != S){
            int parent = parentMap.get(current);
            int val = ver[parent].sosedi.get(current);
            if(val < min) min = val;
            current = parent;
        }
        return min;
    }

    private static void reducePaths(int S, int T, HashMap<Integer, Integer> parentMap, Vertex[] ver, int val){
        int current = T;
        while(current != S){
            int parent = parentMap.get(current);
            ver[parent].sosedi.put(current, ver[parent].sosedi.get(current) - val);
            ver[current].sosedi.put(parent, ver[current].sosedi.get(parent) + val);
            current = parent;
        }
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int V = sc.nextInt();
        int E = sc.nextInt();

        //inicijalizacija na teminjata
        Vertex[] ver = new Vertex[V];
        for(int i = 0; i<V; i++) ver[i] = new Vertex();

        //input na rebrata
        for(int i = 0; i<E; i++){
            int a = sc.nextInt();
            int b = sc.nextInt();
            int c = sc.nextInt();
            ver[a].sosedi.put(b, c);
            if(!ver[b].sosedi.containsKey(a)) ver[b].sosedi.put(a, 0);
        }

        //input na start i finish
        int S = sc.nextInt();
        int T = sc.nextInt();

        //BFS
        int total = 0;
        boolean end;
        do{
            HashMap<Integer, Integer> parentMap = new HashMap<>();
            HashSet<Integer> visited = new HashSet<>();
            Queue<Integer> q = new LinkedList<>();
            q.add(S);
            visited.add(S);
            end = true;
            while(!q.isEmpty()){
                int current = q.remove();
                if(current == T){
                    int minimum = findmin(S, T, parentMap, ver);
                    reducePaths(S, T, parentMap, ver, minimum);
                    total += minimum;
                    end = false;
                    break;
                }
                for(Map.Entry<Integer, Integer> ss : ver[current].sosedi.entrySet()) {
                    if(ss.getValue() <= 0) continue;
                    int sosed = ss.getKey();
                    if(!visited.contains(sosed)){
                        visited.add(sosed);
                        q.add(sosed);
                        parentMap.put(sosed, current);
                    }
                }
            }
        }while(!end);

        System.out.println(total);
    }
}
