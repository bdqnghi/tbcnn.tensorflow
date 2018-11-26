package c_thirdexp.hanoi;

/*
 *
 * @程序名: Hanoi.java
 * @编程人: 陈若楠 (学号: 1512480434)
 * @编程日期: 2017-10-21
 * @修改日期: 2017-10-22
 *
 */

import javax.swing.*;
import java.awt.*;

public class Hanoi extends JFrame implements Runnable {

    private Thread thread = new Thread(this);

    Hanoi() {
        init();
    }

    private void init() {

        // 1 给Hanoi数组赋初值
        for (int i = 0; i < 23; i++) {
            Var.towerA[i] = i;
        }
        for (int i = 0; i < 23; i++) {
            Var.towerB[i] = i;
        }
        for (int i = 0; i < 23; i++) {
            Var.towerC[i] = i;
        }

        // 2 输入Hanoi数量
        int x;
        try {
            x = Integer.valueOf(JOptionPane.showInputDialog("请输入汉诺塔数量(<=20)"));
        } catch (Exception e) {
            return;
        }


        while (x < 0 || x > 21) {
            JOptionPane.showMessageDialog(null, "输入的值不合理，请重新输入");
            x = Integer.valueOf(JOptionPane.showInputDialog("请输入汉诺塔数量(<=20)"));
        }
        Var.numOfTowerA = x - 1;
        Var.numOfTower = x;

        // 3 生成布局
        // 3.1 按钮
        JButton buttonStart = new JButton("start");
        JButton buttonStop = new JButton("stop");
        JButton buttonContinue = new JButton("continue");
        JButton buttonNext = new JButton("next");
        JButton buttonSpeedUp = new JButton("speed up");
        JButton buttonSlowDown = new JButton("slow down");

        // 3.2 按钮事件
        buttonStart.addActionListener(e -> {
            if (Var.startFlag) {
                JOptionPane.showMessageDialog(null, "already started, please click continue");
            } else {
                thread.start();
                Var.startFlag = true;
            }
        });

        buttonStop.addActionListener(e -> {
            if (Var.stop1) {
                JOptionPane.showMessageDialog(null, "already stopped");
            } else {
                hanoiChangeVar();
            }
        });

        buttonContinue.addActionListener(e -> {
            if (!Var.stop1) {
                JOptionPane.showMessageDialog(null, "already keep on");
            } else {
                hanoiContinue();
            }
        });

        buttonNext.addActionListener(e -> {
            if (!Var.startFlag) {
                Var.startFlag = true;
                hanoiChangeVar();
                thread.start();
            } else {
                hanoiNext();
            }
        });

        buttonSpeedUp.addActionListener(e -> {
            Var.sTime -= 1;
            if (Var.sTime < 1) {
                Var.sTime = 1;
                JOptionPane.showMessageDialog(null, "already at highest speed");
            }
        });

        buttonSlowDown.addActionListener(e -> Var.sTime += 1);

        // 3.3 新建JPanel并将Button应用到JPanel中
        JPanel jPanel = new JPanel();
        jPanel.add(buttonStart);
        jPanel.add(buttonStop);
        jPanel.add(buttonContinue);
        jPanel.add(buttonNext);
        jPanel.add(buttonSpeedUp);
        jPanel.add(buttonSlowDown);

        // 3.4 添加JPanel和Hanoi(本身就是Panel)到this(frame)
        this.getContentPane().add(jPanel, BorderLayout.SOUTH);
        this.getContentPane().add(new Paints());

        // 3.5 frame参数设置
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setSize(1150, 500);
        this.setTitle("Hanoi Animation");
        this.setVisible(true);
        this.setResizable(false);

    }

