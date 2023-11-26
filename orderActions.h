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

int totalOrders = 0, notCalledOrders = 0;

int validateFile(FILE *file)
{
    return file == NULL;
}

void loadOrders()
{
    FILE *ordersFile = fopen(ordersFileName, "r");
    FILE *ordersHistoryFile = fopen(ordersHistoryFileName, "r");
    bool verifyHistory = true;
    char ticketHistory[10];
    char ticketHistories[10][10];
    Order order;
    Order readOrders[MAX_ORDERS];
    int alreadyGone[10];
    int i = 0, k = 0, m = 0;

    if (validateFile(ordersFile))
    {
        printf("Arquivo não encontrado  -> %s", ordersFileName);
        return;
    }

    if (validateFile(ordersHistoryFile))
    {
        printf("Arquivo não encontrado  -> %s", ordersHistoryFileName);
        verifyHistory = false;
    }

    while (fscanf(ordersFile, "%s %s %s %s %d %f", order.ticket, order.date, order.time, order.description, &order.quantity, &order.total) != EOF)
    {
        readOrders[m] = order;
        m++;
    }

    totalOrders = m;

    if (verifyHistory)
    {
        while (fscanf(ordersHistoryFile, "%s", ticketHistory) != EOF)
        {
            strcpy(ticketHistories[i], ticketHistory);
            i++;
        }

        for (int z = 0; z < m; z++)
        {
            bool called;
            for (int y = 0; y < i; y++)
            {
                called = true;
                if (strcmp(ticketHistories[y], readOrders[z].ticket) != 0)
                {
                    called = false;
                }
                else
                {
                    break;
                }
            }

            if (!called)
            {
                orders[z] = readOrders[z];
                notCalledOrders++;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        orders[i] = readOrders[i];
    }

    fclose(ordersFile);
}

void showOrders()
{
    FILE *ordersFile = fopen(ordersFileName, "r");
    if (validateFile(ordersFile))
    {
        printf("Nenhum pedido foi feito ainda...\n");
        return;
    }
    Order order;
    printf("%-10s%-11s%-10s%-20s%-15s%-10s\n", "Senha", "Data", "Hora", "Descrição", "Quantidade", "Valor Total");
    while (fscanf(ordersFile, "%s %s %s %s %d %f", order.ticket, order.date, order.time, order.description, &order.quantity, &order.total) != EOF)
    {
        printf("%-10s%s %-10s%-20s%-15dR$%.2f\n", order.ticket, order.date, order.time, order.description, order.quantity, order.total);
    }
}

void saveOrder(Order *order)
{
    FILE *ordersFile = fopen(ordersFileName, "a");

    if (validateFile(ordersFile))
    {
        printf("Arquivo não encontrado -> %s", ordersFileName);
        return;
    }

    fprintf(ordersFile, "%s %s %s %s %d %.2f\n", order->ticket, order->date, order->time, order->description, order->quantity, order->total);

    fclose(ordersFile);
}

int makeOrder(int productNumber, int quantity, int ticketType)
{
    if (productNumber < 1 || productNumber > MAX_ITEMS)
    {
        printf("Produto inválido...");
        return 1;
    }

    int productIndex = productNumber - 1;

    if (products[productIndex].quantity <= 0 || products[productIndex].quantity < quantity)
    {
        printf("Sem estoque do produto escolhido...");
        return 1;
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

    printf("\nPedido registrado.\n");
    printf("Detalhes do pedido feito: \n");
    printf("Senha: %s | Pedido: %s | Quantidade: %d | Valor Total: R$%.2f\n", order.ticket, order.description, order.quantity, order.total);

    updateProducts();
    saveOrder(&order);

    return 0;
}
