package Sudoku;

import javax.swing.JFrame;

public class Main {
	
	public static void main(String[] args) {
		
		Sudokugame game = new Sudokugame();
		
		SudokuGUI gui = new SudokuGUI();
		
		gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		gui.setSize(1000,1000);
		gui.setVisible(true);
		
	}
}
