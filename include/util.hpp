#pragma once

template <class D>
struct Node
{
	D data;
	Node* next;

	Node();
	Node(D data);
	Node(D data, Node* next);
};

template<class D>
inline Node<D>::Node() : next(nullptr)
{}

template<class D>
inline Node<D>::Node(D data)
	: data(data),
	  next(nullptr)
{
}

template<class D>
inline Node<D>::Node(D data, Node * next)
	: data(data),
	  next(next)
{
}

