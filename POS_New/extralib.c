#include <math.h>
#include <ctype.h>
#include <string.h>
#include "extralib.h"

/// <summary> Ask for input confirmation, returns true if Y and false if N </summary>
int confirm() {
	char ch = 0;
	while (ch != 'Y' && ch != 'N')
		ch = toupper(_getch());

	return ch == 'Y' ? 1 : 0;
}

int confirm_custom(const char confirm, const char cancel) {
	char ch = 0;
	while (ch != confirm && ch != cancel)
		ch = toupper(_getch());

	return ch == confirm ? 1 : 0;
}

int confirm_prompt(const char* prompt_text) {
	printf("%s", prompt_text);

	char ch = 0;
	while (ch != 'Y' && ch != 'N')
		ch = toupper(_getch());

	return ch == 'Y' ? 1 : 0;
}

int confirm_prompt_custom(const char* prompt_text, const char confirm, const char cancel) {
	printf("%s", prompt_text);

	char ch = 0;
	while (ch != confirm && ch != cancel)
		ch = toupper(_getch());

	return ch == confirm ? 1 : 0;
}

/// <summary> Ask for input confirmation with custom prompt, returns true space is pressed and continue </summary>
int pause_prompt(const char* prompt) {
	printf("\n%s\n", prompt);

	char ch = 0;
	while (ch != ' ')
		ch = toupper(_getch());

	return 1;
}

/// <summary> Ask for input confirmation, returns true space is pressed and continue </summary>
int pause() {
	printf("\nPress space to continue . . .\n");

	char ch = 0;
	while (ch != ' ')
		ch = toupper(_getch());

	return 1;
}

/// <summary> Ask for specific inputs for confirmation, continue if one of the characters in string was pressed, and return true </summary>
int input_character(char* characters) {
	char ch = 0;
	int exited = 0;

	while (!exited) {
		ch = _getch();
		for (int i = 0; i < strlen(characters); i++) {
			if (characters[i] == ch) {
				exited = 1;
				break;
			}
		}
	}

	return 1;
}

char* alnum_string(char* string, int buffer) {
	char limit_string[MAX_NAME_LEN] = "";
	limit_string[buffer];
	int index = 0;

	for (int i = 0; i < buffer; i++) {
		if (isalnum(string[i])) limit_string[index++] = string[i];
	}

	return limit_string;
}


// Additional Math functions
int clamp_int(int value, int min, int max) {
	return value < min ? min : value > max ? max : value;
}

float clamp_float(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}

double clamp_double(double value, double min, double max) {
	return value < min ? min : value > max ? max : value;
}

double get_percentage(double value, double percent, Round round) {
	double total = (clamp_double(percent, 0, 100) / 100) * value;

	switch (round) {
	case ROUND_UP: total = (total - floor(total) > 0) ? floor(total) + 1 : floor(total); break;
	case ROUND_DOWN: total = (total - floor(total) > 0) ? floor(total) : floor(total); break;
	case ROUND_OFF: total = (total - floor(total) >= 0.5) ? floor(total) + 1 : floor(total); break;
	default: break;
	}

	return total;
}

int round_num(double value, Round round) {
	switch (round) {
	case ROUND_UP: return (value - floor(value)) > 0 ? ceil(value) : floor(value);
	case ROUND_DOWN: return (value - floor(value)) > 0 ? floor(value) : floor(value);
	case ROUND_OFF: return (value - floor(value)) >= 0.5 ? ceil(value) : floor(value);
	}

	return 0;
}



int compare(const char* first_string, const char* second_string) {
	return strcmp(first_string, second_string) == 0 ? 1 : 0;
}

void print_lines(int size, const char character) {
	for (int i = 0; i < size; i++) printf("%c", character);
	printf("\n");
}

void print_header(const char* header, int size) {
	for (int i = 0; i < size; i++) printf("-");
	printf("\n");

	int header_char_size = strlen(header) / 2;
	for (int i = 0; i < (size / 2) - header_char_size; i++)printf(" ");
	printf("%s\n", header);

	for (int i = 0; i < size; i++) printf("-");
	printf("\n");
}

void print_header_custom(const char* header, const char character ,int size, int lower_reduction, int upper_reduction, int pivot) {
	int header_char_size = (size / 2) - (strlen(header) / 2) + pivot;
	int upper_len = (size) - upper_reduction;
	int lower_len = (size) - lower_reduction;
	int upper_len_reduced = ((size - upper_len) / 2);
	int lower_len_reduced = ((size - lower_len) / 2);

	for (int i = 0; i < upper_len_reduced + pivot; i++) printf(" ");
	for (int i = 0; i < upper_len; i++) printf("%c", character);
	for (int i = 0; i < upper_len_reduced - pivot; i++) printf(" ");
	printf("\n");

	// Print the header itself
	for (int i = 0; i < header_char_size; i++) printf(" ");
	printf("%s\n", header);

	for (int i = 0; i < lower_len_reduced + pivot; i++) printf(" ");
	for (int i = 0; i < lower_len; i++) printf("%c", character);
	for (int i = 0; i < lower_len_reduced - pivot; i++) printf(" ");
	printf("\n");
}

char* filter_str(const char* string) {
	char string_holder[MAX_NAME_LEN + 1];
	int index = 0;

	for (int i = 0; i < strlen(string) && i < MAX_NAME_LEN; i++) {
		if (isalnum(string[i])) string_holder[index++] = string[i];
	}

	return string_holder;
}

int haschar(const char* string) {
	if (string != NULL && string[0] != '\0')
		return 1;

	return 0;
}

