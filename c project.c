#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct
{
    char username[20];
    char password[20];
    double best_grade;
    int num_of_line_of_best;
    double last_grade;
    int num_of_line_of_last;
}user;

int chek_first_info = 0;
int info_num = 0;
int user_num;
user* info;

void get_num(void);
void get_info(void);
int login(void);
void menu(void);
double run_grade(double time, char pragraph[], char test_pragraph[]);
void sort(void);
void set1(int num_aray1, int num_aray2);
void set2(user hold,int num_aray);
void search_grades(double grade);
void search_names(char name[20]);


int main()
{
    get_num();
    info = malloc(sizeof(user)*info_num);
    get_info();
    int start = 0;
    while(start == 0)
    {
    if(login()==0)
    {
    put_info();
    put_num();
    free(info);
    return 0;
    }
    printf("\n***Wellcome**");
    menu();
    }
}

void get_num(void)
{
    FILE* i_num;
    i_num = fopen("info_num.txt","r");
    if(i_num==NULL)
    {
    FILE* creat;
    creat = fopen("info_num.txt","w");
    fprintf(creat,"0");
    fclose(creat);
    i_num = fopen("info_num.txt","r");
    }
    fscanf(i_num,"%d",&info_num);
    fclose(i_num);
    if(info_num!=0)
    {chek_first_info++;}


    return;
}

void get_info(void)
{
    if(info_num==0)
    {
    FILE* creat;
    creat = fopen("User_info.txt","wb");
    fclose(creat);
    }
    FILE* User_info;
    User_info = fopen("User_info.txt","rb");
    fread(info,sizeof(user),1,User_info);
    fclose(User_info);

    return;
}

int login(void)
{
    int num;
    while(num!=3)
    {
    printf("\n1- Sign in\n");
    printf("2- sign up\n");
    printf("3- Exist\n");
    
    printf("Enter your request :");
    scanf("%d",&num);

    if(num==1)
    {
    int check = 0;
    while (check==0)
    {
        if(chek_first_info==0)
        {
            printf("\n***************\nYou did not sign up\n***************\n");
            break;
        }
    char usern[20];
    char pass[20];

    printf("\nEnte your\nUsername :");
    scanf("%s",usern);
    printf("Password :");
    scanf("%s",pass);
    for(int i = 0; i < info_num; i++)
    {
    int n=strcmp(info[i].username, usern);
    int m=strcmp(info[i].password, pass);
    if(n==0&&m==0)
    {
        user_num = i;
        return 1;
        
    }
    }
        check = 0;
        int choos,check_1=0;
        printf("\nYour password or username is invalid\n");
        printf("\nIf you want try agan enter 1 or enter 2 to back to menu :");
        while(check_1==0)
        {
        scanf("%d",&choos);
        if(choos==1)
        {check_1++;}
        if(choos==2)
        {check++;break;}
        else
        {
            printf("Please enter correct number\n");
        }
        }
    }

    }
    if(num==2)
    {
    char usern[20];
    char pass1[20];
    char pass2[20];
    
    int check_username=0;
    while(check_username==0)
    {
    printf("Username :");
    scanf("%s",usern);
    int check_user=0;
    for (int i = 0; i < info_num; i++)
    {
       if(0==strcmp(usern,info[i].username))
       {check_user++;}
    }
    
    if(check_user==0)
    {
    int check=0;
    while (check==0)
    {
        printf("Password :");
        scanf("%s",pass1);
        printf("repeat passwod :");
        scanf("%s",pass2);

        int ch = strcmp(pass2,pass1);
        if(ch!=0)
        {
            printf("\n***Password is not same***\n");
        }
        else
        {
            info_num++;
        
            info = realloc(info, sizeof(user)*info_num);
            strcpy(info[info_num-1].username,usern);
            strcpy(info[info_num-1].password,pass1);
            info[info_num-1].best_grade=0;
            printf("\nYour sign up was sucssesful");
            chek_first_info++;
            check_username++;
            check++;
        }
    }
    }
    else
    {
        printf("\n******\nThis user is here   choose enother username\n******\n");
    }
    }
    }

    if(num==3)
    {
        return 0;
    }
    if(num!=3&&num!=2&&num!=1)
    {
        printf("\n************************\n");
        printf("Incorect number\n");
        printf("************************\n");
    }

    }
}

