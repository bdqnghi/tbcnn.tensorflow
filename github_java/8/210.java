/*
 * NOTICE
 * This software was produced for the U.S. Government and is subject to the
 * Rights in Data-General Clause 5.227-14 (May 2014).
 * Copyright 2018 The MITRE Corporation. All rights reserved.
 *
 * “Approved for Public Release; Distribution Unlimited” Case  18-2165
 *
 * This project contains content developed by The MITRE Corporation.
 * If this code is used in a deployment or embedded within another project,
 * it is requested that you send an email to opensource@mitre.org
 * in order to let us know where this software is being used.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package keyterms.util.text.distance;

import java.nio.CharBuffer;

import org.junit.Test;

import keyterms.util.collect.Bags;

import static org.junit.Assert.assertEquals;

public class JaroWinkler_UT {

    private JaroWinkler editDistance = new JaroWinkler();

    @Test
    public void lenient() {
        // Checking that no errors occur
        editDistance.getDistance(null, null);
        editDistance.getDistance(null, "Jello Pudding!");
        editDistance.getDistance("Jello Pudding!", null);
        editDistance.getDistance(null, "dog".toCharArray());
        editDistance.getDistance(null, CharBuffer.wrap("dog".toCharArray()));
        editDistance.getDistance(null, new Character[] { 'd', null, 'g' });
        editDistance.getDistance(null, Bags.arrayList('d', null, 'g'));
    }

    @Test
    public void jaroDistance() {
        editDistance = new JaroWinkler(false, 0.1, false);
        assertEquals(0, editDistance.getDistance("", ""), 0);
        assertEquals(1, editDistance.getDistance("MARTHA", ""), 0);
        assertEquals(1, editDistance.getDistance("", "MARTHA"), 0);
        assertEquals(0, editDistance.getDistance("MARTHA", "MARTHA"), 0);
        assertEquals(0.1777777777777777, editDistance.getDistance("MARTHA", "MARHTZ"), 0.0000000000000001);
        assertEquals(0.05555555555555547, editDistance.getDistance("MARTHA", "MARHTA"), 0.00000000000000001);
        assertEquals(0.1777777777777777, editDistance.getDistance("DWAYNE", "DUANE"), 0.0000000000000001);
        assertEquals(0.2333333333333334, editDistance.getDistance("DIXON", "DICKSONX"), 0.0000000000000001);
    }

    @Test
    public void editDistance() {
        assertEquals(0, editDistance.getDistance("", ""), 0);
        assertEquals(1, editDistance.getDistance("MARTHA", ""), 0);
        assertEquals(1, editDistance.getDistance("", "MARTHA"), 0);
        assertEquals(0, editDistance.getDistance("MARTHA", "MARTHA"), 0);
        assertEquals(0.12444444444444436, editDistance.getDistance("MARTHA", "MARHTZ"), 0.00000000000000001);
        assertEquals(0.03888888888888886, editDistance.getDistance("MARTHA", "MARHTA"), 0.00000000000000001);
        assertEquals(0.15999999999999992, editDistance.getDistance("DWAYNE", "DUANE"), 0.00000000000000001);
        assertEquals(0.18666666666666676, editDistance.getDistance("DIXON", "DICKSONX"), 0.00000000000000001);
    }
}