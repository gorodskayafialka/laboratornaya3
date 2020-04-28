#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "functions.h"

using namespace std;

void printing_matrix(int** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}


void results(int** Prices, int** Middle_points, int n, string filename, string& result, int& price, List* cities)
{
	string city_A, city_B;
	int index_1 = -1, index_2 = -1, index_3 = -1;
	cout << "The adjacency matrix after the algorithm (-1 means no route): " << endl;
	printing_matrix(Prices, n);
	fstream f;
	f.open(filename, ios::in);
	if (f.bad() != 0)
	{
		try
		{

			throw exception("trouble with file");
		}
		catch (const exception & err)
		{
			cout << "Experiencing trouble with opening the 'reading' file";
		}
	}
	getline(f, city_A);
	getline(f, city_B);
	index_1 = cities->get_index(city_A);
	index_2 = cities->get_index(city_B);
	if ((index_1 == -1) || (index_2 == -1))
	{
		try
		{

			throw invalid_argument("wrong city(ies)");
		}
		catch (const invalid_argument & err)
		{
			cout << city_A << " and/or " << city_B << " is not in the list of cities";
			return;
		}
	}
	if (Middle_points[index_1][index_2] == -1)
		result = "No way to travel from " + city_A + " to " + city_B;
	else
	{
		result = "The cheapest way to travel from " + city_A + " to " + city_B + " is: ";
		index_3 = index_1;
		while (index_3 != index_2)
		{
			result = result + cities->at(index_3) + "-";
			index_3 = Middle_points[index_3][index_2];
		}
		result = result + cities->at(index_3);
	}
	price = Prices[index_1][index_2];
	cout << result;
	if (price != -1)
		cout << endl << "The price would be: " << price;
}


void algorithm(int** Prices, int n, List* cities, string filename, string& result, int& price)
{
	int** Middle_points = new int* [n];
	for (int i = 0; i < n; i++)
	{
		Middle_points[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Prices[i][j] != -1)
				Middle_points[i][j] = j;
			else
				Middle_points[i][j] = -1;

		}
	}
	cout << "The adjacency matrix before the algorithm (-1 means no route): " <<endl;
	printing_matrix(Prices, n);
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (((Prices[i][k] + Prices[k][j] < Prices[i][j]) || (Prices[i][j] == -1)) && (Prices[k][j] != -1) && (Prices[i][k] != -1))
				{
					Prices[i][j] = Prices[i][k] + Prices[k][j];
					Middle_points[i][j] = Middle_points[i][k];
				}
			}
		}
	}
	results(Prices, Middle_points, n, filename, result, price, cities);
}

int** reading_prices(List* cities, string filename1)
{
	int n = cities->get_size();
	int** Prices = new int* [n];
	for (int i = 0; i < n; i++)
	{
		Prices[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				Prices[i][j] = 0;
			else
				Prices[i][j] = -1;
		}
	}
	fstream f;
	f.open(filename1, ios::in);
	if (f.bad() != 0)
	{
		try
		{
			throw exception("trouble with file");
		}
		catch (const exception & err)
		{
			cout << "Experiencing trouble with opening the 'reading' file";
		}
	}
	string token[4];
	int index1, index2;
	int price1, price2;
	while (!f.eof())
	{
		getline(f, token[0], ';');
		getline(f, token[1], ';');
		getline(f, token[2], ';');
		getline(f, token[3]);
		index1 = cities->get_index(token[0]);
		index2 = cities->get_index(token[1]);
		if (token[2] == "N/A")
			price1 = -1;
		else
		{
			price1 = stoi(token[2]);
			if (price1 <= 0)
			{
				try
				{
					throw invalid_argument("wrong price");
				}
				catch (const invalid_argument & err)
				{
					cout << "Only a positive number can be a price";
					return nullptr;
				}
			}
		}
		if (token[3] != "N/A")
		{
			price2 = stoi(token[3]);
			if (price2 <= 0)
			{
				try
				{
					throw invalid_argument("wrong price");
				}
				catch (const invalid_argument & err)
				{
					cout << "Only a positive number can be a price";
					return nullptr;
				}
			}
		}
		else
			price2 = -1;
		Prices[index1][index2] = price1;
		Prices[index2][index1] = price2;
	}
	f.close();
	return Prices;
}

List* reading_cities(string filename1)
{
	List* cities = new List;
	fstream f;
	f.open(filename1, ios::in);
	if (f.bad() != 0)
	{
		try
		{

			throw exception("trouble with file");
		}
		catch (const exception & err)
		{
			cout << "Experiencing trouble with opening the 'reading' file";
		}
	}
	string city;
	int counter = 0;
	while (!f.eof())
	{
		if (counter < 2)
		{
			getline(f, city, ';');
			if (cities->get_index(city) == -1)
				cities->push_back(city);
			counter++;
		}
		else
		{
			getline(f, city);
			counter = 0;
		}
	}
	f.close();
	return cities;
}

