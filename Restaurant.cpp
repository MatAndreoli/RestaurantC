#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productsActions.h"
#include "orderActions.h"
#include "ticketManagement.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int opPrincipal;

char enter;

void clear()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void backToMenu()
{
	printf("\nPressione qualquer tecla para voltar ao menu.");
	scanf("%c%c", &enter, &enter);
}

void header(char *text)
{
	printf("============> %s <============\n", text);
}

void showMenu()
{
	printf("%-63s%-63s%s\n", "Pratos", "Bebidas", "Sobremesas");
	for (int i = 0; i < 5; i++)
	{
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\t\t", i + 1, products[i].name, products[i].price, products[i].quantity);
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\t\t", i + 6, products[i + 5].name, products[i + 5].price, products[i + 5].quantity);
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\n", i + 11, products[i + 10].name, products[i + 10].price, products[i + 10].quantity);
	}
}

int main()
{
	loadProducts();
	loadOrders();
	initializeList();

	opPrincipal = 1;
	int chosenProduct, chosenQuantity, ticketType;
	while (opPrincipal != 8)
	{
		clear();
		header("Restaurante");
		printf("Fila de Espera\n");
		l.display();
		printf("\n1. %-20s4. %s\n", "Menu", "Editar Produtos");
		printf("2. %-20s5. %s\n", "Histórico", "Chamar Senha");
		printf("3. %-20s6. %s\n", "Pedir", "Limpar Tudo");
		printf("8. Sair\n");

		printf("Escolha uma opção: ");
		scanf("%i", &opPrincipal);
		switch (opPrincipal)
		{
		case 1:
			clear();
			header("Menu Principal");
			showMenu();
			backToMenu();
			break;
		case 2:
			clear();
			header("Histórico de Pedidos");
			showOrders();
			backToMenu();
			break;
		case 3:
		{
			clear();
			header("Fazer Pedido");
			showMenu();
			printf("Escolha um produto: ");
			scanf("%d", &chosenProduct);
			printf("Quanto do produto vai querer: ");
			scanf("%d", &chosenQuantity);
			printf("Tipo de senha -> 1-Normal 2-Preferencial: ");
			scanf("%d", &ticketType);
			int successfulOrder = makeOrder(chosenProduct, chosenQuantity, ticketType);
			if (successfulOrder == 0)
			{
				l.insert(orders[totalOrders - 1].ticket);
			}
			backToMenu();
			break;
		}
		case 4:
			clear();
			header("Editar Produtos");
			showMenu();
			printf("Digite o código do produto: ");
			scanf("%d", &chosenProduct);
			updateProduct(chosenProduct);
			backToMenu();
			break;
		case 5:
			clear();
			header("Chamar Senha");
			if (l.head == nullptr)
			{
				printf("Nâo há pedidos...");
				backToMenu();
				break;
			}
			callTicket();
			backToMenu();
			break;
		case 6:
			clear();
			header("Excluindo arquivos");
			remove(ordersFileName);
			remove(productsFileName);
			remove(ordersHistoryFileName);
			loadProducts();
			totalOrders = 0;
			l.head = nullptr;
			break;
		case 8:
			clear();
			break;
		default:
			clear();
			header("Opção inválida");
			backToMenu();
			break;
		}
	}

	clear();
	printf("Finalizando...");
	return 0;
}
