package algosound.data.algorithms;


import algosound.data.audio.Sonification;
import algosound.data.audio.OSC;
import algosound.util.AlgosoundUtil;

import java.awt.*;

import static algosound.data.audio.Sonification.INSERTIONSORT_SCALE;
import static algosound.data.audio.Sonification.INSERTIONSORT_WAVE;
import static algosound.util.AlgosoundUtil.expmap;

/**
 * Insertionsort implementation.
 * Handling of new frames and sending osc messages for sonification of insertionsort.
 * ================================
 *
 * @author ekzyis
 * @date 04/03/2018
 */
public class Insertionsort extends SortingAlgorithm {

    // Static field for access during creation of sonifications.
    // This cannot be static in SortingAlgorithm since all subclasses need their own definition of this.
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
        // Gain access to monitor. If not possible, wait here.
        synchronized (this) {
            // Wait until first frame has been drawn.
            notifyFrameReady();
            // First frame of insertionsort consists only of marking first element as sorted.
            elements[0].setSorted();
            notifyFrameReady();
            /**
             * ==================================
             * Start of actual sorting algorithm.
             * ==================================
             */
            /**
             * Starts with second element because insertionsort
             * assumes the first element as sorted.
             * (If you only have one element, it can not not be sorted.)
             */
            for (int i = 1; i < a.length && !isInterrupted(); ++i) {
                /**
                 * All elements to the left of current element are sorted.
                 * To visualize this, everytime the left element will be marked as sorted.
                 * This leads to all element to the left of the current element being sorted.
                 */
                elements[i - 1].setSorted();
                // Save value of element to insert.
                int value = a[i];
                // Also save color of visual element to insert.
                Color insertColor = elements[i].getColor();
                // Also save index of that element.
                int j = i;
                /**
                 * Iterate through the array to the left until
                 * correct place to insert element is found.
                 */
                while (j > 0 && a[j - 1] > value && !isInterrupted()) {
                    /**
                     * The integers don't swap places;
                     * the left element moves to the right
                     * overwriting the previous element on their right
                     * until the right place is found for current element.
                     */
                    a[j] = a[j - 1];
                    // Also move visual elements to the right.
                    moveRight(j - 1);
                    mark(j - 1);
                    j = j - 1;
                    // Notify since new frame is ready.
                    notifyFrameReady();
                    System.out.println("values to map: " + a[j] + ", " + value);
                    int[] args = {expmap(a[j], 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX), expmap(value, 0, AlgosoundUtil.H, FREQ_MIN, FREQ_MAX)};
                    System.out.println("mapped values: " + args[0] + ", " + args[1]);
                    osc.sendMessage(sel.MODPATHS.get(0), args);
                }
                // Place to insert has been found!
                a[j] = value;
                // Visualize inserting by modified element to look like the element which should be inserted.
                elements[j].setHeight(value);
                elements[j].setColor(insertColor);
                notifyFrameReady();
            }
        }
        osc.sendMessage(sel.FREEPATH);
        System.out.println("--- insertionsort-thread has terminated.");
    }

    /**
     * Copies element one step to the right, overriding the previous element.
     * On its previous place, there is still the same element.
     */
    private void moveRight(int i) {
        /**
         * Change the right element to look like the left element
         * to visualize overriding.
         */
        elements[i + 1].setHeight(elements[i].getHeight());
        elements[i + 1].setColor(elements[i].getColor());
    }

    // Native insertionsort implementation.
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
