/*
 * Copyright 2015 Delft University of Technology
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package science.atlarge.graphalytics.giraph.algorithms.bfs;

import science.atlarge.graphalytics.domain.graph.FormattedGraph;
import science.atlarge.graphalytics.domain.algorithms.BreadthFirstSearchParameters;
import science.atlarge.graphalytics.giraph.GiraphJob;
import science.atlarge.graphalytics.giraph.io.DirectedLongNullTextEdgeInputFormat;
import science.atlarge.graphalytics.giraph.io.UndirectedLongNullTextEdgeInputFormat;
import org.apache.giraph.comm.messages.MessageEncodeAndStoreType;
import org.apache.giraph.conf.GiraphConfiguration;
import org.apache.giraph.graph.Computation;
import org.apache.giraph.io.EdgeInputFormat;
import org.apache.giraph.io.EdgeOutputFormat;
import org.apache.giraph.io.VertexInputFormat;
import org.apache.giraph.io.VertexOutputFormat;
import org.apache.giraph.io.formats.IdWithValueTextOutputFormat;

import static science.atlarge.graphalytics.giraph.algorithms.bfs.BreadthFirstSearchConfiguration.SOURCE_VERTEX;
import static org.apache.giraph.conf.GiraphConstants.MESSAGE_ENCODE_AND_STORE_TYPE;

/**
 * The job configuration of the breadth-first-search implementation for Giraph.
 *
 * @author Tim Hegeman
 */
public class BreadthFirstSearchJob extends GiraphJob {

	private BreadthFirstSearchParameters parameters;
	private FormattedGraph formattedGraph;

	/**
	 * Constructs a breadth-first-search job with a BFSParameters object containing
	 * graph-specific parameters, and a graph format specification
	 *
	 * @param parameters  the graph-specific BFS parameters
	 * @param formattedGraph the graph format specification
	 */
	public BreadthFirstSearchJob(Object parameters, FormattedGraph formattedGraph) {
		assert (parameters instanceof BreadthFirstSearchParameters);
		this.parameters = (BreadthFirstSearchParameters)parameters;
		this.formattedGraph = formattedGraph;
	}

	@SuppressWarnings("rawtypes")
	@Override
	protected Class<? extends Computation> getComputationClass() {
		return BreadthFirstSearchComputation.class;
	}

	@SuppressWarnings("rawtypes")
	@Override
	protected Class<? extends VertexInputFormat> getVertexInputFormatClass() {
		return BreadthFirstSearchVertexInputFormat.class;
	}

	@SuppressWarnings("rawtypes")
	@Override
	protected Class<? extends VertexOutputFormat> getVertexOutputFormatClass() {
		return IdWithValueTextOutputFormat.class;
	}

	@SuppressWarnings("rawtypes")
	@Override
	protected Class<? extends EdgeInputFormat> getEdgeInputFormatClass() {
		return formattedGraph.isDirected() ?
				DirectedLongNullTextEdgeInputFormat.class :
				UndirectedLongNullTextEdgeInputFormat.class;
	}

	@SuppressWarnings("rawtypes")
	@Override
	protected Class<? extends EdgeOutputFormat> getEdgeOutputFormatClass() {
		return null;
	}

	@Override
	protected void configure(GiraphConfiguration config) {
		SOURCE_VERTEX.set(config, parameters.getSourceVertex());
		// Set the message store type to optimize for one-to-many messages (i.e. broadcasts as used in BFS)
		MESSAGE_ENCODE_AND_STORE_TYPE.set(config, MessageEncodeAndStoreType.EXTRACT_BYTEARRAY_PER_PARTITION);
	}

}
