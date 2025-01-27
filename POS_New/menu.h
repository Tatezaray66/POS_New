#pragma once

#define PAGE_MAIN 0
#define PAGE_CATEGORIES 1
#define PAGE_PRODUCTS 2
#define PAGE_VARIANT 2
#define PAGE_CART 3
#define PAGE_CONFIG 4
#define PAGE_PRODUCT_MANAGER 5
#define PAGE_PAYMENT 6

void show_shop_name();
void start_transaction();
void category_menu();
void variant_menu(int category_index, int product_index);
void product_menu(int category_index);
void display_cart();
void display_checkout();
void display_reciept();
void display_configurations();
void display_product_manager();
void display_payment_options();