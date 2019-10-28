import javax.swing.*;
import java.awt.*;

public class SudokuGUI extends JFrame {
	final int[][] answer = {{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9},
							{1,2,3,4,5,6,7,8,9}};
	private static JTextField[][] Fields = new JTextField[9][9];
	
	public SudokuGUI() {
		setTitle("Sudoku Game");
		setLocation(250,10);
		
		JPanel board = new JPanel();
		this.add(board);
		board.setLayout(new GridLayout(9,9));
		board.setBackground(Color.WHITE);
		board.setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));
		add(board, "Center");
		
		for(int i=0; i<9; i++) {
			for(int j=0; j<9; j++) {
				Fields[i][j] = new JTextField();
				Fields[i][j].setBorder(BorderFactory.createLineBorder(Color.BLACK));
				board.add(Fields[i][j]);
				Fields[i][j].setHorizontalAlignment(JTextField.CENTER);
			}
		}
		
	}
	
public static void main(String[] args) {
		SudokuGUI gui = new SudokuGUI();

		gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		gui.setSize(450,450);

		gui.setVisible(true);



	}

}
