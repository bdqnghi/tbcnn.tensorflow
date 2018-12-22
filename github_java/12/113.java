/*******************************************************************************
 * Copyright (C) 2016 Embedded Systems and Applications Group
 * Department of Computer Science, Technische Universitaet Darmstadt,
 * Hochschulstr. 10, 64289 Darmstadt, Germany.
 * 
 * All rights reserved.
 * 
 * This software is provided free for educational use only.
 * It may not be used for commercial purposes without the
 * prior written permission of the authors.
 ******************************************************************************/
package mavlc.ast.nodes.expression;

import mavlc.ast.visitor.ASTNodeVisitor;

/**
 * AST-node representing a matrix-multiplication, including 
 * matrix-vector multiplications (commutative). 
 */
public class MatrixMultiplication extends BinaryExpression {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -4427758115968838508L;

	/**
	 * Constructor.
	 * @param sourceLine The source line in which the node was specified.
	 * @param sourceColumn The source column in which the node was specified.
	 * @param leftOperand The left operand of this matrix multiplication.
	 * @param rightOperand The right operand of this matrix multiplication.
	 */
	public MatrixMultiplication(int sourceLine, int sourceColumn, Expression leftOperand, Expression rightOperand){
		super(sourceLine, sourceColumn, leftOperand, rightOperand);
	}

	@Override
	public String dump() {
		return leftOp.dump()+" # "+rightOp.dump();
	}

	@Override
	public <RetTy, ArgTy> RetTy accept(ASTNodeVisitor<? extends RetTy, ArgTy> visitor, ArgTy obj){
		return visitor.visitMatrixMultiplication(this, obj);
	}

}
