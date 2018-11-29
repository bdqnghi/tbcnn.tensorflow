package com.example.damian.kinematicscalculationvs2.openGL;

import android.content.Context;

import com.example.damian.kinematicscalculationvs2.calculations.SingeltonMatrix;
import com.example.damian.kinematicscalculationvs2.openGL.objects.Cube;
import com.example.damian.kinematicscalculationvs2.openGL.objects.CuboidA;
import com.example.damian.kinematicscalculationvs2.openGL.objects.CuboidD;
import com.example.damian.kinematicscalculationvs2.openGL.objects.ObjectParent;
import com.example.damian.kinematicscalculationvs2.openGL.objects.Xaxis;
import com.example.damian.kinematicscalculationvs2.openGL.objects.Yaxis;

import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class RenderManipulator extends AbstractRenderer {

//        Cube cube = new Cube(0, 0, 0);
//    CuboidD cuboidD = new CuboidD((float) 2);
//    CuboidA cuboidA = new CuboidA(2);
//    Cube cube1 = new Cube(8, 8, 8);

    private float[][] tableParameter;
    private float[] effectorCoord;
    private float[] effectorEndCoord;

    private ArrayList<ObjectParent> object = new ArrayList<>();

    public RenderManipulator(Context context, float[][] tableParameter, float[] effectorCoord, float[] effectorEndCoord) {
        this.tableParameter = tableParameter;
        this.effectorCoord = effectorCoord;
        this.effectorEndCoord = effectorEndCoord;
        render();
    }

    private void render() {




        for (int i = 0; i < tableParameter.length; i++) {

            float[][] MatrixUnit = {
                    {1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
            };
//-------------------------------------------------------------------
            // tworzenie członu
            for (int j = 0; j < i; j++) {

                float[][] RotZ = SingeltonMatrix.DHRotZ(tableParameter[j][3]);
                float[][] TransZ = SingeltonMatrix.DHTransZ(tableParameter[j][2]);
                float[][] TransX = SingeltonMatrix.DHTransX(tableParameter[j][0]);
                float[][] RotX = SingeltonMatrix.DHRotX(tableParameter[j][1]);

                float[][] RotZxTransZ = SingeltonMatrix.Multiplication(RotZ, TransZ);
                float[][] xTransX = SingeltonMatrix.Multiplication(RotZxTransZ, TransX);
                float[][] xRotX = SingeltonMatrix.Multiplication(xTransX, RotX);

                MatrixUnit = SingeltonMatrix.Multiplication(MatrixUnit, xRotX);
            }

            object.add(new Cube(MatrixUnit[0][3], MatrixUnit[1][3], MatrixUnit[2][3]));
//-------------------------------------------------------------------
            // tworzenie długości D
            object.add(new CuboidD(tableParameter[i][2]));
            float[] verticlesD = object.get(object.size() - 1).getVerticles();

//            float[][] Ad = {
//                    {1, 0, 0, 0},
//                    {0, 1, 0, 0},
//                    {0, 0, 1, 0},
//                    {0, 0, 0, 1}
//            };
            float[][] Ad = {
                    {1,0,0},
                    {0,1,0},
                    {0,0,1}
            };

            if (i > 0) {

                for (int j = 0; j < i - 1; j++) {

                    float[][] RotZD = SingeltonMatrix.RotZ(tableParameter[j][3]);
                    float[][] RotXD = SingeltonMatrix.RotX(tableParameter[j][1]);

                    float[][] RotZxRotXD = SingeltonMatrix.Multiplication(RotZD, RotXD);

                    Ad = SingeltonMatrix.Multiplication(Ad, RotZxRotXD);
                }

                for (int h = 0; h < verticlesD.length; h = h + 3) {
                    float[] v = {
                            verticlesD[h + 0],
                            verticlesD[h + 1],
                            verticlesD[h + 2]
                    };
                    v = SingeltonMatrix.Multiplication(Ad, v);

                    verticlesD[h + 0] = v[0] + MatrixUnit[0][3];
                    verticlesD[h + 1] = v[1] + MatrixUnit[1][3];
                    verticlesD[h + 2] = v[2] + MatrixUnit[2][3];
                }

                object.get(object.size() - 1).setVerticles(verticlesD);
            }

//            for (int j = 0; j < i; j++) {
//
//                float[][] RotZ = SingeltonMatrix.DHRotZ(tableParameter[j][3]);
//                float[][] TransZ = SingeltonMatrix.DHTransZ(tableParameter[j][2]);
//                float[][] TransX = SingeltonMatrix.DHTransX(tableParameter[j][0]);
//                float[][] RotX = SingeltonMatrix.DHRotX(tableParameter[j][1]);
//
//                float[][] RotZxTransZ = SingeltonMatrix.Multiplication(RotZ, TransZ);
//                float[][] xTransX = SingeltonMatrix.Multiplication(RotZxTransZ, TransX);
//                float[][] xRotX = SingeltonMatrix.Multiplication(xTransX, RotX);
//
//                Ad = SingeltonMatrix.Multiplication(Ad, xRotX);
//            }
//
//            for (int h = 0; h < verticlesD.length; h = h + 3) {
//                float[] v = {
//                        verticlesD[h + 0],
//                        verticlesD[h + 1],
//                        verticlesD[h + 2],
//                        0
//                };
//                v = SingeltonMatrix.Multiplication(Ad, v);
//
//                verticlesD[h + 0] = v[0];
//                verticlesD[h + 1] = v[1];
//                verticlesD[h + 2] = v[2];
//            }
//            object.get(object.size() - 1).setVerticles(verticlesD);

//-------------------------------------------------------------------
            // tworzenie długości A
            object.add(new CuboidA(tableParameter[i][0]));
            float[] verticlesA = object.get(object.size() - 1).getVerticles();

            float[][] Aa = {
                    {1, 0, 0},
                    {0, 1, 0},
                    {0, 0, 1}
            };
            for (int j = 0; j < i; j++) {

                float[][] RotZA = SingeltonMatrix.RotZ(tableParameter[j][3]);
                float[][] RotXA = SingeltonMatrix.RotX(tableParameter[j][1]);

                float[][] RotZxRotXA = SingeltonMatrix.Multiplication(RotZA, RotXA);

                Aa = SingeltonMatrix.Multiplication(Aa, RotZxRotXA);
            }

            float [][] MatrixUnitxRotz = SingeltonMatrix.Multiplication(MatrixUnit,SingeltonMatrix.DHRotZ(tableParameter[i][3]));
            float [][] xTransZ = SingeltonMatrix.Multiplication(MatrixUnitxRotz, SingeltonMatrix.DHTransZ(tableParameter[i][2]));

            for (int h = 0; h < verticlesA.length; h = h + 3) {
                float[] v = {
                        verticlesA[h + 0],
                        verticlesA[h + 1],
                        verticlesA[h + 2]
                };
                v = SingeltonMatrix.Multiplication(Aa, v);

                verticlesA[h + 0] = v[0] + xTransZ[0][3];
                verticlesA[h + 1] = v[1] + xTransZ[1][3];
                verticlesA[h + 2] = v[2] + xTransZ[2][3];
            }

            object.get(object.size() - 1).setVerticles(verticlesA);
//-------------------------------------------------------------------
        }

        object.add(new Cube(effectorEndCoord[0], effectorEndCoord[1], effectorEndCoord[2]));
        object.add(new Xaxis(20));
        object.add(new Yaxis(20));

    }

    @Override
    protected void draw(GL10 gl) {

        for (int i = 0; i < object.size(); i++) {
            object.get(i).draw(gl);
        }

//        cube.draw(gl);
//        cuboidA.draw(gl);
//        cube1.draw(gl);
    }
}