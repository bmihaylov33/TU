#include <stdio.h>
#include <string.h>

int main() {
    FILE* fileptr=fopen("books","wb");
    if(!fileptr) {
        printf("I/O error\n");
        return 1;
    }
    char id[20];
    char sizeID;
    char size_of_title;
    char size_of_author;
    char size_of_press;
    char title[80];
    char author[50];
    double price;
    int year;
    char press[80];
    int COUNT;
    printf("Enter EOF to stop:\n");
    while(1) {
        printf("Enter id: ");
        if(scanf("%s",id)!=1)
            break;
        printf("Enter title: ");
        if(scanf("%s",title)!=1)
            break;
        printf("Enter author: ");
        if(scanf("%s",author)!=1)
            break;
        printf("Enter price: ");
        if(scanf("%lf",&price)!=1)
            break;
        printf("Enter year: ");
        if(scanf("%d",&year)!=1)
            break;
        printf("Enter press: ");
        if(scanf("%s",press)!=1)
            break;
        sizeID = strlen(id);
        size_of_title = strlen(title);
        size_of_author = strlen(author);
        size_of_press = strlen(press);
        fwrite(&sizeID,sizeof(char),1,fileptr);
        fwrite(id,sizeof(char),sizeID,fileptr);
        fwrite(&size_of_title,sizeof(char),1,fileptr);
        fwrite(title,sizeof(char),size_of_title,fileptr);
        fwrite(&size_of_author,sizeof(char),1,fileptr);
        fwrite(author,sizeof(char),size_of_author,fileptr);
        fwrite(&price,sizeof(double),1,fileptr);
        fwrite(&year,sizeof(int),1,fileptr);
        fwrite(&size_of_press,sizeof(char),1,fileptr);
        fwrite(press,sizeof(char),size_of_press,fileptr);
    }
}
