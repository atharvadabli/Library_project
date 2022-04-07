#include"transaction.h"

void editBook()
{
    int b_no;
    FILE *fbooks;
    book b ;
    int n;
    fbooks = fopen("books.dat", "r+b");
    printf("\n\t\t Enter Book number you want to edit ... : ");
    scanf("%d", &b_no) ;

    if(fbooks == NULL)
    {
        printf("\n File not found ");
    } 
    else
    {
        char c;
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
            printf("Do you want to edit this ?(y/n)");
            fflush(stdin);
            scanf("%c", &c);
            if(c=='y' || c== 'Y')
            {   
                
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

                    printf("\n\t\t STATUS present  : ");
                    fflush(stdin);
                    scanf("%c", &(b.status));

                    printf("\n\t\t WRITE OFF status  : ");
                    fflush(stdin);
                    scanf("%c", &(b.write_off));
//**********************************************************************************************************

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
                    fseek(fbooks, sizeof(b)*(b_no-1) , SEEK_SET);
                    fwrite(&b ,sizeof(b),1, fbooks);
                    fclose(fbooks);
                    printf("\n Data saved.");
                }
            }
        }
    }
}



void editMember()
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
            char c;
            fseek(f, sizeof(m)*(m_no - 1), SEEK_SET );
            fread(&m, sizeof(m), 1, f);
            showMembers(&m);
            printf("Do you want to edit this ?(y/n)");
            fflush(stdin);
            scanf("%c", &c);
            if(c=='y' || c== 'Y')
            {   
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

                    printf("\n\t\t STATUS present  : ");
                    fflush(stdin);
                    scanf("%c", &(m.status));

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
                    f = fopen("members.dat","ab");
                    fseek(f, sizeof(m)*(m_no - 1), SEEK_SET );
                    fwrite(&m,sizeof(m),1,f);
                    fclose(f);
                    printf("\n Data saved.");
                }
                return ;
            }
        }
    }
}

void Edit_menu_main()
{
    FILE *books;
    FILE *members;

    int op = 0;
    do
    {
        system("cls");
        //Library Main Menu 
        printf("\n\t\t\t Welcome to EDIT Menu ");
        printf("\n\t\t1. EDIT BOOK ");
        printf("\n\t\t2. EDIT Member ");
        printf("\n\t\t3. Go Back ");
        printf("\n\t\t4. EXIT ");

        printf("\n\t\t Select What you would like to do now ? : ");
        scanf("%d", &op) ;

        switch(op)
        {
            case 1:
                editBook();
                break;
            case 2:
                editMember();
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