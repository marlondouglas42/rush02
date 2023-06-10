#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	long long number;
	char writtenForm[20];
} NumberEntry;

void loadNumberDictionary(NumberEntry *dictionary, int *numEntries, const char *dictFilename) {
	FILE *file = fopen(dictFilename, "r");
	if (file == NULL) {
		printf("Failed to open the dictionary file.\n");
		exit(1);
	}

	int maxEntries = 50;
	*numEntries = 0;
	char line[50];

	while (fgets(line, sizeof(line), file) != NULL) {
		if (*numEntries >= maxEntries) {
			printf("Dictionary file has too many entries.\n");
			exit(1);
			return;  // Adicione esse return para evitar a chamada de fclose
		}

		char *numberStr = strtok(line, ":");
		char *writtenForm = strtok(NULL, ":");

		if (numberStr == NULL || writtenForm == NULL) {
			printf("Invalid dictionary entry.\n");
			exit(1);
			return;  // Adicione esse return para evitar a chamada de fclose
		}

		dictionary[*numEntries].number = atoll(numberStr);
		strcpy(dictionary[*numEntries].writtenForm, writtenForm);

		(*numEntries)++;
	}

	fclose(file);
}


char* getWrittenForm(NumberEntry *dictionary, int numEntries, long long number) {
	for (int i = 0; i < numEntries; i++) {
		if (dictionary[i].number == number) {
			return dictionary[i].writtenForm;
		}
	}

	return "Dict Error";
}
void printNumberInWords(NumberEntry *dictionary, int numEntries, long long number) {
	if (number < 0) {
		printf("Minus ");
		number = -number;
	}

	if (number == 0) {
		printf("%s", getWrittenForm(dictionary, numEntries, 0));
	} else if (number >= 1 && number <= 9) {
		printf("%s", getWrittenForm(dictionary, numEntries, number));
	} else if (number >= 10 && number <= 19) {
		printf("%s", getWrittenForm(dictionary, numEntries, number));
	} else if (number >= 20 && number <= 99) {
		int tens = (number / 10) * 10;
		int ones = number % 10;
		printf("%s", getWrittenForm(dictionary, numEntries, tens));
		if (ones != 0) {
			printf(" %s", getWrittenForm(dictionary, numEntries, ones));
		}
	} else if (number >= 100 && number <= 999) {
		int hundreds = number / 100;
		int remainder = number % 100;
		printf("%s hundred", getWrittenForm(dictionary, numEntries, hundreds));
		if (remainder != 0) {
			printf(" ");
			printNumberInWords(dictionary, numEntries, remainder);
		}
	} else if (number >= 1000 && number <= 999999) {
		int thousands = number / 1000;
		int remainder = number % 1000;
		printNumberInWords(dictionary, numEntries, thousands);
		printf(" %s", getWrittenForm(dictionary, numEntries, thousands * 1000));
		if (remainder != 0) {
			if (remainder < 100)
				printf(" and");
			printf(" ");
			printNumberInWords(dictionary, numEntries, remainder);
		}
	} else if (number >= 1000000 && number <= 999999999) {
		int millions = number / 1000000;
		int remainder = number % 1000000;
		printNumberInWords(dictionary, numEntries, millions);
		printf(" %s", getWrittenForm(dictionary, numEntries, 1000000));
		if (remainder != 0) {
			if (remainder < 1000)
				printf(" and");
			printf(" ");
			printNumberInWords(dictionary, numEntries, remainder);
		}
	} else if (number >= 1000000000 && number <= 999999999999) {
		long long billions = number / 1000000000;
		long long remainder = number % 1000000000;
		printNumberInWords(dictionary, numEntries, billions);
		printf(" %s", getWrittenForm(dictionary, numEntries, 1000000000));
		if (remainder != 0) {
			if (remainder < 1000000)
				printf(" and");
			printf(" ");
			printNumberInWords(dictionary, numEntries, remainder);
		}
	} else {
		printf("Dict Error");
	}
}






int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 3) {
		printf("Invalid number of arguments.\n");
		return 1;
	}

	char *dictFilename = "numbers.dict";
	if (argc == 3) {
		dictFilename = argv[1];
	}

	NumberEntry dictionary[50];
	int numEntries;

	loadNumberDictionary(dictionary, &numEntries, dictFilename);

	int number;
	if (argc == 2) {
		number = atoi(argv[1]);
	} else {
		number = atoi(argv[2]);
	}

	if (number == 0 && strcmp(argv[1], "0") != 0) {
		printf("Error\n");
		return 1;
	}

	printf("Written form: ");
	printNumberInWords(dictionary, numEntries, number);

	return 0;
}