    private void moves(int start, int end) {
        // use to update frame
        switch (start) {
            case 1:
                Var.rectStartMid = 225;
                Var.tower = Var.towerA;
                // assign the quantity of hanoi where hanoi moves from
                Var.moveStartT = Var.numOfTowerA;
                Var.numOfTowerA -= 1;
                break;
            case 2:
                Var.rectStartMid = 575;
                Var.tower = Var.towerB;
                Var.moveStartT = Var.numOfTowerB;
                Var.numOfTowerB -= 1;
                break;
            case 3:
                Var.rectStartMid = 925;
                Var.tower = Var.towerC;
                Var.moveStartT = Var.numOfTowerC;
                Var.numOfTowerC -= 1;
                break;
        }
        switch (end) {
            case 1:
                Var.rectEndMid = 225;
                // assign the quantity of hanoi where hanoi moves to
                Var.moveEndT = Var.numOfTowerA;
                break;
            case 2:
                Var.rectEndMid = 575;
                Var.moveEndT = Var.numOfTowerB;
                break;
            case 3:
                Var.rectEndMid = 925;
                Var.moveEndT = Var.numOfTowerC;
                break;
        }
        if (start >= end) {
            Var.direction = 1;
        } else {
            Var.direction = 0;
        }
        // calculate the coordinate of the rectangle which is going to move
        Var.rectX1 = Var.rectStartMid - (24 - Var.tower[Var.moveStartT]) * 5;
        Var.rectX2 = Var.rectStartMid + (24 - Var.tower[Var.moveStartT]) * 5;
        Var.rectY = 290 - Var.moveStartT * 10;

        // move upwards
        while (Var.rectY >= 40) {
            Var.rectY -= 10;
            repaint();
            try {
                Thread.sleep(Var.sTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // left or right shift
        while (Var.rectStartMid != Var.rectEndMid) {
            // left shift
            if (Var.direction == 1) {
                Var.rectStartMid -= 10;
                Var.rectX1 = Var.rectStartMid - (24 - Var.tower[Var.moveStartT]) * 5;
                Var.rectX2 = Var.rectStartMid + (24 - Var.tower[Var.moveStartT]) * 5;
                repaint();
                try {
                    Thread.sleep(Var.sTime);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else { // right shift
                Var.rectStartMid += 10;
                Var.rectX1 = Var.rectStartMid - (24 - Var.tower[Var.moveStartT]) * 5;
                Var.rectX2 = Var.rectStartMid + (24 - Var.tower[Var.moveStartT]) * 5;
                repaint();
                try {
                    Thread.sleep(Var.sTime);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        // move downwards
        while (Var.rectY <= (270 - (Var.moveEndT) * 10)) {
            Var.rectY += 10;
            repaint();
            try {
                Thread.sleep(Var.sTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // change the layout of the destination hanoi
        switch (end) {
            case 1:
                Var.numOfTowerA += 1;
                Var.towerA[Var.numOfTowerA] = Var.tower[Var.moveStartT];
                repaint();
                break;
            case 2:
                Var.numOfTowerB += 1;
                Var.towerB[Var.numOfTowerB] = Var.tower[Var.moveStartT];
                repaint();
                break;
            case 3:
                Var.numOfTowerC += 1;
                Var.towerC[Var.numOfTowerC] = Var.tower[Var.moveStartT];
                repaint();
                break;
        }
    }

    private void hanoi(int n, int towerA, int towerB, int towerC) throws InterruptedException {
        // move hanoi from towerA to towerC, towerB is used as way station
        if (n > 0) {
            hanoi(n - 1, towerA, towerC, towerB);
            if (Var.stop1) {
                hanoiStop();
            }
            moves(towerA, towerC);
            hanoi(n - 1, towerB, towerA, towerC);
        }
    }

    private void hanoiChangeVar() {
        Var.stop1 = true;
    }

    private synchronized void hanoiContinue() {
        Var.stop1 = false;
        notify();
    }

    private synchronized void hanoiNext() {
        notify();
    }

    private synchronized void hanoiStop() throws InterruptedException {
        wait();
    }

    public void run() {
        try {
            hanoi(Var.numOfTower, 1, 2, 3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}