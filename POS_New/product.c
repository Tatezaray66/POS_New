#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include "product.h"
#include "extralib.h"

Product product_list[MAX_LIST_SIZE];
Product cart_list[MAX_LIST_SIZE];

int category_size = 0;
Category categories[MAX_LIST_SIZE];

// checking for name existence
int category_exist(const char* name) {
	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, name)) return 1;
	}

	return 0;
}
int product_exist(const char* product_name, const char* category) {
	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				if (compare(categories[i].product[u].name, product_name)) return 1; 
			}

			break;
		}
	}

	return 0;
}
int product_check(const char* product_name, const char* category, const char* variant) {
	if (!category_exist(category)) {
		printf("Category '%s' doesn't exists\n", category);
		return;
	}
	if (!product_exist(product_name, category)) {
		printf("Product '%s' (%s) doesn't exists in '%s' category\n", product_name, variant, category);
		return;
	}

	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);
				if (product_found) return 1;
			}

			break;
		}
	}

	return 0;
}
int product_has_variant(const char* product_name, const char* category) {

	int count = 0;
	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && haschar(categories[i].product[u].variant);
				if (product_found) return 1;

			}

			break;
		}
	}

	return count;
}


// Managing items
void new_category(const char* name) {
	if (category_size >= MAX_LIST_SIZE) {
		printf("You have reached the max limit (%d) for item categories\n", MAX_LIST_SIZE);
		return;
	}

	strcpy_s(categories[category_size].name, sizeof(categories[category_size].name), name);
	category_size++;

	printf("NEW: Category '%s' was created\n", name);
}
void add_item(const char* product_name, const char* category, const char* variant, const double price, const int stocks) {
	// if category doesn't exists, add new one
	if (!category_exist(category)) new_category(category);

	// Check if product exists
	if (!product_exist(product_name, category)) {
		for (int i = 0; i < category_size; i++) {
			if (compare(categories[i].name, category)) {
				// add product to the list of products in category
				int product_size = categories[i].product_size;
				strcpy_s(categories[i].product[product_size].name, sizeof(categories[i].product[product_size].name), product_name);
				strcpy_s(categories[i].product[product_size].variant, sizeof(categories[i].product[product_size].variant), variant);
				categories[i].product[product_size].price = price;
				categories[i].product[product_size].stocks = stocks;

				if (haschar(variant)) printf("NEW: Product '%s' (%s) was added on '%s' category\n", product_name, variant, category);
				else printf("NEW: Product '%s' was added on '%s' category\n", product_name, category);

				categories[i].product_size++;
				break;
			}
		}
	}

	else {

		if (haschar(variant)) {

			// Overwrite current product and add a variant
			if (!product_has_variant(product_name, category)) {
				for (int i = 0; i < category_size; i++) {

					if (compare(categories[i].name, category)) {
						int product_size = categories[i].product_size;
						for (int u = 0; u < product_size; u++) {
							int product_found = compare(categories[i].product[u].name, product_name);

							if (product_found) {
								// previous stat
								int current_stocks = categories[i].product[u].stocks;
								float current_price = categories[i].product[u].price;

								// new stat
								strcpy_s(categories[i].product[u].variant, sizeof(categories[i].product[u].variant), variant);
								categories[i].product[u].price = price;
								categories[i].product[u].stocks = stocks;

								// print stat
								printf("Overwritten: variant (%s) was added to product '%s' on category '%s'\n", variant, product_name, category);
								printf("Following was overwritten:\tPrice: P%0.2f --> P%0.2f\n\t\t\t\tStocks: %d --> %d\n", current_price, price, current_stocks, stocks);
								break;
							}
						}
					}
				}
			}

			// Add new variant to an existing product
			else {
				for (int i = 0; i < category_size; i++) {
					if (compare(categories[i].name, category)) {
						int product_size = categories[i].product_size;
						int variant_exists;

						for (int u = 0; u < product_size; u++) {
							variant_exists = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);

							if (variant_exists) {
								// previous stat
								int current_stocks = categories[i].product[u].stocks;
								float current_price = categories[i].product[u].price;

								// new stat
								categories[i].product[u].price = price;
								categories[i].product[u].stocks = stocks;

								// print update
								printf("Overwritten: product '%s' (%s) already exists on '%s' category\n", product_name, variant, category);
								printf("Following was overwritten:\tPrice: P%0.2f --> P%0.2f\n\t\t\t\tStocks: %d --> %d\n", current_price, price, current_stocks, stocks);
								break;
							}

							else {
								// add product to the list of products in category
								int product_size = categories[i].product_size;
								strcpy_s(categories[i].product[product_size].name, sizeof(categories[i].product[product_size].name), product_name);
								strcpy_s(categories[i].product[product_size].variant, sizeof(categories[i].product[product_size].variant), variant);
								categories[i].product[product_size].price = price;
								categories[i].product[product_size].stocks = stocks;

								if (haschar(variant)) printf("NEW: Product '%s' (%s) was added on '%s' category\n", product_name, variant, category);
								else printf("NEW: Product '%s' (%s) was added on '%s' category\n", product_name, variant, category);

								categories[i].product_size++;
								break;
							}
						}
					}
				}
			}
		}
		
		
	}	
}
void remove_item(const char* product_name, const char* category, const char* variant) {
	if (!product_check(product_name, category, variant)) return;

	int index = 0;
	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			// remove product from the list of products in category

			for (int u = 0; u < categories[i].product_size; u++) {
				int product_to_remove = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);
				if (!product_to_remove) categories[i].product[index++] = categories[i].product[u];
			}

			categories[i].product_size--;
			break;
		}
	}

	printf("Product '%s' (%s) was removed from inventory\n", product_name, variant);
}



