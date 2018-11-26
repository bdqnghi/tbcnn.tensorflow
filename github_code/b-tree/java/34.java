package de.vaadin.sample.components;

import com.google.inject.Inject;

import com.vaadin.event.dd.DragAndDropEvent;
import com.vaadin.event.dd.DropHandler;
import com.vaadin.event.dd.DropTarget;
import com.vaadin.event.dd.acceptcriteria.AcceptCriterion;
import com.vaadin.server.PaintException;
import com.vaadin.server.PaintTarget;

import de.vaadin.sample.data.NodeContainer;
import de.vaadin.sample.data.NodeContainerB;
import de.vaadin.sample.data.TreeExpander;
import de.vaadin.sample.data.TreeExpanderB;
import de.vaadin.sample.db.domain.Node;

import static com.vaadin.ui.AbstractSelect.AcceptItem.ALL;

public class TreeB extends SampleTree {

    @Inject
    TreeB(NodeContainerB nodeContainer, TreeExpanderB treeExpander, DropHandler dropHandler) {
        super(nodeContainer, treeExpander, dropHandler);
    }
}
