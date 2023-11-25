#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productsActions.h"
#include "orderActions.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int opPrincipal, opPedido, opPrato, opBebida, opSobremesa;
int ip, ib, is;
char confPedido, enter;
int PRATO = 0, BEBIDA = 1, SOBREMESA = 2;

struct Pedido
{
	int prato[10];
	int bebida[10];
	int sobremesa[10];
};

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
	printf("\n\tPressione qualquer tecla para voltar ao menu.");
	scanf("%c%c", &enter, &enter); // aguarda uma tecla
}

void header(char *text)
{
	printf("============> %s <============\n", text);
}

void showMenu()
{
	header("Menu Principal");
	printf("%-63s%-63s%s\n", "Pratos", "Bebidas", "Sobremesas");
	for (int i = 0; i < 5; i++)
	{
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\t\t", i + 1, products[i].name, products[i].price, products[i].quantity);
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\t\t", i + 6, products[i + 5].name, products[i + 5].price, products[i + 5].quantity);
		printf("-%-5d %-15s - R$%-10.2f - Disponível: %d\n", i + 11, products[i + 10].name, products[i + 10].price, products[i + 10].quantity);
	}
}

struct Pedido pedido;

int main()
{
	loadProducts();
	opPrincipal = 1;
	while (opPrincipal != 0)
	{
		clear();
		header("Restaurante");
		printf("1-Menu\n2-Histórico\n3-Pedir\n0-FIM\nEscolha: ");
		scanf("%i", &opPrincipal);
		switch (opPrincipal)
		{
		case 1:
			clear();
			showMenu();
			backToMenu();
			break;
		case 2:
			//	chamadaSenha();
			break;
		case 3:
			clear();
			showMenu();
			int chosenProduct, chosenQuantity, ticketType;
			printf("Escolha um produto: ");
			scanf("%d", &chosenProduct);
			printf("Quanto do produto vai querer: ");
			scanf("%d", &chosenQuantity);
			printf("Tipo de senha -> 1-Normal 2-Preferencial: ");
			scanf("%d", &ticketType);
			makeOrder(chosenProduct, chosenQuantity, ticketType);
			backToMenu();
			break;
		}
	}

	clear();
	printf("Finalizando...");
	return 0;
}
