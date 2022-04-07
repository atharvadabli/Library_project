#include"EntryMenu.h"

void showBooks(book const *p)
{
     printf("\n BOOK NUMBER    : %d",p->book_number );
     printf("\n BOOK NAME      : %s",p->name );
     printf("\n AUTHOR NAME    : %s",p->author_name   );
     printf("\n PRICE          : %d",p->price  );
     printf("\n STATUS         : %c",p->status);
     printf("\n WRITE OFF      : %c",p->write_off);
     return ;
}



void showMembers(member const *p)
{
     printf("\n MEMBER NUMBER               : %d",p->member_number );
     printf("\n MEMBER NAME                 : %s",p->member_name );
     printf("\n ADDRESS                     : %s",p->address  );
     printf("\n EMAIL                       : %s",p->email  );
     printf("\n MOBILE                      : %s",p->mobiles);
     printf("\n STATUS                      : %c",p->status);
     printf("\n NUMBER OF ISSUED BOOKS      : %d",p->no_of_issued_books);
     return ;
}



void showAllbooks()
{
    FILE *fbooks;
    book b;

    fbooks = fopen("books.dat", "rb");
    if(fbooks == NULL)
    {
        printf("\n File not found ");
    } 
    else
    {
        while(fread(&b, sizeof(b), 1, fbooks))
        {
            showBooks(&b) ;
            printf("\n ") ;
        }
        fclose(fbooks);
    }
    printf("Press enter to continue ..... ");
    fflush(stdin); getch() ;
}

void showallMembers()
{
    FILE *f ;
    member m;
    f = fopen("members.dat", "rb");
    if(f==NULL)
    {
        printf("\n File not found ");
    }
    else
    {
        while(fread(&m, sizeof(m), 1, f))
        {
            showMembers(&m);
            printf("\n\n");
        }
        fclose(f);
    }
    printf("Press ENter to cotinue ...");
    fflush(stdin); getch();
}

void showSpecific_Book()
{
    int b_no;
    FILE *fbooks;
    book b ;
    int n;
    fbooks = fopen("books.dat", "rb");
    printf("\n\t\t Enter Book number you want to see ... : ");
    scanf("%d", &b_no) ;
    if(fbooks == NULL)
    {
        printf("\n File not found ");
    } 
    else
    {
        fseek(fbooks, 0 , SEEK_END);
        n = ftell(fbooks) / sizeof(b) ;
        
        if(b_no<0 || b_no > n)
        {
            printf("Invalid Input ... ");
               
        }
        else
        {
            fseek(fbooks, sizeof(b)*(b_no-1) , SEEK_SET);
            fread(&b, sizeof(b), 1, fbooks);
            showBooks(&b);
        }
        fclose(fbooks);
    }
}

void showsSpecific_member()
{
    int m_no, n ;
    FILE *f ;
    member m ;
    
    f = fopen("members.dat", "rb") ;
    printf("\n\t\t Enter Member number you want to see : ");
    scanf("%d", &m_no);
    if(f==NULL)
    {
        printf("\n File not found ");
    }
    else
    {
        fseek(f,0,SEEK_END); // The file pointer comes at the end of the list
        n = ftell(f)/sizeof(m);  //ftell gives nth byte where file pointer is standing, so currently on EOF mark 

        if(m_no<0 || m_no > n)
        {
            printf("Invalid input ... ") ;
        }
        else
        {
            fseek(f, sizeof(m)*(m_no - 1), SEEK_SET );
            fread(&m, sizeof(m), 1, f);
            showMembers(&m);
        }
        fclose(f);
    }
}


void showIssued()
{
    FILE *fbooks;
    book b ;
    int n;
    fbooks = fopen("books.dat", "rb");

    if(fbooks == NULL)
    {
        printf("\n File not found ");
    } 
    else
    {
        while(fread(&b, sizeof(b), 1, fbooks))
        {
            if(b.status=='N' || b.status=='n')
            {
                showBooks(&b) ;
                printf("\n ") ;
            } 
        }
        fclose(fbooks);
    }
    return ;
}



void Reports()
{
    int op = 0;
    do
    {
        system("cls");
        printf("\n\t\t\t WELCOME TO REPORTS MENU");
        printf("\n\t\t Total Number of books in the library : %d ", ShowTotalbooks());
        printf("\n\t\t 1. SHOW ALL BOOKs");
        printf("\n\t\t 2. SHOW Specific Book ");
        printf("\n\t\t 3. SHOW ALL Issued Books");
        printf("\n\t\t 4. SHOW History of all books ");
        printf("\n\t\t 5. SHOW All Members ");
        printf("\n\t\t 6. SHOW Specific Members ");
        
        printf("\n\t\t 7. Exit ");
        printf("\n\t\t 8. Go Back ");

        printf("\n\t Choose among the above : ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                showAllbooks();
                getch();
                break ;
            case 2:
                showSpecific_Book();
                getch();
                break ;
            case 3:
                showIssued();
                printf("If No data is Shown, That means no book is issued ");
                getch();
                break ;
            case 4:
                showAllHistory();
                getch();
                break ;

            case 5:
                showallMembers();
                getch();
                break ;

            case 6:
                showsSpecific_member();
                getch();
                break ;
            
            case 7:
                exit(0);
                break ;
            case 8:
                break ;
        }
    } while (op!=8);
    

    return ;
}