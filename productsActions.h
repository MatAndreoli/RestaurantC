#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 15

char productsFileName[13] = "products.txt";

struct Product
{
    char name[50];
    int quantity;
    float price;
};

Product products[MAX_ITEMS];

int validateFile1(FILE *file)
{
    return file == NULL;
}

void initializeProducts()
{
    /*
        DISHES
    */
    strcpy(products[0].name, "Pizza");
    products[0].quantity = 6;
    products[0].price = 62;

    strcpy(products[1].name, "Hamburguer");
    products[1].quantity = 20;
    products[1].price = 9.5;

    strcpy(products[2].name, "Feijoada");
    products[2].quantity = 10;
    products[2].price = 55.5;

    strcpy(products[3].name, "Pasta");
    products[3].quantity = 10;
    products[3].price = 15.9;

    strcpy(products[4].name, "Barbecue");
    products[4].quantity = 20;
    products[4].price = 78.9;

    /*
        DRINKS
    */
    strcpy(products[5].name, "Soda");
    products[5].quantity = 30;
    products[5].price = 7.5;

    strcpy(products[6].name, "Juice");
    products[6].quantity = 50;
    products[6].price = 15;

    strcpy(products[7].name, "Coffee");
    products[7].quantity = 25;
    products[7].price = 4.5;

    strcpy(products[8].name, "Beer");
    products[8].quantity = 25;
    products[8].price = 11;

    strcpy(products[9].name, "Water");
    products[9].quantity = 50;
    products[9].price = 4;

    /*
        DESSERTS
    */
    strcpy(products[10].name, "Cake");
    products[10].quantity = 20;
    products[10].price = 8.9;

    strcpy(products[11].name, "Ice_Cream");
    products[11].quantity = 40;
    products[11].price = 7.8;

    strcpy(products[12].name, "Pie");
    products[12].quantity = 15;
    products[12].price = 23.9;

    strcpy(products[13].name, "Chocolate");
    products[13].quantity = 20;
    products[13].price = 5.5;

    strcpy(products[14].name, "Fruits");
    products[14].quantity = 40;
    products[14].price = 6.9;
}

void writeProductsIntoFile(FILE *file) {
    for (int i = 0; i < MAX_ITEMS; ++i)
    {
        fprintf(file, "%s %d %.2f\n", products[i].name, products[i].quantity, products[i].price);
    }
}

void updateProducts() {
    FILE *productsFile = fopen(productsFileName, "w");
    if (validateFile1(productsFile))
    {
        printf("Arquivo não encontrado -> %s", productsFileName);
        return;
    }

    writeProductsIntoFile(productsFile);
    fclose(productsFile);
}

void loadProducts()
{
    FILE *productsFile = fopen(productsFileName, "r");
    initializeProducts();
    if (validateFile1(productsFile))
    {
        printf("O arquivo de produtos não foi encontrado. \n");

        productsFile = fopen(productsFileName, "w");
        if (validateFile1(productsFile))
        {
            printf("Arquivo de produtos não foi criado devido a algum erro.\n");
            return;
        }

        printf("Arquivo de produtos criado com sucesso.\n");

        printf("Carregando os produtos para o arquivo %s", productsFileName);
        for (int i = 0; i < MAX_ITEMS; ++i)
        {
            fprintf(productsFile, "%s %d %.2f\n", products[i].name, products[i].quantity, products[i].price);
        }
    }
    else
    {
        printf("Arquivo encontrado, carregando produtos...\n");
        fclose(productsFile);
        productsFile = fopen(productsFileName, "r");

        for (int i = 0; i < MAX_ITEMS; ++i)
        {
            fscanf(productsFile, "%s %d %f", products[i].name, &products[i].quantity, &products[i].price);
        }
    }
    fclose(productsFile);
}
