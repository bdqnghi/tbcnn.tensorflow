// =============================================================================
//
//   MSTPlugin.java
//
//   Copyright (c) 2001-2006, Gravisto Team, University of Passau
//
// =============================================================================
// $Id$

package org.graffiti.plugins.algorithms.mst;

import org.graffiti.plugin.GenericPluginAdapter;
import org.graffiti.plugin.PluginPathNode;
import org.graffiti.plugin.algorithm.Algorithm;

/**
 * Makes a set of minimum-spanning-tree algorithms available.
 * 
 * @author Harald
 * @version $Revision$ $Date$
 */
public class MSTPlugin extends GenericPluginAdapter {
    /**
     * Sole constructor; makes Prims algorithm available.
     * 
     */
    public MSTPlugin() {
        this.algorithms = new Algorithm[1];
        algorithms[0] = new PrimsAlgorithm();
    }

    @Override
    public PluginPathNode getPathInformation() {
        return new PluginPathNode(
                TREES,
                new Algorithm[0],
                new PluginPathNode[] { new PluginPathNode(MST, algorithms, null) });
    }

}

// -----------------------------------------------------------------------------
// end of file
// -----------------------------------------------------------------------------
