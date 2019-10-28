

import java.util.Random;
import java.util.Scanner;

public class Sudokugame {
   public static void check(int how, int row, int col, int num, int[][] answer, int[][] problem) {
	   System.out.println(row);
	   System.out.println(col);
	   System.out.println(num);
	   System.out.println(answer[row][col]);
	   System.out.println(problem[row][col]);
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
	
	public static void main(String[] args) {
      Scanner scan = new Scanner(System.in);
	  int[] base = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      for(int i=0; i<9; i++) {
    	  System.out.print(base[i]);
      }
      System.out.println(' ');
      System.out.println(' ');
      int[] seed = shuffle(base);
      int[][] answer = { {seed[0], seed[1], seed[2], seed[3], seed[4], seed[5], seed[6], seed[7], seed[8]},
    		  			{seed[6], seed[7], seed[8], seed[0], seed[1], seed[2], seed[3], seed[4], seed[5]},
    		  			{seed[3], seed[4], seed[5], seed[6], seed[7], seed[8], seed[0], seed[1], seed[2]},
    		  			{seed[2], seed[0], seed[1], seed[5], seed[3], seed[4], seed[8], seed[6], seed[7]},
    		  			{seed[8], seed[6], seed[7], seed[2], seed[0], seed[1], seed[5], seed[3], seed[4]},
    		  			{seed[5], seed[3], seed[4], seed[8], seed[6], seed[7], seed[2], seed[0], seed[1]},
    		  			{seed[1], seed[2], seed[0], seed[4], seed[5], seed[3], seed[7], seed[8], seed[6]},
    		  			{seed[7], seed[8], seed[6], seed[1], seed[2], seed[0], seed[4], seed[5], seed[3]},
    		  			{seed[4], seed[5], seed[3], seed[7], seed[8], seed[6], seed[1], seed[2], seed[0]} }; 
      int[][] board = new int[9][9];
      for(int i=0; i<9; i++) System.arraycopy(answer[i], 0, board[i], 0, answer[i].length);
      int level = 15;
      int[][] problem = problem(level, board); // level, answer, 레벨 설정 입력받아서 if로 나누기
      for(int i = 0 ; i < 9; i ++) {
		  for(int j = 0 ; j < 9; j ++) {
			  System.out.print(answer[i][j]);
		  }
		  System.out.println(' ');
      }
      System.out.println(' ');
      for(int i = 0 ; i < 9; i ++) {
		  for(int j = 0 ; j < 9; j ++) {
			  System.out.print(problem[i][j]);
		  }
		  System.out.println(' ');
      }
	  int how = 0;
      while(how < level) {
    	  int row = scan.nextInt();
    	  int col = scan.nextInt();
    	  int number = scan.nextInt();
    	  check(how, row-1, col-1, number, answer, problem);
    	  for(int i = 0 ; i < 9; i ++) {
    		  for(int j = 0 ; j < 9; j ++) {
    			  System.out.print(problem[i][j]);
    		  }
    		  System.out.println(' ');
    	  }
      }
   }
}
