  



#include "Algorithm/MinimumSpanningTree.hh"

using namespace std;

namespace baboon {


	void MinimumSpanningTree::Point::SetPosition( const double &x , const double &y , const double &z ) {

		position.set( x , y , z );
	}


	void MinimumSpanningTree::Point::SetPosition( const ThreeVector &pos ) {

		position = ThreeVector( pos );
	}

	const ThreeVector &MinimumSpanningTree::Point::GetPosition() {

		return position;
	}


	void MinimumSpanningTree::Point::AddConnector( Connector *connector ) {

		if( connector == 0 )
			return;

		if( !this->IsConnectedTo( connector ) ) {
			connectors.push_back( connector );
		}
		return;

	}


	void MinimumSpanningTree::Point::RemoveConnector( MinimumSpanningTree::Connector *connector ) {

		if( connector == 0 )
			return;

		std::vector<MinimumSpanningTree::Connector*>::iterator it = std::find( connectors.begin() , connectors.end() , connector );
		if( it != connectors.end() ) {
			connectors.erase( it );
		}
		return;

	}


	bool MinimumSpanningTree::Point::IsConnectedTo( Connector *connector ) {

		return ( std::find( connectors.begin() , connectors.end() , connector ) != connectors.end() );
	}


	void MinimumSpanningTree::Point::SetObject( void *obj ) {

		object = obj;
	}


	void *MinimumSpanningTree::Point::GetObject() {

		return object;
	}

	bool MinimumSpanningTree::Point::HasNoConnection() {

		return connectors.empty();
	}




	void MinimumSpanningTree::Connector::Connect( Point *point1 , Point *point2 ) {

		if( point1 == 0 || point2 == 0 )
			return;

		pointPair.first = point1;
		pointPair.second = point2;
		weight = 0;
	}


	void MinimumSpanningTree::Connector::Connect( Point *point1 , Point *point2 , float w ) {

		if( point1 == 0 || point2 == 0 )
			return;

		pointPair.first = point1;
		pointPair.second = point2;
		weight = w;
	}


	void MinimumSpanningTree::Connector::Disconnect() {

		pointPair.first = 0;
		pointPair.second = 0;
		weight = 0;
	}





	MinimumSpanningTree::MinimumSpanningTree()
		: AbstractAlgorithm("MinimumSpanningTree") {

		needData = false;
	}


	MinimumSpanningTree::~MinimumSpanningTree() {

	}


	Return MinimumSpanningTree::Init() {

		ClearGraph();
		return BABOON_SUCCESS();
	}


	Return MinimumSpanningTree::CheckConsistency() {

		return BABOON_SUCCESS();
	}


	Return MinimumSpanningTree::Execute() {

		for( unsigned int c=0 ; c<initialPoints.size() ; c++ ) {

		}

		return BABOON_SUCCESS();
	}


	Return MinimumSpanningTree::End() {

		return BABOON_SUCCESS();
	}


	void MinimumSpanningTree::AddPoint( MinimumSpanningTree::Point *p ) {

		if( p == 0 )
			return;

		if( std::find( initialPoints.begin() , initialPoints.end() , p ) != initialPoints.end() ) {
			initialPoints.push_back( p );
		}
	}

	void MinimumSpanningTree::ClearGraph() {

		initialPoints.clear();
		minimumSpanningTree.clear();
		usedPoints.clear();
	}


}  

