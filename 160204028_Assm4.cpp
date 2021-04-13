/***
*   author:   Mayisha Farzana
*    ID:160204028
***/
#include<bits/stdc++.h>
const int N = 555;
char lines[N + 5][N + 5];
char tmp[N + 5][N + 5];
int n;
void remove_comment()
{
    FILE *out_file = fopen("out", "w");
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        int ind = 0;
        for (int j = 0; j < (int) strlen(lines[i]); j++)
        {
            if (j + 1 < (int) strlen(lines[i]) && lines[i][j] == '/' && lines[i][j + 1] == '/')
            {
                tmp[i][ind] = '\n';
                ind++;
                tmp[i][ind] = '\0';
                break;
            }
            if (j + 1 < (int) strlen(lines[i]) && lines[i][j] == '/' && lines[i][j + 1] == '*')
            {
                cnt++;
            }
            if (cnt == 0)
            {
                tmp[i][ind] = lines[i][j];
                ind++;
            }
            if (j - 1 >= 0 && lines[i][j] == '/' && lines[i][j - 1] == '*')
            {
                cnt--;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(out_file, "%d %s", i + 1, tmp[i]);
        strcpy(lines[i], tmp[i]);
    }
}

void check_braces()
{
    int open = 0;
    bool mis[100];
    for (int i = 0; i < 100; i++)
    {
        mis[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int) strlen(lines[i]); j++)
        {
            if (lines[i][j] == '{')
            {
                open++;
            }
            else if(lines[i][j] == '}')
            {
                open--;
                if (open < 0)
                {
                    mis[i] = true;
                }
            }
        }
    }
    if (open != 0)
    {
        puts("braces not matched\n");
    }
    for (int i = 0; i < 100; i++)
    {
        if (mis[i])
        {
            printf("Misplaced } at line %d\n", i + 1);
        }
    }
}
void unmached_keyword()
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        bool err = false;
        for (int j = 0; j < (int) strlen(lines[i]); j++)
        {
            if ((int) j + 1 < (int) strlen(lines[i]) && lines[i][j] == 'i' && lines[i][j + 1] == 'f')
            {
                cnt++;
            }
            if (j + 3 < (int) strlen(lines[i]) && lines[i][j] == 'e' && lines[i][j + 1] == 'l' &&
                    lines[i][j + 2] == 's' && lines[i][j + 3] == 'e')
            {
                cnt--;
                if (cnt < 0)
                {
                    err = true;
                }
            }
        }
        if (err)
        {
            printf("Unmatched else at line %d", i + 1);
        }
    }
}

int main()
{
    FILE *in_file = fopen("in", "r");
    n = 0;
    while (fgets(lines[n], N, in_file) != NULL)
    {
        n++;
    }
    fclose(in_file);
    remove_comment();
    check_braces();
    unmached_keyword();
    return 0;
}
