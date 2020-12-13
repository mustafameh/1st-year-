#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct item{
    int id;
    char name[10];
    double cost;
    char category;
    struct item *next;
};
void printItem(struct item *);
void insert(struct item *head, int id, double cost, char category, char *name);
int checkItem(struct item *,int );
int checkItemName(struct item *head, char* sname);
void searchDisplay(struct item *head, char* sname);
void changeCost(struct item *head, int sid, double scost);
void deleteItem(struct item *head, int sid);
void bubblesortId(struct item *head);
void bubblesortCost(struct item *head);
void bubblesortName(struct item *head);
void bubblesortCategory(struct item *head);

int main(){
    int flag =0;
    int andd;
     char filename[20];
     printf("Enter file name :");
     scanf("%s",filename);

     FILE *fptr;
     fptr= fopen(filename,"r");
     if(fptr==NULL){
         printf("Could not Open file");
     }
     else
     {
         printf("Opened successfully- now transfering..\n");
     }
//////////////////////reading from file into the linked list/////////////////
     int pid;
     char pname[20];
     double pcost;
     char pcategory;
     fscanf(fptr,"%d %s %lf %c \n",&pid, pname, &pcost, &pcategory);

     struct item *head = malloc(sizeof(struct item));

      head->id=pid;
      strcpy (head->name,pname);
      head->category=pcategory;
      head->cost=pcost;
      head->next=NULL;

      while( !feof(fptr)){
     fscanf(fptr,"%d %s %lf %c \n",&pid, pname, &pcost, &pcategory);
     insert(head, pid , pcost, pcategory, pname);

}
     fclose(fptr);
     printItem(head);
/////////////////closing- reading from file into the linked list/////////////////
while(flag==0){
printf("\n1. Add new item \n2. Delete item \n3. Change the cost of an item \n4. Search for item \n5. Display inventory details \n6. Quit \n Enter the Number corresponding to the menue option :");   
/////Menue///////////
int Option;
scanf("%d",&Option);
switch (Option)
{
case 1:///For adding new item to the list
    printf("You have chosen to ADD NEW ITEM:");
    int kid;
    printf("\nEnter Id :");
    scanf("%d",&kid);
    char kname[20];
    printf("\nEnter Name :");
    scanf("%s",&kname);
    fflush(stdin);
    double kcost;
    printf("\nEnter cost :");
    scanf("%lf",&kcost);
    fflush(stdin);
    char kcategory;
    printf("\nEnter category :");
    scanf("%c",&kcategory);
    fflush(stdin);

    if(checkItem(head,kid)==1 || checkItemName(head,kname)){

        printf("Item already exists and will not be added.\n");
    }
    else
    { 
    printf("Inserting the following details :%d %lf %s %c \n",kid,kcost,kname,kcategory);
    insert(head, kid , kcost, kcategory, kname);
    }

    break;

case 4 :
    printf("\nYou have chosen to Search For An Item.\n Please enter the name of item ");
    char Mname[20];
    scanf("%s",Mname);
    searchDisplay(head,Mname);
    break;

case 3:
    printf("\nYou have chosen to change cost For An Item.\n Please enter the id of item :");
    int Mid;
    double Mcost;
    scanf("%d",&Mid);
    printf("\nEnter the new price :");
    scanf("%lf",&Mcost);
    changeCost(head,Mid, Mcost);
    break;
case 6:
    printf("You have chosen to quit");
    flag =1;
    break;

case 2:
    printf("\nYou have chosen to delete an item.\n Enter the id to delete from the database :");
    int Pid;
    scanf("%d",&Pid);
    deleteItem(head,Pid);
   break;

case 5:
    
    printf("\n How do you want your Database be displayed? please chose an option.\n1) Sorted By ID.\n2) Sorted by Cost\n3) Sorted by Name\n4) Sorted by category.-->");
    scanf("%d",&andd);
    switch (andd){
        case 1:
        printf("\nData base will be sorted in ascending by id \n");
        bubblesortId(head);
        printItem(head);
        break;

        case 2:
        printf("\n Data will be sorted in ascending by cost \n");
        bubblesortCost(head);
        printItem(head);
        break;

        case 3:
        printf("\n Data will be sorted in ascending by name \n");
        bubblesortName(head);
        printItem(head);
        break;
        case 4:
        printf("\n Data will be sorted in ascending by category \n");
        bubblesortCategory(head);
        printItem(head);
        break;

       default:
       printf("\nIllegal option____Could not complete operation");
       break;



    }









    

    
    
    
    
    
    
    
    
    break;

default:
    printf("\nIllegal option____Could not complete operation");
    break;
}
}
printItem(head);
////////////////////////////////////////////////////closing menue///////////////////////
if(flag==1){
printf("\nDo you want to save changes yes or no? ");
char reply[10];
scanf("%s",reply);

    if(strcmp(reply,"yes")==0){
        printf("\nEnter the name of the file to save along with .txt :");
        char sfile[20];
        fflush(stdin);
        scanf("%s",sfile);

        fptr= fopen(sfile,"w");
        if(fptr==NULL){
            printf("Could not create file");
        }
        else
        {
            struct item *temp;
            temp=head;

            while(temp != NULL){
                fprintf(fptr,"%d %s %lf %c \n",temp->id,temp->name, temp->cost, temp->category);
                temp=temp->next;
            }
            printf("\n Writing was successfull.\n");
        }
        


    }
    else
    {
        printf("\n Exiting without saving...");
    }
    


    printItem(head);



}
     
     





    //printItem(head);

    return 0;
}


















