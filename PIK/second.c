#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int length_of_brand, length_of_model, number;
    char brand[50];
    char model[50];
    double price;

    int count=0;
    double averageSum=0, averagePrice=0;


    FILE *fp, *fpb;
    if((fp=fopen("phones.bin", "rb"))==NULL)
    {
        printf("Error opening file for read!\n");
        exit(1);
    }

    while(!feof(fp))
    {
        if(ferror(fp))
        {
            printf("Error reading file!\n");
            exit(1);
        }
        if(fread(&length_of_brand, sizeof(int), 1, fp)!=1)
            break;
        if(fread(brand, sizeof(char), length_of_brand, fp)!=length_of_brand)
        {
            printf("Error reading brand!\n");
            exit(1);
        }
        brand[length_of_brand] = '\0';
        if(fread(&length_of_model, sizeof(int), 1, fp)!=1)
        {
            printf("Error reading length_of_model!\n");
            exit(1);
        }
        if(fread(model, sizeof(char), length_of_model, fp)!=length_of_model)
        {
            printf("Error reading model!\n");
            exit(1);
        }
        model[length_of_model] = '\0';
        if(fread(&number, sizeof(int), 1, fp)!=1)
        {
            printf("Error reading number!\n");
            exit(1);
        }
        if(fread(&price, sizeof(double), 1, fp)!=1)
        {
            printf("Error reading price!\n");
            exit(1);
        }
        averageSum+=price;
        count++;
    }
    averagePrice = averageSum/count;
    rewind(fp);

    if((fpb=fopen("sony.bin", "wb"))==NULL)
    {
        printf("Can't open file for write!\n");
        exit(1);
    }

    while(!feof(fp))
    {
        if(ferror(fp))
        {
            printf("Error reading file!\n");
            exit(1);
        }
        if(fread(&length_of_brand, sizeof(int), 1, fp)!=1)
            break;
        if(fread(brand, sizeof(char), length_of_brand, fp)!=length_of_brand)
        {
            printf("Error reading brand!\n");
            exit(1);
        }
        brand[length_of_brand] = '\0';
        if(fread(&length_of_model, sizeof(int), 1, fp)!=1)
        {
            printf("Error reading length_of_model!\n");
            exit(1);
        }
        if(fread(model, sizeof(char), length_of_model, fp)!=length_of_model)
        {
            printf("Error reading model!\n");
            exit(1);
        }
        model[length_of_model] = '\0';
        if(fread(&number, sizeof(int), 1, fp)!=1)
        {
            printf("Error reading number!\n");
            exit(1);
        }
        if(fread(&price, sizeof(double), 1, fp)!=1)
        {
            printf("Error reading price!\n");
            exit(1);
        }

        if(!strcmp(brand, "Sony") && price > averagePrice)
        {
            if(ferror(fpb))
            {
                printf("Error writing to file!\n");
                exit(1);
            }
            if(fwrite(&price, sizeof(double), 1, fpb)!=1)
            {
                printf("Error writing price!\n");
                exit(1);
            }
            if(fwrite(&number, sizeof(int), 1, fpb)!=1)
            {
                printf("Error writing number!\n");
                exit(1);
            }
            if(fwrite(&length_of_brand, sizeof(int), 1, fpb)!=1)
            {
                printf("Error writing length_of_brand!\n");
                exit(1);
            }
            if(fwrite(brand, sizeof(char), length_of_brand, fpb)!=length_of_brand)
            {
                printf("Error writing brand!\n");
                exit(1);
            }
            if(fwrite(&length_of_model, sizeof(int), 1, fpb)!=1)
            {
                printf("Error writing length_of_model!\n");
                exit(1);
            }
            if(fwrite(model, sizeof(char), length_of_model, fpb)!=length_of_model)
            {
                printf("Error writing model!\n");
                exit(1);
            }
        }
    }
    fclose(fpb);
    fclose(fp);
    return 0;
}
