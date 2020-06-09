#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <set>


using namespace std;
// Definition of all functions from Functions.cpp
void ItemEntry();
void EditItem();
void CreateOrder();
void CanselOrder();
void ViewItems();
void ViewOrders();
void Clone(string from, string to);
void Edit2(string item_name, int item_quantity);
void ClearItems();
void CanselOrder2(string n, bool empty = false);