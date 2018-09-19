/*
    Name:   Josh Heyer
    Email:  joshuaray83@gmail.com


    Function: This program takes in a paragraph or paragraphs and formats
    its line length based on a number inputted by the user.
    It then reads each word in the paragraph(s) using spaces as boundries
    and alphabatizes them, also counting how many times each word is
    read. It then outputs the formatted paragraph and the alphabatized list
    of words and their corresponding times used.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define buffSize 100

int strcasecmp (const char *, const char *);
char *strdup(const char *string);

char* concatinate (const char *w, const char *v) {

    char *conWord = malloc (strlen(w) + strlen(v) + 1);
    strcpy (conWord, w);
    strcat (conWord, v);
    return conWord;
}

int comp (const void *a, const void *b) {

    const char **aa = (const char **)a;
    const char **bb = (const char **)b;
    if (strcasecmp(*aa, *bb)) {
        return strcasecmp(*aa, *bb);
    }
    return strcmp (*aa, *bb);
}

int main (int argc, char* argv[]) {

    int lineLength = 0; int line = 0; int x; int numWords = 0; int y = 1;
    long length;
    char *tok; char *len;
    char buff[buffSize];
    FILE *inputFile; FILE *outputFile; FILE *outputWords;
    char **wordList = malloc(sizeof(char*));
    char *buf1; char *buf2;
    char *out = ".out"; char *words = ".words";

    if (argc != 3) {
        printf ("Error: Incorrect number of arguments. Program terminated.\n");
        exit(0);
    }
    length = strtol(argv[1], &len, 10);
    if (errno != 0 || *len != '\0' || length > INT_MAX) {
        printf ("Error: The character length was not a number or was too long\n");
        exit(0);
    }
    else {
        lineLength = length;
    }

    if (lineLength < 25) {
        printf ("Error: %d characters per line is too small. Program terminated.\n", lineLength);
        exit(0);
    }
    if (lineLength > 100) {
        printf ("Error: %d characters per line is too large. Program terminated.\n", lineLength);
        exit(0);
    }

    inputFile = fopen(argv[2], "r");

    buf1 = concatinate(argv[2], out);
    buf2 = concatinate(argv[2], words);

    outputFile = fopen(buf1, "w");
    outputWords = fopen(buf2, "w");

    if (inputFile == 0) {
        printf ("Could not find file. Program terminated.\n");
    }
    else {
        line = 0;
        while (fscanf(inputFile, "%100s", buff) == 1) {
            line += strlen(buff);
            if (line >= lineLength) {
                putc('\n', outputFile);
                line = 0 + strlen(buff);
            }
            tok = strtok(buff, " ");
            wordList = realloc(wordList, (numWords + 1) * sizeof(char*));
            wordList[numWords] = strdup(tok);
            numWords++;
            fputs(buff, outputFile);
            fputc(' ', outputFile);
            line++;
            tok = NULL;
        }
       
        qsort(wordList, numWords, sizeof(char*), &comp);

        for (x = 0; x < numWords - 1; x++) {
            if (strcmp(wordList[x], wordList[x + 1]) == 0) {
                y++;
            }
            else {
                fprintf(outputWords, "%s\t - %d\n", wordList[x], y);
                y = 1;
            }
        }
    }
    
    fclose(inputFile);
    fclose(outputFile);
    fclose(outputWords);
    return 0;
}
