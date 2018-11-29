/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package etomica.conjugategradient;

import etomica.util.FunctionMultiDimensional;
import etomica.util.FunctionMultiDimensionalDifferentiable;
import etomica.util.numerical.FiniteDifferenceDerivative;


public class NonLinearConjugateGradients {

	/*
	 *   Nonlinear Conjugate Gradients with Newton-Raphson and Fletcher-Reeves
	 *  "An Introduction to the Conjugate Gradient Method w/o the Agonizing Pain"
	 *                      Jonathan Richard Shewchuk
	 *                           August 4, 1994
	 *                           
	 *  @author Tai Tan
	 */
	
	protected int imax;
	protected int jmax;
	protected double epsilonCG;
	protected double epsilonNR;
	
	public NonLinearConjugateGradients(){
		
		imax = 100;
		jmax = 100;
		epsilonCG = 0.01;
		epsilonNR = 0.01;
	}
	
	public void nonLinearCG(FunctionMultiDimensionalDifferentiable functionDifferentiable, double[] u){
		
		/*
		 *  imax is a maximum number of CG iterations
		 *  jmax is a maximum number of Newton-Raphson iterations
		 *  
		 */
		
		int i=0;
		int k=0;
		int n;
		int coordinateDim = u.length;
		double deltaNew = 0;
		
		int[] dAssign = new int[coordinateDim];
		double[] uDerivative = new double[coordinateDim];
		
		//finiteDifferenceDerivative.setH(0.01);
		//finiteDifferenceDerivative.setHOptimizer(true);
		/*
		 * To obtain first derivative of a function
		 */
		for (int diff1Counter=0; diff1Counter< coordinateDim; diff1Counter++){
			/*
			 *  To assign d to differentiate over all the dimensions
			 */
			for (int dim=0; dim< coordinateDim; dim++){
				if (diff1Counter==dim){
					dAssign[dim] = 1;
				} else{
					dAssign[dim] = 0;
				}
			}
			uDerivative[diff1Counter] = - functionDifferentiable.df(dAssign, u);
		}
		
		
		double[] r = new double[coordinateDim]; 
		double[] d = new double[coordinateDim];
		double[] d_DoublePrime = new double[coordinateDim];
		
		for (n=0; n<coordinateDim; n++){	
			
			r[n] = uDerivative[n];
			d[n] = r[n];
			
			deltaNew += r[n]*r[n];
			
			System.out.println("r["+n + "] is: " + r[n]);
			System.out.println("d["+n + "] is: " + d[n]);
		}
		
		double delta0 = deltaNew;
		double epsilonCG2_delta0 = epsilonCG*epsilonCG*delta0;
		
		System.out.println("DeltaNew: "+ deltaNew);
		System.out.println("epsilonCG: "+ epsilonCG);
		System.out.println("epsilon2_delta0: "+ epsilonCG2_delta0);
		
		while(i<imax && deltaNew > epsilonCG2_delta0){
			
			System.out.println("\nIn the BIG WHILE loop NOW!!!");
			int j=0;
			double deltad = 0;
			double alpha_num = 0;
			double alpha_denom = 0;
			
			for(n=0; n<coordinateDim; n++){	
				deltad += d[n]*d[n];
			}
			
			double alpha = 0.5; //Let's say alpha =0.5 so as to get into the second WHILE loop
			double alpha2_deltad = alpha*alpha*deltad;
			double epsilonNR2 = epsilonNR*epsilonNR;
			
			while (j<jmax && alpha2_deltad > epsilonNR2){
				System.out.println("In the second smaller for LOOP");
				
				System.out.println("the new u[0] is: "+u[0]);
				System.out.println("the new u[1] is: "+u[1]);
				
				/*
				 * To obtain second derivative of a function
				 */
				double[][] u2Derivative = new double[coordinateDim][coordinateDim];
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////	
				/*
				 * Hessian double derivative with all elements
				 */ 
				/*
				for (int diff2Counter =0; diff2Counter< coordinateDim; diff2Counter++){
					for (int diff1Counter =0; diff1Counter< coordinateDim; diff1Counter++){
						
						/*
						 *  To assign d to differentiate twice over all the dimensions
						 */
					/*	for (int dim =0; dim< coordinateDim; dim++){
							if (diff1Counter==dim){
								dAssign[dim] = 1;
							} else{
								dAssign[dim] = 0;
							}

						}
						
						++ dAssign[diff2Counter];  // determine the next element of the derivative
						
						u2Derivative[diff2Counter][diff1Counter] = functionDifferentiable.df(dAssign, u);
						System.out.println("Second Derivative d["+diff2Counter+"]d["+diff1Counter+"] is: "
								+u2Derivative[diff2Counter][diff1Counter]);
					}
				}
				
				/*
				 * Hessian double derivative with only the diagonal elements
				 */
				for (int diff2Counter =0; diff2Counter< coordinateDim; diff2Counter++){
					for (int diff1Counter =0; diff1Counter< coordinateDim; diff1Counter++){
						
						/*
						 *  To assign d to differentiate twice over all the dimensions
						 */
						for (int dim =0; dim< coordinateDim; dim++){
							if (diff1Counter==dim){
								dAssign[dim] = 2;
							} else{
								dAssign[dim] = 0;
							}

						}
						
						if (diff1Counter == diff2Counter){
							u2Derivative[diff2Counter][diff1Counter] = functionDifferentiable.df(dAssign, u);
						} else {
							u2Derivative[diff2Counter][diff1Counter] = 0;
						}
						System.out.println("Second Derivative d["+diff2Counter+"]d["+diff1Counter+"] is: "
								+u2Derivative[diff2Counter][diff1Counter]);
					}
				}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				/*
				 * Computing Matrix-Multiplication of 
				 * Matrix (1 X CoordinateDim) and Matrix (CoordinateDim X CoordinateDim)
				 */
				for(n=0; n<coordinateDim; n++){
					for(int m=0; m<coordinateDim; m++){
						d_DoublePrime[n] += d[m]*u2Derivative[m][n];
					}
				}
				
				for(n=0; n<coordinateDim; n++){
					alpha_num += -uDerivative[n]*d[n];
					alpha_denom += d_DoublePrime[n]*d[n];
				}
				
				alpha = - alpha_num /alpha_denom;
				System.out.println("Alpha is: "+ alpha);
				
				for(n=0; n<coordinateDim; n++){
					u[n] = u[n] + alpha*d[n];
				}
				
				alpha2_deltad = alpha*alpha*deltad;
				System.out.println("alpha2_deltas is: "+ alpha2_deltad);
				++j;
				
				//System.exit(1);
				
			}
			
			System.out.println("The u[0] after Newton-Raphson is: "+ u[0]);
			System.out.println("The u[1] after Newton-Raphson is: "+ u[1]);
			//System.exit(1);
			
			for (int diff1Counter=0; diff1Counter< coordinateDim; diff1Counter++){
				/*
				 *  To assign d to differentiate over all the dimensions
				 */
				for (int dim=0; dim< coordinateDim; dim++){
					if (diff1Counter==dim){
						dAssign[dim] = 1;
					} else{
						dAssign[dim] = 0;
					}
				}
				uDerivative[diff1Counter] = - functionDifferentiable.df(dAssign, u);
			}
			
			double deltaOld = deltaNew;
			deltaNew = 0;
			
			for(n=0; n<coordinateDim; n++){
				r[n] = uDerivative[n];
				deltaNew += r[n]*r[n];
			}
				
			double beta = deltaNew/ deltaOld;
				
			for(n=0; n<coordinateDim; n++){
				d[n] = r[n] + beta*d[n];
			}
				
			++k;
			
			
			double rTd = 0;
			
			for(n=0; n<coordinateDim; n++){
				rTd += r[n]*d[n];
			}

			if(k == jmax-1 || rTd <= 0){ 
				/*
				 * it is restarted once every (num) iterations,
				 * to improve convergence for small num
				 * num always equals to jMax - 1
				 */
				for(n=0; n<coordinateDim; n++){
					d[n] = r[n];
				}
				k=0;
				//System.exit(1);
			}
			
			++i;
		}
		//System.out.println("u[0] from CG is: "+ u[0]);
		//System.out.println("u[1] from CG is: "+ u[1]);
	}

	public double getEpsilonCG() {
		return epsilonCG;
	}

	public void setEpsilonCG(double epsilonCG) {
		this.epsilonCG = epsilonCG;
	}

	public double getEpsilonNR() {
		return epsilonNR;
	}

	public void setEpsilonNR(double epsilonNR) {
		this.epsilonNR = epsilonNR;
	}

	public int getImax() {
		return imax;
	}

	public void setImax(int imax) {
		this.imax = imax;
	}

	public int getJmax() {
		return jmax;
	}

	public void setJmax(int jmax) {
		this.jmax = jmax;
	}

	
}
