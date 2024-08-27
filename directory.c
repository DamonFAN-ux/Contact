#include"directory.h"
void CheckCapacity(Contact*pc)
{
  if(pc->count==pc->capacity)
  {
    PeoInfo*ptr=(PeoInfo*)realloc(pc->data,(pc->capacity+INC_SZ)*sizeof(PeoInfo));
    if(ptr==NULL)
    {
      printf("分配内存失败！\n");
      exit(1);
    }
    else
    {
      pc->data=ptr;
      pc->capacity+=INC_SZ;
      printf("增容成功！\n");
    }
  }
}
void LoadContact(Contact*pc)
{
  FILE*pfread;
  if((pfread=fopen("C:\\code\\C\\contact.txt","rb"))==NULL)
  {
    printf("Can not open the file!\n");
    exit(0);
  }
  PeoInfo tmp={0};
  while((fread(&tmp,sizeof(PeoInfo),1,pfread))==1)
  {
    CheckCapacity(pc);
    pc->data[pc->count]=tmp;
    pc->count++;
  }
  if(fclose(pfread))
  {
    printf("Can not close the file!\n");
    exit(0);
  }
}
/*void InitContact(Contact*pc)
{
  assert(pc);
  pc->count=0;
  memset(pc->data,0,sizeof(pc->data));
}*/
void InitContact(Contact*pc)
{
  assert(pc);
  pc->count=0;
  pc->data=(PeoInfo*)calloc(3,sizeof(PeoInfo));
  if(pc->data==NULL)
  {
    printf("分配内存失败！\n");
    exit(1);
  }
  pc->capacity=DEFAULT_SZ;
  LoadContact(pc);
}
/*void AddContact(Contact*pc)
{
  assert(pc);
  if(pc->count==MAX)
  {
    printf("通讯录已满，无法再次添加>>>\n");
    return;
  }
  printf("请输入姓名>>>\n");
  scanf("%s",pc->data[pc->count].name);
  printf("请输入年龄>>>\n");
  scanf("%d",&(pc->data[pc->count].age));
  printf("请输入性别>>>\n");
  scanf("%s",pc->data[pc->count].sex);
  printf("请输入电话>>>\n");
  scanf("%s",pc->data[pc->count].tele);
  printf("请输入地址>>>\n");
  scanf("%s",pc->data[pc->count].addr);
  pc->count++;
  printf("增加成功>>>\n");
}*/
void AddContact(Contact*pc)
{
  assert(pc);
  CheckCapacity(pc);
  printf("请输入姓名>>>\n");
  scanf("%s",pc->data[pc->count].name);
  printf("请输入年龄>>>\n");
  scanf("%d",&(pc->data[pc->count].age));
  printf("请输入性别>>>\n");
  scanf("%s",pc->data[pc->count].sex);
  printf("请输入电话>>>\n");
  scanf("%s",pc->data[pc->count].tele);
  printf("请输入地址>>>\n");
  scanf("%s",pc->data[pc->count].addr);
  pc->count++;
  printf("增加成功>>>\n");
}
void ShowContact(Contact*pc)
{
    assert(pc);
    int i=0;
    printf("%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n","姓名","年龄","性别","电话","地址");
    for(i=0;i<pc->count;i++)
    {
        printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n",pc->data[i].name,
                                              pc->data[i].age,
                                              pc->data[i].sex,
                                              pc->data[i].tele,
                                              pc->data[i].addr);
    }
}
static int FindByName(Contact*pc,char name[])
{
    assert(pc);
    int i;
    for(i=0;i<pc->count;i++)
    {
       if(strcmp(pc->data[i].name,name)==0)
       {
        return i;
       }
    }
    return -1;
}

void DelContact(Contact*pc)
{
  char name[MAX_NAME]={0};
  assert(pc);
  if(pc->count==0)
  {
    printf("通讯录为空,没有信息可以删除>>>\n");
    return;
  }
  printf("请输入需要删除的人的名字>>>\n");
  scanf("%s",name);
  int pos=FindByName(pc,name);
  if(pos==-1)
  {
    printf("要删除的人不存在>>>\n");
    return;
  }
  int i;
  for(i=pos;i<pc->count-1;i++)
  {
    pc->data[i]=pc->data[i+1];
  }
  pc->count--;
  printf("删除成功>>>\n");
}
void SearchContact(Contact*pc)
{
  char name[MAX_NAME]={0};
  assert(pc);
  printf("请输入需要查找的人的名字>>>\n");
  scanf("%s",name);
  int pos=FindByName(pc,name);
  if(pos==-1)
  {
  printf("要查找的人不存在>>>\n");
  return;
  }
  else
  {
    printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n","姓名","年龄","性别","电话","地址");
    printf("%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n",pc->data[pos].name,
                                              pc->data[pos].age,
                                              pc->data[pos].sex,
                                              pc->data[pos].tele,
                                              pc->data[pos].addr);
    printf("查找成功>>>\n");                                            
  }
}
void ModifyContact(Contact*pc)
{
  char name[MAX_NAME]={0};
  assert(pc);
  printf("请输入需要修改的人的名字>>>\n");
  scanf("%s",name);
  int pos=FindByName(pc,name);
  if(pos==-1)
  {
  printf("要修改的人不存在>>>\n");
  return;
  }
  printf("要修改的信息已经查找到,接下来开始修改>>>\n");
  printf("请输入姓名>>>\n");
  scanf("%s",pc->data[pos].name);
  printf("请输入年龄>>>\n");
  scanf("%d",&(pc->data[pos].age));
  printf("请输入性别>>>\n");
  scanf("%s",pc->data[pos].sex);
  printf("请输入电话>>>\n");
  scanf("%s",pc->data[pos].tele);
  printf("请输入地址>>>\n");
  scanf("%s",pc->data[pos].addr);
  printf("修改成功>>>\n");
}
int cmp(const void*a,const void*b)
{
    return strcmp(((PeoInfo*)a)->name,((PeoInfo*)b)->name);
}
void SortContact(Contact*pc)
{
    assert(pc);
    qsort(pc->data, pc->count,sizeof(PeoInfo),cmp);
    printf("排序成功\n");
}
void DestroyContact(Contact*pc)
{
  assert(pc);
  free(pc->data);
  pc->data=NULL;
}
void SaveContact(Contact*pc)
{
  assert(pc);
  FILE*pfWrite;
  if((pfWrite=fopen("C:\\code\\C\\contact.txt","wb"))==NULL)
  {
    printf("Can not open the file!\n");
    exit(0);
  }
  int i=0;
  for(i=0;i<pc->count;i++)
  {
    fwrite(pc->data+i,sizeof(PeoInfo),1,pfWrite);
  }
  if(fclose(pfWrite))
  {
    printf("Can not close the File!\n");
    exit(0);
  }
}




