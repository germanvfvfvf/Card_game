#pragma once
#include <iostream>

template<typename T>
class circle_list
{
public:

	circle_list()
	{
		sise = 0;
		head = nullptr;
		tail = head;
	}

	void push_front(T data)
	{
		if (head == nullptr)
		{
			head = new Node<T>(data);
			tail = head;
			current_obj = head;
			sise++;
		}
		else
		{
			Node<T>* current = tail;
			current->pNext = new Node<T>(data);
			tail = current->pNext;
			sise++;
			tail->pNext = head;
		}
		current_obj = tail;

	}
	void pop_current()
	{
		if (sise != 0)
		{
			Node<T>* temp = current_obj;
			next_object();

			while (current_obj->pNext != temp)
			{
				next_object();
			}
			current_obj->pNext = temp->pNext;
			sise--;
			delete temp;
		}
		else
		{
			current_obj->data = 0;
		}
	}

	void next_object() { current_obj = current_obj->pNext; }

	T& get_current_obj() { return current_obj->data; }

	const int get_sise() { return sise; }

	bool empty() {
		if (sise != 0)
		{
			return false;
		}
		return true;
	}

private:

	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node<T>* head;
	Node<T>* tail;
	Node<T>* current_obj = head;
	int sise;
};
