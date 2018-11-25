#ifndef FORDFULKERSON
#define FORDFULKERSON

#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "hollowheap.h"
#include <iostream>
#include <limits.h>
#include <queue>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

# define INF 0x3f3f3f3f

typedef pair<unsigned, unsigned> iPair;
unsigned n, m, s, t;
 
class Graph
{
public:
    unsigned V, iterations;
    list< pair<unsigned, unsigned> > *adj;

    Graph( unsigned V ); 
    void addEdge( unsigned u, unsigned v, unsigned fat );
    unsigned getFlow( unsigned from, unsigned to, HollowHeap heap );
};

Graph::Graph( unsigned V )
{
    this->V = V;
    this->iterations = 0;
    adj = new list<iPair> [ V ];
}
 
void Graph::addEdge( unsigned u, unsigned v, unsigned fat )
{
    adj[ u ].push_back( make_pair( v, fat ) );
}

unsigned Graph::getFlow( unsigned from, unsigned to, HollowHeap heap )
{
	unsigned path = 1, flow = 0;

cout << from << " " << to << endl;
	while ( path == 1 )
	{
		cout << from << " " << to << endl;
		path = 0;
	    vector<unsigned> fats( V, 0 );
	    vector<unsigned> ants( V, 0 );
	    vector<unsigned> visit( V, 0 );

		for ( unsigned z = 1; z < V; z++ ) 
		{
			heap.insert( 0, z );
		}

	    heap.increaseKey( from, INF );

	    fats[ from ] = INF;
	    unsigned u, v = -1, weight = -1, stop = 0, get = 0;
	    unsigned paren[ V ];
	    memset( paren, INF, sizeof( paren ) );
	    paren[ 1 ] = 0;
	 
	    while ( !heap.isEmpty() && stop == 0 )
	    {
	        u = heap.deleteMax();        

	        if ( u != to && visit[ u ] == 0 )
	        {
		        list< pair<unsigned, unsigned> >::iterator i;

		        for ( i = adj[ u ].begin(); i != adj[ u ].end(); ++i )
		        {
		            v = ( *i ).first;

		            if ( v != from )
		            {
			            weight = ( *i ).second;

			            if ( weight > 0 )
			            {
				            unsigned minValue = min( fats[ u ], weight );

				            if ( fats[ v ] < minValue )
				            {
				            	paren[ v ] = u;

				            	fats[ v ] = minValue;
				            	heap.increaseKey( v, fats[ v ] );
				            }
				        }
			        }
		        }

		        visit[ u ] = 1;
		    }

	        if ( u == to )
	        {
	            get = 1;
	        }	        
	    }

	    list< pair<unsigned, unsigned> >::iterator i, i2;

	    unsigned k = V-1;

	    while ( paren[ k ] != 0 )
	    {
	    	if ( paren[ k ] > 0 && paren[ k ] < V )
	    	{
	    		unsigned value = 0;

	    		for ( i = adj[ paren[ k ] ].begin(); i != adj[ paren[ k ] ].end(); ++i )
	        	{
	        		if ( ( *i ).first == k )
	        		{
	        			( *i ).second -= fats[ to ];

	        			int found = 0;

	        			for ( i2 = adj[ k ].begin(); i2 != adj[ k ].end(); ++i2 )
	        			{
	        				if ( ( *i ).first == paren[ k ] )
	        				{
	        					found = 1;
	        					( *i ).second += fats[ to ];
	        					break;
	        				}
	        			}

	        			if ( found == 0 )
	        			{
	        				adj[ k ].push_back( make_pair( paren[ k ], fats[ to ] ) );
	        			}
	        		}
	        	}

	    		k = paren[ k ];
	    	}

	    	else
	    	{
	    		break;
	    	}
	    }

	    if ( get == 1 )
	    {
	    	flow += fats[ to ];
	    }

	    if ( fats[ to ] > 0 )
        {
        	path = 1;
        }

        iterations++;
	}

	return flow;
}

#endif