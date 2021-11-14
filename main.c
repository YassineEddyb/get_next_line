

#include<stdlib.h>
#include<strings.h>

char *f(char *s)
{
    static char *str;

    str = malloc(6);
    strlcat(str, s, 6);
    return (str);
}

int main ()
{
    char s[] = "test test2      test3 test4" ' ';
    int i = -1;
    while(++i < 6)
        printf("%s", f(s));
}
