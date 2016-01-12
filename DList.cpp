#include <iostream>


template <typename T>
struct Node
{
	Node<T> *next;
	Node<T> *prev;
	T data;
};

template<typename T>
class List
{
private:
	Node<T> *head;
	Node<T> *tail;
	unsigned size;
	void exchange(Node<T> *first, Node<T> *second);

public:
	List();
	~List();
	void insertHead(T item);
	void insertTail(T item);
	void insertIndex(unsigned index, T item);
	void deleteHead();
	void deleteTail();
	void deleteIndex(unsigned index);
	void deleteData(T item);
	void removeAll();
	Node<T> *search(T item);
	Node<T> *searchIndex(unsigned index);
	void sort();
	void show();
	bool isEmpty() { return size == 0; }

};

template<typename T>
List<T>::List()
{
	head = new Node<T>();
	tail = new Node<T>();
	size = 0;

	head->next = tail;
	head->prev = head;

	tail->prev = head;
	tail->next = tail;
}

template<typename T>
List<T>::~List()
{
	removeAll();

	delete head;
	delete tail;

}

template<typename T>
void List<T>::insertHead(T item)
{
	Node<T> *newNode = new Node<T>();

	newNode->data = item;

	newNode->next = head->next;
	newNode->prev = head;

	head->next->prev = newNode;
	head->next = newNode;

	size++;
}

template<typename T>
void List<T>::insertTail(T item)
{
	Node<T> *newNode = new Node<T>();

	newNode->data = item;

	newNode->next = tail;
	newNode->prev = tail->prev;

	tail->prev->next = newNode;
	tail->prev = newNode;

	size++;
}

template<typename T>
void List<T>::insertIndex(unsigned index, T item)
{
	if (index > size)
	{
		std::cout << "Index is wrong" << std::endl;
	}

	Node<T> *indexNode = head;

	for (int i = 0; i < index - 1; i++)
		indexNode = indexNode->next;

	Node<T> *newNode = new Node<T>();

	newNode->data = item;

	newNode->next = indexNode->next;
	newNode->prev = indexNode;

	indexNode->next->prev = newNode;
	indexNode->next = newNode;

	size++;

}

template<typename T>
void List<T>::deleteHead()
{
	if (isEmpty())
		return;

	Node<T> *deleteNode = head->next;

	head->next = deleteNode->next;
	head->next->prev = head;

	delete deleteNode;

	size--;
}

template<typename T>
void List<T>::deleteTail()
{
	if (isEmpty())
		return;

	Node<T> *deleteNode = tail->prev;

	tail->prev = deleteNode->prev;
	tail->prev->next = tail;

	delete deleteNode;

	size--;
}

template<typename T>
void List<T>::deleteIndex(unsigned index)
{
	Node<T> *deleteNode = searchIndex(index);

	if (deleteNode == nullptr)
	{
		std::cout << "Index is wrong" << std::endl;
		return;
	}

	deleteNode->next->prev = deleteNode->prev;
	deleteNode->prev->next = deleteNode->next;

	delete deleteNode;
	size--;
}

template<typename T>
void List<T>::deleteData(T item)
{
	Node<T> *deleteNode = head->next;

	while (deleteNode != tail)
	{
		if (deleteNode->data == item)
		{
			deleteNode->next->prev = deleteNode->prev;
			deleteNode->prev->next = deleteNode->next;

			delete deleteNode;
			size--;

			return;
		}

		deleteNode = deleteNode->next;
	}

	std::cout << "This list have not " << item << std::endl;
}

template<typename T>
void List<T>::removeAll()
{
	Node<T> *deleteNode = head->next;
	Node<T> *temp;

	for (int i = 0; i < size; i++)
	{
		temp = deleteNode->next;

		delete deleteNode;

		deleteNode = temp;
	}

	head->next = tail;
	tail->prev = head;
	size = 0;
}

template <typename T>
Node<T> *List<T>::search(T item)
{
	Node<T> *searcher = head->next;

	while (searcher != tail)
	{
		if (searcher->data == item;)
			return searcher;

		searcher = searcher->next;
	}

	return nullptr;
}

template <typename T>
Node<T> *List<T>::searchIndex(unsigned index)
{
	if (index > size)
		return nullptr;

	Node<T> *searcher = head;

	for (int i = 0; i < index; i++)
		searcher = searcher->next;

	return searcher;
}

template<typename T>
void List<T>::sort()
{
	Node<T> *first;
	Node<T> *second;

	for (int i = 1; i <= size - 1; i++)
	{
		first = searchIndex(i);

		for (int j = i + 1; j <= size; j++)
		{
			second = searchIndex(j);

			if (first->data > second->data)
			{
				exchange(first, second);

				first = second;
			}
		}
	}
}

template<typename T>
void List<T>::exchange(Node<T> *first, Node<T> *second)
{
	Node<T> *temp = nullptr;

	if (first->next == second)
	{
		second->prev = first->prev;
		second->prev->next = second;

		first->next = second->next;
		first->next->prev = first;

		second->next = first;
		first->prev = second;
	}
	else
	{
		first->next->prev = second;
		second->prev->next = first;

		first->prev->next = second;
		second->next->prev = first;

		temp = first->next;
		first->next = second->next;
		second->next = temp;

		temp = first->prev;
		first->prev = second->prev;
		second->prev = temp;
	}
}

template <typename T>
void List<T>::show()
{
	Node<T> *showNode = head->next;

	for (int i = 0; i < size; i++)
	{
		std::cout << showNode->data << std::endl;

		showNode = showNode->next;
	}
}


int main()
{
	List<int> list;


	list.insertHead(5);


	list.insertHead(3);
	list.insertTail(4);
	list.insertHead(9);

	list.insertIndex(3, 99);

	list.deleteData(99);

	//list.deleteIndex(1000);

	//list.sort();

	list.show();

	return 0;
}
