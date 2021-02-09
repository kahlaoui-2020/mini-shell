
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"errno.h"
#include<sys/types.h>
#include<sys/wait.h>

#include"mon_shell.h"
#include"lire.h"
#include"execute_pipe.h"

/******************************************** mon_shell ***************************************/
void mon_shell(char *arge[]){
	int no ;
	int status ;
	int nbPipe ;
	char cmd[100] ;
	char *com[20] ;
	signal(SIGINT,SIG_IGN) ;

	printf("Voici mon shell, taper Q pour sortir\n") ;
	printf("> ") ;
	fgets(cmd,sizeof(char*)*100,stdin) ;
	cmd[strlen(cmd)-1]='\0' ;
	
	while(strcmp(cmd,"Q")!=0){
		int tailletab = lire_commande(&nbPipe,cmd,com) ; // tailletab le taille du tableau com
		if(nbPipe==1){
			Pipe(com) ;

		}else{
			int i = 0 ;
			int indicepoints=0;
			while( com[i]!=NULL  && i < tailletab ){ 
				if(strcmp(com[i],"cd")==0){				

					if(com[i+1]==NULL || strcmp(com[1],";")==0){ chdir(getenv("HOME")); i++;
					}else if(chdir(com[i+1])==-1){ perror(com[i]);} i+=2;
				}else if(strcmp(com[i],"getenv")==0){ printf("%s\n",getenv(com[i+1]));i+=2;} 
				else if(strcmp(com[i],"setenv")==0){
						if(com[i+1]==NULL || strcmp(com[1],";")==0){
							for(char **e=arge;*e!=0;e++){
								printf("%s\n",*e) ;
							}i++; 
						}else if(setenv(com[i+1],com[i+2],1)==-1){
							perror(com[i+1]) ;
						} i+=3 ;  // pour sauter setenv est ces parametres dans le tableau
					}
				else{      // Pour les autres : 
					char *option[10] ;
					int j = lire_option(indicepoints,com,option); 
					switch(fork()){
						case -1 : perror("fork") ; exit(-1) ;
						case 0 : execvp(com[i],option)  ; exit(-1) ;
						default :
							no = wait(&status);
		 					printf("Etat de retour du processus %d : %d\n",no, status);
		 					//traite_status(no,status) ;
		 					 
		 					
						}
					
				
						i = j;
					}
				i++;
			  indicepoints++;
	        }
		
	}
	printf("> ");
 	fgets(cmd,sizeof(char*)*100,stdin) ;
 	cmd[strlen(cmd)-1]=0 ;
	}
	
}