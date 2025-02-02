#pragma once
#define MAX_NAME_LEN 21
#define MAX_LIST_SIZE 150
#define VARIANT_NAME_LEN 7

typedef enum {
	DONT_ROUND,
	ROUND_UP,
	ROUND_DOWN,
	ROUND_OFF,
} Round;

// Additional math functions
int clamp_int(int value, int min, int max);
float clamp_float(float value, float min, float max);
double clamp_double(double value, double min, double max);

double get_percentage(double value, double percent, Round round);
int round_num(double value, Round round);

// Functions that will make your life easier 
int confirm();
int confirm_custom(const char confirm, const char cancel);
int confirm_prompt(const char* prompt_text);
int confirm_prompt_custom(const char* prompt_text, const char confirm, const char cancel);

int pause();
int pause_prompt(const char* prompt);
int input_character(char* characters);

char* alnum_string(char* string, int buffer);
int compare(const char* first_string, const char* second_string);
int haschar(const char* string);

void print_lines(int size, const char character);
void print_header(const char* header, int size);
void print_header_custom(const char* header, const char character, int size, int lower_reduction, int upper_reduction, int pivot);
void print_string_center(const char* header, int size);

char* filter_str(const char* string);

void clear_buffer();

