#include<stdio.h>
#include<process.h>
#include<string.h>
#include<windows.h>
#include<string.h>
#include<time.h>

struct login
{
    char name[15];
    char passw[15];
} login[1000];

void clrscr(){system("cls");}
struct login login_fun();
int getch();
int getche();
void mainMenu(char *name);
void bookingMenu(char *name);
char* getPassword(char *checker){
    char ch1;
    printf("\n\n\t\t\t\t  Enter a valid PASSWORD: ");
    int j;
        for(j = 0; j<14; j++){
            ch1 = getch();
            checker[j] = ch1;
            if(ch1!= 13){
                printf("*");
            }
            if(ch1 == 13){
                checker[j] = '\0';
                break;
            }
        }
    return checker;
}

void registration()
{
    int i,flag = 1;
    char checker[15];
    _flushall();
    FILE *fw;
    fw=fopen("userdatabase.txt","a+");
    for(i=0; i<1000; i++)
    {
        printf("\n\n\t\t\t\t  Enter a valid USERNAME: ");
        scanf("%s",checker);
        _flushall();
        while(!feof(fw))
        {
          fread(&login[i],sizeof(login[i]),1,fw);
          if(strcmp(checker,login[i].name)==0)
            {
            printf("\n\n\t\t\t\t  USERNAME ALREDY EXISTS");
            flag = 0;
            break;
            }
        }
        if(flag == 0){
            break;
        }
        strcpy(login[i].name, checker);
        strcpy(login[i].passw, getPassword(checker));
        fwrite(&login[i],sizeof(struct login),1,fw);
        printf("\n\n\t\t\t\t  You registered successfully");
        break;
    }
    fclose(fw);
    getch();
}


struct login login_fun()
{
    FILE *fp;
    char name[15],pass[15];
    int checku,checkp,i;
    struct login flag;
    strcpy(flag.name ,"NULL");
    strcpy(flag.passw ,"NULL");
    fp=fopen("userdatabase.txt","r");
    for(i=0; i<10000; i++)
    {
        clrscr();
        printf("\n\n\t\t\t\t\tWELCOME TO HOTEL LOGIN ZONE");
        printf("\n\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n\n\t\t\t\t  ENTER USERNAME: ");
        _flushall();
        scanf("%s",name);
        strcpy(pass,getPassword(pass));
        while(!feof(fp))
        {

            fread(&login[i],sizeof(login[i]),1,fp);
            checku=strcmp(name,login[i].name);
            checkp=strcmp(pass,login[i].passw);
            if(checku==0&&checkp==0)
            {
                flag=login[i];
                break;
            }
        }

        break;
    }
    fclose(fp);
    return flag;
}

void loginModuleMainFunction()
{
    int choice;
    struct login j;
    while(1){
        clrscr();
        printf("\n\n\t\t\t\t\tWELCOME TO HOTEL SYSTEM");
        printf("\n\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n\n\t\t\t\t  1----------Register");
        printf("\n\n\t\t\t\t  2----------Login");
        printf("\n\n\t\t\t\t  3----------Exit");
        printf("\n\n\t\t\t\t  Enter your choice : ");
        _flushall();
        scanf("%d",&choice);
        switch(choice){
            case 1: registration();
                    break;

            case 2:
                    j=login_fun();
                    clrscr();
                    if(strcmp(j.name,"NULL") != 0)
                    {
                        bookingMenu(j.name);
                        getch();
                    }
                    else
                    {
                        printf("\n\n\t\t\t\t  Username or Password is wrong");
                        getch();
                        continue;
                    }
                    break;
            case 3: exit(0);
            default: printf("\n\n\t\t\t\t  Enter valid choice");
        }
    }
}

void copyFileFunction(FILE *fptr1, FILE *fptr2){
    char c;
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }
    fprintf(fptr2,"\n");
}


void printingFinalBill(FILE *fp){
    system("cls");
    char c[1000];
    printf("\t\t\t\tTotal Bill\n");
    while(fscanf(fp, "%[\n]", c) != EOF){
    fscanf(fp, "%[^\n]", c);
    printf("%s\n",c);}
}

