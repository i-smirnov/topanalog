#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>

int main()
{
  int ifd,ofd,openFlags;
  mode_t filePerms;
  ssize_t numWrite,numRead;
  char charr[]="Try to write this.\n";
  char buff[50];
  ifd=open("../myfile.txt", O_RDWR | O_CREAT); 
  if (ifd == -1) printf("err opening input file\n");

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;
  ofd=open("outfile.txt",openFlags,filePerms); 
  if (ofd == -1) printf("err opening output file\n");
 
  while ((numRead = read(ifd, buff, 10)) > 0)
    {
    printf("Зашли в while\n");
    if (write(ofd, buff, numRead) != numRead)
      printf("couldn't write whole buffer\n");
    }






  close(ifd);
  close(ofd);
  return 0;
    
}
