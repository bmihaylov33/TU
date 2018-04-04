#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp, *fpt;
    if((fp=fopen("clients.dat", "rb"))==NULL)
    {
        printf("Error opening file for write!\n");
        exit(1);
    }

    if((fpt=fopen("temp.dat", "wb"))==NULL)
    {
        printf("Error opening file for write!\n");
        exit(1);
    }

    int clientID, purchasedItem;
    char clientName[50];
    char clientAddress[50];
    double totalSum;
    char c, currentChar;
    int i = 0;

    int passedClientID, passedItemID;
    double passedItemPrice;
    printf("Enter ClientID: ");
    scanf("%d", &passedClientID);
    printf("Enter ItemID: ");
    scanf("%d", &passedItemID);
    printf("Enter ItemPrice: ");
    scanf("%lf", &passedItemPrice);


    while(!feof(fp))
    {
        if(ferror(fp))
        {
            printf("Error reading fp!\n");
            exit(1);
        }
        if(fread(&clientID, sizeof(int), 1, fp)!=1)
        {
            break;
            printf("Error reading clientID\n");
        }
        if(fread(&c, sizeof(char), 1, fp)!=1)
        {
            printf("Error reading |\n");
            exit(1);
        }

        do{
            if(fread(&currentChar, sizeof(char), 1, fp)!=1)
            {
                printf("Error reading currentChar for clientName\n");
                exit(1);
            }
            clientName[i++] = currentChar;
        }while(currentChar != '|');
        clientName[i-1] = '\0';
        i = 0;

        do{
            if(fread(&currentChar, sizeof(char), 1, fp)!=1)
            {
                printf("Error reading currentChar for clientAddress\n");
                exit(1);
            }
            clientAddress[i++] = currentChar;
        }while(currentChar != '|');
        clientAddress[i-1] = '\0';
        i = 0;

        if(fread(&purchasedItem, sizeof(int), 1, fp)!=1)
        {
            printf("Error reading purchasedItem\n");
            exit(1);
        }
        if(fread(&c, sizeof(char), 1, fp)!=1)
        {
            printf("Error reading |\n");
            exit(1);
        }
        if(fread(&totalSum, sizeof(double), 1, fp)!=1)
        {
            printf("Error reading totalSum\n");
            exit(1);
        }
        if(fread(&c, sizeof(char), 1, fp)!=1)
        {
            printf("Error reading |\n");
            exit(1);
        }

        if(clientID == passedClientID)
        {
            if(totalSum > 150)
                passedItemPrice *= 0.95;
            else if(totalSum > 250)
                passedItemPrice *= 0.90;
            totalSum += passedItemPrice;
            printf("Current price of %d is: %g totalSum: %g\n", passedItemID, passedItemPrice, totalSum);
        }

        //printf("%d | %s | %s | %d | %g |\n", clientID, clientName, clientAddress, purchasedItem, totalSum);

        if(ferror(fpt))
        {
            printf("Error writing fpT!\n");
            exit(1);
        }
        if(fwrite(&clientID, sizeof(int), 1, fpt)!=1)
        {
            printf("Error writing clientID\n");
            exit(1);
        }
        if(fwrite(&c, sizeof(char), 1, fpt)!=1)
        {
            printf("Error writing |\n");
            exit(1);
        }
        if(fwrite(clientName, sizeof(char), strlen(clientName), fpt)!=strlen(clientName))
        {
            printf("Error writing clientName\n");
            exit(1);
        }
        if(fwrite(&c, sizeof(char), 1, fpt)!=1)
        {
            printf("Error writing |\n");
            exit(1);
        }
        if(fwrite(clientAddress, sizeof(char), strlen(clientAddress), fpt)!=strlen(clientAddress))
        {
            printf("Error writing clientAddress\n");
            exit(1);
        }
        if(fwrite(&c, sizeof(char), 1, fpt)!=1)
        {
            printf("Error writing |\n");
            exit(1);
        }
        if(fwrite(&passedItemID, sizeof(int), 1, fpt)!=1)
        {
            printf("Error writing passedItemID\n");
            exit(1);
        }
        if(fwrite(&c, sizeof(char), 1, fpt)!=1)
        {
            printf("Error writing |\n");
            exit(1);
        }
        if(fwrite(&totalSum, sizeof(double), 1, fpt)!=1)
        {
            printf("Error writing totalSum\n");
            exit(1);
        }
        if(fwrite(&c, sizeof(char), 1, fpt)!=1)
        {
            printf("Error writing |\n");
            exit(1);
        }
    }
    fclose(fpt);
    fclose(fp);
    //remove(clients.dat);                  deletes the old input file
    //rename(temp.dat, clients.dat);        renames the new temp.dat do clients.dat
    return 0;
}
