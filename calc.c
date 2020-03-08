#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

double compute_rpn(char* rpn){
  char *tok;
  struct stack* s = create_stack();
  while ((tok = strtok_r(rpn, " ", &rpn))){
    if (!(unary_op(*tok)) && !(binary_op(*tok))){
      push(s, atof(tok));
    }
    else if (binary_op(*tok)){
      double i = pop(s);
      float temp = (float)i;
      float k;
      switch (*tok){
        case '+':s -> top -> value += temp;
          break;
        case '-':s -> top -> value -= temp;
          break;
        case '*':s -> top -> value *= temp;
          break;
        case '/':s -> top -> value /= temp;
          break;
        case '^':s -> top -> value = pow(s -> top -> value, temp);
          break;
        case 'f':k = s -> top -> value;
          s -> top -> value = temp;
          temp = k;
          push(s, k);
          break;
        default:printf("error");
          break;
      }
    }
    else if (unary_op(*tok)){
      switch(*tok){
        case 's':s -> top -> value = sin(s -> top -> value);
          break;
        case 'c':s -> top -> value = cos(s -> top -> value);
          break;
        case 't':s -> top -> value = tan(s -> top -> value);
          break;
        case 'e':s -> top -> value = exp(s -> top -> value);
          break;
        case 'i':s -> top -> value = 1/(s -> top -> value);
          break;
        case 'm':s -> top -> value = -1*(s -> top -> value);
          break;
        case 'r':s -> top -> value = sqrt(s -> top -> value);
          break;
        default: printf("ERROR");
          break;
      }
    }
  }
  double q = s -> top -> value;
  delete_stack(s);
  return q;
}
char* get_expressions(char* filename){
  FILE *fp;
  long lSize;
  char *buffer;

  fp = fopen (filename , "r" );

  fseek(fp , 0L , SEEK_END);
  lSize = ftell(fp);
  rewind(fp);

  buffer = malloc(lSize+1);
  fread(buffer, lSize, 1, fp);
  fclose(fp);
  return buffer;
  free(buffer);
}

void process_expressions(char* expressions, char* filename){
  char* tok;
  FILE* out = fopen(filename, "w");

  while ((tok = strtok_r(expressions, "\n", &expressions))){
    double a = compute_rpn(tok);
    printf("%f\n", a);
  }
  fclose(out);
}
