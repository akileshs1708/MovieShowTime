#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100
int bookid=1232;

int book[MAX][MAX]={0};
int lay[MAX]={0};
int movieCount;

char movies[MAX][MAX] = {0};
char date_string[10];
void movielist(){
        FILE *file = fopen("movies.txt", "r");
        if (file == NULL) {
            printf("Error: Unable to open the movie list file.\n");
            return;
        }
        movieCount=0;
        while (fgets(movies[movieCount], MAX, file) != NULL) {
            char* newline = strchr(movies[movieCount], '\n');
            if (newline != NULL) {
                *newline = '\0';
            }
            movieCount++;
        }
}

int bookticket()
{
    int ch,n;
l2:
    n=0;
	printf("\nMOVIES LIST\n\n");
	for(int i=0;i<MAX;i++){
	    if(movies[i][0]!=0){
		    printf("%d. %s\n\n",i+1,movies[i]);
	    }
	}
	printf("Enter movie to book tickets: ");
	scanf("%d",&ch);
	for(int i=0;i<MAX;i++){
        if(book[i][0]!=0){
            if(book[i][0]==ch){
                n=1;
            }
        }
	}
	if(n==0){
        printf("\nMovie Not found !!!\n\n");
        goto l2;
	}
	return ch;
}

int movieDate(){
    int date;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\nShow Date\n\n");
    printf("1. %02d-%d\n\n",tm.tm_mday,tm.tm_mon + 1);
    for (int i = 1; i < 4; i++){
        t += 24 * 3600;
        tm = *localtime(&t);
        printf("%d. %02d-%d\n\n",i+1,tm.tm_mday,tm.tm_mon + 1);
    }
    printf("Enter The Show Date: ");
    scanf("%d",&date);
    return date;
}

int timing(){
    int time,n;
l1:
    n=0;
    printf("\nShow Timing \n\n");
    printf("1. 09:00 am\n\n");
    printf("2. 12:00 pm\n\n");
    printf("3. 06:00 pm\n\n");
    printf("Enter the show timing: ");
    scanf("%d",&time);
    for(int i=0;i<MAX;i++){
        if(book[i][2]!=0){
            if(book[i][2]==time){
                n=1;
            }
        }
	}
	if(n==0){
        printf("\nShow Not found !!!\n\n");
        goto l1;
	}

    return time;
}

void seat(){
    FILE* file = fopen("seat_layout.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open the seat layout file.\n");
    }
    int i=0,num;
    while (fscanf(file,"%d",&num) != EOF) {
        lay[i]=num;
        i++;
    }
    fclose(file);
}

void layout(int z,int d,int t){
    int arr[MAX]={0},n,l[MAX]={0},v;
    for(int i=0;i<MAX;i++){
        if(book[i][0]!=0){
            if(book[i][0]==z&&book[i][1]==d&&book[i][2]==t){
                for(int j=3;j<MAX;j++){
                    if(book[i][j]!=0){
                        arr[n]=book[i][j];
                        n++;
                    }
                }
            }
        }
    }
    for(int i=0;i<MAX;i++){
        l[i]=lay[i];
    }

    printf("--------------------------------------------------------------------------\n");
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            if(arr[i]==l[j]){
                l[j]=0;
                break;
            }
        }
    }
    printf("\n");
    for(int i=0;i<100;i++){
        if(l[i]==0){
            printf("X\t");
            v++;
        }
        else if(i%10==0){
            printf("\n\n");
            printf("%d\t",l[i]);
        }
        else{
            printf("%d\t",l[i]);
        }
    }
    printf("\n\n");
    printf("\t\t\t||| All eyes this way please |||");
    printf("\n\n");
    printf("Availability: %d\t\t\t\t\t\t ",100-v);
    printf("X - Booked Seats\n\n");
    printf("--------------------------------------------------------------------------\n");
}

int update()
{
    int op;
	printf("\nUPDATE MOVIE LIST\n\n");
	printf("1. Add Movies\n\n");
	printf("2. Remove Movies\n\n");
	printf("3. Back\n\n");
	printf("\nEnter a option: ");
	scanf("%d",&op);
	return op;
}
void add(){
    char s[100];
    printf("\nEnter the movie name: ");
    scanf("%s",s);
	FILE *file = fopen("movies.txt","a");
	if (file == NULL) {
            printf("Error: Unable to open the movie list file.\n");
            return;
	}
	fprintf(file,"\n%s",s);
	fclose(file);
	printf("\nMovie Added Successfully !!!\n\n");
}

