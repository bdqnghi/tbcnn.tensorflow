/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 * contributors as indicated by the @authors tag. See the 
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */


/**
 * @ingroup dataflow_components
 * @file
 * Matrix multiplication component.
 * This file contains a generic 4x4 matrix transformation implemented as a \c TriggerComponent.
 *
 * @author Florian Echtler <echtler@in.tum.de>
 */
#include <utDataflow/TriggerComponent.h>
#include <utDataflow/TriggerInPort.h>
#include <utDataflow/TriggerOutPort.h>
#include <utDataflow/ComponentFactory.h>
#include <utMeasurement/Measurement.h>
#include <utMath/Matrix.h>

// get a logger
static log4cpp::Category& logger( log4cpp::Category::getInstance( "Ubitrack.Components.Multiplication" ) );

namespace Ubitrack { namespace Components {



Math::Vector< double, 3 > operator*( const Math::Matrix< double, 4, 4 > mat, const Math::Vector< double, 3 > vec )
{
	Math::Vector< double, 4 > hom( vec[0], vec[1], vec[2], 1.0 );
	Math::Vector< double, 4 > tmp;
	Math::Vector< double, 3 > res;

	tmp = boost::numeric::ublas::prod( mat, hom );
	double w = tmp[3];
	tmp = tmp / w;

	res[0] = tmp[0];
	res[1] = tmp[1];
	res[2] = tmp[2];

	return res;
};


std::vector< Math::Vector< double, 3 > > operator*( const Math::Matrix< double, 4, 4 > mat, const std::vector< Math::Vector< double, 3 > > vecList )
{
	std::vector< Math::Vector< double, 3 > > result( vecList.size() );
	for ( unsigned i = 0; i < vecList.size(); i++ )
		result[ i ] = mat * vecList[i];
	return result;
};


Math::Vector< double, 2 > operator*( const Math::Matrix< double, 3, 4 > mat, const Math::Vector< double, 3 > vec )
{
	Math::Vector< double, 4 > hom( vec(0), vec(1), vec(2), 1.0 );
	Math::Vector< double, 3 > tmp;
	Math::Vector< double, 2 > res;

	tmp = boost::numeric::ublas::prod( mat, hom );
	double w = tmp[2];
	tmp = tmp / w;

	res[0] = tmp[0];
	res[1] = tmp[1];

	return res;
};


Math::Vector< double, 2 > operator*( const Math::Matrix< double, 3, 3 > mat, const Math::Vector< double, 2 > vec )
{
	Math::Vector< double, 3 > hom( vec(0), vec(1), 1.0 );
	Math::Vector< double, 2	> tmp;
	Math::Vector< double, 2 > res;

	tmp = boost::numeric::ublas::prod( mat, hom );
	double w = tmp[1];
	tmp = tmp / w;

	res[0] = tmp[0];
	res[1] = tmp[1];

	return res;
};


std::vector< Math::Vector< double, 2 > > operator*( const Math::Matrix< double, 3, 4 > mat, const std::vector< Math::Vector< double, 3 > > vecList )
{
	std::vector< Math::Vector< double, 2 > > result( vecList.size() );
	for ( unsigned i = 0; i < vecList.size(); i++ )
		result[ i ] = mat * vecList[i];
	return result;
};


std::vector< Math::Vector< double, 2 > > operator*( const Math::Matrix< double, 3, 3 > mat, const std::vector< Math::Vector< double, 2 > > vecList )
{
	std::vector< Math::Vector< double, 2 > > result( vecList.size() );
	for ( unsigned i = 0; i < vecList.size(); i++ )
		result[ i ] = mat * vecList[i];
	return result;
};


/**
 * @ingroup dataflow_components
 * Matrix multiplication component.
 * This file contains a generic 4x4 matrix transformation implemented as a \c TriggerComponent.
 *
 * The component multiplies requested/incoming events with the transformation matrix
 * and returns the homogenized result.
 */
template< class MatType, class VecType, class ResType >
class MatrixMultiplicationComponent
	: public Dataflow::TriggerComponent
{
public:
	/**
	 * Standard component constructor.
	 *
	 * @param sName Unique name of the component.
	 * @param cfg ComponentConfiguration containing all configuration.
	 */
	MatrixMultiplicationComponent( const std::string& sName, boost::shared_ptr< Graph::UTQLSubgraph > pConfig )
		: Dataflow::TriggerComponent( sName, pConfig )
		, m_inPortA( "AB", *this )
		, m_inPortB( "BC", *this )
		, m_outPort( "AC", *this )
	{}

	void compute( Measurement::Timestamp t )
	{
		typename MatType::value_type mat = *(m_inPortA.get());
		typename VecType::value_type vec = *(m_inPortB.get());
		typename ResType::value_type res;

		try {
			res = mat * vec;
		}
		catch (void*) {
			LOG4CPP_INFO( logger, "division by zero during dehomogenization" );
			return;
		}

		m_outPort.send( ResType ( t, res ) );
	}

	
protected:
	/** Input ports of the component. */
	Dataflow::TriggerInPort< MatType > m_inPortA;
	Dataflow::TriggerInPort< VecType > m_inPortB;

	/** Output port of the component. */
	Dataflow::TriggerOutPort< ResType > m_outPort;
};


UBITRACK_REGISTER_COMPONENT( Dataflow::ComponentFactory* const cf ) {
	cf->registerComponent< MatrixMultiplicationComponent< Measurement::Matrix4x4, Measurement::Position, Measurement::Position > > ( "MatrixMultiplication" );
	cf->registerComponent< MatrixMultiplicationComponent< Measurement::Matrix3x4, Measurement::Position, Measurement::Position2D > > ( "MatrixProjection" );
	cf->registerComponent< MatrixMultiplicationComponent< Measurement::Matrix4x4, Measurement::PositionList, Measurement::PositionList > > ( "MatrixListMultiplication" );
	cf->registerComponent< MatrixMultiplicationComponent< Measurement::Matrix3x4, Measurement::PositionList, Measurement::PositionList2 > > ( "MatrixListProjection" );
	cf->registerComponent< MatrixMultiplicationComponent< Measurement::Matrix3x3, Measurement::PositionList2, Measurement::PositionList2 > > ( "MatrixList2Multiplication" );
}

} } // namespace Ubitrack::Components

