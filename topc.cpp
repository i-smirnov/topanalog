#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include <dirent.h>
#include <string>
#include<cstring>
using namespace std;

//formating output for characteristic
void prnt(char *buf,char *str)
{
	char *pt,a;
	int i=strlen(str),l=i;
	pt=strstr(buf,str);
	a=pt[i];
	while (pt[i]!='\n'){printf("%c",pt[i]);i+=1;}	 
	if (isdigit(a)) printf("\t");			//one tabulation after pid
	else if (i<(l+8)) printf("\t\t\t");		
	else printf("\t\t");				//2 or 3 tabs after process name depending on the length of the name
}	



int main()
{
	int ifd,ofd,openFlags;
	mode_t filePerms;
	ssize_t numWrite,numRead;
	char buff[1024]="";

	char filename[20]="/proc/";
	const char pr[20]="/proc/";
	char pid[]="Pid:\t";
	char name[]="Name:\t";
	char state[]="State:\t";

	DIR *dir, *piddir;
 	struct dirent *entry;

  	dir = opendir("/proc");				//open directory stream
  	if (!dir){
     		printf("diropen\n");
     		return(1);
  	};




  	while( (entry = readdir(dir))!=NULL )			//walk through dir
  	{
     		if (isdigit(entry->d_name[0])) 			//check for digits in the begining of directory name
     		{ 
			for(int l=0;l<20;l++) filename[l]=pr[l];	//reset filename value
			strcat(filename,entry->d_name);			//append process dirname to "/proc/"
			piddir=opendir(filename);			//open inner directory stream (step inside "/proc/[pid]")
  			if (!piddir)
			{
     				printf("piddiropen\n");
     				return(1);	
  			};

			strcat(filename,"/status");			// now we have "/proc/[pid]/status"
     		
			ifd=open(filename, O_RDONLY);			//open file "/proc/[pid]/status" for read 
			if (ifd ==-1) printf("error opening input file\n");
			numRead=read(ifd,buff,1024);			//read 1024 bytes
	
			prnt(buff,pid);					//output pid
			prnt(buff,name);				//print process name
			prnt(buff,state);				//print process state
			printf("\n");	
	
			close(ifd);
			closedir(piddir);
     		}
  	}
  	
	closedir(dir);  
}