// Item manipulation techniques
void change_price(const char* product_name, const char* category, const char* variant, const int new_value) {
	if (!product_check(product_name, category, variant)) return;

	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);

				if (product_found) {
					categories[i].product[u].price = new_value;
					return;
				}
			}

			break;
		}
	}
}
void change_stocks(const char* product_name, const char* category, const char* variant, const int new_value) {
	if (!product_check(product_name, category, variant)) return;

	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);

				if (product_found) {
					categories[i].product[u].stocks = new_value;
					return;
				}
			}

			break;
		}
	}
}
void edit_stocks(const char* product_name, const char* category, const char* variant, const int value) {
	if (!product_check(product_name, category, variant)) return;

	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);

				if (product_found) {
					categories[i].product[u].stocks += value;
					return;
				}
			}

			break;
		}
	}
}





// Printing items
void print_item(const char* product_name, const char* category, const char* variant) {
	print_header("PRODUCT INFO", 100);
	for (int i = 0; i < category_size; i++) {
		int product_size = categories[i].product_size;

		if (compare(categories[i].name, category)) {
			for (int u = 0; u < product_size; u++) {

				if (compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant)) {
					char productName[MAX_NAME_LEN];
					char productVariant[MAX_NAME_LEN];
					double productPrice = categories[i].product[u].price;
					int productStocks = categories[i].product[u].stocks;
					strcpy_s(productName, sizeof(productName), categories[i].product[u].name);
					strcpy_s(productVariant, sizeof(productName), categories[i].product[u].variant);

					printf("productName: %s (%s)\t\tprice: P%0.2f\t\tstocks: %d\n", productName, productVariant, productPrice, productStocks);
					break;
				}

			}

			break;
		}		
	}

	pause();
}
void print_item_all() {
	system("cls");

	print_header("PRODUCT LIST", 100);
	for (int i = 0; i < category_size; i++) {
		int product_size = categories[i].product_size;

		print_header_custom(categories[i].name, 100, 75, 75, 0);
		for (int u = 0; u < product_size; u++) {
			char productName[MAX_NAME_LEN];
			char productVariant[MAX_NAME_LEN];categories[i].product[u].variant;
			double productPrice = categories[i].product[u].price;
			int productStocks = categories[i].product[u].stocks;
			strcpy_s(productName, sizeof(productName), categories[i].product[u].name);
			strcpy_s(productVariant, sizeof(productName), categories[i].product[u].variant);

			printf("productName: %s (%s)\t\tprice: P%0.2f\t\tstocks: %d\n", productName, productVariant, productPrice, productStocks);
		}

		printf("\n\n\n\n");
	}

	pause();
}





// template for initializing category list and its products.
// category_size must be the same as the length of categories within the list
// same goes for each product_size in their own respective catery list
int category_template_size = 5;
Category categories_template[MAX_LIST_SIZE] = {
	{.name = "Category1",
		.product_size = 3,
		.product = {{
			"Item1",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item2",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item3",
			"Vrnt",
			5,
			10,
			0
			},

		}
	},

	{.name = "Category2",
		.product_size = 3,
		.product = {{
			"Item1",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item2",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item3",
			"Vrnt",
			5,
			10,
			0
			},

		}
	},

	{.name = "Category3",
		.product_size = 3,
		.product = {{
			"Item1",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item2",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item3",
			"Vrnt",
			5,
			10,
			0
			},

		}
	},

	{.name = "Category4",
		.product_size = 3,
		.product = {{
			"Item1",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item2",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item3",
			"Vrnt",
			5,
			10,
			0
			},

		}
	},

	{.name = "Category5",
		.product_size = 3,
		.product = {{
			"Item1",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item2",
			"Vrnt",
			5,
			10,
			0
			},

			{
			"Item3",
			"Vrnt",
			5,
			10,
			0
			},

		}
	}
};