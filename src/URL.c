#include "../include/URL.h"
#include "../include/secrets.h" //Contains Key and cx

extern CURL *curl;
void error(char * msg, int code)
{
  fprintf(stderr, "%s: %s\n",msg, strerror(errno));
  exit(code);
}

char * Build_Url(char * querry)
{
  char *url = malloc(1024);

  sprintf(url,"%s%s%s%s%s",                           \
      CUSTOM_SEARCH_ENGINE_URL,                     \
      Custom_Search_Engine_cx,                      \
      "&q=",                                        \
      curl_easy_escape(curl,querry,strlen(querry)), \
      Custom_Search_Engine_Key                      \
      );

  return url;
}