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

	sort_product();
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

		clear_buffer();

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

		clear_buffer();

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

		clear_buffer();

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

				clear_buffer();

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
	printf("\n\n");
	print_string_center("--------------------------- YOUR CART ---------------------------", lines_size);
	printf("%-30s %-10s %-13s %-11s\n", "ProductName", "Qty", "Price", "Total");
	print_lines(lines_size, '-');

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
	printf("\n\n");
	print_lines(lines_size, '-');
	printf("%-55s P%0.2f\n", "Subtotal:", total_price);

	// Go directly to checkout
	printf("\n\n\n");
	print_string_center("---------------- CHOOSE AN OPTION ----------------", lines_size);
	print_string_center("[1] ADD PRODUCT   [2] GO HOME   [3] CONFIRM", lines_size);



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

void display_payment_options() {
	page = PAGE_PAYMENT;

	while (page == PAGE_PAYMENT) {
		printf("\n\n");
		int lines_size = 65;
		print_string_center("--------------------------- YOUR CART ---------------------------", lines_size);
	}

	system("cls");
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
	page = PAGE_CONFIG;

	while (page == PAGE_CONFIG) {
		system("cls");
		int line_len = 60;
		char input = 0;
		char manageProduct = '1', logout = '2', back = '0';

		printf("\n\n");
		print_header("CONFIGURATIONS", line_len);
		printf("\n");

		printf("[1] MANAGE PRODUCT\n[2] LOG OUT");
		printf("\n\n\n\n\n[0] BACK");

		while (input == 0)
			input = _getch();

		if (input == manageProduct) display_product_manager();
		else if (input == logout) { exited = 1; break; }
		else if (input == back) { page = PAGE_MAIN; break; }
		
	}
}

