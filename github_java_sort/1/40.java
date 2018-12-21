package algosound.data.algorithms;


import algosound.data.audio.Sonification;
import algosound.data.audio.OSC;
import algosound.util.AlgosoundUtil;

import java.awt.*;

import static algosound.data.audio.Sonification.INSERTIONSORT_SCALE;
import static algosound.data.audio.Sonification.INSERTIONSORT_WAVE;
import static algosound.util.AlgosoundUtil.expmap;


public class Insertionsort extends SortingAlgorithm {

    
    
    public static final String SUFFIX = "INSERTIONSORT";

    public Insertionsort(int N) {
        super(N);
        name = "Insertionsort";
        suffix = SUFFIX;
        sonifications.add(INSERTIONSORT_WAVE);
        sonifications.add(INSERTIONSORT_SCALE);
        selected_sonification = sonifications.get(0);
    }

    @Override
    public void run() {
        System.out.println("---insertionsort-thread starting.");

        OSC osc = OSC.getInstance();
        Sonification sel = selected_sonification;
        if (sel == INSERTIONSORT_WAVE) {
            osc.sendMessage(sel.STARTPATH);
        } else if (sel == INSERTIONSORT_SCALE) {
            int[] args = {FREQ_MIN, FREQ_MAX};
            osc.sendMessage(sel.STARTPATH, args);
        }
        
        synchronized (this) {
            
            notifyFrameReady();
            
            elements[0].setSorted();
            notifyFrameReady();
            
            
            for (int i = 1; i < a.length && !isInterrupted(); ++i) {
                
                elements[i - 1].setSorted();
                
                int value = a[i];
                
                Color insertColor = elements[i].getColor();
                
                int j = i;
                
                while (j > 0 && a[j - 1] > value && !isInterrupted()) {
                    
                    a[j] = a[j - 1];
                    
                    moveRight(j - 1);
                    mark(j - 1);
                    j = j - 1;
                    
                    notifyFrameReady();
                    System.out.println("values to map: " + a[j] + ", " + value);
                    int[] args = {expmap(a[j], 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX), expmap(value, 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX)};
                    System.out.println("mapped values: " + args[0] + ", " + args[1]);
                    osc.sendMessage(sel.MODPATHS.get(0), args);
                }
                
                a[j] = value;
                
                elements[j].setHeight(value);
                elements[j].setColor(insertColor);
                notifyFrameReady();
            }
        }
        osc.sendMessage(sel.FREEPATH);
        System.out.println("--- insertionsort-thread has terminated.");
    }

    
    private void moveRight(int i) {
        
        elements[i + 1].setHeight(elements[i].getHeight());
        elements[i + 1].setColor(elements[i].getColor());
    }

    
    public static void sort(int[] a) {
        for (int i = 1; i < a.length; ++i) {
            int value = a[i];
            int j = i;
            while (j > 0 && a[j - 1] > value) {
                a[j] = a[j - 1];
                j = j - 1;
            }
            a[j] = value;
        }
    }
}
