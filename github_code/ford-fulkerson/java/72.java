import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class BaseballElimination {
    private Map<String, Integer> teams;
    private String[] teamsArray;
    private int[] wins;
    private int[] loses;
    private int[] remains;
    private int[][] gameBetween;
    // This map is used to cache the result of the query
    private Map<String, FordFulkerson> fordFulkersonMap;

    // Map between flow network to a map who maps between flow network's vertex index to game-between
    // vertex
    private Map<FordFulkerson, Map<Integer, GameBetweenVertex>> fordFulkersonToGameBetweenVertexMap;

    // create a baseball division from given filename in format specified below
    public BaseballElimination(String filename) {
        final In in = new In(filename);
        final String firstLine = in.readLine();
        final int numOfTeams = Integer.parseInt(firstLine);
        teams = new HashMap<>();
        teamsArray = new String[numOfTeams];
        wins = new int[numOfTeams];
        loses = new int[numOfTeams];
        remains = new int[numOfTeams];
        gameBetween = new int[numOfTeams][numOfTeams];
        fordFulkersonMap = new HashMap<>();
        fordFulkersonToGameBetweenVertexMap = new HashMap<>();

        int index = 0;
        while (in.hasNextLine()) {
            String line  = in.readLine();
            line = line.trim();
            final String[] segments = line.split("\\s+");
            teamsArray[index] = segments[0];
            teams.put(segments[0], index);
            wins[index] = Integer.parseInt(segments[1]);
            loses[index] = Integer.parseInt(segments[2]);
            remains[index] = Integer.parseInt(segments[3]);
            for (int teamIndex = 0; teamIndex < numOfTeams; teamIndex++) {
                gameBetween[index][teamIndex] = Integer.parseInt(segments[4 + teamIndex]);
            }
            index++;
        }
    }

    // number of teams
    public int numberOfTeams() {
        return teams.size();
    }

    // all teams
    public Iterable<String> teams() {
        return Arrays.asList(teamsArray);
    }

    // number of wins for given team
    public int wins(String team) {
        if (!teams.containsKey(team)) {
            throw new IllegalArgumentException();
        }
        return wins[teams.get(team)];
    }

    // number of losses for given team
    public int losses(String team) {
        if (!teams.containsKey(team)) {
            throw new IllegalArgumentException();
        }
        return loses[teams.get(team)];
    }

    // number of remaining games for given team
    public int remaining(String team) {
        if (!teams.containsKey(team)) {
            throw new IllegalArgumentException();
        }
        return remains[teams.get(team)];
    }

    // number of remaining games between team1 and team2
    public int against(String team1, String team2) {
        if (!teams.containsKey(team1) || !teams.containsKey(team2)) {
            throw new IllegalArgumentException();
        }
        return gameBetween[teams.get(team1)][teams.get(team2)];
    }

    // is given team eliminated?
    public boolean isEliminated(String team) {
        if (!teams.containsKey(team)) {
            throw new IllegalArgumentException();
        }

        FordFulkerson fordFulkerson;
        if (fordFulkersonMap.containsKey(team)) {
            fordFulkerson = fordFulkersonMap.get(team);
        } else {
            fordFulkerson = createFordFulkerson(team);
            fordFulkersonMap.put(team, fordFulkerson);
        }

        if (fordFulkerson == null) {
            return true;
        }

        for (int i = 1; i <= numOfGameVertex(); i++) {
            // inCut === entry in marked array is true === flow not full
            if (fordFulkerson.inCut(i)) {
                return true;
            }
        }

        // All is full, not eliminated
        return false;
    }

    // subset R of teams that eliminates given team; null if not eliminated
    public Iterable<String> certificateOfElimination(String team) {
        if (!teams.containsKey(team)) {
            throw new IllegalArgumentException();
        }

        final Set<String> certificate = new HashSet<>();
        FordFulkerson fordFulkerson;
        if (fordFulkersonMap.containsKey(team)) {
            fordFulkerson = fordFulkersonMap.get(team);
        } else {
            fordFulkerson = createFordFulkerson(team);
            fordFulkersonMap.put(team, fordFulkerson);
        }

        if (fordFulkerson == null) {
            final int teamIndex = teams.get(team);
            // Trivial elimination
            for (int i = 0; i < numberOfTeams(); i++) {
                if (wins[teamIndex] + remains[teamIndex] < wins[i]) {
                    certificate.add(teamsArray[i]);
                }
            }
            return certificate;
        }

        final Map<Integer, GameBetweenVertex> map = fordFulkersonToGameBetweenVertexMap.get(fordFulkerson);
        for (int i = 1; i <= numOfGameVertex(); i++) {
            if (fordFulkerson.inCut(i)) {
                certificate.add(teamsArray[map.get(i).v]);
                certificate.add(teamsArray[map.get(i).w]);
            }
        }
        return certificate.isEmpty() ? null : certificate;
    }

    private int numOfGameVertex() {
        return (numberOfTeams() - 1) * (numberOfTeams() - 2) / 2;
    }

    private FordFulkerson createFordFulkerson(final String team) {
        int teamIndex = teams.get(team);
        final FlowNetwork flowNetwork = new FlowNetwork(2 + (numberOfTeams() - 1)
                * (numberOfTeams() - 2) / 2 + numberOfTeams() - 1);
        int index = 1;
        final Map<Integer, GameBetweenVertex> flowVertexToGameBetweenVertexMap = new HashMap<>();

        // source to gamebetween vertex
        for (int i = 0; i < numberOfTeams(); i++) {
            for (int j = i + 1; j < numberOfTeams(); j++) {
                if (i == teamIndex || j == teamIndex) {
                    continue;
                }

                flowVertexToGameBetweenVertexMap.put(index, new GameBetweenVertex(i, j));
                final FlowEdge flowEdge = new FlowEdge(0, index++, gameBetween[i][j]);
                flowNetwork.addEdge(flowEdge);
            }
        }

        // gamebetween vertex to teams, minus the source
        int numOfGameBetweenVertex = index - 1;
        int flowVertexIndex = numOfGameBetweenVertex + 1;
        final Map<Integer, Integer> teamIndexToFlowVertexIndexMap = new HashMap<>();
        final Map<Integer, Integer> flowVertexIndexToTeamIndex = new HashMap<>();
        for (int i = 0; i < numberOfTeams(); i++) {
            if (i == teamIndex) {
                continue;
            }
            teamIndexToFlowVertexIndexMap.put(i, flowVertexIndex);
            flowVertexIndexToTeamIndex.put(flowVertexIndex, i);
            flowVertexIndex++;
        }

        for (int i = 1; i <= numOfGameBetweenVertex; i++) {
            final GameBetweenVertex gameBetweenVertex = flowVertexToGameBetweenVertexMap.get(i);
            final FlowEdge flowEdge1 = new FlowEdge(i, teamIndexToFlowVertexIndexMap.get(gameBetweenVertex.v), Double.POSITIVE_INFINITY);
            final FlowEdge flowEdge2 = new FlowEdge(i, teamIndexToFlowVertexIndexMap.get(gameBetweenVertex.w), Double.POSITIVE_INFINITY);
            flowNetwork.addEdge(flowEdge1);
            flowNetwork.addEdge(flowEdge2);
        }

        // teams to sink
        for (int flowNetWorkIndex = numOfGameBetweenVertex + 1; flowNetWorkIndex <= numOfGameBetweenVertex + numberOfTeams() - 1; flowNetWorkIndex++) {
            final int capacity = wins[teamIndex] + remains[teamIndex] - wins[flowVertexIndexToTeamIndex.get(flowNetWorkIndex)];
            if (capacity < 0) {
                return null;
            }

            final FlowEdge flowEdge = new FlowEdge(flowNetWorkIndex, flowNetwork.V() - 1, capacity);
            flowNetwork.addEdge(flowEdge);
        }

        final FordFulkerson fordFulkerson = new FordFulkerson(flowNetwork, 0, flowNetwork.V() - 1);
        fordFulkersonToGameBetweenVertexMap.put(fordFulkerson, flowVertexToGameBetweenVertexMap);
        return fordFulkerson;
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            }
            else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}
