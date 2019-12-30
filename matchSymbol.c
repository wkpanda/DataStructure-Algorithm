#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* s){
    if(!s|| s[0] == ' ')
    {
        return 1;
    }
    char* stk = (char*)malloc(strlen(s));
    int top = -1;
    int i;
    for(i=0;s[i]!='\0';i++)
    {
        switch (s[i]) {
            case '(':
            case '[':
            case '{':
                stk[++top] = s[i];
                break;
            case ')':
                if (top < 0 || stk[top--] != '(')
                    return 0;
                break;
            case ']':
                if (top < 0 || stk[top--] != '[')
                    return 0;
                break;
            case '}':
                if (top < 0 || stk[top--] != '{')
                    return 0;
                break;
        }
    }
    if(top>=0)
        return 0;
    return 1;
}

int main() {
    char a[1001];
    scanf("%s",&a[1001]);
    if(isValid(a))
        printf("true");
    else
        printf("false");

    return 0;
}