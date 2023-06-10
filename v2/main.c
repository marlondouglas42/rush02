#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
	long numero;
	char numero_em_palavras[21];
} RegistroDicionario;

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

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

int	getdec(int nb)
{
	if (nb >= 90)
		return (90);
	else if (nb >= 80)
		return (80);
	else if (nb >= 70)
		return (70);
	else if (nb >= 60)
		return (60);
	else if (nb >= 50)
		return (50);
	else if (nb >= 40)
		return (40);
	else if (nb >= 30)
		return (30);
	else if (nb >= 20)
		return (20);
	else if (nb <= 20)
		return (nb);
	else
		return (0);
}

int	getmult(int nb)
{
	if (nb >= 1000000000)
		return (1000000000);
	else if (nb >= 1000000)
		return (1000000);
	else if (nb >= 1000)
		return (1000);
	else if (nb >= 100)
		return (100);
	else
		return (getdec(nb));
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