void display_product_manager() {
	page = PAGE_PRODUCT_MANAGER;
	int loop_again = 0;

	while (page == PAGE_PRODUCT_MANAGER) {
		system("cls");
		char input = 0;
		char addProduct = '1', removeProduct = '2', editProduct = '3', deleteCategory = '4', back = '0';
		int line_len = 60;

		printf("\n\n");
		print_header("PRODUCT MANAGER", line_len);
		printf("\n[1] ADD PRODUCT\n[2] REMOVE PRODUCT\n[3] EDIT PRODUCT\n[4] DELETE CATEGORY\n\n\n[0] BACK\n");
		printf("\n");

		while (input == 0) input = _getch();

		// For adding products
		if (input == addProduct) {
			while (1) {	
				system("cls");
				sort_product();

				char productName[MAX_NAME_LEN] = "";
				char productCategory[MAX_NAME_LEN] = "";
				char productVariant[VARIANT_NAME_LEN] = "";
				double productPrice = 0;
				int productStocks = 0;
				int productCategoryIndex = 0;
				int newCategory = 0;

				int result;
				printf("\n\n");
				print_header("NEW PRODUCT", line_len);
				printf("\n");

				printf("%-10s : ", "Name");
				result = scanf_s("%[^\n]", productName, (unsigned)sizeof(productName));
				if (result != 1) {
					printf("\nYou have entered an invalid input,\nor exceeded the string limit (%d)\n", MAX_NAME_LEN - 1);
					clear_buffer();
					pause();
					break;
				}

				clear_buffer();

				printf("%-10s : ", "Variant");
				result = scanf_s("%[^\n]", productVariant, (unsigned)sizeof(productVariant));
				if (result != 1) {
					printf("\nYou have entered an invalid input,\nor exceeded the string limit (%d)\n", VARIANT_NAME_LEN - 1);
					clear_buffer();
					pause();
					break;
				}

				clear_buffer();

				printf("%-10s : ", "Price");
				result = scanf_s("%lf", &productPrice);
				if (result != 1) {
					printf("You have entered an invalid input");
					clear_buffer();
					pause();
					break;
				}

				clear_buffer();

				printf("%-10s : ", "Stocks");
				result = scanf_s("%d", &productStocks);
				if (result != 1) {
					printf("You have entered an invalid input");
					clear_buffer();
					pause();
					break;
				}

				clear_buffer();

				system("cls");
				printf("\n\n");
				print_header("NEW PRODUCT", line_len);
				printf("\n[1] CHOOSE EXISTING CATEGORY");
				printf("\n[2] CREATE NEW CATEGORY\n");

				int inputDecision = confirm_custom('1', '2');

				if (inputDecision) {
					system("cls");
					printf("\n\n");
					print_header("Choose Category", line_len);

					// Display the categories
					for (int i = 0; i < category_size; i++) {
						printf("%-3d :  %-20s\n", i + 1, categories[i].name);
					}

					print_lines(line_len, '-');
					printf("Index : ");
					scanf_s("%d", &productCategoryIndex);

					if (productCategoryIndex == 0) {
						break;
					}
				}
				else {
					system("cls");
					printf("\n\n");
					print_header("NEW PRODUCT", line_len);
					printf("\n");
					printf("Enter Category Name: ");
					int category_result = scanf_s("%[^\n]", productCategory, (unsigned)sizeof(productCategory));
					clear_buffer();

					if (category_result != 1) {
						printf("\nYou have entered an invalid input,\nor exceeded the string limit (%d)\n", VARIANT_NAME_LEN - 1);
						clear_buffer();
						pause();
						break;
					}

					if (category_exist(productCategory)) {
						system("cls");
						printf("\n\n");
						print_header("NEW PRODUCT", line_len);
						printf("\n");

						print_string_center("The category already exists", line_len);
						print_string_center("Do you wish to include it in the existing category ? ", line_len);
						print_string_center("[1] CONFIRM     [2] CANCEL", line_len);

						int confirmation = confirm_custom('1', '2');

						if (!confirmation) {
							break;
						}
					}

					else {
						newCategory = 1;
					}
				}
				int categoryIndex = clamp_int(productCategoryIndex - 1, 0, category_size);
				if (!newCategory) strcpy_s(productCategory, sizeof(productCategory), categories[categoryIndex].name);

				system("cls");
				printf("\n\n");
				print_string_center("-------------------- PRODUCT INFORMATION -------------------", line_len);
				printf("\n\n");

				if (newCategory) print_string_center("* NEW CATEGORY *", line_len);

				print_string_center(productCategory, line_len);
				print_lines(line_len, '-');
				printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
				print_lines(line_len, '-');
				printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productName, productVariant, productPrice, productStocks);
				printf("\n\n");


				print_string_center("------------------- CONFIRM PRODUCT ------------------", line_len);
				printf("\n");
				print_string_center("[1] CONFIRM	[2] CANCEL", line_len);

				int confirmation = confirm_custom('1', '2');

				if (confirmation) {
					add_item(productName, productCategory, productVariant, productPrice, productStocks);
					system("cls");
					printf("\n\n");
					print_string_center("-------------------- PRODUCT INFORMATION -------------------", line_len);
					printf("\n\n");
					print_string_center(productCategory, line_len);
					print_lines(line_len, '-');
					printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
					print_lines(line_len, '-');
					printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productName, productVariant, productPrice, productStocks);
					printf("\n\n");

					print_string_center("* THE PRODUCT WAS SUCCEFULLY ADDED *", line_len);
					printf("\n");
					print_string_center("Press [ENTER] to continue", line_len);
					input_character("\r");

					// Sorts product after changing the names
					sort_product();

					break;
				}
			}
			
		}

		// For removing products
		if (input == removeProduct) {
			while (1) {
				sort_product();
				int categoryIndexInput = 0, productIndexInput = 0;
				char confirmed = 0;

				print_item_all_index();
				printf("[0] Back\n");
				print_lines(line_len, '-');
				printf("Category[1 - %d] :  ", category_size);
				scanf_s("%d", &categoryIndexInput);

				clear_buffer();

				if (categoryIndexInput > 0) {
					int categoryIndex = clamp_int(categoryIndexInput - 1, 0, category_size);
					printf("Product [1 - %d] :  ", categories[categoryIndex].product_size);
					scanf_s("%d", &productIndexInput);

					if (categoryIndexInput <= category_size && productIndexInput <= categories[categoryIndex].product_size) {
						if (productIndexInput > 0) {
							int productIndex = clamp_int(productIndexInput - 1, 0, categories[categoryIndex].product_size);
							Product productToRemove = categories[categoryIndex].product[productIndex];

							system("cls");
							printf("\n\n");
							print_string_center("---------------------- REMOVE PRODUCT ----------------------", line_len);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, line_len);
							print_lines(line_len, '-');
							printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
							print_lines(line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d\n\n\n", productToRemove.name, productToRemove.variant, productToRemove.price, productToRemove.stocks);
							print_string_center("* WARNING, THIS WILL PERMANENTLY DELETE *", line_len);
							print_string_center("THE PRODUCT IN YOUR INVENTORY", line_len);

							printf("\n");
							print_string_center("---------------- DO YOU WISH TO PROCEED? ------------------", line_len);
							print_string_center("[1] CONFIRM   [2] CANCEL", line_len);
							printf("\n");

							int confirmation = confirm_custom('1', '2');

							if (confirmation) {
								system("cls");
								printf("\n\n");
								remove_item(productToRemove.name, categories[categoryIndex].name, productToRemove.variant);
								print_string_center("--------------------- PRODUCT REMOVED ----------------------", line_len);
								print_string_center("The product was succesfully removed from your inventory", line_len);
								printf("\n\n");

								print_string_center("Press [ENTER] to continue", line_len);
								(void)_getch();

								// Sorts product after changing the names
								sort_product();
							}
						}
					}
				}
				else break;
			}
		}	

		// For editing products
		if (input == editProduct) {
			int local_Line_len = 75;
			int categoryIndexInput = 0, productIndexInput = 0;
			char confirmed = 0;

			sort_product();
			print_item_all_index_plus_discount();
			print_lines(local_Line_len, '-');
			printf("Category[1 - %d]\t:  ", category_size);
			scanf_s("%d", &categoryIndexInput);

			// Get a valid category index
			if (categoryIndexInput > 0) {
				int categoryIndex = clamp_int(categoryIndexInput - 1, 0, category_size);
				printf("Product [1 - %d]\t:  ", categories[categoryIndex].product_size);
				scanf_s("%d", &productIndexInput);

				while (1) {

					if (productIndexInput > 0) {
						int productIndex = clamp_int(productIndexInput - 1, 0, categories[categoryIndex].product_size);
						Product productToEdit = categories[categoryIndex].product[productIndex];

						system("cls");
						printf("\n\n");
						print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

						printf("\n\n");
						print_string_center(categories[categoryIndex].name, local_Line_len);
						print_lines(local_Line_len, '-');
						printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
						print_lines(local_Line_len, '-');
						printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);

						printf("\n");
						print_string_center("------------------ WHATS YOUR ACTION? ---------------------", local_Line_len);
						printf("\n");
						print_string_center("[1] CHANGE NAME   [2] CHANGE PRICE    [3] EDIT DISCOUNT", local_Line_len);
						print_string_center("[4] INCREASE STOCKS   [5] DECREASE STOCKS    [6] EDIT STOCKS", local_Line_len);
						printf("\n");
						print_string_center("[0] BACK", local_Line_len);
						printf("\n");

						char change_name = '1', change_price = '2', change_discount = '3', increase_stocks = '4', decrease_stocks = '5', edit_stocks = '6';
						int user_input = _getch();

						// For Changing Name
						if (user_input == change_name) {
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\nNew Name: ");

							clear_buffer();
							char new_name[MAX_NAME_LEN] = "";
							int input_result = scanf_s("%[^\n]", new_name, (unsigned)sizeof(new_name));

							if (input_result != 1) {
								printf("\nYou have entered an invalid input,\nor exceeded the string limit (%d)\n", MAX_NAME_LEN - 1);
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								system("cls");
								printf("\n\n");
								print_string_center("* THIS WILL OVERWRITE ALL PRODUCT WITH THE SAME NAME *", local_Line_len);
								printf("\n");
								print_string_center("------------------- CONFIRM CHANGED? ----------------------", local_Line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", local_Line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
									for (int i = 0; i < categories[categoryIndex].product_size; i++) {
										Product* productNameToEdit = &categories[categoryIndex].product[i];

										if (compare(productNameToEdit->name, productToEdit.name))
											strcpy_s(productNameToEdit->name, sizeof(productNameToEdit->name), new_name);
									}
								}
							}
						}

						// For Changing Price
						else if (user_input == change_price) {
							system("cls");
							printf("\n\n");
							print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, local_Line_len);
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\Set Price: ");

							clear_buffer();
							double new_price;
							int input_result = scanf_s("%lf", &new_price);

							if (input_result != 1) {
								printf("\nYou have entered an invalid input.\n");
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								printf("\n\n");
								system("cls");
								printf("\n\n\n");

								printf("\n\n");
								print_string_center(categories[categoryIndex].name, local_Line_len);
								print_lines(local_Line_len, '-');
								printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
								print_lines(local_Line_len, '-');
								
								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("OLD", local_Line_len);

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, new_price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("NEW", local_Line_len);
								printf("\n\n");

								print_string_center("------------------- CONFIRM CHANGED? ----------------------", local_Line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", local_Line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
										Product* productNameToEdit = &categories[categoryIndex].product[productIndex];
										productNameToEdit->price = new_price;
								}
							}

						}

						else if (user_input == change_discount) {
							system("cls");
							printf("\n\n");
							print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, local_Line_len);
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\Set Discount: ");

							clear_buffer();
							int new_discount;
							int input_result = scanf_s("%d", &new_discount);

							if (input_result != 1) {
								printf("\nYou have entered an invalid input.\n");
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								printf("\n\n");
								system("cls");
								printf("\n\n\n");

								printf("\n\n");
								print_string_center(categories[categoryIndex].name, local_Line_len);
								print_lines(local_Line_len, '-');
								printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
								print_lines(local_Line_len, '-');

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("OLD", local_Line_len);

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, new_discount);
								print_lines(local_Line_len, '-');
								print_string_center("NEW", local_Line_len);
								printf("\n\n");

								print_string_center("------------------- CONFIRM CHANGED? ----------------------", local_Line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", local_Line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
									Product* productNameToEdit = &categories[categoryIndex].product[productIndex];
									productNameToEdit->discount = new_discount;
								}
							}

						}

						else if (user_input == increase_stocks) {
							system("cls");
							printf("\n\n");
							print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, local_Line_len);
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\Increase Stocks: ");

							clear_buffer();
							int stock_increase;
							int input_result = scanf_s("%d", &stock_increase);

							if (input_result != 1) {
								printf("\nYou have entered an invalid input.\n");
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								printf("\n\n");
								system("cls");
								printf("\n\n\n");

								printf("\n\n");
								print_string_center(categories[categoryIndex].name, local_Line_len);
								print_lines(local_Line_len, '-');
								printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
								print_lines(local_Line_len, '-');

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("OLD", local_Line_len);

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks + abs(stock_increase), productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("NEW", local_Line_len);

								print_string_center("------------------- CONFIRM CHANGED? ----------------------", local_Line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", local_Line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
									Product* productNameToEdit = &categories[categoryIndex].product[productIndex];
									productNameToEdit->stocks += abs(stock_increase);
								}
							}

						}

						else if (user_input == decrease_stocks) {
							system("cls");
							printf("\n\n");
							print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, local_Line_len);
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\Decrease Stocks: ");

							clear_buffer();
							int stock_decrease;
							int input_result = scanf_s("%d", &stock_decrease);

							if (input_result != 1) {
								printf("\nYou have entered an invalid input.\n");
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								printf("\n\n");
								system("cls");
								printf("\n\n\n");

								printf("\n\n");
								print_string_center(categories[categoryIndex].name, local_Line_len);
								print_lines(local_Line_len, '-');
								printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
								print_lines(local_Line_len, '-');

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("OLD", local_Line_len);

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, clamp_int(productToEdit.stocks - abs(stock_decrease), 0, productToEdit.stocks), productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("NEW", local_Line_len);
								printf("\n\n");

								print_string_center("------------------- CONFIRM CHANGED? ----------------------", line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
									Product* productNameToEdit = &categories[categoryIndex].product[productIndex];
									productNameToEdit->stocks -= abs(stock_decrease);
								}
							}

						}

						else if (user_input == edit_stocks) {
							system("cls");
							printf("\n\n");
							print_header_custom("EDIT PRODUCT", '-', local_Line_len, 0, local_Line_len, 0);

							printf("\n\n");
							print_string_center(categories[categoryIndex].name, local_Line_len);
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
							print_lines(local_Line_len, '-');
							printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF \n\n\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
							printf("\n");
							print_lines(local_Line_len, '-');
							printf("\Set Stocks: ");

							clear_buffer();
							int new_stocks;
							int input_result = scanf_s("%d", &new_stocks);

							if (input_result != 1) {
								printf("\nYou have entered an invalid input.\n");
								clear_buffer();
								loop_again = 1;
								pause();
							}
							else {
								printf("\n\n");
								system("cls");
								printf("\n\n\n");

								printf("\n\n");
								print_string_center(categories[categoryIndex].name, local_Line_len);
								print_lines(local_Line_len, '-');
								printf("%-20s %-10s %-11s %-10s %-10s\n", "Product", "Variant", "Price", "Stocks", "Discount");
								print_lines(local_Line_len, '-');

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, productToEdit.stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("OLD", local_Line_len);

								printf("\n");
								printf("%-20s %-10s P%-10.2f x%-10d %d%% OFF\n", productToEdit.name, productToEdit.variant, productToEdit.price, new_stocks, productToEdit.discount);
								print_lines(local_Line_len, '-');
								print_string_center("NEW", local_Line_len);
								printf("\n\n");

								print_string_center("------------------- CONFIRM CHANGED? ----------------------", local_Line_len);
								print_string_center("[1] CONFIRM   [2] CANCEL", local_Line_len);

								int confirmation = confirm_custom('1', '2');

								if (confirmation) {
									Product* productNameToEdit = &categories[categoryIndex].product[productIndex];
									productNameToEdit->stocks = new_stocks;
								}
							}

						}

						else if (user_input == back) {
							clear_buffer();
							break;
						}

					}
				}		
			}
		}

		// For deleting category and its products
		if (input == deleteCategory) {
			system("cls");
			sort_product();

			printf("\n\n");
			print_header("Choose Category", line_len);

			int productCategoryIndex = 0;

			// Display the categories
			for (int i = 0; i < category_size; i++) {
				printf("%-3d :  %-20s\n", i + 1, categories[i].name);
			}
			printf("\n\n[0] Back\n");
			print_lines(line_len, '-');
			printf("Index : ");
			scanf_s("%d", &productCategoryIndex);

			clear_buffer();

			if (productCategoryIndex > 0) {
				int categoryIndex = clamp_int(productCategoryIndex - 1, 0, category_size);
				system("cls");
				printf("\n\n");
				print_string_center("--------------------- REMOVE CATEGORY ----------------------", line_len + 5);

				printf("\n\n");
				print_string_center(categories[categoryIndex].name, line_len + 5);
				print_lines(line_len + 5, '-');
				printf("%-20s %-10s %-11s %-10s\n", "Product", "Variant", "Price", "Stocks");
				print_lines(line_len + 5, '-');

				for (int i = 0; i < categories[categoryIndex].product_size; i++) {
					Product productToRemove = categories[categoryIndex].product[i];
					printf("%-20s %-10s P%-10.2f x%-10d\n", productToRemove.name, productToRemove.variant, productToRemove.price, productToRemove.stocks);
				}

				printf("\n\n");
				print_string_center("* WARNING, THIS WILL PERMANENTLY DELETE *", line_len + 5);
				print_string_center("ALL PRODUCT IN THIS CATEGORY", line_len + 5);

				printf("\n");
				print_string_center("---------------- DO YOU WISH TO PROCEED? ------------------", line_len + 5);
				print_string_center("[1] CONFIRM   [2] CANCEL", line_len + 5);
				printf("\n");

				int confirmation = confirm_custom('1', '2');

				if (confirmation) {
					system("cls");
					printf("\n\n");

					remove_category(categories[categoryIndex].name);

					print_string_center("-------------------- CATEGORY REMOVED ----------------------", line_len + 5);
					print_string_center("The category and all of its products", line_len);
					print_string_center("was succesfully removed from your inventory", line_len);
					printf("\n\n");

					print_string_center("Press [ENTER] to continue", line_len + 5);
					_getch();
				}
			}
			else
				break;
		}

		// For going back
		if (input == back) {
			page = PAGE_CONFIG;
			break;
		}
	}

	if (loop_again) display_product_manager();
}