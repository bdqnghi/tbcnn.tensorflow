import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class BubbleSort extends JPanel {

    private static final long serialVersionUID = 1L;
    int[] x = new int[100];
    int[] extraX = new int[100];
    int y = 120;
    int a = 70;
    int b = 80;
    int speedH = 40;
    int speedL = 700;
    int newPan = 0;
    int extraOval;
    int colorFlag = 100;
    int colorFlag2 = 100;
    int arrSize;
    @SuppressWarnings({ "unchecked", "rawtypes" })
	ArrayList<String> array = new ArrayList();
    String[] text;
    String[] initialText = new String[100];
    JTextField inputText;
    String inputData;
    int[] inte;
    BubbleSort.MyDrawPanel sortPanel;
    JPanel textPanel = new JPanel();
    JButton goSort;
    JFrame bblSrtFrame;

    public BubbleSort() {

        this.inputText = new JTextField();

        this.bblSrtFrame = new JFrame("AlgoVisualizer : Bubble Sort   ");
        this.bblSrtFrame.setDefaultCloseOperation(3);

        this.sortPanel = new BubbleSort.MyDrawPanel();

        this.bblSrtFrame.getContentPane().add(this.sortPanel);
        this.bblSrtFrame.setSize(1380, 730);
        this.bblSrtFrame.setResizable(false);

        this.inte = new int['?'];

        JButton bckToFrst = new JButton();
        bckToFrst.setBounds(1050, 360, 200, 50);
        bckToFrst.setBackground(Color.magenta);
        bckToFrst.setForeground(Color.white);

        bckToFrst.setText("Back to Menu");
        bckToFrst.setFont(new Font("Gill Sans Ultra", 2, 18));
        this.sortPanel.setLayout(null);
        this.sortPanel.add(bckToFrst);

        bckToFrst.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {

                BubbleSort.this.bblSrtFrame.dispose();

                try {
					new FirstFrame();
				} catch (IOException e) {
					e.printStackTrace();
				}
            }
        });

        JButton bblNewInput = new JButton();
        bblNewInput.setBounds(1100, 260, 200, 50);
        bblNewInput.setBackground(Color.yellow);
        bblNewInput.setForeground(Color.black);

        bblNewInput.setText("Input new Data");
        bblNewInput.setFont(new Font("Gill Sans Ultra", 1, 18));
        this.sortPanel.setLayout(null);
        this.sortPanel.add(bblNewInput);

        bblNewInput.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {

                BubbleSort.this.bblSrtFrame.dispose();
                new BubbleSort();
            }
        });

        JButton bblreplay = new JButton();
        bblreplay.setBounds(1150, 160, 200, 50);
        bblreplay.setBackground(Color.pink);
        bblreplay.setForeground(Color.black);

        bblreplay.setText("Replay");
        bblreplay.setFont(new Font("Gill Sans Ultra", 1, 18));
        this.sortPanel.setLayout(null);
        this.sortPanel.add(bblreplay);

        bblreplay.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {

                BubbleSort.this.newPan = 1;
                BubbleSort.this.bblSrtFrame.getContentPane().remove(BubbleSort.this.sortPanel);
                BubbleSort.this.bblSrtFrame.getContentPane().add(BubbleSort.this.sortPanel);
                BubbleSort.this.bblSrtFrame.repaint();
                BubbleSort.this.bblSrtFrame.validate();

                BubbleSort.this.y = 120;
                BubbleSort.this.a = 70;
                BubbleSort.this.b = 80;
                BubbleSort.this.colorFlag = 100;
                BubbleSort.this.colorFlag2 = 100;

                for (int i = 0; i < BubbleSort.this.text.length + 5; i++) {

                    BubbleSort.this.x[i] = (400 + i * 100);
                    BubbleSort.this.extraX[i] = BubbleSort.this.x[i];
                }

                for (int i = 0; i < BubbleSort.this.text.length; i++) {

                    BubbleSort.this.text[i] = BubbleSort.this.initialText[i];
                }
                BubbleSort.this.newPan = 0;
                BubbleSort.this.startSort();
            }
        });

        JLabel label = new JLabel();
        
        label.setText("        Input Integers [max 6] (use only one SPACE to separate)");
        label.setFont(new Font("Gill Sans Ultra", 1, 24));
        
        this.textPanel.add(label);
        label.setBounds(200, 150, 1000, 70);

        this.inputText.setBounds(200, 200, 700, 60);
        this.textPanel.setLayout(null);
        this.textPanel.add(this.inputText);

        this.textPanel.setBackground(Color.CYAN);

        JButton bckFrst = new JButton();
        bckFrst.setBounds(500, 300, 200, 50);
        bckFrst.setBackground(Color.magenta);
        bckFrst.setForeground(Color.white);

        bckFrst.setText("Back to Menu");
        bckFrst.setFont(new Font("Gill Sans Ultra", 10, 18));
        this.sortPanel.setLayout(null);
        this.textPanel.add(bckFrst);

        bckFrst.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {

                BubbleSort.this.bblSrtFrame.dispose();

                try {
					new FirstFrame();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        });

        this.goSort = new JButton();
        this.goSort.setLocation(920, 200);
        this.goSort.setBackground(Color.RED);
        this.goSort.setForeground(Color.white);
        this.goSort.setSize(100, 60);
        this.goSort.setText("Sort");
        this.goSort.setFont(new Font("Gill Sans Ultra Bold", 2, 18));
        this.goSort.setLayout(null);

        this.goSort.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {

                BubbleSort.this.inputData = BubbleSort.this.inputText.getText();
                BubbleSort.this.text = BubbleSort.this.inputData.split(" ");
                
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        BubbleSort.this.bblSrtFrame.getContentPane().remove(BubbleSort.this.textPanel);
                        BubbleSort.this.bblSrtFrame.getContentPane().add(BubbleSort.this.sortPanel);
                        BubbleSort.this.bblSrtFrame.repaint();
                        BubbleSort.this.bblSrtFrame.validate();
                        for (int i = 0; i < BubbleSort.this.text.length; i++) {
                            BubbleSort.this.x[i] = (400 + i * 100);
                            BubbleSort.this.extraX[i] = BubbleSort.this.x[i];
                        }
                        for (int i = 0; i < BubbleSort.this.text.length; i++) {
                            BubbleSort.this.initialText[i] = BubbleSort.this.text[i];
                        }
                        if ((BubbleSort.this.text.length <= 6) && (BubbleSort.this.text.length != 0)) {
                            BubbleSort.this.startSort();
                        } else {
                            BubbleSort.this.bblSrtFrame.dispose();
                            new BubbleSort();
                        }
                    }
                });
            }
        });
        this.textPanel.add(this.goSort);
        this.bblSrtFrame.add(this.textPanel);

        this.inputText.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                BubbleSort.this.inputData = BubbleSort.this.inputText.getText();
                BubbleSort.this.text = BubbleSort.this.inputData.split(" ");
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        BubbleSort.this.bblSrtFrame.getContentPane().remove(BubbleSort.this.textPanel);
                        BubbleSort.this.bblSrtFrame.getContentPane().add(BubbleSort.this.sortPanel);
                        BubbleSort.this.bblSrtFrame.repaint();
                        BubbleSort.this.bblSrtFrame.validate();
                        for (int i = 0; i < BubbleSort.this.text.length + 5; i++) {
                            BubbleSort.this.x[i] = (400 + i * 100);
                            BubbleSort.this.extraX[i] = BubbleSort.this.x[i];
                        }
                        for (int i = 0; i < BubbleSort.this.text.length; i++) {
                            BubbleSort.this.initialText[i] = BubbleSort.this.text[i];
                        }
                        if ((BubbleSort.this.text.length <= 6) && (BubbleSort.this.text.length != 0)) {
                            BubbleSort.this.startSort();
                        } else {
                            BubbleSort.this.bblSrtFrame.dispose();
                            new BubbleSort();
                        }
                    }
                });
            }
        });
        repaint();
        revalidate();
        this.bblSrtFrame.repaint();
        this.bblSrtFrame.setVisible(true);
    }

    private void startSort() {
        this.extraOval = this.text.length;
        try {
            Thread.sleep(this.speedH);
        } catch (Exception localException) {}
        for (int j = 0; j < this.text.length; j++) {
            this.inte[j] = Integer.parseInt(this.text[j]);
        }
        for (int i = 0; i < this.text.length; i++) {
            this.array.add(this.text[i]);
        }
        this.arrSize = this.text.length;
        Thread thread = new Thread(new Runnable() {
            public void run() {
                int loopSize = BubbleSort.this.text.length - 1;
                while (BubbleSort.this.arrSize > 1) {
                    for (int i = 0; i < loopSize; i++) {
                        if (BubbleSort.this.newPan == 1) {
                            BubbleSort.this.newPan = 0;
                            return;
                        }
                        if (BubbleSort.this.inte[i] > BubbleSort.this.inte[(i + 1)]) {
                            int temp = BubbleSort.this.inte[i];
                            BubbleSort.this.inte[i] = BubbleSort.this.inte[(i + 1)];
                            BubbleSort.this.inte[(i + 1)] = temp;
                            for (int k = 1; k <= 100; k++) {
                                BubbleSort.this.x[i] += 1;
                                BubbleSort.this.x[(i + 1)] -= 1;
                                BubbleSort.this.colorFlag = i;
                                BubbleSort.this.colorFlag2 = (i + 1);

                                BubbleSort.this.sortPanel.repaint();
                                try {
                                    Thread.sleep(BubbleSort.this.speedH);
                                } catch (Exception localException) {}
                            }
                            int temPix = BubbleSort.this.x[i];
                            BubbleSort.this.x[i] = BubbleSort.this.x[(i + 1)];
                            BubbleSort.this.x[(i + 1)] = temPix;

                            String temText = BubbleSort.this.text[i];
                            BubbleSort.this.text[i] = BubbleSort.this.text[(i + 1)];
                            BubbleSort.this.text[(i + 1)] = temText;
                        } else {
                            BubbleSort.this.colorFlag = i;
                            BubbleSort.this.colorFlag2 = (i + 1);

                            BubbleSort.this.sortPanel.repaint();
                            try {
                                Thread.sleep(BubbleSort.this.speedL);
                            } catch (Exception localException1) {}
                            BubbleSort.this.colorFlag = 100;
                            BubbleSort.this.colorFlag2 = 100;
                        }
                        try {
                            Thread.sleep(BubbleSort.this.speedH);
                        } catch (Exception localException2) {}
                    }
                    for (int i = 0; i < BubbleSort.this.text.length; i++) {
                        BubbleSort.this.array.add(BubbleSort.this.text[i]);
                    }
                    BubbleSort.this.y += 90;

                    BubbleSort.this.extraOval += BubbleSort.this.text.length;
                    BubbleSort.this.colorFlag = 100;
                    BubbleSort.this.colorFlag2 = 100;
                    System.out.println(BubbleSort.this.text.length);
                    BubbleSort.this.sortPanel.repaint();

                    loopSize--;
                    BubbleSort.this.arrSize -= 1;
                }
            }
        });
        thread.start();
    }

    public class MyDrawPanel
            extends JPanel {
        private static final long serialVersionUID = 1L;

        public MyDrawPanel() {}

        public void paintComponent(Graphics g) {
            Graphics2D g2d = (Graphics2D)g;

            g2d.setColor(Color.CYAN);
            g2d.fillRect(0, 0, getWidth(), getHeight());

            int extraY = 30;
            for (int i = 0; i < BubbleSort.this.extraOval; i++) {
                g2d.setColor(Color.orange);
                if ((i % BubbleSort.this.text.length == 0) && (i != 0)) {
                    extraY += 90;
                }
                g2d.fillOval(BubbleSort.this.extraX[(i % BubbleSort.this.text.length)], extraY, BubbleSort.this.a, BubbleSort.this.b);

                g2d.setFont(new Font("Calibri", 0, 36));
                FontMetrics font = g2d.getFontMetrics();
                double textWidth = font.getStringBounds((String)BubbleSort.this.array.get(i), g2d)
                                   .getWidth();

                g2d.setColor(Color.black);
                g2d.drawString(
                    (String)BubbleSort.this.array.get(i),
                    (int)((2 * BubbleSort.this.extraX[(i % BubbleSort.this.text.length)] + BubbleSort.this.a) / 2 - textWidth / 2.0D),
                    (2 * extraY + BubbleSort.this.b) / 2 + font.getMaxAscent() / 2);
            }
            for (int i = 0; i < BubbleSort.this.text.length; i++) {
                if ((BubbleSort.this.colorFlag == i) || (BubbleSort.this.colorFlag2 == i)) {
                    g2d.setColor(Color.green);
                } else {
                    g2d.setColor(Color.red);
                }
                if (BubbleSort.this.arrSize > 0) {
                    g2d.fillOval(BubbleSort.this.x[i], BubbleSort.this.y, BubbleSort.this.a, BubbleSort.this.b);

                    g2d.setFont(new Font("Calibri", 0,
                                         36));
                    FontMetrics font = g2d.getFontMetrics();
                    double textWidth = font.getStringBounds(BubbleSort.this.text[i], g2d)
                                       .getWidth();

                    g2d.setColor(Color.WHITE);
                    g2d.drawString(BubbleSort.this.text[i],
                                   (int)((2 * BubbleSort.this.x[i] + BubbleSort.this.a) / 2 - textWidth / 2.0D),
                                   (2 * BubbleSort.this.y + BubbleSort.this.b) / 2 + font.getMaxAscent() / 2);
                }
            }
        }
    }
}
