#include"Editmenu.h"

int main()
{
    int op = 0;
    
    
    do
    {
        system("cls");
        //Library Main Menu 
        printf("\n\t\t\t Welcome to Library System ");
        printf("\n\t\t1. NEW ENTRIES ");
        printf("\n\t\t2. EDIT ");
        printf("\n\t\t3. TRANSACTIONS ");
        printf("\n\t\t4. REPORTS");
        printf("\n\t\t5. EXIT ");

        printf("\n\t\t Select What you would like to do now ? : ");
        scanf("%d", &op) ;

        switch(op)
        {
            case 1:
                Entry_menu_main();
                break;
            case 2:
                Edit_menu_main();
                break;
            case 3:
                transaction_main();
                break;
            case 4:
                Reports();
                break;
            case 5:
                exit(0);
                break;
            case 6:
                break;
        }
        
    } while (op != 5);
    return 0;
}