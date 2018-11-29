package equation_solvers;

import DAO.RowState;
import DAO.State;
import Settings.Parameters;
import Settings.StandardMatrix;
import utils.Matrix;

/**
 * Created by Georg Mayur on 24.09.16.
 * Try to iterative filtrate input signals via Kalman's noise_addition
 */
public class KalmansFilterAdaptive {

	// constants for covariation matrix
	private final double gravity_const = Settings.Parameters.gravity_const.getValue();
	private final double earth_radius = Settings.Parameters.earth_radius.getValue();

	// contain the references between assessment and previous step state
	private double[][] covariation_matrix = null;

	// P as the covariation matrix of assessment errors
	private double[][] covariation_error =
		new double[][]{
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		};

	// states from previous step
	private double[][] previous_step_state = new double[][]{
		{0},
		{0},
		{0}
	};

	// noise
	private double[][] Q;

	// velocity noise
	private double R = 0.0;
	private double C = 1.0;

	// set R and Q
	public KalmansFilterAdaptive(double[][] Q) {
		this.Q = Q;
	}

	// Kalman's filter iteration
	public State next(RowState rowState) {

		if (covariation_matrix == null)
			covariation_matrix = new double[][]{
				{1, -gravity_const * Parameters.time_delta.getValue(), 0},
				{1 / earth_radius, 1, Parameters.time_delta.getValue()},
				{0, 0, 1}
			};

		// get the assessment via covariation matrix
		double[][] assessment_state = Matrix.matrix_multiplication(covariation_matrix, previous_step_state);

		// START: solve covariation-error matrix
		// Ф * Px * Ф
		double[][] first_addendum = Matrix.matrix_multiplication(
			Matrix.matrix_multiplication(covariation_matrix, covariation_error),
			Matrix.matrix_transpose(covariation_matrix)
		);

		// G * Q * G_T
		double[][] second_addendum = Matrix.matrix_multiplication(
			Matrix.matrix_multiplication(StandardMatrix.G.getMatrix(), Q),
			Matrix.matrix_transpose(StandardMatrix.G.getMatrix())
		);

		// P as the covariation matrix of assessment errors
		covariation_error = Matrix.matrix_addition(
			first_addendum,
			second_addendum
		);
		// END: solve covariation-error matrix

		// START:solve Kalman's gain coefficient
		// P * H_T
		double[][] first_multiplier = Matrix.matrix_multiplication(
			covariation_error,
			Matrix.matrix_transpose(StandardMatrix.H.getMatrix())
		);

		// H * P * H_T, output is scalar, that's important
		double[][] first_addendum_of_second_multiplier = Matrix.matrix_multiplication(
			StandardMatrix.H.getMatrix(),
			first_multiplier
		);

		// ( (k-1) / k ) * C + ( 1 / k ) * (H * P * H_T + R)
		double first_c_component = (((double) rowState.time) / (double) (rowState.time + 1)) * C;
		double second_c_component = (1.0 / (double) rowState.time ) * (first_addendum_of_second_multiplier[0][0] + R);

		C = first_c_component + second_c_component;
		R = C - first_addendum_of_second_multiplier[0][0];

		double second_multipliers_first_addendum = first_addendum_of_second_multiplier[0][0];

		double second_multiplier = second_multipliers_first_addendum +
			// R as noised velocity
			R;

		double[][] K = Matrix.matrix_multiplication(
			first_multiplier,
			// second_multiplier ** -1
			(1 / second_multiplier)
		);
		// END:solve Kalman's gain coefficient

		// solve strange coefficient Z as H * state + R
		double Z = Matrix.matrix_multiplication(
			StandardMatrix.H.getMatrix(),
			new double[][]{
				{rowState.velocity},
				{rowState.angle},
				{rowState.noise}
			}
			// noised velocity
		)[0][0] + rowState.velocity_noise;

		// START:find new state as state + K * (Z - H * assessment)
		// Z - H * assessment
		double[][] second_addition =
			Matrix.matrix_multiplication(
				K,
				Z - Matrix.matrix_multiplication(
					StandardMatrix.H.getMatrix(),
					assessment_state
				)[0][0]
			);

		previous_step_state = Matrix.matrix_addition(
			assessment_state,
			second_addition
		);
		// END:find new state as state + P * (Z - H * assessment)

		// solve covariation matrix's correct coefficient
		double coefficient = 1.0 - Matrix.matrix_multiplication(
			K,
			StandardMatrix.H.getMatrix()
		)[0][0];

		// correction covariation matrix
		covariation_error = Matrix.matrix_multiplication(
			covariation_error,
			coefficient
		);

		return new State(previous_step_state);
	}
}
