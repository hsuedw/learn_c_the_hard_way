#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>
#include "dbg.h"

#define AND (1)
#define OR  (2)
#define MAX_FILENAME (128)
#define MAX_FILE_SZ  (40960)

void usage()
{
    printf("logfind [-o] keyword1 keyword2 ...\n");
}

void free_keywords(char **keywords, int num_keywords)
{
    if (keywords == NULL || num_keywords == 0) {
        return;
    }
    for (int i = 0; i < num_keywords; ++i) {
        if (*(keywords + i) != NULL) {
            free(*(keywords + i));
	}
    }
    free(keywords);
}

int main(int argc, char *argv[])
{
    // parse the argments from command line
    if (argc < 2) {
        usage();
	return -1;
    }

    // argc >= 2 is true.
    int logic_flag = AND;
    if (strlen(argv[1]) == 2 && argv[1][0] == '-') {
        if (strncmp(argv[1], "-o", 2) == 0) {
            logic_flag = OR;
            if (argc < 3) {
                usage();
                return -2;
            }
	} else {
            usage();
            return -3;
	}
    }

    char **keywords = NULL;
    int argi = logic_flag == AND ? 1 : 2;
    int num_keywords = argc - argi;
    keywords = calloc(num_keywords, sizeof(char*));
    check(keywords != NULL, "");
    for (int i = 0; i < num_keywords; ++i, ++argi) {
        *(keywords + i) = strdup(*(argv + argi));
    }

#if 0
    for (int i = 0; i < num_keywords; ++i) {
        printf("%s\n", *(keywords + i));
    }
    if (logic_flag == AND) {
        printf("AND\n");
    } else {
        printf("OR\n");
    }
#endif

    // check if the .logfind exists
    FILE *cfgp = fopen("./.logfind", "r");
    check(cfgp != NULL, ".logfind doesn't exist!");

    // read the .logfind from current directory
    char pattern[MAX_FILENAME];
    while (fgets(pattern, MAX_FILENAME, cfgp) != NULL) {
        pattern[strlen(pattern) - 1] = '\0';

        glob_t gl;
        glob(pattern, GLOB_TILDE, NULL, &gl);
        for (int i = 0; i < gl.gl_pathc; ++i) {
            FILE *fp = fopen(gl.gl_pathv[i], "r");
	    char file_data[MAX_FILE_SZ];
	    memset(file_data, 0, MAX_FILE_SZ);
            while (fgets(file_data + strlen(file_data), MAX_FILE_SZ, fp) != NULL)
		    ;
	    fclose(fp);
                
            int foundKeywords = 0;
            char *pos = file_data;
            for (int k = 0; k < num_keywords; ++k) {
                if (strstr(pos, *(keywords + k)) != NULL) {
                    ++foundKeywords;
		}
            }

	    if ((logic_flag == AND && foundKeywords == num_keywords) ||
                (logic_flag == OR && foundKeywords > 0)) {
                printf("%s\n", gl.gl_pathv[i]);
	    }
        } // end of for-loop
        globfree(&gl);
    } // end of while-loop

    fclose(cfgp);

    free_keywords(keywords, num_keywords);
    return 0;

error:
    if (keywords != NULL) {
        free_keywords(keywords, num_keywords);
    }

    if (cfgp != NULL) {
        fclose(cfgp);
    }
    return -10;
}
