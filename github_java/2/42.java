package client;

import game.draw.Drawer;
import game.entities.Dragon;
import game.logic.trees.AVLTree;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.slf4j.Marker;
import org.slf4j.MarkerFactory;
import util.Math;
import game.logic.lists.SimpleList;
import game.logic.trees.BinaryTree;
import game.logic.trees.TreeNode;

import java.util.List;

public class WaveGenerator {

    private static Logger logger = LoggerFactory.getLogger(WaveGenerator.class);
    private static final Marker SYS = MarkerFactory.getMarker("SYS");
    private static SimpleList<SimpleList<Dragon>> treeList = new SimpleList<>();
    private static String[] waveSortMethod = {"selection", "insertion", "quick", "binary-tree", "avl-tree"};
    private static RestClient client = new RestClient();

    /**
     * Get Method that ask to the client for a new Wave
     * @param size of the wave required
     * @return the new Wave
     */
    public static Wave getNewWave(int size) {
        Wave wave = client.getNewWave(size);
        unSortWave(wave);
        return wave;
    }

    public static void deleteWave(long id) {
        client.deleteWave(id);
    }


    /**
     * Put method that sends a Wave to the client to received sorted
     * @param wave the wave to sort
     * @param type last formation
     * @return the wave sorted and added to the GUI
     */
    public static Wave getWaveSorted(Wave wave, int type) {
        treeList = new SimpleList<>();
        int i = type % waveSortMethod.length;
        String sort = waveSortMethod[i];
        wave.setFormation(sort);

        // Here the client ask for a sorted wave
        Wave newWave = client.getWaveSorted(wave, sort);

        // Reposition the Dragons in formation
        if (i < 3) sort = "list";
        if (i == 3) sort = "binary-tree";
        if (i == 4) sort = "avl-tree";

        // Determines based in "sort" the formation of the wave
        if (sort.equals("list")) {
            switchListWave(wave.dragonsList, newWave.dragonsList);
            listWave(wave);
        } else if (sort.equals("binary-tree")){
            wave.setDragonsBinaryTree(newWave.getDragonsBinaryTree());
            switchBinaryWave(wave);
            readTree(wave.getDragonsBinaryTree().getRoot());
            treeWave(wave.dragonsList);
        } else if (sort.equals("avl-tree")){
            wave.setDragonsAVLTree(newWave.getDragonsAVLTree());
            switchAVLWave(wave);
            readTree(wave.getDragonsAVLTree().getRoot());
            treeWave(wave.dragonsList);
        }
        return wave;
    }

    private static void switchListWave(List<Dragon> list, List<Dragon> newList) {
        for (int i = 0; i < list.size(); i++){
            Dragon dragon = list.get(i);
            for (int j = 0; j < newList.size(); j++ ){
                if (newList.get(j).getAge() == dragon.getAge()){
                    Dragon tmp = list.get(j);
                    list.set(j, dragon);
                    list.set(i, tmp);
                    break;
                }
            }
        }
    }

    private static void switchBinaryWave(Wave wave) {
        List<Dragon> dragonList = wave.getDragonsList();
        BinaryTree tree = wave.getDragonsBinaryTree();
        for (Dragon dragon : dragonList) {
            tree.setDragon(dragon);
        }
    }

    private static void switchAVLWave(Wave wave) {
        List<Dragon> dragonList = wave.getDragonsList();
        AVLTree tree = wave.getDragonsAVLTree();
        for (Dragon dragon : dragonList) {
            tree.setDragon(dragon);
        }
    }

    /**
     * Gets a new Wave in disorder pattern
     * @param wave the wave to disorder
     */
    private static void unSortWave(Wave wave){
        List<Dragon> dragons = wave.getDragonsList();
        int waveSize = wave.getSize();
        int columns = 8;
        int rows = waveSize / columns;
        double width = Drawer.width / 2;
        double height = Drawer.height;
        double xOffset = width / columns;
        double yOffset = height / (rows + 1);
        double xPoss = Drawer.width;
        double yMax = yOffset * rows;

        int n = 0;
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                double x = (i + 1) * xOffset;
                double y = Math.getRandomNumberInRange(0, (int) yMax);
                x += xPoss;
                generateDragon(x, y, dragons, n);
                n++;
            }
        }
    }

    /**
     * Makes an cubic like formation
     * @param wave the wave to order
     */
    private static void listWave(Wave wave) {
        List<Dragon> dragons = wave.getDragonsList();
        int waveSize = wave.getSize();
        int columns = (int) java.lang.Math.sqrt(waveSize);
        int rows = waveSize / columns;
        double width = Drawer.width / 2;
        double height = Drawer.height;
        double xOffset = width / columns;
        double yOffset = height / (rows + 1);
        double xPoss = getMinXPoss(dragons) - xOffset;

        int xi = 0;
        int n = 0;
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                double x = (i + 1) * xOffset;
                double y = (j + 1) * yOffset;
                Dragon dragon = dragons.get(n);
                x += xPoss;
                // Sets the position of the Dragon to animate
                dragon.setPoss(x, y);
                n++;
            }
            xi = i + 1;
        }

        // Adds the extra Dragons to the formation
        while(n < dragons.size()){
            columns += 1;
            for (int j = 0; j < rows; j++) {
                double y = (j + 1) * yOffset;
                double x = (xi + 1) * xOffset;
                Dragon dragon = dragons.get(n);
                dragon.setPoss(x, y);
            }
            n++;
        }

    }

    /**
     * Translates the Dragons received from the Server
     * @param x xPoss
     * @param y yPoss
     * @param list list of dragons
     * @param i position of the Dragon in the Wave
     */
    private static void generateDragon(double x, double y, List<Dragon> list, int i) {
        Dragon dragon = list.get(i);
        int parentAge = dragon.getParentAge();
        int age = dragon.getAge();
        String rank = dragon.getRank();
        String name = dragon.getName();
        int lives = dragon.getLives();
        int fire_rate = dragon.getFire_rate();
        list.set(i, new Dragon(x, y, parentAge, age, rank, name, lives, fire_rate));
    }

    /**
     * Looks for the minimum xPosition to place the Dragons
     * @param dragons list of the wave
     * @return the minimum xPoss
     */
    private static double getMinXPoss(List<Dragon> dragons){
        double result = dragons.get(0).getxPoss();
        for (Dragon dragon : dragons){
            if (dragon.getxPoss() < result){
                result = dragon.getxPoss();
            }
        }
        return result;
    }

    /**
     *
     */
    private static void treeWave(List<Dragon> dragons) {
        double width = Drawer.width;
        double height = Drawer.height;
        int columns = treeList.getLarge();
        double xOffset = width / columns;
        double xPoss = getMinXPoss(dragons);

        for (int i = 0; i < columns; i++){
            SimpleList<Dragon> list = treeList.getByIndex(i).getValue();
            int rows = list.getLarge();
            double yOffset = height / (rows + 1);

            for (int j = 0; j < rows; j++){
                double x = (i + 1) * xOffset;
                double y = (j + 1) * yOffset;
                x += xPoss;
                Dragon dragon = list.getByIndex(j).getValue();
                dragon.setPoss(x, y);
            }
        }
    }

    private static void readTree(TreeNode current){
        insertOnTreeList(current);
        if(current.left != null){
            readTree(current.left);
        }
        if (current.right != null){
            readTree(current.right);
        }
    }

    private static void insertOnTreeList(TreeNode node){
        int i = node.getLevel();
        while (treeList.getByIndex(i) == null){
            treeList.addAtEnd(new SimpleList<>());
        }
        treeList.getByIndex(i).getValue().addAtEnd(node.dragon);
    }



}
