/* Î¨¥Ìïú Í≥ÑÏÇ∞Í∏?
?∞ÏÇ∞???∞ÏÑ†?úÏúÑ??( == 0, +, - == 1, *, / == 2, ) == 3 ?¥Ï?Îß? ?ºÏ™Ω Í¥ÑÌò∏??Î¨¥Ï°∞Í±??£Í≥† Î≥∏Îã§.
?®ÏàòÍµ¨ÌòÑ???∏Ïùò?±ÏùÑ ?ÑÌï¥??(?  0?ºÎ°ú ?êÏóà?? 
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define SIZE_FRONT (first->f_end - first->f_start >= second->f_end - second->f_start ? first->f_end - first->f_start + 3 : second->f_end - second->f_start + 3)
#define SIZE_BACK (first->b_end - first->b_start >= second->b_end - second->b_start ? first->b_end - first->b_start + 1 : second->b_end - second->b_start + 1)
#define SIZE_MULTIPLE_FRONT ((first->f_end - first->f_start) + (second->f_end - second->f_start) + 3)
#define SIZE_MULTIPLE_BACK ((first->b_end - first->b_start) + (second->b_end - second->b_start) + 2)
#define SIZE_MULTIPLE_ALL ((first->f_end - first->f_start) + (second->f_end - second->f_start) + (first->b_end - first->b_start) + (second->b_end - second->b_start) + 4)


typedef struct Node {
   char *f_start;
   char *f_end;
   char *b_start;
   char *b_end;
   int op_flag;
   int op;
   int op_prec;
   struct Node *prev;
   struct Node *next;
} Node;

typedef struct {
   Node *head;
   Node *tail;
} DLL;

Node *newnode(int op_flag, int op, int op_prec, char *f_start, char *f_end, char *b_start, char *b_end) {
   Node *temp = (Node *)malloc(sizeof(Node));
   temp->op_prec = op_prec;
   temp->op_flag = op_flag; 
   temp->f_start = f_start;
   temp->f_end = f_end;
   temp->b_start = b_start;
   temp->b_end = b_end;
   temp->op = op;
   temp->next = NULL;
   temp->prev = NULL;
   return temp;
}

DLL *newDLL() {
   DLL *temp = (DLL *)malloc(sizeof(DLL));
   temp->head = NULL;
   temp->tail = NULL;
   return temp;
}
void minus(Node *first, Node *second, int minus_flag, DLL *stack);
void plus(Node *first, Node *second, DLL *stack);
void completing_calculation_for_minus(char *result_f, char *result_b, int minus_flag, Node *first, Node *second, DLL *stack);
void completing_calculation(char *result_f, char *result_b, int minus_flag, Node *first, Node *second, DLL *stack);

void append(DLL *list, Node *newnode) {
   Node *temp = list->head;
   if(list->head == NULL) {
      list->head = newnode;
      list->tail = newnode;
   } else {
      while(temp->next != NULL) {
         temp = temp->next;
      }
      list->tail->next = newnode;
      newnode->prev = temp;
      list->tail = newnode;
   }
}


void print(DLL *list){   
   Node *tmp = list->head;
   char *f_temp = tmp->f_start;
   char *s_temp = tmp->b_start;
   while(tmp){
      //printf("(%d %d %d %p %p %p %p)\n ", tmp->op_flag, tmp->op, tmp->op_prec, tmp->f_start, tmp->f_end, tmp->b_start, tmp->b_end);
      f_temp = tmp->f_start;
      s_temp = tmp->b_start;
     if(tmp->op_flag == 0) {
        for(f_temp; f_temp <= tmp->f_end; f_temp++) {
           if(*f_temp == '-') printf("-");
         else printf("%d",*f_temp);
         }
         if(s_temp != NULL) {
            printf(".");
            for(s_temp; s_temp <= tmp->b_end; s_temp++) {
               printf("%d", *s_temp);
            }
         }
      } else {
         if(tmp->op == 1) printf("+");
         else if(tmp->op == 2) printf("-");
      	 else if(tmp->op == 4) printf("*");
	  }
      //if(tmp->op_flag == 0) printf("%d %d\n", *tmp->f_start, *tmp->f_end);
      printf(" ");
      tmp = tmp->next;
   }
}

void pop_push(DLL *op_stack, DLL *stack) {
   Node *temp = op_stack->tail;
   if(op_stack->tail->op == -8 || op_stack->tail->op == -7) {
      if(op_stack->tail->prev == NULL) {
         free(op_stack->tail);
         op_stack->head = NULL;
         op_stack->tail = NULL;
      } else {
         op_stack->tail = op_stack->tail->prev;
         op_stack->tail->next->prev = NULL;
         free(op_stack->tail->next);
         op_stack->tail->next = NULL;
         }
      return;
   }
   append(stack, newnode(1, temp->op, temp->op_prec, temp->f_start, temp->f_end, temp->b_start, temp->b_end));
   if(op_stack->tail->prev == NULL) {
      free(op_stack->tail);
      op_stack->head = NULL;
      op_stack->tail = NULL;
   } else {
      op_stack->tail = op_stack->tail->prev;
      op_stack->tail->next->prev = NULL;
      free(op_stack->tail->next);
      op_stack->tail->next = NULL;
      
   }
}

void infix_to_postfix(DLL *list, DLL *stack) { //stack??postfixÎ°?Î≥ ?òÎêú ?ùÏù¥ ?§Ïñ¥Í∞ÑÎã§. Î¶¨Ïä§?∏Îäî ?¨Ìôú?©Ìñà??
   DLL *op_stack = newDLL();
   Node *temp = list->head;
   while(temp) {
      if(temp->op_flag == 0) { //?´Ïûê??Í≤ΩÏö∞ Í∑∏ÎÉ• append?úÎã§.
         append(stack, newnode(0, 0, 0 , temp->f_start, temp->f_end, temp->b_start, temp->b_end)); //temp???¥Îãπ?òÎäî ?∏ÎìúÎ•?append
      } else {
         if(op_stack->head == NULL || temp->op == -8) { // ?∞ÏÇ∞???§ÌÉù??NULL?¥Í±∞??tempÍ∞  ?ºÏ™Ω Í¥ÑÌò∏?ºÎïå 
            append(op_stack, newnode(1, temp->op, temp->op_prec, temp->f_start, temp->f_end, temp->b_start, temp->b_end)); // Î¨¥Ï°∞Í±?append?úÎã§.
         } else {
             if(temp->op_prec > op_stack->tail->op_prec) { //?§Ïñ¥Í∞??∞ÏÇ∞???úÏúÑÍ∞  op_stack ÏµúÏÉÅ?ÑÏóê ?àÎäî ?∞ÏÇ∞???úÏúÑÎ≥¥Îã§ ?íÏ? Í≤ΩÏö∞
                append(op_stack, newnode(1, temp->op, temp->op_prec, temp->f_start, temp->f_end, temp->b_start, temp->b_end)); // Í∑∏ÎÉ• append?úÎã§.
            } else { //?∞ÏÇ∞???úÏúÑÍ∞  Í∞ôÍ±∞???ëÏ? Í≤ΩÏö∞
               while(temp->op_prec <= op_stack->tail->op_prec && op_stack->head != NULL) {
                  //printf("here?\n");
                  pop_push(op_stack, stack); //?£ÏùÑ ???àÎäî ?ÅÌô©???¨ÎïåÍπåÏ? ÎπºÎÇ¥??stack??push?úÎã§.
                  if(op_stack->head == NULL) break;
               }
               append(op_stack, newnode(1, temp->op, temp->op_prec, temp->f_start, temp->f_end, temp->b_start, temp->b_end)); //??Î∫êÏúº??push?úÎã§.
            }
         }
      }
      temp = temp->next;
   }
   while(op_stack->head) {
      pop_push(op_stack, stack);
   }
   printf("postfix: ");
   print(stack);
   printf("\n");
}

void completing_calculation_for_minus(char *result_f, char *result_b, int minus_flag, Node *first, Node *second, DLL *stack) {
   if(first->next->op_flag == 0) completing_calculation(result_f, result_b, minus_flag, first, second, stack);
   else completing_calculation(result_f, result_b, minus_flag, second, first, stack);
}

void completing_calculation(char *result_f, char *result_b, int minus_flag, Node *first, Node *second, DLL *stack)
{
   if(minus_flag == 1 && result_f[1] == 1) {
        result_f[0] = -3;
        Node *temp = newnode(0, 0, 0, result_f, result_f + SIZE_FRONT - 1, result_b, result_b + SIZE_BACK );
        if(first->prev == NULL) {
           stack->head = temp;
        } else {
            temp->prev = first->prev;
            first->prev->next = temp;
        }
        temp->next = second->next->next;
        second->next->next->prev = temp;
    } else if(minus_flag == 1 && result_f[1] == 0) {
        result_f[1] = -3;
        Node *temp = newnode(0, 0, 0, &result_f[1], result_f + SIZE_FRONT - 1, result_b, result_b + SIZE_BACK - 1);
        if(first->prev == NULL) {
            stack->head = temp;
        } else {
            temp->prev = first->prev;
            first->prev->next = temp;
        }
        if(second->next->next == NULL) {
           stack->tail = temp;
        } else {
           second->next->next->prev = temp;
           temp->next = second->next->next;
        }
    } else if(minus_flag == 0 && result_f[1] == 1) {
        Node *temp = newnode(0, 0, 0, &result_f[1], result_f + SIZE_FRONT - 1, result_b, result_b + SIZE_BACK - 1);
        if(first->prev == NULL) {
            stack->head = temp;
        } else {
            temp->prev = first->prev;
            first->prev->next = temp;
        }
        if(second->next->next == NULL) {
           stack->tail = temp;
        } else {
           second->next->next->prev = temp;
           temp->next = second->next->next;
        }
    } else {
        Node *temp = newnode(0, 0, 0, &result_f[2], result_f + SIZE_FRONT - 1, result_b, result_b + SIZE_BACK - 1);
        if(first->prev == NULL) {
            stack->head = temp;
        } else {
            temp->prev = first->prev;
            first->prev->next = temp;
        }
        if(second->next->next == NULL) {
           stack->tail = temp;
        } else {
           second->next->next->prev = temp;
           temp->next = second->next->next;
        }
    }
    free(second->next);
    free(second);
    free(first);
}

void multiple(Node *first, Node *second, int minus_flag, DLL *stack){
   printf("multiple...start...\n");
   char *f_temp = first->b_end;
    char *s_temp = second->b_end;
    minus_flag = 0;
    if(*first->f_start == -3 && *second->f_start != -3) { //øø * øø  
      first->f_start = first->f_start + 1;
     minus_flag = 1;
   }
   if(*first->f_start != -3 && *second->f_start == -3) { //øø * øø  
      second->f_start = second->f_start + 1;
      minus_flag = 1;
   }
    if(*first->f_start == -3 && *second->f_start == -3) { //øø * øø
        first->f_start = first->f_start + 1;
        second->f_start = second->f_start + 1;
    }

   char *result_a = (char *)malloc(SIZE_MULTIPLE_ALL);
   char *result_temp = result_a;

   for(result_temp; result_temp < result_a + SIZE_MULTIPLE_ALL; result_temp++) *result_temp = 0;
   *result_temp = 0; 
   
   int count = 0;
   if(second->b_start == NULL){
         //printf("b_start is NULL\n");
      s_temp = second->f_end;
   }
   if(first->b_start == NULL){
      //printf("f_start is NULL\n");
      f_temp = first->f_end;
   }
   while(s_temp != second->f_start){
      while(f_temp != first->f_start){
         if(*result_temp + *f_temp * *s_temp >= 10){
               *(result_temp - 1) += (*result_temp + *f_temp * *s_temp) / 10;
               *result_temp = (*result_temp + *f_temp * *s_temp) % 10;   
         }
            else *result_temp = *result_temp + (*f_temp * *s_temp);
            if(f_temp == first->b_start) f_temp = first->f_end;
            else{
               f_temp--;
            }
            result_temp --;
            count++;
         }
      if(*result_temp + *f_temp * *s_temp >= 10){
         *(result_temp - 1) += (*result_temp + *f_temp * *s_temp) / 10;
         *result_temp = (*result_temp + *f_temp * *s_temp) % 10;
         }
      else *result_temp += (*f_temp * *s_temp);
      
      s_temp == second->b_start? s_temp = second->f_end : s_temp--;
      first->b_start == NULL? (f_temp = first->f_end) : (f_temp = first->b_end);
      result_temp = result_temp + count - 1;
      count=0;
   }
   while(f_temp != first->f_start){
      if(*result_temp + *f_temp * *s_temp >= 10){
            *(result_temp - 1) += (*result_temp + *f_temp * *s_temp) / 10;
            *result_temp = (*result_temp + *f_temp * *s_temp) % 10;
         }
      else *result_temp += (*f_temp * *s_temp);
      if(f_temp == first->b_start) f_temp = first->f_end;
      else{   
         f_temp--;
      }
      result_temp--;
   }
   if(*result_temp + *f_temp * *s_temp >= 10){
      *(result_temp - 1) += (*result_temp + *f_temp * *s_temp) / 10;
      *result_temp = (*result_temp + *f_temp * *s_temp) % 10;
   }
   else *result_temp += (*f_temp * *s_temp);

   result_temp --;

   while(*result_temp != 0) result_temp--;
   result_temp++;

   char *result_front = (char *)malloc(SIZE_MULTIPLE_FRONT);   
   char *result_back = (char *)malloc(SIZE_MULTIPLE_BACK);
   for(int i=0; i < SIZE_MULTIPLE_ALL - SIZE_MULTIPLE_BACK-1; i++){
      printf("%d", *result_temp);
      result_front = result_temp;
      result_front++;
      result_temp++;
   }
	printf(".");
   for(int i=0; i < SIZE_MULTIPLE_BACK-2; i++){
      printf("%d", *result_temp);
      result_back = result_temp;
      result_back++;
      result_temp++;
   }

	printf("\n");
   result_front = result_front - (SIZE_MULTIPLE_ALL - SIZE_MULTIPLE_BACK);
   result_back = result_back - (SIZE_MULTIPLE_BACK);
   completing_calculation(result_front, result_back, minus_flag, first, second, stack);
}
   
void minus(Node *first, Node *second, int minus_flag, DLL *stack) {
    char *f_temp = first->f_start;
    char *s_temp = second->f_start;
    char *result_b_end = NULL;
    char *result_f_end = NULL;
    char *minus_minus_front = NULL;
    char *minus_minus_temp = NULL;
    
   char *result_b_f = NULL;
    char *result_b_s = NULL;
    char *result_b_f_temp = NULL;
    char *result_b_s_temp = NULL;
    char *result_b_f_end = NULL;
    char *result_b_s_end = NULL;
    char *result_b_f_copy = NULL;
    char *result_b_s_copy = NULL;
    
   if(*first->f_start == -3 && *second->f_start != -3) { //¿Ωºˆ - æÁºˆ
       minus_minus_front = (char *)malloc(second->f_end - second->f_start + 2);
       minus_minus_front[0] = -3;
       minus_minus_temp = minus_minus_front + 1;
       while(s_temp != second->f_end) {
          *minus_minus_temp = *s_temp;
          minus_minus_temp++;
          s_temp++;
       } *minus_minus_temp = *s_temp;
       second->f_start = minus_minus_front;
       second->f_end = minus_minus_temp;
       plus(first, second, stack);
       return;
   }
   if(*first->f_start != -3 && *second->f_start == -3) { // æÁºˆ - ¿Ωºˆ
      second->f_start = second->f_start + 1;
      plus(first, second, stack);
      return;
   }
    if(*first->f_start == -3 && *second->f_start == -3) { // ¿Ωºˆ - ¿Ωºˆ
        first->f_start = first->f_start + 1;
        second->f_start = second->f_start + 1;
        minus(second, first, 0, stack);
        return;
    }
    if(first->f_end - first->f_start < second->f_end - second->f_start) {
      minus(second, first, 1, stack); //ππ∞° ¥ı ≈´¡ˆ, ∫Œ»£ ≥÷æÓº≠
      return;
   }
    if(first->f_end - first->f_start == second->f_end - second->f_start) {
        while(f_temp != first->f_end && s_temp != second->f_end) {
            if(*f_temp < *s_temp) {
                minus(second, first, 1, stack);
                return;
            } else {
                f_temp++;
                s_temp++;
            }
        }
        if(*f_temp < *s_temp) {
         minus(second, first, 1, stack);
         return;
      }
    }
    f_temp = first->f_start;
    s_temp = second->f_start;

    //∞ËªÍ Ω√¿€
    char *result_f = (char *)malloc(SIZE_FRONT);
    char *result_f_temp = result_f;
    char *result_b = NULL;
    if(first->b_start != NULL || second->b_start != NULL) {
        result_b = (char *)malloc(SIZE_BACK);
        result_b_f = (char *)malloc(SIZE_BACK);
        result_b_s = (char *)malloc(SIZE_BACK);
    }
    char *result_b_temp = result_b;
    result_b_f_temp = result_b_f;
    result_b_s_temp = result_b_s;
    result_b_f_copy = result_b_f;
    result_b_s_copy = result_b_s;
    
    for(result_f_temp; result_f_temp < result_f + SIZE_FRONT; result_f_temp++) *result_f_temp = 0;
    result_f_temp--;
    result_f_end = result_f_temp;
    if(result_b != NULL) {
        for(result_b_temp; result_b_temp < result_b + SIZE_BACK  ; result_b_temp++) *result_b_temp = 0; // ?åÏàò?êÎèÑ ?àÏúºÎ©?Ï¥àÍ∏∞?îs
        for(result_b_f_temp; result_b_f_temp < result_b_f + SIZE_BACK ; result_b_f_temp++) *result_b_f_temp = 0;
        result_b_f_end = result_b_f_temp;
      result_b_f_temp--;
        for(result_b_s_temp; result_b_s_temp < result_b_s + SIZE_BACK ; result_b_s_temp++) *result_b_s_temp = 0;
        result_b_s_end = result_b_s_temp;
      result_b_s_temp--;
      result_b_end = result_b_temp;
      result_b_temp--;
      f_temp = first->b_start;
      s_temp = second->b_start;
      while(f_temp != first->b_end) {
         *result_b_f_copy = *f_temp;
         f_temp++;
         result_b_f_copy++;
      }
      *result_b_f_copy = *f_temp;
      while(s_temp != second->b_end) {
         *result_b_s_copy = *s_temp;
         s_temp++;
         result_b_s_copy++;
      }
      *result_b_s_copy = *s_temp;
    }

    f_temp = first->f_end;
    s_temp = second->f_end;

    while(f_temp != first->f_start && s_temp != second->f_start ) {
        *result_f_temp += *f_temp - *s_temp;
        if(*result_f_temp < 0) {
            *result_f_temp += 10;
            *(result_f_temp - 1) -= 1;
        }
        result_f_temp--;
        f_temp--;
        s_temp--;
    }
    *result_f_temp += *f_temp - *s_temp;
    if(*result_f_temp < 0) {
       *result_f_temp += 10;
      *(result_f_temp - 1) -= 1;
    }
    
    if(f_temp != first->f_start) { 
        f_temp--;
        result_f_temp--;
        while(f_temp != first->f_start) {
            *result_f_temp += *f_temp;
            if(*result_f_temp < 0) {
             *result_f_temp += 10;
            *(result_f_temp - 1) -= 1;
          }
            result_f_temp--;
            f_temp--;
        }
        *result_f_temp += *f_temp;
        if(*result_f_temp < 0) {
          *result_f_temp += 10;
         *(result_f_temp - 1) -= 1;
         }
    }
    
    if(result_b != NULL) {
       result_b_f_temp = result_b_f + SIZE_BACK - 1;
       result_b_s_temp = result_b_s + SIZE_BACK - 1;
      while(result_b_f_temp != result_b_f && result_b_s_temp != result_b_s) {
         *result_b_temp += *result_b_f_temp - *result_b_s_temp;
           if(*result_b_temp < 0) {
               *result_b_temp += 10;
               *(result_b_temp - 1) -= 1;
           }
           result_b_temp--;
           result_b_f_temp--;
           result_b_s_temp--;
       }
       *result_b_temp += *result_b_f_temp - *result_b_s_temp;
       if(*result_b_temp < 0) {
         *result_b_temp += 10;
         *result_f_end -= 1;
        }
        result_f_temp = result_f_end;
        while(*result_f_temp < 0) {
           *result_f_temp += 10;
           *(result_f_temp - 1) -= 1;
           result_f_temp--;
      }
    }
    completing_calculation_for_minus(result_f, result_b, minus_flag, first, second, stack);
}

void plus(Node *first, Node *second, DLL *stack) {
    char *f_temp = first->f_end;
    char *s_temp = second->f_end;
    char *result_b_end = NULL;
    char *result_f_end = NULL;
    int minus_flag = 0;
    if(*first->f_start == -3 && *second->f_start != -3) { // ?åÏàò + ?ëÏàò
      first->f_start = first->f_start + 1;
      minus(second, first, 0, stack);
      return;
   }
   if(*first->f_start != -3 && *second->f_start == -3) { // ?ëÏàò + ?åÏàò
      second->f_start = second->f_start + 1;
      minus(first, second, 0, stack);
      return;
   }
    if(*first->f_start == -3 && *second->f_start == -3) { // ?????åÏàò?ºÎïå Ï≤òÎ¶¨
        first->f_start = first->f_start + 1;
        second->f_start = second->f_start + 1;
        minus_flag = 1;
    }
    char *result_f = (char *)malloc(SIZE_FRONT);
   char *result_f_temp = result_f;
    
   
   char *result_b = NULL;
    if(first->b_start != NULL || second->b_start != NULL) {
        result_b = (char *)malloc(SIZE_BACK);
    }
    char *result_b_temp = result_b;
    for(result_f_temp; result_f_temp < result_f + SIZE_FRONT; result_f_temp++) *result_f_temp = 0;
    result_f_temp--;
    result_f_end = result_f_temp;
    
   if(result_b != NULL) {
        for(result_b_temp; result_b_temp < result_b + SIZE_BACK  ; result_b_temp++) *result_b_temp = 0; // ?åÏàò?êÎèÑ ?àÏúºÎ©?Ï¥àÍ∏∞?îs
      result_b_end = result_b_temp;
      result_b_temp--;
    }
    
   
   while(f_temp != first->f_start && s_temp != second->f_start) {
      *result_f_temp += *f_temp + *s_temp;
        if(*result_f_temp >= 10) {
            *result_f_temp = *result_f_temp - 10;
            *(result_f_temp - 1) += 1;
        }
        result_f_temp--;
        f_temp--;
        s_temp--;
    }
    
   if(f_temp == first->f_start && s_temp != second->f_start) { // ?ïÏàòÎ∂ Î∂?Í≥ÑÏÇ∞
        *result_f_temp += *f_temp + *s_temp;
        if(*result_f_temp >= 10) {
            *result_f_temp = *result_f_temp - 10;
            *(result_f_temp - 1) += 1;
        }
        result_f_temp--;
        s_temp--;
        for(s_temp; s_temp != second->f_start ; s_temp--) {
           *result_f_temp += *s_temp;
            if(*result_f_temp >= 10) {
               *result_f_temp = *result_f_temp - 10;
               *(result_f_temp - 1) += 1;
           }
            result_f_temp--;
        }
        *result_f_temp += *s_temp;
    } else if(f_temp != first->f_start && s_temp == second->f_start) {
        *result_f_temp += *f_temp + *s_temp;
        if(*result_f_temp >= 10) {
            *result_f_temp = *result_f_temp - 10;
            *(result_f_temp - 1) += 1;
        }
        result_f_temp--;
        f_temp--;
        for(f_temp; f_temp != first->f_start ; f_temp--) {
            *result_f_temp += *f_temp;
            if(*result_f_temp >= 10) {
               *result_f_temp = *result_f_temp - 10;
               *(result_f_temp - 1) += 1;
           }
            result_f_temp--;
        }
       *result_f_temp += *f_temp;
    } else {
      *result_f_temp += *f_temp + *s_temp;
        if(*result_f_temp >= 10) {
            *result_f_temp = *result_f_temp - 10;
            *(result_f_temp - 1) += 1;
            result_f_temp--;
        }
    }
    
    
   if(result_b != NULL) {
      f_temp = first->b_end;
      s_temp = second->b_end;
   
      if(f_temp == NULL || s_temp == NULL) { // «œ≥™¥¬ ¡§ºˆ «œ≥™¥¬ º“ºˆ 
         while(result_b_temp != result_b) {
            *result_b_temp = (f_temp == NULL ? *s_temp : *f_temp);
            result_b_temp--;
            (f_temp == NULL ? s_temp-- : f_temp--);;
         }
         *result_b_temp = (f_temp == NULL ? *s_temp : *f_temp);
         completing_calculation(result_f, result_b, minus_flag, first, second, stack);
         return;
      }
      
      
      while(f_temp - first->b_start != s_temp - second->b_start) { //¿⁄∏¥ºˆ ∏¬√Á¡÷±‚ 
         if(first->b_end - first->b_start > second->b_end - second->b_start) {
            *result_b_temp += *f_temp;
         } else if(first->b_end - first->b_start < second->b_end - second->b_start) {
            *result_b_temp += *s_temp;
         }
         result_b_temp--;
         (first->b_end - first->b_start > second->b_end - second->b_start ? f_temp-- : s_temp--);
      }
   
      while(f_temp != first->b_start && s_temp != second->b_start) {
         *result_b_temp += *f_temp + *s_temp;
           if(*result_b_temp >= 10) {
               *result_b_temp = *result_b_temp - 10;
               *(result_b_temp - 1) += 1;
           }
           result_b_temp--;
           f_temp--;
           s_temp--;
       }
    
      if(f_temp == first->b_start && s_temp != second->b_start) { // ?ïÏàòÎ∂ Î∂?Í≥ÑÏÇ∞
           *result_b_temp += *f_temp + *s_temp;
           if(*result_b_temp >= 10) {
               *result_b_temp = *result_b_temp - 10;
               *(result_b_temp - 1) += 1;
           }
           result_b_temp--;
           s_temp--;
           for(s_temp; s_temp != second->b_start ; s_temp--) {
              *result_b_temp += *s_temp;
               if(*result_b_temp >= 10) {
                  *result_b_temp = *result_b_temp - 10;
                  *(result_b_temp - 1) += 1;
              }
               result_b_temp--;
           }
           *result_b_temp += *s_temp;
       } else if(f_temp != first->b_start && s_temp == second->b_start) {
           *result_b_temp += *f_temp + *s_temp;
           if(*result_b_temp >= 10) {
               *result_b_temp = *result_b_temp - 10;
               *(result_b_temp - 1) += 1;
           }
             result_b_temp--;
           f_temp--;
           for(f_temp; f_temp != first->b_start ; f_temp--) {
               *result_b_temp += *f_temp;
               if(*result_b_temp >= 10) {
                  *result_b_temp = *result_f_temp - 10;
                  *(result_b_temp - 1) += 1;
              }
               result_b_temp--;
           }
             *result_b_temp += *f_temp;
       } else {
         *result_b_temp += *f_temp + *s_temp;
           if(*result_b_temp >= 10) {
               *result_b_temp = *result_b_temp - 10;
               *result_f_end += 1;
           }
       }
       result_f_temp = result_f_end;
       while(result_f_temp != &result_f[2]) {
          if(*result_f_temp >= 10) {
             *result_f_temp -= 10;
             *(result_f_temp - 1) += 1;   
          }
          result_f_temp--;
       }
       if(*result_f_temp >= 10) {
          *result_f_temp -= 10;
          *(result_f_temp - 1) += 1;
         }
    }
    printf("%d %d %d %d \n", result_f[0], result_f[1], result_f[2], result_f[3]);
    completing_calculation(result_f, result_b, minus_flag, first, second, stack);
}

int main(void)
{
   printf("Welcome to infinite caculator!\n");
   char *ch;
   char ch_temp;
   char *i_start = NULL;
   char *temp = NULL;
   char *i_end = NULL;
   char *f_start;
   char *f_end;
   char *b_start;
   char *b_end;
   int b_flag = 0;
   FILE *ifp;
   DLL *list = newDLL();
   DLL *stack = newDLL();
   if((ifp = fopen("input.txt", "r")) == NULL) {
      printf("File Open Error!\n");
      return -1;
   }
   ch = (char *)malloc(sizeof(ifp));
   i_start = ch;
   temp = i_start;
   while((ch_temp = fgetc(ifp)) != EOF) { 
      ch_temp = ch_temp - '0';
      *temp = ch_temp;
      temp++;
   }
   i_end = temp-1;
   f_start = &ch[0];
   if(*f_start == -8) { // Îß?Ï≤òÏùå????Í¥ÑÌò∏?ºÎïå
      append(list, newnode(1, *f_start, 0, f_start, NULL, NULL, NULL));
      f_start = &ch[1];
   }
   for(char *k = i_start + 1; k < i_end; k++) {
      if(*k == -2) { //?åÏàò?êÏùÑ ÎßåÎÇ¨?ÑÎïå
         b_flag = 1;
         f_end = k - 1;
         b_start = k + 1;
      }
      if(k + 1 == i_end && b_flag == 0) { // ?ùÏóê ?ÑÎã¨?òÍ≥†, ?ïÏàò??Í≤ΩÏö∞
         if(*k == -7) { // ')'
             f_end = k - 1;
             append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //?´Ïûê 
             append(list, newnode(1, *k, 3, k, NULL, NULL, NULL)); //?§Î•∏ Í¥ÑÌò∏ 
             break;
         } else {
            f_end = k;
            append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //?´Ïûê 
            break;
         }
      }
      if(k + 1 == i_end && b_flag == 1) { // ?ùÏóê ?ÑÎã¨?òÍ≥†, ?åÏàò??Í≤ΩÏö∞
         if(*k == -7) {
             b_end = k - 1;
             append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); //?´Ïûê 
             append(list, newnode(1, *k, 3, k, NULL, NULL, NULL)); //?§Î•∏ Í¥ÑÌò∏
             break;
         } else {
            b_end = k;
            append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); // ?´Ïûê
            break;
         }
      }
      if(b_flag == 0) { // ?ïÏàò??Í≤ΩÏö∞
         if(*k == -5 || *k == -3 || *k == -6 || *k == -1) { // ?∞ÏÇ∞?êÎ? ÎßåÎÇú Í≤ΩÏö∞
            f_end = k - 1;
            if(*(k - 1) == -7 && *(k + 1) == -8) { // ')' '+' '('
               f_end = k - 2;
               append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //number??
               append(list, newnode(1, *(k - 1), 0,  k - 1, NULL, NULL, NULL)); // '('
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               append(list, newnode(1, *(k + 1), 3,  k + 1, NULL, NULL, NULL)); // ')'
               f_start = k + 2;
               if(*(k + 2) == -3) { //for '-'
                  k = k + 2;
                  continue;
               }
            } else if( *(k - 1) != -7 && *(k + 1) == -8) { // number '+' '('
               append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //number
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               append(list, newnode(1, *(k + 1), 0, k + 1, NULL, NULL, NULL)); //'('
               f_start = k + 2;
               if(*(k + 2) == -3) { //  for '-' 
                  k = k + 2;
                  continue;
               }
            } else if(*(k - 1) == -7 && *(k + 1) != -8) { //')' '+'
               f_end = k - 2;
               append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //number
               append(list, newnode(1, *(k - 1), 3, k - 1, NULL, NULL, NULL)); //')'
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               f_start = k + 1;
            } else {
               append(list, newnode(0, 0, 0, f_start, f_end, NULL, NULL)); //number
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               f_start = k + 1;
            }
         }
      } else {
         if(*k == -5 || *k == -3 || *k == -6 || *k == -1) { //?∞ÏÇ∞?êÎ? ÎßåÎÇú Í≤ΩÏö∞
            b_end = k - 1;
            if(*(k - 1) == -7 && *(k + 1) == -8) { // ')' '+' '('
               b_end = k - 2;
               append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); //number
               append(list, newnode(1, *(k - 1), 0, k - 1, NULL, NULL, NULL)); // '('
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               append(list, newnode(1, *(k + 1), 3, k + 1, NULL, NULL, NULL)); // ')'
               f_start = k + 2;
               if(*(k + 2) == -3) { //for '-'
                  k = k + 2;
                  continue;
               }
            } else if( *(k - 1) != -7 && *(k + 1) == -8) { // number '+' '('
               append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); //number
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               append(list, newnode(1, *(k + 1), 0, k + 1, NULL, NULL, NULL)); //'('
               f_start = k + 2;
               if(*(k + 2) == -3) { //for '-'
                  k = k + 2;
                  b_flag = 0;
                  continue;
               }
            } else if(*(k - 1) == -7 && *(k + 1) != -8) { //')' '+'
               b_end = k - 2;
               append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); //number
               append(list, newnode(1, *(k - 1), 3, k - 1, NULL, NULL, NULL)); //')'
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               f_start = k + 1;
            } else {
               append(list, newnode(0, 0, 0, f_start, f_end, b_start, b_end)); //number
               if(*k == -5) append(list, newnode(1, 1, 1, k, NULL, NULL, NULL)); // '+'operator
               if(*k == -3) append(list, newnode(1, 2, 1, k, NULL, NULL, NULL)); // '-'operator
               if(*k == -6) append(list, newnode(1, 4, 2, k, NULL, NULL, NULL)); // '*'operator
               if(*k == -1) append(list, newnode(1, 5, 2, k, NULL, NULL, NULL)); // '/'operator
               f_start = k + 1;
            }
            b_flag = 0;
         }
      }
   }
   //print(list);
   infix_to_postfix(list, stack);
   //print(stack);
   Node *temp_stack = stack->head;
   while(temp_stack) {
      if(temp_stack->op == 1 ) { 
         plus(temp_stack->prev->prev, temp_stack->prev, stack);
         //temp_stack = stack->head;
      }
      else if(temp_stack->op == 2) {
         minus(temp_stack->prev->prev, temp_stack->prev, 0, stack);
         //temp_stack = stack->head;
      }
      else if(temp_stack->op == 4){
             multiple(temp_stack->prev->prev, temp_stack->prev, 0, stack);
             printf("multiple\n");
        }
      //else divide(temp->prev, temp->prev->prev);
      temp_stack = temp_stack->next;
   } 
   print(stack);
   
   return 0;
}   
