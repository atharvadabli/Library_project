#include "reports.h"

void showIssues(issue1 const *p)
{
    printf("\n BOOK NUMBER    : %d", p->book_no);
    printf("\n MEMBER NUMBER  : %d", p->member_no);
    printf("\n ISSUE DATE     : %s", p->issue_date);
    printf("\n DUE DATE       : %s", p->due_date);
    return;
}

void showHistory(complete_history const *p)
{
    printf("\n BOOK NUMBER    : %d", p->book_no);
    printf("\n MEMBER NUMBER  : %d", p->member_no);
    printf("\n ISSUE DATE     : %s", p->issue_date);
    printf("\n DUE DATE       : %s", p->due_date);
    printf("\n Return Data    : %s", p->return_date);
    printf("\n FINE           : %d", p->fine);
    return;
}

void showAllHistory()
{
    FILE *f;
    complete_history b;

    f = fopen("history.dat", "rb");
    if(f == NULL)
    {
        printf("\n File not found ");
    } 
    else
    {
        while(fread(&b, sizeof(b), 1, f))
        {
            showHistory(&b) ;
            printf("\n ") ;
        }
        fclose(f);
    }
    printf("Press enter to continue ..... ");
    fflush(stdin); getch() ;

}

void Issue()
{
    char a, ch1;
    printf("\n\t\t Do you want to see all books ?(y/n) ");
    fflush(stdin);
    scanf("%c", &a);
    if (a == 'y' | a == 'Y')
    {
        showAllbooks();
    }

    printf("\n\t\t Enter Book Number to be Issued : ");
    int b_no;
    scanf("%d", &b_no);

    FILE *fbooks;
    book b;
    int n;
    fbooks = fopen("books.dat", "r+b");
    if (fbooks == NULL)
    {
        printf("\n File not found ");
    }
    else
    {
        fseek(fbooks, 0, SEEK_END);
        n = ftell(fbooks) / sizeof(b);

        if (b_no < 0 || b_no > n)
        {
            printf("Invalid Input ... ");
        }
        else
        {
            fseek(fbooks, sizeof(b) * (b_no - 1), SEEK_SET);
            fread(&b, sizeof(b), 1, fbooks);
            showBooks(&b);
        }
    }

    if (b.status == 'Y' || b.status == 'y')
    {
        printf("\n\t\t Enter Member number to issue to : ");
        int m_no;
        char issue;
        scanf("%d", &m_no);
        int n;
        FILE *f;
        member m;

        f = fopen("members.dat", "r+b");
        if (f == NULL)
        {
            printf("\n File not found ");
        }
        else
        {
            fseek(f, 0, SEEK_END);    // The file pointer comes at the end of the list
            n = ftell(f) / sizeof(m); //ftell gives nth byte where file pointer is standing, so currently on EOF mark

            if (m_no < 0 || m_no > n)
            {
                printf("Invalid input ... ");
            }
            else
            {
                fseek(f, sizeof(m) * (m_no - 1), SEEK_SET);
                fread(&m, sizeof(m), 1, f);
                showMembers(&m);
                printf("\n\t\t Do you want to issue the book ? (y/n) ");
                fflush(stdin);
                scanf("%c", &issue);
                if (issue == 'y' || issue == 'Y')
                {
                    b.status = 'N';
                    m.no_of_issued_books++;
                    fseek(fbooks, sizeof(b) * (b_no - 1), SEEK_SET);
                    fwrite(&b, sizeof(b), 1, fbooks);

                    fseek(f, sizeof(m) * (m_no - 1), SEEK_SET);
                    fwrite(&m, sizeof(m), 1, f);

                    fclose(f);
                    fclose(fbooks);

                    FILE *h;
                    issue1 i;

                    i.book_no = b_no;
                    i.member_no = m_no;
                    do
                    {
                        printf("\n\t\t Give the date of issue in dd/mm/yyyy format : ");
                        fflush(stdin);
                        scanf("%s", &i.issue_date);

                        printf("\n\t\t Give the due date : ");
                        fflush(stdin);
                        scanf("%s", &i.due_date);

                        ENTER();

                        showIssues(&i);

                        printf("\n\t Do you want to save ? (y/n) ");
                        fflush(stdin);
                        scanf("%c", &ch1);

                    } while (!(ch1 == 'y' || ch1 == 'Y'));

                    if (ch1 == 'y' || ch1 == 'Y')
                    {
                        h = fopen("issue.dat", "ab");
                        fwrite(&i, sizeof(i), 1, h);
                        fclose(h);
                        printf("\n\tData Saved ");
                        issued_books++;
                        showMembers(&m) ;
                        showBooks(&b);
                    }
                }
            }
        }
    }
    else
    {
        printf("\n\t\t The book has already been issued ");
    }
}

