//jaggu1999
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define flush fflush(stdin);
#define lli long long

void importFromFile(char *fname,lli sheet[][10])
{
    FILE *f = fopen(fname,"r");
    if(f==NULL)
        printf("What the 404...\nError Opening File!!\n");
    else
    {
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                fscanf(f,"%lld",&sheet[i][j]);
        printf("Imported Successfully!!\n");
    }
    fclose(f);
}

void set(char *string,lli sheet[][10])
{
    int row=string[0]-48,col,flag=0;
    if(string[1]>=65 && string[1]<=90)
        col=string[1]-65;
    else col=string[1]-97;
    if(string[3]==' ' || string[3]=='=')
        printf("What the 404...\nInvalid Syntax or Command\n");
    else
    {
        lli value=0;
        for(int i=3;string[i]!='\0';i++)
        {
            if(string[i]>=48 && string[i]<=57)
                    value=value*10+(string[i]-48);
            else
            {
                printf("What the 404...\nInvalid Syntax or Command\n");
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            sheet[row][col]=value;
            printf("Value is Set successfully\n");
        }
    }
}

lli get(char *string,lli sheet[][10])
{
    int row=string[0]-48,col;
    if(string[1]>=65 && string[1]<=90)
        col=string[1]-65;
    else col=string[1]-97;
    return sheet[row][col];
}

void print(lli sheet[][10])
{
    printf("\nExcel Sheet:\n\n");
    for(int i=0;i<11;i++)
    {
        if(i==0)
        {
            char alpha=65;
            printf(" \t");
            for(int j=0;j<10;j++)
                printf("%c\t",alpha++);
            printf("\n");
        }
        else{
            printf("%d\t",i-1);
            for(int j=0;j<10;j++)
                printf("%lld\t",sheet[i-1][j]);
        }
        printf("\n\n");
    }
}

char *split(char *str,int *start)
{
    char *string=(char *)malloc(100);
    int i=0,j=*start;
    while((str[j]!='\0') && (str[j]!=' '))
    {
        string[i]=str[j];
        j++;
        i++;
    }
    string[i]='\0';
    *start=++j;
    return string;
}

int check(char *command)
{
    if(strcmpi(command,"help")==0)
        return 1;
    if(strcmpi(command,"import")==0)
        return 2;
    if(strcmpi(command,"set")==0)
        return 3;
    if(strcmpi(command,"get")==0)
        return 4;
    if(strcmpi(command,"print")==0)
        return 5;
    if(strcmpi(command,"export")==0)
        return 6;
    if(strcmpi(command,"exit")==0)
        return 0;
    return -1;
}

void exportToFile(char *fname,lli sheet[][10])
{
    FILE *temp=fopen("temporary.txt","w+");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            fprintf(temp,"%lld", sheet[i][j]);
            if(j!=9)
                fprintf(temp," ");
        }
        fprintf(temp,"\n");
    }
    fclose(temp);
    rename(fname,"temp.txt");
    rename("temporary.txt",fname);
    remove("temp.txt");
    printf("Exported Successfully!!\n");
}

signed main()
{
    long long sheet[10][10]={0},value;
    char string[100];
    printf(">>>>>>>>>>>>>>> Welcome to Excel Sheets!! <<<<<<<<<<<<<<<\n\n");
    printf("Credits: Jagadeesh Kumar Ch\n\n");
    printf("Email: jagadeeshch1999@gmail.com\n\n");
    printf("Type \"help\" for help\n\n");
    for(;;)
    {
        flush;
        printf(">> ");
        scanf("%[^\n]s",string);
        int pos=0,cmd=check(split(string,&pos));
        switch (cmd)
        {
            case 1: printf("\nCommands available are:\n\n");
                    printf("1-> import <filename>\n\n2-> set <row><column>=<value>\n\n3-> get <row><column>\n\n4-> print\n\n5-> export <filename>\n\n6-> exit\n");
                    break;
            case 2: printf("Importing File...\n");
                    importFromFile(split(string,&pos),sheet);
                    break;
            case 3: set(split(string,&pos),sheet);
                    break;
            case 4: printf("%lld\n",get(split(string,&pos),sheet));
                    break;
            case 5: print(sheet);
                    break;
            case 6: printf("Exporting File...\n");
                    exportToFile(split(string,&pos),sheet);
                    break;
            case 0: printf("Go and have a Cup of Coffee...\n");
                    exit(0);
            default: printf("\nWhat the 404...\nInvalid Syntax or Command!!\n");
                     break;
        }
        printf("\n");
    }
    return 0;
}
