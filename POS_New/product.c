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
Category categories[MAX_LIST_SIZE];
int category_size = 0;
int cart_size = 0;
int silent_mode = 0;

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
int product_is_on_cart(const char* product_name, const char* category, const char* variant) {
	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);
				if (product_found) {
					return categories[i].product[u].on_cart;
				}
			}
			break;
		}
	}

	return 0;
}


// Managing items
void new_category(const char* name) {
	if (category_size >= MAX_LIST_SIZE) {
		printf("You have reached the max limit (%d) for item categories\n", MAX_LIST_SIZE);
		return;
	}

	strcpy_s(categories[category_size].name, sizeof(categories[category_size].name), name);
	category_size++;

	if (!silent_mode) printf("NEW: Category '%s' was created\n", name);
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

				if (!silent_mode) {
					printf("NEW: Product '%s' was added on '%s' category\n", product_name, category);
					if (haschar(variant)) printf("Variant: (%s) was added to the product '%s' of category '%s'\n", variant, product_name, category);

				}
				
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
								if (!silent_mode) {
									printf("Overwritten: variant (%s) was added to product '%s' on category '%s'\n", variant, product_name, category);
									printf("Following was overwritten:\tPrice: P%0.2f --> P%0.2f\n\t\t\t\tStocks: %d --> %d\n", current_price, price, current_stocks, stocks);
									break;
								}
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
								if (!silent_mode) {
									printf("Overwritten: product '%s' (%s) already exists on '%s' category\n", product_name, variant, category);
									printf("Following was overwritten:\tPrice: P%0.2f --> P%0.2f\n\t\t\t\tStocks: %d --> %d\n", current_price, price, current_stocks, stocks);
									break;
								}

							}

							else {
								// add product to the list of products in category
								int product_size = categories[i].product_size;
								strcpy_s(categories[i].product[product_size].name, sizeof(categories[i].product[product_size].name), product_name);
								strcpy_s(categories[i].product[product_size].variant, sizeof(categories[i].product[product_size].variant), variant);
								categories[i].product[product_size].price = price;
								categories[i].product[product_size].stocks = stocks;

								if (!silent_mode) printf("Variant: (%s) was added to the product '%s' of category '%s'\n", variant, product_name, category);

								categories[i].product_size++;
								break;
							}
						}
					}
				}
			}
		}	
	}	

	Sleep(1);
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

	if (!silent_mode) printf("Product '%s' (%s) was removed from inventory\n", product_name, variant);
}
void add_to_cart(const char* product_name, const char* category, const char* variant, const int amount) {	
	Product new_product = PRODUCT_DEFAULT;

	for (int i = 0; i < cart_size; i++) {
		if (compare(cart_list[i].name, product_name) && compare(cart_list[i].variant, variant)) {
			cart_list[i].stocks += amount;
			break;
		}
	}

	for (int i = 0; i < category_size; i++) {
		if (compare(categories[i].name, category)) {
			for (int u = 0; u < categories[i].product_size; u++) {
				int product_found = compare(categories[i].product[u].name, product_name) && compare(categories[i].product[u].variant, variant);
				int on_cart = product_is_on_cart(product_name, category, variant);

				if (product_found && !on_cart) {
					strcpy_s(new_product.name, sizeof(new_product.name), categories[i].product[u].name);
					strcpy_s(new_product.variant, sizeof(new_product.variant), categories[i].product[u].variant);
					new_product.price = categories[i].product[u].price;
					new_product.stocks = amount;

					// Add on cart value of the actual product to prevent having more product on cart than on the stocks
					categories[i].product[u].on_cart += amount;

					if (!silent_mode) printf("x%d Product %s ('%s') was added to cart\n", new_product.stocks, new_product.name, new_product.variant);
					break;
				}	

				if (product_found && on_cart) {
					categories[i].product[u].on_cart += amount;
					return;
				}
			}
		}
	}

	cart_list[cart_size] = new_product;
	cart_size++;
}
void checkout() {

	// too slow (make this faster)
	for (int i = 0; i < cart_size; i++) {
		for (int u = 0; u < category_size; u++) {
			for (int j = 0; j < categories[u].product_size; j++) {
				if (compare(cart_list[i].name, categories[u].product[j].name) && compare(cart_list[i].variant, categories[u].product[j].variant)) {
					categories[u].product[j].stocks -= categories[u].product[j].on_cart;
					categories[u].product[j].on_cart = 0;
				}
			}
		}
	}

	// reset cart
	memset(cart_list, 0, sizeof(cart_list));
	cart_size = 0;
}
void cart_free() {
	for (int i = 0; i < cart_size; i++) {
		for (int u = 0; u < category_size; u++) {
			for (int j = 0; j < categories[u].product_size; j++) {
				if (compare(cart_list[i].name, categories[u].product[j].name) && compare(cart_list[i].variant, categories[u].product[j].variant)) {
					categories[u].product[j].on_cart = 0;
				}
			}
		}
	}

	// reset cart
	memset(cart_list, 0, sizeof(cart_list));
	cart_size = 0;
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

	int line_len = 55;
	printf("\n\n");
	print_header_custom("+                    INVENTORY LIST                   +",'+', line_len, 0, 0, 0);
	printf("\n\n");

	for (int i = 0; i < category_size; i++) {
		int product_size = categories[i].product_size;

		print_string_center(categories[i].name, line_len);
		print_lines(line_len, '-');
		printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
		print_lines(line_len, '-');

		for (int u = 0; u < product_size; u++) {
			char productName[MAX_NAME_LEN];
			char productVariant[MAX_NAME_LEN];
			double productPrice = categories[i].product[u].price;
			int productStocks = categories[i].product[u].stocks;
			strcpy_s(productName, sizeof(productName), categories[i].product[u].name);
			strcpy_s(productVariant, sizeof(productName), categories[i].product[u].variant);

			if (haschar(productVariant)) {
				if (productStocks > 0) printf("%-20s %-10s P%-10.2f x%-10d\n", productName, productVariant, productPrice, productStocks);
				else printf("%-20s %-10s P%-10.2f (OUT OF STOCK)\n", productName, productVariant, productPrice);
			} 
			else {
				if (productStocks > 0) printf("%-20s %-10s P%-10.2f x%-10d\n", productName, "", productPrice, productStocks);
				else printf("%-20s %-10s P%-10.2f (OUT OF STOCK)\n", productName, "", productPrice);
			}
		}

		printf("\n\n\n");
	}

	print_string_center("------ Press [SPACE] to return ------", line_len);
	pause_prompt("");
}
void print_item_all_index() {
	system("cls");

	int line_len = 60;
	printf("\n\n");
	print_header_custom("+                       INVENTORY LIST                     +", '+', line_len, 0, 0, 0);
	printf("\n\n");

	for (int i = 0; i < category_size; i++) {
		int product_size = categories[i].product_size;

		printf("%-6d : % -20s\n", i + 1, categories[i].name);
		print_lines(line_len, '-');
		printf("%-6s : %-20s %-10s %-11s %-10s\n", "Index", "Product", "Variant", "Price", "Stocks");
		print_lines(line_len, '-');

		for (int u = 0; u < product_size; u++) {
			char productName[MAX_NAME_LEN];
			char productVariant[MAX_NAME_LEN];
			double productPrice = categories[i].product[u].price;
			int productStocks = categories[i].product[u].stocks;
			strcpy_s(productName, sizeof(productName), categories[i].product[u].name);
			strcpy_s(productVariant, sizeof(productName), categories[i].product[u].variant);

			if (haschar(productVariant)) {
				if (productStocks > 0) printf("%-6d : %-20s %-10s P%-10.2f x%-10d\n", 1 + u, productName, productVariant, productPrice, productStocks);
				else printf("%-6d : %-20s %-10s P%-10.2f (OUT OF STOCK)\n", 1 + u, productName, productVariant, productPrice);
			}
			else {
				if (productStocks > 0) printf("%-6d : %-20s %-10s P%-10.2f x%-10d\n", 1 + u, productName, "", productPrice, productStocks);
				else printf("%-6d : %-20s %-10s P%-10.2f (OUT OF STOCK)\n", 1 + u, productName, "", productPrice);
			}
		}

		printf("\n\n\n");
	}
}



