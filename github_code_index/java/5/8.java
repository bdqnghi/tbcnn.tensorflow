package pathsim.algo;

import java.awt.Point;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;
import java.util.logging.Level;
import java.util.logging.Logger;
import pathsim.gui.panels.MainPanel;
import pathsim.map.Tile;

public class DFS extends Algorithm {

    public DFS() {
        super();
    }
    
    private Point p;
    private Tile current;
    private Stack tileStack;
    private LinkedList visList;
    private HashMap<Tile, Tile> prevHash;

    public void pathfind() {
        if(!initialized) {
            map.unmarkAllTiles();
            
            p = origin;

            current = map.tileAt(p);
            tileStack = new Stack();
            visList = new LinkedList();
            prevHash = new HashMap<Tile, Tile>();

            current.mark();
            tileStack.push(current);
            visList.add(current);
            
            initialized = true;
        }
        
        if(!tileStack.empty() && state == State.tracing) {
              current = (Tile) tileStack.peek();
              p = current.getLocation();
        
              if(current == map.tileAt(destination.x, destination.y)) {
                 initialized = false;
                 
                 for(Tile tile = map.tileAt(destination); tile != null; tile = prevHash.get(tile))
                     tile.markTrail();
                 
                 MainPanel.bStart.setEnabled(true);
                 MainPanel.bPause.setEnabled(false);
                 MainPanel.bStop.setEnabled(false);
                 javax.swing.JOptionPane.showMessageDialog(null, "Path Found!", "Success", javax.swing.JOptionPane.INFORMATION_MESSAGE);
                 state = state.idle;
                 return;
              }              

              if(map.tileAt(p.x, p.y-1) != null && !map.tileAt(p.x, p.y-1).marked() && map.tileAt(p.x, p.y-1).passable() && !visList.contains(map.tileAt(p.x, p.y-1))) {
                 map.tileAt(p.x, p.y-1).mark();
                 tileStack.push(map.tileAt(p.x, p.y-1)); // LEFT
                 visList.add(map.tileAt(p.x, p.y-1));
                 prevHash.put(map.tileAt(p.x, p.y-1), current);
              } else if(map.tileAt(p.x-1, p.y) != null && !map.tileAt(p.x-1, p.y).marked() && map.tileAt(p.x-1, p.y).passable() && !visList.contains(map.tileAt(p.x-1, p.y))) {
                 map.tileAt(p.x-1, p.y).mark();
                 tileStack.push(map.tileAt(p.x-1, p.y)); // UP
                 visList.add(map.tileAt(p.x-1, p.y));
                 prevHash.put(map.tileAt(p.x-1, p.y), current);
              } else if(map.tileAt(p.x, p.y+1) != null && !map.tileAt(p.x, p.y+1).marked() && map.tileAt(p.x, p.y+1).passable() && !visList.contains(map.tileAt(p.x, p.y+1))) {
                 map.tileAt(p.x, p.y+1).mark();
                 tileStack.push(map.tileAt(p.x, p.y+1)); // RIGHT
                 visList.add(map.tileAt(p.x, p.y+1));
                 prevHash.put(map.tileAt(p.x, p.y+1), current);
              } else if(map.tileAt(p.x+1, p.y) != null && !map.tileAt(p.x+1, p.y).marked() && map.tileAt(p.x+1, p.y).passable() && !visList.contains(map.tileAt(p.x+1, p.y))) {
                 map.tileAt(p.x+1, p.y).mark();
                 tileStack.push(map.tileAt(p.x+1, p.y)); // DOWN
                 visList.add(map.tileAt(p.x+1, p.y));
                 prevHash.put(map.tileAt(p.x+1, p.y), current);
              } else
                 current = (Tile) tileStack.pop();
            try {
                Thread.sleep(40);
            } catch (InterruptedException ex) {
                Logger.getLogger(BFS.class.getName()).log(Level.SEVERE, null, ex);
            }
        }          
        
        if(tileStack.empty()) {
           initialized = false;
           MainPanel.bStart.setEnabled(true);
           MainPanel.bPause.setEnabled(false);
           MainPanel.bStop.setEnabled(false);
           javax.swing.JOptionPane.showMessageDialog(null, "No Path Available.", "Failure", javax.swing.JOptionPane.INFORMATION_MESSAGE);
           state = state.idle;
        }
    }
    
}