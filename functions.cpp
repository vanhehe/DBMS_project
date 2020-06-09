#include "Functions.h"


void ItemEntry() {


	//The function allows you to add items in "Items.txt"
	//selected quantity of goods to the list of items as:
	// Item name
	//Item price
	// Item catrgory
	// Item quantity


	string name;
	int price;
	string category;
	int quantity;
	int n;
	cout << "How much different items do you want to add? ";
	cin >> n;
	ofstream record("Items.txt", ios::app);
	if (record) {
		for (int i = 0; i < n; i++) {
			cout << "Enter item name- ";
			cin >> name;
			cout << "Enter item price- ";
			cin >> price;
			cout << "Enter item category- ";
			cin >> category;
			cout << "Enter item quantity- ";
			cin >> quantity;
			record << "Item_name: " << name << "\n";
			record << "Item_price: " << price << "\n";
			record << "Item_category: " << category << "\n";
			record << "Item_quantity: " << quantity << "\n";
			cout << "__________________________________" << "\n";
		}
	}
	else {
		cout << "File opening error" << "\n";

		record.close();
	}
	cout << "Your items successefully added in catalog!" << "\n" << "\n";
}



void EditItem() {


	//	The function displays all items, asks which one
	//we want to change, and changes it in the file "Items.txt"


	Clone("Items.txt", "Items_Clone.txt");
	ifstream reading("Items_Clone.txt");
	ofstream record("Items.txt", ios::out);
	cout << "Choose item number for editting: " << "\n";
	if (reading) {
		if (record) {
			string name, name1;
			int price, stat;
			string category, s;
			int quantity;
			int n, i = 1, j = 1;
			while (getline(reading, s)) {
				if (i % 4 == 1) {
					cout << "(" << ((i - 1) / 4) + 1 << ") " << s.substr(11) << "\n";
				}
				i++;
			}
			ifstream reading1("Items_Clone.txt");
			cout << "\n" << "Your choise? ";
			cin >> n;
			while (true) {
				cout << "\n" << "What exactly do you want to edit in (" << n << ") ?" << "\n"
					<< "(1) item name" << "\n"
					<< "(2) price" << "\n"
					<< "(3) category" << "\n"
					<< "(4) quantity" << "\n"
					<< "(0) Exit" << "\n"
					<< "Your choise: ";
				cin >> stat;
				i = ((n - 1) * 4) + 1;
				while (getline(reading1, s)) {
					if (j == i) {
						name = s;
						if (stat == 1) {
							cout << "Enter new name for " << name.substr(11) << ": ";
							cin >> name1;
							record << "Item_name: " << name1 << "\n";
							j++;
							continue;
						}
					}
					if (j == i + 1 && stat == 2) {
						cout << "Enter new price of " << name.substr(11) << ": ";
						cin >> price;
						record << "Item_price: " << price << "\n";
						j++;
						continue;
					}
					if (j == i + 2 && stat == 3) {
						cout << "Enter new category of " << name.substr(11) << ": ";
						cin >> category;
						record << "Item_category: " << category << "\n";
						j++;
						continue;
					}
					if (j == i + 3 && stat == 4) {
						cout << "Enter new quantity of " << name.substr(11) << ": ";
						cin >> quantity;
						record << "Item_quantity: " << quantity << "\n";
						j++;
						continue;
					}
					j++;
					record << s << "\n";
				}
				if (stat == 0) {
					break;
				}
			}

		}
	}
	cout << "Data changed successefully!" << "\n" << "\n";
}



void Clone(string from, string to) {


	// The function accepts two files as input(where to copy and what to copy) and copy


	ifstream reading(from);
	if (reading)
	{
		ofstream record(to);
		record << reading.rdbuf();
		record.close();
		reading.close();
	}
}



