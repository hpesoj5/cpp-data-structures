// WILL HAVE A PROPER TESTING FRAMEWORK IN THE FUTURE
// ASSUMES SIZE GETTER IS IMPLEMENTED CORRECTLY
#include "MyLinkedList.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

void testDefaultConstructor()
{
    MyList<int> int_list;
    MyList<double> double_list;

    assert(int_list.size() == 0 && "testDefaultConstructor: Size of int list is not 0");
    assert(double_list.size() == 0 && "testDefaultConstructor: Size of double list is not 0");
}

void testCopyConstructorAssignment()
{
    MyList<int> int_list;
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);
    assert(int_list.size() == 3 && "testCopyConstructorAssignment: Size of original int list is not 3");

    MyList<int> int_list_copy { int_list };
    assert(int_list_copy.size() == 3 && "testCopyConstructorAssignment: Size of copy constructed int list is not 3");
    assert(int_list.size() == 3 && "testCopyConstructorAssignment: Size of original int list after copy is not 3");

    MyList<int> int_list_2;
    int_list.push_back(1);
    assert(int_list_2.size() == 1 && "testCopyConstructorAssignment: Size of original int list 2 is not 1");

    int_list_copy = int_list_2;
    assert(int_list_copy.size() == 1 && "testCopyConstructorAssignment: Size of copy assigned list is not 1");
    assert(int_list_2.size() == 1 && "testCopyConstructorAssignment: Size of original list after assignment is not 1");
}

void testMoveConstructorAssignment()
{
    MyList<int> int_list;
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);
    assert(int_list.size() == 3 && "testMoveConstructorAssignment: Size of original int list is not 3");

    MyList<int> int_list_move { std::move(int_list) };
    assert(int_list_move.size() == 3 && "testMoveConstructorAssignment: Size of copy constructed int list is not 3");
    assert(int_list.size() == 0 && "testMoveConstructorAssignment: Size of original int list after copy is not 0");

    MyList<int> int_list_2;
    int_list.push_back(1);
    assert(int_list_2.size() == 1 && "testMoveConstructorAssignment: Size of original int list 2 is not 1");

    int_list_move = std::move(int_list_2);
    assert(int_list_move.size() == 1 && "testMoveConstructorAssignment: Size of copy assigned list is not 1");
    assert(int_list_2.size() == 0 && "testMoveConstructorAssignment: Size of original list after assignment is not 0");
}

void testFrontBack()
{
    MyList<int> int_list;
    int_list.push_back(1);

    assert(int_list.front() == 1 && "testFrontBack: front of int list is not 1");
    assert(int_list.back() == 1 && "testFrontBack: back of int list is not 1");

    int_list.push_back(2);
    int_list.push_back(3);

    assert(int_list.front() == 1 && "testFrontBack: front of int list is not 1");
    assert(int_list.back() == 3 && "testFrontBack: back of int list is not 3");

    MyList<char> empty_list;
    bool front_throws {};
    bool back_throws {};

    try { empty_list.front(); } catch (const std::out_of_range& exception) { front_throws = true; }
    try { empty_list.back(); } catch (const std::out_of_range& exception) { back_throws = true; }

    assert(front_throws == true && "testFrontBack: front() did not throw on empty list");
    assert(back_throws == true && "testFrontBack: back() did not throw on empty list");
}

void testPushPop()
{
    MyList<int> int_list;

    bool pop_front_throws {};
    bool pop_back_throws {};

    try { int_list.pop_front(); } catch (const std::out_of_range& exception) { pop_front_throws = true; }
    try { int_list.pop_back(); } catch (const std::out_of_range& exception) { pop_back_throws = true; }

    assert(pop_front_throws == true && "testPushPop: pop_front() on empty list does not throw");
    assert(pop_back_throws == true && "testPushPop: pop_back() on empty list does not throw");

    int_list.push_back(2);
    int_list.push_front(1);

    assert(int_list.size() == 2 && "testPushPop: push failed to add 2 elements");
    assert(int_list.front() == 1 && "testPushPop: front element of int list is not 1");
    assert(int_list.back() == 2 && "testPushPop: back element of int list is not 2");

    int_list.push_back(3);
    assert(int_list.size() == 3 && "testPushPop: pushed failed to add 3 elements");
    assert(int_list.front() == 1 && "testPushPop: front element of int list is not 1");
    assert(int_list.back() == 3 && "testPushPop: back element of int list is not 3");

    int_list.pop_front();
    assert(int_list.size() == 2 && int_list.front() == 2 && int_list.back() == 3 && "testPushPop: pop_front() failed to pop element 1 at the front");

    int_list.pop_back();
    assert(int_list.size() == 1 && int_list.front() == 2 && int_list.back() == 2 && "testPushPop: pop_back() failed to pop element 3 at the back");

    int_list.pop_front();
    assert(int_list.size() == 0 && "testPushPop: pop_front() failed to pop element 2 at the front");
}

// void testInsert()
// {

// }

// void testErase()
// {

// }

void testClear()
{
    MyList<int> int_list;
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    assert(int_list.size() == 3 && "testClear: size of original list is not 3");

    int_list.clear();
    assert(int_list.size() == 0 && "testClear: size of cleared list is not 0");
}

void testEmpty()
{
    MyList<int> int_list;
    int_list.push_back(1);

    MyList<int> empty_list;

    assert(empty_list.empty() && "testEmpty: empty list does not return true");
    assert(!int_list.empty() && "testEmpty: non-empty list does not return false");

    int_list.pop_front();
    assert(int_list.empty() && "testEmpty: cleared list does not return true");
}

int main()
{
    testDefaultConstructor();
    testCopyConstructorAssignment();
    testMoveConstructorAssignment();
    // destructors will be tested with valgrind
    testPushPop();
    testInsert();
    testErase();
    testClear();

    testFrontBack();
    testGetSizeEmpty();

    std::cout << "All tests passed\n";
    return 0;
}