void removemov(){
    int num;
    printf("\nMOVIES LIST\n\n");
	for(int i=0;i<MAX;i++){
	    if(movies[i][0]!=0){
		    printf("%d. %s\n\n",i+1,movies[i]);
	    }
	}
	printf("\nEnter Movie to be removed: ");
	scanf("%d",&num);
	for(int i=num-1;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			movies[i][j]=movies[i+1][j];
		}
	}
	FILE *file = fopen("movies.txt","w");
	for(int i=0;i<MAX;i++){
        if(movies[i][0]!=0){
            fprintf(file,"%s",movies[i]);
            if(movies[i+1][0]!=0){
                fprintf(file,"\n");
            }
        }
    }
	for(int i=0;i<MAX;i++){
        if(book[i][0]==num){
            for(int j=1;j<MAX;j++){
                book[i][j]=0;
            }
            break;
        }
	}
	printf("\nMovie Removed Successfully !!!\n\n");
}

char* dateTime() {
    time_t current_time;
    current_time = time(NULL);
    char* c_time_string = ctime(&current_time);
    return c_time_string;
}
void bill(int z,int tno,char *name,char *number,char *datetime,int date,int *s){
    char tstring[9];
    float price;
    struct tm *tm;
    time_t t = time(NULL);
    float totalPrice=0;
    switch(date){
        case 1:
            tm = localtime(&t);
            strftime(date_string, sizeof(date_string), "%d-%m", tm);
            break;
        case 2:
            t += 24 * 3600;
            tm = localtime(&t);
            strftime(date_string, sizeof(date_string), "%d-%m", tm);
            break;
        case 3:
            t += (24 * 3600)*2;
            tm = localtime(&t);
            strftime(date_string, sizeof(date_string), "%d-%m", tm);
            break;
        case 4:
            t += (24 * 3600)*3;
            tm = localtime(&t);
            strftime(date_string, sizeof(date_string), "%d-%m", tm);
            break;
    }
    switch(tno){
        case 1:
            strcpy(tstring,"09:00 am");
            break;
        case 2:
            strcpy(tstring,"12:00 pm");
            break;
        case 3:
            strcpy(tstring,"06:00 pm");
            break;
    }
    int i=0;
    while(s[i]!=0){
    int seat=s[i];
    if(seat>=1&&seat<=20){
        price=220.97;
    }
    else if(seat>=21&&seat<=50){
        price=190.67;
    }
    else if(seat>=51&&seat<=80){
        price=149.26;
    }
    else if(seat>=81&&seat<=100){
        price=60.54;
    }
    printf("------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\tMOVIE TICKET\t\t\t\t\n\n");
    printf("------------------------------------------------------------------------------------\n\n");
    printf("Booking ID: %d\t\t\t\t\t\tMovie : %s\n\n",bookid,movies[z-1]);
    printf("Customer Name : %s\t\t\t\t\t\tShow Date : %s\n\n",name,date_string);
    printf("Mobile no.: %10s\t\t\t\t\t\tSeat: %d\n\n",number,seat);
    printf("Price: Rs. %.2f\t\t\t\t\t\tShow Time: %s\n\n",price,tstring);
    printf("Booking Date:%s\n\n",datetime);
    printf("\t\t\tCancellation not available at this venue\n\n");
    printf("------------------------------------------------------------------------------------\n");
    totalPrice+=price;
    i++;
    }
    printf("\n\t\t\t\t\t\t\tTotal Amount : Rs. %.2f\n\n",totalPrice);
    printf("------------------------------------------------------------------------------------\n");

}
void record(int bookid,int z,int time,char *name,char *number,char *datetime,int *s){
    FILE *fp;
    fp = fopen("record.csv", "a");
    if (fp == NULL) {
        printf("Could not open file record.csv for writing.\n");
    }
    int i=0;
    while(s[i]!=0){
    int seat=s[i];
    fprintf(fp,"%d,%s,%s,%s,%s,%d,%d,%s",bookid,name,number,movies[z-1],date_string,time,seat,datetime);
    i++;
    }
    fclose(fp);
}
int admin(){
    char pwd[10],word[] = "123asd";
    printf("\nEnter the Password: ");


    scanf("%s",pwd);
    if(strcmp(pwd,word)==0){
        return 1;
    }
    else{
        printf("\nIncorrect Password !!!\n\n");
        return 0;
    }
}
void book_form(){
    int n=1,m=1,p=1;
    for(int i=0;i<movieCount*12;i++){
        book[i][0]=n;
        if((i+1)%12==0){
            n++;
        }
        book[i][1]=m;
        if((i+1)%3==0){
            m++;
            if(m>4){
                m=1;
            }
        }
        book[i][2]=p;
        p++;
        if(p>3){
            p=1;
        }
    }
}

