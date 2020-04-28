#pragma once
#include <string>
#include "List.h"

using namespace std;

void algorithm(int** Prices, int n, List* cities, string filename, string& result, int& price);

int** reading_prices(List* cities, string filename1);

List* reading_cities(string filename1);


