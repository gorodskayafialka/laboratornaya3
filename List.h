#pragma once
#include <string>

using namespace std;

class List
{
	void add_first(string new_element);
	void reset();
	class Node
	{
	public:
		Node(string data, Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		};
		~Node() {};
		string data;
		Node* next;
	};
	Node* head;
	Node* tail;
	size_t size;
public:
	List();
	~List();
	size_t get_size() const;
	void push_back(string new_element);
	string at(size_t index);
	void clear();
	bool isEmpty();
	int get_index(string sublist);
	void print_to_console();
};