int main(){
    int n=1;
    seat();
    while(n!=0){
        int in,z,time,seat,p,per,date,ticket,s[11]={0};
        movielist();
        book_form();
        char number[10];
        char name[30];
	    printf("\nMOVIE BOOKING SYSTEM\n\n");
	    printf("1.Book Ticket\n\n");
	    printf("2.Update Booking Details (ADMINS ONLY)\n\n");
        printf("3.Movie List\n\n");
	    printf("4.Exit\n\n");
	    printf("\nEnter the option (1-4): ");
	    scanf("%d",&in);
	    switch(in){
		    case 1:
                ticket=0;
			    z=bookticket();
			    date=movieDate();
			    time=timing();
			    layout(z,date,time);
                printf("\nEnter your Name: ");
                scanf("%s",name);
            l3:
                printf("\nEnter your Mobile No.: ");
                scanf("%s",number);
                if(strlen(number)!=10){
                    printf("\nEnter a Valid Mobile Number\n");
                    goto l3;
                }
            l4:
                printf("\nEnter the number of ticket to be booked (Max 10) : ");
			    scanf("%d",&ticket);
                if(ticket<1||ticket>10){
                    printf("Exceeding the limit\n");
                    goto l4;
                }
                for(int r=0;r<ticket;r++){
              l:
                p=0;
                printf("\nSelect the seat no.: ");
                scanf("%d",&seat);
                if(seat<1||seat>MAX){
                    printf("Invalid Seat\n\n");
                    goto l;
                }
                for(int i=0;i<MAX;i++){
                    if(book[i][0]!=0){
                        if(book[i][0]==z&&book[i][1]==date&&book[i][2]==time){
                            for(int j=3;j<MAX;j++){
                                if(book[i][j]==seat){
                                    p=1;
                                }
                            }
                        }
                    }
                }
                if(p==1){
                    printf("\nSeat had been booked already !!!\n\n");
                    goto l;
                }
                for(int i=0;i<MAX;i++){
                    if(book[i][0]==z&&book[i][1]==date&&book[i][2]==time){
                        for(int j=0;j<MAX;j++){
                            if(book[i][j]==0){
                                book[i][j]=seat;
                                break;
                            }
                        }
                    }
                }
                s[r]=seat;
                }
                char* datetime=dateTime();
                bill(z,time,name,number,datetime,date,s);
                record(bookid,z,time,name,number,datetime,s);
                printf("\nTicket Booked Successfully !!!\n\n");
                bookid++;
                break;
		    case 2:
		        per=admin();
		        if(per==0){
                    break;
		        }
		        z=update();
		        switch(z){
		            case 1:
			            add();
    		            break;
		            case 2:
		                removemov();
		                break;
                    case 3:
                        main();
                        break;
                    default:
                        printf("\nError, Invalid Input\n\n");
                        main();
	            }
			    break;
            case 3:
                printf("\nMOVIES LIST\n\n");
                for(int i=0;i<100;i++){
                    if(movies[i][0]!=0){
                        printf("%d. %s\n\n",i+1,movies[i]);
                    }
                }
                break;
            case 4:
			    n=0;
			    break;
		    default:
			    printf("\nInvalid input\n\n");
			    n=1;
	    }
    }
    return 0;
}
