#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct Pedido pedido;

int fileCreated(FILE *file)
{
	if (file == NULL)
	{
		printf("Nao foi possivel abrir o arquivo.\n");
		return 1;
	}
	return 0;
}

void createOrderType(int type, int dishes[10])
{
	FILE *orderFile;
	char fileName[22];
	int typeIndex;

	switch (type)
	{
	case 0:
		strcpy(fileName, "pratosPedidos.csv");
		typeIndex = ip;
		break;
	case 1:
		strcpy(fileName, "bebidasPedidas.csv");
		typeIndex = ib;
		break;
	case 2:
		strcpy(fileName, "sobremesasPedidas.csv");
		typeIndex = is;
		break;
	}

	if (typeIndex > 0)
	{
		orderFile = fopen(fileName, "a+");
		fileCreated(orderFile);
		fprintf(orderFile, "%d", dishes[0]);

		if (typeIndex > 1)
		{
			int dishIndex = 1;
			while (dishIndex < typeIndex)
			{
				fprintf(orderFile, ",%d", dishes[dishIndex]);
				dishIndex++;
			}
		}
		fprintf(orderFile, "\n");
		fclose(orderFile);
	}
}

void gerarPedido(FILE *dishFile)
{
	printf("\n");
	printf("Prato escolhido: \n");
	for (int i = 0; i < ip; i++)
	{
		printf("%i\n", pedido.prato[i]);
	}
	printf("\n");
	printf("Bebida escolhida: \n");
	for (int i = 0; i < ib; i++)
	{
		printf("%i\n", pedido.bebida[i]);
	}
	printf("\n");
	printf("Sobremesa escolhida: \n");
	for (int i = 0; i < is; i++)
	{
		printf("%i\n", pedido.sobremesa[i]);
	}
	printf("Confirmar pedido? S/N\n");
	scanf(" %c", &confPedido);
	printf("Value: %d\n", confPedido);
	switch (confPedido)
	{
	case 83:
		printf("Criando e salvando pedido...");

		createOrderType(PRATO, pedido.prato);
		createOrderType(BEBIDA, pedido.bebida);
		createOrderType(SOBREMESA, pedido.sobremesa);

		sleep(3);
		break;
	case 78:
		printf("Pedido nao foi confirmado, continue seu pedido.\n");
		opPedido = 1;
		break;
	default:
		break;
	}
}

void menuPrato()
{
	printf("=============== Menu de pratos ===============\n");
	printf("1. %-20s4. %-20s\n", "Prato1", "Prato4");
	printf("2. %-20s5. %-20s\n", "Prato2", "Prato5");
	printf("3. %-20s\n", "Prato3");
	scanf("%i", &opPrato);
	switch (opPrato)
	{
	case 1:
		pedido.prato[ip] = 1;
		break;
	case 2:
		pedido.prato[ip] = 2;
		break;
	case 3:
		pedido.prato[ip] = 3;
		break;
	case 4:
		pedido.prato[ip] = 4;
		break;
	case 5:
		pedido.prato[ip] = 5;
		break;
	}
	ip++;
	printf("\n");
}

void menuBebida()
{
	printf("=============== Menu de bebidas ===============\n");
	printf("1. %-20s4. %-20s\n", "Bebida1", "Bebida4");
	printf("2. %-20s5. %-20s\n", "Bebida2", "Bebida5");
	printf("3. %-20s\n", "Bebida3");
	scanf("%i", &opBebida);
	switch (opBebida)
	{
	case 1:
		pedido.bebida[ib] = 1;
		break;
	case 2:
		pedido.bebida[ib] = 2;
		break;
	case 3:
		pedido.bebida[ib] = 3;
		break;
	case 4:
		pedido.bebida[ib] = 4;
		break;
	case 5:
		pedido.bebida[ib] = 5;
		break;
	}

	printf("Bebida: %d", pedido.bebida[ib]);
	ib++;
	printf("\n");
}

void menuSobremesa()
{
	printf("=============== Menu de Sobremesas ===============\n");
	printf("1. %-20s4. %-20s\n", "Sobremesa1", "Sobremesa4");
	printf("2. %-20s5. %-20s\n", "Sobremesa2", "Sobremesa5");
	printf("3. %-20s\n", "Sobremesa3");
	scanf("%i", &opSobremesa);
	switch (opSobremesa)
	{
	case 1:
		pedido.sobremesa[is] = 1;
		break;
	case 2:
		pedido.sobremesa[is] = 2;
		break;
	case 3:
		pedido.sobremesa[is] = 3;
		break;
	case 4:
		pedido.sobremesa[is] = 4;
		break;
	case 5:
		pedido.sobremesa[is] = 5;
		break;
	}

	is++;
	printf("\n");
}

void menuPedido(FILE *dishFile)
{
	// system("clear");
	opPedido = 1;
	ip = 0;
	ib = 0;
	is = 0;

	while (opPedido != 0)
	{
		printf("1. %-20s3. %-20s\n", "Prato", "Sobremesa");
		printf("2. %-20s0. %-20s\n", "Bebida", "Fechar pedido");
		scanf("%i", &opPedido);
		switch (opPedido)
		{
		case 1:
			menuPrato();
			break;
		case 2:
			menuBebida();
			break;
		case 3:
			menuSobremesa();
			break;
		case 0:
			// gerarSenha();
			gerarPedido(dishFile);
			break;
		}
	}
}

int main()
{
	FILE *dishFile, *drinkFile, *dessertFile;
	opPrincipal = 1;
	while (opPrincipal != 0)
	{
		// system("clear");
		printf("1-Pedido\n2-Chamada\n3-Gerencia\n0-FIM\nEscolha: ");
		scanf("%i", &opPrincipal);
		switch (opPrincipal)
		{
		case 1:
			menuPedido(dishFile);
			break;
		case 2:
			//	chamadaSenha();
			break;
		case 3:
			//	menuGerencia();
			break;
		}
	}

	return 0;
}
