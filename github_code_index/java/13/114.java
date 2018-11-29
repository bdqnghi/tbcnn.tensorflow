package com.eaglebytes.sorting;

import com.eaglebytes.util.MathUtils;
import com.eaglebytes.util.Vector2f;
import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

public class Shell extends javax.swing.JFrame {

    private int[] data;
    private Object[] sortArray;

    public Shell() {
        initComponents();
        pack();
        BubbleSort bubble = new BubbleSort();
        QuickSort quick = new QuickSort();
        PartitionSort partition = new PartitionSort();
        ShellSort shell = new ShellSort();
        sortArray = new Object[]{bubble, quick, partition, shell};
        setSize(1065, 750);
        setLocationRelativeTo(null);
        ((Panel) renderPanel).preInit();
        sequentialButton.doClick();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        renderPanel = new Panel();
        dataGenPanel = new javax.swing.JPanel();
        dataGenLabel = new javax.swing.JLabel();
        minMaxPanel = new javax.swing.JPanel();
        minValuePanel = new javax.swing.JPanel();
        minValueSlider = new javax.swing.JSlider();
        minValueLabel = new javax.swing.JLabel();
        minTextField = new javax.swing.JTextField();
        maxSliderPanel = new javax.swing.JPanel();
        maxValueSlider = new javax.swing.JSlider();
        maxValueLabel = new javax.swing.JLabel();
        maxTextField = new javax.swing.JTextField();
        sequentialButton = new javax.swing.JButton();
        elementsField = new javax.swing.JTextField();
        generateButton = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        elementsSlider = new javax.swing.JSlider();
        jButton1 = new javax.swing.JButton();
        sortButton = new javax.swing.JButton();
        jButton2 = new javax.swing.JButton();
        jSlider1 = new javax.swing.JSlider();
        sortTypes = new javax.swing.JComboBox();
        animateSortButton = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Shell");
        setResizable(false);

        renderPanel.setPreferredSize(new java.awt.Dimension(800, 672));

        javax.swing.GroupLayout renderPanelLayout = new javax.swing.GroupLayout(renderPanel);
        renderPanel.setLayout(renderPanelLayout);
        renderPanelLayout.setHorizontalGroup(
            renderPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 800, Short.MAX_VALUE)
        );
        renderPanelLayout.setVerticalGroup(
            renderPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        dataGenPanel.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        dataGenLabel.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        dataGenLabel.setText("Data Generation");

        minMaxPanel.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));

        minValueSlider.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        minValueSlider.setMajorTickSpacing(100);
        minValueSlider.setMaximum(600);
        minValueSlider.setMinorTickSpacing(25);
        minValueSlider.setOrientation(javax.swing.JSlider.VERTICAL);
        minValueSlider.setPaintLabels(true);
        minValueSlider.setPaintTicks(true);
        minValueSlider.setValue(100);
        minValueSlider.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                minValueSliderStateChanged(evt);
            }
        });

        minValueLabel.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        minValueLabel.setText("Min");

        minTextField.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        minTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        minTextField.setText("100");
        minTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                minTextFieldActionPerformed(evt);
            }
        });
        minTextField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                minTextFieldKeyReleased(evt);
            }
        });

        javax.swing.GroupLayout minValuePanelLayout = new javax.swing.GroupLayout(minValuePanel);
        minValuePanel.setLayout(minValuePanelLayout);
        minValuePanelLayout.setHorizontalGroup(
            minValuePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(minValuePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(minValuePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(minValuePanelLayout.createSequentialGroup()
                        .addComponent(minValueSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, minValuePanelLayout.createSequentialGroup()
                        .addComponent(minValueLabel)
                        .addGap(25, 25, 25))))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, minValuePanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(minTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        minValuePanelLayout.setVerticalGroup(
            minValuePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(minValuePanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(minValueLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(minValueSlider, javax.swing.GroupLayout.DEFAULT_SIZE, 175, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(minTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        maxValueSlider.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        maxValueSlider.setMajorTickSpacing(100);
        maxValueSlider.setMaximum(600);
        maxValueSlider.setMinorTickSpacing(25);
        maxValueSlider.setOrientation(javax.swing.JSlider.VERTICAL);
        maxValueSlider.setPaintLabels(true);
        maxValueSlider.setPaintTicks(true);
        maxValueSlider.setValue(600);
        maxValueSlider.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                maxValueSliderStateChanged(evt);
            }
        });

        maxValueLabel.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        maxValueLabel.setText("Max");

        maxTextField.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        maxTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        maxTextField.setText("600");
        maxTextField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                maxTextFieldKeyReleased(evt);
            }
        });

        javax.swing.GroupLayout maxSliderPanelLayout = new javax.swing.GroupLayout(maxSliderPanel);
        maxSliderPanel.setLayout(maxSliderPanelLayout);
        maxSliderPanelLayout.setHorizontalGroup(
            maxSliderPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(maxSliderPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(maxSliderPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(maxSliderPanelLayout.createSequentialGroup()
                        .addComponent(maxValueSlider, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, maxSliderPanelLayout.createSequentialGroup()
                        .addComponent(maxValueLabel)
                        .addGap(25, 25, 25))))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, maxSliderPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(maxTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        maxSliderPanelLayout.setVerticalGroup(
            maxSliderPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(maxSliderPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(maxValueLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(maxValueSlider, javax.swing.GroupLayout.DEFAULT_SIZE, 175, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(maxTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        sequentialButton.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        sequentialButton.setText("Sequential");
        sequentialButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sequentialButtonActionPerformed(evt);
            }
        });

        elementsField.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        elementsField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        elementsField.setText("710");
        elementsField.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                elementsFieldMousePressed(evt);
            }
        });
        elementsField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                elementsFieldKeyReleased(evt);
            }
        });

        generateButton.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        generateButton.setText("Random");
        generateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                generateButtonActionPerformed(evt);
            }
        });

        jLabel1.setFont(new java.awt.Font("Comic Sans MS", 0, 13)); // NOI18N
        jLabel1.setText("Number of Elements");

        elementsSlider.setMajorTickSpacing(355);
        elementsSlider.setMaximum(710);
        elementsSlider.setMinorTickSpacing(150);
        elementsSlider.setPaintLabels(true);
        elementsSlider.setPaintTicks(true);
        elementsSlider.setValue(710);
        elementsSlider.setPreferredSize(new java.awt.Dimension(100, 23));
        elementsSlider.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                elementsSliderStateChanged(evt);
            }
        });

        jButton1.setText("Sine");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout minMaxPanelLayout = new javax.swing.GroupLayout(minMaxPanel);
        minMaxPanel.setLayout(minMaxPanelLayout);
        minMaxPanelLayout.setHorizontalGroup(
            minMaxPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(minMaxPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(minMaxPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(minMaxPanelLayout.createSequentialGroup()
                        .addComponent(minValuePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(maxSliderPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(sequentialButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(elementsField)
                    .addComponent(elementsSlider, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(minMaxPanelLayout.createSequentialGroup()
                        .addComponent(generateButton, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 74, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, minMaxPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel1)
                .addGap(35, 35, 35))
        );

        minMaxPanelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {generateButton, jButton1});

        minMaxPanelLayout.setVerticalGroup(
            minMaxPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(minMaxPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(minMaxPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(maxSliderPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(minValuePanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel1)
                .addGap(2, 2, 2)
                .addComponent(elementsField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(elementsSlider, javax.swing.GroupLayout.DEFAULT_SIZE, 52, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sequentialButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(minMaxPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(generateButton)
                    .addComponent(jButton1))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        minMaxPanelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {generateButton, jButton1, sequentialButton});

        sortButton.setText("Sort");
        sortButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sortButtonActionPerformed(evt);
            }
        });

        jButton2.setText("Step");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });

        jSlider1.setMajorTickSpacing(250);
        jSlider1.setMaximum(1000);
        jSlider1.setMinorTickSpacing(100);
        jSlider1.setPaintLabels(true);
        jSlider1.setPaintTicks(true);
        jSlider1.setValue(0);
        jSlider1.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                jSlider1StateChanged(evt);
            }
        });

        sortTypes.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Bubble Sort", "Quick Sort", "Partition Sort", "Shell Sort" }));

        animateSortButton.setText("Animate");
        animateSortButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                animateSortButtonActionPerformed(evt);
            }
        });

        jLabel2.setText("Animation Speed");

        javax.swing.GroupLayout dataGenPanelLayout = new javax.swing.GroupLayout(dataGenPanel);
        dataGenPanel.setLayout(dataGenPanelLayout);
        dataGenPanelLayout.setHorizontalGroup(
            dataGenPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(dataGenPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(dataGenPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataGenPanelLayout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(dataGenLabel)
                        .addGap(64, 64, 64))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataGenPanelLayout.createSequentialGroup()
                        .addComponent(sortTypes, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataGenPanelLayout.createSequentialGroup()
                        .addComponent(minMaxPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addContainerGap())
                    .addGroup(dataGenPanelLayout.createSequentialGroup()
                        .addComponent(sortButton, javax.swing.GroupLayout.PREFERRED_SIZE, 96, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(animateSortButton, javax.swing.GroupLayout.PREFERRED_SIZE, 99, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())
                    .addGroup(dataGenPanelLayout.createSequentialGroup()
                        .addGap(55, 55, 55)
                        .addComponent(jLabel2)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataGenPanelLayout.createSequentialGroup()
                        .addGroup(dataGenPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(jButton2, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jSlider1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addContainerGap())))
        );

        dataGenPanelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {animateSortButton, sortButton});

        dataGenPanelLayout.setVerticalGroup(
            dataGenPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(dataGenPanelLayout.createSequentialGroup()
                .addGap(7, 7, 7)
                .addComponent(dataGenLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(minMaxPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sortTypes, javax.swing.GroupLayout.DEFAULT_SIZE, 46, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(dataGenPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(sortButton)
                    .addComponent(animateSortButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSlider1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jButton2)
                .addContainerGap())
        );

        jMenu1.setText("File");

        jMenuItem2.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_F4, java.awt.event.InputEvent.ALT_MASK));
        jMenuItem2.setText("Exit");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem2);

        jMenuBar1.add(jMenu1);

        jMenu2.setText("Help");

        jMenuItem1.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_H, java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem1.setText("About");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem1);

        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(renderPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(dataGenPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(renderPanel, javax.swing.GroupLayout.DEFAULT_SIZE, 687, Short.MAX_VALUE)
                    .addComponent(dataGenPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void generateButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_generateButtonActionPerformed
        try {
            int indices = Integer.parseInt(elementsField.getText());
            data = new int[indices];
            for (int i = 0; i < indices; i++)
                data[i] = (int) (Math.random() * (maxValueSlider.getValue() - minValueSlider.getValue()) + minValueSlider.getValue());
            ((Panel) renderPanel).data = data;
            ((Panel) renderPanel).init();
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_generateButtonActionPerformed

    private void maxValueSliderStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_maxValueSliderStateChanged
        if (minValueSlider.getValue() > maxValueSlider.getValue() - 1)
            minValueSlider.setValue(maxValueSlider.getValue() - 1);
        if (maxValueSlider.getValue() == 0)
            maxValueSlider.setValue(1);
        maxTextField.setText("" + maxValueSlider.getValue());
    }//GEN-LAST:event_maxValueSliderStateChanged

    private void minValueSliderStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_minValueSliderStateChanged
        if (maxValueSlider.getValue() < minValueSlider.getValue() + 1)
            maxValueSlider.setValue(minValueSlider.getValue() + 1);
        if (minValueSlider.getValue() == 600)
            minValueSlider.setValue(599);
        minTextField.setText("" + minValueSlider.getValue());
    }//GEN-LAST:event_minValueSliderStateChanged

    private void minTextFieldKeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_minTextFieldKeyReleased
        try {
            if (!minTextField.getText().matches("800|[0-7][0-9][0-9]|[0-9][0-9]|[0-9]"))
                minTextField.setText(minTextField.getText().substring(0, minTextField.getText().length() - 1));
            minValueSlider.setValue(Integer.parseInt(minTextField.getText()));
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_minTextFieldKeyReleased

    private void maxTextFieldKeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_maxTextFieldKeyReleased
        try {
            if (!maxTextField.getText().matches("800|[0-7][0-9][0-9]|[0-9][0-9]|[0-9]"))
                maxTextField.setText(maxTextField.getText().substring(0, maxTextField.getText().length() - 1));
            maxValueSlider.setValue(Integer.parseInt(maxTextField.getText()));
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_maxTextFieldKeyReleased

    private void elementsFieldMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_elementsFieldMousePressed
        if (elementsField.getText().matches(""))
            elementsField.setText("");
    }//GEN-LAST:event_elementsFieldMousePressed

    private void sequentialButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sequentialButtonActionPerformed
        try {
            int indices = Integer.parseInt(elementsField.getText());
            data = new int[indices];
            for (int i = 0; i < indices; i++)
                data[i] = (int) (maxValueSlider.getValue()-(float) i * (maxValueSlider.getValue() - minValueSlider.getValue()) / (indices - 1));
            ((Panel) renderPanel).data = data;
            ((Panel) renderPanel).init();
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_sequentialButtonActionPerformed

    private void elementsFieldKeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_elementsFieldKeyReleased
        try {
            if (!elementsField.getText().matches("800|[0-7][0-9][0-9]|[0-9][0-9]|[0-9]"))
                elementsField.setText(elementsField.getText().substring(0, elementsField.getText().length() - 1));
            elementsSlider.setValue(Integer.parseInt(elementsField.getText()));
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_elementsFieldKeyReleased

    private void elementsSliderStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_elementsSliderStateChanged
        elementsField.setText("" + elementsSlider.getValue());
    }//GEN-LAST:event_elementsSliderStateChanged

    private void sortButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sortButtonActionPerformed
        ((Panel) renderPanel).sort();
    }//GEN-LAST:event_sortButtonActionPerformed

    private void jSlider1StateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_jSlider1StateChanged
        ((Panel) renderPanel).sortSpeed = jSlider1.getValue();
    }//GEN-LAST:event_jSlider1StateChanged

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed
        ((Panel) renderPanel).sortStep();
    }//GEN-LAST:event_jButton2ActionPerformed

    private void animateSortButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_animateSortButtonActionPerformed
        ((Panel) renderPanel).animateSort();
    }//GEN-LAST:event_animateSortButtonActionPerformed

    private void minTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_minTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_minTextFieldActionPerformed

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        try {
            int indices = Integer.parseInt(elementsField.getText());
            data = new int[indices];
            for (int i = 0; i < indices; i++)
                data[i] = (int)(600f*Math.abs(Math.sin(Math.toRadians(1/2f*i/data.length*360))));
//                data[i] = (int)((i-indices/2f)/15f*(i-indices/2f)/15f);
//                data[i] = (int)(100f/Math.abs(Math.sin(Math.toRadians(20f*i/data.length*360f))));
            ((Panel) renderPanel).data = data;
            ((Panel) renderPanel).init();
        } catch (Exception e) {
            System.err.println(e);
        }
    }//GEN-LAST:event_jButton1ActionPerformed

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        JOptionPane.showMessageDialog(this, "Made in 2015\nDeveloped By Eagle Bytes:\n\nDaniel Church\nDieter Grosswiler\nSeth Probert\nTrent Halstad\nNathan Starkel\nRandall Deffert", "Credits", 0, new ImageIcon("res/eagle.png"));
    }//GEN-LAST:event_jMenuItem1ActionPerformed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        System.exit(0);
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels())
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Shell.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Shell.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Shell.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Shell.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Shell().setVisible(true);
            }
        });
    }

    private class Panel extends JPanel {

        private int[] data;
        @Deprecated//TODO:
        private int[] selectedIndices = new int[]{-1, -1};
        private Color[] colors;

        private BufferedImage img;
        private Graphics2D bg;

        private int mouseX, mouseY;
        
        @Deprecated//TODO:
        private int timerSpeed = 10;
        
        private int temp = 0;
        private int tempIndex = 0;
        
        private final Color startColor = Color.cyan;
        private final Color endColor = Color.blue;

        public Panel() {
            addMouseMotionListener(new MouseAdapter() {
                @Override
                public void mouseMoved(MouseEvent me) {
                    mouseX = me.getX();
                    mouseY = me.getY();
                    repaint();
                }
            });
            //TODO: Remove?
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent me) {
                    int index = getDataIndexFromCoord(new Vector2f(me.getX(), me.getY()));
//                    if(index != -1)
                    selectDataIndex(index);
                    if (me.getButton() == MouseEvent.BUTTON3)
                        //TODO: Slow down
                        //Note: The time here MUST match the time on the other timer.
                        new javax.swing.Timer(timerSpeed, new ActionListener() {
                            private int index = 0;

                            @Override
                            public void actionPerformed(ActionEvent ae) {
                                selectDataIndex(index++);
                                selectDataIndex(data.length - index);
                                if (index > data.length - 1)
                                    ((Timer) ae.getSource()).stop();
                            }
                        }).start();
                }
            });
        }

        public int sortSpeed = 0;
        private Timer sortTimer;
        
        /**
         * Instantly sorts the array with the selected sort method.
         */
        public void sort() {
            ((Sort)(sortArray[sortTypes.getSelectedIndex()])).sort(data);
            setShadeSequentially(startColor, endColor);
            repaint();
        }
        
        /**
         * Sorts the array as an animation, with the selected sort method.
         */
        public void animateSort(){
            ((Sort) (sortArray[sortTypes.getSelectedIndex()])).init(data);
            if (sortTimer != null)
                sortTimer.stop();
            sortTimer = new Timer(sortSpeed, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    sortStep();
                }
            });
            sortTimer.start();
        }
        
        /**
         * Sorts one step of the selected sort method.
         */
        public void sortStep() {
            ((Sort) sortArray[sortTypes.getSelectedIndex()]).sortStep(data);
            temp = ((Sort) sortArray[sortTypes.getSelectedIndex()]).getTemp();
            tempIndex = ((Sort) sortArray[sortTypes.getSelectedIndex()]).getTempIndex();
            selectDataIndex(tempIndex);
            selectDataIndex(((Sort) sortArray[sortTypes.getSelectedIndex()]).getTempIndex2());
            setShadeSequentially(startColor, endColor);
            repaint();
        }

        /**
         * Swaps the two indices in the array, ONLY IN THE DATA.
         *
         * @param index The first index to swap. Use -1 to take from temp.
         * @param destination The second index to swap. Use -1 to put in temp.
         */
        public void swapData(int index, int destination) {
            int temp = data[index];
            data[index] = data[destination];
            data[destination] = temp;
            //TODO: Not necessary if color based on length.
            Color tempColor = colors[index];
            colors[index] = colors[destination];
            colors[destination] = tempColor;
        }
        
        /**
         * Graphically and literally swaps two values in an array.
         * @param index First value to swap.
         * @param destination  Second value to swap.
         */
        @Deprecated
        public void swap(final int index, final int destination) {
            new Timer(20, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    Vector2f offset = dataOffset.get(index);
                    Vector2f offset2 = dataOffset.get(destination);
                    if (getCoordsFromDataIndex(index).x + offset.x > getCoordsFromDataIndex(destination).x - offset2.x) {
                        offset.x -= 5f;
                        offset2.x += 5f;
                        if (getCoordsFromDataIndex(index).x + offset.x < getCoordsFromDataIndex(destination).x - offset2.x) {
                            swapData(index, destination);
                            dataOffset.get(index).x = 0;
                            dataOffset.get(destination).x = 0;
                            ((Timer) ae.getSource()).stop();
                        }
                    } else {
                        offset.x += 5f;
                        offset2.x -= 5f;
                        if (getCoordsFromDataIndex(index).x - offset.x > getCoordsFromDataIndex(destination).x + offset2.x) {
                            swapData(index, destination);
                            dataOffset.get(index).x = 0;
                            dataOffset.get(destination).x = 0;
                            ((Timer) ae.getSource()).stop();
                        }
                    }
                    repaint();
                }
            }).start();
        }

        private javax.swing.Timer animationTimer;
        
        /**
         * Called when the panel is created, sets up essential assets for the graphics engine.
         */
        public void preInit() {
            img = new BufferedImage(800, 700, BufferedImage.TYPE_INT_ARGB);
            bg = (Graphics2D) img.getGraphics();
            bg.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
            bg.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        }
        
        //Used for the commented out code below.
        //private float speed = 3f;
        
        /**
         * Called each time data is generated, sets it up to be displayed.
         */
        public void init() {
            temp = 0;
            dataOffset.clear();
            for (int i : data)
                dataOffset.add(new Vector2f(0, 0));
            setShadeSequentially(startColor, endColor);
            //Animates the vertical changes of a piece of data being selected.
            /*
            if (animationTimer != null)
                animationTimer.stop();
            animationTimer = new javax.swing.Timer(timerSpeed, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    for (int i = 0; i < data.length; i++)
                        if (i == selectedIndices[0] || i == selectedIndices[1]) {
                            //TODO: Slow down
                            speed = 100f;
                            Vector2f offset = dataOffset.get(i);
                            if (offset.y > -200)
                                dataOffset.get(i).y = offset.y - speed;
                            repaint();
                        } else {
                            //TODO: Remove hard-coded descent speed
                            speed = 10f;
                            Vector2f offset = dataOffset.get(i);
                            if (offset.y < 0)
                                dataOffset.get(i).y = offset.y + speed;
                            repaint();
                        }
                }
            });
            animationTimer.start();
            */
            if (sortTimer != null)
                sortTimer.stop();
            ((Sort) (sortArray[sortTypes.getSelectedIndex()])).init(data);
            repaint();
        }

        /**
         * Sets the color of the data as a linear gradient from left(black) to right(white).
         */
        @Deprecated
        private void setBlackAndWhite() {
            colors = new Color[data.length];
            for (int i = 0; i < data.length; i++) {
                float colorValue = MathUtils.clamp((float) i / colors.length, 0.2f, 1);
                colors[i] = new Color(colorValue, colorValue, colorValue);
            }
        }

        /**
         * Sets the color of the data somehow, I don't remember anymore. Looks like its set randomly. Yeah.... definitely randomly.
         */
        @Deprecated
        private void setColor() {
            colors = new Color[data.length];
            for (int i = 0; i < data.length; i++)
                colors[i] = new Color((float) Math.random(), (float) Math.random(), (float) Math.random());
        }
        
        /**
         * Sets the color poorly based on the actual data value. Almost what we wanted.
         */
        @Deprecated
        private void setColorSequentially() {
            colors = new Color[data.length];
            int max = MathUtils.getMax(data);
            int min = MathUtils.getMin(data);
            for (int i = 0; i < data.length; i++) {
                int color = (int) MathUtils.scale((data[i] - min) / (float) (max - min), 0f, 1f, 0x000000, 0xFFFFFF);
                colors[i] = new Color((int) ((color & 0xFF0000) / (float) 0xFF0000 * 255f), (int) ((color & 0x00FF00) / (float) 0x00FF00 * 255f), (int) ((color & 0x0000FF) / (float) 0x0000FF * 255f));
            }
        }

        /**
         * Sets the color as a gradient between the start and end colors, based on the data value.
         * @param start Start Color.
         * @param end End Color.
         */
        private void setShadeSequentially(Color start, Color end) {
            colors = new Color[data.length];
            for (int i = 0; i < data.length; i++) {
                int max = MathUtils.getMax(data);
                int min = MathUtils.getMin(data);
                float color = (float) (data[i] - min) / (max - min);
                
                int red = (int)interpolate(color, start.getRed(), end.getRed());
                int green = (int)interpolate(color, start.getGreen(), end.getGreen());
                int blue = (int)interpolate(color, start.getBlue(), end.getBlue());
                colors[i] = new Color(red, green, blue);
            }
        }
        
        private float interpolate(float ratio, float value1, float value2){
            return Math.abs((ratio * value1) + ((1 - ratio) * value2));
        }
        
        @Deprecated
        private List<Vector2f> dataOffset = new ArrayList<Vector2f>();
        @Deprecated
        private boolean firstSelection = false;

        public void selectDataIndex(int index) {
            if (firstSelection = !firstSelection)
                this.selectedIndices[0] = index;
            else
                this.selectedIndices[1] = index;

//            if(selectedIndices[1] != -1){
//                swap(selectedIndices[0], selectedIndices[1]);
//                for(int i = 0; i < selectedIndices.length; i++)
//                    selectedIndices[i] = -1;
//            }
            repaint();
        }

        private int getDataIndexFromCoord(Vector2f coordinate) {
            for (int i = 0; i < data.length; i++) {
                int xPos = (int) (i * 800f / (9 / 8f * data.length)) + (int) dataOffset.get(i).x;
                int yPos = 680 - data[i] + (int) dataOffset.get(i).y;
                int width = (int) (800f / (9 / 8f * data.length));
                int height = data[i];
                if (coordinate.x > xPos && coordinate.x < xPos + width && coordinate.y > yPos && coordinate.y < yPos + height)
                    return i;
            }
            return -1;
        }

        private Vector2f getCoordsFromDataIndex(int index) {
            return new Vector2f((int) (index * 800f / (9 / 8f * data.length)) + (int) dataOffset.get(index).x, 680 - data[index] + (int) dataOffset.get(index).y);
        }

        @Override
        public void paint(Graphics gfx) {
            //Graphics Initialization
            Graphics2D g = (Graphics2D) gfx;
            g.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
            g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
            g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            //Draw Elements onto a backbuffer
            bg.setColor(Color.black);
            bg.fillRect(0, 0, 800, 700);
            bg.setColor(Color.DARK_GRAY);
            bg.fillRect(710, 0, 800, 700);
            if (data != null && colors != null) {
                for (int i = 0; i < data.length; i++) {
                    int xPos = (int) (i * 799f / (9f / 8f * data.length)) + (int) dataOffset.get(i).x;
                    int yPos = 700 - data[i] + (int) dataOffset.get(i).y;
                    int width = (int) (800f / (9 / 8f * data.length));
                    int height = data[i];
                    if (i != selectedIndices[0] && i != selectedIndices[1]) {
                        bg.setColor(colors[i]);
                        bg.fill3DRect(xPos, yPos + (int) dataOffset.get(i).y, width, height, true);
                    }
                }
                for (int i = 0; i < data.length; i++) {
                    int xPos = (int) (i * 799f / (9f / 8f * data.length)) + (int) dataOffset.get(i).x;
                    int yPos = 700 - data[i] + (int) dataOffset.get(i).y;
                    int width = (int) (800f / (9 / 8f * data.length));
                    int height = data[i];
                    if (i == selectedIndices[0]) {
                        //Beam of light behind the data
                        bg.setPaint(new GradientPaint(0, 0, new Color(255, 255, 100, 150), 0, 680, new Color(255, 255, 0, 100)));
                        bg.fillPolygon(new int[]{
                            xPos + (int) dataOffset.get(i).x,
                            (int) (xPos + (int) dataOffset.get(i).x + width),
                            (int) (xPos + (int) dataOffset.get(i).x + 3 / 2f * width),
                            (int) (xPos + (int) dataOffset.get(i).x - 1 / 2f * width)
                        }, new int[]{0, 0, 680, 680}, 4);

                        //Data
                        bg.setColor(colors[i]);
                        bg.fill3DRect(xPos, yPos, width, height, true);

                        //Beam of light infront of the data
                        bg.setPaint(new GradientPaint(0, 0, new Color(255, 255, 100, 100), 0, 680, new Color(255, 255, 0, 25)));
                        bg.fillPolygon(new int[]{
                            xPos + (int) dataOffset.get(i).x,
                            (int) (xPos + (int) dataOffset.get(i).x + width),
                            (int) (xPos + (int) dataOffset.get(i).x + 3 / 2f * width),
                            (int) (xPos + (int) dataOffset.get(i).x - 1 / 2f * width)
                        }, new int[]{0, 0, 680, 680}, 4);
                    } else if (i == selectedIndices[1]) {
                        //Beam of light behind the data
                        bg.setPaint(new GradientPaint(0, 0, new Color(255, 0, 255, 150), 0, 680, new Color(0, 0, 255, 100)));
                        bg.fillPolygon(new int[]{
                            xPos + (int) dataOffset.get(i).x,
                            (int) (xPos + (int) dataOffset.get(i).x + width),
                            (int) (xPos + (int) dataOffset.get(i).x + 3 / 2f * width),
                            (int) (xPos + (int) dataOffset.get(i).x - 1 / 2f * width)
                        }, new int[]{0, 0, 680, 680}, 4);

                        //Data
                        bg.setColor(colors[i]);
                        bg.fill3DRect(xPos, yPos, width, height, true);

                        //Beam of light infront of the data
                        bg.setPaint(new GradientPaint(0, 0, new Color(255, 0, 255, 100), 0, 680, new Color(0, 0, 255, 25)));
                        bg.fillPolygon(new int[]{
                            xPos + (int) dataOffset.get(i).x,
                            (int) (xPos + (int) dataOffset.get(i).x + width),
                            (int) (xPos + (int) dataOffset.get(i).x + 3 / 2f * width),
                            (int) (xPos + (int) dataOffset.get(i).x - 1 / 2f * width)
                        }, new int[]{0, 0, 680, 680}, 4);
                    }
                }
            }
            //Draw the backbuffer to the screen
            g.drawImage(img, 0, 0, this);
            //Draw the y-coordinate text
            g.setColor(Color.yellow);
            for (int i = 0; i <= 6; i++)
                g.drawString("" + (100 * i), 20, 700 - (i * 100));
            g.drawString("Temp", 740, 20);
            g.drawLine(710, 30, 800, 30);
            
            //Draw temp element
            if(tempIndex < colors.length-1){
                g.setColor(colors[tempIndex]);
                g.fill3DRect(735, 700-temp, 40, temp, true);
            }
            //Draw the point intersection lines
            g.setColor(Color.pink);
            g.drawLine(0, mouseY, 800, mouseY);
            g.drawLine(mouseX, 0, mouseX, 700);
        }
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton animateSortButton;
    private javax.swing.JLabel dataGenLabel;
    private javax.swing.JPanel dataGenPanel;
    private javax.swing.JTextField elementsField;
    private javax.swing.JSlider elementsSlider;
    private javax.swing.JButton generateButton;
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JSlider jSlider1;
    private javax.swing.JPanel maxSliderPanel;
    private javax.swing.JTextField maxTextField;
    private javax.swing.JLabel maxValueLabel;
    private javax.swing.JSlider maxValueSlider;
    private javax.swing.JPanel minMaxPanel;
    private javax.swing.JTextField minTextField;
    private javax.swing.JLabel minValueLabel;
    private javax.swing.JPanel minValuePanel;
    private javax.swing.JSlider minValueSlider;
    private javax.swing.JPanel renderPanel;
    private javax.swing.JButton sequentialButton;
    private javax.swing.JButton sortButton;
    private javax.swing.JComboBox sortTypes;
    // End of variables declaration//GEN-END:variables
}
