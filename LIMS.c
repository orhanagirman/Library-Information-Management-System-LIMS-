#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Books{
	
	char name[40];
	char author[40];
	char category[40];
	int date;
	int section;
	struct Books *next1;
};

struct Areas{
	int num;
	char literature[40];
	struct Areas *next2;
};

typedef struct Books node1;
typedef struct Areas node2;

void readfile();
void queryauthor();
void querycategory();
void queryyear();
void queryarea();
void add_newarea();
void add_newbook();
void removearea();
void removebooks();
void mystrcmp();
void printlist();
int countfunction();
int mystrlen();

int main(){

	node1 *root1;
	node2 *root2;
	
	root1=(node1 *)malloc(sizeof(node1));
	root1->next1=NULL;
	
	root2=(node2 *)malloc(sizeof(node2));
	root2->next2=NULL;
	
	int input;
	int temp=0;
	
	readfile(root1,root2);
	
	while(temp==0){
		printf("\nPlease select an process.\n1.Query all books in alphabetical order\n2.Add an Area\n3.Add a book to the book list of an area\n4.Show detailed information about a particular area\n5.Remove an Area\n6.Query the books which were written by a particular author\n7.Query the books according to a particular category\n8.Query the books according to a particular publication year\n0.Exit\nSelected process:");
		scanf("%d",&input);
		if(input==1){
			mystrcmp(root1);
		}
		else if(input==2){
			char newarea[40];
			char *p2=newarea;
			int length2;
			printf("\nPlease enter a title for the new area(The names must be unique and use '_' character in spaces):\n");
			scanf("%s",&newarea);
			length2=mystrlen(newarea);
			add_newarea(root2,p2,length2);
		}
		else if(input==3){
			char searcharea[40];
			char *p3=searcharea;
			int length3;
			printf("\nPlease enter the title of the area which you want to add a book(use '_' character in spaces and the first letter of all words must be uppercase):\n");
			scanf("%s",&searcharea);
			length3=mystrlen(searcharea);
			add_newbook(root1,root2,p3,length3);
		}
		else if(input==4){
			char area[40];
			char *p4=area;
			int length4;
			printf("\nPlease enter an area(use '_' character in spaces and the first letter of all words must be uppercase):\n");
			scanf("%s",&area);
			length4=mystrlen(area);
			queryarea(root1,root2,p4,length4);
		}
		else if(input==5){
			char rmvarea[40];
			char *p5=rmvarea;
			int length5;
			printf("\nPlease enter the title of the area which you want to remove(use '_' character in spaces and the first letter of all words must be uppercase):\n");
			scanf("%s",&rmvarea);
			length5=mystrlen(rmvarea);
			int count=countfunction(root2,p5,length5);
			removearea(&root2,p5,count);
			printlist(root2);
			removebooks(&root1,count);
		}
		else if(input==6){
			char author[40];
			char *p6=author;
			int length6;
			printf("\nPlease enter a author(use '_' character in spaces and the first letter of all words must be uppercase):\n");
			scanf("%s",&author);
			length6=mystrlen(author);
            queryauthor(root1,root2,p6,length6);
		}
		else if(input==7){
			char category[40];
			char *p7=category;
			int length7;
			printf("\nPlease enter a category(the first letter of all words must be uppercase):\n");
			scanf("%s",&category);
			length7=mystrlen(category);
			querycategory(root1,root2,p7,length7);
		}
		else if(input==8){
			int min;
			int max;
			printf("\nplease enter min. year:");
			scanf("%d",&min);
			printf("please enter max. year:");
			scanf("%d",&max);
			queryyear(root1,root2,min,max);
		}
		else if(input==0){
			exit(0);
		}
		else{
			printf("\nInvalid Input\n");
		}
	}	
}

