/*§
  ===========================================================================
  GraphsJ - Algorithms
  ===========================================================================
  Copyright (C) 2009-2015 Gianluca Costa
  ===========================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public
  License along with this program.  If not, see
  <http://www.gnu.org/licenses/gpl-3.0.html>.
  ===========================================================================
*/

package info.gianlucacosta.graphsj3.scenarios.fordfulkerson;

import info.gianlucacosta.arcontes.algorithms.*;
import info.gianlucacosta.arcontes.fx.canvas.DefaultGraphCanvas;
import info.gianlucacosta.arcontes.fx.canvas.GraphCanvas;
import info.gianlucacosta.arcontes.fx.rendering.DefaultGraphRenderer;
import info.gianlucacosta.arcontes.graphs.Graph;
import info.gianlucacosta.arcontes.graphs.GraphContext;
import info.gianlucacosta.arcontes.graphs.Link;
import info.gianlucacosta.arcontes.graphs.Vertex;
import info.gianlucacosta.arcontes.graphs.wrappers.LinkWrapper;
import info.gianlucacosta.arcontes.graphs.wrappers.VertexWrapper;
import info.gianlucacosta.arcontes.graphs.wrappers.linkwrappers.NameBasedArcWrapper;
import info.gianlucacosta.arcontes.graphs.wrappers.vertexwrappers.NameBasedVertexWrapper;
import info.gianlucacosta.graphsj3.algorithms.fordfulkerson.FordFulkerson;
import info.gianlucacosta.graphsj3.algorithms.fordfulkerson.metainfo.FordFulkersonRuntimeVertexLabelInfo;
import info.gianlucacosta.graphsj3.scenarios.common.CommonScenario;
import info.gianlucacosta.graphsj3.scenarios.common.ScenarioSolution;
import info.gianlucacosta.helios.metainfo.MetaInfoRepository;

import java.util.Collection;
import java.util.Collections;

/**
 * Ford-Fulkerson's scenario
 */
public class FordFulkersonScenario extends CommonScenario {

    public FordFulkersonScenario() {
        super(true);
    }

    @Override
    protected CommonAlgorithm doCreateAlgorithm(GraphContext graphContext, CommonAlgorithmSettings algorithmSettings, AlgorithmInput algorithmInput, AlgorithmOutput algorithmOutput) {
        return new FordFulkerson(graphContext, algorithmSettings, algorithmInput, algorithmOutput);
    }

    @Override
    protected ScenarioSolution getPartialSolution(final Algorithm algorithm, int step) {
        return new ScenarioSolution() {
            @Override
            public Collection<Vertex> getVertexes() {
                return Collections.emptyList();
            }

            @Override
            public Collection<Link> getLinks() {
                FordFulkerson fordFulkerson = (FordFulkerson) algorithm;

                return fordFulkerson.getAugmentingPath();
            }

        };
    }

    @Override
    protected ScenarioSolution getCompleteSolution(final Algorithm algorithm) {
        return new ScenarioSolution() {
            @Override
            public Collection<Vertex> getVertexes() {
                FordFulkerson fordFulkerson = (FordFulkerson) algorithm;

                return fordFulkerson.getV2Group();
            }

            @Override
            public Collection<Link> getLinks() {
                FordFulkerson fordFulkerson = (FordFulkerson) algorithm;

                return fordFulkerson.getAugmentingPath();
            }

        };
    }

    @Override
    public void initRuntimeGraphContext(GraphContext runtimeGraphContext) {
        Graph graph = runtimeGraphContext.getGraph();
        MetaInfoRepository metaInfoRepository = runtimeGraphContext.getMetaInfoRepository();

        for (Vertex vertex : graph.getVertexes()) {
            metaInfoRepository.putMetaInfo(vertex, new FordFulkersonRuntimeVertexLabelInfo(metaInfoRepository, vertex));
        }
    }

    @Override
    public GraphCanvas createGraphCanvas(GraphContext graphContext) {
        return new DefaultGraphCanvas(
                new DefaultGraphRenderer(),
                new FordFulkersonCanvasAgentsFactory(getSettings(), getInputService()));
    }

    @Override
    public VertexWrapper createInputVertexWrapper(GraphContext graphContext, Vertex vertex) {
        return new NameBasedVertexWrapper(vertex, graphContext.getMetaInfoRepository());
    }

    @Override
    public LinkWrapper createInputLinkWrapper(GraphContext graphContext, Link link) {
        return new NameBasedArcWrapper(link, graphContext.getMetaInfoRepository());
    }

}
