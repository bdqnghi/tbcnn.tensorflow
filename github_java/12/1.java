import processing.core.*; 
import processing.xml.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class firstAssig extends PApplet {

class Cube {
  private Vertex[] vertArray = new Vertex[]{
    // create 8 vertexes for cube
    new Vertex(50.0f, 50.0f, -100.0f, 1.0f),
    new Vertex(150.0f, 50.0f, -100.0f, 1.0f),
    new Vertex(150.0f, 150.0f, -100.0f, 1.0f),
    new Vertex(50.0f, 150.0f, -100.0f, 1.0f),
    new Vertex(50.0f, 50.0f, 0.0f, 1.0f),
    new Vertex(150.0f, 50.0f, 0.0f, 1.0f),
    new Vertex(150.0f, 150.0f, 0.0f, 1.0f),
    new Vertex(50.0f, 150.0f, 0.0f, 1.0f)
  };
  private Line[] lineArray = new Line[]{
    // 12 lines out of 8 vertexes
    // clockwise arrangement from top left, first front then back
    new Line(vertArray[0], vertArray[1]),
    new Line(vertArray[1], vertArray[2]),
    new Line(vertArray[2], vertArray[3]),
    new Line(vertArray[3], vertArray[0]),
    new Line(vertArray[0], vertArray[4]),
    new Line(vertArray[1], vertArray[5]),
    new Line(vertArray[2], vertArray[6]),
    new Line(vertArray[3], vertArray[7]),
    new Line(vertArray[4], vertArray[5]),
    new Line(vertArray[5], vertArray[6]),
    new Line(vertArray[6], vertArray[7]),
    new Line(vertArray[7], vertArray[4])
  };
  private float[][] transfArray;
  private Vertex[] newVertArray;
  private Line[] newLineArray;
  
  Cube() {
   this.setVertArray(this.vertArray);
  	this.setLineArray(this.lineArray);
  }
  
  public void setVertArray(Vertex[] vertArray) {
  	this.vertArray = vertArray;
  }
  
  public void setLineArray(Line[] lineArray) {
  	this.lineArray = lineArray;
  }
  
  public void setTransfArray(float[][] transfArray) {
    this.transfArray = transfArray;   
  }
  
  public void createLineArray(Vertex[] newVertArray) {
    newLineArray = new Line[12];
    newLineArray[0] = new Line(newVertArray[0], newVertArray[1]);
    newLineArray[1] = new Line(newVertArray[1], newVertArray[2]);
    newLineArray[2] = new Line(newVertArray[2], newVertArray[3]);
    newLineArray[3] = new Line(newVertArray[3], newVertArray[0]);
    newLineArray[4] = new Line(newVertArray[0], newVertArray[4]);
    newLineArray[5] = new Line(newVertArray[1], newVertArray[5]);
    newLineArray[6] = new Line(newVertArray[2], newVertArray[6]);
    newLineArray[7] = new Line(newVertArray[3], newVertArray[7]);
    newLineArray[8] = new Line(newVertArray[4], newVertArray[5]);
    newLineArray[9] = new Line(newVertArray[5], newVertArray[6]);
    newLineArray[10] = new Line(newVertArray[6], newVertArray[7]);
    newLineArray[11] = new Line(newVertArray[7], newVertArray[4]);
    setLineArray(newLineArray);
  }
  
  public void display() {
    for (int i=0; i<lineArray.length; i++) {
      lineArray[i].display2D();
    }
  }
  
  public void display(Vertex[] newVertArray) {
    for (int i=0; i<lineArray.length; i++) {
      lineArray[i].display2D();
    }
  }
  
  public void transform() {
    // new vertex-array for transformed vertexes
    newVertArray = new Vertex[vertArray.length];
    // count rows of transformation matrix
    int transfColumns = this.transfArray[0].length;
    // check if matrix-multiplication is possible
    if (transfColumns != 4) {
      println("transformation Array " + transfColumns + " did not match homogenous coordinate.");
    }
    for (int h=0; h<vertArray.length; h++) {
      // iterate through vertArray
      // return new vertArray
      float[] newCoordinateArray = new float[4];
      for (int i=0; i<transfArray.length; i++) {
        // iterate through each row of transfArray
        // return new Vertex
        float newCoordinate = 0.0f;
        // iterate through each value of transfArray-Row 
        // and multiply with Vertex, add to newCoordinate
        newCoordinate += (transfArray[i][0] * vertArray[h].x);
        newCoordinate += (transfArray[i][1] * vertArray[h].y);
        newCoordinate += (transfArray[i][2] * vertArray[h].z);
        newCoordinate += (transfArray[i][3] * vertArray[h].t);
        newCoordinateArray[i] = newCoordinate;
      }
      // asign values of newCoordinateArray to x, y, z or t
      Vertex newVertex = new Vertex(
        newCoordinateArray[0], // assign to x
        newCoordinateArray[1], // assign to y
        newCoordinateArray[2], // assign to z
        newCoordinateArray[3]  // assign to t
      );
      newVertArray[h] = newVertex;
    }
    createLineArray(newVertArray);
  }
}

class Line {
  Vertex v1, v2;
  Line(Vertex v1, Vertex v2) {
    this.v1 = v1;
    this.v2 = v2;
  }
  float projX1, projY1, projX2, projY2;
  
  // Translation of the automated 3DLine to a 2DLine
  public void display2D() {
    projX1 = this.v1.x/(1+(this.v1.z/200));
    projY1 = this.v1.y/(1+(this.v1.z/200));
    projX2 = this.v2.x/(1+(this.v2.z/200));
    projY2 = this.v2.y/(1+(this.v2.z/200));
    //print(projX1, projY1, projX2, projY2);
    line(projX1, projY1, projX2, projY2);
  }

  public void display() {
    print(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
    line(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
  }
}

private static int rotations = 8; 

class Object {
  private Vertex[] pointArray = new Vertex[] {
    new Vertex(0.0f, 0.0f, 0.0f, 1.0f), 
    new Vertex(50.0f, 50.0f, 0.0f, 1.0f), 
    new Vertex(70.0f, 100.0f, 0.0f, 1.0f), 
    new Vertex(80.0f, 150.0f, 0.0f, 1.0f), 
    new Vertex(70.0f, 200.0f, 0.0f, 1.0f), 
    new Vertex(50.0f, 250.0f, 0.0f, 1.0f), 
    new Vertex(20.0f, 300.0f, 0.0f, 1.0f),
  };
  private float[][] transfArray = {   
    {1.0f, 0.0f, 0.0f, 0.0f}, 
    {0.0f, 1.0f, 0.0f, 0.0f}, 
    {0.0f, 0.0f, 1.0f, 0.0f}, 
    {0.0f, 0.0f, 0.0f, 1.0f}
  };
  private Line[] lineArray;
  private Vertex[][] rotationArray;

  Object() {
    this.setRotationArray(this.pointArray);
    this.createLineArray(this.rotationArray);
    this.setLineArray(this.lineArray);
  }

  public void setPointArray(Vertex[] pointArray){
    this.pointArray = pointArray;
  }
  
  public Vertex[] getPointArray(){
    return this.pointArray;
  }

  public void setTransfArray(float[][] transfArray){
    this.transfArray = transfArray;
  }
  
  public float[][] getTransfArray(){
    return this.transfArray;
  }
  
  public void setRotationArray(Vertex[] pointArray) {
    rotationArray = new Vertex[rotations][pointArray.length];
    rotationArray[0] = pointArray;
    for (int j=1; j<rotations; j++) {
      /*
       *  take user-defined Vertexes and rotate them 7 times to form Object
       */
      float[][] rotationTransformationArray = {   
        {cos(j*QUARTER_PI), 0.0f, sin(j*QUARTER_PI), 0.0f}, 
        {0.0f, 1.0f, 0.0f, 0.0f}, 
        {-sin(j*QUARTER_PI), 0.0f, cos(j*QUARTER_PI), 0.0f}, 
        {0.0f, 0.0f, 0.0f, 1.0f}
      };
      Vertex[] newRotationArray = new Vertex[pointArray.length];
      /*
       *  iterate through pointArray
       */
      for (int h=0; h<pointArray.length; h++) {
        float[] newCoordinateArray = new float[4];
        /*
         *  iterate through each row of rotationTransformationArray
         *  create newCoordinateArray
         */
        for (int i=0; i<rotationTransformationArray.length; i++) {
            float newCoordinate = 0.0f;
            /* 
             *  multiply each value of rotTransformationArray-Row with
             *  corresponding Vertex-value and add to newCoordinate
             */
            newCoordinate += (rotationTransformationArray[i][0] * pointArray[h].x);
            newCoordinate += (rotationTransformationArray[i][1] * pointArray[h].y);
            newCoordinate += (rotationTransformationArray[i][2] * pointArray[h].z);
            newCoordinate += (rotationTransformationArray[i][3] * pointArray[h].t);
            //print(newCoordinate);
            newCoordinateArray[i] = newCoordinate;
            //printArray(newCoordinateArray);
        }
        // asign values of newCoordinateArray to x, y, z or t
        Vertex newVertex = new Vertex(
          newCoordinateArray[0], // assign to x
          newCoordinateArray[1], // assign to y
          newCoordinateArray[2], // assign to z
          newCoordinateArray[3]  // assign to t
        );
        newRotationArray[h] = newVertex;
      }
      // create multidimensional array full with rotated Vertexes
      rotationArray[j] = newRotationArray;
    }
  }

  public Vertex[][] getRotationArray(){
    return this.rotationArray;
  }

  public void setLineArray(Line[] lineArray) {
    this.lineArray = lineArray;
  }
  
  public Line[] getLineArray(){
    return this.lineArray;
  }

  public void createLineArray(Vertex[][] rotationArray) {
    int lastEl = rotationArray[0].length-1;
    Line[] newLineArray;
    newLineArray = new Line[0];
    for (int j=0; j<rotationArray.length; j++) {
      if (j!=7) {
        for (int i=0; i<rotationArray[0].length-1; i++) {
          Line line1 = new Line(rotationArray[j][i], rotationArray[j+1][i]);
          newLineArray = (Line[]) append(newLineArray, line1);
          Line line2 = new Line(rotationArray[j][i], rotationArray[j+1][i+1]);
          newLineArray = (Line[]) append(newLineArray, line2); 
          Line line3 = new Line(rotationArray[j][i], rotationArray[j][i+1]);
          newLineArray = (Line[]) append(newLineArray, line3);
        }
        Line lowLine = new Line(rotationArray[j][lastEl], rotationArray[j+1][lastEl]);
        newLineArray = (Line[]) append(newLineArray, lowLine);
      } 
      else {
        for (int i=0; i<rotationArray[0].length-1; i++) {
          Line line1 = new Line(rotationArray[j][i], rotationArray[0][i]);
          newLineArray = (Line[]) append(newLineArray, line1);
          Line line2 = new Line(rotationArray[j][i], rotationArray[0][i+1]);
          newLineArray = (Line[]) append(newLineArray, line2); 
          Line line3 = new Line(rotationArray[j][i], rotationArray[j][i+1]);
          newLineArray = (Line[]) append(newLineArray, line3);
        }
        Line lowLine = new Line(rotationArray[j][lastEl], rotationArray[0][lastEl]);
        newLineArray = (Line[]) append(newLineArray, lowLine);
      }
    }
    //printArray(newLineArray);
    setLineArray(newLineArray);
  }

  public void display() {
    for (int i=0; i<lineArray.length; i++) {
      lineArray[i].display2D();
    }
  }
  
  public void transform(float[][] transfArray) {
    setTransfArray(transfArray);
    // new vertex-array for transformed vertexes
    Vertex[] newVertArray = new Vertex[pointArray.length];
    // count rows of transformation matrix
    int transfColumns = this.transfArray[0].length;
    // check if matrix-multiplication is possible
    if (transfColumns != 4) {
      println("transformation Array " + transfColumns + " did not match homogenous coordinate.");
    }
    for (int h=0; h<vertArray.length; h++) {
      // iterate through vertArray
      // return new vertArray
      float[] newCoordinateArray = new float[4];
      for (int i=0; i<transfArray.length; i++) {
        // iterate through each row of transfArray
        // return new Vertex
        float newCoordinate = 0.0f;
        // iterate through each value of transfArray-Row 
        // and multiply with Vertex, add to newCoordinate
        newCoordinate += (transfArray[i][0] * vertArray[h].x);
        newCoordinate += (transfArray[i][1] * vertArray[h].y);
        newCoordinate += (transfArray[i][2] * vertArray[h].z);
        newCoordinate += (transfArray[i][3] * vertArray[h].t);
        newCoordinateArray[i] = newCoordinate;
      }
      // asign values of newCoordinateArray to x, y, z or t
      Vertex newVertex = new Vertex(
      newCoordinateArray[0], // assign to x
      newCoordinateArray[1], // assign to y
      newCoordinateArray[2], // assign to z
      newCoordinateArray[3]  // assign to t
      );
      newVertArray[h] = newVertex;
    }
    //setPointArray(newVertArray);
    setRotationArray(newVertArray);
    createLineArray(getRotationArray());
    display();
  }

}


class Vertex {
  float x, y, z, t; // t is for transformation
  Vertex(float x, float y, float z, float t) {
    this.x = x;
    this.y = y;
    this.z = z;
    this.t = t;
  }  
  public void display() {
    vertex(x, y, z);
  }
}

// instanciate array and object
Vertex[] vertArray;
float[][] transfArray = {   
    {1.0f, 0.0f, 0.0f, 0.0f}, 
    {0.0f, 1.0f, 0.0f, 0.0f}, 
    {0.0f, 0.0f, 1.0f, 0.0f}, 
    {0.0f, 0.0f, 0.0f, 1.0f}
};
//Cube cube;
Object object;
int factor;

public void setup() {
  background(255);
  size(800, 600, P3D);
  translate(200, 150);
  stroke(0xff000000);
  strokeWeight(1);
  frameRate(1);
  // create Cube-Object
  // cube = new Cube();
  // create custom Object
  object = new Object();
  object.display();
}

public void draw() {
  // CUBE 
  /* translation along y-axis
  //transfArray[0][3] += 10.0;
  */
  /* scaling
  transfArray[0][0] += 1.0;
  transfArray[1][1] += 1.0;
  transfArray[2][2] += 1.0;
  */
  /* rotation about the z-axis
  factor += 1;
  float mySin = sin(factor*QUARTER_PI);
  float myCos = cos(factor*QUARTER_PI);
  transfArray[1][1] = myCos;
  transfArray[1][2] = -mySin;
  transfArray[2][1] = mySin;
  transfArray[2][2] = myCos;
  //print(transfArray[1][1]);
  //print(transfArray[1][2]);
  //print(transfArray[2][1]);
  //print(transfArray[2][2]);
  cube.display();
  cube.setTransfArray(transfArray);
  cube.transform();
  */
  
  // OBJECT
  // translation along y-axis
  transfArray[0][3] += 10.0f;
  object.transform(transfArray);
  object.display();
}

    static public void main(String args[]) {
        PApplet.main(new String[] { "--bgcolor=#ECE9D8", "firstAssig" });
    }
}
