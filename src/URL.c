#include "../include/URL.h"
#include "../include/secrets.h" //Contains Key and cx

extern CURL *curl;


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

char * Build_Url(char * querry, char * start)
{
  char *url = malloc(1024);
  char start[50];
  char *file_name;
  strcpy(start,"&start=");
  if((file_name = isDirectoryEmpty("Searches")) == NULL)
    printf("Directory is NOT empty\nLatest File: %s\n",file_name);
  else{
    strcat(start,"1");
    printf("Directory is Empty\n");
  }

  char start_count[50];
  sprintf(start_count,"&start=%d",atoi(start));

  sprintf(url,"%s%s%s%s%s%s",                         \
      CUSTOM_SEARCH_ENGINE_URL,                     \
      Custom_Search_Engine_cx,                      \
      "&q=",                                        \
      curl_easy_escape(curl,querry,strlen(querry)), \
      "&start=101",
      start_count,
      Custom_Search_Engine_Key                      \
      );
  

  return url;
}

void error(char * msg, int code)
{
  fprintf(stderr, "%s: %s\n",msg, strerror(errno));
  exit(code);
}

char * isDirectoryEmpty(char *dirname)
{
  int n = 0;
  struct dirent *d;
  struct stat stats;
  struct tm dt;
  time_t time, time_new;
  char *file_name = malloc(255);
  DIR *dir = opendir(dirname);
  char file_path[255];

  if (dir == NULL) //Not a directory or doesn't exist
    return NULL;
  printf("Reading \t%s\n",dirname);

  if((d = readdir(dir)) != NULL){
    n++;
    printf("%d - %s\n", n, d->d_name);
    sprintf(file_path,"%s/%s",dirname,d->d_name);
    if(stat(file_path, &stats) == 0){
      time = stats.st_ctime;
      sprintf(file_name,"%s/%s",dirname, d->d_name);
    }
  }
  else
    return NULL;
  

  while ((d = readdir(dir)) != NULL){
    n++;
    printf("%d - %s\n", n, d->d_name);
    sprintf(file_path,"%s/%s",dirname,d->d_name);
    if(stat(d->d_name, &stats) == 0){
      time_new =  stats.st_ctime;
    }
    printf("time :%ld\ttime_new :%ld\n",time,time_new);
    if(time_new < time){
      sprintf(file_name,"%s/%s",dirname, d->d_name);
      time = time_new;
    }
    else
    {
      printf("OOPs\n");
    }
    
  }
  printf("Latest File: \t%s\n",file_name);
  printf("Closing\t%s\n",dirname);
  closedir(dir);

  if (n <= 2) //Directory Empty
    return NULL;
  else
    return file_name;
}