void CreateOrder() {


	//The function requires you to enter the number of products 
	//that you want to add to the order, asks which goods and 
	//how many, and writes them to a file "Orders.txt"


	string order_number;
	string item_name, m;
	int item_quantity;
	int client_id, order_price = 0;
	int n, cnt = 0, cnt2 = 0;
	bool suc = false;
	cout << "How much different items are in basket? ";
	cin >> n;
	ofstream record("Orders.txt", ios::app);
	ifstream read1("Items.txt");
	if (read1) {
		while (getline(read1, m)) {
			cnt++;
		}
	}
	if (record) {
		cout << "Enter order number- ";
		cin >> order_number;
		cout << "Enter client id- ";
		cin >> client_id;
		record << "Order_number: " << order_number << "\n";
		record << "Client_id: " << client_id << "\n" << "{" << "\n";
		for (int i = 0; i < n; i++) {
			ifstream reading("Items.txt");
			bool flag = false;
			string s;
			int cnt1 = 0, j = 0;
			cout << "Enter item name- ";
			cin >> item_name;
			cout << "Enter quantity of this item- ";
			cin >> item_quantity;
			while (getline(reading, s)) {
				cnt1++;
				string s1 = s;
				if (s1.substr(11) == item_name) {
					flag = true;
				}
				if (flag) {
					j++;
				}
				if (j == 2) {
					s = s.substr(12);
					order_price += atoi(s.c_str()) * item_quantity;
				}
				if (j == 4) {
					s = s.substr(15);
					if (item_quantity > atoi(s.c_str())) {
						cout << "Unfortunately, the items are not enough." << "\n"
							<< "Maximum quantity of " << item_name << ": " << atoi(s.c_str()) << "\n" << "\n";
					}
					else {
						record << "Item_name: " << item_name << "\n";
						record << "Item_quantity: " << item_quantity << "\n";

						Edit2(item_name, item_quantity);
						cout << "Item was added in your order" << "\n";
						cout << "__________________________________" << "\n";
						cnt2++;
						suc = true;
					}
				}
				if (cnt1 == cnt && flag == false) {
					cout << "Item not in catalog! " << "\n";
					cout << "__________________________________" << "\n";
				}
			}

		}
		record << "}" << "\n";
		record << "Order_price: " << order_price << "\n";
		if (cnt2 == 0) {
			cout << "Your order was deleted because it was empty. " << "\n";
			bool empty = true;
			record.close();
			CanselOrder2(order_number, empty);
		}
		if (suc == true) {
			cout << "Your order successefully created! " << "\n" << "\n";
		}
	}
	else
		cout << "File opening error" << "\n";
	record.close();
}



void Edit2(string item_name, int item_quantity) {


	//The function changes the number of items after the cancellation of the order 
	//(adds as much as was ordered to the quantity of items in "Items.txt")


	Clone("Items.txt", "Items_Clone.txt");
	string s, m;
	bool flag = false;
	int j = 0, cnt = 0, cnt2 = 0;
	ifstream reading("Items_Clone.txt");
	ifstream read1("Items_Clone.txt");
	ofstream record("Items.txt", ios::out);
	while (getline(read1, m)) {
		cnt++;
	}
	while (getline(reading, s)) {
		cnt2++;
		if (s.substr(11) == item_name) {
			flag = true;
		}
		if (flag) {
			j++;
		}
		if (j == 4) {
			record <<"Item_quantity: "<< atoi(s.substr(15).c_str()) - item_quantity << "\n";
			continue;

		}

		record << s << "\n";
	}
}



void CanselOrder() {


	// The function displays the numbers of orders available for deletion. 
	//After selecting the order number, it passes it to the function CanselOrder2()


	ifstream reading("Orders.txt");
	cout << "Choose order number for editting? " << "\n";
	cout << "Order numbers: " << "\n";
	if (reading) {
		string n;
		int j = 0;
		string s;
		bool flag = false, flag2 = true;
		while (getline(reading, s)) {
			if (s == "}") {
				flag = true;
				j = 0;
				continue;
			}
			if (flag2) {
				cout << s.substr(14) << "\n";
				flag2 = false;
				continue;
			}
			if (flag) {
				j++;
				flag = false;
				continue;
			}
			if (j == 1) {
				cout << s.substr(14) << "\n";
				j = 0;
				continue;
			}
		}
		cout << "Enter number of order which you want to delete: ";
		cin >> n;
		CanselOrder2(n);
	}
}



