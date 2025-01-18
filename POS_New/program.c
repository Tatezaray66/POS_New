#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "product.h"
#include "extralib.h"
#include "menu.h"

int exited = 0;
int transaction_ended = 0;
int returned = 0;
int cart_filled = 0;

int generate_products() {
	memset(categories, 0, sizeof(categories));
	silent_mode = 1;
	printf("Loading products. . .\n");

	add_item("Beef", "FOOD", "", 450, 60);

	// UNDERGARMENTS
	add_item("Brief", "UNDERGARMENTS", "3pcs", 450, 60);
	add_item("Boxer", "UNDERGARMENTS", "3pcs", 600, 60);
	add_item("Panty", "UNDERGARMENTS", "3pcs", 400, 60);
	add_item("Socks", "UNDERGARMENTS", "3pcs", 300, 60);
	add_item("Foot Socks", "UNDERGARMENTS", "3pcs", 250, 60);



	// LOWER CLOTHING
	add_item("Denim Pants", "LOWER CLOTHING", "L", 899, 30);
	add_item("Denim Pants", "LOWER CLOTHING", "M", 869, 30);
	add_item("Denim Pants", "LOWER CLOTHING", "S", 849, 30);

	add_item("Slocks", "LOWER CLOTHING", "L", 499, 30);
	add_item("Slocks", "LOWER CLOTHING", "M", 449, 30);
	add_item("Slocks", "LOWER CLOTHING", "S", 399, 30);

	add_item("Jogging Pants", "LOWER CLOTHING", "L", 699, 30);
	add_item("Jogging Pants", "LOWER CLOTHING", "M", 699, 30);
	add_item("Jogging Pants", "LOWER CLOTHING", "S", 699, 30);

	add_item("Leggings", "LOWER CLOTHING", "L", 499, 30);
	add_item("Leggings", "LOWER CLOTHING", "M", 499, 30);
	add_item("Leggings", "LOWER CLOTHING", "S", 499, 30);

	add_item("Skirt", "LOWER CLOTHING", "L", 399, 30);
	add_item("Skirt", "LOWER CLOTHING", "M", 399, 30);
	add_item("Skirt", "LOWER CLOTHING", "S", 399, 30);



	// UPPER CLOTHING
	add_item("T-Shirt", "UPPER CLOTHING", "XL", 899, 30);
	add_item("T-Shirt", "UPPER CLOTHING", "L", 899, 30);
	add_item("T-Shirt", "UPPER CLOTHING", "M", 899, 30);
	add_item("T-Shirt", "UPPER CLOTHING", "S", 899, 30);
	add_item("T-Shirt", "UPPER CLOTHING", "XS", 899, 30);

	add_item("Hoodie", "UPPER CLOTHING", "XL", 1399, 30);
	add_item("Hoodie", "UPPER CLOTHING", "L", 1299, 30);

	add_item("Polo", "UPPER CLOTHING", "XXL", 749, 30);
	add_item("Polo", "UPPER CLOTHING", "XL", 739, 30);
	add_item("Polo", "UPPER CLOTHING", "L", 729, 30);
	add_item("Polo", "UPPER CLOTHING", "M", 699, 30);

	add_item("Polo Shirt", "UPPER CLOTHING", "XL", 499, 30);
	add_item("Polo Shirt", "UPPER CLOTHING", "L", 499, 30);

	add_item("Sweater ", "UPPER CLOTHING", "XL", 899, 30);
	add_item("Sweater ", "UPPER CLOTHING", "L", 879, 30);



	// PERFUME
	add_item("Cool Blue", "PERFUME", "50ml", 2999, 15);
	add_item("Cool Blue", "PERFUME", "100ml", 3999, 15);

	add_item("Brave Man", "PERFUME", "50ml", 2899, 15);
	add_item("Brave Man", "PERFUME", "100ml", 3899, 15);

	add_item("Vanilla Lace", "PERFUME", "75ml", 1499, 15);
	add_item("Vanilla Lace", "PERFUME", "250ml", 1999, 15);

	add_item("Cream Cloud", "PERFUME", "75ml", 1499, 15);
	add_item("Cream Cloud", "PERFUME", "236ml", 2399, 15);

	add_item("Versace Eros", "PERFUME", "50ml", 4000, 10);
	add_item("Versace Eros", "PERFUME", "100ml", 5500, 10);
	add_item("Versace Eros", "PERFUME", "200ml", 7000, 10);



	// ACCESSORIES 
	add_item("Silver Earrings", "ACCESSORIES", "", 299, 20);
	add_item("Silver Necklace", "ACCESSORIES", "", 499, 20);
	add_item("Silver Bracelet", "ACCESSORIES", "", 299, 20);
	add_item("Sun Glasses", "ACCESSORIES", "", 499, 35);
	add_item("Hat", "ACCESSORIES", "brown", 499, 15);
	add_item("Hat", "ACCESSORIES", "black", 499, 25);
	add_item("Hat", "ACCESSORIES", "blue", 499, 15);

}

