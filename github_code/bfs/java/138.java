package utilities;

import bot.BotState;
import move.MoveType;

import java.awt.*;
import java.util.ArrayList;

@SuppressWarnings("WeakerAccess")
public class MakeMove {
    private Pathfinder pathfinder;
    private BFS playerBfs;
    private BFS antagonistBFS;
    private BombManager bombManager;
    private BugManager bugManager;

    public MakeMove(BFS playerBfs) {
        this.pathfinder = new Pathfinder();
        this.playerBfs = playerBfs;
        this.antagonistBFS = new BFS(playerBfs.getWidth(), playerBfs.getHeight());
        this.bombManager = new BombManager();
        this.bugManager = new BugManager(playerBfs.getWidth(), playerBfs.getHeight());
    }

    public MoveType escapeBomb(BotState state, ArrayList<Point> bombHarazd) {
        return pathfinder.findPath(state, playerBfs.getParent(), bombManager.saveField(state, bombHarazd, playerBfs));
    }


    public MoveType getBomb(BotState state) {

        playerBfs.clear();
        playerBfs.startBFS(state.getField().getMyPosition(), state);

        BFS localBFS = new BFS(playerBfs.getWidth(), playerBfs.getHeight());
        Double[][] distance = playerBfs.getDistance();

        double closestDistanceBomb = Double.POSITIVE_INFINITY;
        Point clsBombPos = new Point(-1, -1);

        for (Point point : state.getField().getBombPositions()) {
            if (distance[point.x][point.y] < closestDistanceBomb) {
                closestDistanceBomb = distance[point.x][point.y];
                clsBombPos = point;
            }
        }

        if (clsBombPos.equals(new Point(-1, -1)))
            return pathfinder.findPath(state, playerBfs.getParent(), clsBombPos);

        double closestDistanceSnipp = Double.POSITIVE_INFINITY;
        Point clsSnippPos = new Point(-1, -1);
        for (Point point : state.getField().getBombPositions()) {
            if (distance[point.x][point.y] < closestDistanceSnipp) {
                closestDistanceSnipp = distance[point.x][point.y];
                clsSnippPos = point;
            }
        }

        if (clsSnippPos.equals(new Point(-1, -1)))
            return pathfinder.findPath(state, playerBfs.getParent(), clsBombPos);

        localBFS.clear();
        localBFS.startBFS(clsSnippPos, state);

        if (closestDistanceSnipp < closestDistanceBomb + localBFS.getDistance()[clsSnippPos.x][clsSnippPos.y] + 9) {
            return pathfinder.findPath(state, playerBfs.getParent(), clsSnippPos);
        } else
            return pathfinder.findPath(state, playerBfs.getParent(), clsBombPos);
    }

    public MoveType getSnippet(BotState state) {

        playerBfs.clear();
        playerBfs.startBFS(state.getField().getMyPosition(), state);

        antagonistBFS.clear();
        antagonistBFS.startBFS(state.getField().getOpponentPosition(), state);

        Double[][] distance = playerBfs.getDistance();
        double closestDistanceSnipp = Double.POSITIVE_INFINITY;
        Point clsSnippPos = new Point(-1, -1);

        for (Point point : state.getField().getSnippetPositions()) {
            if (distance[point.x][point.y] < closestDistanceSnipp) {
                closestDistanceSnipp = distance[point.x][point.y];
                clsSnippPos = point;
            }
        }
        if (clsSnippPos.equals(new Point(-1, -1)))
            return pathfinder.findPath(state, playerBfs.getParent(), clsSnippPos);

        if (state.getField().getSnippetPositions().size() > 1 && antagonistBFS.getDistance()[clsSnippPos.x][clsSnippPos.y] > closestDistanceSnipp) {

            double TMPClosestDistanceSnipp = Double.POSITIVE_INFINITY;
            Point TMPClsSnippPos = new Point(-1, -1);

            for (Point point : state.getField().getSnippetPositions()) {
                if (distance[point.x][point.y] < TMPClosestDistanceSnipp && !TMPClsSnippPos.equals(clsSnippPos)) {
                    TMPClosestDistanceSnipp = distance[point.x][point.y];
                    TMPClsSnippPos = point;
                }
            }
            clsSnippPos = TMPClsSnippPos;
        }
        return pathfinder.findPath(state, playerBfs.getParent(), clsSnippPos);
    }
}
