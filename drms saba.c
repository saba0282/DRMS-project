#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
void pause();
void userFlood();
void userCyc();
void userFire();
void userEq();

void pause() {
    printf("\nPress Enter to continue...");
    getchar();
}
struct item
{
    char name[100];
    char dis[50];
    char type[10];
    char expiry[30];
    int quantity;
};

void adm();
void login();

void add()
{
    int i, n;
    struct item I[50];
    FILE *f = fopen("items.txt", "a");
    if (!f)
    {
        printf("Cannot open file to write.\n");
        return;
    }

    printf("\t\t\t\t\t\t Add Items\n\n\n");
    printf("\nEnter the number of items you want to add: ");
    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++)
    {
        printf("\nEnter item name: ");
        gets(I[i].name);
        printf("Enter quantity: ");
        scanf("%d", &I[i].quantity);
        getchar();
        printf("Enter expiry date: ");
        gets(I[i].expiry);
        printf("Enter item type: ");
        gets(I[i].type);
        printf("Enter the disaster category: ");
        gets(I[i].dis);
    }

    for (i = 0; i < n; i++)
        fprintf(f, "\n%-25s %-14d %-20s %-15s %-20s\n",
                I[i].name, I[i].quantity, I[i].expiry, I[i].type, I[i].dis);

    fclose(f);
    printf("\n\nItem/s added successfully!\n");
    pause();
    adm();
}