void insert(struct item *head, int id, double cost, char category, char *name){
    struct item *new, *temp;
    new=(struct item *)malloc(sizeof(struct item));
    new->id=id;
    new->cost=cost;
   strcpy(new->name,name);
    new->category=category;
    new->next=NULL;
    temp=head;
    while(temp->next!=NULL){
        temp=temp->next;;
    }
    temp->next=new;




}




void printItem(struct item *head){
    struct item *temp;
    temp=head;

    while(temp != NULL){
        printf("The name is %s and the id is %d cost is %lf and category is %c.\n",temp->name,(*temp).id, temp->cost, temp->category);


        temp=temp->next;
    }
}

/////returns 1 if found and 0 if not/////
int checkItem(struct item *head,int sid){
    struct item *temp;
    temp=head;

     while(temp != NULL){
         
         if(temp->id==sid){
             return 1;
         }


         temp=temp->next;
     }






    return 0;
}


int checkItemName(struct item *head, char* sname){
struct item *temp;
    temp=head;

     while(temp != NULL){
         
         if(strcmp(temp->name,sname)==0){
             return 1;
         }


         temp=temp->next;
     }


return 0;
}

void searchDisplay(struct item *head, char* sname){
     int flag = 0;
     struct item *temp;
     temp=head;

     while(temp!=NULL){
         if(strcmp(temp->name,sname)==0){
             printf("\nThe name is %s and the id is %d cost is %lf and category is %c.\n",temp->name,(*temp).id, temp->cost, temp->category);
             flag = 1;
         }

         temp=temp->next;
     }


    if(flag == 0){
        printf("\nItem not found.\n");


    }


}

void changeCost(struct item *head, int sid, double scost){
    int flag =0;
    struct item *temp;
    temp=head;

     while(temp!=NULL){
         if(temp->id==sid){
             temp->cost=scost;
             printf("\nUpdated Cost to the following : The name is %s and the id is %d cost is %lf and category is %c.\n",temp->name,(*temp).id, temp->cost, temp->category);
             flag = 1;
         }

         temp=temp->next;
     }




    if(flag==0){
        printf("\ncItem not found \n" );
    }


}

///retarded deletion//
void deleteItem(struct item *head, int sid){
    int flag=0; 
    struct item *temp;
    struct item *previous;
    struct item *hell;
    struct item *soup;
    temp=head;
    previous=head;

    while(temp != NULL){
        if(temp->id==sid){

            printf("\nFound and deleting..\n");
            flag=1;
            break;
        }

        previous=temp;
        temp=temp->next;
    }
/////////at this point previous has the address of node where we have to link the last one and temp is the address we have to delete but the address contained in it has to be put in last elent
        hell=temp->next;//address to  be put in last elemnt 
        temp=head;

        while(temp->next != NULL){

          soup=temp;
         temp=temp->next;
         }
         previous->next=temp;
         temp->next=hell;
         soup->next=NULL;
if(flag==0){
    printf("\n Item with such id does not exist");

}

}


