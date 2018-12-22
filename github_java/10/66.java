package nl.hva.dmci.ict.se.datastructures.sortstudents.util;

import java.util.List;

/**
 * Bubblesort utility class om lijsten te sorteren
 *
 * @author Achmed Waly
 * @author Jerry Blaauw
 * @version 2.0
 */
public class Bubblesort {

    /**
     * Deze methode sorteert een lijst die wordt meegegeven
     * Hij sorteert door 2 getallen met elkaar te vergelijken in de lijst tot de grootste achteraan staat
     * Hij begint vooraan met het vergelijken van het eerste en tweede getal in de lijst, daarna de tweede en derde enz enz
     * Als het grootste getal achteraan staat, doet hij precies hetzelfde nog een keer, 
     * maar dan zonder het laatste getal meegenomen, want die heeft hij net goed gezet
     * Dit doet hij net zolang tot er nog maar 1 getal over is
     * 
     * @param <T> T kan van elk type zijn wat comparable is
     * @param lijst lijst die hij gaat sorteren
     */
    public static <T extends Comparable<T>> void sort(List<T> lijst) {
        //bron: https://stackoverflow.com/questions/16088994/sorting-an-array-of-int-using-bubblesort/16089042
        
        int n = lijst.size(); //slaat de grootte van de lijst op
        T temp; //dit is een variabel om tijdelijk een waarde op te slaan om uiteindelijk 2 getallen om te draaien

        //deze loop maakt de lijst steeds kleiner, zodat hij niet de getallen nog eens hoeft te controleren die hij goed heeft gezet
        for (int i = 0; i < n; i++) {
            
            //deze loop gaat elk getal af en kijkt of het getal voor hem groter is dan hemzelf
            for (int j = 1; j < (n - i); j++) {
                if (lijst.get(j - 1).compareTo(lijst.get(j)) > 0) {
                    
                    //hiermee ruilt hij de 2 getallen om de grootste na de kleinste te zetten
                    temp = lijst.get(j - 1);
                    lijst.set((j - 1), lijst.get(j));
                    lijst.set(j, temp);
                }

            }
        }
    }

}
