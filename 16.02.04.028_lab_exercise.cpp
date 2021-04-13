#include<bits/stdc++.h>
using namespace std;
char str[10005];
int i = 0, f = 0, l;

void A();
void X();

void A() {
    if (str[i] == 'a') {
        i++;
        X();
        if (f == 1 && str[i] == 'd') {
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
void X() {
    if (str[i] == 'b') {
        i++;
        if (str[i] == 'b') {
            i++;
            f = 1;
        } else if (str[i] == 'c') {
            i++;
            f = 1;
        } else {
            f = 0;
            return ;
        }
    } else {
        f = 1;
        return ;
    }
    if (f == 1 && i + 1 < l) {
        X();
    }
}
int main() {
    gets(str);
    l = strlen(str);
    A();
    if (f == 1 && i == l) {
        puts("accepted\n");
    } else {
        puts("rejected\n");
    }
    return 0;
}