void feedBackMenu(FILE *fp)
{
    int a,b,c;
    system("cls");
    fprintf(fp,"\nFEEDBACK RESULT");
    printf("---* WE'D LOVE YOUR FEEDBACK *---");
    printf("\n\nThank you! Please take a minute to review your order and say it like it is.");
    printf("\nReview us out of 5: ");
    a1:printf("\nHow was your experience with our staff? :");
    scanf("%d",&a);
    if (a>=1 && a<=5)
    {
        fprintf(fp,"\nExperience with staff : %d",a);
        printf("-------------");
        printf("\n| ");
        while (a<=5 && a>=1)
            {
                printf("*");
                printf(" ");
                a--;
            }
        printf("|");
        printf("\n-------------");
    }
    else if (a<1 || a>5)
    {
        printf("\nPlease rate out of 5.\n");
        goto a1;
    }
    b1:printf("\nHow was our food quality? :");
    scanf("%d",&b);
    if (b>=1 && b<=5)
    {
        fprintf(fp,"\nFood Quality : %d",b);
        printf("-------------");
        printf("\n| ");
            while (b<=5 && b>=1)
                {
                    printf("*");
                    printf(" ");
                    b--;
                }
        printf("|");
        printf("\n-------------");

    }
    else if (b<1 || b>5)
    {
        printf("\nPlease rate out of 5.\n");
        goto b1;
    }
    c1:printf("\nAbout hygiene :");
    scanf("%d",&c);
    if (c>=1 && c<=5)
    {
        fprintf(fp,"\nHygiene : %d\n",c);
        printf("-------------");
        printf("\n| ");
        while (c<=5 && c>=1)
            {
                printf("*");
                printf(" ");
                c--;
            }
        printf("|");
        printf("\n-------------");

    }
    else if(c>=5 || c<=1)
    {
        printf("\nPlease rate out of 5.\n");
        goto c1;
    }
    printf("\n\nThank you.");
}

void dateAndTimeFunction(FILE *fp){
    time_t t;
    time(&t);
    char *dataTime = ctime(&t);
    fprintf(fp,dataTime);
    fprintf(fp,"\n");
}

void bookingMenu(char *name)
{
    int x,y,x1,x2,x3;
    z:
    printf("-----------------* Welcome *-----------------");
    printf("\nMention your booking type:-");
    printf("\n1. Take away");
    printf("\n2. Table reservation");
    printf("\n3. Place order");
    printf("\n0. To exit.");
    printf("\n\nPlease enter serial number of your order type:");
    scanf("%d",&x);
    if (x==1)
    {
        printf("");
        printf("---------------------------------------------");
        printf("---------------------------------------------");
        printf("\nYou selected for Take away.");
        printf("\n\nPress 0 to go back to previous page.");
        printf("\n\nPress 1 to book Your Order.\n");
        scanf("%d",&x1);
        printf("---------------------------------------------");
        if (x1==0)
        {
            goto z;
        }
    }
    else if (x==2)
    {
        printf("---------------------------------------------");
        printf("---------------------------------------------");
        printf("\nYou selected for Table reservation.");
        printf("\n\nPress 0 to go back to previous page.");
        printf("\n\nPress 1 to reserve your table.\n");
        scanf("%d",&x2);
        if (x2==0)
        {
            goto z;
        }
        else if (x2==1)
        {
        printf("\nPlease mention total number of members:");
        scanf("%d",&y);
        printf("\n\nAt what hour(0 to 24) you would like to come? :");
        scanf("%d",&x3);
        printf("\nThank you, your table has been reserved.\n");
        printf("---------------------------------------------");
        }
    }
    else if (x==0)
    {
        exit(0);
    }
    if (x1==1 || x==3)
    {
        mainMenu(name);
    }
}

