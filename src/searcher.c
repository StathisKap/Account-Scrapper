#include "../include/URL.h"
CURL *curl;


int main(int argc, char ** argv)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  curl = curl_easy_init();
   curl_global_init(CURL_GLOBAL_ALL);
  CURLcode res;
  struct curl_slist *Custom_Headers = NULL;
  char *url = Build_Url("\"@\" Brighton Caitlin");
  char *Json_Name = malloc(255);
  sprintf(Json_Name,"%s-%d-%02d-%02d %02d:%02d:%02d%s","./Searches/Google_Search", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,".json");
  FILE *json = fopen(Json_Name,"wb");
  printf("%s\n\n",Json_Name);
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
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, write_data);
    if(json)
      curl_easy_setopt(curl, CURLOPT_WRITEDATA,(void*)json);
    else
      error("File didn't open",2);

    res = curl_easy_perform(curl);
    
    if (res ==0)
      printf("Perform was Successful\nRES: %d\n",res);
    else
      printf("Perform was NOT Successful\nRES: %d\n",res);
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();
  }
  else
  {
    free(url);
    fclose(json);
    error("Curl is NOT installed", 1);
  }
  
  free(url);
  fclose(json);
  curl_slist_free_all(Custom_Headers);
  return 0;
}