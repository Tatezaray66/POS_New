#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "product.h"
#include "extralib.h"
#include "menu.h"

#define SHOP_NAME "SCENT AND STICH"
#define SALES_TAX 5

int exited = 0;
int page = 0;


int generate_products() {
	memset(categories, 0, sizeof(categories));
	silent_mode = 1;
	printf("Loading products. . .\n");

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

	printf("sorting products . . .\n");
	sort_product();
	printf("sorting categories . . .\n");
	sort_category();
}

int main() {
	generate_products();

	show_shop_name();

	// Start menu
	while (!exited) {
		system("cls");
		char input = 0;
		char newTransaction = '1', viewCart = '2', viewInventory = '3', configuration = '9';
		page = PAGE_MAIN;

		show_shop_name();

		// PROMPT INPUT
		printf("[1] NEW TRANSACTION\n[2] VIEW CART\n[3] INVENTORY\n\n\n\n--------------------------------\n[9] CONFIGURATION");

		while (input == 0)
			input = _getch();

		if (input == newTransaction) start_transaction();
		else if (input == viewCart) display_cart();
		else if (input == viewInventory) print_item_all();
		else if (input == configuration) display_configurations();
		
	}

	system("cls");
	printf("Goodbye :)");

	Sleep(5000);
	system("cls");

	return 0;
}

void show_shop_name() {
	printf("\n\n");
	print_lines(45, '*');
	print_string_center(SHOP_NAME, 45);
	print_lines(45, '*');
	printf("\n");
}

void start_transaction() {
	cart_free();
	category_menu();
}

void category_menu() {
	page = PAGE_CATEGORIES;

	while (page == PAGE_CATEGORIES) {
		system("cls");

		printf("\n\n");
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

		if (input <= 0) {
			page = PAGE_MAIN;
			break;
		}
		else if (input <= category_size) {
			product_menu(input - 1);
		}
	}
}

void product_menu(int category_index) {
	page = PAGE_PRODUCTS;

	while (page == PAGE_PRODUCTS) {
		system("cls");
		printf("\n\n");
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

		if (input <= 0) {
			page = PAGE_CATEGORIES;
			break;
		}

		else if (input < index) {
			int get_product_index = product_index[input];
			variant_menu(category_index, get_product_index);
		}
	}
}

