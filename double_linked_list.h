#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <iostream>

/**
 *  Double_Linked_List
 *
 *  Implementation of a double Linked List with template and iterator.
 *
 *  @author youzp.
 */
template<typename T>
class CDoubleLinkedList
{
private:
    struct Node;

public:
    CDoubleLinkedList();
    ~CDoubleLinkedList();

    bool empty();
    size_t size();
    void clear();
    void push_back(const T &);
    void push_front(const T &);
    void pop_back();
    void pop_front();

    void print_list();

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    Iterator find(const T &) const;

    class Iterator
    {
    public:
        explicit Iterator(Node* node);
        Node* node() const;
        T& Value() const;
        bool Valid() const;
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

    private:
        Node* m_pNode;
    };

private:
    void InsertNodeBeforePosition(const T&, const Iterator& position);
    void RemoveNodeAtPosition(const Iterator& position);

private:
    struct Node
    {
        Node *pPrev;
        Node *pNext;
        T value;
    };

    Node *m_pHeadNode;
    Node *m_pTailNode;

    size_t m_NodeSize;
};

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline CDoubleLinkedList<T>::Iterator::Iterator(Node* node):m_pNode(node) {}

template<typename T>
inline bool CDoubleLinkedList<T>::Iterator::Valid() const
{
    return (m_pNode != NULL);
}

template<typename T>
inline T& CDoubleLinkedList<T>::Iterator::Value() const
{
    assert(Valid());
    return (m_pNode->value);
}

template<typename T>
typename CDoubleLinkedList<T>::Node* CDoubleLinkedList<T>::Iterator::node() const
{
    return m_pNode;
}

template<typename T>
typename CDoubleLinkedList<T>::Iterator& CDoubleLinkedList<T>::Iterator::operator++()
{
    assert(Valid());
    if (m_pNode->pNext != NULL)
    {
        m_pNode = m_pNode->pNext;
    }
    return *this;
}

template<typename T>
typename CDoubleLinkedList<T>::Iterator& CDoubleLinkedList<T>::Iterator::operator--()
{
    assert(Valid());
    if (m_pNode->pPrev != NULL)
    {
        m_pNode = m_pNode->pPrev;
    }
    return *this;
}

template<typename T>
inline bool CDoubleLinkedList<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (rhs.m_pNode == this->m_pNode);
}

template<typename T>
inline bool CDoubleLinkedList<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return (rhs.m_pNode != this->m_pNode);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
template<typename T>
typename CDoubleLinkedList<T>::Iterator CDoubleLinkedList<T>::begin() const
{
    return Iterator(m_pHeadNode->pNext);
}

template<typename T>
typename CDoubleLinkedList<T>::Iterator CDoubleLinkedList<T>::end() const
{
    return Iterator(m_pTailNode);
}

template<typename T>
typename CDoubleLinkedList<T>::Iterator CDoubleLinkedList<T>::find(const T& value) const
{
    Iterator it = this->begin();
    for (; it != this->end(); ++it)
    {
        if (value == it.Value())
        {
            return it;
        }
    }
    return it;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
template<typename T>
CDoubleLinkedList<T>::CDoubleLinkedList()
{
    m_pHeadNode = new Node();
    m_pTailNode = new Node();

    m_pHeadNode->pNext = m_pTailNode;
    m_pHeadNode->pPrev = NULL;

    m_pTailNode->pNext = NULL;
    m_pTailNode->pPrev = m_pHeadNode;

    m_NodeSize = 0;
}

template<typename T>
CDoubleLinkedList<T>::~CDoubleLinkedList()
{
    m_pHeadNode->pNext = NULL;
    m_pHeadNode->pPrev = NULL;

    m_pTailNode->pNext = NULL;
    m_pTailNode->pPrev = NULL;

    if (m_pHeadNode)
    {
        delete m_pHeadNode;
        m_pHeadNode = NULL;
    }

    if (m_pTailNode)
    {
        delete m_pTailNode;
        m_pTailNode = NULL;
    }

    m_NodeSize = 0;
}

template<typename T>
bool CDoubleLinkedList<T>::empty()
{
    if ((m_pTailNode == m_pHeadNode->pNext) && (m_pHeadNode == m_pTailNode->pPrev))
    {
        return true;
    }

    return false;
}

template<typename T>
size_t CDoubleLinkedList<T>::size()
{
    return m_NodeSize;
}

template<typename T>
void CDoubleLinkedList<T>::clear()
{
    if (empty())  return;

    for (Iterator it = this->begin(); it != this->end(); ++it)
    {
        Node* pCurrentNode = it.node();
        delete pCurrentNode;
        pCurrentNode = NULL;
    }

    m_pHeadNode->pNext = m_pTailNode;
    m_pTailNode->pPrev = m_pHeadNode;

    m_NodeSize = 0;
}

template<typename T>
void CDoubleLinkedList<T>::push_back(const T& value)
{
    Iterator iter(m_pTailNode);
    InsertNodeBeforePosition(value, iter);
}

template<typename T>
void CDoubleLinkedList<T>::push_front(const T& value)
{
    Iterator iter(m_pHeadNode->pNext);
    InsertNodeBeforePosition(value, iter);
}

template<typename T>
void CDoubleLinkedList<T>::pop_back()
{
    Iterator iter(m_pTailNode->pPrev);
    RemoveNodeAtPosition(iter);
}

template<typename T>
void CDoubleLinkedList<T>::pop_front()
{
    Iterator iter(m_pHeadNode->pNext);
    RemoveNodeAtPosition(iter);
}

template<typename T>
void CDoubleLinkedList<T>::print_list()
{
    std::cout << "***Begin to print list***" << std::endl;
    for (Iterator it = this->begin(); it != this->end(); ++it)
    {
        std::cout << "value=" << it.Value() << std::endl;
    }
}

template<typename T>
void CDoubleLinkedList<T>::InsertNodeBeforePosition(const T& value, const Iterator& position)
{
    Node *pNewNode = new Node();
    Node *pCurNode = position.node();

    pNewNode->pNext = pCurNode;
    pNewNode->pPrev = pCurNode->pPrev;
    pCurNode->pPrev = pNewNode;
    pNewNode->pPrev->pNext = pNewNode;

    pNewNode->value = value;

    ++m_NodeSize;
}

template<typename T>
void CDoubleLinkedList<T>::RemoveNodeAtPosition(const Iterator& position)
{
    Node *pCurNode = position.node();

    pCurNode->pNext->pPrev = pCurNode->pPrev;
    pCurNode->pPrev->pNext = pCurNode->pNext;

    delete pCurNode;
    pCurNode = NULL;
    --m_NodeSize;
}

#endif
