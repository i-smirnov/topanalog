#include<cctype>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>
#include <dirent.h>
#include<ftw.h>
#include<iostream>
#include <string>
#include<cstring>
using namespace std;

// с сайта https://forums.freebsd.org/threads/for-the-beginner-c-programmer.36791/

int action(const char *path, const struct stat *st, int flags)
{
   printf("%s\n", path);
   return 0;
}
//----------------


		void prnt(char *buf,char *str)
		{
		 char *pt,a;
		 int i=strlen(str),l=i;
		 pt=strstr(buf,str);
		 a=pt[i];
		 while (pt[i]!='\n'){printf("%c",pt[i]);i+=1;}	
		 
		 if (isdigit(a)) printf("\t");
		 else if (i<(l+8)) printf("\t\t\t");
		 else printf("\t\t");
		}	

int main()
{
  int ifd,ofd,openFlags;
  mode_t filePerms;
  ssize_t numWrite,numRead;
  char charr[]="Try to write this.\n";
  char buff[1024]="";

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;

// попробуем прочитать директорию
  printf("Lets try to read a directory\n");
  DIR *dir, *piddir;
  struct dirent *entry;

  dir = opendir("/proc");
  if (!dir){
     printf("diropen\n");
     return(1);
  };

int ppp=0;
char filename[20]="/proc/";
const char pr[20]="/proc/";
char ad[6]="";
char *ln;
char pid[]="Pid:\t";
char name[]="Name:\t";
char state[]="State:\t";


  while( (entry = readdir(dir))!=NULL )
  {
     if (isdigit(entry->d_name[0])) 
     { 
	for(int l=0;l<20;l++) filename[l]=pr[l]; //reset filename value
	strcat(filename,entry->d_name);	
//-	printf("filename=%s \n",filename);
	piddir=opendir(filename);
  	if (!piddir)
	{
     		printf("piddiropen\n");
     		return(1);	
  	};
	
    // 	if (ppp==3) //without this if we can't open EVERY status 
//	{
		

		strcat(filename,"/status");
//-		printf("filename=%s \n",filename);
     		
		ifd=open(filename, O_RDONLY);
		if (ifd ==-1) printf("error opening input file\n");
  		
//-		int z=0;
/*
		do// while (buff[z-1]!='\0')
		{
			printf("z=%d\n",z);
			numRead = read(ifd, &buff[z], 1);
			z+=1;
		} while (buff[z-1]!='\n');
*/
		numRead=read(ifd,buff,1024);
		
		
//		void prnt(char *buf,char *str,char *pt)
		
//		printf("buff= %s\n",buff);
	//	ln=strstr(buff,"Pid:\t");
	//	while(ln[z+strlen("Pid:\t")]!='\n') { printf("%c",ln[z+5]); z+=1;}
		prnt(buff,pid);	
		prnt(buff,name);
		prnt(buff,state);
		printf("\n");	
/*		ofd=open("outfile.txt",openFlags,filePerms); 
  		if (ofd == -1) printf("err opening output file\n");
 
//		getline(ifd,str1);

  		while ((numRead = read(ifd, buff, 10)) > 0)
    		{
    			if (write(ofd, buff, numRead) != numRead)
      			printf("couldn't write whole buffer\n");
    		}*/
		close(ifd);
		//close(ofd);
 //	}
   //  	ppp+=1;
	closedir(piddir);
     }
  }

 
 // cout<<"filename="<<filename<<endl;
  closedir(dir);
  

//необходимо пройтись по всем подкаталогам proc и считать файлы status
/*  int flags=0;
  flags=FTW_PHYS;
  return nftw("/etc",action,1,flags); 
  */
//  return 0;
    
}
