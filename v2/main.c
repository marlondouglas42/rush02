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

		char *numero_em_char = removeSpacesFromStr(strtok(linha, ":"));
		char *numero_em_palavras = removeSpacesFromStr(strtok(NULL, ":"));

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

// void printNumeroEmPalavras(RegistroDicionario *dicionario, int numero_de_registros, long numero) {
// 	if (numero < 0) {
// 		ft_putstr("minus ");
// 		numero = -numero;
// 	}

// 	char numero_em_palavras[200] = "";

// 	if (numero <= 20)
// 	{
// 		ft_putstr(receber_numero_em_palavras(dicionario, numero_de_registros, numero));
// 		return;
// 	}

// 	if (numero >= 1000000000) {
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000000000));
// 		strcat(numero_em_palavras, " billion ");
// 		numero %= 1000000000;
// 	}

// 	if (numero >= 1000000) {
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000000));
// 		strcat(numero_em_palavras, " million ");
// 		numero %= 1000000;
// 	}

// 	if (numero >= 1000) {
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 1000));
// 		strcat(numero_em_palavras, " thousand ");
// 		numero %= 1000;
// 	}

// 	if (numero >= 100) {
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero / 100));
// 		strcat(numero_em_palavras, " hundred ");
// 		numero %= 100;
// 	}

// 	if (numero >= 20) {
// 		int dezena = numero / 10;
// 		int unidade = numero % 10;
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, dezena * 10));
// 		if (unidade > 0) {
// 			strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, unidade));
// 		}
// 	} else {
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero));
// 	}

// 	ft_putstr(numero_em_palavras);
// }
// void printNumeroEmPalavras(RegistroDicionario *dicionario, int numero_de_registros, long numero) {
// 	if (numero < 0) {
// 		ft_putstr("minus ");
// 		numero = -numero;
// 	}

// 	char numero_em_palavras[200] = "";

// 	if (numero <= 20)
// 	{
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, numero));
// 	}

// 	if (numero > 20)
// 	{
// 		int dezena = numero / 10;
// 		int unidade = numero % 10;
// 		strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, dezena * 10));
// 		if (unidade > 0)
// 		{
// 			strcat(numero_em_palavras, receber_numero_em_palavras(dicionario, numero_de_registros, unidade));
// 		}
// 	}

// 	ft_putstr_sem_quebra(numero_em_palavras);
// }

#include <stdio.h>
#include <stdlib.h>

const char *ones[] = {
    "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
    "seventeen", "eighteen", "nineteen"
};

const char *tens[] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
};

const char *illions[] = {
    "", "thousand", "million", "billion", "trillion", "quadrillion",
    "quintillion", "sextillion", "septillion", "octillion", "nonillion", "decillion"
};

char *say_number(int i);
char *say_number_pos(int i);
char *divide(int dividend, int divisor, const char *magnitude);
char *join(const char *args[], int count);

char *say_number(int i)
{
    if (i < 0) {
        char *negative = say_number_pos(-i);
        char *result = (char *)malloc(strlen(negative) + strlen("negative") + 1);
        sprintf(result, "negative %s", negative);
        free(negative);
        return result;
    }

    if (i == 0) {
        return strdup("zero");
    }

    return say_number_pos(i);
}

char *say_number_pos(int i)
{
    if (i < 20) {
        return strdup(ones[i]);
    }

    if (i < 100) {
        int tens_digit = i / 10;
        int ones_digit = i % 10;
        char *result = (char *)malloc(strlen(tens[tens_digit]) + strlen(ones[ones_digit]) + 1);
        sprintf(result, "%s %s", tens[tens_digit], ones[ones_digit]);
        return result;
    }

    if (i < 1000) {
        return divide(i, 100, "hundred");
    }

    int illions_number = 0;
    const char *illions_name = "";

    for (int n = 1; n <= 11; n++) {
        if (i < (int)pow(1000, n + 1)) {
            illions_number = n;
            illions_name = illions[n];
            break;
        }
    }

    return divide(i, (int)pow(1000, illions_number), illions_name);
}

char *divide(int dividend, int divisor, const char *magnitude)
{
    char *quotient = say_number_pos(dividend / divisor);
    char *remainder = say_number_pos(dividend % divisor);
    char *result = (char *)malloc(strlen(quotient) + strlen(magnitude) + strlen(remainder) + 3);
    sprintf(result, "%s %s %s", quotient, magnitude, remainder);
    free(quotient);
    free(remainder);
    return result;
}

char *join(const char *args[], int count)
{
    int total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(args[i]) + 1;
    }

    char *result = (char *)malloc(total_length + 1);
    result[0] = '\0';

    for (int i = 0; i < count; i++) {
        strcat(result, args[i]);
        if (i < count - 1) {
            strcat(result, " ");
        }
    }

    return result;
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

	//printNumeroEmPalavras(dicionario, numero_de_registros, numero);

    char *result = say_number(numero);
    printf("%d: %s\n", numero, result);
    free(result);

	return 0;
}
