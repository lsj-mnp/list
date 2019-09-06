#pragma once
#include <iostream>
#include <initializer_list>
#include <cassert>

#define SAFE_DELETE(a) { if(a) { delete a; a = nullptr; } }
#define MAX(a, b) { (a > b) ? a : b }
#define MIN(a, b) { (a < b) ? a : b }

struct SNode
{
	SNode() {};
	SNode(int _Value) : Value{ _Value } {};

	SNode* Next{};
	SNode* Prev{};
	int Value{};
};

class CList
{
public:
	class CListBaseIterator
	{
	public:
		CListBaseIterator(SNode* _NodePointer) : m_NodePointer{ _NodePointer } {};
		virtual ~CListBaseIterator() {};

		virtual CListBaseIterator& operator++() = 0;

		virtual bool operator!=(const CListBaseIterator& B)
		{
			return (m_NodePointer != B.m_NodePointer) ? true : false;
		}

		virtual int& operator*()
		{
			assert(m_NodePointer);
			return m_NodePointer->Value;
		}

	protected:
		SNode* m_NodePointer{};
	};

	class CListBaseConstIterator
	{
	public:
		CListBaseConstIterator(SNode* _NodePointer) : m_NodePointer{ _NodePointer } {};
		virtual ~CListBaseConstIterator() {};

		virtual CListBaseConstIterator& operator++() = 0;

		virtual bool operator!=(const CListBaseConstIterator& B)
		{
			return (m_NodePointer != B.m_NodePointer) ? true : false;
		}

		virtual const int& operator*()
		{
			assert(m_NodePointer);
			return m_NodePointer->Value;
		}

	protected:
		SNode* m_NodePointer{};
	};

	class CListIterator : public CListBaseIterator
	{
	public:
		CListIterator(SNode* _NodePointer) : CListBaseIterator(_NodePointer) {};
		~CListIterator() {};

		CListIterator& operator++() override
		{
			m_NodePointer = m_NodePointer->Next;
			return *this;
		}
	};

	class CListReverseIterator : public CListBaseIterator
	{
	public:
		CListReverseIterator(SNode* _NodePointer) : CListBaseIterator(_NodePointer) {};
		~CListReverseIterator() {};

		CListReverseIterator& operator++() override
		{
			m_NodePointer = m_NodePointer->Prev;
			return *this;
		}
	};

	class CListConstIterator : public CListBaseConstIterator
	{
	public:
		CListConstIterator(SNode* _NodePointer) : CListBaseConstIterator(_NodePointer) {};
		~CListConstIterator() {};

		CListConstIterator& operator++() override
		{
			m_NodePointer = m_NodePointer->Next;
			return *this;
		}
	};

	class CListConstReverseIterator : public CListBaseConstIterator
	{
	public:
		CListConstReverseIterator(SNode* _NodePointer) : CListBaseConstIterator(_NodePointer) {};
		~CListConstReverseIterator() {};

		CListConstReverseIterator& operator++() override
		{
			m_NodePointer = m_NodePointer->Prev;
			return *this;
		}
	};

	using iterator = CListIterator;
	using reverse_iterator = CListReverseIterator;
	using const_iterator = CListConstIterator;
	using const_reverse_iterator = CListConstReverseIterator;

public:
	CList() {};
	CList(std::initializer_list<int> IList)
	{
		const int* iter{ IList.begin() };

		while (iter != IList.end())
		{
			PushBack(*iter);

			++iter;
		}
	};
	~CList()
	{
		Clear();
	};

	void Display() const;

	void PushBack(int Value);

	void PushFront(int Value);

	int PopBack();

	int PopFront();

	void Clear();

	bool IsEmpty();

	const SNode* Front() const;

	const SNode* Back() const;

	int Size() const;

	SNode* At(int Index);

	void Insert(int Index, int Value);

	void Erase(int Index);

public:
	iterator begin();

	iterator end();

	reverse_iterator rbegin();

	reverse_iterator rend();

	const_iterator cbegin();

	const_iterator cend();

	const_reverse_iterator crbegin();

	const_reverse_iterator crend();

private:
	SNode* m_Front{};
	SNode* m_Back{};

	int m_Size{};
};