int main() {
	generate_products();

	// Start menu
	while (!exited) {
		transaction_ended = 0;
		returned = 0;

		char input = 0;
		char optionA = '1', optionB = '2', optionC = '3', optionD = '4', optionZ = '0';
		char optionAs = '9';
		

		system("cls");

		// SHOP NAME
		print_lines(42, '*');
		printf(">>\tWELCOME TO SCENT AND STICH\t<<\n");
		print_lines(42, '*');
		printf("\n");

		// PROMPT INPUT
		if (!cart_filled) printf("[1] NEW TRANSACTION\n[2] VIEW CART\n[3] CHECKOUT\n\n\n\n\n[0] LOG OUT\n");
		else printf("[1] NEW TRANSACTION\n[2] VIEW CART\n[3] CHECKOUT\n\n[4] ADD MORE PRODUCTS\n\n\n[0] LOG OUT\n");
		printf("\n");
		print_lines(20, '-');

		printf("Input: ");
		scanf_s("%c", &input, (unsigned)sizeof(input));

		if (!cart_filled) {
			if (input == optionA) start_transaction();
			else if (input == optionB) display_cart();
			else if (input == optionC) display_checkout();
			else if (input == optionZ) exited = 1;

			else if (input == optionAs) print_item_all();
		}

		else {
			if (input == optionA) start_transaction();
			else if (input == optionB) display_cart();
			else if (input == optionC) display_checkout();
			else if (input == optionD) main_menu();
			else if (input == optionZ) exited = 1;

			else if (input == optionAs) print_item_all();
		}
	}

	system("cls");
	printf("Goodbye :)");

	Sleep(5000);
	system("cls");

	return 0;
}

void start_transaction() {
	cart_filled = 0;
	cart_free();
	main_menu();
}

void main_menu() {

	while (1) {
		if (transaction_ended) return;
		returned = 0;

		system("cls");
		print_header("CHOOSE A CATEGORY", 50);
		printf("\n");

		int input = 0;
		for (int i = 0; i < category_size; i++) {
			printf("[%d] %s\n", i + 1, categories[i].name);
		}

		printf("\n\n\n[0] RETURN\n");
		print_lines(20, '-');
		printf("Input: ");
		scanf_s("%d", &input);

		if (input <= 0) break;
		else if (input <= category_size) category_menu(input - 1);
	}
}

void category_menu(int category_index) {

	while (1) {
		if (returned || transaction_ended) return;

		system("cls");
		print_header("CHOOSE A PRODUCT", 50);
		printf("\n");

		int product_size = categories[category_index].product_size;
		char name_list[MAX_LIST_SIZE][MAX_NAME_LEN];
		int product_index[MAX_LIST_SIZE];
		int index = 1;
		int input = 0;

		memset(name_list, 0, sizeof(name_list));
		memset(product_index, 0, sizeof(product_index));

		for (int i = 0; i < product_size; i++) {
			int displayed = 0;
			char product_name[MAX_NAME_LEN];
			strcpy_s(product_name, sizeof(product_name), categories[category_index].product[i].name);

			// check if product is already listed
			for (int u = 0; u < product_size; u++) {
				if (compare(name_list[u], product_name)) {
					displayed = 1;
					break;
				}
			}

			// add it to list of names and indices
			if (!displayed) {
				printf("[%d] %s\n", index, product_name);
				strcpy_s(name_list[index], sizeof(name_list[index]), categories[category_index].product[i].name);
				product_index[index] = i;
				index++;
			}
		}

		printf("\n\n\n[0] RETURN");
		printf("\n");
		print_lines(20, '-');
		printf("Input: ");
		scanf_s("%d", &input);

		if (input <= 0) break;
		else if (input < index) {
			int get_product_index = product_index[input];
			product_menu(category_index, get_product_index);
		}
	}
}

