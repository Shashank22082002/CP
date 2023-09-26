#include <stdio.h>

int main()
{
    FILE* fp = fopen("new.txt", "w");
    for (int i = 0; i < 200000; ++i)
        fprintf(fp, "%s", "D");
    return 0;
}