/*
 * @(#)InsertionSortAlgorithm.java	1.0	97/02/15 Alyce Brady
 * based on @(#)BubbleSortAlgorithm.java	1.6f 95/01/31 James Gosling
 *
 * which had Copyright (c) 1994-1996 Sun Microsystems, Inc. All Rights Reserved.
 *
 * See additional copyright information below.
 *
 *
 * An insertion sort demonstration algorithm based on
 * SortAlgorithm.java and
 * SortItem.java.
 *
 */

class InsertionSortAlgorithm extends SortAlgorithm
{
    void sort(int a[]) throws Exception
    {
	// Loop through the array & put each item in the proper slot,
	// shifting other items out of the way as you go.
	for (int i = 1; i < a.length; i++ )
	{
	    int value = a[i];		// next item to be inserted in order
	    int j;

	    // Back up in the array to find the spot for value.
	    for ( j = i - 1; j >= 0 && a[j] > value; j-- )
            {
		if (stopRequested)
                {   return;
                }

                // This element is bigger than the element being inserted,
                // so move it up one slot.
                a[j+1] = a[j];
                pause(i,j);
            }
 
            // a[j] is the item that should precede value.
	    // Put value after it.
            a[j+1] = value;
	}
    }
}

/*
 * Permission information for original BubbleSort algorithm:
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for NON-COMMERCIAL or COMMERCIAL purposes and
 * without fee is hereby granted. 
 * Please refer to the file http://java.sun.com/copy_trademarks.html
 * for further important copyright and trademark information and to
 * http://java.sun.com/licensing.html for further important licensing
 * information for the Java (tm) Technology.
 * 
 * SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR
 * ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
 * DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 * 
 * THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 * CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 * PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 * NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 * SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 * SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 * PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES").  SUN
 * SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 * HIGH RISK ACTIVITIES.
 */