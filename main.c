#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NL printf("\n")

typedef struct Product
{
    char name[31];
    int id;
    char expireDate[11];
    double price;
}Product;
Product* products;
int count=0;
Product* fromBin;

Product* higherPriceProducts;
int higherPriceCount=0;

void addProduct(Product p)
{
    products=(Product*)realloc(products,sizeof(Product)*(1+count));
    if(products==NULL)
    {
        printf("Error reallocating memory!");
        exit(1);
    }
    strcpy(products[count].name,p.name);
    products[count].id=p.id;
    strcpy(products[count].expireDate,p.expireDate);
    products[count].price=p.price;
    count++;

    FILE* fp;
    fp=fopen("in.bin","ab+");
    if(fp==NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
    if(fwrite(&p,sizeof(Product),1,fp)!=1)
    {
        printf("Error writing to file!");
        exit(1);
    }
    fclose(fp);
}

void ReadFromBinary()
{
    FILE* fp;
    fp=fopen("in.bin","rb");
    if(fp==NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
    if(fread(fromBin,sizeof(Product),count,fp)!=count)
    {
        printf("Error reading from file!");
        exit(1);
    }
    fclose(fp);
}

void printProduct(Product p)
{
    printf("Name -> %s\n",p.name);
    printf("ID -> %d\n",p.id);
    printf("ExpDate -> %s\n",p.expireDate);
    printf("Price -> %g\n",p.price);
    printf("\n");
}

//task2
Product* returnByHigherPrice(Product* prods,int prodsCount,double price)
{
    for(int i=0;i<prodsCount;i++)
    {
        if(prods[i].price>price)
        {
            higherPriceProducts=(Product*)realloc(higherPriceProducts,sizeof(Product)*(1+higherPriceCount));
            strcpy(higherPriceProducts[higherPriceCount].name,prods[i].name);
            higherPriceProducts[higherPriceCount].id=prods[i].id;
            strcpy(higherPriceProducts[higherPriceCount].expireDate,prods[i].expireDate);
            higherPriceProducts[higherPriceCount].price=prods[i].price;
            higherPriceCount++;
        }
    }
    return higherPriceProducts;
}

//task3
void writeToTxtDataFromBin()
{
    FILE* fp;
    fp=fopen("outTxt.txt","w");
    if(fp==NULL)
    {
        printf("Error opening txt file!");
        exit(1);
    }
    for(int i=0;i<count;i++)
    {
        fprintf(fp,"Name -> %s\n",fromBin[i].name);
        fprintf(fp,"ID -> %d\n",fromBin[i].id);
        fprintf(fp,"Expire Date -> %s\n",fromBin[i].expireDate);
        fprintf(fp,"Price -> %g\n",fromBin[i].price);
    }
    fclose(fp);
}


int main()
{
    Product bread;
    strcpy(bread.name,"Bread");
    bread.id=101;
    strcpy(bread.expireDate,"2022.05.27");
    bread.price=1;
    addProduct(bread);

    Product oil;
    strcpy(oil.name,"Oil");
    oil.id=102;
    strcpy(oil.expireDate,"2021.11.27");
    oil.price=4;
    addProduct(oil);

    Product cheese;
    strcpy(cheese.name,"Cheese");
    cheese.id=103;
    strcpy(cheese.expireDate,"2022.03.04");
    cheese.price=12;
    addProduct(cheese);

    fromBin=(Product*)malloc(sizeof(Product)*count);
    ReadFromBinary();

    writeToTxtDataFromBin();

    higherPriceProducts=returnByHigherPrice(products,count,3);

    free(products);
    free(fromBin);
    free(higherPriceProducts);
    return 0;
}
