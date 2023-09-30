/*
CSE 115 Section: 6
Group no: 6

Project title: Restaurant Management System

Group Members:
1. Wasif Haider                     2232829642
2. Quazi Md. Sadman                 2233303642
3. Mir Mohammad Asif Abdullah       2233244642
*/


//included header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//global variables
int nOrders,totalMenuItems,n9am,n3pm,n9pm,disc,len;
char vouch[15];


//user-defined data types
typedef struct
{
    char item[50];
    int serial, price, qty;
} orderedItems;

typedef struct
{
    char name[50];
    int contact,nItems;
    orderedItems ordered[100];
} customer;
customer cust[100];

typedef struct
{
    char item[50];
    int price, serial;
} MENU;
MENU menu[100];

typedef struct
{
    char name[50];
    int contact;
} rsvp;
rsvp nineAM[5], threePM[5], ninePM[5];


//function prototypes
void customers();
void order();
void printBill(int n, customer cust[n]);
void printBillVouch(int n, customer cust[n]);
void reservation();
void getPass();
void correctPass();
void viewOrders();
void viewReservations();
void viewMenu();
void completeOrder();
void inputMenu();
void delMenu();
void updatePrice();
void cancelReservation();
void searchOrder();
void searchReservations();
void changeVoucher();
void changePass();
//file updating functions
void orderWrite(int n, customer cust[n]);
void menuWrite(int n, MENU menu[n]);
void nineAMwrite(int n, rsvp nineAM[n]);
void threePMwrite(int n, rsvp threePM[n]);
void ninePMwrite(int n, rsvp ninePM[n]);
//animation functions
void loading();
void delay(int milliseconds);


//function codes
int main()
{
    int i,j;

    //reading the orders into array
    FILE *f1 = fopen("order.txt","r");
    if (!feof(f1) && fgetc(f1)!=EOF)
    {
        rewind(f1);
        fscanf(f1, "%d\n", &nOrders);
        while(!feof(f1))
        {
            for (i=0;i<nOrders;i++)
            {
                fflush(stdin);
                fgets(cust[i].name,50,f1);
                len = strlen(cust[i].name);
                cust[i].name[len-1] = '\0';
                fscanf(f1,"%d\n",&cust[i].contact);
                fscanf(f1,"%d\n",&cust[i].nItems);
                for (j=0;j<cust[i].nItems;j++)
                {
                    fscanf(f1,"%d %d\n", &cust[i].ordered[j].serial, &cust[i].ordered[j].qty);
                }
            }
        }
    }
    else if (f1==NULL)
    {
        printf("Error in opening order.txt");
        return 0;
    }
    fclose(f1);

    //reading the menu items into array
    FILE *f2 = fopen("menu.txt","r");
    if (!feof(f2) && fgetc(f2)!=EOF)
    {
        rewind(f2);
        fscanf(f2,"%d\n",&totalMenuItems);
        while(!feof(f2))
        {
            for (i=0;i<totalMenuItems;i++)
            {
                fflush(stdin);
                fgets(menu[i].item,50,f2);
                len = strlen(menu[i].item);
                menu[i].item[len-1] = '\0';
                fscanf(f2,"%d\n",&menu[i].price);
            }
        }
    }
    else if (f2==NULL)
    {
        printf("Error in opening menu.txt");
        return 0;
    }
    fclose(f2);

    //reading the reservations into array
    FILE *f3 = fopen("9am.txt","r");
    if(!feof(f3) && fgetc(f3)!=EOF)
    {
        rewind(f3);
        fscanf(f3,"%d\n",&n9am);
        while(!feof(f3))
        {
            for (i=0;i<n9am;i++)
            {
                fflush(stdin);
                fgets(nineAM[i].name,50,f3);
                len = strlen(nineAM[i].name);
                nineAM[i].name[len-1] = '\0';
                fscanf(f3,"%d\n",&nineAM[i].contact);
            }
        }
    }
    else if (f3==NULL)
    {
        printf("Error in opening 9am.txt");
        return 0;
    }
    fclose(f3);
    FILE *f4 = fopen("3pm.txt","r");
    if(!feof(f4) && fgetc(f4)!=EOF)
    {
        rewind(f4);
        fscanf(f4,"%d\n",&n3pm);
        while(!feof(f4))
        {
            for (i=0;i<n3pm;i++)
            {
                fflush(stdin);
                fgets(threePM[i].name,50,f4);
                len = strlen(threePM[i].name);
                threePM[i].name[len-1] = '\0';
                fscanf(f4,"%d\n",&threePM[i].contact);
            }
        }
    }
    else if (f4==NULL)
    {
        printf("Error in opening 3pm.txt");
        return 0;
    }
    fclose(f4);
    FILE *f5 = fopen("9pm.txt","r");
    if(!feof(f5) && fgetc(f5)!=EOF)
    {
        rewind(f5);
        fscanf(f5,"%d\n",&n9pm);
        while(!feof(f5))
        {
            for (i=0;i<n9pm;i++)
            {
                fflush(stdin);
                fgets(ninePM[i].name,50,f5);
                len = strlen(ninePM[i].name);
                ninePM[i].name[len-1] = '\0';
                fscanf(f5,"%d\n",&ninePM[i].contact);
            }
        }
    }
    else if (f5==NULL)
    {
        printf("Error in opening 9pm.txt");
        return 0;
    }
    fclose(f5);

    char opt;
    printf("\n\t====================================================\n");
    printf("\t~~~~~~~~~~~~~ Welcome to KASHUNDI 2.0 ~~~~~~~~~~~~~~");
    printf("\n\t====================================================\n");
    printf("\n\tYou are a/an _______?\n");
    printf("\t1. Admin\n");
    printf("\t2. Customer\n");
    printf("\n\t(Press only enter to exit the program)\n");
    printf("\n\tChoose: ");
    scanf("%c", &opt);
    fflush(stdin);
    switch (opt)
    {
    case 49:
        system("cls");
        getPass();
        break;
    case 50:
        system("cls");
        customers();
        break;
    case 10:
        exit(0);
        break;
    default:
        printf("\n\tInvalid input!\n");
        main();
    }
    return 0;
}


