#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "funcoes_uteis.c"

typedef struct {
	long numero;
	char numero_em_palavras[21];
} RegistroDicionario;

void carregueDicionarioNaMemoria(RegistroDicionario *dicionario, int *numero_de_registros, char *arquivo_de_dicionario) {
	FILE *arquivo = fopen(arquivo_de_dicionario, "r");
	if (arquivo == NULL) {
		printf("Falha ao abrir arquivo.\n");
		return ;
	}

	int registros_maximo = 50;
	*numero_de_registros = 0;
	char linha[50];

	while (fgets(linha, sizeof(linha), arquivo) != NULL) {
		if (*numero_de_registros >= registros_maximo) {
			printf("O dicionário tem muitos registros.\n");
			return ;
		}

		char *numero_em_char = strtok(linha, ":");
		char *numero_em_palavras = strtok(NULL, ":");

		if (numero_em_char == NULL || numero_em_palavras == NULL) {
			printf("Registro inválido.\n");
			return;
		}

		dicionario[*numero_de_registros].numero = atoll(numero_em_char);
		strcpy(dicionario[*numero_de_registros].numero_em_palavras, numero_em_palavras);

		(*numero_de_registros)++;
	}

	fclose(arquivo);
}

char* receber_numero_em_palavras(RegistroDicionario *dicionario, int numero_de_registros, long numero) {
	for (int i = 0; i < numero_de_registros; i++) {
		if (dicionario[i].numero == numero) {
			return dicionario[i].numero_em_palavras;
		}
	}

	return "receber_numero_em_palavras() - numero não achado no dicionário.";
}

void printNumeroEmPalavras(RegistroDicionario *dicionario, int numero_de_registros, long numero) {
	if (numero < 0) {
		printf("minus ");
		numero = -numero;
	}

	while (numero / 10 > 0)
	{

	}
}


int main(int quantidade_de_argumentos, char *lista_de_argumentos[]) {
	if (quantidade_de_argumentos < 2 || quantidade_de_argumentos > 3) {
		//testes();
		printf("Número inválido de argumentos.\n");
		return 1;
	}

	char *arquivo_de_dicionario = "numbers.dict";
	if (quantidade_de_argumentos == 3) {
		arquivo_de_dicionario = lista_de_argumentos[1];
	}

	RegistroDicionario dicionario[50];
	int numero_de_registros;

	carregueDicionarioNaMemoria(dicionario, &numero_de_registros, arquivo_de_dicionario);

	int numero;
	if (quantidade_de_argumentos == 2) {
		numero = ft_atoi(lista_de_argumentos[1]);
	} else {
		numero = ft_atoi(lista_de_argumentos[2]);
	}

	printNumeroEmPalavras(dicionario, numero_de_registros, numero);

	// int i = 100;
	// while (i < 200)
	// {
	// 	printNumeroEmPalavras(dicionario, numero_de_registros, i);
	// 	i++;
	// }

	return 0;
}