void bubblesortId(struct item *head){
    struct item *ptr, *cpt;
    int tempid;
    double tempcost;
    char tempname[20];
    char tempcategory;
    ptr = head;

    while(ptr->next != NULL){
        cpt=ptr->next;

        while(cpt != NULL){
            if(ptr->id>cpt->id){
                ///swap id////
                tempid=ptr->id;
                ptr->id=cpt->id;
                cpt->id=tempid;
                ///swap cost///
                tempcost=ptr->cost;
                ptr->cost=cpt->cost;
                cpt->cost = tempcost;
                ///swap name///
                strcpy(tempname, ptr->name);
                strcpy(ptr->name, cpt->name);
                strcpy(cpt->name, tempname);
                ///swap category//
                tempcategory=ptr->category;
                ptr->category=cpt->category;
                cpt->category = tempcategory;
            }

            cpt=cpt->next;
        }
        ptr=ptr->next;

    }

}

void bubblesortCost(struct item *head){
    struct item *ptr, *cpt;
    int tempid;
    double tempcost;
    char tempname[20];
    char tempcategory;
    ptr = head;

    while(ptr->next != NULL){
        cpt=ptr->next;

        while(cpt != NULL){
            if(ptr->cost>cpt->cost){
                ///swap id////
                tempid=ptr->id;
                ptr->id=cpt->id;
                cpt->id=tempid;
                ///swap cost///
                tempcost=ptr->cost;
                ptr->cost=cpt->cost;
                cpt->cost = tempcost;
                ///swap name///
                strcpy(tempname, ptr->name);
                strcpy(ptr->name, cpt->name);
                strcpy(cpt->name, tempname);
                ///swap category//
                tempcategory=ptr->category;
                ptr->category=cpt->category;
                cpt->category = tempcategory;
            }

            cpt=cpt->next;
        }
        ptr=ptr->next;

    }


}

void bubblesortName(struct item *head){
    struct item *ptr, *cpt;
    int tempid;
    double tempcost;
    char tempname[20];
    char tempcategory;
    ptr = head;

    while(ptr->next != NULL){
        cpt=ptr->next;

        while(cpt != NULL){
            if(strcmp (ptr->name,cpt->name)>0){
                ///swap id////
                tempid=ptr->id;
                ptr->id=cpt->id;
                cpt->id=tempid;
                ///swap cost///
                tempcost=ptr->cost;
                ptr->cost=cpt->cost;
                cpt->cost = tempcost;
                ///swap name///
                strcpy(tempname, ptr->name);
                strcpy(ptr->name, cpt->name);
                strcpy(cpt->name, tempname);
                ///swap category//
                tempcategory=ptr->category;
                ptr->category=cpt->category;
                cpt->category = tempcategory;
            }

            cpt=cpt->next;
        }
        ptr=ptr->next;

    }


}

void bubblesortCategory(struct item *head){
    struct item *ptr, *cpt;
    int tempid;
    double tempcost;
    char tempname[20];
    char tempcategory;
    ptr = head;

    while(ptr->next != NULL){
        cpt=ptr->next;

        while(cpt != NULL){
            if(ptr->category>cpt->category){
                ///swap id////
                tempid=ptr->id;
                ptr->id=cpt->id;
                cpt->id=tempid;
                ///swap cost///
                tempcost=ptr->cost;
                ptr->cost=cpt->cost;
                cpt->cost = tempcost;
                ///swap name///
                strcpy(tempname, ptr->name);
                strcpy(ptr->name, cpt->name);
                strcpy(cpt->name, tempname);
                ///swap category//
                tempcategory=ptr->category;
                ptr->category=cpt->category;
                cpt->category = tempcategory;
            }

            cpt=cpt->next;
        }
        ptr=ptr->next;

    }


}
