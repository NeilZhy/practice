#pragma once
#include<assert.h>
#include<queue>
#include<stack>
#include<iostream>
using namespace std;

template<typename T>
struct BinaryTreeNode  //�����ڵ�
{
    T _data;
    BinaryTreeNode<T> *_left;
    BinaryTreeNode<T> *_right;
    BinaryTreeNode(const T& data)
        :_data(data)
        , _left(NULL)
        , _right(NULL)
    {}
};

template<typename T>
class BinaryTree
{
    typedef BinaryTreeNode<T> Node;
public:
    BinaryTree()
        :_root(NULL)
    {}
    BinaryTree(T* arr,size_t size,const T& invalid = T())
    {
        assert(arr);
        size_t index = 0;
        _root = CreateTree(arr,size,invalid,index);
    }

    BinaryTree(BinaryTree<T> &t)
    {
        assert(t._root);
        _root = _Copy(t._root);
    }
    //��ͳд��
    /*BinaryTree<T>& operator=(BinaryTree<T>& t)
    {
        if (this != &t)
        {
            Node* tmp = _Copy(t._root);
            _root = _Destroy(_root);
            _root = tmp;
        }
        return *this;
    }*/
    //�ִ�д��
    BinaryTree<T>& operator=(BinaryTree<T>& t)
    {
        if (this != &t)
        {
            BinaryTree<T> tmp(t);
            std::swap(tmp._root, _root);
        }
        return *this;
    }

    ~BinaryTree()
    {
        if (_root)
        {
            _root = _Destroy(_root);
        }
    }
public:
    size_t Size()
    {
        return _Size(_root);
    }
    size_t Depth()
    {
        return _Depth(_root);
    }

    void PreOrder()
    {
        _PreOrder(_root);
        cout << endl;
    }
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    void PostOrder()
    {
        _PostOrder(_root);
        cout << endl;
    }

    void LevelOrder()
    {
        _LevelOrder(_root);
        cout << endl;
    }

	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}

public:
	//����������
    Node* CreateTree(T* arr, size_t size, const T& invalid,size_t& index)
    {
        Node* root = NULL;
        if (index < size)
        {
            if (arr[index] != invalid)
            {
                root = new Node(arr[index]);
                root->_left = CreateTree(arr, size, invalid, ++index);
                root->_right = CreateTree(arr, size, invalid, ++index);
            }
        }
        return root;
    }
	//����������
    Node* _Copy(Node* root)
    {
        Node* cur = NULL;
        if (root)
        {
            cur = new Node(root->_data);
            cur->_left = _Copy(root->_left);
            cur->_right = _Copy(root->_right);
        }
        return cur;
    }
	//�ͷŶ������ڵ�
    Node* _Destroy(Node* root)
    {
        if (root != NULL)
        {
            root->_left = _Destroy(root->_left);
            root->_right = _Destroy(root->_right);
            delete root;
            root = NULL;
        }
        return root;
    }
	//�ݹ����������ڵ�ĸ���
    size_t _Size(Node* root)     
    {
        if (root == NULL)
            return 0;
        return _Size(root->_left) + _Size(root->_right) + 1;
    }
	//��������������
    size_t _Depth(Node* root)
    {
        size_t maxDepth = 1;
        if (root)
        {
            size_t depth = 1;
            if (root->_left)             //��Ϊ����������������
            {
                depth += _Depth(root->_left);
            }
            if (depth > maxDepth)
            {
                maxDepth = depth;
            }
            if (root->_right)          //�Ҳ�Ϊ��������������Ȼ�����+1
            {
                depth = _Depth(root->_right) + 1;
            }
            if (depth > maxDepth)
            {
                maxDepth = depth;
            }
        }
        return maxDepth;
    }
	//������ǰ������ĵݹ�ʵ��
    void _PreOrder(Node* root)
    {
        if (root)
        {
            cout << root->_data << " ";
            _PreOrder(root->_left);
            _PreOrder(root->_right);

        }
    }
    //��������������ĵݹ�ʵ��
    void _InOrder(Node* root)
    {
        if (root)
        {
            _InOrder(root->_left);
            cout << root->_data << " ";
            _InOrder(root->_right);

        }
    }
	//��������������ĵݹ�ʵ��
    void _PostOrder(Node* root)
    {
        if (root)
        {
            _PostOrder(root->_left);
            _PostOrder(root->_right);
            cout << root->_data << " ";
        }
    }
	//���������������ʵ��
    void _LevelOrder(Node* root)
    {
        queue<Node*> q;
        if (root)
            q.push(root);
        while (!q.empty())
        {
            Node* front = q.front();
            cout << front->_data << " ";
            q.pop();
            if (front->_left)
            {
                q.push(front->_left);
            }
            if (front->_right)
            {
                q.push(front->_right);
            }
        }
    }
	//�������в���ĳ��ֵ�Ľڵ�
	Node* _Find(Node* root,const T& data)
	{
		Node* cur = root;
		if(root == NULL)
			return NULL;
		if(root->_data == data)         //�ҵ��򷵻ؽڵ�
			return root;
		Node* ret = _Find(cur->_left,data);
		if(ret == NULL)
		{
			ret = _Find(cur->_right,data);
		}
		return ret;
	}
