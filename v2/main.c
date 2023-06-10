#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "funcoes_uteis.c"

typedef struct {
	long numero;
	char numero_em_palavras[21];
} RegistroDicionario;

void carregueDicionarioNaMemoria(RegistroDicionario *dicionario, int *numero_de_registros, char *arquivo_de_dicionario) {
	FILE *arquivo = fopen(arquivo_de_dicionario, "r");
	if (arquivo == NULL) {
		ft_putstr("Falha ao abrir arquivo.\n");
		return ;
	}

	int registros_maximo = 50;
	*numero_de_registros = 0;
	char linha[50];

	while (fgets(linha, sizeof(linha), arquivo) != NULL) {
		if (*numero_de_registros >= registros_maximo) {
			ft_putstr("O dicionário tem muitos registros.\n");
			return ;
		}

		char *numero_em_char = strtok(linha, ":");
		char *numero_em_palavras = strtok(NULL, ":");

		if (numero_em_char == NULL || numero_em_palavras == NULL) {
			ft_putstr("Registro inválido.\n");
			return;
		}

		dicionario[*numero_de_registros].numero = ft_atoi(numero_em_char);
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
		ft_putstr("minus ");
		numero = -numero;
	}

	char numero_em_palavras[200] = "";

	if (numero == 0) {
		ft_putstr("zero");
		return;
	}

	if (numero >= 1000000000) {
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000000000));
		strcat(numero_em_palavras, " billion ");
		numero %= 1000000000;
	}

	if (numero >= 1000000) {
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000000));
		strcat(numero_em_palavras, " million ");
		numero %= 1000000;
	}

	if (numero >= 1000) {
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000));
		strcat(numero_em_palavras, " thousand ");
		numero %= 1000;
	}

	if (numero >= 100) {
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 100));
		strcat(numero_em_palavras, " hundred ");
		numero %= 100;
	}

	if (numero >= 20) {
		int dezena = numero / 10;
		int unidade = numero % 10;
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, dezena * 10));
		if (unidade > 0) {
			strcat(numero_em_palavras, "-");
			strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, unidade));
		}
	} else {
		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero));
	}

	ft_putstr(numero_em_palavras);
}


int main(int quantidade_de_argumentos, char *lista_de_argumentos[]) {
	if (quantidade_de_argumentos < 2 || quantidade_de_argumentos > 3) {
		ft_putstr("Número inválido de argumentos.\n");
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

	return 0;
}
