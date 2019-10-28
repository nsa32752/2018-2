package Sudoku;

import java.awt.*;
import java.awt.event.*;

public class FrameTest {
   public Frame f;
    private Label head;
    private Label statue;
    private Panel c;
    public int levelnum = 0;
    
    public FrameTest() {
        prepareGUI();
    }
 
    private void prepareGUI() {
        // Frame 에 대한 셋팅
        f = new Frame("Sudoku");
        f.setSize(600, 600);
        f.setLayout(new GridLayout(3, 1));
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent) {
                System.exit(0);
            }
        });
 
        // 상단에 있는 라벨
        head = new Label();
        head.setAlignment(Label.CENTER);
        head.setText(" Welcome to the Sudoku Game ! ");
        head.setFont(new Font("고딕", Font.BOLD, 25));
 
        // 하단 상태값 라벨
        statue = new Label();
        statue.setText("Status Lable");
        statue.setFont(new Font("고딕", Font.BOLD, 25));
        statue.setAlignment(Label.CENTER);
        statue.setSize(350, 100);
        
        Color color = new Color(36, 168, 169); // 배경 색 설정
 
        c = new Panel();
        c.setLayout(new FlowLayout());
        
        this.showButton();
        f.setBackground(color);
        f.add(head);
        f.add(c);
        f.add(statue);
        f.setVisible(true);
    }
 
    private void showButton() {
 
        Button hard = new Button("Hard");
        hard.setFont(new Font("고딕", Font.BOLD,45));
        Button normal = new Button("Normal");
        normal.setFont(new Font("고딕", Font.BOLD,45));
        Button easy = new Button("Easy");
        easy.setFont(new Font("고딕", Font.BOLD,45));
 
        hard.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               levelnum = 25;
                statue.setText("Hard mode start!");
            }
        });
 
        normal.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               levelnum = 20;
                statue.setText("Normal mode start!");
            }
        });
 
        easy.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               levelnum = 15;
                statue.setText("Easy mode start!");
            }
        });
 
        c.add(hard);
        c.add(normal);
        c.add(easy);
    }
    public int getlevelnum() {
       return this.levelnum;
    }
}