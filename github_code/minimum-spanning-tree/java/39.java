package br.usp.pf.jung.mst;

import br.usp.pf.core.Graph;
import br.usp.pf.util.colors.scales.*;
import br.usp.pf.view.util.PrintScreenPanel;
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import edu.uci.ics.jung.algorithms.layout.*;
import edu.uci.ics.jung.algorithms.shortestpath.*;
import edu.uci.ics.jung.graph.DelegateForest;
import edu.uci.ics.jung.graph.DelegateTree;
import edu.uci.ics.jung.visualization.*;
import edu.uci.ics.jung.visualization.control.*;
import edu.uci.ics.jung.visualization.decorators.*;
import edu.uci.ics.jung.visualization.renderers.Renderer;
import edu.uci.ics.jung.visualization.transform.MutableTransformer;

import org.apache.commons.collections15.Transformer;

/**
 *
 * @author fm
 */
public class MinimumSpanningTree extends JApplet {
    
    /**
	 */
    VisualizationViewer<Integer, MyLink> vv1;
    /**
	 */
    MutableTransformer layoutTransformer;
    
    /**
	 */
    Dimension preferredSize = new Dimension(1000, 800);
    /**
	 */
    Dimension preferredLayoutSize = new Dimension(2000, 1200);
    /**
	 */
    Dimension preferredSizeRect = new Dimension(2000, 1200);
    
    //edge weight transformer
    /**
	 */
    Transformer<MyLink, Double> wtTransformer = new Transformer<MyLink, Double>() {
        @Override
        public Double transform(MyLink link) {
            return (double) link.getWeight();
        }
    };    

    public MinimumSpanningTree(String filename) throws Exception {

        final Graph graph = new Graph(filename);
        
        System.gc();
        
        MinimumSpanningForest2<Integer, MyLink> msf = new MinimumSpanningForest2<Integer, MyLink>
                (graph.getUndirectedSparseGraph(), 
                 new DelegateForest<Integer, MyLink>(),
                 DelegateTree.<Integer, MyLink>getFactory(),
                 wtTransformer);
        
//        MinimumSpanningForest<Integer, MyLink> msf = new MinimumSpanningForest<Integer, MyLink>
//                (graph.getUndirectedSparseGraph(),
//                new DelegateForest<Integer, MyLink>(),
//                graph.getRoot().getKey());
                
        
        System.gc();

        Layout<Integer, MyLink> mstLayout = new TreeLayout<Integer, MyLink>(msf.getForest(), 10, 500);
        
        Layout<Integer, MyLink> otherLayout = null;        
        //otherLayout = new FRLayout(graph.getUndirectedSparseGraph());
        //otherLayout = new FRLayout2(graph.getUndirectedSparseGraph());
        //otherLayout = new CircleLayout(graph.getUndirectedSparseGraph());
        //otherLayout = new SpringLayout(graph.getUndirectedSparseGraph());
        //otherLayout = new SpringLayout2(graph.getUndirectedSparseGraph());
        //otherLayout =  new KKLayout(graph.getUndirectedSparseGraph());        
        //otherLayout = new ISOMLayout(graph.getUndirectedSparseGraph());
        //otherLayout = new StaticLayout(graph.getUndirectedSparseGraph());
        //otherLayout.setMaxIterations(2000);
        //otherLayout.setSize(new Dimension(1600000000, 900000000));
        //otherLayout.setSize(new Dimension(160000, 90000));
        
        VisualizationModel<Integer, MyLink> vm1 = new DefaultVisualizationModel<Integer, MyLink>
                (mstLayout, preferredSizeRect);

        //--------------------------------------------------------------------------------

        vv1 = new VisualizationViewer<Integer, MyLink>(vm1, preferredSizeRect);

        vv1.getRenderContext().setEdgeShapeTransformer(new EdgeShape.Line());

        Color back = Color.WHITE;
        vv1.setBackground(back);

        vv1.getRenderer().getVertexLabelRenderer().setPosition(Renderer.VertexLabel.Position.CNTR);
        vv1.setForeground(Color.darkGray);
        
        //define color scale for edges drawing
        final ColorScale edgesColorScale = new BlueToYellowScale2();        
        edgesColorScale.setMinMax(graph.getEdgesMinEnergy(), graph.getEdgesMaxEnergy());
        edgesColorScale.setReverse(false);

        //edge paint transformer
        Transformer<MyLink, Paint> linkPaint = new Transformer<MyLink, Paint>() {
            @Override
            public Paint transform(MyLink l) {
                return edgesColorScale.getColor(l.getWeight());
            }
        };

        //vertices body paint transformer
        Transformer<Integer, Paint> vertexPaint = new Transformer<Integer, Paint>() {
            @Override
            public Paint transform(Integer i) {
                //float nodeEnergy = nodes[i].energy;
                //return calculateColor(nodeEnergy, rootEnergy);
                return Color.DARK_GRAY;
            }
        };

        vv1.getRenderContext().setEdgeDrawPaintTransformer(linkPaint);
        vv1.getRenderContext().setVertexFillPaintTransformer(vertexPaint);

        vv1.setVertexToolTipTransformer(new ToStringLabeller());

        vv1.setLayout(new BorderLayout());

        Container content = getContentPane();
        JPanel grid = new JPanel(new GridLayout(0, 1));
        JPanel panel = new JPanel(new BorderLayout());
        grid.add(new GraphZoomScrollPane(vv1));
        panel.add(grid);

        content.add(panel);

        DefaultModalGraphMouse gm0 = new DefaultModalGraphMouse();
        DefaultModalGraphMouse gm1 = new DefaultModalGraphMouse();
        DefaultModalGraphMouse gm2 = new DefaultModalGraphMouse();
        DefaultModalGraphMouse gm3 = new DefaultModalGraphMouse();

        vv1.setGraphMouse(gm1);

        final ScalingControl scaler = new CrossoverScalingControl();

        vv1.scaleToLayout(scaler);

        JButton plus = new JButton("+");
        plus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                scaler.scale(vv1, 1.1f, vv1.getCenter());
            }
        });
        JButton minus = new JButton("-");
        minus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                scaler.scale(vv1, 1 / 1.1f, vv1.getCenter());
            }
        });
        
        PrintScreenPanel psp = new PrintScreenPanel(vv1);

        JPanel zoomPanel = new JPanel(new GridLayout(1, 2));
        zoomPanel.setBorder(BorderFactory.createTitledBorder("Zoom"));
                

        JPanel controls = new JPanel();
        zoomPanel.add(plus);
        zoomPanel.add(minus);
        controls.add(zoomPanel);
        controls.add(psp);
        content.add(controls, BorderLayout.SOUTH);

    }
    
    public static void main(String[] args) throws Exception {
        JFrame f = new JFrame();
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //f.getContentPane().add(new MinimumSpanningTree("../data/graphs/jung/testes/t-10.gph"));
        f.getContentPane().add(new MinimumSpanningTree("../data/graphs/jung/inicial/c-5.gph"));
        //f.getContentPane().add(new MinimumSpanningTree("../data/graphs/jung/res_alta_hidrofobicidade/c-5.gph"));
        //f.getContentPane().add(new MinimumSpanningTree("../data/graphs/jung/res_baixa_hidrofobicidade/c-5.gph"));
        //f.getContentPane().add(new MinimumSpanningTree("../data/graphs/jung/novos_dados/c-2.gph"));
        f.pack();
        f.setVisible(true);

    }
}
