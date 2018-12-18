package algosound.data.algorithms;

import algosound.data.audio.Sonification;
import algosound.data.audio.OSC;
import algosound.util.AlgosoundUtil;

import static algosound.data.audio.Sonification.SELECTIONSORT_SCALE;
import static algosound.data.audio.Sonification.SELECTIONSORT_WAVE;
import static algosound.util.AlgosoundUtil.expmap;
import static processing.core.PApplet.map;


public class Selectionsort extends SortingAlgorithm {

    
    
    public static final String SUFFIX = "SELECTIONSORT";

    public Selectionsort(int N) {
        super(N);
        name = "Selectionsort";
        suffix = SUFFIX;
        sonifications.add(SELECTIONSORT_WAVE);
        sonifications.add(SELECTIONSORT_SCALE);
        selected_sonification = sonifications.get(0);
    }

    @Override
    public void run() {
        System.out.println("--- selectionsort-thread has started.");

        OSC osc = OSC.getInstance();
        Sonification sel = selected_sonification;
        if (sel == SELECTIONSORT_WAVE) {
            osc.sendMessage(sel.STARTPATH);
        } else if (sel == SELECTIONSORT_SCALE) {
            int[] args = {FREQ_MIN, FREQ_MAX};
            osc.sendMessage(sel.STARTPATH, args);
        }
        
        synchronized (this) {
            
            notifyFrameReady();
            
            int start = 0;
            do {
                int minIndex = start;
                for (int i = minIndex + 1; i < a.length & !isInterrupted(); ++i) {
                    int arg1 = expmap(a[i], 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX);
                    float pan = map(i, 0, elements.length - 1, -1, 1);
                    if (a[i] < a[minIndex]) {
                        minIndex = i;
                        int arg2 = expmap(a[minIndex], 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX);
                        float[] args = {arg2, 0};
                        osc.sendMessage(sel.MODPATHS.size() == 2 ? sel.MODPATHS.get(1) : sel.MODPATHS.get(0), args);
                    }
                    
                    mark(minIndex);
                    mark(i);
                    float[] args = {arg1, pan};
                    osc.sendMessage(sel.MODPATHS.get(0), args);
                    notifyFrameReady();
                }
                int tmp = a[minIndex];
                a[minIndex] = a[start];
                a[start] = tmp;
                swap(minIndex, start);
                elements[start].setSorted();
                notifyFrameReady();
                start++;
            } while (start < a.length & !isInterrupted());
        }
        osc.sendMessage(sel.FREEPATH);
        System.out.println("--- selectionsort-thread has terminated.");
    }
}
