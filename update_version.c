#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    const char s[2] = ".";
    char *token;
    unsigned int version[3];
    unsigned short int i = 0;
    int count = 0;

    fp = fopen("current_version.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        /* get the first token */
        token = strtok(line, s);

        /* walk through other tokens */
        while (token != NULL)
        {
            version[i] = atoi(token);
            i++;
            token = strtok(NULL, s);
        }
    }
    fclose(fp);
    if (line)
        free(line);
    line = NULL;
    len = 0;

    fp = fopen("current_version.txt", "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    printf("%d\n", version[2]);
    version[2] = version[2] + 1;
    printf("%d\n", version[2]);
    fprintf(fp, "%u.%u.%u", version[0], version[1], version[2]);
    fclose(fp);

    i = 0;
    fp = fopen("include/version.h", "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    fprintf(fp, "#ifndef _VERSION_H\n");
    fprintf(fp, "#define _VERSION_H 1\n\n");
    for (i = 0; i < 3; i++)
    {
        fprintf(fp, "#define V%d %u\n", i + 1, version[i]);
    }
    fprintf(fp, "\n#endif");

    return 0;
}