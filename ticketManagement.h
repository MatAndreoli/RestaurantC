#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

struct Node
{
    char *data;
    Node *next;

    // Parameterised constructor with default argument
    Node(char *val) : data(val), next(nullptr) {}
    // Parameterise constructor
    Node(char *val, Node *tempNext) : data(val), next(tempNext) {}
};

class LinkedList
{
public:
    Node *head;

    LinkedList() : head(nullptr)
    {
    }

    void insert(char *val)
    {
        Node *newNode = new Node(val);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void shift()
    {
        if (head != nullptr)
        {
            head = head->next;
        }
    }

    void display()
    {
        Node *current = head;
        while (current != nullptr)
        {
            printf("%s ---> ", current->data);
            current = current->next;
        }
        printf("final da fila\n");
    }
};
LinkedList l;

void initializeList()
{
    int initial = 0;
    if (notCalledOrders > 0)
    {
        initial = totalOrders - notCalledOrders;
    }
    else
    {
        return;
    }
    FILE *temp = fopen(ordersHistoryFileName, "r");
    for (int i = initial; i < totalOrders; i++)
    {
        l.insert(orders[i].ticket);
    }
}

void callTicket()
{
    FILE *ordersFile = fopen(ordersFileName, "r");
    FILE *temp = fopen(ordersHistoryFileName, "a");
    fseek(ordersFile, 0, SEEK_SET);
    Order order;

    char *ticket = l.head->data;

    printf("Senhas esperando...\n");
    printf("---------------------------------------------\n");
    l.display();
    printf("---------------------------------------------\n");

    while (fscanf(ordersFile, "%s %s %s %s %d %f", order.ticket, order.date, order.time, order.description, &order.quantity, &order.total) != EOF)
    {
        if (strcmp(ticket, order.ticket) == 0)
        {
            printf("\nChamando Senha ---------> %s <---------\n", order.ticket);
            printf("Detalhes do pedido: \n");
            printf("Senha: %s | Pedido: %s | Quantidade: %d | Valor Total: R$%.2f\n", order.ticket, order.description, order.quantity, order.total);
        }
    }

    fprintf(temp, "%s\n", ticket);

    fclose(ordersFile);
    fclose(temp);
    l.shift();
    loadOrders();
}
