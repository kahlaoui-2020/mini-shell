#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"errno.h"
#include<sys/types.h>
#include<sys/wait.h>

#include"lire.h"


int lire_commande(int *pipe,char ligne[], char *ligne_decoupee[]){

	int i = 0 ;
	int j = 0 ;
	char *tmp = strtok(ligne," ") ;

	while(tmp != NULL){
		if(strcmp(tmp,"|")==0) j++ ;
		ligne_decoupee[i] = tmp ;
		tmp = strtok(NULL," ") ;
		i++ ;
	}
	ligne_decoupee[i] ='\0' ;
	*pipe = j ;
	return  i ;
	
}

   
int lire_option(int i,char *ligne_decoupee[],char *option[]){
	int j = 0 ;
	int x=0;
	while(x<i){
		if(ligne_decoupee[j]!=NULL && strcmp(ligne_decoupee[j],";")==0){
			x++;
		}
		j++;
	}
	x=0;
	while(ligne_decoupee[j]!=NULL && strcmp(ligne_decoupee[j],";")!=0){
		option[x] = ligne_decoupee[j] ;
		x++; j++;
	}
	option[x] = 0 ;
	
	return j;
}

void lire_avant_pipe(int i,char *com[],char *chaine){

	if(strcmp(com[i],"|" )!=0){
		strcpy(chaine,com[i]) ;
		i++ ;
		while(strcmp(com[i],"|")!=0 && com[i]!=NULL){
			strcat(chaine," ") ;
			strcat(chaine,com[i]) ;
			i++ ;
		}

	}
}
int lire_apres_pipe(char *com[],char *chaine){
	int i =0 ;
	while(strcmp(com[i],"|" )!=0 ){ i++ ; }
	i+=2 ;
	int j = i-1 ;
	if(com[i]!=NULL){
		strcpy(chaine,com[i]) ;
		i++ ;
		while(com[i]!=NULL){
				strcat(chaine," ") ;
				strcat(chaine,com[i]) ;
				i++ ;
			}

	}
	return j ;
}