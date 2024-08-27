#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 30
#define DEFAULT_SZ 3
#define INC_SZ 2
typedef struct PeoInfo
{
  char name[MAX_NAME];
  int age;
  char sex[MAX_SEX];
  char tele[MAX_TELE];
  char addr[MAX_ADDR];
}PeoInfo;

/*typedef struct Contact
{
    PeoInfo data[MAX];
    int count;
}Contact;*/

typedef struct Contact
{
    PeoInfo *data;
    int count;
    int capacity;
}Contact;

void InitContact(Contact*pc);
void DestroyContact(Contact*pc);
void AddContact(Contact*pc);
void ShowContact(Contact*pc);
void DelContact(Contact*pc);
void SearchContact(Contact*pc);
void ModifyContact(Contact*pc);
void SortContact(Contact*pc);
void SaveContact(Contact*pc);
void LoadContact(Contact*pc);





