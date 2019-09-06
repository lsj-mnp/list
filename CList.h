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

	using iterator = CListIterator;

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

	void Display() const
	{
		SNode* iter{ m_Front };

		std::cout << "Size of list\t: " << m_Size << "\n";
		std::cout << "Entries\t\t: ";

		while (iter != nullptr)
		{
			std::cout << "[" << iter->Value << "]";

			iter = iter->Next;
		}
	}

	void PushBack(int Value)
	{
		if (m_Front == nullptr)
		{
			m_Front = new SNode{ Value };

			m_Back = m_Front;
		}
		else
		{
			SNode* new_node = new SNode{ Value };

			m_Back->Next = new_node;

			new_node->Prev = m_Back;

			m_Back = new_node;
		}

		++m_Size;
	}

	void PushFront(int Value)
	{
		if (m_Front == nullptr)
		{
			m_Front = new SNode{ Value };

			m_Back = m_Front;
		}
		else
		{
			SNode* new_node = new SNode{ Value };

			m_Front->Prev = new_node;

			new_node->Next = m_Front;

			m_Front = new_node;
		}

		++m_Size;
	}

	int PopBack()
	{
		if (!m_Back) { return 0; }

		int result{ m_Back->Value };

		m_Back = m_Back->Prev;

		if (!m_Back)
		{
			SAFE_DELETE(m_Front);
		}
		else
		{
			SAFE_DELETE(m_Back->Next);
		}

		--m_Size;

		return result;
	}

	int PopFront()
	{
		if (!m_Front) { return 0; }

		int result{ m_Front->Value };

		m_Front = m_Front->Next;

		if (!m_Front)
		{
			SAFE_DELETE(m_Back);
		}
		else
		{
			SAFE_DELETE(m_Front->Prev);
		}

		--m_Size;

		return result;
	}

	void Clear()
	{
		while (!m_Front)
		{
			PopBack();
		}
	}

	bool IsEmpty() { return (m_Size == 0) ? true : false; }

	const SNode* Front() const { return m_Front; }

	const SNode* Back() const { return m_Back; }

	int Size() const { return m_Size; }

	SNode* At(int Index)
	{
		Index = MIN(Index, m_Size - 1);
		Index = MAX(Index, 0);

		SNode* iter{ m_Front };

		for (int i = 0; i < Index; ++i)
		{
			iter = iter->Next;
		}

		return iter;
	}

	void Insert(int Index, int Value)
	{
		SNode* at{ At(Index) };

		if (Index >= m_Size) { at = nullptr; }

		if (at == m_Front)
		{
			PushFront(Value);

			return;
		}
		else if (at == nullptr)
		{
			PushBack(Value);

			return;
		}
		else
		{
			SNode* new_node = new SNode{ Value };

			at->Prev->Next = new_node;

			new_node->Prev = at->Prev;

			new_node->Next = at;

			at->Prev = new_node;

			++m_Size;
		}
	}

	void Erase(int Index)
	{
		SNode* at{ At(Index) };

		if (at == m_Front)
		{
			PopFront();

			return;
		}
		else if (at == m_Back)
		{
			PopBack();

			return;
		}
		else if (at == nullptr)
		{
			return;
		}
		else
		{
			at->Prev->Next = at->Next;

			at->Next->Prev = at->Prev;

			SAFE_DELETE(at);

			--m_Size;
		}
	}

public:
	iterator begin()
	{
		return iterator(m_Front);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

private:
	SNode* m_Front{};
	SNode* m_Back{};

	int m_Size{};
};
