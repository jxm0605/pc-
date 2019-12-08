#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct customer{ 
    char number[10]; // 001\0 
    char name[20];
    char time_begin[20];
    char time_end[20];
    char member[4];
    int money;
};

/*
*Get_sum()
*Get data rows from file
*Afferent: file name
*Return : Data rows
*/
int Get_sum(const char * filename) {
    FILE * filedata;
    int sum = 0;
    int flag = '\n';
    filedata = fopen(filename,"r");
    if(filedata){
        while(!feof(filedata)){
            flag = fgetc(filedata);
            if(flag == '\n')
                sum++;
        }
        sum++;
    }
    else{
        printf("Can't open %s\n",filename);
        exit(1);
     }
    fclose(filedata);
    return sum;
}

/*
*Get_data()
*Get all data from file
*Afferent: file name,struct customer
*Return : void
*/
void Get_data(const char * filename,struct customer * Customer) {
    FILE * filedata;
    int i;
    
    filedata = fopen(filename,"r");
    if(filedata){
        i=0;
        while(!feof(filedata)){
            fscanf(filedata,"%s%s%s%s%s",Customer[i].number,Customer[i].name,Customer[i].time_begin,Customer[i].time_end,Customer[i].member);
            i++;
        }
    }
    else{
        printf("Can't open %s\n",filename);
        exit(1);
     }
    fclose(filedata);   
}

/*
*Print_data()
*Show all data
*Afferent: sum,struct customer
*Return : void
*/
void Print_data(int sum,struct customer * Customer) {
    int i;
    printf("\nUser Information:\n\n\tnumber\tname\tbegin\tend\tmember\n");
    for(i=0;i<sum;i++)
        printf("\t%s\t%s\t%s\t%s\t%s\n",Customer[i].number,Customer[i].name,Customer[i].time_begin,Customer[i].time_end,Customer[i].member);
    printf("\n");
}

/*
*Print_member()
*Show member data
*Afferent: sum,struct customer
*Return : void
*/
void Print_member(int sum,struct customer * Customer) {
    int i;
    printf("\nMember Information:\n\n\tnumber\tname\tmember\n");
    for(i=0;i<sum;i++){
        if(!(strcmp(Customer[i].member, "yes")))
            printf("\t%s\t%s\t%s\n",Customer[i].number,Customer[i].name,Customer[i].member);
    }
    printf("\n");
    for(i=0;i<sum;i++){
        if(!(strcmp(Customer[i].member, "no")))
            printf("\t%s\t%s\t%s\n",Customer[i].number,Customer[i].name,Customer[i].member);
    }
    printf("\n");
}

/*
*Print_money()
*Show member data
*Afferent: sum,struct customer
*Return : void
*/
void Print_money(int sum,struct customer * Customer) {
    int i;
    int begin,end,t;
    int all_money=0;
    printf("\nMoney Information:\n\n\tnumber\tname\tbegin\tend\tmember\ttime\tmoney\n");
    for(i=0;i<sum;i++){
        begin = (Customer[i].time_begin[0]-'0')*10+(Customer[i].time_begin[1]-'0');
        end = (Customer[i].time_end[0]-'0')*10+(Customer[i].time_end[1]-'0');
        t = end-begin;
        if((Customer[i].time_end[3]>Customer[i].time_begin[3]) || ((Customer[i].time_end[3] == Customer[i].time_begin[3])&&(Customer[i].time_end[4] > Customer[i].time_begin[4])))
            t++;
        if(!(strcmp(Customer[i].member, "yes")))
             Customer[i].money = 1000*t;
        if(!(strcmp(Customer[i].member, "no")))
             Customer[i].money = 1500*t;
        all_money += Customer[i].money;
        
        printf("\t%s\t%s\t%s\t%s\t%s\t%dh\t%d\n",Customer[i].number,Customer[i].name,Customer[i].time_begin,Customer[i].time_end,Customer[i].member,t,Customer[i].money);
    }
    printf("\tAll money :%d\n",all_money);
}

int main () {
    char filename[] = "data.txt";
    struct customer * Customer = NULL;
    int sum;
    char choice;

    // initialize:
    sum = Get_sum(filename);
    Customer = (struct customer *)malloc(sizeof(struct customer)*sum);
    Get_data(filename,Customer);

    // menu:
    while(1){
        printf("\x1b[H\x1b[2J"); //clear screen
        printf("#********** Internet Bar **********#\n");
        printf("#                                  #\n");
        printf("#  1. Show User information.       #\n");
        printf("#  2. Membership information.      #\n");
        printf("#  3. Business information.        #\n");
        printf("#  q. Exit procedure.              #\n");
        printf("#                                  #\n");
        printf("#**********************************#\n");
        printf("Please enter your choice: ");
        scanf("%c",&choice);
        getchar();
        
        // function:
        printf("\x1b[H\x1b[2J"); //clear screen
        switch (choice)
        {
        case '1':   
            Print_data(sum,Customer);
            break;
        case '2':   
            Print_member(sum,Customer);
            break;
        case '3':   
            Print_money(sum,Customer);
            break;
        case 'q':   
            exit(0);
        default:
            printf("Please enter the correct option!!\n");
            break;
        }
        getchar();
    }

    return 0;
}