void readfile(node1*booklist1,node2*booklist2){
	node1 *iter1;
	iter1=booklist1;
	FILE *fptr1;
	fptr1=fopen("Books.txt","r");
	while(!feof(fptr1)){
		 
		fscanf(fptr1,"%s %s %s %d %d",&iter1->name,&iter1->author,&iter1->category,&iter1->date,&iter1->section);
	    iter1->next1=(node1 *)malloc(sizeof(node1));
	    iter1=iter1->next1;
     	iter1->next1=NULL;		
   }
   
	fclose(fptr1);
	
	node2 *iter2;
	iter2=booklist2;
	FILE *fptr2;
	fptr2=fopen("Areas.txt","r");
	while(!feof(fptr2)){
			
		fscanf(fptr2,"%d %s",&iter2->num,&iter2->literature);
	    iter2->next2=(node2 *)malloc(sizeof(node2));
	    iter2=iter2->next2;
     	iter2->next2=NULL;
	}
	fclose(fptr2);
}

void queryauthor(node1 *sort1,node2 *sort2,char *author,int length){
	
	node1 *iter1;
	iter1=sort1;
	node2 *iter2;
	iter2=sort2;
	int i,constant,temp=0;
	while(iter1->next1!=NULL){
		constant=0;
		for(i=0;i<length;i++){
			if(iter1->author[i]==author[i]){
			constant++;	
		    }
		}
		if(constant==length){
			if(temp==0){
			    printf("\nList of books:\nNAME\t\t\t      CATEGORY\t\t\t    YEAR      AREA\n");
			}
		    printf("%-30s%-30s%-10d",iter1->name,iter1->category,iter1->date);
		    temp++;
			while(iter2->next2!=NULL){
					if(iter1->section==iter2->num){
		                printf("%-25s\n",iter2->literature); 		
					}
					iter2=iter2->next2;
				}
				iter2=sort2;
	    }
		iter1=iter1->next1;
	}
	if(temp==0){
		printf("\nThe book not found\n");
	}
}

void querycategory(node1 *sort1,node2 *sort2,char *category,int length){
	
	node1 *iter1;
	iter1=sort1;
	node2 *iter2;
	iter2=sort2;
	int i,constant,temp=0;
	while(iter1->next1!=NULL){
		constant=0;
		for(i=0;i<length;i++){
			if(iter1->category[i]==category[i]){
			constant++;	
		    }
		}
		if(constant==length){
			if(temp==0){
			    printf("\nList of books:\nNAME\t\t\t      AUTHOR\t\t\t    YEAR      AREA\n");
			}
		    printf("%-30s%-30s%-10d",iter1->name,iter1->author,iter1->date);
			temp++;
			while(iter2->next2!=NULL){
					if(iter1->section==iter2->num){
		                printf("%-25s\n",iter2->literature); 		
					}
					iter2=iter2->next2;
				}
				iter2=sort2;
	    }
		iter1=iter1->next1;
	}
	if(temp==0){
		printf("\nThe book not found\n");
	}
}

void queryyear(node1 *sort1,node2 *sort2,int min,int max){
	
	if(min<=max){
	    node1 *iter1;
	    iter1=sort1;
	    node2 *iter2;
	    iter2=sort2;
	    int constant=0,temp=0;
	    while(iter1->next1!=NULL){
			if(iter1->date>=min && iter1->date<=max){
				if(constant==0){
				    printf("\nList of books:\nNAME\t\t\t      AUTHOR\t\t\t   CATEGORY\t\t    AREA\t\t\t     YEAR\n");
				}
				printf("%-30s%-29s%-25s",iter1->name,iter1->author,iter1->category);
				while(iter2->next2!=NULL){
					if(iter1->section==iter2->num){
		                printf("%-25s%-10d\n",iter2->literature,iter1->date);
		                temp++;
		                constant++;		
					}
					iter2=iter2->next2;
				}
				iter2=sort2;	
		    }
		    iter1=iter1->next1;
        }	
	    if(temp==0){
		printf("\nThe book not found\n");
	   }		
   }
   else{
   	printf("\nInvalid Input\n");
   }
}

