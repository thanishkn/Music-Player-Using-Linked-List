#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    struct node* prev;//address to the previous structure/null if first node
    char* data;//data
    struct node* next;//address to the next structure/null if last node
}NODE;


NODE* createnode(const char* x)
{
    NODE *newn= (NODE*)malloc(sizeof(NODE));
    newn->data=strdup(x);
    newn->next=NULL;
    newn->prev=NULL;
    return newn;
}

// void createlist(int n, NODE** headref) {
//     if (n == 0) {
//         *headref = NULL;
//         return;
//     }

//     char a[100];
//     printf("Enter elements:\n");
//     fflush(stdin);
//     // Create the head of the linked list
//     fgets(a, sizeof(a), stdin);
//     a[strcspn(a, "\n")] = '\0';  // Remove the newline character
//     NODE* head = createnode(a);
//     NODE* temp = head;
//     NODE* t = head;

//     for (int i = 1; i < n; i++) {
//         fflush(stdin);
//         fgets(a, sizeof(a), stdin);
//         a[strcspn(a, "\n")] = '\0';  // Remove the newline character
//         temp->next = createnode(a);
//         temp->next->prev = temp;
//         temp = temp->next;
//         temp->next = NULL;
//         t = temp;
//     }

//     *headref = head;
// }


void displaylist(NODE* head)
{
    NODE* temp;
    temp=head;
    if(head==NULL){
        //printf("linked List is empty");
        return;}
    else
    {
        int i=1;
        //printf("The list is:\n");
        while(temp!=NULL)
        {
            printf("%d) %s\n",i,temp->data);
            temp=temp->next;i++;
        }
        printf("\n");
    }
}

NODE* gettail(NODE* head)
{
    NODE* tail=head;
    if(tail==NULL){return tail;}
    while(tail->next!=NULL)
    {
        tail=tail->next;
    }
    return tail;
}

void freelist(NODE** headref)
{
    NODE* head=*headref;
    while(head!=NULL)
    {
        NODE* temp=head->next;
        free(head);
        head=temp;
    }
    *headref=NULL;
}

void insertfront(NODE** headref,char* a)
{
    NODE* temp=createnode(a);
    temp->prev=NULL;
    temp->next=*headref;
    *headref=temp;
}

void deletefront(NODE** headref)
{
    NODE* head=*headref;
    NODE* temp=head;
    head=head->next;
    free(temp);
    head->prev=NULL;
    *headref= head;
}

void deletelast(NODE** headref)
{
    NODE* head=*headref;
    NODE* tail=gettail(head);
    tail->prev->next=NULL;
    free(tail);
    *headref= head;
}

void insertlast(NODE** headref,char* a)
{
    NODE* head=*headref;
    NODE* temp=createnode(a);
    NODE* tail=gettail(head);
    temp->prev=tail;tail->next=temp;
    temp->next=NULL;
    *headref= head;
}

void insertpos(NODE** headref, int pos, char* a)
{
    NODE* head = *headref;
    NODE* temp = head;

    if (head == NULL) {
        *headref = createnode(a);
        return;
    }

    int i = 1;
    while (temp->next != NULL && i < pos)
    {
        temp = temp->next;
        i++;
    }

    NODE* newn = createnode(a);
    newn->prev = temp;
    newn->next = temp->next;

    if (temp->next != NULL) {
        temp->next->prev = newn;
    }

    temp->next = newn;
}


void deletepos(NODE** headref, int pos)
{
    NODE* head=*headref;
    NODE* temp=head;
    int i=0;
    while(temp->next!=NULL && i<pos)
    {
        temp=temp->next;i++;
    }
    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    free(temp);
    *headref= head;
}