#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct student
{
  char name[25]; //name of the student
  int id;        //id of the student
  int x_val;     //x co-ordinate of student's location
  int y_val;     //y co-ordinate of student's location
  int distance;
  struct student *link;
  char cluster_name[25];
  int cluster_id;
  int cluster_x;
  int cluster_y;
};
typedef struct student *student;


struct study_centre
{
  char name[25]; //name of the study centre
  int id;        //id of the study centre
  int x;         //x co-ordinate of study centre's location
  int y;        //y co-ordinate of study centre's location
  struct study_centre *centre_link;
};
typedef struct study_centre *study;


int x_cluster[25],y_cluster[25],x_num=0,y_num=0;


student get_student();
study get_study();
int distance(int centre_x,int centre_y,int student_x,int student_y);
void input_student(int n,student head);
void input_centre(int n,study centre_head);
void display(student head);
void display_centre(study centre_head);
void allocation(student head,study centre_head);
int minimum(int a,int b,int c);
void allotment(student head);
void centroid_mean(student head,study centre_head);
int mean_calculation(int a[25],int n);
void print_info(student head);

student get_student()  //structure for the student
{
 student x;
 x=(student)malloc(sizeof(struct student));
 x->link=NULL;
 return x;
}

study get_study()//structure for the study centre
{
 study x;
 x=(study)malloc(sizeof(struct study_centre));
 x->centre_link=NULL;
 return x;
}

int distance(int centre_x,int centre_y,int student_x,int student_y)//function to calculate distance between two points
{
 int d,x,y;
 x=centre_x-student_x;
 y=centre_y-student_y;
 d=sqrt((x*x)+(y*y));
 return d;

}

void input_student(int n,student head)//function to take the details of students as input and store it in the linked list
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

void input_centre(int n,study centre_head)//function to take the details of students as input and store it in the linked list
{
 int i,x,y;
 study temp,cur,prev;

 for(i=1;i<=n;i++)
 {
   temp=get_study();
   //printf("Name:");
   scanf("%s",temp->name);
   //printf("Id:");
   scanf("%d",&temp->id);
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

void display(student head)//function to display the details of students
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
void display_centre(study centre_head)//function to display the details of study centre
{
 study cur,prev;
 cur=centre_head->centre_link;
 prev=NULL;
 while(cur!=NULL)
 {
  printf("%s  ",cur->name);
  printf("%d  ",cur->id);
  printf("%d  ",cur->x);
  printf("%d\n",cur->y);
  prev=cur;
  cur=cur->centre_link;
  
 }
}

void allocation(student head,study centre_head)//function in which students are allocated to a particular study centre based on nearest distance
{
 float d1,d2,d3,least_distance;
 student stu_cur,stu_prev;
 study centre_cur,centre_prev;
 stu_cur=head->link;
 stu_prev=NULL;
 

 while(stu_cur!=NULL)
 {
  centre_cur=centre_head->centre_link;
  centre_prev=NULL;
  d1=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val);
  //distance between the student and first study centre


  centre_prev=centre_cur;
  centre_cur=centre_cur->centre_link;
  d2=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val);
  //distance between the student and second study centre
 
  centre_prev=centre_cur;
  centre_cur=centre_cur->centre_link;
  d3=distance(centre_cur->x,centre_cur->y,stu_cur->x_val,stu_cur->y_val);
  //distance between the student and third study centre

  least_distance=minimum(d1,d2,d3);//least distance is calculated

  if(least_distance==d3)// if least distance is d3 then student is allocated to 3rd study centre
  {
   strcpy(stu_cur->cluster_name,centre_cur->name);
   stu_cur->cluster_x=centre_cur->x;
   stu_cur->cluster_y=centre_cur->y;
   stu_cur->cluster_id=centre_cur->id;
   stu_cur->distance=d3;
  }

  else if(least_distance==d2)// if least distance is d2 then student is allocated to 2nd study centre
  {
   strcpy(stu_cur->cluster_name,centre_prev->name);
   stu_cur->cluster_x=centre_prev->x;
   stu_cur->cluster_y=centre_prev->y;
   stu_cur->cluster_id=centre_cur->id;
   stu_cur->distance=d2;
  }


  else if(least_distance==d1)// if least distance is d1 then student is allocated to 1st study centre
  {
   centre_cur=centre_head->centre_link;
   strcpy(stu_cur->cluster_name,centre_cur->name);
   stu_cur->cluster_x=centre_cur->x;
   stu_cur->cluster_y=centre_cur->y;
   stu_cur->cluster_id=centre_cur->id;
   stu_cur->distance=d1;
  }
  
  stu_prev=stu_cur;
  stu_cur=stu_cur->link;
 }
  
}

int minimum(int a,int b,int c)//function to calculate the smallest number among three numbers
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

void allotment(student head)//function to display the allocated study centre fo the students along with x and y co-ordinates
{
  int i;
  student cur,prev;
  cur=head->link;
  while(cur!=NULL)
  {
    printf("%s   %s  %d  %d\n",cur->name,cur->cluster_name,cur->cluster_x,cur->cluster_y);
    prev=cur;
    cur=cur->link;
  }
}

void centroid_mean(student head,study centre_head)//function to change the actual value of the co-ordinates of the centroid to the mean value after allotment of students
{
  float x_mean,y_mean;
  study centre_cur,centre_prev;
  student stu_cur,stu_prev;
  
  centre_cur=centre_head->centre_link;
  //centre_prev=NULL;
  while(centre_cur!=NULL)
  {
     stu_cur=head->link;
     stu_prev=NULL;
     
     while(stu_cur!=NULL)
     {

       if(centre_cur->id==stu_cur->cluster_id)
        {
          x_cluster[x_num]=stu_cur->x_val;//each value of x is stored in array
          y_cluster[y_num]=stu_cur->y_val;//each value of y is stored in array
          x_num++;
          y_num++;
        }
       
       x_mean=mean_calculation(x_cluster,x_num);
       y_mean=mean_calculation(y_cluster,y_num);
       
       centre_cur->x=x_mean;
       centre_cur->y=y_mean;

       //stu_prev=stu_cur;
       stu_cur=stu_cur->link;
     }
     //centre_prev=centre_cur;
     centre_cur=centre_cur->centre_link;
  }
}

int mean_calculation(int a[25],int n)//function to calculate the mean value for x and y of the centroids
{
 int i,sum=0,result;
 for(i=0;i<n;i++)
 {
  sum+=a[i];
 }
 result=sum/n;
 return result;
}
void print_info(student head)
{
  student stu_cur;
  
  printf("\n-------------------------------------------------\n");
  printf("               student information                   \n");
  printf("NAME   ID   STU_X   STU_Y  DISTANCE CENTRE NAME CENTRE ID CENTRE_X CENTRE_Y\n");
  

  stu_cur=head->link;
  while(stu_cur!=NULL)
  {
   printf("%s        %d        %d       ",stu_cur->name,stu_cur->id,stu_cur->x_val);
   printf("%d        %d        %s       ",stu_cur->y_val,stu_cur->distance,stu_cur->cluster_name);
   printf("%d      %d      %d\n",stu_cur->cluster_id,stu_cur->cluster_x,stu_cur->cluster_y);
   stu_cur=stu_cur->link;
  }

}
int main()
{
 int n,i;
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
 allocation(head,centre_head);
 printf("First iteration\n");
 allotment(head);
 allocation(head,centre_head);
 printf("after 1 iteration\n");
 //for(i=1;i<=2;i++)
 {
 centroid_mean(head,centre_head);
 allocation(head,centre_head);
 }
 allotment(head);
 print_info(head);
return (0);
}