void search()
{
    FILE *f = fopen("items.txt", "r");
    if (!f)
    {
        printf("File not found.\n");
        pause();
        adm();
        return;
    }

    char s[40];
    printf("\t\t\t\t\t\t    Search Bar\n\n\n\n");
    getchar();
    printf("Enter the keyword you want to search: ");
    gets(s);

    for (int i = 0; s[i] != '\0'; i++)
        s[i] = toupper(s[i]);

    int found = 0;
    char line[256];
    printf("\n%-25s %-14s %-20s %-15s %-20s\n\n", "Name", "Quantity", "Expiry Date", "Type", "Disaster");

    while (fgets(line, sizeof(line), f))
    {
        char up[256];
        strcpy(up, line);
        for (int i = 0; up[i]; i++)
            up[i] = toupper(up[i]);
        if (strstr(up, s) != NULL)
        {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo matching items found.\n");

    fclose(f);
    pause();
    adm();
}

void view()
{
    FILE *f = fopen("items.txt", "r");
    if (!f)
    {
        printf("File not found.\n");
        pause();
        adm();
        return;
    }

    char line[200];
    printf("\t\t\t\t\t\t List Of Available Items\n\n\n");
    printf("%-25s %-14s %-20s %-15s %-20s\n\n", "Name", "Quantity", "Expiry Date", "Type", "Disaster");

    while (fgets(line, sizeof(line), f))
        printf("%s", line);

    fclose(f);
    pause();
    adm();
}

void edit()
{
    FILE *fp = fopen("items.txt", "r");
    if (!fp)
    {
        printf("File not found.\n");
        pause();
        adm();
        return;
    }

    struct item items[50];
    int count = 0;
    char namepart[50];

    printf("\t\t\t\t\t\t     Edit Items\n\n\n\n");
    getchar();
    printf("Enter the required keyword to find: ");
    gets(namepart);

    for (int j = 0; namepart[j] != '\0'; j++)
        namepart[j] = toupper(namepart[j]);

    char line[256];
    while (count < 50 && fgets(line, sizeof(line), fp))
    {
        int quantity;
        char name[100], type[10], expiry[30], dis[50];
        int matched = sscanf(line, "%24[^\t\n] %d %19s %14s %19s", name, &quantity, expiry, type, dis);
        if (matched == 5)
        {
            strcpy(items[count].name, name);
            items[count].quantity = quantity;
            strcpy(items[count].expiry, expiry);
            strcpy(items[count].type, type);
            strcpy(items[count].dis, dis);
            count++;
        }
    }
    fclose(fp);

    int index[50], match = 0;
    printf("\n%-25s %-14s %-20s %-15s %-20s\n", "Name", "Quantity", "Expiry Date", "Type", "Disaster");

    for (int i = 0; i < count; i++)
    {
        char up[100];
        strcpy(up, items[i].name);
        for (int j = 0; up[j]; j++)
            up[j] = toupper(up[j]);

        if (strstr(up, namepart))
        {
            printf("%d. %-25s %-13d %-19s %-15s %-20s\n", match + 1,
                   items[i].name, items[i].quantity, items[i].expiry, items[i].type, items[i].dis);
            index[match++] = i;
        }
    }

    if (match == 0)
    {
        printf("\nNo matching items found.\n");
        pause();
        adm();
    }

    int choice;
    printf("\nEnter the number of the record you want to edit: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > match)
    {
        printf("\nInvalid choice. Please try again!\n");
        pause();
        adm();
    }

    int editIndex = index[choice - 1];
    printf("\nEnter new name: ");
    gets(items[editIndex].name);
    printf("Enter new quantity: ");
    scanf("%d", &items[editIndex].quantity);
    getchar();
    printf("Enter new expiry date: ");
    gets(items[editIndex].expiry);
    printf("Enter item type: ");
    gets(items[editIndex].type);
    printf("Enter disaster category: ");
    gets(items[editIndex].dis);

    fp = fopen("items.txt", "w");
    if (!fp)
    {
        printf("Cannot open file to save.\n");
        return;
    }

    for (int i = 0; i < count; i++)
        fprintf(fp, "\n%-25s %-14d %-20s %-15s %-20s\n",
                items[i].name, items[i].quantity, items[i].expiry, items[i].type, items[i].dis);

    fclose(fp);
    printf("\nItem updated successfully.\n");
    pause();
    adm();
}

void donor()
{
    FILE *f = fopen("donations.txt", "r");
    if (!f)
    {
        printf("File not found.\n");
        pause();
        adm();
        return;
    }

    char line[200];
    printf("\t\t\t\t\t\t Information About Donors\n\n\n");

    while (fgets(line, sizeof(line), f))
        printf("%s", line);

    fclose(f);
    pause();
    adm();
}

void reqList()
{
    FILE *f = fopen("requests.txt", "r");
    if (!f)
    {
        printf("File not found.\n");
        pause();
        adm();
        return;
    }

    char line[200];
    printf("\t\t\t\t\t\t  Relief Requests\n\n\n\n");

    while (fgets(line, sizeof(line), f))
        printf("%s", line);

    fclose(f);
    pause();
    adm();
}

void logout()
{
    printf("\t\t\t\t\t\t\tLOGOUT\n\n\n");
    printf("Thank you for using the Disaster Relief Management System.\n\n");
    printf("Logging out safely...\n");
    printf("\nPress Enter to Continue");
    getchar();
    getchar();
    system(CLEAR);
    login();
}


void viewflood()
{
    FILE *flood = fopen("flood.txt","r");
    if(!flood)
    {
        printf("No flood items available.\n");
        pause();
        userFlood();
        return;
    }
    char line[200];
    printf("\t\t\t\t\t\tList Of Available Items\n\n\n");
    printf("\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");
    while(fgets(line,sizeof(line),flood)) printf("%s",line);
    fclose(flood);
    pause();

}

void searchFlood()
{
    FILE *fp = fopen("flood.txt","r");
    if (!fp)
    {
        printf("Could not open flood.txt file.\n");
        pause();
        userFlood();
        return;
    }
    char line[200], searchTerm[50];
    int found = 0;
    printf("\t\t\t\t\t\t Search Relief Items\n\n\n");
    getchar();
    printf("Enter the keyword you want to search: ");
    gets(searchTerm);

    for(int i=0; searchTerm[i]; i++) searchTerm[i] = toupper(searchTerm[i]);
    printf("\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while(fgets(line,sizeof(line),fp))
    {
        char up[200];
        strcpy(up,line);
        for(int i=0; up[i]; i++) up[i] = toupper(up[i]);
        if(strstr(up, searchTerm)!=NULL)
        {
            printf("\n%s\n",line);
            found=1;
        }
    }

    if(!found) printf("\nNo matching items found.\n");
    fclose(fp);
    pause();

}

void requestItemFlood()
{
    struct req
    {
        char name[60];
        int age;
        char num[15];
        char location[60];
        char type[50];
        int quantity;
    } user;
    FILE *fp = fopen("requests.txt","a");
    if(!fp)
    {
        printf("Requests file not found.\n");
        pause();
        userFlood();
        return;
    }

    printf("\t\t\t\t\t\tRelief Items Request Entry\n\n\n");
    getchar();
    printf("Enter your full name: ");
    gets(user.name);
    printf("Enter your age: ");
    scanf("%d",&user.age);
    getchar();
    printf("Enter your contact number: ");
    gets(user.num);
    printf("Enter your location: ");
    gets(user.location);
    printf("Enter the name of the item: ");
    gets(user.type);
    printf("Enter quantity needed: ");
    scanf("%d",&user.quantity);
    getchar();

    fprintf(fp,"\nName:%s\nAge:%d\nContact Number:%s\nLocation:%s\nRequired Item:%s\nRequired Quantity:%d\n\n",
            user.name,user.age,user.num,user.location,user.type,user.quantity);
    fclose(fp);
    printf("\nRequest recorded successfully!\nThanks for your request. Your request is sent for monitoring to the admin!\n");
    pause();

}

void donateFlood()
{
    struct donate
    {
        char name[40];
        char num[15];
        char item[25];
        int quantity;
    } person;
    printf("\t\t\t\t\t\tDonation To DRMS\n\n\n");
    getchar();
    printf("Enter the name of the donor: ");
    gets(person.name);
    printf("Enter contact number: ");
    gets(person.num);
    printf("Enter the name of item to be donated: ");
    gets(person.item);
    printf("Enter the quantity: ");
    scanf("%d",&person.quantity);

    FILE *f=fopen("items.txt","r");
    FILE *temp=fopen("temp.txt","w");
    char line[200];
    int found=0;

    while(fgets(line,sizeof(line),f))
    {
        char itemName[50]= {0}, expiry[20]= {0}, type[20]= {0}, dis[20]= {0};
        int quantityAvailable=0;
        int matched = sscanf(line,"%24[^\t\n] %d %19s %14s %19s", itemName,&quantityAvailable,expiry,type,dis);
        if(matched!=5)
        {
            fputs(line,temp);
            continue;
        }
        int len = strlen(itemName);
        while(len>0 && itemName[len-1]==' ') itemName[--len]='\0';
        if(strcmp(itemName,person.item)==0)
        {
            quantityAvailable+=person.quantity;
            found=1;
        }
        fprintf(temp,"%-25s %-14d %-20s %-15s %-20s\n", itemName, quantityAvailable, expiry, type, dis);
    }
    fclose(f);
    fclose(temp);
    remove("items.txt");
    rename("temp.txt","items.txt");

    if(!found)
    {
        FILE *fnew=fopen("items.txt","a");
        fprintf(fnew,"\n%-25s %-14d %-20s %-15s %-20s\n", person.item, person.quantity, "N/A","N/A","N/A");
        fclose(fnew);
    }

    FILE *don=fopen("donations.txt","a");
    fprintf(don,"Name:%s\nContact Number:%s\nItem donated:%s\nQuantity:%d\n\n", person.name,person.num,person.item,person.quantity);
    fclose(don);
    printf("\nDonation successful. Thanks for your kindness!\n");
    pause();

}

void userFlood()
{
    system(CLEAR);
    int choice;
    printf("\t\t\t\t\t\t Welcome User!\n\n\n");
    printf("\t\t\t\t\t\t\tMain Menu\n\n");
    printf("\t\t\t1. View Relief Items\n");
    printf("\t\t\t2. Search Relief Items\n");
    printf("\t\t\t3. Submit Relief Request\n");
    printf("\t\t\t4. Donate to DRMS\n");
    printf("\t\t\t5. Logout\n\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
    system(CLEAR);
    viewflood();
    break;

    case 2:
        system(CLEAR);
        searchFlood();
        break;
    case 3:
        system(CLEAR);
        requestItemFlood();
        break;
    case 4:
        system(CLEAR);
        donateFlood();
        break;
    case 5:
        system(CLEAR);
        logout();
        break;
    default:
        printf("\nInvalid choice. Please try again!");
        getchar();
        getchar();
        userFlood();
    }
}
void viewcyc()
{
    FILE *cyc = fopen("cyclone.txt","r");
    if (!cyc)
    {
        printf("File not found.\n");
        pause();
        userCyc();
        return;
    }

    char line[200];
    printf("\t\t\t\t\t\tList Of Available Items\n\n\n");
    printf("%-25s %-14s %-20s %-15s %-20s\n\n", "Name","Quantity","Expiry Date","Type","Disaster");

    while(fgets(line,sizeof(line),cyc))
        printf("%s",line);

    fclose(cyc);
    printf("\n\n");
    pause();

}

void searchCyc()
{
    FILE *fp = fopen("cyclone.txt","r");
    if (!fp)
    {
        printf("Could not open cyclone.txt file.\n");
        pause();
        userCyc();
        return;
    }

    char line[200], searchTerm[50];
    int found = 0;
    printf("\t\t\t\t\t\t    Search Bar\n\n\n\n");
    getchar();
    printf("Enter the keyword you want to search: ");
    gets(searchTerm);

    for (int i=0; searchTerm[i]!='\0'; i++)
        searchTerm[i]=toupper(searchTerm[i]);

    printf("\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while(fgets(line,sizeof(line),fp))
    {
        char up[200];
        strcpy(up,line);
        for (int i=0; up[i]; i++)
            up[i]=toupper(up[i]);
        if (strstr(up,searchTerm)!= NULL)
        {
            printf("%s",line);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo matching items found.\n");

    fclose(fp);
    printf("\n\n");
    pause();
    userCyc();
}

void requestItemCyc()
{
    struct req
    {
        char name[60];
        int age;
        char num[15];
        char location[60];
        char type[50];
        int quantity;
    };

    FILE *fp = fopen("requests.txt","a");
    if (!fp)
    {
        printf("Requests file not found.\n");
        pause();
        userCyc();
        return;
    }

    struct req user;
    printf("\t\t\t\t\t\tRelief Items Request Entry\n\n\n");
    getchar();
    printf("Enter your full name: ");
    gets(user.name);
    printf("Enter your age: ");
    scanf("%d",&user.age);
    getchar();
    printf("Enter your contact number: ");
    gets(user.num);
    printf("Enter your location: ");
    gets(user.location);
    printf("Enter the name of the item: ");
    gets(user.type);
    printf("Enter quantity needed: ");
    scanf("%d",&user.quantity);
    getchar();

    fprintf(fp,"Name:%s\nAge:%d\nContact Number:%s\nLocation:%s\nRequired Item:%s\nRequired Quantity:%d\n\n\n",
            user.name,user.age,user.num,user.location,user.type,user.quantity);
    fclose(fp);

    printf("\nRequest recorded successfully!\nYour request is sent for monitoring to the admin!\n");
    pause();

}

void donateCyc()
{
    struct donate
    {
        char name[40];
        char num[15];
        char item[25];
        int quantity;
    };

    printf("\t\t\t\t\t\tDonation To DRMS\n\n\n");
    struct donate person;
    getchar();
    printf("Enter the name of the donor: ");
    gets(person.name);
    printf("Enter contact number: ");
    gets(person.num);
    printf("Enter the name of item to be donated: ");
    gets(person.item);
    printf("Enter the quantity: ");
    scanf("%d",&person.quantity);

    FILE *f = fopen("items.txt","r");
    FILE *temp = fopen("temp.txt","w");
    if (!f || !temp)
    {
        printf("Error opening file.\n");
        pause();
        userCyc();
        return;
    }

    char line[200];
    int found = 0;

    while(fgets(line,sizeof(line),f))
    {
        char itemName[50]= {0}, expiry[20]= {0}, type[20]= {0}, dis[20]= {0};
        int quantityAvailable=0;

        int matched = sscanf(line,"%24[^\t\n] %d %19s %14s %19s",
                             itemName,&quantityAvailable,expiry,type,dis);
        if (matched != 5)
        {
            fputs(line,temp);
            continue;
        }

        int len = strlen(itemName);
        while(len>0 && itemName[len-1]==' ')
            itemName[--len]='\0';

        if(strcmp(itemName, person.item)==0)
        {
            quantityAvailable += person.quantity;
            found = 1;
        }

        fprintf(temp,"%-25s %-14d %-20s %-15s %-20s\n",
                itemName,quantityAvailable,expiry,type,dis);
    }

    fclose(f);
    fclose(temp);

    remove("items.txt");
    rename("temp.txt","items.txt");

    if(!found)
    {
        FILE *fnew = fopen("items.txt","a");
        fprintf(fnew,"\n%-25s %-14d %-20s %-15s %-20s\n",
                person.item, person.quantity,"N/A","N/A","N/A");
        fclose(fnew);
    }

    FILE *don = fopen("donations.txt","a");
    fprintf(don,"Name:%s\nContact Number:%s\nName of the item donated:%s\nQuantity of the item donated:%d\n\n\n",
            person.name, person.num, person.item, person.quantity);
    fclose(don);

    printf("\nDonation successful. Thanks for your kindness!\n");
    getchar();
    pause();

}

void userCyc()
{
    system(CLEAR);
    int choice;
    printf("\t\t\t\t\t\t      Welcome User!\n\n\n");
    printf("\t\t\t\t\t\t\tMain Menu\n\n\n");
    printf("\t\t\t\t\t\t1.View Relief Items\n");
    printf("\t\t\t\t\t\t2.Search Relief Items\n");
    printf("\t\t\t\t\t\t3.Submit Relief Request\n");
    printf("\t\t\t\t\t\t4.Donate to DRMS\n");
    printf("\t\t\t\t\t\t5.Logout\n\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        system(CLEAR);
        viewcyc();
        break;
    case 2:
        system(CLEAR);
        searchCyc();
        break;
    case 3:
        system(CLEAR);
        requestItemCyc();
        break;
    case 4:
        system(CLEAR);
        donateCyc();
        break;
    case 5:
        system(CLEAR);
        logout();
        break;
    default:
        printf("\nInvalid choice. Please try again!\n");
        getchar();
        getchar();
        userCyc();
    }
}
void viewFire()
{
    FILE *fire;
    char line[200];
    fire = fopen("fire.txt","r");
    if (!fire)
    {
        printf("No fire relief items found.\n");
        pause();
        userFire();
        return;
    }

    printf("\t\t\t\t\t\tList Of Available Items\n\n\n");
    printf("\n\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while(fgets(line,sizeof(line),fire))
    {
        printf("%s",line);
    }

    printf("\n\n");
    fclose(fire);
    pause();
    getchar();
    userFire();
}

void searchFire()
{
    FILE *fp = fopen("fire.txt","r");
    if (!fp)
    {
        printf("Could not open fire.txt file.\n");
        pause();
        userFire();
        return;
    }

    char line[200];
    int found = 0;
    char searchTerm[50];

    getchar();
    printf("\t\t\t\t\t\tSearch Relief Items\n\n\n");
    printf("Enter keyword to search: ");
    gets(searchTerm);

    for (int i = 0; searchTerm[i]; i++)
        searchTerm[i] = toupper(searchTerm[i]);

    printf("\n\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while (fgets(line,sizeof(line),fp))
    {
        char up[200];
        strcpy(up,line);
        for (int i = 0; up[i]; i++)
            up[i] = toupper(up[i]);

        if (strstr(up,searchTerm) != NULL)
        {
            printf("%s",line);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo matching items found.\n");

    fclose(fp);
    pause();
    userFire();
}

void requestItemFire()
{
    struct req
    {
        char name[60];
        int age;
        char num[15];
        char location[60];
        char type[50];
        int quantity;
    };

    FILE *fp = fopen("requests.txt","a");
    if (!fp)
    {
        printf("Requests file not found.\n");
        pause();
        userFire();
        return;
    }

    printf("\t\t\t\t\t\tRelief Items Request Entry\n\n\n");
    struct req user;
    getchar();
    printf("Enter your full name: ");
    gets(user.name);
    printf("Enter your age: ");
    scanf("%d",&user.age);
    getchar();
    printf("Enter your contact number: ");
    gets(user.num);
    printf("Enter your location: ");
    gets(user.location);
    printf("Enter the name of the item: ");
    gets(user.type);
    printf("Enter quantity needed: ");
    scanf("%d",&user.quantity);
    getchar();

    fprintf(fp,"Name:%s\nAge:%d\nContact Number:%s\nLocation:%s\nRequired Item:%s\nRequired Quantity:%d\n\n\n",
            user.name,user.age,user.num,user.location,user.type,user.quantity);

    fclose(fp);
    printf("\nRequest recorded successfully! Your request has been sent to admin.\n");
    pause();
    userFire();
}

void donateFire()
{
    struct donate
    {
        char name[40];
        char num[15];
        char item[25];
        int quantity;
    };

    printf("\t\t\t\t\t\tDonation To DRMS\n\n\n");
    struct donate person;
    getchar();
    printf("Enter donor name: ");
    gets(person.name);
    printf("Enter contact number: ");
    gets(person.num);
    printf("Enter name of item to be donated: ");
    gets(person.item);
    printf("Enter quantity: ");
    scanf("%d",&person.quantity);

    FILE *f = fopen("items.txt","r");
    FILE *temp = fopen("temp.txt","w");
    char line[200];
    int found = 0;

    while(fgets(line,sizeof(line),f))
    {
        char itemName[50]= {0}, expiry[20]= {0}, type[20]= {0}, dis[20]= {0};
        int quantityAvailable=0;
        int matched = sscanf(line,"%24[^\t\n] %d %19s %14s %19s",itemName,&quantityAvailable,expiry,type,dis);

        if(matched != 5)
        {
            fputs(line,temp);
            continue;
        }

        int len = strlen(itemName);
        while(len > 0 && itemName[len-1]==' ')
            itemName[--len]='\0';

        if(strcmp(itemName,person.item)==0)
        {
            quantityAvailable += person.quantity;
            found = 1;
        }

        fprintf(temp,"%-25s %-14d %-20s %-15s %-20s\n",itemName,quantityAvailable,expiry,type,dis);
    }

    fclose(f);
    fclose(temp);

    remove("items.txt");
    rename("temp.txt","items.txt");

    if(!found)
    {
        FILE *fnew = fopen("items.txt","a");
        fprintf(fnew,"%-25s %-14d %-20s %-15s %-20s\n", person.item, person.quantity, "N/A", "N/A", "N/A");
        fclose(fnew);
    }

    FILE *don = fopen("donations.txt","a");
    fprintf(don,"Name:%s\nContact Number:%s\nName of the item donated:%s\nQuantity of the item donated:%d\n\n\n",
            person.name,person.num,person.item,person.quantity);
    fclose(don);

    printf("\nDonation successful. Thanks for your kindness!\n");
    getchar();
    pause();
    userFire();
}

void userFire()
{
    system(CLEAR);
    int choice;
    printf("\t\t\t\t\t\t      Welcome User!\n\n\n");
    printf("\t\t\t\t\t\t\tMain Menu\n\n\n");
    printf("\t\t\t\t\t\t1.View Relief Items\n\n");
    printf("\t\t\t\t\t\t2.Search Relief Items\n\n");
    printf("\t\t\t\t\t\t3.Submit Relief Request\n\n");
    printf("\t\t\t\t\t\t4.Donate to DRMS\n\n");
    printf("\t\t\t\t\t\t5.Logout\n\n\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        system(CLEAR);
        viewFire();
        break;
    case 2:
        system(CLEAR);
        searchFire();
        break;
    case 3:
        system(CLEAR);
        requestItemFire();
        break;
    case 4:
        system(CLEAR);
        donateFire();
        break;
    case 5:
        system(CLEAR);
        logout();
        break;
    default:
        printf("\nInvalid choice. Please try again!");
        getchar();
        getchar();
        userFire();
    }
}
void viewEq()
{
    FILE *eq;
    char line[200];
    eq = fopen("earthquake.txt", "r");
    if (!eq)
    {
        printf("No earthquake relief items found.\n");
        pause();
        userEq();
        return;
    }

    printf("\t\t\t\t\t\tList Of Available Items\n\n\n");
    printf("\n\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while(fgets(line,sizeof(line),eq))
    {
        printf("%s",line);
    }
    printf("\n\n");
    fclose(eq);
    pause();
    getchar();
    userEq();
}

void searchEq()
{
    FILE *fp = fopen("earthquake.txt","r");
    if (!fp)
    {
        printf("Could not open earthquake.txt file.\n");
        pause();
        userEq();
        return;
    }

    char line[200];
    int found = 0;
    char searchTerm[50];

    getchar();
    printf("\t\t\t\t\t\tSearch Relief Items\n\n\n");
    printf("Enter keyword to search: ");
    gets(searchTerm);

    for (int i = 0; searchTerm[i]; i++)
        searchTerm[i] = toupper(searchTerm[i]);

    printf("\n\n%-25s %-14s %-20s %-15s %-20s\n\n","Name","Quantity","Expiry Date","Type","Disaster");

    while (fgets(line,sizeof(line),fp))
    {
        char up[200];
        strcpy(up,line);
        for (int i = 0; up[i]; i++)
            up[i] = toupper(up[i]);

        if (strstr(up,searchTerm) != NULL)
        {
            printf("%s",line);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo matching items found.\n");

    fclose(fp);
    pause();
    userEq();
}

void requestItemEq()
{
    struct req
    {
        char name[60];
        int age;
        char num[15];
        char location[60];
        char type[50];
        int quantity;
    };

    FILE *fp = fopen("requests.txt","a");
    if (!fp)
    {
        printf("Requests file not found.\n");
        pause();
        userEq();
        return;
    }

    printf("\t\t\t\t\t\tRelief Items Request Entry\n\n\n");
    struct req user;
    getchar();
    printf("Enter your full name: ");
    gets(user.name);
    printf("Enter your age: ");
    scanf("%d",&user.age);
    getchar();
    printf("Enter your contact number: ");
    gets(user.num);
    printf("Enter your location: ");
    gets(user.location);
    printf("Enter the name of the item: ");
    gets(user.type);
    printf("Enter quantity needed: ");
    scanf("%d",&user.quantity);
    getchar();

    fprintf(fp,"Name:%s\nAge:%d\nContact Number:%s\nLocation:%s\nRequired Item:%s\nRequired Quantity:%d\n\n\n",
            user.name,user.age,user.num,user.location,user.type,user.quantity);

    fclose(fp);
    printf("\nRequest recorded successfully! Your request has been sent to admin.\n");
    pause();
    userEq();
}

void donateEq()
{
    struct donate
    {
        char name[40];
        char num[15];
        char item[25];
        int quantity;
    };

    printf("\t\t\t\t\t\tDonation To DRMS\n\n\n");
    struct donate person;
    getchar();
    printf("Enter donor name: ");
    gets(person.name);
    printf("Enter contact number: ");
    gets(person.num);
    printf("Enter name of item to be donated: ");
    gets(person.item);
    printf("Enter quantity: ");
    scanf("%d",&person.quantity);

    FILE *f = fopen("items.txt","r");
    FILE *temp = fopen("temp.txt","w");
    char line[200];
    int found = 0;

    while(fgets(line,sizeof(line),f))
    {
        char itemName[50]= {0}, expiry[20]= {0}, type[20]= {0}, dis[20]= {0};
        int quantityAvailable=0;
        int matched = sscanf(line,"%24[^\t\n] %d %19s %14s %19s",itemName,&quantityAvailable,expiry,type,dis);

        if(matched != 5)
        {
            fputs(line,temp);
            continue;
        }

        int len = strlen(itemName);
        while(len > 0 && itemName[len-1]==' ')
            itemName[--len]='\0';

        if(strcmp(itemName,person.item)==0)
        {
            quantityAvailable += person.quantity;
            found = 1;
        }

        fprintf(temp,"%-25s %-14d %-20s %-15s %-20s\n",itemName,quantityAvailable,expiry,type,dis);
    }

    fclose(f);
    fclose(temp);

    remove("items.txt");
    rename("temp.txt","items.txt");

    if(!found)
    {
        FILE *fnew = fopen("items.txt","a");
        fprintf(fnew,"%-25s %-14d %-20s %-15s %-20s\n", person.item, person.quantity, "N/A", "N/A", "N/A");
        fclose(fnew);
    }

    FILE *don = fopen("donations.txt","a");
    fprintf(don,"Name:%s\nContact Number:%s\nName of the item donated:%s\nQuantity of the item donated:%d\n\n\n",
            person.name,person.num,person.item,person.quantity);
    fclose(don);

    printf("\nDonation successful. Thanks for your kindness!\n");
    getchar();
    pause();
    userEq();
}

void userEq()
{
    system(CLEAR);
    int choice;
    printf("\t\t\t\t\t\t      Welcome User!\n\n\n");
    printf("\t\t\t\t\t\t\tMain Menu\n\n\n");
    printf("\t\t\t\t\t\t1.View Relief Items\n\n");
    printf("\t\t\t\t\t\t2.Search Relief Items\n\n");
    printf("\t\t\t\t\t\t3.Submit Relief Request\n\n");
    printf("\t\t\t\t\t\t4.Donate to DRMS\n\n");
    printf("\t\t\t\t\t\t5.Logout\n\n\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        system(CLEAR);
        viewEq();
        break;
    case 2:
        system(CLEAR);
        searchEq();
        break;
    case 3:
        system(CLEAR);
        requestItemEq();
        break;
    case 4:
        system(CLEAR);
        donateEq();
        break;
    case 5:
        system(CLEAR);
        logout();
        break;
    default:
        printf("\nInvalid choice. Please try again!");
        getchar();
        getchar();
        userEq();
    }
}
void chooseDis()
{
    system(CLEAR);
    int disasterChoice;
    printf("\t\t\t\t\t\tChoose Disaster Type\n\n\n\n");
    printf("\t\t\t\t\t 1.Flood\n\n");
    printf("\t\t\t\t\t 2.Cyclone\n\n");
    printf("\t\t\t\t\t 3.Fire\n\n");
    printf("\t\t\t\t\t 4.Earthquake\n");
    printf("\n\n\t\t\t\t\t\t Enter your choice:");
    scanf("%d",&disasterChoice);
    getchar();

    switch (disasterChoice)
    {
    case 1:
        userFlood();
        break;
    case 2:
        userCyc();
        break;
    case 3:
        userFire();
        break;
    case 4:
        userEq();
        break;
    default:
        printf("\n\t\t\t\t\t Invalid choice. Please choose again!\n");
        getchar();
        chooseDis();
    }
}

void adm()
{
    system(CLEAR);
    int choice;
    printf("\t\t\t\t\t\t       Welcome Admin!\n\n\n");
    printf("\t\t\t\t\t\t\t Main Menu\n\n\n");
    printf("\t\t\t\t\t1.View Relief Items\n");
    printf("\t\t\t\t\t2.Search Relief Items\n");
    printf("\t\t\t\t\t3.Edit Items\n");
    printf("\t\t\t\t\t4.Add New Items\n");
    printf("\t\t\t\t\t5.View User Requests for Aid\n");
    printf("\t\t\t\t\t6.Information Related To Donors\n");
    printf("\t\t\t\t\t7.Logout\n");
    printf("\n\n\t\t\t\t\tEnter your choice: ");
    scanf("%d",&choice);
    getchar();

    switch(choice)
    {
    case 1:
        system(CLEAR);
        view();
        break;
    case 2:
        system(CLEAR);
        search();
        break;
    case 3:
        system(CLEAR);
        edit();
        break;
    case 4:
        system(CLEAR);
        add();
        break;
    case 5:
        system(CLEAR);
        reqList();
        break;
    case 6:
        system(CLEAR);
        donor();
        break;
    case 7:
        system(CLEAR);
        logout();
        break;
    default:
        printf("\n\n\t\t\t\t\tInvalid choice. Please try again!");
        getchar();
        adm();
    }
}

void login()
{
    char name[100];
    char pass[30];

    while (1)
    {
        printf("\t\t\t\t\t   ||Disaster Relief Management System||\n\n\n");
        printf("\t\t\t\t\t\t\t LOGIN \n\n\n");
        printf("\t\t\t\t\tEnter ID name: ");
        gets(name);
        printf("\n\t\t\t\t\tEnter ID password: ");
        gets(pass);

        if (strcmp(name,"DRMS")==0 && strcmp(pass,"!@#$%")==0)
        {
            adm();  // Admin login
            break;
        }
        else if (strcmp(pass,"13579")==0)
        {
            chooseDis();  // User login
            break;
        }
        else
        {
            printf("\n\n\n\t\t\t\t\tLogin Invalid. Please Try Again!");
            getchar();
            system(CLEAR);
        }
    }
}
int main()
{
    login();
    return 0;
}