void queryarea(node1 *sort1,node2 *sort2,char *area,int length){
	
	    node1 *iter1;
	    iter1=sort1;
	    node2 *iter2;
	    iter2=sort2;
	    int i,constant,temp=0;
	    while(iter2->next2!=NULL){
	    	 constant=0;
		     for(i=0;i<length;i++){
		     	if(iter2->literature[i]==area[i]){
		     		constant++;
				 }
			 }
			 if(constant==length){
			 	if(temp==0){
				    printf("\nAREA'S ID:%d\n\nList of books:\nNAME\t\t\t      AUTHOR\t\t\t    CATEGORY\t\t\t  YEAR     AREA\n",iter2->num);
				}
			    while(iter1->next1!=NULL){
			    	if(iter2->num==iter1->section){
			    		printf("%-30s%-30s%-30s%-10d%-10d\n",iter1->name,iter1->author,iter1->category,iter1->date,iter1->section);
			    		temp++;
					}	
			        iter1=iter1->next1;	
				}
			 }
		   iter2=iter2->next2;
		}
		if(temp==0){
		printf("The book not found\n");
	   }	
}

void add_newarea(node2 *sort2,char *newarea,int length){
	
	node2 *iter2;
	iter2=sort2;
	int i,constant,temp=0;
	while(iter2->next2!=NULL){
	        constant=0;
		    for(i=0;i<length;i++){
		     	if(iter2->literature[i]==newarea[i]){
		     		constant++;
				 }
			 }
			 if(constant==length){
			 	printf("\nArea already exists.\n");
		        return;
		     }
		temp=iter2->num;    
		iter2=iter2->next2;
   }
   iter2->next2=(node2 *)malloc(sizeof(node2));
   iter2->next2->next2=NULL;
   for(i=0;i<length;i++){
   	   iter2->literature[i]=newarea[i];
   }
   for(i=temp;i<temp+1;i++){
   	   iter2->num=i+1;
   }
   printf("\nArea is added\n");
   printf("\nArea Information:\nName:%s\nId:%d\n",iter2->literature,iter2->num);
}

void add_newbook(node1 *sort1,node2 *sort2,char *searcharea,int length){
	
	node1 *iter1;
	iter1=sort1;
	node2 *iter2;
	iter2=sort2;
	int i,constant,temp=0;
	
	char name[40];
	char author[40];
	char category[40];
	int date,nameln=0,authorln=0,categoryln=0;
	while(iter2->next2!=NULL){
	        constant=0;
		    for(i=0;i<length;i++){
		     	if(iter2->literature[i]==searcharea[i]){
		     		constant++;
				 }
			}

			 if(constant==length){
			 	temp++;
			 	printf("\nPlease enter features of the book(use '_' character in spaces and the first letter of all words must be uppercase)\nName:");
			 	scanf("%s",&name);
			    printf("Author:");
			 	scanf("%s",&author);
			 	printf("Category:");
			 	scanf("%s",&category);
			 	printf("Year:");
			 	scanf("%d",&date);
			 	while(iter1->next1!=NULL){
			 		
                   iter1=iter1->next1;
			   }
			   if(iter1->next1==NULL){
			 		   iter1->next1=(node1 *)malloc(sizeof(node1));
                       iter1->next1->next1=NULL;
                       iter1->date=date;
                       iter1->section=iter2->num;
                       for(i=0;name[i]!='\0';i++){
                    	   nameln++;  
					   }
					   for(i=0;author[i]!='\0';i++){
                    	   authorln++;  
					   }
					    for(i=0;category[i]!='\0';i++){
                    	   categoryln++;  
					   }
					   for(i=0;i<nameln;i++){
   	                       iter1->name[i]=name[i];
                       }
					   for(i=0;i<authorln;i++){
   	                       iter1->author[i]=author[i];
                       }
                       for(i=0;i<categoryln;i++){
   	                       iter1->category[i]=category[i];
                       }
					   printf("\nThe book is added\n");	
				   } 
		    }  
		iter2=iter2->next2;
   }
   if(temp==0){
	    printf("\nThe area not found\n");
		return;
	}  
}

