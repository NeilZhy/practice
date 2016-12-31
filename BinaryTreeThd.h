#pragma once
#include<assert.h>
#include<iostream>
using namespace std;
enum Tag
{
	THREAD,
	LINK
};
template<typename  T>
struct BinaryTreeThdNode
{
	T _data;
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;

	Tag _leftTag;
	Tag _rightTag;

	BinaryTreeThdNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template<typename T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd(const T* arr,size_t size,const T& invalid = T())
	{
		assert(arr);
		size_t index = 0;
		_root = Create(arr,index,size,invalid);         //����������������
	}
	void PrevOrderThd()                     //ǰ��������
	{
		assert(_root);
		Node* prev = _root;
		_PrevOrderThd(_root,prev);
	}
	void _PrevOrderThd(Node* root,Node*& prev)
	{
		if(root == NULL)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			return;
		if(root->_left == NULL)
		{
			root->_left = prev;
			root->_leftTag = THREAD;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_right = root;
			prev->_rightTag = THREAD;
		}

		prev = root;
		if(root->_leftTag == LINK)
			_PrevOrderThd(root->_left,prev);
		if(root->_rightTag == LINK)
			_PrevOrderThd(root->_right,prev);
	}

	void PrevOrderPrint()                  //ǰ���������Ĵ�ӡ
	{
		assert(_root);
		_PrevOrderPrint(_root);
	}

	void _PrevOrderPrint(Node* root)
	{
		Node* cur = root;
		if(root == NULL)
			return;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}
			cout<<cur->_data<<" ";
			while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				if(cur)
					cout<<cur->_data<<" ";
			}
			if(cur)
				cur = cur->_right;
		}
	}

	void InOrderThd()             //����������
	{
		assert(_root);
		Node* prev = NULL;
		_InOrderThd(_root,prev);
		prev->_right = NULL;
		prev->_rightTag = THREAD;
	}

	void _InOrderThd(Node* root,Node*& prev)      //����������     
	{
		if(root == NULL)
			return;
		//�ҵ�����ڵ�
		_InOrderThd(root->_left,prev);
		//����ڵ�Ϊ�յĽڵ����������
		if(root->_left == NULL)
		{
			root->_left = prev;
			root->_leftTag = THREAD;
		}
		
		//���ҽڵ�Ϊ�յĽڵ����������
		if(prev && prev->_right == NULL)
		{
			prev->_right = root;
			prev->_rightTag = THREAD;
		}
		prev = root;
		_InOrderThd(root->_right,prev);
	}
	void InOrderThdPrint()
	{
		assert(_root);
		_InOrderThdPrint(_root);
	}
	void _InOrderThdPrint(Node* root)          //������������ӡ
	{
		Node* cur = root;
		if(cur == NULL)
			return;
		while(cur)
		{
			//�ҵ���������ڵ�
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			//����ڵ�ֵ
			cout<<cur->_data<<" ";
			//�����ǰ������Ϊ���������ͷ������ĺ�̽ڵ�
			while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				if(cur)
					cout<<cur->_data<<" ";
			}
			//����ͷ�������������
			if(cur)
				cur = cur->_right;
		}
	}
	void InOrder()
	{
		assert(_root);
		_InOrder(_root);
		cout<<endl;
	}
	void _InOrder(Node* root)           //�������
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);

	}
public:
	Node* Create(const T* arr,size_t &index,size_t size,const T& invalid)  //����������������
	{
		Node* root = NULL;
		if(index < size && arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = Create(arr,++index,size,invalid);
			root->_right = Create(arr,++index,size,invalid);
		}
		return root;
	}
private:
	Node* _root;
};


void FunTest()
{
	int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTreeThd<int> bt(arr,sizeof(arr)/sizeof(arr[0]),'#');
	bt.InOrder();
//	bt.InOrderThd();
//	bt.InOrderThdPrint();
	bt.PrevOrderThd();
	bt.PrevOrderPrint();
}