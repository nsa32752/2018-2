package Sudoku;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SudokuGUI extends JPanel {
   
   Sudokugame problem;
   private Font font = new Font("Courier", Font.BOLD,30);
   private Font buttonfont = new Font("Courier", Font.BOLD,18);
   private Font empty = new Font("Courier", Font.BOLD,30);
   //public static int rownum;
   //public static int colnum;
   //public static int numnum;
   
   private JTextField[][] Fields = new JTextField[9][9];
   
   public SudokuGUI() { 
   }
   
   public void setSudokuGUI(int levelnum) {
     problem = new Sudokugame(levelnum);
      JPanel frame = new JPanel();
//      frame.setTitle("Sudoku Game");
      frame.setLocation(0,0);
      
      JLabel rowlabel = new JLabel("가로");
      JLabel collabel = new JLabel("세로");
      JLabel numlabel = new JLabel("숫자");
      JLabel blanklabel = new JLabel("   ");
      
      JButton check = new JButton("확인");
      check.setFont(buttonfont);
      JTextField rowt = new JTextField();
      JTextField colt = new JTextField();
      JTextField numbert = new JTextField();
      JPanel board = new JPanel();
      JPanel board2 = new JPanel();
      board.setName("Sudoku Game");
      
      board2.setLayout(new GridLayout(4,1));
      board2.add(rowlabel);
      board2.add(rowt);
      board2.add(collabel);
      board2.add(colt);
      board2.add(numlabel);
      board2.setFont(font);
      board2.add(numbert);
      board2.add(blanklabel);
      board2.add(check);
      board2.setBackground(Color.WHITE);
      board2.setBorder(BorderFactory.createEmptyBorder(20, 5, 20, 0));
      
      board.setLayout(new GridLayout(9, 9));
      board.setBounds(0,0,500,500);
      board.setBackground(Color.WHITE);
      board.setBorder(BorderFactory.createEmptyBorder(185, 430, 185, 0));//상,좌,하,우
      add(board, "West");
      add(board2, "East");
      
      problem.panmake();
      problem.Core();
      
      for(int i=0; i<9; i++) {
         for(int j=0; j<9; j++) {
            Fields[i][j] = new JTextField();
            Fields[i][j].setBorder(BorderFactory.createLineBorder(Color.BLACK)); //테두리
            board.add(Fields[i][j]);
            Fields[i][j].setHorizontalAlignment(JTextField.CENTER);
            if(problem.board[i][j] != 0) {
               Fields[i][j].setText(Fields[i][j].getText() + problem.board[i][j]);
               Fields[i][j].setFont(font);
               Fields[i][j].setEnabled(false);
            }
            else {
               Fields[i][j].setText(Fields[i][j].getText());
               Fields[i][j].setForeground(Color.BLUE);
               Fields[i][j].setFont(empty);
            }
         }
      }
      check.addActionListener(new ActionListener() {
         
         public void actionPerformed(ActionEvent e) {
            int rownum = Integer.parseInt(rowt.getText())-1;
            int colnum = Integer.parseInt(colt.getText())-1;
            int numnum = Integer.parseInt(numbert.getText());
            if(problem.problem[colnum][rownum] == 0) {
               if(numnum == problem.answer[colnum][rownum]) {
                  Fields[colnum][rownum].setText("");
                  Fields[colnum][rownum].setText(Fields[colnum][rownum].getText() + problem.answer[colnum][rownum]);
                  Fields[colnum][rownum].setFont(font);
                  Fields[colnum][rownum].setForeground(Color.BLACK);
               }
            }
            System.out.println(numnum);
         }
      });
      
      
   }
   
//public static void main(String[] args) {
//      SudokuGUI gui = new SudokuGUI();
//
//      gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//
//      gui.setSize(1000,1000);
//
//      gui.setVisible(true);
//      
//      gui.setTitle("Sudoku");
//
//
//
//   }

}