void menu(void)
{

    int num = 0;
    while(num!=6)
    {
        printf("\n\n1- Type Testing");
        printf("\n2- View sorted Statistical info");
        printf("\n3- Search users by their best scores");
        printf("\n4- Search users by names");
        printf("\n5- Change Password");
        printf("\n6- Logout\n");

        printf("\nEnter your request :");
        scanf("%d",&num);

        if(num==1)
        {
            char pragraph[5][90];
            FILE*pragraphf;
            pragraphf=fopen("pragraph.txt","r");
            for (int i = 0; i < 5; i++)
            {
                fgets(pragraph[i],90,pragraphf);
            }
            fclose(pragraphf);
            int check_test = 0;
            while(check_test==0)
            {
            char test_pragraph[100];
            int pragraph_num = rand()%(4-0+1)+0;
            printf("\nWrite pragraph and then click enter");
            printf("\nPragraph num is :%d\n",pragraph_num+1);
            printf("\n%s",pragraph[pragraph_num]);
            gets(test_pragraph);
            
            time_t start_t, end_t;
            double diff_t;

            time(&start_t);
            gets(test_pragraph);
            time(&end_t);

            diff_t = difftime(end_t,start_t);
            char p_send[90];
            strcpy(p_send,pragraph[pragraph_num]);
            double grade = run_grade(diff_t, p_send, test_pragraph);
            printf("\n****Your grade is :%f****\n",grade);
            info[user_num].last_grade = grade;
            info[user_num].num_of_line_of_last = pragraph_num+1;
            if(grade>info[user_num].best_grade)
            {
                info[user_num].best_grade = grade;
                info[user_num].num_of_line_of_best = pragraph_num+1;
            }
           
            int check_back = 0;
            while(check_back==0)
            {
            printf("\nIf you want ti try again click 1 or click 2 to back to menu :");
            int choose;
            scanf("%d",&choose);
            if(choose==1)
            {check_back++;}
            if(choose==2)
            {check_test++;check_back++;}
            else
            {}
            }
            }
        }
        if(num==2)
        {
            sort();
            for (int i = 0; i < info_num; i++)
            {
                printf("\n%d)Username : %s",i+1,info[i].username);
                printf("\n  Best grade : %f  for pragraph :%d",info[i].best_grade,info[i].num_of_line_of_best);
                printf("\n  Last grade : %f  for pragraph :%d",info[i].last_grade,info[i].num_of_line_of_last);
            }
            
        }
        if(num==3)
        {
            double search;
            printf("\nEnter best grade :");
            scanf("%lf",&search);
            search_grades(search);

        }
        if(num==4)
        {
            char name[20];
            printf("\nEnter Username :");
            gets(name);
            gets(name);
            search_names(name);
        }
        if(num==5)
        {
            char check_user[20];
            printf("\nYour username is :%s",info[user_num].username);
            int check_pass=0;
            while(check_pass == 0)
            {
            printf("\nEnter your password :");
            scanf("%s",check_user);
            int c=strcmp(info[user_num].password,check_user);
            if(c==0)
            {
                check_pass++;
                int check_new_pass = 0;
                while(check_new_pass == 0)
                {
                    char new_pass1[20];
                    char new_pass2[20];
                    printf("\nEnter new password :");
                    scanf("%s",new_pass1);
                    printf("Enter password again :");
                    scanf("%s",new_pass2);

                    int v=strcmp(new_pass2,new_pass1);
                    if(v==0)
                    {
                        check_new_pass++;
                        strcpy(info[user_num].password,new_pass2);
                        printf("\n**Your password has succsesfuly changed**");
                    }
                    else
                    {
                        printf("\n******\nThise password not same\n******\n");
                    }
                }
            }
            else
            {
                printf("\n******\nYour password is incorrect\n******\n");
            }
            }

        }
        if(num==6)
        {
            return;
        }

    }
}

