/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hanoiTower;

import framework_puzzle.Canvas;
import framework_puzzle.Move;
import framework_puzzle.Problem;
import framework_puzzle.State;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Nam Phung
 */
public class HanoiTowerProblem extends Problem {

    /**
     * This constructor stores an introductory message describing the problem,
     * the problem's possible moves, the initial state, and final state, by
     * sending them to the parent <b>Problem</b> class. It also creates and
     * sends lists of other initial states and final states for selection in a
     * problem chooser.
     */
    public HanoiTowerProblem() {

        List<Move> moves = new ArrayList<Move>();
        moves.add(new HanoiTowerMove("Move disk from p to q"));
        moves.add(new HanoiTowerMove("Move disk from p to r"));
        moves.add(new HanoiTowerMove("Move disk from q to p"));
        moves.add(new HanoiTowerMove("Move disk from q to r"));
        moves.add(new HanoiTowerMove("Move disk from r to p"));
        moves.add(new HanoiTowerMove("Move disk from r to q"));

        HanoiTowerState start1 = new HanoiTowerState("12", "", "");
        HanoiTowerState final1 = new HanoiTowerState("", "", "12");

        HanoiTowerState start2 = new HanoiTowerState("123", "", "");
        HanoiTowerState final2 = new HanoiTowerState("", "", "123");

        HanoiTowerState start3 = new HanoiTowerState("1234", "", "");
        HanoiTowerState final3 = new HanoiTowerState("", "", "1234");

        HanoiTowerState start4 = new HanoiTowerState("12345", "", "");
        HanoiTowerState final4 = new HanoiTowerState("", "", "12345");

        HanoiTowerState start5 = new HanoiTowerState("123456", "", "");
        HanoiTowerState final5 = new HanoiTowerState("", "", "123456");

        HanoiTowerState start6 = new HanoiTowerState("1234567", "", "");
        HanoiTowerState final6 = new HanoiTowerState("", "", "1234567");

        HanoiTowerState start7 = new HanoiTowerState("12345678", "", "");
        HanoiTowerState final7 = new HanoiTowerState("", "", "12345678");

        HanoiTowerState start8 = new HanoiTowerState("123456789", "", "");
        HanoiTowerState final8 = new HanoiTowerState("", "", "123456789");

        List<State> startStates = new ArrayList<State>();
        List<State> finalStates = new ArrayList<State>();
        List<Integer> moveCounts = new ArrayList<Integer>();

        startStates.add(start1);
        finalStates.add(final1);
        moveCounts.add(3);
        startStates.add(start2);
        finalStates.add(final2);
        moveCounts.add(7);
        startStates.add(start3);
        finalStates.add(final3);
        moveCounts.add(15);
        startStates.add(start4);
        finalStates.add(final4);
        moveCounts.add(31);
        startStates.add(start5);
        finalStates.add(final5);
        moveCounts.add(63);
        startStates.add(start6);
        finalStates.add(final6);
        moveCounts.add(127);
        startStates.add(start7);
        finalStates.add(final7);
        moveCounts.add(255);
        startStates.add(start8);
        finalStates.add(final8);
        moveCounts.add(511);

        setInitialStates(startStates);
        setFinalStates(finalStates);
        setMoveCounts(moveCounts);

        setCurrentState(start1);
        setFinalState(final1);

        List<Canvas> initialCanvas = new ArrayList();
        for (State s : startStates) {
            initialCanvas.add(new HanoiTowerCanvasIconified(s));
        }

        List<Canvas> finalCanvas = new ArrayList();
        for (State s : finalStates) {
            finalCanvas.add(new HanoiTowerCanvasIconified(s));
        }

        setInitialCanvas(initialCanvas);
        setFinalCanvas(finalCanvas);

        setMoves(moves);
        setIntroduction(
                "Welcome to the Tower of Hanoi Problem\n\n"
                + "The problem consists of a table top with three places p, q, and r,\n"
                + "and a variable number of disks that can be arranged in \n"
                + "places on the table or stacked on one another.  A legal action is to \n"
                + "move a disk from one place or disk onto another place or disk, with\n"
                + "the only restrictions being that the moved disk must be smaller than the\n"
                + "disk in the destination stack");
    }

    /**
     * Checks for whether this problem has been successfully solved.
     *
     * @return true if the current state is equal to the final state, false
     * otherwise
     */
    @Override
    public boolean success() {
        HanoiTowerState currentState = (HanoiTowerState) getCurrentState();
        HanoiTowerState finalState = (HanoiTowerState) getFinalState();
        return currentState.equals(finalState);
    }

    @Override
    public boolean isFinalState(State currentState) {
        return currentState.equals(this.getFinalState());
    }
}
