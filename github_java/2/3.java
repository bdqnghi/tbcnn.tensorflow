package tree_visualization;

import meetup_21_avl_tree.AvlBinarySearchTree;
import tree_visualization.avl.AvlInsertActionListener;
import tree_visualization.avl.AvlRemoveActionListener;

import javax.swing.*;
import java.awt.*;

public class AvlTreeDemo {
    public static boolean RIGHT_TO_LEFT = false;

    public static void addComponentsToPane(GroupLayout layout, JFrame frame) {
        JLabel valueLabel = new JLabel("Value:");
        JTextField valueField = new JTextField();

        Insets buttonMargin = new Insets(0, 0, 0, 0);
        JButton insertButton = new JButton("Insert");
        insertButton.setMargin(buttonMargin);

        AvlBinarySearchTree<Integer> tree = new AvlBinarySearchTree<>();
        TreePanel treePanel = new TreePanel();

        JButton removeButton = new JButton("Remove");
        removeButton.setMargin(buttonMargin);
        insertButton.addActionListener(new AvlInsertActionListener(treePanel, valueField, frame, tree));
        removeButton.addActionListener(new AvlRemoveActionListener(treePanel, valueField, frame, tree));

        layout.setHorizontalGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(valueLabel)
                                .addComponent(valueField)
                                .addComponent(insertButton)
                                .addComponent(removeButton))
                        .addComponent(treePanel)));

        layout.setVerticalGroup(layout.createSequentialGroup()
                .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                                .addComponent(valueLabel)
                                .addComponent(valueField)
                                .addComponent(insertButton)
                                .addComponent(removeButton)))
                .addComponent(treePanel));
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("AVL Binary Search Tree Demo");
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Container contentPane = frame.getContentPane();
        GroupLayout layout = new GroupLayout(contentPane);
        contentPane.setLayout(layout);

        layout.setAutoCreateGaps(true);
        layout.setAutoCreateContainerGaps(true);

        addComponentsToPane(layout, frame);

        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        /* Use an appropriate Look and Feel */
        try {
            //UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
            UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
        } catch (UnsupportedLookAndFeelException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }

        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        SwingUtilities.invokeLater(() -> createAndShowGUI());
    }

}
