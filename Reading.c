#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char * explorer=NULL;

    fp = fopen("./Dummy.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);				
		if ((explorer = strsep(&line, "|")) != NULL){
			printf("%s\n", explorer);
			explorer = strsep(&line, "|");
		}
		while( (explorer = strsep(&line,"|")) != NULL )	{
	        printf("%s\n",explorer);
		}
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