void mainMenu(char *name)
{
    int i=1, j=0, q,ib;///ib is our individual bill
    int bill = 0;
    system("cls");
    FILE *fp;
    FILE *fw;
    char filename[40];
    strcpy(filename,name);
    strcat(filename,".txt");
    fp=fopen("order.txt","w");
    fprintf(fp,"Quantity    Items        bill");
    label:
    system("cls");
    printf("\n\t\t\t\t\t***Main Menu***");
    printf("\nWhat would you like to have?");
    printf("\n1. Starters\n2. Breads\n3. Vegetables\n4. Rice\n5. Dal\n6. South Indian\n7. Pizza\n8. Sandwich\n9. Noodles\n10. Beverages\n0. Get final amount");
    printf("\nEnter the serial number to get the menu card:");
    scanf("%d",&j);
    switch(j)
    {

    case 1:


        for (;i != 0;)
        {

            printf("\n\n**STARTERS**\n\n");
            printf("1. Tomato Soup                   40\n2. Manchow Soup                  45\n3. Hot & Sour Soup               45\n4. Sweet Corn Soup               40\n5. Dragon Potato                 35\n6. Garlic Bread                  35\n7. Dry Manchurian                70\n8. Chilli-Paneer                 50\n9. Aloo Paratha                  50");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i1:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib =40 *q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Tomato soup(s)---->%d",q,ib);
                    fprintf(fp,"\n%d Tomato soup(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i1;
                        }

                    case 2:

                        i2:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=45*q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Manchow soup(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Manchow soup(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i2;
                        }

                    case 3:
                        i3:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=(45 * q);
                        bill = bill + ib;
                        printf("\nYou ordered %d Hot & Sour soup(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Hot & Sour soup(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i3;
                        }

                    case 4:
                        i4:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=40 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Sweet Corn soup(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Sweet Corn soup(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i4;
                        }

                    case 5:
                        i5:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=35 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Dragon Potato---->%d",q,ib);
                        fprintf(fp,"\n%d Dragon Potato---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i5;
                        }

                    case 6:
                        i6:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=35 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Garlic Bread---->%d",q,ib);
                        fprintf(fp,"\n%d Garlic Bread---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i6;
                        }

                    case 7:
                        i7:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=70 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Gravy/Dry Manchurian---->%d",q,ib);
                        fprintf(fp,"\n%d Gravy/Dry Manchurian---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i7;
                        }

                    case 8:
                        i8:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib=50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Chilli-Paneer---->%d",q,ib);
                        fprintf(fp,"\n%d Chilli-Paneer---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i8;
                        }

                    case 9:
                        i9:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Aloo Paratha---->%d",q,ib);
                        fprintf(fp,"\n%d Aloo Paratha---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i9;
                        }

                    case 0:
                        goto label;

                }
        }
    case 2:
            i = 69;
            for (;i != 0;)
            {
                printf("\n\n**BREADS**\n\n");
                printf("1. Plain Roti                    10\n2. Butter Roti                   15\n3. Tandoori Roti                 20\n4. Plain Naan                    20\n5. Butter Naan                   25\n6. Cheese Naan                   35\n7. Cheese-Butter Naan            45\n8. Plain Paratha                 20\n9. Butter Paratha                30\n10. Paneer Paratha               40");
                printf("\n\nEnter 0 to go back to the main menu");
                printf("\nEnter the serial number of the item you want to enter:");
                scanf("%d",&i);

                switch (i)
                {
                    case 1:
                        i10:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 10 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Plain Roti(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Plain Roti(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i10;
                        }

                    case 2:
                        i11:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 15 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Butter Roti(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Butter Roti(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i11;
                        }

                    case 3:
                        i12:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 20 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Tandoori Roti(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Tandoori Roti(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i12;
                        }

                    case 4:
                        i13:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 20 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Plain Naan(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Plain Naan(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i13;
                        }

                    case 5:
                        i14:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 25 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Butter Naan(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Butter Naan(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i14;
                        }

                    case 6:
                        i15:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 35 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Cheese Naan(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Cheese Naan(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i15;
                        }

                    case 7:
                        i16:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 45 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Cheee-Butter Naan(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Cheee-Butter Naan(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i16;
                        }

                    case 8:
                        i17:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 20 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Plain Paratha(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Plain Paratha(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i17;
                        }

                    case 9:
                        i18:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 30 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Butter Paratha(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Butter Paratha(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i18;
                        }

                    case 10:
                        i19:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 40 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Paratha(s)---->%d",q,ib);
                        fprintf(fp,"\n%d Paneer Paratha(s)---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i19;
                        }

                    case 0:
                        goto label;
                }
            }
    case 3:
        i = 69;
        for (;i != 0;)
            {
                printf("\n\n**VEGETABLES**\n\n");
                printf("1. Paneer Tikka                  60\n2. Paneer-Bhurji                 70\n3. Paneer-Handi                  70\n4. Kadai-Paneer                  75\n5. Shahi-Paneer                  75\n6. Palak-Paneer                  60\n7. Paneer Butter Massala         75\n8. Paneer-Toofani                65\n9. Paneer-Pasanda                70\n10. Veg. Tadka                   70\n11. Veg. Kofta                   80\n12. Aloo-Mutter                  50\n13. Khoya-Kaju                   65\n14. Sev-Tameta                   50\n15. Baingan ka Bharta            50\n16. Garlic-Potato                40");
                printf("\n\nEnter 0 to go back to the main menu");
                printf("\nEnter the serial number of the item you want to enter:");
                scanf("%d",&i);

                switch (i)
                {
                    case 1:
                        i20:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 60 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Tikka---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Tikka---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i20;
                        }

                    case 2:
                        i21:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 70 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Bhurji---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Bhurji---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i21;
                        }

                    case 3:
                        i22:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 70 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Handi---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Handi---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i22;
                        }

                    case 4:
                        i23:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 75 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Kadai Paneer---->%d",q,ib);
                        fprintf(fp,"\n %d Kadai Paneer---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i23;
                        }

                    case 5:
                        i24:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 75 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Shahi Paneer---->%d",q,ib);
                        fprintf(fp,"\n %d Shahi Paneer---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i24;
                        }

                    case 6:
                        i25:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 60 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Palak Paneer---->%d",q,ib);
                        fprintf(fp,"\n %d Palak Paneer---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i25;
                        }

                    case 7:
                        i26:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 75 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Butter Masala---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Butter Masala---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i26;
                        }

                    case 8:
                        i27:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 65 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Toofani---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Toofani---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i27;
                        }

                    case 9:
                        i28:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 70 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Paneer Pasanda---->%d",q,ib);
                        fprintf(fp,"\n %d Paneer Pasanda---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i28;
                        }

                    case 10:
                        i29:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 70 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Veg. Tadka---->%d",q,ib);
                        fprintf(fp,"\n %d Veg. Tadka---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i29;
                        }

                    case 11:
                        i30:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 80 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Veg. Kofta---->%d",q,ib);
                        fprintf(fp,"\n %d Veg. Kofta---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i30;
                        }

                    case 12:
                        i31:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Aloo Mutter---->%d",q,ib);
                        fprintf(fp,"\n %d Aloo Mutter---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i31;
                        }

                    case 13:
                        i32:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 65 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Khoya-Kaju---->%d",q,ib);
                        fprintf(fp,"\n %d Khoya-Kaju---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i32;
                        }

                    case 14:
                        i33:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Sev Tameta---->%d",q,ib);
                        fprintf(fp,"\n %d Sev Tameta---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i33;
                        }

                    case 15:
                        i34:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Baingan ka bharta---->%d",q,ib);
                        fprintf(fp,"\n %d Baingan ka bharta---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i34;
                        }

                    case 16:
                        i35:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 40 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Garlic Potato---->%d",q,ib);
                        fprintf(fp,"\n %d Garlic Potato---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i35;
                        }

                    case 0:
                        goto label;
                }
            }

    case 4:
        i = 69;
        for (;i != 0;)
            {
                printf("\n\n**RICE**\n\n");
                printf("1. Plain Rice                    25\n2. Jeera-Rice                    30\n3. Pulao                         40\n4. Schezwan Rice                 50\n5. Manchurian Rice               50\n6. Biryani                       55\n7. Khichdi                       35");
                printf("\n\nEnter 0 to go back to the main menu");
                printf("\nEnter the serial number of the item you want to enter:");
                scanf("%d",&i);

                switch (i)
                {
                    case 1:
                        i36:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 25 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Plain Rice---->%d",q,ib);
                        fprintf(fp,"\n %d Plain Rice---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i36;
                        }

                    case 2:
                        i38:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 30 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Jeera Rice---->%d",q,ib);
                        fprintf(fp,"\n %d Jeera Rice---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i38;
                        }

                    case 3:
                        i39:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 40 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Pulao---->%d",q,ib);
                        fprintf(fp,"\n %d Pulao---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i39;
                        }

                    case 4:
                        i40:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Schezwan Rice---->%d",q,ib);
                        fprintf(fp,"\n %d Schezwan Rice---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i40;
                        }

                    case 5:
                        i41:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 50 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Manchurian Rice---->%d",q,ib);
                        fprintf(fp,"\n %d Manchurian Rice---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i41;
                        }

                    case 6:
                        i42:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 55 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Biryani---->%d",q,ib);
                        fprintf(fp,"\n %d Biryani---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i42;
                        }

                    case 7:
                        i43:printf("Enter quantity:");
                        scanf("%d",&q);
                        if (q >= 0)
                        {
                        ib = 35 * q;
                        bill = bill + ib;
                        printf("\nYou ordered %d Khichdi---->%d",q,ib);
                        fprintf(fp,"\n %d Khichdi---->%d",q,ib);
                        break;
                        }
                        else
                        {
                        printf("Enter positive quantity\n");
                        goto i43;
                        }

                    case 0:
                        goto label;
                }
            }
    case 5:
        i = 69;
        for (;i != 0;)
        {
            printf("\n\n**DAL**\n\n");
            printf("1. Plain Dal                     20\n2. Dal Tadka                     30\n3. Dal Makhni                    35\n4. Dal Fry                       30\n5. Curry                         25");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i44:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 20 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Plain Dal---->%d",q,ib);
                    fprintf(fp,"\n %d Plain Dal---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i44;
                    }

                case 2:
                    i45:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Dal Tadka---->%d",q,ib);
                    fprintf(fp,"\n %d Dal Tadka---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i45;
                    }

                case 3:
                    i46:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 35 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Dal Makhni---->%d",q,ib);
                    fprintf(fp,"\n %d Dal Makhni---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i46;
                    }

                case 4:
                    i47:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Dal Fry---->%d",q,ib);
                    fprintf(fp,"\n %d Dal Fry---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i47;
                    }

                case 5:
                    i48:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 25 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Curry---->%d",q,ib);
                    fprintf(fp,"\n %d Curry---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i48;
                    }

                case 0:
                    goto label;

            }
        }
    case 6:
        i = 69;
        for (;i != 0;)
        {
            printf("\n\n**SOUTH-INDIAN**\n\n");
            printf("1. Idli-Sambar                   40\n2. Plain-Paper dosa              20\n3. Masala Dosa                   30\n4. Mysore-Masala Dosa            45\n5. Plain Uttapam                 30\n6. Onion Uttapam                 35\n7. Cheese-Butter Uttapam         50\n8. Vadai-Sambar                  30");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i49:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 40 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Idli-Sambar---->%d",q,ib);
                    fprintf(fp,"\n %d Idli-Sambar---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i49;
                    }

                case 2:
                    i50:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 20 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Plai Paper Dosa---->%d",q,ib);
                    fprintf(fp,"\n %d Plai Paper Dosa---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i50;
                    }

                case 3:
                    i51:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Masala Dosa---->%d",q,ib);
                    fprintf(fp,"\n %d Masala Dosa---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i51;
                    }

                case 4:
                    i52:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 45 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Mysore Masala Dosa---->%d",q,ib);
                    fprintf(fp,"\n %d Mysore Masala Dosa---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i52;
                    }

                case 5:
                    i53:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Plain Uttapam---->%d",q,ib);
                    fprintf(fp,"\n %d Plain Uttapam---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i53;
                    }

                case 6:
                    i54:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 35 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Onion Uttapam---->%d",q,ib);
                    fprintf(fp,"\n %d Onion Uttapam---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i54;
                    }

                case 7:
                    i55:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 50 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Cheese- Uttapam---->%d",q,ib);
                    fprintf(fp,"\n %d Cheese- Uttapam---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i55;
                    }

                case 8:
                    i56:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Vadai-Sambar---->%d",q,ib);
                    fprintf(fp,"\n %d Vadai-Sambar---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i56;
                    }

                case 0:
                    goto label;

            }
        }
    case 7:
        i = 69;
        for (;i != 0;)
        {
            printf("\n\n**PIZZA**\n\n");
            printf("1. Margherita Pizza              80\n2. Mushroom Pizza                75\n3. Italian Pizza                 80\n4. Cheese-Burst Pizza            85\n5. Mexican Pizza                 70\n6. Chatpata-Paneer Pizza         80\n7. Veg. Pizza                    65");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i57:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 80 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Margherita Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Margherita Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i57;
                    }

                case 2:
                    i58:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 75 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Mushroom Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Mushroom Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i58;
                    }

                case 3:
                    i59:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 80 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Italian Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Italian Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i59;
                    }

                case 4:
                    i60:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 85 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Cheese-Burst Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Cheese-Burst Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i60;
                    }

                case 5:
                    i61:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 70 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Mexican Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Mexican Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i61;
                    }

                case 6:
                    i62:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 80 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Chatpta Paneer Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Chatpta Paneer Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i62;
                    }

                case 7:
                    i63:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 65 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Veg. Pizza(s)---->%d",q,ib);
                    fprintf(fp,"\n %d Veg. Pizza(s)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i63;
                    }

                case 0:
                    goto label;

            }
        }
    case 8:
        i = 69;
        for (;i != 0;)
        {
            printf("\n\n**SANDWICH**\n\n");
            printf("1. Veg. Sandwich                 30\n2. Veg. Grill Sandwich           50\n3. Cheese Sandwich               60\n4. Cheese Grill Sandwich         70\n5. Bread Mayonnaise/Butter/Jam   50");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i64:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Veg. Sandwich(es)---->%d",q,ib);
                    fprintf(fp,"\n %d Veg. Sandwich(es)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i64;
                    }

                case 2:
                    i65:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 50 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Veg. Grill Sandwich(es)---->%d",q,ib);
                    fprintf(fp,"\n %d Veg. Grill Sandwich(es)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i65;
                    }

                case 3:
                    i66:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 60 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Cheese Sandwich(es)---->%d",q,ib);
                    fprintf(fp,"\n %d Cheese Sandwich(es)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i66;
                    }

                case 4:
                    i67:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 75 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Cheese Grill Sandwich(es)---->%d",q,ib);
                    fprintf(fp,"\n %d Cheese Grill Sandwich(es)---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i67;
                    }

                case 5:
                    i68:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 55 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Bread Mayonnaise/Butter/Jam---->%d",q,ib);
                    fprintf(fp,"\n %d Bread Mayonnaise/Butter/Jam---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i68;
                    }

                case 0:
                    goto label;

            }
        }
    case 9:
        i = 69;
        for (;i != 0;)
        {
        printf("\n\n**NOODLES**\n\n");
        printf("1. Hakka-Noodles                 60\n2. Schezwan-Noodles              75\n3. Manchurian-Noodles            75\n4. Maggie                        40");
        printf("\n\nEnter 0 to go back to the main menu");
        printf("\nEnter the serial number of the item you want to enter:");
        scanf("%d",&i);

        switch (i)
            {
                case 1:
                    i69:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 60 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Hakka-Noodles---->%d",q,ib);
                    fprintf(fp,"\n %d Hakka-Noodles---->%d",q,ib);
                    break;
                    }else
                    {
                    printf("Enter positive quantity\n");
                    goto i69;
                    }

                case 2:
                    i70:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 75 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Schezwan-Noodles---->%d",q,ib);
                    fprintf(fp,"\n %d Schezwan-Noodles---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i70;
                    }

                case 3:
                    i71:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 75 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Manchurian-Noodles---->%d",q,ib);
                    fprintf(fp,"\n %d Manchurian-Noodles---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i71;
                    }

                case 4:
                    i72:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 40 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Maggie---->%d",q,ib);
                    fprintf(fp,"\n %d Maggie---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i72;
                    }

                case 0:
                    goto label;

            }
        }
    case 10:
        i = 69;
        for (;i != 0;)
        {
            printf("\n\n**Beverages**\n\n");
            printf("1. Buuter-Milk                   10\n2. Curd                          20\n3. Coca-Cola                     45\n4. Pepsi                         40\n5. ThumsUp                       45\n6. Sprite                        35\n7. Limca                         35\n8. Maaza                         50\n9. Frooti                        30\n10. Fanta                        35\n11. Monster                     100\n12. Red-Bull                    120\n13. Tea                          15\n14. Coffee                       20\n15. Cold-Coffee                  55");
            printf("\n\nEnter 0 to go back to the main menu");
            printf("\nEnter the serial number of the item you want to enter:");
            scanf("%d",&i);

            switch (i)
            {
                case 1:
                    i73:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 10 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Butter-Milk---->%d",q,ib);
                    fprintf(fp,"\n%d Butter-Milk---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i73;
                    }

                case 2:
                    i74:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 20 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Curd---->%d",q,ib);
                    fprintf(fp,"\n %d Curd---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i74;
                    }

                case 3:
                    i75:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 45 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Coca-Cola---->%d",q,ib);
                    fprintf(fp,"\n %d Coca-Cola---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i75;
                    }

                case 4:
                    i76:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 40 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Pepsi---->%d",q,ib);
                    fprintf(fp,"\n %d Pepsi---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i76;
                    }

                case 5:
                    i77:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 45 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d ThumsUp---->%d",q,ib);
                    fprintf(fp,"\n%d ThumsUp---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i77;
                    }

                case 6:
                    i78:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 35 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Sprite---->%d",q,ib);
                    fprintf(fp,"\n %d Sprite---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i78;
                    }

                case 7:
                    i79:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 35 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Limca---->%d",q,ib);
                    fprintf(fp,"\n %d Limca---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i79;
                    }

                case 8:
                    i80:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 50 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Maaza---->%d",q,ib);
                    fprintf(fp,"\n %d Maaza---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i80;
                    }

                case 9:
                    i81:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 30 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Frooti---->%d",q,ib);
                    fprintf(fp,"\n %d Frooti---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i81;
                    }

                case 10:
                    i82:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 35 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Fanta---->%d",q,ib);
                    fprintf(fp,"\n %d Fanta---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i82;
                    }

                case 11:
                    i83:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 100 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Monster---->%d",q,ib);
                    fprintf(fp,"\n %d Monster---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i83;
                    }

                case 12:
                    i84:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 120 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Red-Bull---->%d",q,ib);
                    fprintf(fp,"\n %d Red-Bull---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i84;
                    }

                case 13:
                    i85:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 15 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Tea---->%d",q,ib);
                    fprintf(fp,"\n %d Tea---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i85;
                    }

                case 14:
                    i86:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 20 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Coffee---->%d",q,ib);
                    fprintf(fp,"\n %d Coffee---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i86;
                    }

                case 15:
                    i87:printf("Enter quantity:");
                    scanf("%d",&q);
                    if (q >= 0)
                    {
                    ib = 55 * q;
                    bill = bill + ib;
                    printf("\nYou ordered %d Cold-Coffee---->%d",q,ib);
                    fprintf(fp,"\n %d Cold-Coffee---->%d",q,ib);
                    break;
                    }
                    else
                    {
                    printf("Enter positive quantity\n");
                    goto i87;
                    }

                case 0:
                    goto label;

            }
        }
    case 0:
        fprintf(fp,"\n\nTOTAL Amount is %d",bill);
        fclose(fp);
        fw = fopen(filename,"a+");
        fp = fopen("order.txt","r");
        printingFinalBill(fp);
        time_t t;
        time(&t);
        char *dataTime = ctime(&t);
        printf("\nCurrent Time : %s",dataTime);
        if(bill>0){
        printf("\nPlease provide your feedback");
        getch();
        fp = fopen("order.txt","r");
        copyFileFunction(fp,fw);
        feedBackMenu(fw);
        dateAndTimeFunction(fw);
        }
    }
    fclose(fp);
    fclose(fw);

}

int main(){
    loginModuleMainFunction();
    return 0;
}
