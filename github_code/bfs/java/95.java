package search;

import agent.State;
import agent.VacuumCleaner;
import environment.Environment;

import java.util.*;

import static auxiliary.AuxiliaryFunctions.findColumnOnGraph;
import static auxiliary.AuxiliaryFunctions.findRowOnGraph;

public class BreadthFirstSearch {

    private List<State> expanded;
    private Queue<State> edge;

    public BreadthFirstSearch(State initial) {
        this.expanded = new ArrayList<>();
        this.edge = new ArrayDeque<>();

        this.edge.add(initial);
    }

    private List<State> getExpanded() {

        return expanded;
    }

    private Queue<State> getEdge() {

        return edge;
    }

    public VacuumCleaner BFS(VacuumCleaner agent, Environment environment) {

        if (getEdge().peek() != null) {
            State actualState = getEdge().remove();

            if (!actualState.isObjective()) {
                int column;
                int row;

                if ((actualState.equals(environment.getInitialState()))) {
                    row = findRowOnGraph(actualState, environment);
                    expanded.add(actualState);
                    generateStates(actualState, row, environment);
                } else {
                    column = findColumnOnGraph(actualState, environment);
                    expanded.add(actualState);
                    generateStates(actualState, column, environment);
                }

                agent.setState(actualState);
                this.BFS(agent, environment);

            } else {
                agent.setState(actualState);
                return agent;
            }
        } else {
            System.out.println("Borda vazia, objetivo não encontrado!");
        }

        return agent;
    }

    private void generateStates(State actual, int i, Environment environment) {

        for (State state: environment.getGraph()[i]) {
            if (state != null) {
                if (!getExpanded().contains(state) &&
                        !getEdge().contains(state)) {

                    state.setFather(actual);
                    edge.add(state);
                }
            }
        }
    }
}
