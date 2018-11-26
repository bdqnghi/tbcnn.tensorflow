/*
 * Copyright 2004-2010 Information & Software Engineering Group (188/1)
 *                     Institute of Software Technology and Interactive Systems
 *                     Vienna University of Technology, Austria
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.ifs.tuwien.ac.at/dm/somtoolbox/license.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package at.tuwien.ifs.somtoolbox.layers.quality;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeMap;

import at.tuwien.ifs.somtoolbox.data.InputData;
import at.tuwien.ifs.somtoolbox.layers.Layer;
import at.tuwien.ifs.somtoolbox.layers.LayerAccessException;
import at.tuwien.ifs.somtoolbox.layers.Unit;
import at.tuwien.ifs.somtoolbox.layers.metrics.DistanceMetric;
import at.tuwien.ifs.somtoolbox.layers.metrics.MetricException;

/**
 * Implementation of SOM Spearman Coeffizient. (Bezdek, 1995)
 * 
 * @author Christoph Hohenwarter
 * @version $Id: SpearmanCoefficient.java 3888 2010-11-02 17:42:53Z frank $
 */
public class SpearmanCoefficient extends AbstractQualityMeasure {

    private double spearman = 0.0;

    public SpearmanCoefficient(Layer layer, InputData data) {
        super(layer, data);

        mapQualityNames = new String[] { "spearmanCoefficient" };
        mapQualityDescriptions = new String[] { "Spearman-Coefficient" };

        int xs = layer.getXSize();
        int ys = layer.getYSize();

        ArrayList<Unit> neurons = new ArrayList<Unit>();
        ArrayList<Double> Da = new ArrayList<Double>();
        ArrayList<Double> Dv = new ArrayList<Double>();

        DistanceMetric metric = layer.getMetric();

        // Construction of an array A of all neurons
        for (int xi = 0; xi < xs; xi++) {
            for (int yi = 0; yi < ys; yi++) {
                try {
                    neurons.add(layer.getUnit(xi, yi));
                } catch (LayerAccessException e) {
                    System.out.println(e.getMessage());
                }
            }
        }

        // Construction of AxA out of the array A of the neurons
        // (n1,n2) element of AxA with n1!=n2
        for (int n1 = 0; n1 < neurons.size(); n1++) {
            for (int n2 = 0; n2 < neurons.size(); n2++) {

                if (n1 != n2) {
                    Unit neuro1 = neurons.get(n1);
                    Unit neuro2 = neurons.get(n2);

                    Double da = layer.getMapDistance(neuro1, neuro2);
                    Da.add(da);

                    try {
                        Double dv = metric.distance(neuro1.getWeightVector(), neuro2.getWeightVector());
                        Dv.add(dv);
                    } catch (MetricException e) {
                        System.out.println(e.getMessage());
                    }
                }

            }
        }

        Spearman sp = new Spearman(Dv, Da);
        spearman = sp.getR();

    }

    @Override
    public double getMapQuality(String name) throws QualityMeasureNotFoundException {
        return spearman;
    }

    @Override
    public double[][] getUnitQualities(String name) throws QualityMeasureNotFoundException {
        throw new QualityMeasureNotFoundException("Quality measure with name " + name + " not found.");
    }

}

class Spearman {

    private double coeff = 0.0;

    // Dv = Values of the inputspace, Da = Values of the outputspace
    public Spearman(ArrayList<Double> Dv, ArrayList<Double> Da) {

        Da.trimToSize();
        Dv.trimToSize();

        double rq = 0.0;
        double sq = 0.0;
        double rsk = 0.0;
        double rk = 0.0;
        double sk = 0.0;
        int k = 0;

        ArrayList<Double> Dv_rank = ranking(Dv);
        ArrayList<Double> Da_rank = ranking(Da);

        k = Da_rank.size();

        for (int i = 0; i < k; i++) {
            rq = rq + Da_rank.get(i);
            sq = sq + Da_rank.get(i);
        }

        // Mean values of the ranks
        rq = rq / k;
        sq = sq / k;

        for (int i = 0; i < k; i++) {
            rsk = rsk + (Da_rank.get(i) - rq) * (Dv_rank.get(i) - sq);

            rk = rk + Math.pow((Da_rank.get(i) - rq), 2);
            sk = sk + Math.pow((Dv_rank.get(i) - sq), 2);
        }

        // Roots
        rk = Math.sqrt(rk);
        sk = Math.sqrt(sk);

        // Endresult
        coeff = rsk / (rk * sk);

    }

    /**
     * Method for getting a ranked order list of the inputvector
     * 
     * @return ArrayList of the ranking of the inputvector
     */
    @SuppressWarnings({ "rawtypes", "unchecked" })
    private ArrayList<Double> ranking(ArrayList<Double> vec) {
        vec.trimToSize();

        ArrayList<Double> Da_rank_tmp = new ArrayList<Double>();
        ArrayList<Double> Da_value = new ArrayList<Double>();
        ArrayList<Double> Da_rank = new ArrayList<Double>();
        ArrayList<Double> Da_c = (ArrayList<Double>) vec.clone();

        TreeMap tm = new TreeMap();

        // Sorting the inputvector
        Collections.sort(vec);

        int i2 = 0;
        double rank_tmp = 0.0;
        double rank_count = 0.0;

        for (int i = 0; i < vec.size();) {

            i2 = i + 1;

            if (i2 < vec.size() && vec.get(i2).compareTo(vec.get(i)) == 0) {
                // Two equal values next to each other

                rank_count = i + i2 + 2;
                i2++;

                if (i2 < vec.size()) {
                    while (i2 < vec.size() && vec.get(i2).compareTo(vec.get(i)) == 0) {

                        rank_count += i2 + 1; // Shifting ot the rank to 1 to
                        // n

                        i2++;
                    }
                }

                if (i2 > i + 2) {
                    rank_tmp = rank_count / (i2 - i + 1);

                    // There are more equal values in the vector

                    Da_value.add(vec.get(i));
                    Da_rank_tmp.add(rank_tmp);
                    i = i2;

                } else {
                    // Exactly two equal values
                    rank_tmp = rank_count / 2;
                    Da_value.add(vec.get(i));
                    Da_rank_tmp.add(rank_tmp);
                    i = i + 2;
                }

            }

            // No equal => rank == index
            else {
                Da_value.add(vec.get(i));
                Da_rank_tmp.add((double) (i + 1));
                i++;
            }
        }

        // reduce memoryusage
        Da_rank_tmp.trimToSize();
        Da_value.trimToSize();

        // Inserting of the data into a red-black-tree (TreeMap)
        // because of performance reasons => searchtime log(n)
        for (int i = 0; i < Da_value.size(); i++) {
            tm.put(Da_value.get(i), Da_rank_tmp.get(i));
        }

        // mapping of the ranking to the original vector
        for (int i = 0; i < Da_c.size(); i++) {
            Da_rank.add((Double) tm.get(Da_c.get(i)));
        }

        // reduce memoryusage
        Da_rank.trimToSize();

        // return rank vector
        return Da_rank;

    }

    // Getter for the spearman coefficient
    public double getR() {
        return coeff;
    }

}
