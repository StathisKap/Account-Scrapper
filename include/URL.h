#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>
#include <time.h>

#define CUSTOM_SEARCH_ENGINE_URL "https://customsearch.googleapis.com/customsearch/v1?"

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
char * Build_Url(char * querry, char *start	);
void error(char * msg, int code);
