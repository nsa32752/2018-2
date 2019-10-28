package Sudoku.copy.copy;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class EndGame extends JPanel{
   private static Font font = new Font("Courier", Font.BOLD,50);
   
   public EndGame(MainController mainController) {
     long clearTime = (mainController.endTime - mainController.startTime);
     System.out.println(mainController.endTime);
     System.out.println(mainController.startTime);
     double sec = clearTime / 1000000000;
     double min = sec / 60;
     double hour = sec / 3600;
     
     System.out.println(clearTime);
     String timebuffer = String.format("%02.0f:%02.0f:%02.0f", hour, min, sec);
     System.out.println(timebuffer);
     
      JPanel last = new JPanel();
      last = new JPanel(new GridLayout(8, 1));

      Color color = new Color(36, 189, 186);
      setBackground(color);
      last.setBackground(color);      
      
      JLabel a = new JLabel("");
      a.setFont(font);
      last.add(a);
      
      JLabel b = new JLabel("");
      b.setFont(font);
      last.add(b);
      
      JLabel c = new JLabel("");
      c.setFont(font);
      last.add(c);
      
      JLabel d = new JLabel("");
      d.setFont(font);
      last.add(d);
      
      JLabel lbl = new JLabel("    Congratulations!");
      lbl.setFont(font);
      lbl.setAlignmentX(Label.CENTER);
      last.add(lbl);
      
      JLabel lbl2 = new JLabel("You clear Sudoku Game");
      lbl2.setFont(font);
      last.add(lbl2);
      
      JLabel lb3 = new JLabel();
      lb3.setText("Clear Time is " + timebuffer);
      lb3.setFont(font);
      last.add(lb3);

      
      add(last);
      
   }


}