#include <stdio.h>

int parseBrainfuck(char[]);
int parseToken(char*, int**, char[], int*);

int main(int argc, char** argv) {
    FILE *fp;
    char buff[255];

    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);
    fclose(fp);

    parseBrainfuck(buff);

    return 0;
}

int parseBrainfuck(char buff[]) {
    int bfMemory[256] = { [ 0 ... 255 ] = 0 };
    int* bfMemoryPt = bfMemory;

    for (int i = 0; buff[i] != '\0'; i++) {
        parseToken(&buff[i], &bfMemoryPt, buff, &i);
        if (buff[i] == ']') { 
            if (*bfMemoryPt != 0) {
                while (buff[i] != ']') {
                    i = i - 1;
                }
            }
        }
    }

    return 1;
}

int parseToken(char* token, int** memPt, char* buffer, int* indexPt) {
    if (*token == '+') {
        **memPt = **memPt + 1;
    } else if (*token == '-') {
        **memPt = **memPt - 1;
    } else if (*token == '>') {
        ++(*memPt);
    } else if (*token == '<') {
        --(*memPt);
    } else if (*token == '.') {
        char c = **memPt;
        printf("%c", c);
    } else if (*token == '[') {
        if (**memPt != 0) {
            int increases = 1;
            *indexPt = *indexPt + 1;
            while (buffer[*indexPt] != ']') {
                parseToken(&buffer[*indexPt], memPt, buffer, indexPt);
                *indexPt = *indexPt + 1;
                increases = increases + 1;
            }
            *indexPt = *indexPt - increases - 1;

        } else {
            while (buffer[*indexPt] != ']') {
                *indexPt = *indexPt + 1;
            }
        }
    }

    return 1;
}