void Return()
{
    int b_no;
    printf("\n\t\t Enter book number to be returned : ") ;
    scanf("%d", &b_no);

    FILE *fbooks;
    book b;
    int n;
    fbooks = fopen("books.dat", "r+b");
    if (fbooks == NULL)
    {
        printf("\n File not found ");
    }
    else
    {
        fseek(fbooks, 0, SEEK_END);
        n = ftell(fbooks) / sizeof(b);

        if (b_no < 0 || b_no > n)
        {
            printf("Invalid Input ... ");
        }
        else
        {
            fseek(fbooks, sizeof(b) * (b_no - 1), SEEK_SET);
            fread(&b, sizeof(b), 1, fbooks);
            showBooks(&b);
        }
    }

    if (b.status == 'N' || b.status == 'n')
    {
        FILE *h, *iss ;
        complete_history h1 ;
        issue1 i1 ;

        iss = fopen("issue.dat", "rb");
        fseek(iss, 0, SEEK_SET );
        while(fread(&i1, sizeof(i1), 1, iss))
        {
            if(i1.book_no == b_no)
            {
                printf("\n\t\t Member Number   : %d", i1.member_no);
                printf("\n\t\t Issue Date   : %s", i1.issue_date);
                printf("\n\t\t Due Date   : %s", i1.due_date); 
                break ; 
            }
        }
        
        int m_no = i1.member_no;
        char issue, ch1;
        int n;
        FILE *f;
        member m;

        f = fopen("members.dat", "r+b");
        if (f == NULL)
        {
            printf("\n File not found ");
        }
        else
        {
            fseek(f, 0, SEEK_END);    // The file pointer comes at the end of the list
            n = ftell(f) / sizeof(m); //ftell gives nth byte where file pointer is standing, so currently on EOF mark

            if (m_no < 0 || m_no > n)
            {
                printf("Invalid input ... ");
            }
            else
            {
                fseek(f, sizeof(m) * (m_no - 1), SEEK_SET);
                fread(&m, sizeof(m), 1, f);
                showMembers(&m);
                printf("\n\t\t Do you want to return the book ? (y/n) ");

                fflush(stdin);
                scanf("%c", &issue);
                if (issue == 'y' || issue == 'Y')
                {
                    b.status = 'Y';
                    (m.no_of_issued_books)--;

                    fseek(fbooks, sizeof(b) * (b_no - 1), SEEK_SET);
                    fwrite(&b, sizeof(b), 1, fbooks);

                    fseek(f, sizeof(m) * (m_no - 1), SEEK_SET);
                    fwrite(&m, sizeof(m), 1, f);

                    fclose(f);
                    fclose(fbooks);

                    FILE *h;
                    issue1 i;

                    h1.book_no = i1.book_no ;
                    h1.member_no = i1.member_no ;
                    strcpy(h1.due_date, i1.due_date) ;
                    strcpy(h1.issue_date, i1.issue_date );

                    do
                    {
                        printf("\n\t\t Enter Return Date : ");
                        fflush(stdin);
                        scanf("%s", &(h1.return_date));

                        printf("\n\t\t FINE IMPOSED : ");
                        scanf("%d", &(h1.fine));

                        showHistory(&h1);

                        printf("\n\t\t Do you want to save ? ");
                        fflush(stdin);
                        scanf("%c", &(ch1));

                    } while (!(ch1 == 'y' || ch1 == 'Y'));


                    if (ch1 == 'y' || ch1 == 'Y')
                    {
                        h = fopen("history.dat", "ab");
                        fwrite(&h1, sizeof(h1), 1, h);
                        fclose(h);
                        printf("\n\tData Saved ");
                        issued_books--;
                        showMembers(&m) ;
                        showBooks(&b) ;
                    }
                }
            }
        }
    }
    else
    {
        printf("\n\t\t The book has not been issued yet ");
    }
}

void transaction_main()
{
    int op = 0;
    do
    {
        system("cls");
        printf("\n\t\t\t TRANSACTION MENU \n");
        printf("\n\t\t 1. ISSUE BOOK ");
        printf("\n\t\t 2. Return Book ");
        printf("\n\t\t 3. Exit ");
        printf("\n\t\t 4. Go back");

        printf("\n\t Choose one : ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            Issue();
            getch();
            break;
        case 2:
            Return();
            getch();
            break;
        case 3:
            exit(0);
            break;
        case 4:

            break;
        }

    } while (op != 4);
    return;
}