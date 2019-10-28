package Sudoku.copy.copy;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



public class FrameTest extends JPanel{
   public int levelnum = 0;
   private static Font font = new Font("Courier", Font.BOLD,50);
   private static Font font2 = new Font("Courier", Font.BOLD,60);
   
   public FrameTest(MainController mainController) {
      
      JPanel last = new JPanel();
      last = new JPanel(new GridLayout(2, 1));

      JLabel lbl = new JLabel("    " + "  Welcome To The Sudoku Game!      ");
      lbl.setFont(font);
      last.add(lbl);   
      
      JPanel buttonPanel = new JPanel();
      buttonPanel = new JPanel(new GridLayout(3, 1));
      
      Color color = new Color(36, 189, 186);
       setBackground(color);
       last.setBackground(color);
       buttonPanel.setBackground(color);
      
      JButton hard = new JButton("Hard");
      hard.setFont(font2);
      buttonPanel.add(hard);
      buttonPanel.setBorder(BorderFactory.createEmptyBorder(0, 300, 0, 300));
      
      JButton normal = new JButton("Normal");
      normal.setFont(font2);
      buttonPanel.add(normal);
      buttonPanel.setBorder(BorderFactory.createEmptyBorder(0, 300, 0, 300));
      
      JButton easy = new JButton("Easy");
      easy.setFont(font2);
      buttonPanel.add(easy);
      buttonPanel.setBorder(BorderFactory.createEmptyBorder(0, 300, 0, 300));
      
       hard.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                  mainController.changePanel(25);
               }
        });
    
        normal.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {
                  mainController.changePanel(20);
            }
        });
    

        easy.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {
                  mainController.changePanel(15);
           }
        });
           
      last.add(buttonPanel);
      
      add(last);
      
   }

   

//   public static void main(String[] args) {
//
//      //프레임을 띄워주기 위해 frame객체 생성
//
//      JFrame frame = new JFrame("Sudoku");
//
//      //메인 클래스 객체 생성
//
//      FrameTest jPanelFrameTest = new FrameTest();
//
//      //프레임에 메인 클래스 객체 넣어줌
//
//      frame.getContentPane().add(jPanelFrameTest);
//      //프레임을 뿌려줌
//
//      frame.setBounds(200, 200, 800, 800);
//      frame.setVisible(true);
//      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//
//   }
}