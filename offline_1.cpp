/*
Name:Mayisha Farzana    ID:160204028
Section:A1              Assignment:01

*/

#include<bits/stdc++.h>
const int N = 100005;
char inp[N + 5];
bool is_keyword(char ar[]){
		if (strcmp(ar, "int") == 0){
			return true;
		}
		if (strcmp(ar, "return") == 0){
			return true;
		}
		if (strcmp(ar, "float") == 0){
			return true;
		}
		if (strcmp(ar, "double") == 0){
			return true;
		}if (strcmp(ar, "long") == 0){
			return true;
		}
		return false;
}
int main(){
	FILE *input_file = fopen("input.c", "r");
	FILE *out_file = fopen("output.c", "w");
	char c;
	int i = 0;
	while ((c = fgetc(input_file)) != EOF){
		inp[i] = c;
		i++;
	}
	inp[i] = '\0';
	char init[N + 5];
	strcpy(init, inp);
	char modify[N + 5];
	int flag = 0;
	int ind = 0;
	for (int i = 0; i < (int) strlen(inp); i++){
		if (inp[i] == '/' && inp[i + 1] == '/'){
			flag = 1;
		}
		if (flag == 0){
			modify[ind] = inp[i];
			ind++;
		}
		if (inp[i] == '\n'){
			flag = 0;
		}
	}
	modify[ind] = '\0';
	strcpy(inp, modify);
	int cnt = 0;
	ind = 0;
	for (int i = 0; i < (int) strlen(inp); i++){
		if (inp[i] == '/' && inp[i + 1] == '*'){
			cnt++;
		}
		if (cnt == 0){
			modify[ind] = inp[i];
			ind++;
		}
		if (inp[i] == '/' && inp[i - 1] == '*'){
			cnt--;
		}
	}
	modify[ind] = '\0';
	strcpy(inp, modify);
	ind = 0;
	char token[1000];
	for (int i = 0; i < (int)strlen(inp); i++){
		while (i < (int)strlen(inp) && inp[i] == ' '){
			i++;
		}
		int ti = 0;
		while (i < (int)strlen(inp) && inp[i] != ' ' && inp[i] != '\n'){
			token[ti++] = inp[i];
			i++;
		}
		token[ti] = '\0';
		for (int j = 0; j < (int) strlen(token); j++){
			modify[ind++] = token[j];
		}
		if (is_keyword(token) ){
			modify[ind++] = ' ';
		}
	}
	modify[ind] = '\0';
	strcpy(inp, modify);

	fprintf(out_file, "Actual source:\n\n");
	fprintf(out_file, "%s\n\n", init);
	fprintf(out_file, "Modified source:\n\n");
	fprintf(out_file, "%s\n", inp);
	return 0;
}