public:
	void PreOrderNonR()
	{
		_PreOrderNonR(_root);
		cout<<endl;
	}
	void InOrderNonR()
	{
		_InOrderNonR(_root);
		cout<<endl;
	}
	void PostOrderNonR()
	{
		_PostOrderNonR(_root);
		cout<<endl;
	}
public:
	//������ǰ������ķǵݹ�ʵ��
	void _PreOrderNonR(Node* root)
	{
		Node* cur = root;
		stack<Node*> s;
		while(!s.empty() || cur)
		{
			while(cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;

		}
		
	}
	//��������������ķǵݹ�ʵ��
	void _InOrderNonR(Node* root)
	{
		Node* cur = root;
		stack<Node*> s;
		while(!s.empty() || cur)
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();
			cur = top->_right;
		}
	}
	//��������������ķǵݹ�ʵ��
	void _PostOrderNonR(Node* root)
	{
		Node* cur = root;
		stack<Node*> s;
		Node* prev = NULL;
		while(!s.empty() || cur)
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout<<top->_data<<" ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
	}
public:
	size_t GetKLevelSize(size_t k)
	{
		assert(_root);
		size_t level = 1;
		size_t count = 0;
		_GetKLevelSize(_root,k,level,count);
		return count;
	}
	//��ȡ��k��ڵ�ĸ�������k���ڲ���levelʱ��count++������ֱ����������������
	void _GetKLevelSize(Node* root,size_t k,size_t level,size_t& count)
	{
		if(root == NULL)
			return;
		if(k == level)
		{
			count++;
			return;
		}
		_GetKLevelSize(root->_left,k,level+1,count);
		_GetKLevelSize(root->_right,k,level+1,count);
	}
	size_t GetLeafSize()
	{
		size_t count = 0;
		_GetLeafSize(_root,count);
		return count;
	}
	//��ȡҶ�ӽڵ㣨���ڵ������Ϊ��������Ϊ��ʱ����Ҷ������1��
	void _GetLeafSize(Node* root,size_t& count)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL)
		{
			count++;
			return;
		}
		_GetLeafSize(root->_left,count);
		_GetLeafSize(root->_right,count);
	}
	size_t SizePrev()
	{
		size_t count = 0;
		_SizePrev(_root,count);
		return count;
	}
	//�����õķ�����ȡ�������ڵ�ĸ���(��Ҫ��ջ)
	void _SizePrev(Node* root,size_t& count)
	{
		if(root == NULL)
			return;
		Node* cur = root;
		stack<Node*> s;
		while(!s.empty() || cur)
		{
			while(cur)
			{
				s.push(cur);
				count++;
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
	}
private:
    Node* _root;
};


void FunTest()
{
    int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
    int arr1[] = { 1, 2,'#', 3, '#', '#', 4, 5,'#',6 ,'#', 7,'#','#',8};

    BinaryTree<int> b1(arr,sizeof(arr)/sizeof(arr[0]),'#');
    BinaryTree<int> b6(arr1, sizeof(arr1) / sizeof(arr1[0]), '#');

    BinaryTree<int> b2(b1);
    BinaryTree<int> b3;
    b3 = b2;
    cout << b1.Size() << endl;
    cout << b2.Size() << endl;
    cout << b3.Size() << endl;
    cout << b1.Depth() << endl;
    cout << b6.Depth() << endl;
    cout<<"b1���ݹ��������->";
	b1.PreOrder();
	cout<<"b1���ݹ��������->";
    b1.InOrder();
	cout<<"b1���ݹ�������->";
    b1.PostOrder();
	cout<<"b1���������->";
    b1.LevelOrder();
	cout<<"b1���ǵݹ��������->";
	b1.PreOrderNonR();
	cout<<"b1���ǵݹ��������->";
	b1.InOrderNonR();
	cout<<"b1���ǵݹ�������->";
	b1.PostOrderNonR();
	cout<<"Find(4)?"<<endl;
	cout<<b1.Find(4)->_data<<endl;
	cout<<"GetLeafSize:"<<b1.GetLeafSize()<<endl;
	cout<<"_SizePrev:"<<b1.SizePrev()<<endl;
	cout<<"b6���ݹ��������->";
    b6.PreOrder();
	cout<<"b6���ݹ��������->";
    b6.InOrder();
	cout<<"b6���ݹ�������->";
    b6.PostOrder();
	cout<<"b6���ݹ�������->";
    b6.LevelOrder();
	cout<<"������ڵ���:"<<b6.GetKLevelSize(3)<<endl;
	cout<<"���Ĳ�ڵ���:"<<b6.GetKLevelSize(4)<<endl;
	cout<<"�����ڵ���:"<<b6.GetKLevelSize(5)<<endl;
	cout<<"GetLeafSize:"<<b6.GetLeafSize()<<endl;
	cout<<"_SizePrev:"<<b6.SizePrev()<<endl;
}