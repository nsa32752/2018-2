package Sudoku;



import java.util.Random;
import java.util.Scanner;

public class Sudokugame {
	
	public static int levelnum = 0;
	
	public static int[][] problem;
	
	private static int[] base = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	private static  int[] seed = shuffle(base);
	
	public static int[][] answer = { {seed[0], seed[1], seed[2], seed[3], seed[4], seed[5], seed[6], seed[7], seed[8]},  // 정답판
  									  {seed[6], seed[7], seed[8], seed[0], seed[1], seed[2], seed[3], seed[4], seed[5]},
  									  {seed[3], seed[4], seed[5], seed[6], seed[7], seed[8], seed[0], seed[1], seed[2]},
  									  {seed[2], seed[0], seed[1], seed[5], seed[3], seed[4], seed[8], seed[6], seed[7]},
  									  {seed[8], seed[6], seed[7], seed[2], seed[0], seed[1], seed[5], seed[3], seed[4]},
  									  {seed[5], seed[3], seed[4], seed[8], seed[6], seed[7], seed[2], seed[0], seed[1]},
  									  {seed[1], seed[2], seed[0], seed[4], seed[5], seed[3], seed[7], seed[8], seed[6]},
  									  {seed[7], seed[8], seed[6], seed[1], seed[2], seed[0], seed[4], seed[5], seed[3]},
  									  {seed[4], seed[5], seed[3], seed[7], seed[8], seed[6], seed[1], seed[2], seed[0]} }; 
	
	public static int[][] board = new int[9][9]; // 0들어가있는거
	
   public static void check(int how, int row, int col, int num, int[][] answer, int[][] problem) {
	   if(answer[row][col] == num && problem[row][col] == 0) {
		   System.out.println("check");
		   how++;
		   problem[row][col] = num;
	   }
   }
   
   public static int[] shuffle(int[] result) {
	   int temp, seed;
	   for(int i=0; i<result.length;i++) {
	       seed = (int)(Math.random()*8)+1;
	       temp = result[i];
	       result[i] = result[seed];
	       result[seed] = temp;
	   }
	   return result;
   }
   
   public static int[][] problem(int level, int[][] result) {
	   int num = 0;
	   int row, col;
	   while(num < level) {
		   row = (int)(Math.random() *8);
		   col = (int)(Math.random() *8);
		   if(result[row][col] != 0) {
			   result[row][col] = 0;
			   num++;
		   }
	   }
	   return result;
   }
   
   public static int level() {
	   Scanner scan = new Scanner(System.in);
	   String level = scan.next();
	   if(level == "Low") return 15;
	   else if(level == "Mid") return 20;
	   else return 25;
   }
	
   	public static void panmake() {
   		for(int i=0; i<9; i++) System.arraycopy(answer[i], 0, board[i], 0, answer[i].length);
   	}
   	
   
	public static void Core() {
      levelnum = 20;
      problem = problem(levelnum, board); // level, answer, 레벨 설정 입력받아서 if로 나누기
   }
}

