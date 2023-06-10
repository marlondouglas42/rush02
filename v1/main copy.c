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
        }

        char *numberStr = strtok(line, ":");
        char *writtenForm = strtok(NULL, ":");

        if (numberStr == NULL || writtenForm == NULL) {
            printf("Invalid dictionary entry.\n");
            exit(1);
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
        printf("%s ", getWrittenForm(dictionary, numEntries, tens));
        printNumberInWords(dictionary, numEntries, ones);
    } else if (number >= 100 && number <= 999) {
        int hundreds = number / 100;
        int remainder = number % 100;
        printf("%s hundred ", getWrittenForm(dictionary, numEntries, hundreds));
        printNumberInWords(dictionary, numEntries, remainder);
    } else if (number >= 1000 && number <= 999999) {
        int thousands = number / 1000;
        int remainder = number % 1000;
        printNumberInWords(dictionary, numEntries, thousands);
        printf(" %s ", getWrittenForm(dictionary, numEntries, thousands * 1000));
        printNumberInWords(dictionary, numEntries, remainder);
    } else if (number >= 1000000 && number <= 999999999) {
        int millions = number / 1000000;
        int remainder = number % 1000000;
        printNumberInWords(dictionary, numEntries, millions);
        printf(" %s ", getWrittenForm(dictionary, numEntries, 1000000));
        printNumberInWords(dictionary, numEntries, remainder);
    } else if (number >= 1000000000 && number <= 999999999999) {
        long long billions = number / 1000000000;
        long long remainder = number % 1000000000;
        printNumberInWords(dictionary, numEntries, billions);
        printf(" %s ", getWrittenForm(dictionary, numEntries, 1000000000));
        printNumberInWords(dictionary, numEntries, remainder);
    } else {
        printf("Dict Error");
    }
}

void testConversion(long long number, const char *expectedResult) {
    char command[100];
    snprintf(command, sizeof(command), "./rush-02 %lld", number);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run the program.\n");
        return;
    }

    char result[100];
    if (fgets(result, sizeof(result), fp) != NULL) {
        // Trim newline character
        result[strcspn(result, "\n")] = '\0';

        if (strcmp(result, expectedResult) == 0) {
            printf("PASSED: %lld => %s\n", number, result);
        } else {
            printf("FAILED: %lld => Expected: %s, Actual: %s\n", number, expectedResult, result);
        }
    }

    pclose(fp);
}

void runTests() {
    // Test cases
    testConversion(0, "zero");
    testConversion(42, "forty two");
    testConversion(10, "ten");
    testConversion(100000, "one hundred thousand");
    testConversion(123456789, "one hundred twenty three million four hundred fifty six thousand seven hundred eighty nine");
    testConversion(9876543210, "nine billion eight hundred seventy six million five hundred forty three thousand two hundred ten");
    testConversion(999999999999, "nine hundred ninety nine billion nine hundred ninety nine million nine hundred ninety nine thousand nine hundred ninety nine");
    testConversion(20, "Dict Error");
    testConversion(-42, "Minus forty two");
    testConversion(10, "Error");
}

int main2() {
    runTests();
    return 0;
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
	printf("\n");

	return 0;
}
