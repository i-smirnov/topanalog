#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>
#include <dirent.h>
int main()
{
  int ifd,ofd,openFlags;
  mode_t filePerms;
  ssize_t numWrite,numRead;
  char charr[]="Try to write this.\n";
  char buff[50];
 
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;

  ifd=open(("/proc/2476/status"), O_RDONLY | O_CREAT); 
  if (ifd == -1) printf("err opening input file\n");


  ofd=open("outfile.txt",openFlags,filePerms); 
  if (ofd == -1) printf("err opening output file\n");
 

  while ((numRead = read(ifd, buff, 10)) > 0)
    {
    if (write(ofd, buff, numRead) != numRead)
      printf("couldn't write whole buffer\n");
    }
// попробуем прочитать директорию

  printf("Попробуем считать директорию\n");
  DIR *dir;
  struct dirent *entry;

  dir = opendir("/proc");
  if (!dir){
     printf("diropen\n");
     return(1);
  };

  while( (entry = readdir(dir))!=NULL ){
     printf("%s [%d] %d\n", 
            entry->d_name,entry->d_type,entry->d_reclen);
  } 
 

  closedir(dir);
  




  close(ifd);
  close(ofd);
  return 0;
    
}
