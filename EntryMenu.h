#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int total_books;
int total_members;
int issued_books;
typedef struct Book
{
    int book_number;
    char name[30];
    char author_name[30];
    int price;
    char status; // whether present or not, y for Yes, n for No ;
    char write_off; // whether book thrown away - Y if thrown, N if present
    int owned; 
} book ;

typedef struct Member
{
    int member_number;
    char member_name[30];
    char address[30];
    char email[20];
    char mobiles[33];
    char status; // whether member still present or not ;
    int no_of_issued_books ;
} member ;


typedef struct Issue
{
    int book_no;
    int member_no;
    char issue_date[11]; // The date on which book is issued in dd/mm/yyyy format
    char due_date[11];
} issue1;


typedef struct History
{
    int book_no;
    int member_no;
    char issue_date[11]; // The date on which book is issued in dd/mm/yyyy format
    char due_date[11];
    char return_date[11];
    int fine ;

} complete_history;

void showAllHistory();
void ENTER()
{
    printf("\n\t\t PRESS ENTER TO CONTINUE ");
    fflush(stdin); getch();
    return ;
}

void addBook()
{
    FILE *book_f;
    
    book b;
    char ch;
    do
    {
        printf("\n\t\t BOOK NUMBER : ");
        fflush(stdin); scanf("%d", &(b.book_number));
        
        printf("\n\t\t Book NAME : ");
        fflush(stdin); scanf("%[^\n]s", &(b.name));

        printf("\n\t\t Author Name : ");
        fflush(stdin); scanf("%[^\n]s", &(b.author_name));

        printf("\n\t\t Price : ");
        scanf("%d", &(b.price));

        b.status = 'Y' ;
        b.write_off = 'N';
        printf("\n\n");

        printf("\n\t\t BOOK NUMBER : ");
        printf("%d", b.book_number);
        
        printf("\n\t\t BOOK NAME : ");
        printf("%s", b.name);

        printf("\n\t\t Author Name : ");
        printf("%s", b.author_name);

        printf("\n\t\t Price : ");
        printf("%d", b.price);

        printf("\n\t\t Status : ");
        printf("%c", b.status);

        printf("\n\t\t Write Off : ");
        printf("%c", b.write_off);

        printf("\n\t Do you want to save and continue ? ");
        fflush(stdin); scanf("%c", &ch);
    } while (ch!='y'  && ch != 'Y');

    if(ch=='y'||ch=='Y')
    {
        book_f = fopen("books.dat", "ab");
        fwrite(&b ,sizeof(b),1, book_f);
        fclose(book_f);
        printf("\n Data saved.");
        total_books++ ;
    }
    
}
void addMember()
{
    FILE *member_f;
    member_f = fopen("members.dat", "ab");
    member m;
    char ch;
    do
    {
        printf("\n\t\t MEMBER NUMBER : ");
        fflush(stdin); scanf("%d", &(m.member_number));
        
        printf("\n\t\t MEMBER NAME : ");
        fflush(stdin); scanf("%[^\n]s", &(m.member_name));

        printf("\n\t\t Address : ");
        fflush(stdin); scanf("%[^\n]s", &(m.address));

        printf("\n\t\t Email : ");
        fflush(stdin); scanf("%[^\n]s", &(m.email));

        printf("\n\t\t Mobile Number(s) : ");
        fflush(stdin); scanf("%[^\n]s", &(m.mobiles));

        m.status = 'Y' ;
        m.no_of_issued_books = 0;

        printf("\n\t\t MEMBER NUMBER : ");
        printf("%d", m.member_number);
        
        printf("\n\t\t MEMBER NAME : ");
        printf("%s", m.member_name);

        printf("\n\t\t Address : ");
        printf("%s", m.address);

        printf("\n\t\t Email : ");
        printf("%s", m.email);

        printf("\n\t\t Mobile Number(s) : ");
        printf("%s", m.mobiles);

        printf("\n\t\t STATUS : ");
        printf("%c", m.status);

        printf("\n\t\t Number of issued books : %d", m.no_of_issued_books) ;


        printf("\n\t Do you want to save and continue ? ");
        fflush(stdin); scanf("%c", &ch);
    } while (ch != 'y' && ch!= 'Y'); 

    if(ch=='y'||ch=='Y')
    {
        member_f = fopen("members.dat","ab");
        fwrite(&m,sizeof(m),1,member_f);
        fclose(member_f);
        printf("\n Data saved.");
        total_members++;
    }
}

int ShowTotalbooks()
{
    FILE *f;
    f = fopen("books.dat", "rb");
    fseek(f, 0, SEEK_END) ;
    int n = ftell(f)/sizeof(book);
    return n ;
}

int ShowTotalMembers()
{
    FILE *f;
    f = fopen("members.dat", "rb");
    fseek(f, 0, SEEK_END) ;
    int n = ftell(f)/sizeof(member);
    return n ;
}

void Entry_menu_main()
{
    FILE *books;
    FILE *members;

    int op = 0;
    do
    {
        system("cls");
        //Library Main Menu 
        printf("\n\t\t\t Welcome to Entry Menu ");
        printf("\n\t\t1. NEW BOOK ");
        printf("\n\t\t2. New Member ");
        printf("\n\t\t3. Go Back ");
        printf("\n\t\t4. EXIT ");

        printf("\n\t\t Select What you would like to do now ? : ");
        scanf("%d", &op) ;

        switch(op)
        {
            case 1:
                addBook();
                break;
            case 2:
                addMember();
                break;
            case 3:
                break;
            case 4:
                exit(0);
                break;
        }
    } while (op != 3);
    return ;
}