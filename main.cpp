#include "Functions.h"

int MenuSt;

void Menu() {
	//  View possible actions for the user
	cout << "Enter command number: " << "\n"
		<< "(1) Add an item in the catalog" << "\n" //Название , цена, раздел, кол-во  *
		<< "(2) Edit item" << "\n" //Изменить цену\кол-во   *
		<< "(3) Create order" << "\n" // Номер заказа, название товара, айди клиента  *** 
		<< "(4) Cansel order" << "\n" // Номер заказа    *
		<< "(5) View items" << "\n" // Показ товаров с фильтрацией/без
		<< "(6) View orders" << "\n" // Показ заказов c фильтрацией /без
		<< "(7) Clear items in catalog" << "\n" //Удаление вещей из каталога
		<< "(0) Exit" << "\n" << "\n" // Выход 
		<< "Your choise: ";
	cin >> MenuSt;
}




int main()
{
	//The main function, which, according to our choice, directs us to other functions

	Menu();
	while (MenuSt != 0) {
		if (MenuSt == 1) {
			ItemEntry();
			Menu();
			continue;
		}
		if (MenuSt == 2) {
			EditItem();
			Menu();
			continue;
		}
		if (MenuSt == 3) {
			CreateOrder();
			Menu();
			continue;
		}
		if (MenuSt == 4) {
			CanselOrder();
			Menu();
			continue;
		}
		if (MenuSt == 5) {
			ViewItems();
			Menu();
			continue;
		}
		if (MenuSt == 6) {
			ViewOrders();
			Menu();
			continue;
		}
		if (MenuSt == 7) {
			ClearItems();
			Menu();
			continue;
		}
		else {
			cout << "Unknown command. Try again!" << "\n";
			break;
		}




	}

	cout << "Ending..." << "\n";

	return 0;
}
