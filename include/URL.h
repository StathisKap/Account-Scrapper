#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <stdint.h>

#define CUSTOM_SEARCH_ENGINE_URL "https://customsearch.googleapis.com/customsearch/v1?"

typedef struct {
    char *name;
    time_t time;
    char *full_path;
} Search;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
char * Build_Url(char * querry, char * start);
void error(char * msg, int code);
char * isDirectoryEmpty(char *dirname);
int Parse_For_Count(char *filename);