double run_grade(double time, char pragraph[], char test_pragraph[])
{
    double correcct_char = 0;
    double num_of_pragraph = strlen(pragraph);
    double num_of_test_pragraph = strlen(test_pragraph);
    for (int i = 0; i < num_of_pragraph; i++)
    {
        if(pragraph[i]==test_pragraph[i])
        {correcct_char++;}
    }
    double time_min = time/60;
    double words = (correcct_char/num_of_pragraph)*100;
    double times = (num_of_test_pragraph/time_min)*2;
    return words+times;
}

void sort(void)
{
    user hold;
    for ( int i = 0; i < info_num - 1 ; i++ )
        {
        for ( int j = 0; j < info_num - 1; j++ )
            {
            if ( info[ j ].best_grade < info[ j + 1 ].best_grade )
            {
                hold.best_grade = info[ j ].best_grade;
                hold.last_grade = info[ j ].last_grade;
                hold.num_of_line_of_best = info[ j ].num_of_line_of_best;
                hold.num_of_line_of_last = info[ j ].num_of_line_of_last;
                strcpy(hold.password,info[ j ].password);
                strcpy(hold.username,info[ j ].username);

            set1(j,j+1);
            set2(hold,j+1);
            }
            }
        }
    return;
}

void set1(int num_aray1, int num_aray2)
{
    info[ num_aray1 ].best_grade = info[ num_aray2 ].best_grade;
    info[ num_aray1 ].last_grade = info[ num_aray2 ].last_grade;
    info[ num_aray1 ].num_of_line_of_best = info[ num_aray2 ].num_of_line_of_best;
    info[ num_aray1 ].num_of_line_of_last = info[ num_aray2 ].num_of_line_of_last;
    strcpy(info[ num_aray1 ].password,info[ num_aray2 ].password);
    strcpy(info[ num_aray1 ].username,info[ num_aray2 ].username);

    return;
}

void set2(user hold,int num_aray)
{
    info[ num_aray ].best_grade = hold.best_grade;
    info[ num_aray ].last_grade = hold.last_grade;
    info[ num_aray ].num_of_line_of_best = hold.num_of_line_of_best;
    info[ num_aray ].num_of_line_of_last = hold.num_of_line_of_last;
    strcpy(info[ num_aray ].password,hold.password);
    strcpy(info[ num_aray ].username,hold.username);

    return;
}

void search_grades(double grade)
{
    for (int i = 0; i < info_num; i++)
    {
        if (info[i].best_grade==grade)
        {   
            printf("\nUsername : %s",info[i].username);
            printf("\nBest grade : %f  for pragraph :%d",info[i].best_grade,info[i].num_of_line_of_best);
            printf("\nLast grade : %f  for pragraph :%d",info[i].last_grade,info[i].num_of_line_of_last);    
            return;        
        }
    }
    printf("\nThise grade is not avalable");
    return;
    
}

void search_names(char name[20])
{
    for (int i = 0; i < info_num; i++)
    {
        int c = strcmp(name,info[i].username);
        if(c==0)
        {
            printf("\nUsername : %s",info[i].username);
            printf("\nBest grade : %f  for pragraph :%d",info[i].best_grade,info[i].num_of_line_of_best);
            printf("\nLast grade : %f  for pragraph :%d",info[i].last_grade,info[i].num_of_line_of_last);    
            return;        
        }
    }
    printf("\nThise Username is not avalable");
    return;
    
}

void put_info(void)
{
    FILE* User_info;
    User_info = fopen("User_info.txt","wb");
    fwrite(info,sizeof(user),info_num,User_info);
    fclose(User_info);   

    return;
}

void put_num(void)
{
    FILE* i_num;
    i_num = fopen("info_num.txt","w");
    fprintf(i_num,"%d",info_num);
    fclose(i_num);

    return;
}