void CanselOrder2(string n, bool empty) {


	//The function accepts the order number as input and deletes it. 
	//In case of successful finding, it starts the function Edit2() which corrects quantity of Item


	Clone("Orders.txt", "Orders_Clone.txt");
	ofstream record("Orders.txt", ios::out);
	ifstream reading1("Orders_Clone.txt");
	ofstream rec("Items.txt", ios::app);
	string s;
	bool flag = false, suc = false;
	while (getline(reading1, s)) {
		if (s.size() > 14) {
			if (s.substr(14) == n) {
				flag = true;
				suc = true;
				continue;
			}
		}
		if (flag) {
			while (s != "}") {
				if (empty == true) {
					getline(reading1, s);
					getline(reading1, s);
					getline(reading1, s);
					break;
				}
				getline(reading1, s);
				if (s == "{") {
					getline(reading1, s);
					while (s != "}") {
						string item_name = s.substr(11);
						getline(reading1, s);
						s = s.substr(15);
						int qunt = atoi(s.c_str());
						Edit2(item_name, -qunt);
						getline(reading1, s);
					}
				}
			}
			getline(reading1, s);
			flag = false;
			continue;
		}
		record << s << "\n";
	}
	if (suc == true) {
		cout << "Order successefully deleted! " << "\n" << "\n";
	}
	else {
		cout << "Choosen order not found! " << "\n" << "\n";
	}
}




void ClearItems() {


	//the function deletes one item of your choice 
	//or all products at once from "Items.txt"


	int status, n, i = 1;
	string s;
	Clone("Items.txt", "Items_Clone.txt");
	ifstream reading("Items_Clone.txt");
	ifstream read1("Items_Clone.txt");
	cout << "Items list: " << "\n";
	while (getline(read1, s)) {
		if (i % 4 == 1) {
			cout << s.substr(11) << "\n";
		}
		i++;
	}
	cout << "\n" << "What do you want to do? " << "\n"
		<< "(1) Delete 1 item" << "\n"
		<< "(2) Clear all items" << "\n"
		<< "(0) Exit " << "\n"
		<< "Your choise: ";
	cin >> status;
	if (status == 1) {
		ofstream record("Items.txt", ios::out);
		int j = 0, k = 1;
		bool flag = false, flag2 = false;
		string itname;
		cout << "Enter item name: ";
		cin >> itname;
		while (getline(reading, s)) {
			k++;
			if (s.substr(11) == itname) {
				flag = true;
				flag2 = true;
			}
			if (flag) {
				j++;
				if (j == 4) {
					cout << "Item deleted! " << "\n" << "\n";
					flag = false;
					continue;
				}
				continue;
			}
			if (i == k && flag2 == false) {
				cout << "You want to delete nonexistent! " << "\n" << "\n";
			}

			record << s << "\n";
		}
	}
	if (status == 2) {
		ofstream record("Items.txt", ios::out);
		cout << "All items deleted!" << "\n" << "\n";
	}
	if (status == 0) {
		cout << "Exit..." << "\n" << "\n";
		return;
	}
}