void removearea(node2 **sort2,char *rmvarea,int count){
	
	node2 *nextnode=NULL;
	node2 *iter2;
	iter2=*sort2;
	node2 *previous;
    node2 *current;
    node2 *temp;
	
	int i,constant;
	
   	if((*sort2)->num==count){
	   if (*sort2== NULL) {
           return;
          }
        nextnode = (*sort2)->next2;
        free(*sort2);
        *sort2=nextnode;
        printf("\nThe area is removed\n");
    }
        previous = *sort2;
		current = (*sort2)->next2;
		
		while(current !=NULL && current->num !=count ){
			 previous = current;
			 current = current->next2;
		}
	if(current!=NULL){
		temp = current;
		previous->next2=current->next2;
		free(temp);
		printf("\nThe area is removed\n");
		
	}		 
}

void removebooks(node1 **sort1,int count){
	
	node1 *iter1;
	iter1=*sort1;
	node1 *temp1=NULL;
	node1 *temp2;
	
    if((*sort1)->section==count){
   	  temp1=(*sort1)->next1;
   	  free(*sort1);
   	  *sort1=temp1;
    }
    
   	while(iter1->next1!=NULL){
   	        if(iter1->next1->section==count){
            	temp1=iter1->next1;
                iter1->next1=iter1->next1->next1;
                free(temp1);	
			}
			else{
				iter1=iter1->next1;
				}           
    }
}

void mystrcmp(node1 *sort1){
	
	node1 *iter1;
	node1 *temp1;
	char tempname[40];
	char tempauthor[40];
	char tempcategory[40];
	int tempdate;
	int tempsection;
	
	for(iter1=sort1;iter1->next1!=NULL;iter1=iter1->next1){
			for(temp1=iter1->next1;temp1->next1!=NULL;temp1=temp1->next1){
					if(strcmp(iter1->name,temp1->name)>0){
						strcpy(tempname,iter1->name);
						strcpy(iter1->name,temp1->name);
						strcpy(temp1->name,tempname);
						
						strcpy(tempauthor,iter1->author);
						strcpy(iter1->author,temp1->author);
						strcpy(temp1->author,tempauthor);
						
						strcpy(tempcategory,iter1->category);
						strcpy(iter1->category,temp1->category);
						strcpy(temp1->category,tempcategory);
						
						tempdate=iter1->date;
						iter1->date=temp1->date;
						temp1->date=tempdate;
						
						tempsection=iter1->section;
						iter1->section=temp1->section;
						temp1->section=tempsection;
					}
			}
	}
	
	iter1=sort1;
    printf("\nList of books:\nNAME\t\t\t      AUTHOR\t\t\t    CATEGORY\t\t\t  YEAR\t   AREA\n");
    while(iter1->next1!=NULL){
    	printf("%-30s%-30s%-30s%-10d%d\n",iter1->name,iter1->author,iter1->category,iter1->date,iter1->section);
    	iter1=iter1->next1;
	}	
}

int countfunction(node2 *sort2,char *rmvarea,int length){
	
	node2 *iter2;
	iter2=sort2;
	int i,constant,count;
	
    while(iter2->next2!=NULL){
	        constant=0;
		    for(i=0;i<length;i++){
		     	if(iter2->literature[i]==rmvarea[i]){
		     		constant++;
				 }
			 }
			 if(constant==length){
			 	count=iter2->num;
			 } 
		iter2=iter2->next2;
   }
   return count;
}

void printlist(node2 *sort2){
	
  	node2 *iter2;
	iter2=sort2;
	
	printf("\nList of areas:\n");
	while(iter2->next2!=NULL){
		printf("%-5d%-20s\n",iter2->num,iter2->literature);
		iter2=iter2->next2;
	}
}

int mystrlen(char ln[]){
	int i,length=0;
	for(i=0;ln[i]!='\0';i++){
		length++;
	}
	return length;
}
