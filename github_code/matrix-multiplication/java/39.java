package tobi.flappy.math;

import java.nio.FloatBuffer;
import tobi.flappy.utils.*;


public class Matrix4f {

	public static final int SIZE = 4 * 4;
	public float[] elements = new float[SIZE];
	
	public Matrix4f(){
		
	}
	
	public static Matrix4f identity(){
		Matrix4f result = new Matrix4f();
		for(int i = 0; i < SIZE; i++){
			result.elements[i] = 0.0f;
		}
		
		/*		| 	1	0	0	0	|
		 * 		|	0	1	0	0	|
		 * 		|	0	0	1	0	|
		 * 		| 	0	0	0	1	|
		 * 
		 */
		
		// first number: row of matrix, second number: column of matrix, 4: constant width of matrix
		result.elements[0 + 0 * 4] = 1.0f;	// -> 0
		result.elements[1 + 1 * 4] = 1.0f;	// -> 5
		result.elements[2 + 2 * 4] = 1.0f;	// -> 10
		result.elements[3 + 3 * 4] = 1.0f;	// -> 15
		
		return result;
	}
	
	public static Matrix4f orthographic(float left, float right, float bottom, float top, float near, float far){
		Matrix4f result = identity();
		
		/*		| 	2/(right-left)	0						0					(left + right) / (left -right)	|
		 * 		|	0				2 / (top - bottom)		0					(bottom + top) / (bottom - top)	|
		 * 		|	0				0						2 / (near - far)	(near + far) / (far - near)		|
		 * 		| 	0				0						0					1								|
		 * 
		 */
		
		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (right - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);
		
		result.elements[0 + 3 * 4] = (right + left) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (near + far) / (far - near);
		// elements[3 + 3 * 4] = 1 muss nicht angegeben werden, weil identity()
		
		return result;
		
	}
	
	public static Matrix4f translate(Vector3f vector){
		Matrix4f result = identity();
		result.elements[0 + 3 * 4] = vector.x;
		result.elements[1 + 3 * 4] = vector.y;
		result.elements[2 + 3 * 4] = vector.z;
		
		return result;
	}
	
	public static Matrix4f rotate(float angle){
		Matrix4f result = identity();
		float r = (float) Math.toRadians(angle);
		float cos = (float) Math.cos(r);
		float sin = (float) Math.sin(r);
		
		result.elements[0 + 0 *4] = cos;
		result.elements[1 + 0 *4] = sin;
		result.elements[0 + 1 *4] = -sin;
		result.elements[1 + 1 *4] = cos;
		
		return result;
	}
	
	public Matrix4f multiply(Matrix4f matrix){
		Matrix4f result = new Matrix4f();
		// "a's" rows
		for(int i = 0; i < 4; i++){
			// "b's" columns
			for(int j = 0; j < 4; i++){
				float sum = 0.0f;
				// matrix-multiplication
				for(int e = 0; e < 4; e++){
					sum += this.elements[j + e * 4] * matrix.elements[e + i * 4];
				}
				result.elements[i + j * 4] = sum;
			}
		}
		return result;
	}
	
	public FloatBuffer toFloatBuffer(){
		return BufferUtils.createFloatBuffer(elements);
	}
}