void ViewItems() {


	//The function allows you to conveniently view a list of all things from the catalog "Items.txt".
	//It offers us filtering by price, category and quantity.
	//Also filtering can be omitted


	string name, price_s, quantity_s;
	int price;
	string category;
	int quantity;
	string s, cond, dig, filtering = "a", sorting = "a", actual_file = "Items.txt", fp = "a", fc = "a", fq = "a";;
	int n = 0, digit = 0;
	cout << "Do you want to filter item list? (y/n)" << "\n";
	while (filtering != "y" && filtering != "n") {
		cout << "Your choise: ";
		cin >> filtering;
	}
	if (filtering == "y") {
		cout << "Choose filtering types: " << "\n" << "\n"
			<< "Apply filtering by price (y/n)? " << "\n";
		while (fp != "y" && fp != "n") {
			cout << "Your choise: ";
			cin >> fp;
		}
		cout << "Apply filtering by category (y/n)?" << "\n";
		while (fc != "y" && fc != "n") {
			cout << "Your choise: ";
			cin >> fc;
		}
		cout << "Apply filtering by quantity (y/n)?" << "\n";
		while (fq != "y" && fq != "n") {
			cout << "Your choise: ";
			cin >> fq;
		}
		if (fp == "y") {
			ifstream read(actual_file);
			actual_file = "Items_fp.txt";
			ofstream record(actual_file, ios::out);
			cout << "Enter filtering by price condition (examples: =500 ; >200 ; <100)" << "\n"
				<< "Your choise: ";
			cin >> cond;
			s = cond[0];
			dig = cond.substr(1);
			digit = atoi(dig.c_str());
			while (getline(read, name)) {
				getline(read, price_s);
				price_s = price_s.substr(12);
				price = atoi(price_s.c_str());
				getline(read, category);
				getline(read, quantity_s);
				quantity_s = quantity_s.substr(15);
				quantity = atoi(quantity_s.c_str());
				if (s == "=") {
					if (price == digit) {
						record <<name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
				if (s == ">") {
					if (price > digit) {
						record << name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
				if (s == "<") {
					if (price < digit) {
						record << name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
			}
		}
		if (fc == "y") {
			cout << "Choose category from available ones:" << "\n";
			ifstream read1(actual_file);
			set <string> S;
			while (getline(read1, s)) {
				getline(read1, s);
				getline(read1, s);
				if (S.find(s) == S.end()) {
					cout << s.substr(15) << "\n";
				}
				S.insert(s);
				getline(read1, s);
			}
			cout << "\n" << "Your choise: ";
			ifstream read(actual_file);
			actual_file = "Items_fc.txt";
			ofstream record(actual_file, ios::out);
			cin >> cond;
			while (getline(read, name)) {
				getline(read, price_s);
				getline(read, category);
				getline(read, quantity_s);
				quantity = atoi(quantity_s.c_str());
				if (category.substr(15) == cond) {
					record << name << "\n"
						<< price_s << "\n"
						<< category << "\n"
						<< quantity_s << "\n";
				}
			}

		}
		if (fq == "y") {
			ifstream read(actual_file);
			actual_file = "Items_fq.txt";
			ofstream record(actual_file, ios::out);
			cout << "Enter filtering by quantity condition (examples: =500 ; >200 ; <100)" << "\n"
				<< "Your choise: ";
			cin >> cond;
			s = cond[0];
			dig = cond.substr(1);
			digit = atoi(dig.c_str());
			while (getline(read, name)) {
				getline(read, price_s);
				price_s = price_s.substr(12);
				price = atoi(price_s.c_str());
				getline(read, category);
				getline(read, quantity_s);
				quantity_s = quantity_s.substr(15);
				quantity = atoi(quantity_s.c_str());
				if (s == "=") {
					if (quantity == digit) {
						record << name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
				if (s == ">") {
					if (quantity > digit) {
						record << name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
				if (s == "<") {
					if (quantity < digit) {
						record << name << "\n"
							<< "Item_price: " << price << "\n"
							<< category << "\n"
							<< "Item_quantity: " << quantity << "\n";
						continue;
					}
					continue;
				}
			}
		}
	}
	ifstream read(actual_file);
	cout << "Items:" << "\n" << "\n";
	while (getline(read, s)) {
		cout << s << "\n";
		getline(read, s);
		cout << s << "\n";
		getline(read, s);
		cout << s << "\n";
		getline(read, s);
		cout << s << "\n" << "\n";
	}
	cout << "This items list saved in " << actual_file << "\n" << "\n";
}



void ViewOrders() {


	//The function conveniently displays the list of products in the console.
	//It offers filtering by price and client’s ID, 
	//but you can refuse it then everything will be displayed by default.


	string name, price_s, quantity_s;
	int price;
	string client;
	string s, s1, c, cond, dig, filtering = "a", actual_file = "Orders.txt";
	string fp = "a", fc = "a";
	int n = 0, digit = 0;
	cout << "Do you want to filter order list? (y/n)" << "\n";
	while (filtering != "y" && filtering != "n") {
		cout << "Your choise: ";
		cin >> filtering;
	}
	if (filtering == "y") {
		cout << "Choose filtering types: " << "\n" << "\n"
			<< "Apply filtering by order price (y/n)? " << "\n";
		while (fp != "y" && fp != "n") {
			cout << "Your choise: ";
			cin >> fp;
		}
		cout << "Apply filtering by client id (y/n)?" << "\n";
		while (fc != "y" && fc != "n") {
			cout << "Your choise: ";
			cin >> fc;
		}
		if (fp == "y") {
			ifstream read(actual_file);
			actual_file = "Orders_fp.txt";
			ofstream record(actual_file, ios::out);
			cout << "Enter filtering by order price condition (examples: =500 ; >200 ; <100)" << "\n"
				<< "Your choise: ";
			cin >> cond;
			c = cond[0];
			dig = cond.substr(1);
			digit = atoi(dig.c_str());
			while (getline(read, name)) {
				getline(read, client);
				ofstream temp("temp.txt");
				getline(read, s);
				while (s != "}") {
					temp << s << "\n";
					getline(read, s);
				}
				temp << s;
				temp.close();
				getline(read, price_s);
				price_s = price_s.substr(13);
				price = atoi(price_s.c_str());
				if (c == "=") {
					if (price == digit) {
						record << name << "\n"
							<< client << "\n";
						ifstream temp("temp.txt");
						while (getline(temp, s)) {
							record << s << "\n";
						}
						record << "Order_price: " << price << "\n";
						continue;
					}
					continue;
				}
				if (c == ">") {
					if (price > digit) {
						record << name << "\n"
							<< client << "\n";
						ifstream temp("temp.txt");
						while (getline(temp, s)) {
							record << s << "\n";
						}
						record << "Order_price: " << price << "\n";
						continue;
					}
					continue;
				}
				if (c == "<") {
					if (price < digit) {
						record << name << "\n"
							<< client << "\n";
						ifstream temp("temp.txt");
						while (getline(temp, s)) {
							record << s << "\n";
						}
						record << "Order_price: " << price << "\n";
						continue;
					}
					continue;
				}
			}
		}
		if (fc == "y") {
			set <string> S;
			cout << "Choose client id from all buyers:" << "\n";
			ifstream read1(actual_file);
			while (getline(read1, s)) {
				getline(read1, client);
				if (S.find(client) == S.end()) {
					cout << client.substr(11) << "\n";
				}
				S.insert(client);
				getline(read1, s);
				while (s != "}") {
					getline(read1, s);
				}
				getline(read1, s);
			}
			cout << "Your choise: ";
			cin >> cond;
			ifstream read(actual_file);
			actual_file = "Orders_fc.txt";
			ofstream record(actual_file, ios::out);
			while (getline(read, name)) {
				getline(read, client);
				getline(read, s);
				if (client.substr(11) == cond) {
					record << name << "\n"
						<< client << "\n"
						<< s << "\n";
					while (s != "}") {
						getline(read, s);
						record << s << "\n";
					}
					getline(read, s);
					record << s << "\n";
				}
				else {
					while (s != "}") {
						getline(read, s);
					}
					getline(read, s);
				}

			}
		}
	}
	ifstream read(actual_file);
	cout << "Orders:" << "\n" << "\n";
	while (getline(read, s)) {
		cout << s << "\n";
		getline(read, s);
		cout << s << "\n";
		getline(read, s);
		getline(read, s);
		while (s != "}") {
			cout << s << "\n";
			getline(read, s);
			cout << s << "\n";
			getline(read, s);
		}
		getline(read, s);
		cout << s << "\n" << "\n";
	}
	cout << "This orders list saved in " << actual_file << "\n" << "\n";
}
