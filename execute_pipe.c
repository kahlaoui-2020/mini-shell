#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"errno.h"
#include<sys/types.h>
#include<sys/wait.h>

#include"lire.h"
#include"execute_pipe.h"

/******************************************** commande avec pipe ***************************************/

void Pipe(char *com[]){
int i = 0 ;
int j = 1 ;
int f[2] ;
char *chaine = malloc(sizeof(char)*20) ;
pipe(f) ;
switch(fork()){
case -1 :
perror("fork");
exit(-1) ;
case 0 :
lire_avant_pipe(j,com,chaine) ;
close(1) ;
dup(f[1]) ;
close(f[1]) ;
close(f[0]) ;
if(strcmp(com[1],"|")!=0){
        if(execlp(com[0],com[0],chaine,(char*)0)<1){
          perror("execlp 1") ;
          exit(-1) ;
        }
}else{ if(execlp(com[0],com[0],(char*)0)){
              perror("execlp 1") ;
              exit(-1) ;
        }


}


default :
switch(fork()){
case -1 :
perror("fork");
exit(-1) ;
case 0 :
i = lire_apres_pipe(com,chaine) ;
close(0) ;
dup(f[0]) ;
close(f[1]) ;
close(f[0]) ;
if(com[i+1]!=NULL){
if(execlp(com[i],com[i],chaine,(char*)0)<1){
              perror("execlp 1") ;
              exit(-1) ;
            }
}else{
if(execlp(com[i],com[i],(char*)0)){
              perror("execlp 1") ;
              exit(-1) ;
        }
}
default :
close(f[0]) ;
close(f[1]) ;
          while(wait(NULL)!=-1) ;




}
}
}

