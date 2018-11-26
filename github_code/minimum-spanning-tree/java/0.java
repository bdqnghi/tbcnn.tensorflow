/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package minimum.spanning.tree;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;
import javax.swing.JPanel;

/**
 *
 * @author usu
 */
public class PanelTree extends JPanel {

    public static final int TREE_NONE = 0;
    public static final int TREE_KEMUNGKINAN = 1;
    public static final int TREE_PRIM = 2;
    public static final int TREE_KRUSKAL = 3;
    private int treeType;
    private ArrayList<Point> minimumSpanningTree;
    private ArrayList<Color> minimumSpanningTreeColor;
    private ArrayList<Point> minimumSpanningTreeHistory;
    private ArrayList<Color> minimumSpanningTreeColorHistory;
    private Random random;

    /*
     * Serial version UID
     */
    private static final long serialVersionUID = 1L;

    /**
     * 
     */
    public PanelTree() {
        super();

        setMinimumSpanningTree(new ArrayList<Point>());
        setMinimumSpanningTreeHistory(new ArrayList<Point>());
        setMinimumSpanningTreeColor(new ArrayList<Color>());
        setMinimumSpanningTreeColorHistory(new ArrayList<Color>());

        setRandom(new Random());
        showTree(TREE_NONE);
        addMouseListener(new MouseAdapter() {

            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                doMouseClick(e);
            }
        });
    }

    protected ArrayList<Color> getMinimumSpanningTreeColorHistory() {
        return minimumSpanningTreeColorHistory;
    }

    protected void setMinimumSpanningTreeColorHistory(ArrayList<Color> minimumSpanningTreeColorHistory) {
        this.minimumSpanningTreeColorHistory = minimumSpanningTreeColorHistory;
    }

    protected ArrayList<Point> getMinimumSpanningTreeHistory() {
        return minimumSpanningTreeHistory;
    }

    protected void setMinimumSpanningTreeHistory(ArrayList<Point> minimumSpanningTreeHistory) {
        this.minimumSpanningTreeHistory = minimumSpanningTreeHistory;
    }

    public boolean canUndo() {
        if (getMinimumSpanningTree().size() > 0) {
            return true;
        }
        return false;
    }

    public boolean canRedo() {
        if (getMinimumSpanningTreeHistory().size() > 0) {
            return true;
        }
        return false;
    }

    public void undo() {
        Point p = getMinimumSpanningTree().remove(getMinimumSpanningTree().size() - 1);
        getMinimumSpanningTreeHistory().add(p);
        repaint();
    }

    public void redo() {
        Point p = getMinimumSpanningTreeHistory().remove(getMinimumSpanningTreeHistory().size() - 1);
        getMinimumSpanningTree().add(p);
        repaint();
    }

    protected void doMouseClick(MouseEvent e) {
        getMinimumSpanningTree().add(e.getPoint());
        getMinimumSpanningTreeColor().add(new Color(getRandom().nextInt(255), getRandom().nextInt(255), getRandom().nextInt(255)));
        while (getMinimumSpanningTreeHistory().size() > 0) {
            getMinimumSpanningTreeHistory().remove(0);
        }
        repaint();
    }

    public void showTree(int type) {
        treeType = type;
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2 = (Graphics2D) g.create();
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        if (getMinimumSpanningTree().size() > 0) {

            if (treeType != TREE_NONE) {
                ArrayList<Point> source = new ArrayList<Point>();
                for (Point p : getMinimumSpanningTree()) {
                    source.add(p);
                }
                if (treeType == TREE_KEMUNGKINAN) {
                    g2.setColor(getBackground());
                    for (int i = 0; i < source.size(); i++) {
                        Point p1 = source.get(i);
                        for (int j = 0; j < source.size(); j++) {
                            if (i != j) {
                                Point p2 = source.get(j);
                                g2.drawLine(p1.x, p1.y, p2.x, p2.y);
                            }
                        }
                    }
                } else if (treeType == TREE_PRIM) {
                    g2.setColor(getBackground());
                    ArrayList<Sisi> arraySisi = new ArrayList<Sisi>();
                    for (int i = 0; i < source.size(); i++) {
                        Point p1 = source.get(i);
                        for (int j = 0; j < source.size(); j++) {
                            if (i != j) {
                                Point p2 = source.get(j);
                                arraySisi.add(new Sisi(p1, p2, getDistance(p1, p2)));
                            }
                        }
                    }

                    removeDuplicate(arraySisi);

                    Collections.sort(arraySisi, new Comparator<Sisi>() {

                        public int compare(Sisi o1, Sisi o2) {
                            return ((Double) o1.getDistance()).compareTo(((Double) o2.getDistance()));
                        }
                    });

                    ArrayList<Sisi> result = new ArrayList<Sisi>();
                    result.add(arraySisi.remove(0));

                    for (int i = 0; i < source.size() - 2; i++) {
                        for (int j = 0; j < arraySisi.size(); j++) {
                            Sisi s = arraySisi.get(j);
                            if (isBeside(result, s)) {
                                if (!isCircular(result, s)) {
                                    arraySisi.remove(s);
                                    result.add(s);
                                    break;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < getMinimumSpanningTree().size(); i++) {
                        g2.setColor(getMinimumSpanningTreeColor().get(i));
                        Point p = getMinimumSpanningTree().get(i);
                        g2.fillOval(p.x - 5, p.y - 5, 10, 10);
                    }

                    g2.setColor(getBackground());
                    for (Sisi s : result) {
                        g2.drawLine(s.getFrom().x, s.getFrom().y, s.getTo().x, s.getTo().y);
                    }

                    g2.setColor(Color.RED);
                    for (Sisi s : result) {
                        int x = s.getFrom().x + (s.getTo().x - s.getFrom().x) / 2;
                        int y = s.getFrom().y + (s.getTo().y - s.getFrom().y) / 2;
                        g2.drawString("" + s.getDistance(), x, y);
                    }

                } else if (treeType == TREE_KRUSKAL) {
                    g2.setColor(getBackground());
                    ArrayList<Sisi> arraySisi = new ArrayList<Sisi>();
                    for (int i = 0; i < source.size(); i++) {
                        Point p1 = source.get(i);
                        for (int j = 0; j < source.size(); j++) {
                            if (i != j) {
                                Point p2 = source.get(j);
                                arraySisi.add(new Sisi(p1, p2, getDistance(p1, p2)));
                            }
                        }
                    }

                    removeDuplicate(arraySisi);

                    Collections.sort(arraySisi, new Comparator<Sisi>() {

                        public int compare(Sisi o1, Sisi o2) {
                            return ((Double) o1.getDistance()).compareTo(((Double) o2.getDistance()));
                        }
                    });

                    ArrayList<Sisi> result = new ArrayList<Sisi>();
                    result.add(arraySisi.remove(0));

                    while (result.size() < source.size() - 1) {
                        for (int j = 0; j < arraySisi.size(); j++) {
                            Sisi s = arraySisi.get(j);
                            if (isBeside(result, s)) {
                                if (!isCircular(result, s)) {
                                    result.add(arraySisi.remove(j));
                                    break;
                                }
                            }
                        }
                    }
                    for (Sisi s : result) {
                        g2.drawLine(s.getFrom().x, s.getFrom().y, s.getTo().x, s.getTo().y);
                    }

                    g2.setColor(Color.YELLOW);
                    for (Sisi s : result) {
                        int x = s.getFrom().x + (s.getTo().x - s.getFrom().x) / 2;
                        int y = s.getFrom().y + (s.getTo().y - s.getFrom().y) / 2;
                        g2.drawString("" + s.getDistance(), x, y);
                    }
                }
            }

            for (int i = 0; i < getMinimumSpanningTree().size(); i++) {
                g2.setColor(getMinimumSpanningTreeColor().get(i));
                Point p = getMinimumSpanningTree().get(i);
                g2.fillOval(p.x - 5, p.y - 5, 10, 10);
            }

        }

    }

    public static void removeDuplicate(ArrayList<Sisi> array) {
        int index = 0;
        while (index < array.size()) {
            Sisi s = array.get(index);
            for (int j = index + 1; j < array.size(); j++) {
                Sisi s2 = array.get(j);
                if (s.equals(s2)) {
                    array.remove(s2);
                } else {
                    if (s.getFrom() == s2.getTo() && s.getTo() == s2.getFrom()) {
                        array.remove(s2);
                    }
                }
            }
            index++;
        }
    }

    public ArrayList<Point> getMinimumSpanningTree() {
        return minimumSpanningTree;
    }

    public void setMinimumSpanningTree(ArrayList<Point> minimumSpanningTree) {
        this.minimumSpanningTree = minimumSpanningTree;
    }

    public Random getRandom() {
        return random;
    }

    public void setRandom(Random random) {
        this.random = random;
    }

    public ArrayList<Color> getMinimumSpanningTreeColor() {
        return minimumSpanningTreeColor;
    }

    public void setMinimumSpanningTreeColor(ArrayList<Color> minimumSpanningTreeColor) {
        this.minimumSpanningTreeColor = minimumSpanningTreeColor;
    }

    public void clearTree() {
        while (getMinimumSpanningTree().size() > 0) {
            getMinimumSpanningTree().remove(0);
            getMinimumSpanningTreeColor().remove(0);
        }
        showTree(TREE_NONE);
        repaint();
    }

    public static double getDistance(Point p1, Point p2) {
        double result = Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
        return result;
    }

    public static boolean isCircular(ArrayList<Sisi> result, Sisi s) {
        boolean curcular = false;

        ArrayList<Point> temp = new ArrayList<Point>();

        for (int i = 0; i < result.size(); i++) {
            Sisi sisiTemp = result.get(i);
            temp.add(sisiTemp.getFrom());
            temp.add(sisiTemp.getTo());
        }

        int index = 0;
        while (index < temp.size()) {
            Point p = temp.get(index);
            for (int i = index; i < temp.size(); i++) {
                if (i != index) {
                    Point p2 = temp.get(i);
                    if (p == p2) {
                        temp.remove(i);
                    }
                }
            }
            index++;
        }

        if (temp.contains(s.getFrom()) && temp.contains(s.getTo())) {
            curcular = true;
        }

        return curcular;
    }

    public static boolean isBeside(ArrayList<Sisi> result, Sisi s) {
        for (int i = 0; i < result.size(); i++) {
            if (result.get(i).getFrom() == s.getFrom() || result.get(i).getFrom() == s.getTo() || result.get(i).getTo() == s.getFrom() || result.get(i).getTo() == s.getTo()) {
                return true;
            }
        }
        return false;
    }

    private class Sisi {

        private Point from,  to;
        private double distance;

        public Sisi(Point from,
                Point to,
                double distance) {
            this.from = from;
            this.to = to;
            this.distance = distance;
        }

        public double getDistance() {
            return distance;
        }

        public void setDistance(double distance) {
            this.distance = distance;
        }

        public Point getFrom() {
            return from;
        }

        public void setFrom(Point from) {
            this.from = from;
        }

        public Point getTo() {
            return to;
        }

        public void setTo(Point to) {
            this.to = to;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null) {
                return false;
            }
            if (getClass() != obj.getClass()) {
                return false;
            }
            final Sisi other = (Sisi) obj;
            if (this.from != other.from && (this.from == null || !this.from.equals(other.from))) {
                return false;
            }
            if (this.to != other.to && (this.to == null || !this.to.equals(other.to))) {
                return false;
            }
            if (this.distance != other.distance) {
                return false;
            }
            return true;
        }

        @Override
        public int hashCode() {
            int hash = 3;
            hash = 71 * hash + (this.from != null ? this.from.hashCode() : 0);
            hash = 71 * hash + (this.to != null ? this.to.hashCode() : 0);
            hash = 71 * hash + (int) (Double.doubleToLongBits(this.distance) ^ (Double.doubleToLongBits(this.distance) >>> 32));
            return hash;
        }
    }
}
