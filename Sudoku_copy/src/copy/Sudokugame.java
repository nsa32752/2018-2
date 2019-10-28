package Sudoku.copy.copy;

public class Sudokugame {
   
   public int levelnum = 0;
   
   public int[][] problem;
   
   private int[] base = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   
   private  int[] seed = shuffle(base);
   
   public int[][] answer = { {seed[0], seed[1], seed[2], seed[3], seed[4], seed[5], seed[6], seed[7], seed[8]},  // 정답판
                               {seed[6], seed[7], seed[8], seed[0], seed[1], seed[2], seed[3], seed[4], seed[5]},
                               {seed[3], seed[4], seed[5], seed[6], seed[7], seed[8], seed[0], seed[1], seed[2]},
                               {seed[2], seed[0], seed[1], seed[5], seed[3], seed[4], seed[8], seed[6], seed[7]},
                               {seed[8], seed[6], seed[7], seed[2], seed[0], seed[1], seed[5], seed[3], seed[4]},
                               {seed[5], seed[3], seed[4], seed[8], seed[6], seed[7], seed[2], seed[0], seed[1]},
                               {seed[1], seed[2], seed[0], seed[4], seed[5], seed[3], seed[7], seed[8], seed[6]},
                               {seed[7], seed[8], seed[6], seed[1], seed[2], seed[0], seed[4], seed[5], seed[3]},
                               {seed[4], seed[5], seed[3], seed[7], seed[8], seed[6], seed[1], seed[2], seed[0]} }; 
   
   public int[][] board = new int[9][9]; // 0들어가있는거
   
   public Sudokugame(int levelnum) {
      this.setLevel(levelnum);
   }
   
   public int[] shuffle(int[] result) {
      int temp, seed;
      for(int i=0; i<result.length;i++) {
          seed = (int)(Math.random()*8)+1;
          temp = result[i];
          result[i] = result[seed];
          result[seed] = temp;
      }
      return result;
   }
   
   public int[][] problem(int level, int[][] result) {
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
   
   public void setLevel(int levelnum) {
      this.levelnum = levelnum;
   }
   
   
      public void panmake() {
         for(int i=0; i<9; i++) System.arraycopy(answer[i], 0, board[i], 0, answer[i].length);
      }
      
   
   public void Core() {
      problem = problem(levelnum, board); // level, answer, 레벨 설정 입력받아서 if로 나누기
   }
}