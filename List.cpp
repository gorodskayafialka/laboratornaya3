#include <string>
#include <stdexcept>
#include <iostream>
#include "List.h"

using namespace std;

void List::reset()//resets the list 
{
	head = nullptr;
	tail = nullptr;
};

List::List() //Constructor
{
	reset();
	size = 0;
};

List::~List()
{
	List::clear();
};

void List::add_first(string new_element)//adds the first element to an empty list
{
	head = new Node(new_element);
	tail = head;
};

size_t List::get_size() const
{
	return size;
};

void List::push_back(string new_element) // adds an element to the list's end
{
	if (size == 0) { add_first(new_element); }
	else
	{
		tail->next = new Node(new_element);
		tail = tail->next;
	}
	size++;
};

string List::at(size_t index) // returns the value of the element based on its index
{
	if ((index >= size) || (index < 0)) { throw out_of_range("Impossible index"); }
	else
	{
		size_t counter = 0;
		Node* current = head;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}
		return current->data;
	}
};
void List::clear()//delets the list
{
	Node* current = head;
	while (current != tail)
	{
		Node* Next = current->next;
		delete current;
		current = Next;
		size--;
	}
	delete current;
	size--;
	reset();
};

bool List::isEmpty() // checks if the list is empty
{
	if (size == 0) { return true; }
	else { return false; }
};

int List::get_index(string sublist)
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == sublist)
			return(counter);
		current = current->next;
		counter++;
	}
	return (-1);
}

void List::print_to_console()// prints the list to console
{
	Node* current = head;
	while (current != nullptr)
	{
		cout << current->data << " ";
		current = current->next;
	}
};
