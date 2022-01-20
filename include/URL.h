#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>

#define CUSTOM_SEARCH_ENGINE_URL "https://customsearch.googleapis.com/customsearch/v1?"

char * Build_Url(char * querry);
void error(char * msg, int code);