void variant_menu(int category_index, int product_index) {
	page = PAGE_VARIANT;
	int input = 0;
	int out_of_stock = 0;
	int amount_exceeded = 0;
	int maxxed = 0;

	while (page == PAGE_VARIANT) {
		system("cls");

		char product_name[MAX_NAME_LEN];
		strcpy_s(product_name, sizeof(product_name), categories[category_index].product[product_index].name);

		// Print product name
		printf("\n\n");
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

		// Print all variants of the product
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
						if (variant_stocks > 0) printf("[%d] %-15s (%s) %-5s P%-8.2f (%d/%d)\n", index, product_name, variant_name, "", variant_price, variant_oncart, variant_stocks);
						else printf("[%d] %-15s (%s) %-5s P%-8.2f (OUT OF STOCKS)\n", index, product_name, variant_name, "", variant_price);
						
						strcpy_s(name_list[index], sizeof(name_list[index]), variant_name);
						variant_index[index] = i;
						index++;
					}
				}				
			}
			else {
				// Display something different if product doesn't have a variant
				if (compare(product_name, categories[category_index].product[product_index].name)) {
					printf("[%d] %-26s P%-8.2f (%d/%d)\n", index, product_name, variant_price, variant_oncart, variant_stocks);
					index++;
					break;
				}
			}

		}

		printf("\n\n\n[0] RETURN");
		printf("\n");
		print_lines(20, '-');

		if (out_of_stock) printf("* Product is currently out of stock *\n\n");
		if (amount_exceeded) printf("* Amount you entered exceeded the current stocks left (%d) *\n\n", amount_exceeded);
		if (maxxed && !out_of_stock) printf("* Amount maxed *\n\n");

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
			if (input <= 0) {
				page = PAGE_PRODUCTS;
				break;
			}

			else if (input < index) {
				int amount = 0;
				char confirmed = 0;
				printf("Amount: ");
				scanf_s("%d", &amount);

				if (amount > 0 && amount <= stocks_left) {
					int lines_size = 50;
					printf("\n");
					print_string_center("---------------- CHOOSE AN OPTION ----------------", lines_size);
					print_string_center("[1] ADD CART   [2] CANCEL", lines_size);
					confirmed = confirm_custom('1', '2');

					if (confirmed) {
						char product[MAX_NAME_LEN];
						char variant[VARIANT_NAME_LEN];
						char category[MAX_NAME_LEN];
						strcpy_s(product, sizeof(product), categories[category_index].product[get_product_index].name);
						strcpy_s(variant, sizeof(variant), categories[category_index].product[get_product_index].variant);
						strcpy_s(category, sizeof(category), categories[category_index].name);

						add_to_cart(product, category, variant, amount);
						page = 1;

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

		// Will sort product
		sort_product();
	}
}

void display_cart() {
	system("cls");
	int lines_size = 65;
	double total_price = 0;
	printf("\n");
	print_string_center("--------------------------- YOUR CART ---------------------------", lines_size);
	printf("%-30s %-10s %-13s %-11s\n", "ProductName", "Qty", "Price", "Total");
	print_lines(lines_size, '-');
	printf("\n\n");
	print_lines(lines_size, '-');
	printf("%-55s P%0.2f\n", "Subtotal:", total_price);

	if (cart_size > 0) {

		for (int i = 0; i < cart_size; i++) {
			double price = cart_list[i].price;
			int amount = cart_list[i].stocks;
			double calculated_price = price * amount;
			total_price += calculated_price;

			char product_name[MAX_NAME_LEN];
			char product_variant[MAX_NAME_LEN];
			strcpy_s(product_name, sizeof(product_name), cart_list[i].name);
			strcpy_s(product_variant, sizeof(product_variant), cart_list[i].variant);


			printf("%-20s %-6s %-3s %-9d P%-12.2f P%-12.2f\n", product_name, product_variant, "", amount, price, calculated_price);
		}

	}

	// Go directly to checkout
	printf("\n\n\n");
	print_string_center("---------------- CHOOSE AN OPTION ----------------", lines_size);
	print_string_center("[1] ADD PRODUCT   [2] GO HOME   [3] CHECKOUT", lines_size);



	int confirmed = 0;
	while (confirmed != '1' && confirmed != '2' && confirmed != '3')
		confirmed = _getch();


	if (confirmed == '1') {
		page = PAGE_CATEGORIES;
		category_menu();
		return;
	}
	else if (confirmed == '2') {
		page = 0;
		return;
	}
	else if (confirmed == '3') {
		display_checkout();
		return;
	}

}

void display_checkout() {
	system("cls");

	if (cart_size > 0) {
		display_reciept();
		checkout();
	}

	else {
		printf("There is nothing to check out. . .");
		(void)_getch();
	}

	page = 0;
}

void display_reciept() {
	// Display Reciept
	int size = 68;
	printf("\n\n");
	print_lines(size, '*');
	print_string_center(SHOP_NAME, size);
	print_string_center("1234 Mabini Street, Barangay Poblacion", size);
	print_string_center("Makati City, 1200 Metro Manila Philippines", size);
	print_string_center("(02) 856 5430 / (02) 862 7701", size);
	print_lines(size, '*');
	printf("\n\n");
	printf("%-30s %-10s %-13s %-11s\n", "Description", "Qty", "Price", "Total");
	print_lines(size, '-');

	double total_price = 0;
	for (int i = 0; i < cart_size; i++) {
		double price = cart_list[i].price;
		int amount = cart_list[i].stocks;
		double calculated_price = price * amount;
		total_price += calculated_price;

		char product_name[MAX_NAME_LEN];
		char product_variant[MAX_NAME_LEN];
		strcpy_s(product_name, sizeof(product_name), cart_list[i].name);
		strcpy_s(product_variant, sizeof(product_variant), cart_list[i].variant);


		printf("%-20s %-6s %-3s %-9d P%-12.2f P%-12.2f\n", product_name, product_variant, "", amount, price, calculated_price);
	}
	printf("\n\n");
	print_lines(size, '-');
	printf("%-55s P%0.2f\n", "Subtotal:", total_price);
	printf("%-55s P%0.2f (%d%%)\n", "Sales Tax:", get_percentage(total_price, SALES_TAX, DONT_ROUND), SALES_TAX);
	print_lines(size, '-');
	printf("%-55s P%0.2f\n\n", "TOTAL:", total_price + get_percentage(total_price, SALES_TAX, DONT_ROUND));
	print_lines(size, '-');
	print_string_center("THANKS FOR SHOPPING WITH US", size);

	printf("\n\n");
	print_string_center("---- Press [SPACE] to end transaction ----", size);
	pause_prompt("");

}




void display_configurations() {

	while (1) {
		system("cls");
		char input = 0;
		char manageProduct = '1', logout = '2', back = '0';

		printf("\n\n");
		print_header("CONFIGURATIONS", 50);
		printf("\n");

		printf("[1] MANAGE PRODUCT\n[2] LOG OUT");
		printf("\n\n\n\n\n[0] BACK");

		while (input == 0)
			input = _getch();

		if (input == manageProduct) display_product_manager();
		else if (input == logout) { exited = 1; break; }
		else if (input == back) break;
		
	}
}

void display_product_manager() {
	while (1) {
		system("cls");
		char input = 0;
		char addProduct = '1', removeProduct = '2', editProduct = '3', back = '0';
		int line_len = 55;

		print_item_all_index();
		print_string_center("------------------- PRODUCT MANAGER -------------------", line_len);
		print_string_center("[1] ADD   [2] REMOVE   [3] EDIT   [0] BACK", line_len);
		printf("\n");

		while (input == 0)
			input = _getch();

		if (input == addProduct) {
			system("cls");
			printf("\n\n");
			char productName[MAX_NAME_LEN];
			char productCategory[MAX_NAME_LEN];
			char productVariant[VARIANT_NAME_LEN];
			double productPrice = 0;
			int productStocks = 0;
			int newCategory = 0;

			print_string_center("------------------- ADD NEW PRODUCT -------------------", line_len + 5);
			printf("\n");
			printf("%-10s : ", "Name");
			scanf_s("%s", productName, (unsigned)sizeof(productName));

			if (!haschar(productName)) {
				printf("\n\n* You have entered an invalid input\n\n\n");
				pause();
				display_product_manager();
				return;
			}

			printf("%-10s : ", "Category");
			scanf_s("%s", productCategory, (unsigned)sizeof(productCategory));

			if (!haschar(productCategory)) {
				printf("\n\n* You have entered an invalid input\n\n\n");
				pause();
				display_product_manager();
				return;
			}

			printf("%-10s : ", "Variant");
			scanf_s("%s", productVariant, (unsigned)sizeof(productVariant));

			if (!haschar(productVariant)) {
				printf("\n\n* You have entered an invalid input\n\n\n");
				pause();
				display_product_manager();
				return;
			}

			printf("%-10s : ", "Price");
			scanf_s("%lf", &productPrice);

			printf("%-10s : ", "Stocks");
			scanf_s("%d", &productStocks);

			if (!category_exist(productCategory)) {
				system("cls");
				printf("\n\n");
				printf("Category doesn't exists. Create a new one?\n-----------------------------------\n");
				printf("[1] CONFIRM\n[2] CANCEL\n");
				printf("\n");

				int confirmation = confirm_custom('1', '2');

				if (!confirmation) {
					display_product_manager();
					return;
				}

				newCategory = 1;
			}
		
			system("cls");
			print_string_center("-------------------- PRODUCT INFO --------------------", line_len + 5);
			printf("\n\n");

			if (newCategory) print_string_center("* NEW CATEGORY *", line_len + 5);

			print_string_center(productCategory, line_len + 5);
			print_lines(line_len + 5, '-');
			printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
			print_lines(line_len + 5, '-');
			printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productName, productVariant, productPrice, productStocks);
			printf("\n\n");


			print_string_center("------------------- CONFIRM PRODUCT ------------------", line_len + 5);
			print_string_center("[1] CONFIRM	[2] CANCEL", line_len + 5);


			int confirmation = confirm_custom('1', '2');

			if (confirmation) {
				system("cls");

				add_item(productName, productCategory, productVariant, productPrice, productStocks);

				print_string_center("--------------------- PRODUCT CREATED ----------------------", line_len + 5);
				printf("\n\n");
				print_string_center(productCategory, line_len + 5);
				print_lines(line_len + 5, '-');
				printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
				print_lines(line_len + 5, '-');
				printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productName, productVariant, productPrice, productStocks);
				printf("\n\n");
				printf("%d\n", category_size);
				pause();
			}

		}

		// For removing products
		if (input == removeProduct) {
			int categoryIndexInput = 0, productIndexInput = 0;
			char confirmed = 0;

			printf("Category[1 - %d]\t:\t ", category_size);
			scanf_s("%d", &categoryIndexInput);

			if (categoryIndexInput > 0) {
				int categoryIndex = clamp_int(categoryIndexInput - 1, 0, category_size);
				printf("Product[1 - %d]\t:\t ", categories[categoryIndex].product_size);
				scanf_s("%d", &productIndexInput);

				if (productIndexInput > 0) {
					int productIndex = clamp_int(productIndexInput - 1, 0, categories[categoryIndex].product_size);
					Product productToRemove = categories[categoryIndex].product[productIndex];

					system("cls");
					printf("\n\n");
					print_string_center("---------------------- REMOVE PRODUCT ----------------------", line_len + 5);

					printf("\n\n");
					print_string_center(categories[categoryIndex].name, line_len + 5);
					print_lines(line_len + 5, '-');
					printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
					print_lines(line_len + 5, '-');
					printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productToRemove.name, productToRemove.variant, productToRemove.price, productToRemove.stocks);
					print_string_center("* WARNING, THIS WILL PERMANENTLY DELETE *", line_len + 5);
					print_string_center("THE PRODUCT IN YOUR INVENTORY", line_len + 5);

					printf("\n");
					print_string_center("----------------- DO YOU WISH TO REMOVE? ------------------", line_len + 5);
					print_string_center("[1] CONFIRM   [2] CANCEL", line_len + 5);
					printf("\n");

					int confirmation = confirm_custom('1', '2');

					if (confirmation) {
						system("cls");
						remove_item(productToRemove.name, categories[categoryIndex].name, productToRemove.variant);
						print_string_center("--------------------- PRODUCT REMOVED ----------------------", line_len + 5);
						printf("\nThe product was succesfully removed from your inventory\n\n\n");

						pause();
					}

				}
			}
		}	
	}
}