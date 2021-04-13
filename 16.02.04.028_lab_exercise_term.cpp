#include<bits/stdc++.h>

using namespace std;

char str[10005];
int i = 0, f = 0, l;

void Exp();
void term();
void factor();
void id();
void num();

void Exp() {
    term();
    if (f == 1 && (str[i] == '+' || str[i] == '-')) {
        i++;
        term();
    }
}
void term() {
    factor();
    if (f == 1 && (str[i] == '*' || str[i] == '/')) {
        i++;
        f = 1;
        factor();
    }
}

void id() {
    if (str[i] >= 'a' && str[i] <= 'e') {
        i++;
        f = 1;
    } else {
        f = 0;
    }
}

void num() {
    if (str[i] >= '0' && str[i] <= '9') {
        i++;
        f = 1;
    } else {
        f = 0;
    }
}

void factor() {
    id();
    if (f == 0) {
        num();
    }
    if (f == 1) {
        f = 1;
        return ;
    } else if (str[i] == '(') {
        i++;
        Exp();
        if (f == 1 && str[i] == ')') {
            f = 1;
            i++;
            return ;
        } else {
            f = 0;
            return ;
        }
    } else {
        f = 0;
        return ;
    }
}
int main() {
    gets(str);
    l = strlen(str);
    Exp();
    if (f == 1 && i == l) {
        puts("accepted\n");
    } else {
        puts("rejected\n");
    }
    return 0;
}
