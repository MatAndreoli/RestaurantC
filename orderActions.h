#include <stdio.h>
#include <string.h>
#include <time.h>

char ordersFileName[13] = "orders.txt";
char ordersHistoryFileName[20] = "ordersHistory.txt";

#define MAX_ORDERS 100

struct Order
{
    char ticket[10];
    char date[20];
    char time[20];
    char description[100];
    int quantity;
    float total;
};

Order orders[MAX_ORDERS];
Order order;
int totalOrders = 0;

int validateFile(FILE *file)
{
    return file == NULL;
}

void saveOrder()
{
    int newTotalHistory = 0;
    FILE *ordersFile = fopen(ordersFileName, "w");
    FILE *ordersHistoryFile = fopen(ordersHistoryFileName, "r");
    if (validateFile(ordersFile))
    {
        printf("Arquivo não encontrado -> %s", ordersFileName);
        return;
    }

    if (validateFile(ordersHistoryFile))
    {
        ordersHistoryFile = fopen(ordersHistoryFileName, "w");
        fprintf(ordersHistoryFile, "%d", totalOrders);
        newTotalHistory = totalOrders;
    }
    else
    {
        ordersHistoryFile = fopen(ordersHistoryFileName, "r+");
        if (totalOrders > 1)
        {
            fprintf(ordersHistoryFile, "%d", totalOrders);
            newTotalHistory = totalOrders;
        }
        else
        {
            char totalHistory;
            fscanf(ordersHistoryFile, "%c", &totalHistory);
            newTotalHistory = totalOrders + totalHistory;
            fprintf(ordersHistoryFile, "%d", newTotalHistory);
        }
    }

    for (int i = 0; i < newTotalHistory; i++)
    {
        fprintf(ordersFile, "%s %s %s %s %d %.2f\n", orders[i].ticket, orders[i].date, orders[i].time, orders[i].description, orders[i].quantity, orders[i].total);
    }

    fclose(ordersFile);
    fclose(ordersHistoryFile);
}

void makeOrder(int productNumber, int quantity, int ticketType)
{
    printf("Total orders: %d", totalOrders);
    if (productNumber < 1 || productNumber > MAX_ITEMS)
    {
        printf("Produto inválido...");
        return;
    }
    int productIndex = productNumber - 1;

    if (products[productIndex].quantity <= 0 || products[productIndex].quantity < quantity)
    {
        printf("Sem estoque do produto escolhido...");
        return;
    }

    products[productIndex].quantity = products[productIndex].quantity - quantity;

    Order order;
    strcpy(order.description, products[productIndex].name);
    order.quantity = quantity;
    order.total = quantity * products[productIndex].price;
    sprintf(order.ticket, "%c%d%d", (ticketType == 1 ? 'N' : 'P'), totalOrders / 100, totalOrders % 100);

    time_t agora = time(NULL);
    struct tm *dateTime = localtime(&agora);
    strftime(order.date, 20, "%Y-%m-%d", dateTime);
    strftime(order.time, 20, "%H:%M:%S", dateTime);

    orders[totalOrders] = order;
    totalOrders++;
    printf("Total orders: %d", totalOrders);

    printf("Pedido registrado.\n");
    printf("Detalhes do pedido feito: \n");
    printf("Senha: %s | Pedido: %s | Quantidade: %d | Valor Total: R$%.2f\n", order.ticket, order.description, order.quantity, order.total);

    updateProducts();
    saveOrder();
}
