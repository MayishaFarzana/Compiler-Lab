#include<bits/stdc++.h>

using namespace std;

const int N = 10005;
char inp[N + 5];

struct symbol{
  int sl_no;
  char name[100];
  char id_type[100];
  char data_type[100];
  char scope[100];
  char value[100];
};

symbol table[10000];
int curr_pos = 0;

char scope[100][100];
int scope_id = 0;

void rev(char ar[]){
  int i = 0;
  int j = strlen(ar) - 1;
  while (i < j){
    swap(ar[i], ar[j]);
    i++;
    j--;
  }
}

bool digit(char c){
  return (c >= '0' && c <= '9') || (c == '.');
}

bool ok(char ar[]){
  for (int i = 0; i < strlen(ar); i++){
    if (!digit(ar[i])){
      return false;
    }
  }
  return true;
}

char * top() {
  if (scope_id == 0){
    return "null";
  }
  return scope[scope_id - 1];
}

void pop() {
  scope_id--;
}

void push(char inp[]){
  strcpy(scope[scope_id], inp);
  scope_id++;
}

int Search(symbol ar){
  for (int i = 0; i < curr_pos; i++){
    if (strcmp(table[i].name, ar.name) == 0 && strcmp(table[i].scope, ar.scope) == 0){
      return i;
    }
  }
  return -1;
}

void insert(symbol ar){
  if (Search(ar) != -1){
    puts("");
    return ;
  }
  table[curr_pos] = ar;
  curr_pos++;
}

void Delete(symbol ar){
  int pos = Search(ar);
  if (pos == -1){
    return ;
  }
  for (int i = pos + 1; i < curr_pos; i++){
    table[i - 1] = table[i];
  }
  curr_pos--;
}

void update(symbol ar){
  int pos = Search(ar);
  if (pos == -1){
    insert(ar);
  } else {
    if ((int) strlen(ar.value) > 0 && ok(ar.value)){
      strcpy(table[pos].value, ar.value);
    }
  }
}


void Display(){
  for (int i = 0; i < curr_pos; i++){
    printf("%2d %10s %10s %10s %10s %10s\n", i + 1, table[i].name, table[i].id_type, table[i].data_type, table[i].scope, table[i].value);
  }
  puts("");
  puts("");
}

void step_1(){
  FILE *fp = fopen("tmp.c", "w");
  int n = strlen(inp);
  for (int i = 0; i < n; i++){
    while (inp[i] == ' '){   // surur white space gula ignore koro
      i++;
    }
    char token[100];
    int ind = 0;
    while (inp[i] != ' '){         // ebare space er ager tuku read kore token a store koro ex: [kw , [id,  [sep  esob store hobe token er vetore
      token[ind] = inp[i];
      ind++;
      i++;
    }
    token[ind] = '\0';
    i++;
    fprintf(fp, "[");
    if (strcmp(token, "[id") == 0){      // ebare token a id thakle oita o print kore dite hobe age
      fprintf(fp, "%s ", token + 1);
    }
    while (inp[i] != ']'){            // R porer part tuku sob somoy e print hobe
      fprintf(fp, "%c", inp[i]);
      i++;
    }
    fprintf(fp, "]");
  }
  fprintf(fp, "\n");
  fclose(fp);
}

void step_2(){
  push("global");
  FILE *fp = fopen("tmp.c", "r");
  char ar[N + 5];
  char c;
  int i = 0;
  while ((c = getc(fp)) != EOF){
    ar[i++] = c;
  }
  ar[i] = '\0';
  int n = strlen(ar);
  char prev[1000];
  for (i = 0; i < n; i++){
    while (ar[i] == ' '){
      i++;
    }
    char token[1005];
    int ind = 0;
    while (ar[i] != ']'){
      token[ind++] = ar[i];
      i++;
    }
    token[ind] = '\0';
    int len = strlen(token);
    if (token[1] == '}'){
      pop();
    }
    if (len > 2 && token[0] == '[' && token[1] == 'i' && token[2] == 'd' && i + 2 < n && ar[i + 2] == '('){
      symbol sym;
      char act[100];
      int x = 0;
      for (int k = 4; k < (int) strlen(token); k++){
        act[x++] = token[k];
      }
      act[x] = '\0';
      strcpy(sym.name, act);
      strcpy(sym.scope, top());
      strcpy(sym.id_type, "func");


      if (strcmp(prev, "[int") == 0 || strcmp(prev, "[float") == 0 || strcmp(prev, "[double") == 0) {
        char av[100];
        for (int i = 1; i < (int) strlen(prev); i++){
          av[i - 1] = prev[i];
        }
        av[(int) strlen(prev) - 1] = '\0';
        strcpy(sym.data_type, av);
      }

      push(act);
      update(sym);

    } else if (len > 2 && token[0] == '[' && token[1] == 'i' && token[2] == 'd'){
      char val[1000];
      int pt = 0;
      symbol sym;
      strcpy(sym.value, "");
      if (ar[i + 2] == '=') {
        for (int k = i + 5; k < n && ar[k] != ']'; k++){
          val[pt++] = ar[k];
        }
        val[pt] = '\0';
        strcpy(sym.value, val);
      }
      char act[100];
      int x = 0;
      for (int k = 4; k < (int) strlen(token); k++){
        act[x++] = token[k];
      }
      act[x] = '\0';
      strcpy(sym.name, act);
      strcpy(sym.scope, top());
      strcpy(sym.id_type, "var");
      if (strcmp(prev, "[int") == 0 || strcmp(prev, "[float") == 0 || strcmp(prev, "[double") == 0) {
        char av[100];
        for (int i = 1; i < (int) strlen(prev); i++){
          av[i - 1] = prev[i];
        }
        av[(int) strlen(prev) - 1] = '\0';
        strcpy(sym.data_type, av);
      }
      update(sym);
    }
    strcpy(prev, token);
  }
  Display();
}

int main(){
  FILE *in_file = fopen("in", "r");
  int i = 0;
  char c;
  while ((c = getc(in_file)) != EOF){
    inp[i] = c;
    i++;
  }
  inp[i] = '\0';
  step_1();
  step_2();
  return 0;
}
