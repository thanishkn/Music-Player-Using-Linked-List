#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LL.h"
#include<time.h>



void playsong(const char* song)
{
    const char* directory = "C:\\Users\\Admin\\DSA_Miniproject\\music\\";
    char fpath[550];
    snprintf(fpath, sizeof(fpath), "\"%s%s\"", directory, song); 
    //printf("%s",fpath);
    system(fpath);
}


void createlist(NODE** headref, int* n) {
    char a[100];
    FILE* file = fopen("library.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(0);
    }

    if (fgets(a, sizeof(a), file) != NULL) {
        a[strcspn(a, "\n")] = '\0';  
        NODE* head = createnode(a);(*n)++;
        NODE* temp = head;
        NODE* t = head;

        while (fgets(a, sizeof(a), file) != NULL) {
            a[strcspn(a, "\n")] = '\0';  
            temp->next = createnode(a); (*n)++;
            temp->next->prev = temp;
            temp = temp->next;
            temp->next = NULL;
            t = temp;
        }

        fclose(file);

        *headref = head;
    } else {
        fclose(file);
        *headref = NULL;
    }
}


void playQueue(NODE* head)
{
    NODE* cursong=head;
    int ch=0,flag=0;

    
    while(ch!=3)
    {
        printf("\n\n-----------------------------\n");
        printf("NOW PLAYING: %s\n",cursong->data);
        if(!(flag)){playsong(cursong->data);}
        
        printf("\n\n1) Next Song\n2) Previous Song\n3) Exit\n");
        printf("-----------------------------\n");
        printf("Enter Choice: "); scanf("%d",&ch);
        printf("\n\n");

        switch(ch)
        {
            case 1:
            cursong=cursong->next;flag=0;
            if(cursong==NULL)
            {printf("End of Queue, Playing from beginning again!\n"); cursong=head;}
            break;
            
            case 2:
            cursong=cursong->prev;flag=0;
            if(cursong==NULL)
            {printf("End of Queue, Playing from beginning again!\n"); cursong=head;}
            break;

            case 3:
            return;

            default:
            printf("Invalid Choice!"); flag=1;

        }

    }

}

int getRandomNumber(int n) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 0 and n
    int randomNumber = rand() % (n + 1);

    return randomNumber;
}

void shufflePlay(NODE* head, int n)
{
    NODE* shuff=NULL, *temp=head;
    int x;
    for(int i=0;i<n;i++)
    {
        x = getRandomNumber(i+1);
        insertpos(&shuff,x,temp->data);
        temp=temp->next;
    }
    playQueue(shuff);
}



int main() {
    NODE* head = NULL;
    int n=0;
    createlist(&head,&n);
    NODE* cursong=head;
    //displaylist(head);

    //playsong(cursong->data);//plays current song
    //cursong-next for next song and cursong->prev for previous song

    

    int ch=0,e=1;
    
    while(e)
    {
        printf("------------Music Player-------------\n");
        printf("1) Play in Queue\n2) Shuffle Play\n3) Show Library\n4) Exit\n");
        printf("Enter Choice: "); scanf("%d",&ch);
        system("cls");
        switch(ch)
        {
            case 1:
            playQueue(head);
            freelist(&head);
            exit(0);
            break;

            case 2:
            shufflePlay(head,n);
            freelist(&head);
            exit(0);
            break;

            case 3:
            printf("\nSongs in the Library:\n");
            displaylist(head);
            printf("\n\n");
            break;

            case 4:
            e=0; break;

            default:
            printf("Invalid Choice!");e=0;
            break;
        }
    }

    freelist(&head);
    return 0;
}