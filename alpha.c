#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc,char** argv[]){
    system("clear");
    char indata[100];
    char* sa[10];
    char* token;
    int i;
    while(1){
	char cwd[500];
	if(getcwd(cwd,sizeof(cwd))!=NULL){
	        printf("%s ",cwd);
	}else{
	    perror("getcwd() error");
	}
	/*printf("~alpha>");*/
	fgets(indata,sizeof(indata),stdin);
	indata[strcspn(indata,"\n")]=0;
	if(strcmp(indata,"exit")==0)return 0;
	/*printf("%s\n",indata);*/
	i=0;
	token=strtok(indata," ");
	while(token!=NULL){
	    sa[i]=token;
	    token=strtok(NULL," ");
	    i++;
	}
	sa[i]=NULL;
	if(sa[0]==NULL)continue;
	/*for(j=0;j<i;j++){
	    printf("%s\n",sa[j]);
        }*/
	if(strcmp(sa[0],"cd")==0){
	    char path[200];
	    if(sa[1]==NULL){
		char* home=getenv("HOME");
		if(home!=NULL){
		    chdir(home);
		}
	    }else{
		if(sa[1][0]=='~'){
		    char* home=getenv("HOME");
		    if(home!=NULL){
			snprintf(path,sizeof(path),"%s%s",home,sa[1]+1);
			if(chdir(path)!=0){
			    perror("cd failed");
		  	}
		    }
		}else{
		    if(chdir(sa[1])!=0){
			perror("failed");
		    }
		}
	    }
	    continue;
	}
	pid_t p=fork();
	if(p>0){
	    wait(NULL);
	    printf("Parent terminated\n");
	}else if(p==0){
	    execvp(sa[0],sa);
	    perror("exec failed");
	    exit(1);
	}else{
	    printf("fork failed\n");
	}
    }
    printf("End of main\n");
    return 0;
}
