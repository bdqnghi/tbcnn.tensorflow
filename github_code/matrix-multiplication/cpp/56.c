//
// Created by click on 3/27/2016.
//
#pragma once
#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include "Ray.h"
#include "Color.h"
#include "Matrix.h"
#include <vector>
using namespace std;


class Shape {
protected:
    Matrix matrix;
    float ambience;
    Matrix transformationMatrix;
    Matrix inversetransformationMatrix;
    float diffusedCoefficient;
    float specularCoefficient;


public:


    virtual const Color getColor() = 0;
    Shape(){};
    virtual const double getIntersectionDistance(Ray r) = 0;
    Shape(float a, float d, float s){
        ambience = a;
        diffusedCoefficient = d;
        specularCoefficient = s;
    }

    virtual const Vector3D getNormalFor(Vector3D intersectionPoint) = 0;
    float getAmbience(){
        return ambience;
    }
    float getDiffusedcoefficient(){
        return diffusedCoefficient;
    }
    float getSpecularccoefficient(){
        return specularCoefficient;
    }
    //Transformation and inverse transformation matrix
    Matrix translateXYZ(double tx, double ty, double tz){
        transformationMatrix = matrix.matrixMultiplication(transformationMatrix, matrix.tranlate2D(tx, ty, tz));
        inversetransformationMatrix = matrix.matrixMultiplication(inversetransformationMatrix, matrix.translateInverse(tx, ty, tz));

    }
    Matrix rotateXaxis(double cth){
        transformationMatrix = matrix.matrixMultiplication(transformationMatrix, matrix.rotateXaxis(cth));
        inversetransformationMatrix = matrix.matrixMultiplication(inversetransformationMatrix, matrix.rotateXaxisInverse(cth));

    }
    Matrix rotateYaxis(double cth){
        transformationMatrix = matrix.matrixMultiplication(transformationMatrix, matrix.rotateYaxis(cth));
        inversetransformationMatrix = matrix.matrixMultiplication(inversetransformationMatrix, matrix.rotateYaxisInverse(cth));

    }
    Matrix rotateZaxis(double cth){
        transformationMatrix = matrix.matrixMultiplication(transformationMatrix, matrix.rotateZaxis(cth));
        inversetransformationMatrix = matrix.matrixMultiplication(inversetransformationMatrix, matrix.rotateZaxisInverse(cth));

    }
    Matrix scale2D(double a, double b, double c){
        transformationMatrix = matrix.matrixMultiplication(transformationMatrix, matrix.scaleInverse(a, b, c));

    }


    Matrix getTransformationMatrix() const {
        return transformationMatrix;
    }

    Matrix getInversetransformationMatrix() const {
        return inversetransformationMatrix;
    }
};





#endif //RAYTRACER_SHAPE_H