void product_menu(int category_index, int product_index) {

	int input = 0;
	int out_of_stock = 0;
	int amount_exceeded = 0;
	int maxxed = 0;

	while (1) {
		if (returned || transaction_ended) return;

		char product_name[MAX_NAME_LEN];
		strcpy_s(product_name, sizeof(product_name), categories[category_index].product[product_index].name);

		system("cls");
		print_header(product_name, 50);
		printf("\n");

		int has_variant = product_has_variant(product_name, categories[category_index].name);
		int product_size = categories[category_index].product_size;
		char name_list[MAX_LIST_SIZE][VARIANT_NAME_LEN];
		int variant_index[MAX_LIST_SIZE];
		int index = 1;
		int input = 0;

		memset(name_list, 0, sizeof(name_list));
		memset(variant_index, 0, sizeof(variant_index));

		for (int i = 0; i < product_size; i++) {
			int displayed = 0;

			double variant_price = categories[category_index].product[i].price;
			int variant_stocks = categories[category_index].product[i].stocks;
			int variant_oncart = categories[category_index].product[i].on_cart;
			char variant_name[MAX_NAME_LEN];
			strcpy_s(variant_name, sizeof(variant_name), categories[category_index].product[i].variant);

			int product_found = compare(product_name, categories[category_index].product[i].name);

			if (has_variant) {
				if (product_found) {
					// check if variant is already listed
					for (int u = 0; u < product_size; u++) {

						if (compare(name_list[u], variant_name)) {
							displayed = 1;
							break;
						}
					}

					// add it to list of names and indices
					if (!displayed) {
						if (variant_stocks > 0) printf("[%d] %s (%s)\t\tP%0.2f (%d/%d)\n", index, product_name, variant_name, variant_price, variant_oncart, variant_stocks);
						else printf("[%d] %s (%s)\t\tP%0.2f (OUT OF STOCKS)\n", index, product_name, variant_name, variant_price);
						
						strcpy_s(name_list[index], sizeof(name_list[index]), variant_name);
						variant_index[index] = i;
						index++;
					}
				}				
			}
			else {
				// Display something different if product doesn't have a variant
				if (compare(product_name, categories[category_index].product[product_index].name)) {
					printf("[%d] BUY %s\t\tP%0.2f (%d/%d)\n", index, product_name, variant_price, variant_oncart, variant_stocks);
					index++;
					break;
				}
			}

		}

		printf("\n\n\n[0] RETURN");
		printf("\n");
		print_lines(20, '-');

		if (out_of_stock) printf("\n * Product is currently out of stock *\n\n");
		if (amount_exceeded) printf("* Amount you entered exceeded the current stocks left (%d) *\n\n", amount_exceeded);
		if (maxxed) printf("* Amount maxed *\n\n");

		printf("Input: ");
		scanf_s("%d", &input);

		// Checking for product stocks
		int get_product_index = variant_index[input];
		int stocks_count = categories[category_index].product[get_product_index].stocks;
		int stocks_left = stocks_count - (categories[category_index].product[get_product_index].on_cart);

		// reset state
		amount_exceeded = 0;
		out_of_stock = stocks_count <= 0;
		maxxed = stocks_left <= 0 ? 1 : 0;

		if (!out_of_stock) {
			if (input <= 0) break;

			else if (input < index) {
				int amount = 0;
				char confirmed = 0;
				printf("Amount: ");
				scanf_s("%d", &amount);

				if (amount > 0 && amount <= stocks_left) {
					printf("\n\n[ENTER]\t\t:\tADD TO CART\n");
					printf("[BACKSPACE]\t:\tCANCEL\n");
					confirmed = confirm_custom('\r', '\b');

					if (confirmed) {
						char product[MAX_NAME_LEN];
						char variant[VARIANT_NAME_LEN];
						char category[MAX_NAME_LEN];
						strcpy_s(product, sizeof(product), categories[category_index].product[get_product_index].name);
						strcpy_s(variant, sizeof(variant), categories[category_index].product[get_product_index].variant);
						strcpy_s(category, sizeof(category), categories[category_index].name);

						add_to_cart(product, category, variant, amount);
						cart_filled = 1;
						returned = 1;

						display_cart();
						return;
					}
				}

				else if (amount > stocks_left) {
					amount_exceeded = stocks_left;
				}

				else if (amount > stocks_left) {
					amount_exceeded = stocks_left;
				}
			}
		}	
	}
}

void display_cart() {
	system("cls");
	print_header_custom("YOUR CART", '*', 65, 0, 0, 0);
	printf("\n");

	if (cart_size > 0) {
		double total_price = 0;

		printf("PRODUCT\t\t\t\tTOTAL\n");
		print_lines(50, '-');
		for (int i = 0; i < cart_size; i++) {
			double price = cart_list[i].price;
			int amount = cart_list[i].stocks;
			double calculated_price = price * amount;
			total_price += calculated_price;

			char product_name[MAX_NAME_LEN];
			char product_variant[MAX_NAME_LEN];
			strcpy_s(product_name, sizeof(product_name), cart_list[i].name);
			strcpy_s(product_variant, sizeof(product_variant), cart_list[i].variant);


			printf("%s (%s) x%d\t\t\tP%0.2f (P%0.2f)\n", product_name, product_variant, amount, calculated_price, price);
		}
		printf("\n\n");
		print_lines(50, '-');
		printf("\t\t\t\tP%0.2f\n", total_price);
	}

	else {
		printf("This empty cart sits in the void, \na hollow space awaiting the weight of purpose.\n\n\n\n\n\n\n\n\n");
		printf("Press [BACKSPACE] to return\n");
		input_character("\b");
		return;
	}

	// Go directly to checkout
	printf("\n\n\n\n\n\n[ENTER]\t\t:\tCHECK OUT\n");
	printf("[BACKSPACE]\t:\tADD MORE\n");
	int confirmed = confirm_custom('\r', '\b');
	if (confirmed) {
		display_checkout();
		return;
	}
}

void display_checkout() {
	returned = 1;
	cart_filled = 0;
}

void display_reciept() {

}