//customer interface
void customers()
{
    int opt;
    printf("\n\t~~~~~~~~ CUSTOMER PAGE ~~~~~~~~\n");
    printf("\n\tWhat do you want to do today?\n");
    printf("\n\t1. Make an order\n");
    printf("\t2. Make a reservation\n");
    printf("\n\tChoose: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch (opt)
    {
    case 1:
        printf("\n\tLoading the order page");
        loading();
        system("cls");
        order();
        break;
    case 2:
        printf("\n\tLoading the reservation page");
        loading();
        system("cls");
        reservation();
        break;
    default:
        printf("\tInvalid input!");
        customers();
    }
}

void order()
{
    int i,disc;
    char opt,voucher[15],enteredVoucher[15];
    printf("\n\t~~~~~~~~ ORDER PAGE ~~~~~~~~\n");
    printf("\n\tWelcome Mr./Mrs...\n\n\tName: ");
    gets(cust[nOrders].name);
    fflush(stdin);
    printf("\tContact no.: +880");
    scanf("%d",&cust[nOrders].contact);
    fflush(stdin);
    printf("\n\tLoading the menu");
    loading();
    system("cls");

    //showing the menu
    printf("\n\t\t\t~~~~~~~~ THE MENU ~~~~~~~~\n\n");
    printf("\tSl.\t\t\tItem\t\t\tPrice (in Taka)\n");
    for (i=0;i<totalMenuItems;i++)
    {
        printf("\t%d.\t%30s\t\t\t%d/-\n", i+1, menu[i].item, menu[i].price);
    }

    //taking input the number of items to be ordered
    printf("\n\tNumber of items you want to order: ");
    scanf("%d", &cust[nOrders].nItems);
    fflush(stdin);

    //actually taking the order
    printf("\n\tEnter the items you want to order (max is %d):\n", cust[nOrders].nItems);
    for (i=0;i<cust[nOrders].nItems;i++)
    {
        printf("\n\tEnter serial of item no. %d: ", i+1);
        scanf("%d", &cust[nOrders].ordered[i].serial);
        fflush(stdin);
        printf("\tEnter quantity: ");
        scanf("%d", &cust[nOrders].ordered[i].qty);
        fflush(stdin);
    }
    FILE *fd = fopen("discount.txt","r");
    if (fd != NULL)
        fscanf(fd,"%d",&disc);
    fclose(fd);
    FILE *fv = fopen("voucher.txt","r");
    if (fv == NULL)
    {
        printf("\n\tPreparing your bill");
        loading();
        system("cls");
        printBill(nOrders,cust);
    }
    else
    {
        printf("\n\tDo you want to apply the voucher for %d%% discount? (y/n): ", disc);
        scanf("%c", &opt);
        fflush(stdin);
        if (opt=='y' || opt=='Y')
        {
            fgets(voucher,"%[^\n]",fv);
            printf("\n\tEnter voucher: ");
            scanf("%[^\n]", enteredVoucher);
            fflush(stdin);
            if (strcmp(voucher,enteredVoucher)==0)
            {
                printf("\n\tVoucher applied!\n");
                printf("\n\tPreparing your bill");
                loading();
                system("cls");
                printBillVouch(nOrders,cust);
            }
            else
            {
                printf("\n\tInvalid Voucher!\n");
                printf("\n\tPreparing your bill");
                loading();
                system("cls");
                printBill(nOrders,cust);
            }
        }
        else
        {
            printf("\n\tPreparing your bill");
            loading();
            system("cls");
            printBill(nOrders,cust);
        }
    }
    fclose(fv);
    nOrders++;
    orderWrite(nOrders, cust);
    int c;
    printf("\n\tWhat do you want to do next?\n");
    printf("\t1. Make another order\n");
    printf("\t2. Make a reservation\n");
    printf("\t3. Navigate to the home page\n");
    printf("\n\tOperation: ");
    scanf("%d", &c);
    fflush(stdin);
    switch (c)
    {
    case 1:
        printf("\n\tLoading the order page");
        loading();
        system("cls");
        order();
        break;
    case 2:
        printf("\n\tLoading the reservation page");
        loading();
        system("cls");
        reservation();
        break;
    case 3:
        printf("\n\tRedirecting");
        loading();
        system("cls");
        main();
        break;
    default:
        return;
    }
}

void printBill(int n, customer cust[n])
{
    int billAmount=0;
    for (int j=0 ; j<cust[n].nItems ; j++)
    {
        billAmount += ((menu[cust[n].ordered[j].serial-1].price)*(cust[n].ordered[j].qty));
    }
    printf("\n\t\t\t\a~~~~~~~~~ KASHUNDI 2.0 ~~~~~~~~~\n\n");
    printf("\tCustomer Name: %s\n", cust[n].name);
    printf("\tCustomer Contact: +880%d\n", cust[n].contact);
    printf("\t-------------------------------------------------------------\n");
    printf("\tOrdered items:\n");
    for (int j=0 ; j<cust[n].nItems ; j++)
    {
        printf("\t%d. %d x %30s\t\t%d x %7d/-\n", j+1, cust[n].ordered[j].qty, menu[cust[n].ordered[j].serial-1].item, cust[n].ordered[j].qty, menu[cust[n].ordered[j].serial-1].price);
    }
    printf("\t-------------------------------------------------------------\n");
    printf("\tTotal:\t\t\t\t\t\t%7d/-\n", billAmount);
    printf("\n\tWe hope to serve you again! Have a pleasant day!\n");
}

void printBillVouch(int n, customer cust[n])
{
    int billAmount=0,disc;
    float discount, withVouch;
    for (int j=0 ; j<cust[n].nItems ; j++)
    {
        billAmount += ((menu[cust[n].ordered[j].serial-1].price)*(cust[n].ordered[j].qty));
    }
    FILE *fd = fopen("discount.txt","r");
    fscanf(fd,"%d",&disc);
    discount = (disc/100.0)*billAmount;
    withVouch = billAmount-discount;
    fclose(fd);
    printf("\n\t\t\t\a~~~~~~~~~ KASHUNDI 2.0 ~~~~~~~~~\n\n");
    printf("\tCustomer Name: %s\n", cust[n].name);
    printf("\tCustomer Contact: +880%d\n", cust[n].contact);
    printf("\t-------------------------------------------------------------\n");
    printf("\tOrdered items:\n");
    for (int j=0 ; j<cust[n].nItems ; j++)
    {
        printf("\t%d. %d x %30s\t\t%d x %7d/-\n", j+1, cust[n].ordered[j].qty, menu[cust[n].ordered[j].serial-1].item, cust[n].ordered[j].qty, menu[cust[n].ordered[j].serial-1].price);
    }
    printf("\t-------------------------------------------------------------\n");
    printf("\tTotal:\t\t\t\t\t\t%7d/-\n", billAmount);
    printf("\tVoucher: %d%%\t\t\t\t\t-%7.2f/-\n", disc,discount);
    printf("\t-------------------------------------------------------------\n");
    printf("\tSub-Total:\t\t\t\t\t%7.2f/-\n", withVouch);
    printf("\n\tWe hope to serve you again! Have a pleasant day!\n");
}

void reservation()
{
    int time;
    FILE *f;
    printf("\n\t~~~~~~~~ RESERVATION PAGE ~~~~~~~~\n");
    printf("\n\tAvailable Time Slots:\n");
    printf("\t1. 9:00 am\n");
    printf("\t2. 3:00 pm\n");
    printf("\t3. 9:00 pm\n");
    printf("\n\tPick a time for your reservation: ");
    scanf("%d", &time);
    fflush(stdin);

    switch (time)
    {
    case 1:
        if (n9am <= 5)
        {
            printf("\n\tPlease enter your details...\n\n\tName: ");
            gets(nineAM[n9am].name);
            fflush(stdin);
            printf("\tContact no.: +880");
            scanf("%d",&nineAM[n9am].contact);
            fflush(stdin);
            printf("\n\tReserving your table");
            loading();
            printf("\n\t\aSuccess! Your reservation has been saved for 9 AM. We're looking forward to having you with us!\n");
            n9am++;
            nineAMwrite(n9am,nineAM);
        }
        else
        {
            printf("\n\t\aNo more tables available for this time! Please pick another time slot");
            loading();
            system("cls");
            reservation();
        }
        break;
    case 2:
        if (n3pm <= 5)
        {
            printf("\n\tPlease enter your details...\n\n\tName: ");
            gets(threePM[n3pm].name);
            fflush(stdin);
            printf("\tContact no.: +880");
            scanf("%d",&threePM[n3pm].contact);
            fflush(stdin);
            printf("\n\tReserving your table");
            loading();
            printf("\n\t\aSuccess! Your reservation has been saved for 3 PM. We're looking forward to having you with us!\n");
            n3pm++;
            threePMwrite(n3pm,threePM);
        }
        else
        {
            printf("\n\t\aNo more tables available for this time! Please pick another time slot");
            loading();
            system("cls");
            reservation();
        }
        break;
    case 3:
        if (n9pm <= 5)
        {
            printf("\n\tPlease enter your details...\n\n\tName: ");
            gets(ninePM[n9pm].name);
            fflush(stdin);
            printf("\tContact no.: +880");
            scanf("%d",&ninePM[n9pm].contact);
            fflush(stdin);
            printf("\n\tReserving your table");
            loading();
            printf("\n\t\aSuccess! Your reservation has been saved for 9 PM. We're looking forward to having you with us!\n");
            n9pm++;
            ninePMwrite(n9pm,ninePM);
        }
        else
        {
            printf("\n\t\aNo more tables available for this time! Please pick another time slot");
            loading();
            system("cls");
            reservation();
        }
        break;
    default:
        printf("\n\t\aInvalid input! Try again");
        loading();
        system("cls");
        reservation();
    }
    int c;
    printf("\n\tWhat do you want to do next?\n");
    printf("\t1. Make another reservation\n");
    printf("\t2. Make an order\n");
    printf("\t3. Navigate to the home page\n");
    printf("\n\tOperation: ");
    scanf("%d", &c);
    fflush(stdin);
    switch (c)
    {
    case 1:
        printf("\n\tLoading the reservation page");
        loading();
        system("cls");
        reservation();
        break;
    case 2:
        printf("\n\tLoading the order page");
        loading();
        system("cls");
        order();
        break;
    case 3:
        printf("\n\tRedirecting");
        loading();
        system("cls");
        main();
        break;
    default:
        return;
    }
}


//admin interface
void getPass()
{
    int x;
    char pass[10],findPass[10],want;
    FILE *f3,*f2,*f1,*fp = fopen("password.txt","r");
    if (fp == NULL)
    {
        f1 = fopen("password.txt","w");
        printf("\n\tCreate a password for admin (max 10 characters): ");
        scanf(" %[^\n]", &pass);
        fflush(stdin);
        fprintf(f1,"%s",pass);
        fclose(f1);
        printf("\n\t\aPassword set successfully!\n");
        printf("\n\tRedirecting");
        loading();
        system("cls");
        f3 = fopen("voucher.txt","r");
        if (f3 == NULL)
        {
            printf("\n\tNew Admin detected!\n\n\tWould you like to setup a voucher code for your customers? (y/n): ");
            scanf("%c", &want);
            fflush(stdin);
            if (want=='y' || want=='Y')
            {
                printf("\n\tRedirecting");
                loading();
                system("cls");
                changeVoucher();
            }
            else
            {
                printf("\n\tRedirecting");
                loading();
                system("cls");
                correctPass();
            }
        }
        else
        {
            correctPass();
        }
        fclose(f3);
    }
    else
    {
        printf("\n\tPassword: ");
        scanf(" %[^\n]", findPass);
        fflush(stdin);
        f2 = fopen("password.txt","r");
        fgets(pass,10,f2);
        if (strcmp(pass,findPass)==0)
        {
            printf("\n\t\aLogged in successfully!\n");
            printf("\n\tRedirecting");
            loading();
            system("cls");
            correctPass();
        }
        else
        {
            printf("\n\tAccess denied!\n\n");
            printf("\t1. Try Again\n");
            printf("\t2. Return to home\n");
            printf("\n\tOperation: ");
            scanf(" %d", &x);
            fflush(stdin);
            switch(x)
            {
            case 1:
                system("cls");
                getPass();
            case 2:
                system("cls");
                main();
            default:
                printf("\tInvalid input! Redirecting");
                loading();
                system("cls");
                getPass();
            }
        }
    }
    fclose(fp);
}

void correctPass()
{
    int n;
    printf("\n\t~~~~~~~~ ADMIN PAGE ~~~~~~~~\n");
    printf("\n\tView:\n");
    printf("\t 1. Pending Orders\n");
    printf("\t 2. Reservations\n");
    printf("\t 3. Menu\n");
    printf("\n\tOthers:\n");
    printf("\t 4. Complete an Order\n");
    printf("\t 5. Add items to the menu\n");
    printf("\t 6. Delete items from the menu\n");
    printf("\t 7. Update price of menu item\n");
    printf("\t 8. Cancel a reservation\n");
    printf("\t 9. Search for an Order\n");
    printf("\t10. Search for a Reservation\n");
    printf("\t11. Change the Voucher Code\n");
    printf("\t12. Change the Admin Password\n");
    printf("\t13. Navigate back to the Home Page\n");
    printf("\t14. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &n);
    fflush(stdin);
    switch (n)
    {
    case 1:
        printf("\n\tLoading orders");
        loading();
        system("cls");
        viewOrders();
        break;
    case 2:
        system("cls");
        viewReservations();
        break;
    case 3:
        printf("\n\tLoading the menu");
        loading();
        system("cls");
        viewMenu();
        break;
    case 4:
        printf("\n\tLoading pending orders");
        loading();
        system("cls");
        completeOrder();
        break;
    case 5:
        system("cls");
        inputMenu();
        break;
    case 6:
        printf("\n\tLoading the menu");
        loading();
        system("cls");
        delMenu();
        break;
    case 7:
        printf("\n\tLoading the menu");
        loading();
        system("cls");
        updatePrice();
        break;
    case 8:
        system("cls");
        cancelReservation();
        break;
    case 9:
        system("cls");
        searchOrder();
        break;
    case 10:
        system("cls");
        searchReservations();
        break;
    case 11:
        system("cls");
        changeVoucher();
        break;
    case 12:
        system("cls");
        changePass();
        break;
    case 13:
        printf("\n\tRedirecting");
        loading();
        system("cls");
        main();
        break;
    case 14:
        return;
        break;
    default:
        printf("\n\tInvalid operation! Try again\n");
        printf("\n\tRedirecting");
        loading();
        system("cls");
        correctPass();
    }
}

void viewOrders()
{
    int i,j;
    printf("\n\t\aYou have %d orders pending.\n\n", nOrders);
    for (i=0 ; i<nOrders ; i++)
    {
        printf("\n\tOrder #%d\n",i+1);
        printf("\tName: %s\n", cust[i].name);
        printf("\tContact: +880%d\n", cust[i].contact);
        printf("\tNo. of items ordered: %d\n", cust[i].nItems);
        for (j=0 ; j<cust[i].nItems ; j++)
        {
            printf("\t%d. %d x %s\n", j+1, cust[i].ordered[j].qty, menu[cust[i].ordered[j].serial-1].item);
        }
        printf("\n\t-------------------------------\n");
    }
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Return to Admin page\n");
    printf("\t2. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        correctPass();
        break;
    case 2:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void viewReservations()
{
    int time,i;
    printf("\n\tChoose the time slot you want to view the reservations for:\n\n");
    printf("\t1. 9:00 AM\n");
    printf("\t2. 3:00 PM\n");
    printf("\t3. 9:00 PM\n");
    printf("\n\tChoose: ");
    scanf("%d", &time);
    fflush(stdin);
    switch(time)
    {
    case 1:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 9:00 AM:\n\n", n9am);
        for (i=0 ; i<n9am ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", nineAM[i].name);
            printf("\tContact: +880%d\n", nineAM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        break;
    case 2:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 3:00 PM:\n\n", n3pm);
        for (i=0 ; i<n3pm ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", threePM[i].name);
            printf("\tContact: +880%d\n", threePM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        break;
    case 3:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 9:00 PM:\n\n", n9pm);
        for (i=0 ; i<n9pm ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", ninePM[i].name);
            printf("\tContact: +880%d\n", ninePM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        break;
    default:
        printf("\t\aInvalid operation! Try again\n");
        printf("\n\tRedirecting");
        loading();
        system("cls");
        viewReservations();
    }
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. View reservations for another time-slot\n");
    printf("\t2. Return to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        viewReservations();
        break;
    case 2:
        printf("\n\tRedirecting");
        loading();
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void viewMenu()
{
    int i;
    printf("\n\t\t\t\a~~~~~~~~ THE MENU ~~~~~~~~\n\n");
    printf("\tSl.\t\t\tItem\t\t\tPrice (in Taka)\n");
    for (i=0;i<totalMenuItems;i++)
    {
        printf("\t%d.\t%30s\t\t\t%d/-\n", i+1, menu[i].item, menu[i].price);
    }
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Return to Admin page\n");
    printf("\t2. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        correctPass();
        break;
    case 2:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void completeOrder()
{
    int del,i,j,opt;
    printf("\n\tYou have %d orders pending:\n\n", nOrders);
    for (i=0 ; i<nOrders ; i++)
    {
        printf("\n\tOrder #%d\n",i+1);
        printf("\tName: %s\n", cust[i].name);
        printf("\tContact: +880%d\n", cust[i].contact);
        printf("\tNo. of items ordered: %d\n", cust[i].nItems);
        for (j=0 ; j<cust[i].nItems ; j++)
        {
            printf("\t%d. %s\n", j+1, menu[cust[i].ordered[j].serial-1].item);
        }
        printf("\n\t---------------------------\n");
    }
    printf("\n\tChoose the order that you want to complete: ");
    scanf("%d", &del);
    fflush(stdin);
    for (i=del-1 ; i<nOrders-1 ; i++)
    {
        strcpy(cust[i].name , cust[i+1].name);
        cust[i].contact = cust[i+1].contact;
        cust[i].nItems = cust[i+1].nItems;
        for (j=0 ; j<cust[i+1].nItems ; j++)
        {
            cust[i].ordered[j].serial = cust[i+1].ordered[j].serial;
        }
    }
    nOrders--;
    orderWrite(nOrders,cust);
    printf("\n\tCompleting order #%d",del);
    loading();
    printf("\n\t\aOrder #%d has been completed!\n", del);
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Complete another order\n");
    printf("\t2. Go back to admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch (opt)
    {
    case 1:
        system("cls");
        completeOrder();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        return;
    }
}

void inputMenu()
{
    int i,j,n;
    printf("\n\tNumber of items you want to add into the menu: ");
    scanf("%d", &n);
    fflush(stdin);
    for (i=totalMenuItems, j=1 ; i<(totalMenuItems+n) ; i++, j++)
    {
        printf("\n\tEnter name of item no. %d: ", j);
        gets(menu[i].item);
        fflush(stdin);
        printf("\tEnter a price for the item: ");
        scanf("%d", &menu[i].price);
        fflush(stdin);
    }
    totalMenuItems+=n;
    menuWrite(totalMenuItems, menu);
    printf("\n\tAdding item(s) to the menu");
    loading();
    printf("\n\t\aAdded item(s) successfully!\n");
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Add more items to the menu\n");
    printf("\t2. Return to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        inputMenu();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void delMenu()
{
    int i,opt,index,option;
    printf("\n\t\t\t\a~~~~~~~~ THE MENU ~~~~~~~~\n\n");
    printf("\tSl.\t\t\tItem\t\t\tPrice (in Taka)\n");
    for (i=0;i<totalMenuItems;i++)
    {
        printf("\t%d.\t%30s\t\t\t%d/-\n", i+1, menu[i].item, menu[i].price);
    }
    printf("\n\tEnter the serial of the item you want to delete: ");
    scanf("%d", &opt);
    index = opt-1;
    for (i=index ; i<totalMenuItems-1 ; i++)
    {
        strcpy(menu[i].item , menu[i+1].item);
        menu[i].price = menu[i+1].price;
    }
    totalMenuItems--;
    menuWrite(totalMenuItems,menu);
    printf("\n\tDeleting menu item #%d",opt);
    loading();
    printf("\n\t\aMenu item #%d has been deleted!\n", opt);
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Delete another item\n");
    printf("\t2. Go back to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &option);
    fflush(stdin);
    switch (option)
    {
    case 1:
        printf("\n\tLoading the menu");
        loading();
        system("cls");
        delMenu();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        return;
    }
}

void updatePrice()
{
    int i,serial,newPrice,index;
    printf("\n\t\t\t~~~~~~~~ THE MENU ~~~~~~~~\n\n");
    printf("\tSl.\t\t\tItem\t\t\tPrice (in Taka)\n");
    for (i=0;i<totalMenuItems;i++)
    {
        printf("\t%d.\t%30s\t\t\t%d/-\n", i+1, menu[i].item, menu[i].price);
    }
    printf("\n\tEnter the serial of the item whose price you want to update: ");
    scanf("%d", &serial);
    fflush(stdin);
    printf("\tEnter new price: ");
    scanf("%d", &newPrice);
    index = serial-1;
    menu[index].price = newPrice;
    menuWrite(totalMenuItems, menu);
    printf("\n\tUpdating price of the item");
    loading();
    printf("\n\t\aUpdated price successfully!\n");
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Update more prices\n");
    printf("\t2. Return to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        updatePrice();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void cancelReservation()
{
    int time,i,cancel,index,option;
    printf("\n\tChoose the time-slot you want to delete the reservation for:\n\n");
    printf("\t1. 9:00 AM\n");
    printf("\t2. 3:00 PM\n");
    printf("\t3. 9:00 PM\n");
    printf("\n\tChoose: ");
    scanf("%d", &time);
    fflush(stdin);
    switch(time)
    {
    case 1:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 9:00 AM:\n\n", n9am);
        for (i=0 ; i<n9am ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", nineAM[i].name);
            printf("\tContact: +880%d\n", nineAM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        printf("\n\tChoose the reservation that you want to cancel: ");
        scanf("%d", &cancel);
        fflush(stdin);
        index = cancel-1;
        for (i=index ; i<n9am-1 ; i++)
        {
            strcpy(nineAM[i].name , nineAM[i+1].name);
            nineAM[i].contact = nineAM[i+1].contact;
        }
        n9am--;
        nineAMwrite(n9am,nineAM);
        printf("\n\tCanceling reservation for table #%d", cancel);
        loading();
        printf("\n\t\aReservation for table #%d has been cancelled!\n", cancel);
        printf("\n\tWhat do you want to do?\n");
        printf("\t1. Cancel another reservation\n");
        printf("\t2. Go back to Admin page\n");
        printf("\t3. Exit the program\n");
        printf("\n\tOperation: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            system("cls");
            cancelReservation();
            break;
        case 2:
            system("cls");
            correctPass();
            break;
        case 3:
            return;
            break;
        default:
            return;
        }
        break;
    case 2:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 3:00 PM:\n\n", n3pm);
        for (i=0 ; i<n3pm ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", threePM[i].name);
            printf("\tContact: +880%d\n", threePM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        printf("\n\tChoose the reservation that you want to cancel: ");
        scanf("%d", &cancel);
        fflush(stdin);
        index = cancel-1;
        for (i=index ; i<n3pm-1 ; i++)
        {
            strcpy(threePM[i].name , threePM[i+1].name);
            threePM[i].contact = threePM[i+1].contact;
        }
        n3pm--;
        threePMwrite(n3pm,threePM);
        printf("\n\tCanceling reservation for table #%d", cancel);
        loading();
        printf("\n\t\aReservation for table #%d has been cancelled!\n", cancel);
        printf("\n\tWhat do you want to do?\n");
        printf("\t1. Cancel another reservation\n");
        printf("\t2. Go back to Admin page\n");
        printf("\t3. Exit the program\n");
        printf("\n\tOperation: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            system("cls");
            cancelReservation();
            break;
        case 2:
            system("cls");
            correctPass();
            break;
        case 3:
            return;
            break;
        default:
            return;
        }
        break;
    case 3:
        printf("\n\tLoading reservations");
        loading();
        system("cls");
        printf("\n\t\aYou have %d out of 5 tables reserved for 9:00 PM:\n\n", n9pm);
        for (i=0 ; i<n9pm ; i++)
        {
            printf("\n\tTable #%d:\n", i+1);
            printf("\tName: %s\n", ninePM[i].name);
            printf("\tContact: +880%d\n", ninePM[i].contact);
            printf("\n\t-------------------------------------\n");
        }
        printf("\n\tChoose the reservation that you want to cancel: ");
        scanf("%d", &cancel);
        fflush(stdin);
        index = cancel-1;
        for (i=index ; i<n9pm-1 ; i++)
        {
            strcpy(ninePM[i].name , ninePM[i+1].name);
            ninePM[i].contact = ninePM[i+1].contact;
        }
        n9pm--;
        ninePMwrite(n9pm,ninePM);
        printf("\n\tCanceling reservation for table #%d", cancel);
        loading();
        printf("\n\t\aReservation for table #%d has been cancelled!\n", cancel);
        printf("\n\tWhat do you want to do?\n");
        printf("\t1. Cancel another reservation\n");
        printf("\t2. Go back to Admin page\n");
        printf("\t3. Exit the program\n");
        printf("\n\tOperation: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            system("cls");
            cancelReservation();
            break;
        case 2:
            system("cls");
            correctPass();
            break;
        case 3:
            return;
            break;
        default:
            return;
        }
        break;
    default:
        printf("\t\aInvalid operation! Try again\n");
        printf("\n\tRedirecting");
        loading();
        system("cls");
        cancelReservation();
    }
}

void searchOrder()
{
    int i,j,k,contact,choice;
    char name[50];
    printf("\n\tWhat do you want to search by?\n");
    printf("\t1. Search by name\n");
    printf("\t2. Search by contact number\n");
    printf("\n\tOperation: ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 1:
        system("cls");
        printf("\n\tEnter the full name of the customer: ");
        gets(name);
        fflush(stdin);
        printf("\n\tSearching");
        loading();
        system("cls");
        printf("\n\tOrders with the name %s:\n", name);
        for (i=0,k=0 ; i<nOrders ; i++)
        {
            if(strcmp(name,cust[i].name)==0)
            {
                printf("\n\tName: %s\n", cust[i].name);
                printf("\tContact: +880%d\n", cust[i].contact);
                printf("\tNo. of items ordered: %d\n", cust[i].nItems);
                for (j=0 ; j<cust[i].nItems ; j++)
                {
                    printf("\t%d. %d x %s\n", j+1, cust[i].ordered[j].qty, menu[cust[i].ordered[j].serial-1].item);
                }
                k++;
                printf("\n\t-------------------------------\n");
            }
        }
        printf("\n\t\aSearch complete! %d result(s) found.\n", k);
        break;
    case 2:
        system("cls");
        printf("\n\tEnter the contact number of the customer: +880");
        scanf("%d", &contact);
        fflush(stdin);
        printf("\n\tSearching");
        loading();
        system("cls");
        printf("\n\tOrders with the contact number +880%d:\n", contact);
        for (i=0,k=0 ; i<nOrders ; i++)
        {
            if(cust[i].contact == contact)
            {
                printf("\n\tName: %s\n", cust[i].name);
                printf("\tContact: +880%d\n", cust[i].contact);
                printf("\tNo. of items ordered: %d\n", cust[i].nItems);
                for (j=0 ; j<cust[i].nItems ; j++)
                {
                    printf("\t%d. %d x %s\n", j+1, cust[i].ordered[j].qty, menu[cust[i].ordered[j].serial-1].item);
                }
                k++;
                printf("\n\t-------------------------------\n");
            }
        }
        printf("\n\t\aSearch complete! %d result(s) found.\n", k);
        break;
    default:
        printf("\n\tInvalid input! Try again\n");
        printf("\n\tRedirecting");
        loading();
        system("cls");
        searchOrder();
    }
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Search for another order\n");
    printf("\t2. Return to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        searchOrder();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void searchReservations()
{
    int time,i,j,choice,contact;
    char name[50];
    printf("\n\tChoose the time slot you want to search in:\n\n");
    printf("\t1. 9:00 AM\n");
    printf("\t2. 3:00 PM\n");
    printf("\t3. 9:00 PM\n");
    printf("\n\tChoose: ");
    scanf("%d", &time);
    fflush(stdin);
    printf("\n\tWhat do you want to search by?\n");
    printf("\t1. Search by name\n");
    printf("\t2. Search by contact number\n");
    printf("\n\tOperation: ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 1:
        system("cls");
        printf("\n\tEnter the full name of the customer: ");
        gets(name);
        fflush(stdin);
        printf("\n\tSearching");
        loading();
        system("cls");
        switch(time)
        {
        case 1:
            printf("\n\tReservations for 9:00 AM with name \"%s\"\n", name);
            for (i=0,j=0 ; i<n9am ; i++)
            {
                if(strcmp(name,nineAM[i].name)==0)
                {
                    printf("\n\tName: %s\n", nineAM[i].name);
                    printf("\tContact: +880%d\n", nineAM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        case 2:
            printf("\n\tReservations for 3:00 PM with name \"%s\"\n", name);
            for (i=0,j=0 ; i<n3pm ; i++)
            {
                if(strcmp(name,threePM[i].name)==0)
                {
                    printf("\n\tName: %s\n", threePM[i].name);
                    printf("\tContact: +880%d\n", threePM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        case 3:
            printf("\n\tReservations for 9:00 PM with name \"%s\"\n", name);
            for (i=0,j=0 ; i<n9pm ; i++)
            {
                if(strcmp(name,ninePM[i].name)==0)
                {
                    printf("\n\tName: %s\n", ninePM[i].name);
                    printf("\tContact: +880%d\n", ninePM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");;
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        default:
            printf("\t\aInvalid operation! Try again\n");
            printf("\n\tRedirecting");
            loading();
            system("cls");
            searchReservations();
        }
        break;
    case 2:
        system("cls");
        printf("\n\tEnter the contact number of the customer: +880");
        scanf("%d", &contact);
        fflush(stdin);
        printf("\n\tSearching");
        loading();
        system("cls");
        switch(time)
        {
        case 1:
            printf("\n\tReservations for 9:00 AM with contact number +880%d\n", contact);
            for (i=0,j=0 ; i<n9am ; i++)
            {
                if(nineAM[i].contact == contact)
                {
                    printf("\n\tName: %s\n", nineAM[i].name);
                    printf("\tContact: +880%d\n", nineAM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        case 2:
            printf("\n\tReservations for 3:00 PM with contact number +880%d\n", contact);
            for (i=0,j=0 ; i<n3pm ; i++)
            {
                if(threePM[i].contact == contact)
                {
                    printf("\n\tName: %s\n", threePM[i].name);
                    printf("\tContact: +880%d\n", threePM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        case 3:
            printf("\n\tReservations for 9:00 PM with contact number +880%d\n", contact);
            for (i=0,j=0 ; i<n9pm ; i++)
            {
                if(ninePM[i].contact == contact)
                {
                    printf("\n\tName: %s\n", ninePM[i].name);
                    printf("\tContact: +880%d\n", ninePM[i].contact);
                    j++;
                    printf("\n\t---------------------------\n");
                }
            }
            printf("\n\t\aSearch complete! %d result(s) found.\n", j);
            break;
        default:
            printf("\t\aInvalid operation! Try again\n");
            printf("\n\tRedirecting");
            loading();
            system("cls");
            searchReservations();
        }
        break;
    }
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Search for another reservation\n");
    printf("\t2. Return to Admin page\n");
    printf("\t3. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        searchReservations();
        break;
    case 2:
        system("cls");
        correctPass();
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void changeVoucher()
{
    FILE *fv = fopen("voucher.txt","w");
    FILE *fd = fopen("discount.txt","w");
    printf("\n\tEnter voucher code: ");
    scanf("%[^\n]", vouch);
    fflush(stdin);
    printf("\n\tEnter the discount in %%: ");
    scanf("%d", &disc);
    fflush(stdin);
    fprintf(fv,"%s",vouch);
    fprintf(fd,"%d",disc);
    printf("\n\tChanging the voucher code");
    loading();
    fclose(fv);
    fclose(fd);
    printf("\n\t\aVoucher code changed successfully!\n");
    int opt;
    printf("\n\tWhat do you want to do?\n");
    printf("\t1. Return to Admin page\n");
    printf("\t2. Exit the program\n");
    printf("\n\tOperation: ");
    scanf("%d", &opt);
    fflush(stdin);
    switch(opt)
    {
    case 1:
        system("cls");
        correctPass();
        break;
    case 2:
        return;
        break;
    default:
        printf("\n\tInvalid input! Terminating the program");
        loading();
        return;
    }
}

void changePass()
{
    char newPass[10];
    FILE *fp = fopen("password.txt","w+");
    printf("\n\tEnter new password: ");
    scanf("%[^\n]", &newPass);
    fflush(stdin);
    fprintf(fp,"%s",newPass);
    fclose(fp);
    printf("\n\tChanging the password");
    loading();
    printf("\n\t\aPassword changed successfully!\n");
    printf("\n\tThe new password is: %s\n", newPass);
    printf("\n\tRedirecting");
    loading();
    system("cls");
    getPass();
}

//file updating functions
//updating the order file
void orderWrite(int n, customer cust[n])
{
    int i,j;
    FILE *f=fopen("order.txt","w");
    fprintf(f,"%d\n",n);
    for (i=0;i<n;i++)
    {
        fprintf(f,"%s\n",cust[i].name);
        fprintf(f,"%d\n",cust[i].contact);
        fprintf(f,"%d\n",cust[i].nItems);
        for (j=0;j<cust[i].nItems;j++)
        {
            fprintf(f,"%d %d\n", cust[i].ordered[j].serial, cust[i].ordered[j].qty);
        }
    }
    fclose(f);
}
//updating the menu file
void menuWrite(int n, MENU menu[n])
{
    int i;
    FILE *f = fopen("menu.txt","w");
    fprintf(f,"%d\n", n);
    for (i=0;i<n;i++)
    {
        fprintf(f,"%s\n",menu[i].item);
        fprintf(f,"%d\n",menu[i].price);
    }
    fclose(f);
}
//writing the reservations
void nineAMwrite(int n, rsvp nineAM[n])
{
    int i;
    FILE *f = fopen("9am.txt","w");
    fprintf(f,"%d\n",n);
    for (i=0 ; i<n ; i++)
    {
        fprintf(f,"%s\n", nineAM[i].name);
        fprintf(f,"%d\n", nineAM[i].contact);
    }
    fclose(f);
}
void threePMwrite(int n, rsvp threePM[n])
{
    int i;
    FILE *f = fopen("3pm.txt","w");
    fprintf(f,"%d\n",n);
    for (i=0 ; i<n ; i++)
    {
        fprintf(f,"%s\n", threePM[i].name);
        fprintf(f,"%d\n", threePM[i].contact);
    }
    fclose(f);
}
void ninePMwrite(int n, rsvp ninePM[n])
{
    int i;
    FILE *f = fopen("9pm.txt","w");
    fprintf(f,"%d\n",n);
    for (i=0 ; i<n ; i++)
    {
        fprintf(f,"%s\n", ninePM[i].name);
        fprintf(f,"%d\n", ninePM[i].contact);
    }
    fclose(f);
}

//animation functions
void loading()
{
    delay(500);
    printf(".");
    delay(500);
    printf(".");
    delay(500);
    printf(".\n");
}
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
