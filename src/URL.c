#include "../include/URL.h"
#include "../include/secrets.h" //Contains Key and cx

extern CURL *curl;


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

char * Build_Url(char * querry)
{
  char *url = malloc(1024);

  sprintf(url,"%s%s%s%s%s",                         \
      CUSTOM_SEARCH_ENGINE_URL,                     \
      Custom_Search_Engine_cx,                      \
      "&q=",                                        \
      curl_easy_escape(curl,querry,strlen(querry)), \
      Custom_Search_Engine_Key                      \
      );

  return url;
}

void error(char * msg, int code)
{
  fprintf(stderr, "%s: %s\n",msg, strerror(errno));
  exit(code);
}