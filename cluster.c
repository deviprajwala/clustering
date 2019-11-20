#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct student
{
  char name[25]; //name of the student
  int id;        //id of the student
  int x_val;     //x co-ordinate student's location
  int y_val;     //y co-ordinate student's location
  int distance;
  struct student *link;
  char cluster_name[25];
  int cluster_x;
  int cluster_y;
};
typedef struct student *student;


struct study_centre
{
  char name[25]; //name of the student
  int x;         //x co-ordinate study centre's location
  int y;        //y co-ordinate study centre's location
  struct study_centre *centre_link;
};
typedef struct study_centre *study;

student get_student();
study get_study();
int distance(int centre_x,int centre_y,int student_x,int student_y);
void input_student(int n,student head);
void input_centre(int n,study centre_head);
void display(student head);
void display_centre(study centre_head);
void allocation(student head,study centre_head);
int minimum(int a,int b,int c);

student get_student()
{
 student x;
 x=(student)malloc(sizeof(struct student));
 x->link=NULL;
 return x;
}

study get_study()
{
 study x;
 x=(study)malloc(sizeof(struct study_centre));
 x->centre_link=NULL;
 return x;
}

int distance(int centre_x,int centre_y,int student_x,int student_y)
{
 int d;
 d=sqrt(((centre_x-student_x)*(centre_x-student_x))-((centre_y-student_y)*(centre_y-student_y)));
 return d;

}

void input_student(int n,student head)
{
 int i,x,y,id;
 student temp,cur,prev;

 for(i=1;i<=n;i++)
 {
   temp=get_student();
   //printf("Name:");
   scanf("%s",temp->name);
   //printf("Id:");
   scanf("%d",&id);
   temp->id=id;
   //printf("x location:");
   scanf("%d",&x);
   temp->x_val=x;
   //printf("y location:");
   scanf("%d",&y);
   temp->y_val=y;
   
   if(head->link==NULL)
   {
      head->link=temp;
      
   }
   else
   {
     cur=head;
     prev=NULL;
     while(cur!=NULL)
     {
       prev=cur;
       cur=cur->link;
     }
     prev->link=temp;
   }
 }
}

void input_centre(int n,study centre_head)
{
 int i,x,y;
 study temp,cur,prev;

 for(i=1;i<=n;i++)
 {
   temp=get_study();
   //printf("Name:");
   scanf("%s",temp->name);
   //printf("x location:");
   scanf("%d",&temp->x);
   //printf("y location:");
   scanf("%d",&temp->y);
   
   if(centre_head->centre_link==NULL)
   {
      centre_head->centre_link=temp;
      
   }
   else
   {
     cur=centre_head;
     prev=NULL;
     while(cur!=NULL)
     {
       prev=cur;
       cur=cur->centre_link;
     }
     prev->centre_link=temp;
   }
 }
}

void display(student head)
{
 student cur,prev;
 cur=head->link;
 prev=NULL;
 while(cur!=NULL)
 {
  printf("%s  ",cur->name);
  printf("%d  ",cur->id);
  printf("%d  ",cur->x_val);
  printf("%d\n",cur->y_val);
  prev=cur;
  cur=cur->link;
  
 }
}
void display_centre(study centre_head)
{
 study cur,prev;
 cur=centre_head->centre_link;
 prev=NULL;
 while(cur!=NULL)
 {
  printf("%s  ",cur->name);
  printf("%d  ",cur->x);
  printf("%d\n",cur->y);
  prev=cur;
  cur=cur->centre_link;
  
 }
}

void allocation(student head,study centre_head)
{
 int d1,d2,d3,least_distance;
 student stu_cur,stu_prev;
 study centre_cur,centre_prev;
 stu_cur=head->link;
 stu_prev=NULL;
 

 while(stu_cur!=NULL)
 {
  centre_cur=centre_head->centre->link;
  centre_prev=NULL;
  d1=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val)

  prev=centre_cur;
  centre_cur=centre_cur->centre_link;
  d2=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val)
   
  prev=centre_cur;
  centre_cur=centre_cur->centre_link;
  d3=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val)
  
  least_distance=minimum(d1,d2,d3);

  if(least_distance==d3)
  {
   strcpy(stu_cur->name,centre_cur->name);
   stu_cur->cluster_x=centre_cur->x;
   stu_cur->cluster_y=centre_cur->y;
  }

  else if(least_distance==d2)
  {
   strcpy(stu_cur->name,prev_cur->name);
   stu_cur->cluster_x=prev_cur->x;
   stu_cur->cluster_y=prev_cur->y;
  }


  centre_cur=centre_head->centre->link;
  else if(least_distance==d1)
  {
   strcpy(stu_cur->name,centre_cur->name);
   stu_cur->cluster_x=centre_cur->x;
   stu_cur->cluster_y=centre_cur->y;
  }
  
  stu_prev=stu_cur;
  stu_cur=stu_cur->link;
 }
  
}

int minimum(int a,int b,int c)
{
 if((a<b)&&(a<c))
 {
  return a;
 }
 else if((b<a)&&(b<c))
 {
  return b;
 }
 else
 {
  return c;
 }
}
int main()
{
 int n;
 student head;
 head=get_student();
 study centre_head;
 centre_head=get_study();
 printf("Enter number of students\n");
 scanf("%d",&n);
 printf("Enter the details of students:\n");
 input_student(n,head);
 printf("Enter the details of 3 study centres:\n");
 input_centre(3,centre_head);
 printf("\n-------------------------------------------------------------\n");
 display(head);
 printf("\n-------------------------------------------------------------\n");
 display_centre(centre_head);
 printf("\n-------------------------------------------------------------\n");
return (0);
}

