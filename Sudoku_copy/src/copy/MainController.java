package Sudoku.copy.copy;

import javax.swing.*;

public class MainController {
   JFrame main = new JFrame();
   SudokuGUI sudokugui;
   FrameTest ft;
   EndGame endgame;
   Sudokugame sudokugame;
   public static long startTime;
   public static long endTime;
   
   public MainController() { 
      this.ft = new FrameTest(this);
      this.sudokugui = new SudokuGUI();
      
      this.main.setTitle("sudoku");
      this.main.setSize(900, 900);
      this.main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      this.main.setVisible(true);      
      this.main.getContentPane().add(this.ft);
   }
   
   public void changePanel(int levelnum) {
      startTime = System.nanoTime();
      System.out.println(startTime);
      this.sudokugui.setSudokuGUI(levelnum);
      this.main.getContentPane().removeAll();
      this.main.getContentPane().add(this.sudokugui);
      main.revalidate();
      main.repaint();
   }
   
   public void EndPanel() { 
      endTime = System.nanoTime();
      System.out.println(endTime);
      this.endgame = new EndGame(this);
      this.main.getContentPane().removeAll();
      this.main.getContentPane().add(this.endgame);
      main.revalidate();
      main.repaint();
   }
}