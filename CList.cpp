#include "CList.h"

void CList::Display() const
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

void CList::PushBack(int Value)
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

void CList::PushFront(int Value)
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

int CList::PopBack()
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

int CList::PopFront()
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

void CList::Clear()
{
	while (!m_Front)
	{
		PopBack();
	}
}

bool CList::IsEmpty() { return (m_Size == 0) ? true : false; }

const SNode* CList::Front() const { return m_Front; }

const SNode* CList::Back() const { return m_Back; }

int CList::Size() const { return m_Size; }

SNode* CList::At(int Index)
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

void CList::Insert(int Index, int Value)
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

void CList::Erase(int Index)
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

CList::iterator CList::begin()
{
	return iterator(m_Front);
}

CList::iterator CList::end()
{
	return iterator(nullptr);
}

CList::reverse_iterator CList::rbegin()
{
	return reverse_iterator(m_Back);
}

CList::reverse_iterator CList::rend()
{
	return reverse_iterator(nullptr);
}

CList::const_iterator CList::cbegin()
{
	return const_iterator(m_Front);
}

CList::const_iterator CList::cend()
{
	return const_iterator(nullptr);
}

CList::const_reverse_iterator CList::crbegin()
{
	return const_reverse_iterator(m_Back);
}

CList::const_reverse_iterator CList::crend()
{
	return const_reverse_iterator(nullptr);
}