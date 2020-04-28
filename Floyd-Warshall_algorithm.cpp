#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "functions.h"

using namespace std;

int main()
{
	string filename1 = "source.txt", filename2 = "firstandlast.txt", result;
	int price;
	List* cities = reading_cities(filename1);
	cout << "Available cities: ";
	cities->print_to_console();
	cout << endl;
	int** Prices= reading_prices(cities, filename1);
	if (Prices!=nullptr)
		algorithm(Prices, cities->get_size(), cities, filename2, result, price);

}

