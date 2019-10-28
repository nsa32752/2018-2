package Sudoku.copy.copy;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SudokuGUI extends JPanel {
   
   Sudokugame problem;
   EndGame endgame;
   private Font font = new Font("Courier", Font.BOLD,30);
   private Font buttonfont = new Font("Courier", Font.BOLD,18);
   private Font empty = new Font("Courier", Font.BOLD,30);
   private Font small = new Font("Courier", Font.BOLD,10);
   public int count = 0;
   
   private JTextField[][] Fields = new JTextField[9][9];
   
   public static boolean isStringInt(String s) {
       try {
           Integer.parseInt(s); // ������ true return 
           return true;
       } catch (NumberFormatException e) { // �� ��(Ư����ȣ, �Ҽ�, ����) ��� false return 
           return false;
       }
     }

   
   public SudokuGUI() { 
   }
   
   public void setSudokuGUI(int levelnum) {
      problem = new Sudokugame(levelnum);
      JPanel panel = new JPanel();
      panel.setLocation(250,250);
      
      JLabel rowlabel = new JLabel("����");
      JLabel collabel = new JLabel("����");
      JLabel numlabel = new JLabel("����");
      JLabel blanklabel = new JLabel("   ");
      JLabel statuelabel = new JLabel("   ");
      statuelabel.setFont(small);
      
      Color color = new Color(255, 255, 255);
     setBackground(color);
           
      JButton check = new JButton("Ȯ��");
      check.setFont(buttonfont);
      JTextField rowt = new JTextField();
      JTextField colt = new JTextField();
      JTextField numbert = new JTextField();
      JPanel board = new JPanel();
      JPanel board2 = new JPanel();
      board.setName("Sudoku Game");
      
      board.setPreferredSize(new Dimension(700,900));
      board2.setLayout(new GridLayout(5,1));
      board2.add(rowlabel);
      board2.add(rowt);
      board2.add(collabel);
      board2.add(colt);
      board2.add(numlabel);
      board2.setFont(font);
      board2.add(numbert);
      board2.add(blanklabel);
      board2.add(check);
      board2.add(statuelabel);
      board2.setBackground(Color.WHITE);
      board2.setBorder(BorderFactory.createEmptyBorder(380, 5, 380, 10));
      
      board.setLayout(new GridLayout(9, 9));
      board.setBounds(500,500,500,500);
      board.setBackground(Color.WHITE);
      board.setBorder(BorderFactory.createEmptyBorder(100, 25, 100, 25));//��,��,��,��
      add(board, "West");
      add(board2, "East");
      
      problem.panmake();
      problem.Core();
      
      for(int i=0; i<9; i++) {
         for(int j=0; j<9; j++) {
            Fields[i][j] = new JTextField();
            Fields[i][j].setBorder(BorderFactory.createLineBorder(Color.BLACK)); //�׵θ�
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
            String rownumt = rowt.getText();
            String colnumt = colt.getText();
            String numnumt = numbert.getText();
            if(isStringInt(numnumt) == false || isStringInt(colnumt) == false || isStringInt(rownumt) == false) {
               statuelabel.setText("���ڰ� �ƴ�.");
            }
            else {
               int flag = 0;
               int rownum = Integer.parseInt(rowt.getText())-1;
               int colnum = Integer.parseInt(colt.getText())-1;
               int numnum = Integer.parseInt(numbert.getText());
               
               if(rownum < 0 || rownum > 8) { //rownum = ���� ��ȣ
                  statuelabel.setText("���ο���(1~9)");
                  flag = 1; // ���� Ȯ�� ���θ� ��ġ�� ���� ���� ���� �뵵 
               }
               if(colnum < 0 || colnum > 8) { //colnum = ���� ��ȣ
                  statuelabel.setText("���ο���(1~9)");
                  flag = 1;
               }
               if(numnum < 1 || numnum > 9) { //numnum = ������ĭ�� �� ����
                  statuelabel.setText("���ڿ���(1~9)");
                  flag = 1;
               }
               
               if(flag == 0 && problem.problem[colnum][rownum] == 0) { // ��� ����ó���� �����ǰ� �Է°� ��
                  if(numnum == problem.answer[colnum][rownum]) {
                    problem.answer[colnum][rownum] = numnum;
                     Fields[colnum][rownum].setText("");
                     Fields[colnum][rownum].setText(Fields[colnum][rownum].getText() + problem.answer[colnum][rownum]);
                     Fields[colnum][rownum].setFont(font);
                     Fields[colnum][rownum].setEnabled(false);
                     count ++;
                     statuelabel.setText("");
                  }
                  else statuelabel.setText("Ʋ�Ƚ��ϴ�"); // ������ ���, ���� �޼��� ���
               }
               if(count == levelnum) {
                  MainController maincontroller = new MainController();
                    maincontroller.EndPanel();
                    //endgame = new EndGame(maincontroller);
               }
               System.out.println(numnum);
           }
         }
      });      
   }
}