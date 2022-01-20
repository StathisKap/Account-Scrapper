#include "../include/URL.h"

CURL *curl;

int main(int argc, char ** argv)
{
  curl = curl_easy_init();
  CURLcode res;
  struct curl_slist *Custom_Headers = NULL;
  char *url = Build_Url("\"@\" Brighton Caitlin");
  printf("%s\n\n",url);


  if(curl){
    puts("Curl is installed");
    Custom_Headers = curl_slist_append(Custom_Headers, "Accept: application/json");

    curl_easy_setopt(curl,CURLOPT_HTTPHEADER, Custom_Headers); 
    curl_easy_setopt(curl,CURLOPT_URL, url);
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION, 1L); 
    curl_easy_setopt(curl,CURLOPT_TRANSFER_ENCODING, 1L); 
    curl_easy_setopt(curl,CURLOPT_VERBOSE, 1L); 
    curl_easy_setopt(curl,CURLOPT_USERAGENT, "Curl-Agent");
    res = curl_easy_perform(curl);
    
    if (res ==0)
      printf("Perform was Successful\nRES: %d\n",res);
    else
      printf("Perform was NOT Successful\nRES: %d\n",res);
    
    curl_easy_cleanup(curl);
  }
  else
  {
    free(url);
    error("Curl is NOT installed", 1);
  }
  
  free(url);
  curl_slist_free_all(Custom_Headers);
  return 0;
}
