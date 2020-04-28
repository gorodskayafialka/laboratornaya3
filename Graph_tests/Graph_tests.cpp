#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../List.cpp"
#include "../functions.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Graphtests
{
	TEST_CLASS(Graphtests)
	{
	public:
		
		TEST_METHOD(Test_Correct_work1)
		{
			string filename1 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem1.txt", filename2 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem1.2.txt", result;
			int price;
			string test = "The cheapest way to travel from Moscow to London is: Moscow-Paris-London";
			List* cities = reading_cities(filename1);
			int** Prices = reading_prices(cities, filename1);
			algorithm(Prices, cities->get_size(), cities, filename2, result, price);
			Assert::AreEqual(price, 5);
			Assert::AreEqual(result, test);
		}

		TEST_METHOD(Test_Correct_work2)
		{
			string filename1 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem2.txt", filename2 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem2.2.txt", result;
			int price;
			string test = "No way to travel from Moscow to Paris";
			List* cities = reading_cities(filename1);
			int** Prices = reading_prices(cities, filename1);
			algorithm(Prices, cities->get_size(), cities, filename2, result, price);
			Assert::AreEqual(price, -1);
			Assert::AreEqual(result, test);
		}

		TEST_METHOD(wrong_price)
		{
			string filename1 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem3.txt";
			string test = "No way to travel from Moscow to Paris";
			List* cities = reading_cities(filename1);
			try
			{
				int** Prices = reading_prices(cities, filename1);
			}
			catch (std::invalid_argument e)
			{
				Assert::AreEqual("wrong price", e.what());
			}
		}

		TEST_METHOD(wrong_city)
		{
			string filename1 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem2.txt", filename2 = "C:\\Users\\Prog\\source\\repos\\Floyd-Warshall_algorithm\\Graph_tests\\problem2.3.txt", result;
			int price;
			string test = "No way to travel from Moscow to Paris";
			List* cities = reading_cities(filename1);
			int** Prices = reading_prices(cities, filename1);
			try
			{
				algorithm(Prices, cities->get_size(), cities, filename2, result, price);
			}
			catch (std::invalid_argument e)
			{
				Assert::AreEqual("wrong city(ies)", e.what());
			}
		}
	};
}