// Sorting and such
void swap_product(Product* product_a, Product* product_b) {
	Product temp_product = *product_a;
	*product_a = *product_b;
	*product_b = temp_product;
}
void swap_category(Category* category_a, Category* category_b) {
	Category temp_category = *category_a;
	*category_a = *category_b;
	*category_b = temp_category;
}

void sort_category() {
	int exit = 0;
		
	if (category_size > 0) {

		while (!exit) {
			int last_index = category_size - 1;
			int char_index = 0;

			// Swap the products from a (lowest) to z (highest)
			for (int i = 0; i < last_index; i++) {
				char get_char1 = categories[i].name[char_index];
				char get_char2 = categories[i + 1].name[char_index];

				// swap products if 'product a' has character in index 'char_index' value higher than 'product b'
				if (get_char1 > get_char2) {
					swap_product(&categories[i], &categories[i]);
					char_index = 0;
				}

				// retain order if 'product a' has character value less than 'product b'
				else if (get_char1 < get_char2) {
					char_index = 0;
				}

				// compare next index if characters are the same
				else if (get_char1 == get_char2) {
					char_index++;
					i--;
				}
			}

			// check if its sorted out by incrementing order count and comparing it to the product list count
			// if true, the list is sorted, if false repeat the process
			int order_count = 1;
			for (int i = 0; i < last_index; i++) {
				char get_char1 = toupper(categories[i].name[char_index]);
				char get_char2 = toupper(categories[i].name[char_index]);

				if (get_char1 < get_char2) {
					char_index = 0;
					order_count++;
				}

				else if (get_char1 > get_char2) {
					char_index = 0;
					break;
				}

				else if (get_char1 == get_char2) {
					char_index++;
					i--;
				}
			}

			if (order_count == category_size) {
				if (!silent_mode) printf("categories was sorted. . .\n");
				exit = 1;
			}
		}
	}

	Sleep(2);
}
void sort_product() {
	for (int i = 0; i < category_size; i++) {
		int exit = 0;
		int product_size = categories[i].product_size;
		if (!silent_mode) printf("Sorting category '%s' products. . . \n", categories[i].name);

		if (product_size > 0) {
			while (!exit) {
				int last_index = product_size - 1;
				int char_index = 0;

				// Swap the products from a (lowest) to z (highest)
				for (int u = 0; u < last_index; u++) {
					char get_char1 = categories[i].product[u].name[char_index];
					char get_char2 = categories[i].product[u + 1].name[char_index];

					// swap products if 'product a' has character in index 'char_index' value higher than 'product b'
					if (get_char1 > get_char2) {
						swap_product(&categories[i].product[u], &categories[i].product[u + 1]);
						char_index = 0;
					}

					// retain order if 'product a' has character value less than 'product b'
					else if (get_char1 < get_char2) {
						char_index = 0;
					}

					// compare next index if characters are the same
					else if (get_char1 == get_char2) {
						char_index++;
						u--;
					}
				}

				// check if its sorted out by incrementing order count and comparing it to the product list count
				// if true, the list is sorted, if false repeat the process
				int order_count = 1;
				for (int u = 0; u < last_index; u++) {
					char get_char1 = toupper(categories[i].product[u].name[char_index]);
					char get_char2 = toupper(categories[i].product[u + 1].name[char_index]);

					if (get_char1 < get_char2) {
						char_index = 0;
						order_count++;
					}

					else if (get_char1 > get_char2) {
						char_index = 0;
						break;
					}

					else if (get_char1 == get_char2) {
						char_index++;
						u--;
					}
				}

				if (order_count == product_size) {
					if (!silent_mode) printf("'%s' products sorted. . .\n", categories[i].name);
					exit = 1;
				}
			}
		}
	
		Sleep(2);
	}
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