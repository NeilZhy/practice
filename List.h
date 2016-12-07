#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct ListNode
{
	struct ListNode* _next;
	struct ListNode* _prev;
	T _data;
	ListNode(const T& data)
		:_data(data)
		,_next(NULL)
		,_prev(NULL)
	{}
};

template<typename T,typename Ref,typename Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListIterator<T,const T&,const T*> ConstIterator;
	typedef ListIterator<T,Ref,Ptr> Self;
	ListIterator(Node* node)
		:_node(node)
	{}

	bool operator==(const Self& x)
	{
		return _node == x._node;
	}

	bool operator!=(const Self& x)
	{
		return _node != x._node;
	}

	Ref operator*()
	{
		return (*_node)._data;
	}

	Ref operator*() const
	{
		return (*_node)._data;
	}
	Ptr operator->()
	{
		return &(*_node)._data;
	}

	Self& operator++()
	{
		_node = (*_node)._next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp = *this;
		++(*this);
		return tmp;
	}

	Self& operator--()
	{
		_node = (*_node)._prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp = *this;
		--(*this);
		return tmp;
	}

	Node* _node;
};

template<typename T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListIterator<T,const T&,const T*> ConstIterator;
public:
	Node* BuyNode(const T& data)
	{
		return new Node(data);
	}
public:
	List()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
public:
	Iterator Begin()              
	{
		return (*_head)._next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator Begin() const
	{
		return (*_head)._next;
	}

	ConstIterator End() const
	{
		return _head;
	}

public:
	void PushBack(const T& data)              //β��
	{
		Node* tmp = BuyNode(data);
		Node* tail = _head->_prev;
		tail->_next = tmp;
		tmp->_prev = tail;
		tmp->_next = _head;
		_head->_prev = tmp;
	}


	void PopBack()                //βɾ
	{
		Node* del = _head->_prev;
		Node* pre = del->_prev;
		Node* next = del->_next;

		pre->_next = next;
		next->_prev = pre;

		delete del;
	}

	void PushFront(const T& data)          //ͷ��
	{
		Node* tmp = BuyNode(data);
		Node* next = _head->_next;
		_head->_next = tmp;
		tmp->_prev = _head;

		tmp->_next = next;
		next->_prev = tmp;
	}

	void PopFront()               //ͷɾ
	{
		Node* prev = _head->_prev;
		Node* next = _head->_next;
		prev->_next = next;
		next->_prev = prev;

		_head = next;
	}

	Iterator Insert(Iterator pos,const T& data)      //ĳһ��λ��ǰ����
	{
		Node* tmp = BuyNode(data);
		Node* prev = pos._node->_prev;
		Node* cur = pos._node;
		
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;
		return tmp;
	}

	ConstIterator Insert(ConstIterator pos,const T& data)      //ĳһ��λ��ǰ����
	{
		Node* tmp = BuyNode(data);
		Node* prev = pos._node->_prev;
		Node* cur = pos._node;
		
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;
		return tmp;
	}

	Iterator Erase(Iterator pos)            //ɾ��ĳ��λ��
	{
		assert(pos._node && pos._node != _head);    //�жϽڵ��Ƿ�Ϊ�գ���ֻʣһ��ͷ�ڵ�

		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;
		delete pos._node;
		return Iterator(next);           //������һ��λ��
	}

	bool Empty()        //�ж������Ƿ�Ϊ��
	{
		return _head == _head->_next;
	}

	T& Front()
	{
		return _head->_next->_data;
	}

	T& Back()
	{
		return _head->_prev->_data;
	}

	const T& Front() const
	{
		return _head->_next->_data;
	}

	const T& Back() const
	{
		return _head->_prev->_data;
	}

	void Swap(List<T>& l)
	{
		swap(_head,l._head);
	}
	template<typename InputIterator>
	void Insert(Iterator pos,InputIterator first,InputIterator last)
	{
		while(first != last)
		{
			Insert(pos,*first);
			++first;
		}
	}

	void Insert(Iterator pos,ConstIterator first,ConstIterator last)
	{
		for(;first != last;++first)
			Insert(pos,*first);
	}
private:
	Node* _head;
};

void PrintList(List<int>& l)
{
	List<int>::Iterator it = l.Begin();
	while(it != l.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
