#include <cstdlib>
#include "list.hpp"

template <class Type>
Node<Type>::Node(): next(NULL), prev(NULL) {}

template <class Type>
Node<Type>::Node(Type _data): next(NULL), prev(NULL),
                              data(_data) {}

template <class Type>
Node<Type>::~Node() {
    if(next != NULL)
        delete next;
}

template <class Type>
List<Type>::List(): length(0), head(NULL), tail(NULL) {}

template <class Type>
List<Type>::List(int _length): length(_length) {
	if(length > 0) {
		head = new Node<Type>;
		tail = head;
		for(int i = 1; i < length; i++) {
			tail->next = new Node<Type>;
			tail->next->prev = tail;
			tail = tail->next;
		}
	} else {
		head = NULL;
		tail = NULL;
		length = 0;
	}
}

template <class Type>
List<Type>::~List() {
    delete head;
}

template <class Type>
int List<Type>::size() {
	return length;
}

template <class Type>
void List<Type>::add(Type data) {
	if(length > 0) {
		Node<Type>* newNode = new Node<Type>(data);
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	} else if(length == 0) {
		head = new Node<Type>(data);
		tail = head;
	}
	length++;
}

template <class Type>
void List<Type>::insert(int i, Type data) {
	if(length > 0) {
		Node<Type>* newNode = new Node<Type>(data);
		Node<Type>* counter = NULL;
		if(i < length / 2 && i >= 0) {
			counter = head;
			for(int j = 0; j < i; j++)
				counter = counter->next;
		} else if(i >= length / 2 && i < length) {
			counter = tail;
			for(int j = length - 1; j > i; j--)
				counter = counter->prev;
		} else 
			return;
		
		counter->prev = newNode;
		newNode->next = counter;
		if(i == 0)
			head = newNode;
		else if(i == length - 1)
			tail = newNode;
		length++;
	}
}

template <class Type>
Type List<Type>::remove(int i) {
	if(length > 0 && i >= 0 && i < length) {
		Node<Type>* counter = NULL;
		if(i < length / 2 && i >= 0) {
			counter = head;
			for(int j = 0; j < i; j++)
				counter = counter->next;
		} else if(i >= length / 2 && i < length) {
			counter = tail;
			for(int j = length - 1; j > i; j--)
				counter = counter->prev;
		}
		if(counter != NULL) {
			Node<Type>* prev = counter->prev;
			Node<Type>* next = counter->next;
			if(prev != NULL)
				prev->next = next;
			else
				head = counter->next;
			if(next != NULL)
				next->prev = prev;
			else
				tail = counter->prev;
				
			counter->next = NULL;
            Type data = counter->data;
			delete counter;
			length--;
            return data;
		}
	}
}

template <class Type>
Type& List<Type>::operator [](int i) {
	Node<Type>* counter;
	if(i < length / 2 && i >= 0) {
		counter = head;
		for(int j = 0; j < i; j++)
			counter = counter->next;
	} else if(i >= length / 2 && i < length) {
		counter = tail;
		for(int j = length - 1; j > i; j--)
			counter = counter->prev;
	}
	
	return counter->data;
}

template <class Type>
Iterator<Type>::Iterator(): node(NULL) {}

template <class Type>
Iterator<Type>::Iterator(List<Type>* list, int startPos) {
	if(startPos <= list->size() / 2 && startPos >= 0) {
        node = list->head;
        for(int i = 0; i < startPos; i++)
            node = node->next;
    } else if(startPos > list->size() / 2 && startPos < list->size()) {
        node = list->tail;
        for(int i = 0; i < startPos - list->size(); i++)
            node = node->prev;
    } else
        node = NULL;
}

template <class Type>
Iterator<Type>::~Iterator() {}

template <class Type>
Type& Iterator<Type>::get() {
	return node->data;
}

template <class Type>
void Iterator<Type>::next() {
	if(node != NULL)
		node = node->next;
}

template <class Type>
bool Iterator<Type>::valid() {
	return node != NULL;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator =(Iterator<Type> other) {
	this->node = other.node;
	return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator +(int i) {
    Iterator<Type> retVal = *this;
    for(int j = 0; j < i && retVal.node != NULL; j++)
        retVal.node = retVal.node->next;
    return retVal;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator -(int i) {
    Iterator<Type> retVal = *this;
    for(int j = 0; j < i && retVal.node != NULL; j++)
        retVal.node = retVal.node->prev;
    return retVal;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator +=(int i) {
    *this = *this + i;
    return *this;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator -=(int i) {
    *this = *this - i;
    return *this;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator ++() {
    *this += 1;
    return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator ++(int dummy) {
    Iterator<Type> retVal = *this;
    ++(*this);
    return retVal;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator --() {
    *this -= 1;
    return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator --(int dummy) {
    Iterator<Type> retVal = *this;
    --(*this);
    return retVal;
}
