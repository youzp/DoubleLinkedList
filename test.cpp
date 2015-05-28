#include "double_linked_list.h"
#include <assert.h>
#include <iostream>

using namespace std;

void TestInt()
{
    CDoubleLinkedList<int> oList;
    assert(true == oList.empty());

    oList.push_back(11);
    oList.push_back(22);
    oList.push_back(33);

    assert(false == oList.empty());
    assert(3 == oList.size());
    oList.print_list();

    CDoubleLinkedList<int>::Iterator iter1 = oList.find(22);
    assert(iter1 != oList.end());

    CDoubleLinkedList<int>::Iterator iter2 = oList.find(99);
    assert(iter2 == oList.end());

    oList.push_front(44);
    assert(4 == oList.size());
    oList.print_list();

    oList.pop_back();
    assert(3 == oList.size());
    oList.print_list();

    oList.pop_front();
    assert(2 == oList.size());
    oList.print_list();

    oList.pop_back();
    assert(1 == oList.size());
    oList.print_list();

    oList.clear();
    assert(0 == oList.size());
    oList.print_list();
}

void TestString()
{
    CDoubleLinkedList<string> oList;
    assert(true == oList.empty());

    oList.push_back("111");
    oList.push_back("222");
    oList.push_back("333");

    assert(false == oList.empty());
    assert(3 == oList.size());

    oList.print_list();

    CDoubleLinkedList<string>::Iterator iter1 = oList.find("222");
    assert(iter1 != oList.end());

    CDoubleLinkedList<string>::Iterator iter2 = oList.find("999");
    assert(iter2 == oList.end());

    oList.push_front("444");
    assert(4 == oList.size());
    oList.print_list();

    oList.pop_back();
    assert(3 == oList.size());
    oList.print_list();

    oList.pop_front();
    assert(2 == oList.size());
    oList.print_list();

    oList.pop_back();
    assert(1 == oList.size());
    oList.print_list();

    oList.clear();
    assert(0 == oList.size());
    oList.print_list();
}

int main()
{
    TestInt();
    TestString();

    return 0;
}

