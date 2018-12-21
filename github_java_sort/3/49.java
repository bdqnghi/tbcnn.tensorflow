
package org.hibernate.envers.internal.tools.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public final class GraphTopologicalSort {
	private GraphTopologicalSort() {
	}

	
	public static <V, R> List<V> sort(GraphDefiner<V, R> definer) {
		final List<V> values = definer.getValues();
		final Map<R, Vertex<R>> vertices = new HashMap<>();

		
		for ( V v : values ) {
			final R rep = definer.getRepresentation( v );
			vertices.put( rep, new Vertex<>( rep ) );
		}

		
		for ( V v : values ) {
			for ( V vn : definer.getNeighbours( v ) ) {
				vertices.get( definer.getRepresentation( v ) )
						.addNeighbour( vertices.get( definer.getRepresentation( vn ) ) );
			}
		}

		
		final List<R> sortedReps = new TopologicalSort<R>().sort( vertices.values() );

		
		final List<V> sortedValues = new ArrayList<>( sortedReps.size() );
		for ( R rep : sortedReps ) {
			sortedValues.add( definer.getValue( rep ) );
		}

		return sortedValues;
	}
}
