  



#ifndef MINIMUMSPANNINGTREE_HH
#define MINIMUMSPANNINGTREE_HH

#include "Algorithm/AbstractAlgorithm.hh"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <utility>

#include "Geometry/ThreeVector.hh"

namespace baboon {

	

	class MinimumSpanningTree : public AbstractAlgorithm {


		class Connector;


		
		class Point {


			public:
				
				void SetPosition( const double &x , const double &y , const double &z );

				
				void SetPosition( const ThreeVector &pos );

				
				const ThreeVector &GetPosition();

				
				void AddConnector( MinimumSpanningTree::Connector *connector );

				
				void RemoveConnector( MinimumSpanningTree::Connector *connector );

				
				bool IsConnectedTo( MinimumSpanningTree::Connector *connector );

				
				void SetObject( void *obj );

				
				void *GetObject();

				
				bool HasNoConnection();


			protected:

				ThreeVector position;
				std::vector<MinimumSpanningTree::Connector *> connectors;
				void *object;
		};

		
		class Connector {

			public:
				
				void Connect( MinimumSpanningTree::Point *point1 , MinimumSpanningTree::Point *point2 );

				
				void Connect( MinimumSpanningTree::Point *point1 , MinimumSpanningTree::Point *point2 , float w );

				
				void Disconnect();


			protected:
				std::pair<MinimumSpanningTree::Point*,MinimumSpanningTree::Point*> pointPair;
				float weight;

		};

		public:
			
			MinimumSpanningTree();

			
			virtual ~MinimumSpanningTree();

			
			virtual Return Init();

			
			virtual Return CheckConsistency();

			
			virtual Return Execute();

			
			virtual Return End();

			
			void AddPoint( MinimumSpanningTree::Point *p );


		protected:

			
			void ClearGraph();

			
			void FindLeastConnection( MinimumSpanningTree::Connector *connector );

			std::vector<MinimumSpanningTree::Point *> initialPoints;
			std::vector<MinimumSpanningTree::Connector *> minimumSpanningTree;
			std::vector<MinimumSpanningTree::Point *> usedPoints;

	};  

}  

#endif  
