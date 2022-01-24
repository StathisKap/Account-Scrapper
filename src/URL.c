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
  char *file_name;
  int startIndex= 0;
  char start_count[50];
  if(((file_name = isDirectoryEmpty("Searches")) != NULL) && start == NULL){
    startIndex = Parse_For_Count(file_name);
    printf("Directory is NOT empty\n\
    Latest File: %s\n\
    Count: %d\n",file_name,startIndex);
    puts("It's still good here");
    sprintf(start_count,"&start=%d",startIndex+10);
  }
  else{
    strcpy(start,"1");
    printf("Directory is Empty\n");
    sprintf(start_count,"&start=%d",atoi(start));
  }

  sprintf(url,"%s%s%s%s%s%s",                       \
      CUSTOM_SEARCH_ENGINE_URL,                     \
      Custom_Search_Engine_cx,                      \
      "&q=",                                        \
      curl_easy_escape(curl,querry,strlen(querry)), \
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
  char *file_name = malloc(255);
  DIR *dir = opendir(dirname);
  char file_path[255];

  char Searches[] = "Searches/";
  char Searches_Path[100];
  Search Latest;
  
  Latest.time = 1;
  Latest.name = malloc(100);
  Latest.full_path = malloc(150);

  if (dir == NULL) //Not a directory or doesn't exist
    return NULL;
  printf("Reading: %s\n",dirname);
  
  while ((d = readdir(dir)) != NULL)
  {
    if(d->d_name[0] != '.'){
      sprintf(Searches_Path,"%s%s",Searches,d->d_name);
      if(stat(Searches_Path, &stats) == 0)
        printf("%d. %s - %ld\n",++n,d->d_name,stats.st_birthtimespec.tv_sec);
      else
        puts("OOps");
      if(n == 1){
        Latest.time = stats.st_birthtimespec.tv_sec;
        strcpy(Latest.name,d->d_name); 
      }
      if ((stats.st_birthtimespec.tv_sec > Latest.time) && Latest.name[0] != '.')
      {
        strcpy(Latest.name,d->d_name); 
        strcpy(Latest.full_path,Searches_Path); 
        Latest.time = stats.st_birthtimespec.tv_sec;
      }
    }
  }
  printf("Latest File: %s\n",Latest.name);
  printf("Closing: %s\n",dirname);
  closedir(dir);

  if (n <= 2) //Directory Empty
    return NULL;
  else
    return Latest.full_path;
}

int Parse_For_Count(char *filename){
  FILE * file_ptr = fopen(filename, "r");
  char * line = NULL;
  char *startIndex_ptr;
  size_t len = 0;
  ssize_t read;
  if(file_ptr == NULL) 
    puts("Couldn't open file");
  puts("Opened file");
  while ((read = getline(&line, &len, file_ptr)) != -1){
    if(strstr(line,"\"request\": [")){
        while ((read = getline(&line, &len, file_ptr)) != -1){
            if((startIndex_ptr = strstr(line,"\"startIndex\":")) != NULL){
            break;
            }
        }
        break;
    }
  }
  startIndex_ptr += strlen("\"startIndex\":") + 1;
  fclose(file_ptr);
  free(line);
  return atoi(startIndex_ptr);
}