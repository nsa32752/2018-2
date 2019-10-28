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
           Integer.parseInt(s); // 정수만 true return 
           return true;
       } catch (NumberFormatException e) { // 그 외(특수기호, 소수, 문자) 모두 false return 
           return false;
       }
     }

   
   public SudokuGUI() { 
   }
   
   public void setSudokuGUI(int levelnum) {
      problem = new Sudokugame(levelnum);
      JPanel panel = new JPanel();
      panel.setLocation(250,250);
      
      JLabel rowlabel = new JLabel("가로");
      JLabel collabel = new JLabel("세로");
      JLabel numlabel = new JLabel("숫자");
      JLabel blanklabel = new JLabel("   ");
      JLabel statuelabel = new JLabel("   ");
      statuelabel.setFont(small);
      
      Color color = new Color(255, 255, 255);
     setBackground(color);
           
      JButton check = new JButton("확인");
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
      board.setBorder(BorderFactory.createEmptyBorder(100, 25, 100, 25));//상,좌,하,우
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
            String rownumt = rowt.getText();
            String colnumt = colt.getText();
            String numnumt = numbert.getText();
            if(isStringInt(numnumt) == false || isStringInt(colnumt) == false || isStringInt(rownumt) == false) {
               statuelabel.setText("숫자가 아님.");
            }
            else {
               int flag = 0;
               int rownum = Integer.parseInt(rowt.getText())-1;
               int colnum = Integer.parseInt(colt.getText())-1;
               int numnum = Integer.parseInt(numbert.getText());
               
               if(rownum < 0 || rownum > 8) { //rownum = 가로 번호
                  statuelabel.setText("가로오류(1~9)");
                  flag = 1; // 정답 확인 여부를 거치는 것을 막기 위한 용도 
               }
               if(colnum < 0 || colnum > 8) { //colnum = 세로 번호
                  statuelabel.setText("세로오류(1~9)");
                  flag = 1;
               }
               if(numnum < 1 || numnum > 9) { //numnum = 선택한칸에 들어갈 숫자
                  statuelabel.setText("숫자오류(1~9)");
                  flag = 1;
               }
               
               if(flag == 0 && problem.problem[colnum][rownum] == 0) { // 모든 예외처리후 정답판과 입력값 비교
                  if(numnum == problem.answer[colnum][rownum]) {
                    problem.answer[colnum][rownum] = numnum;
                     Fields[colnum][rownum].setText("");
                     Fields[colnum][rownum].setText(Fields[colnum][rownum].getText() + problem.answer[colnum][rownum]);
                     Fields[colnum][rownum].setFont(font);
                     Fields[colnum][rownum].setEnabled(false);
                     count ++;
                     statuelabel.setText("");
                  }
                  else statuelabel.setText("틀렸습니다"); // 오답인 경우, 오답 메세지 출력
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