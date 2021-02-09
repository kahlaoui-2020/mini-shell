
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"errno.h"
#include<sys/types.h>
#include<sys/wait.h>

#include"mon_shell.h"
/****************************** main ****************************************/

int main(int argc,char *argv[],char *arge[]){

	mon_shell(arge) ;
	return 0 ;	
}