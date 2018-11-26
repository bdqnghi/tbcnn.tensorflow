package dialog.aboutdialog;

import javax.swing.JDialog;
import javax.swing.JTabbedPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Container;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.text.StyledDocument;
import javax.swing.text.BadLocationException;
import javax.swing.text.MutableAttributeSet;
import java.awt.Font;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.text.StyleConstants;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JSplitPane;
import panel.main.CGameContainer;
import javax.swing.JLabel;
import java.awt.Graphics;
import java.io.File;

/**
 * @author Daniel Oikarainen
 */

public class CAboutDialog extends JDialog
{
    //For running class in isolation
    public static void main(String[] args)
    {        
    }
    
    public CAboutDialog(JFrame pParent, CGameContainer pGameContainer, JCheckBoxMenuItem pPauseMenuItem)
    {
        super(pParent, "About Tetris and me...", true);
        mGameContainer = pGameContainer;
        mPauseMenuItem = pPauseMenuItem;
        Container contentPane = getContentPane();
        
        mTabbedPane = new JTabbedPane();
        mTabbedPane.addTab("Tetris", new CPanelGame());
        mTabbedPane.addTab("Personligt Brev", new CPanelMe());
        mTabbedPane.addTab("CV", new CPanelCV());
        
        //Added for SAAB
        mTabbedPane.addTab("SAAB", new CPanelSAAB());
        
        contentPane.add(mTabbedPane, BorderLayout.CENTER);
        
        //Close button makes dialog "invisible"
        JButton closeButton = new JButton("Close");
        closeButton.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent evt)
            {
                if (!mGameContainer.isActiveGame())
                    ;
                else
                {
                    if (mPauseMenuItem.isSelected())
                        ;
                    else
                        mGameContainer.resumeGame();
                }
                setVisible(false);
            }
        });
        
        JPanel panel = new JPanel();
        panel.add(closeButton);
        contentPane.add(panel, BorderLayout.SOUTH);
        
        setResizable(false);        
        setSize(WIDTH, HEIGHT);                        
    } 
    
    //Added for SAAB
    private class CPanelSAAB extends JPanel
    {
        public CPanelSAAB()
        {            
            this.setLayout(new BorderLayout());
            
            JPanel kickOff2018 = new JPanel();             
            kickOff2018.add(new JLabel("V�lkommen till SAAB - Daniel Oikarainen"));
                        
            mTumbUp = new ImageIcon("resoures" + File.separator + "tumme_upp.gif").getImage();            
            mTumbDown = new ImageIcon("resoures" + File.separator + "tumme_ner.gif").getImage();            
            mKoda = new ImageIcon("resoures" + File.separator + "coding.gif").getImage();            
            mSova = new ImageIcon("resoures" + File.separator + "sova.gif").getImage();
           
            JPanel pictures = new JPanel()
            {    
                final int xAlignPicture = 200; 
                protected void paintComponent(Graphics g) 
                {
                    super.paintComponent(g);
                    //Center picture in middle
                    g.drawImage(mTumbUp, ((CAboutDialog.WIDTH / 2) - (mTumbUp.getWidth(null))), 0, this); 
                    g.drawImage(mKoda, (CAboutDialog.WIDTH / 2), 0, this);
                    g.drawImage(mTumbDown, ((CAboutDialog.WIDTH / 2) - (mTumbUp.getWidth(null))), mTumbUp.getWidth(null), this);
                    g.drawImage(mSova, (CAboutDialog.WIDTH / 2) , mTumbUp.getWidth(null), this);
                }
            };                                  
            
            JPanel kickOff2019 = new JPanel();
            kickOff2019.add(new JLabel("Tackar! En �ra och ett privilegium fr�n min sida"));
            
            add(kickOff2018, BorderLayout.NORTH);
            add(pictures, BorderLayout.CENTER);
            add(kickOff2019, BorderLayout.SOUTH);                                    
        }
        private Image mTumbUp;
        private Image mTumbDown;
        private Image mKoda;
        private Image mSova;
    }
    
    //3 Tabbed JPanels inside aboutDialog    
    private class CPanelGame extends JPanel
    {
        public CPanelGame()
        {
            //Avoid that panel gets blue
            setLayout(new GridLayout(1, 1));
                
            String textString = "Tetris is a falling-blocks puzzle video game, released on a vast spectrum of platforms. Alexey Pajitnov originally designed and programmed the game in June 1985, while working for the Dorodnicyn Computing Centre of the Academy of Science of the USSR in Moscow. Pajitnov has cited pentominoes as a source of inspiration for the game. He derived its game from the Greek numerical prefix tetra-, as all of the pieces contain four segments, and tennis, Pajitnov's favorite sport. The game (or one of its many variants) is available for nearly every video game console and computer operating system, as well as on devices such as graphing calculators, mobile phones, portable media playes, and PDAs. It has even been played on the sides of various buildings, with the record holder for the world largest fully functional game of Tetris being an effort by Dutch students in 1995 that lit up all 15 floors of the electrical Engineering department at Delft University of Technology. While versions of Tetris were sold for a range of 1980s home computer platforms, it was the huge successful handheld version for the Game Boy launched in 1989 that established the reputation of the game as one of the most popular ever. In 2007, Tetris came in second place in IGN�n 100 Greatest Video Games of ALL Time.";
            JTextArea textArea = new JTextArea(textString, 8, 40);
            textArea.setCaretPosition(1);
            textArea.setEditable(false);
            textArea.setLineWrap(true);
            textArea.setWrapStyleWord(true);
            
            JScrollPane scrollPane = new JScrollPane(textArea);
            add(scrollPane);
        }
    }
    
    private class CPanelMe extends JPanel
    {
        public CPanelMe()
        {
            //Avoid that panel gets blue
            setLayout(new GridLayout(1,1));
            
            JTextArea textArea = new JTextArea(8,40);
            String newLine = "\n";
            String paragraph1 = "Jag �r i grunden en utbildad ingenj�r inom Data-IT-Elektronik p� GTI som jobbat dom senaste 15 �ren p� Volvo Personvagnar. Dessa �r har gett mig en st�rre �helhetssyn� vad som faktiskt involverar f�r att bygga en hel bil. Mina arbetsuppgifter tangerande allt fr�n bygga d�rr till att skriva felanalyser/fels�kningar. Men efter 15 �r k�ndes det att det var dags att g�ra n�got annat. Jag sa sj�lvmant upp mig och den st�rsta bidragande orsaken var att det fanns inget mer att l�ra sig. Dessutom �r det ju programmering som jag brinner f�r, inte bilar. Det �r d�rf�r jag s�ker denna position med stor entusiasm!!!";
            textArea.append(paragraph1 + newLine + newLine);
            String paragraph2 = "Jag fullkomligt dyrkar alla aspekter av programmering. Det �r d�rf�r jag l�gger ner majoriteten av min fritid med sysslor relaterat till programmering. Det blir v�ldigt mycket l�sning. Tar tid att l�ra sig nya kunskaper. Eftersom det �r en stor zon vad g�llande programmering �r det oftast konplicerat att prioritera �r�tt�. Vill ju bredda mina programmerings-kompetens maximalt men samtidigt ha relevanta kunskaper som efters�ks p� arbetsmarknaden. Min st�rsta akillesh�l var n�tverksbiten. Denna gigantiska zon kunskaps-er�vrades genom att bygga en egengjord router(pfSense) och en NAS(FreeNAS). Har �ven hunnit med att programmera en tetris-klon i java(n�tverksst�d skall implementeras och en portning till c++ �r aktuellt). Vill �ven till�gga att allt detta har gjorts p� min privata fritid. Jag hade G�RNA programmerat p� heltid. L�nen �r inte den bidragande orsaken till mitt intresse f�r denna tj�nst utan det �r min brinnande passion f�r programmering.  Tycker �ven om cykla n�r tillf�llet ges, anv�nder den hellre �n bil n�r s� �r m�jligt. Resten av tiden(det lilla som �terst�r) till�gnas �t familjen. 2 barn, en flicka p� 10 �r och en pojke p� 6 �r samt en f�rst�ende fru. Sj�lv �r jag 38 �r gammal (eller ung :D ).";
            textArea.append(paragraph2 + newLine + newLine);
            String paragraph3 = "Jag �r personen som inte ger upp f�r att hitta buggen som alla missar. Jag svarar p� fr�gan n�r du ska anv�nda en hashmap eller en linked list. Eller ska du rent av till�mpa ett bin�rt s�ktr�d ist�llet? Hur ska man igentligen optimera kod-basen? Finns det verkligen f�rdelar med shell-sort gentemot quick-sort? Eller visar program-profileringen att vi t�nkt fel i program-strukturen(och algorithmen inte �r boven)? Och beh�ver vi verkligen en avancerad red-black tree (som tar 5 g�nger l�ngre tid att implementera) �n en simpel vector till priset av 10% snabbare exekvering-kod igentligen??? Om Ni s�ker en person som har svar p� dessa fr�gor samt kan f�rklara varf�r det �r just s�, d� har Ni kommit r�tt. Garanterat!";
            textArea.append(paragraph3 + newLine + newLine);
            String paragraph4 = "Ge mig en chans att visa vad jag kan genom att erbjuda mig en intervju. Jag hoppas att resultat av den intervjun kan �vertyga Er om att jag kan bli en v�rdefull tillg�ng/medarbetare f�r Er. Tar med mig 2 programmerings projekt (c++ och java) d�r Ni kan granska min kod. Kanske kan Ni s�tta ett nytt High Score i Tetris, man m�ste ju kunna testk�ra programmet  f�r att kvalitetss�kra koden :D. Tack f�r Er tid.";
            textArea.append(paragraph4 + newLine + newLine);
            String nameSign = "Daniel Oikarainen";
            textArea.append(nameSign + newLine + newLine);
                        
            textArea.setCaretPosition(1);
            textArea.setEditable(false);
            textArea.setLineWrap(true);
            textArea.setWrapStyleWord(true);
            
            JScrollPane scrollPane = new JScrollPane(textArea);
            add(scrollPane);
        }
    }
        
    private class CPanelCV extends JPanel
    {
        public CPanelCV()
        {
            //Avoid that panel gets blue
            setLayout(new GridLayout(1,1));
            
            mTextPane = new JTextPane();
            mTextPane.setEditable(false);
            mDoc = mTextPane.getStyledDocument();
            
            DefaultMutableTreeNode topRoot = new DefaultMutableTreeNode("CURRICULUM VITAE (CV)");
            createTree(topRoot);
            mCvTree = new JTree(topRoot);
            
            mCvTree.addTreeSelectionListener(new TreeSelectionListener()
            {
                public void valueChanged(TreeSelectionEvent event)
                {
                    DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode)mCvTree.getLastSelectedPathComponent();
                    
                    if (selectedNode != null)
                    {
                        //Child Node
                        if (selectedNode.isLeaf())
                        {
                            //Clear mDoc every time a new click on node occur
                            try
                            {
                                mDoc.remove(0, mDoc.getLength());
                            }
                            catch (BadLocationException exp)
                            {}
                            
                            foo info = (foo)selectedNode.getUserObject();
                            
                            int numbersOfHeadRow = info.getRowCount();
                            for (int i = 0; i < numbersOfHeadRow; ++i)
                            {
                                //Bold rubrik
                                MutableAttributeSet attrBold = mTextPane.getInputAttributes();
                                Font fontBold = new Font("Serif", Font.BOLD, 16);
                                StyleConstants.setFontFamily(attrBold, fontBold.getFamily());
                                StyleConstants.setFontSize(attrBold, fontBold.getSize());
                                StyleConstants.setItalic(attrBold, (fontBold.getStyle() & Font.ITALIC) != 0);
                                StyleConstants.setBold(attrBold, (fontBold.getStyle() & Font.BOLD) != 0);
                                
                                try
                                {
                                    //Rubrik 1
                                    mDoc.insertString(mDoc.getLength(), info.getRowLine(i).getHeadLine(), attrBold);
                                    mDoc.insertString(mDoc.getLength(), "\n", attrBold);
                                }
                                catch (BadLocationException exp)
                                {}
                                
                                MutableAttributeSet attrPlain = mTextPane.getInputAttributes();
                                Font fontPlain = new Font("Serif", Font.PLAIN, 14);
                                StyleConstants.setFontSize(attrPlain, fontPlain.getSize());
                                StyleConstants.setItalic(attrPlain, (fontPlain.getStyle() & Font.ITALIC) != 0);
                                StyleConstants.setBold(attrPlain, (fontPlain.getStyle() & Font.BOLD) != 0);
                                StyleConstants.setAlignment(attrPlain, StyleConstants.ALIGN_CENTER);
                                
                                try
                                {
                                    //Data
                                    int numbersOfRowInHead = info.getRowLine(i).getLineCount();
                                    for (int j = 0; j < numbersOfRowInHead; ++j)
                                    {
                                        String line = info.getRowLine(i).getContent()[j];
                                        
                                        mDoc.insertString(mDoc.getLength(), line+"\n", attrPlain);
                                    }
                                }
                                catch(BadLocationException exp)
                                {}
                            }
                            //Moves up the view to start of JTextPane
                            mTextPane.setCaretPosition(1);
                        }
                        else if (selectedNode.isRoot())
                        {
                            //Clear mDoc every time a new click on root node occur
                            try
                            {
                                mDoc.remove(0, mDoc.getLength());
                            }
                            catch (BadLocationException exp)
                            {}
                        }
                        //Parent Node
                        else
                        {
                            
                        }
                    }
                }
            });
            
        JScrollPane treeView = new JScrollPane(mCvTree);
        JScrollPane textAreaView = new JScrollPane(mTextPane);
        
        JSplitPane cvSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, treeView, textAreaView);
        
        add(cvSplitPane);
        }
        
        private foo createCVInfo1()
        {
            String nodeName = "Personlig Information";
            
            String name = "Namn";
            String[] content1 = {"Daniel Oikarainen"};
            CUnderRubrik nodeInfo1 = new CUnderRubrik(name, content1);
            
            String adress = "Adress";
            String[] content2 = {"Lindormsgatan 17", "506 44 Bor�s"};
            CUnderRubrik nodeInfo2 = new CUnderRubrik(adress, content2);
            
            String telefon = "Telefon";
            String[] content3 = {"0704-911852", "033-3403942"};
            CUnderRubrik nodeInfo3 = new CUnderRubrik(telefon, content3);
            
            String epost = "E-Post";
            String[] content4 = {"daniel.oikarainen.jobb@comhem.se"};
            CUnderRubrik nodeInfo4 = new CUnderRubrik(epost, content4);
            
            String fodelsedatum = "F�delesedatum";
            String[] content5 = {"1979-12-16"};
            CUnderRubrik nodeInfo5 = new CUnderRubrik(fodelsedatum, content5);
            
            String egenskaper = "Egenskaper";
            String[] content6 = {"Proaktiv;M�lmedveten;Systematisk;Vetgirig;Stoisk"};
            CUnderRubrik nodeInfo6 = new CUnderRubrik(egenskaper, content6);
            
            String intressen = "Intressen";
            String[] content7 = {"Programmering;Communities;Cykling;Nutrition;Facklitteratur;Hundar"};
            CUnderRubrik nodeInfo7 = new CUnderRubrik(intressen, content7);
            
            CUnderRubrik[] underRubrikAllt = new CUnderRubrik[7];
            underRubrikAllt[0] = nodeInfo1;
            underRubrikAllt[1] = nodeInfo2;
            underRubrikAllt[2] = nodeInfo3;
            underRubrikAllt[3] = nodeInfo4;
            underRubrikAllt[4] = nodeInfo5;
            underRubrikAllt[5] = nodeInfo6;
            underRubrikAllt[6] = nodeInfo7;
            
            return new foo(nodeName, underRubrikAllt);
        }
        
        private foo createCVInfo2()
        {
            String nodeName = "Utbildning";
                        
            String tid1 = "1999-2001";            
            String[] content1 = {"Ingenj�rexamen inom Data-IT-Elektronik", "G�teborgs Tekniska Institut(GTI), G�teborg", "Medelbetyg 4.5"};
            CUnderRubrik nodeInfo1 = new CUnderRubrik(tid1, content1);
            
            CUnderRubrik[] underRubrikAllt = new CUnderRubrik[1];
            underRubrikAllt[0] = nodeInfo1;            
            
            return new foo(nodeName, underRubrikAllt);
        }
        
        private foo createCVInfo3()
        {
            String nodeName = "Anst�llningar/Karri�rhistoria";
            
            String tid1 = "2003-2018";
            String[] content1 = {"Volvo Personvagnar AB, Torslanda", "D�rrmont�r, Resurs, Lagledare"};
            CUnderRubrik nodeInfo1 = new CUnderRubrik(tid1, content1);
            
            CUnderRubrik[] underRubrikAllt = new CUnderRubrik[1];
            underRubrikAllt[0] = nodeInfo1;           
            
            return new foo(nodeName, underRubrikAllt);
        }
        
        private foo createCVInfo4()
        {
            String nodeName = "DataKunskaper";
            
            String sprak = "Spr�k";
            String[] content1 = {"Utm�rkt: Java, c++, c", "Bra: Visual Basic(VB), SQL, Pascal, ASM(x86)"};
            CUnderRubrik nodeInfo1 = new CUnderRubrik(sprak, content1);
           
            String ide = "IDE";
            String[] content2 = {"Visual Studio, Eclipse, NetBeans, JBuilder, Code::CBlocks, Dev C++, Geany"};
            CUnderRubrik nodeInfo2 = new CUnderRubrik(ide, content2);
            
            String operativsystem = "Operativsystem";
            String[] content3 = {"Windows 95/98/Me/2000/XP/7/8/10, Linux(Mint, ubuntu, Debian)"};
            CUnderRubrik nodeInfo3 = new CUnderRubrik(operativsystem, content3);
            
            String overigt = "�vrigt";
            String[] content4 = {"Datastrukturer & Algorithmer, SQL, OOP-konceptet, TCP/IP stacken, STL-Standard Template Library, Windows - programmering (API), HTML, n�tverk-koncept"};
            CUnderRubrik nodeInfo4 = new CUnderRubrik(overigt, content4);                        
            
            CUnderRubrik[] underRubrikAllt = new CUnderRubrik[4];
            underRubrikAllt[0] = nodeInfo1;
            underRubrikAllt[1] = nodeInfo2;
            underRubrikAllt[2] = nodeInfo3;
            underRubrikAllt[3] = nodeInfo4;            
            
            return new foo(nodeName, underRubrikAllt);
        }
        
        private foo createCVInfo5()
        {
            String nodeName = "�vriga kunskaper";                       
            
            String vanligasprak = "\"Vanliga\" spr�k";
            String[] content1 = {"Svenska(modersm�l), engelska(skrift och tal)"};
            CUnderRubrik nodeInfo1 = new CUnderRubrik(vanligasprak, content1);
            
            String korkort = "K�rkort";
            String[] content2 = {"Innehar B-kort"};
            CUnderRubrik nodeInfo2 = new CUnderRubrik(korkort, content2);
            
            CUnderRubrik[] underRubrikAllt = new CUnderRubrik[2];
            underRubrikAllt[0] = nodeInfo1;            
            underRubrikAllt[1] = nodeInfo2;
            
            return new foo(nodeName, underRubrikAllt);
        }
        
        private void createTree(DefaultMutableTreeNode root)
        {
            DefaultMutableTreeNode rubrikNode1 = new DefaultMutableTreeNode(createCVInfo1());
            DefaultMutableTreeNode rubrikNode2 = new DefaultMutableTreeNode(createCVInfo2());
            DefaultMutableTreeNode rubrikNode3 = new DefaultMutableTreeNode(createCVInfo3());
            DefaultMutableTreeNode rubrikNode4 = new DefaultMutableTreeNode(createCVInfo4());
            DefaultMutableTreeNode rubrikNode5 = new DefaultMutableTreeNode(createCVInfo5());
            
            root.add(rubrikNode1);
            root.add(rubrikNode2);
            root.add(rubrikNode3);
            root.add(rubrikNode4);
            root.add(rubrikNode5);
        }
        
        private JTree mCvTree;
        private JTextPane mTextPane;
        private StyledDocument mDoc;
        
        private class foo
        {
            public foo(String pNodeName, CUnderRubrik[] pLines)
            {
                mNodeName = pNodeName;
                mLines = pLines;
            }
            
            public CUnderRubrik getRowLine(int pRow)
            {
                return mLines[pRow];
            }
            
            public int getRowCount()
            {
                return mLines.length;
            }
            
            public String toString()
            {
                return mNodeName;
            }
            
            private String mNodeName;
            private CUnderRubrik[] mLines;
        }
        
        private class CUnderRubrik
        {
            public CUnderRubrik(String pHeadLine, String[] pContent)
            {
                mHeadLine = pHeadLine;
                mContent = pContent;
            }
            
            public String getHeadLine()
            {
                return mHeadLine;
            }
            
            public String[] getContent()
            {
                return mContent;
            }
            
            public int getLineCount()
            {
                return mContent.length;
            }
            
            private String mHeadLine;
            private String[] mContent;
        }
    }    
    
    private JTabbedPane mTabbedPane;
    private CGameContainer mGameContainer;
    private JCheckBoxMenuItem mPauseMenuItem;
    
    public static final int WIDTH = 650;
    public static final int HEIGHT = 400;        
}
