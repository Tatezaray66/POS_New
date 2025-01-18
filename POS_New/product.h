#pragma once
#include "extralib.h"

#define PRODUCT_DEFAULT { .name = NULL, .variant = "", .price = 0, .stocks = 0, .discount = 0 }
#define CATEGORY_DEFAULT { .name = NULL, .product = NULL }
#define CATEGORY_SIZE 25
#define ITEM_PER_CATEGORY 100

// The structure of our product, edit if necessary
typedef struct {
	char name[MAX_NAME_LEN];
	char variant[VARIANT_NAME_LEN];
	double price;
	int stocks;
	int discount;

} Product;
typedef struct {
	char name[25];
	int product_size;
	Product product[ITEM_PER_CATEGORY];

} Category;

extern Category categories[MAX_LIST_SIZE];
extern int category_size;
extern Product display_list[MAX_LIST_SIZE];
extern Product cart_list[MAX_LIST_SIZE];


// Checking for item and categories
int category_exist(const char* name);


// Managing items
void new_category(const char* name);
void add_item(const char* product_name, const char* category, const char* variant, const double price, const int stocks);
void remove_item(const char* product_name, const char* category, const char* variant);


// Item manipulation techniques
void change_price(const char* product_name, const char* category, const char* variant, const int new_value);
void change_stocks(const char* product_name, const char* category, const char* variant, const int new_value);

/// <summary> For increasing/decreasing product stock </summary>
void edit_stocks(const char* product_name, const char* category, const char* variant, const int value);


// Printing items
void print_item(const char* product_name, const char* category, const char* variant);
void print_item_all();