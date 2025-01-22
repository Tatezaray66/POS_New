#pragma once
#include "extralib.h"

#define PRODUCT_DEFAULT { .name = NULL, .variant = "", .price = 0, .stocks = 0, .discount = 0 , .on_cart = 0 }
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
	int on_cart;

} Product;
typedef struct {
	char name[MAX_NAME_LEN];
	int product_size;
	Product product[ITEM_PER_CATEGORY];
} Category;

extern Category categories[MAX_LIST_SIZE];
extern Product display_list[MAX_LIST_SIZE];
extern Product cart_list[MAX_LIST_SIZE];

extern int category_size;
extern int cart_size;
extern int silent_mode;


// Checking for item and categories
int category_exist(const char* name);
int product_exist(const char* product_name, const char* category);
int product_check(const char* product_name, const char* category, const char* variant);
int product_has_variant(const char* product_name, const char* category);
int product_is_on_cart(const char* product_name, const char* category, const char* variant);

// Managing items
void new_category(const char* name);
void add_item(const char* product_name, const char* category, const char* variant, const double price, const int stocks);
void remove_item(const char* product_name, const char* category, const char* variant);
void add_to_cart(const char* product_name, const char* category, const char* variant, const int amount);
void checkout();
void cart_free();


// Item manipulation techniques
void change_price(const char* product_name, const char* category, const char* variant, const int new_value);
void change_stocks(const char* product_name, const char* category, const char* variant, const int new_value);

/// <summary> For increasing/decreasing product stock </summary>
void edit_stocks(const char* product_name, const char* category, const char* variant, const int value);


// Printing items
void print_item(const char* product_name, const char* category, const char* variant);
void print_item_all();
void print_item_all_index();

void sort_product();
void sort_category();