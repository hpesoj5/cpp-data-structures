// TODO: revamp to look more like "MyLinkedList.test.cpp"

// #include "MyVector.hpp"
// #include <exception>
// #include <iostream>
// #include <utility>

// template <typename T>
// void printVector(const MyVector<T>& v)
// {
//     std::cout << "Size: " << v.size() << "\nCapacity: " << v.capacity() << '\n';
//     v.print();

//     std::cout << '\n';
// }

// void testDefaultConstructor()
// {
//     std::cout << "\nTesting default constructor:\n";
//     MyVector<int> a;
//     printVector(a);
//     MyVector<int> b{};
//     printVector(b);
// }

// void testSizeListConstructor()
// {
//     std::cout << "\nTesting size constructor:\n";
//     MyVector<int> a(5, 2);
//     printVector(a);

//     MyVector<int> b{5, 2};
//     printVector(b);
// }

// void testCopyConstructor()
// {
//     std::cout << "\nTesting copy constructor: \n";
//     MyVector<int> a{ 1, 2, 3, 4, 5 };
//     printVector(a);

//     MyVector b{ a };
//     printVector(b);
//     printVector(a);
// }

// void testMoveConstructor()
// {
//     std::cout << "\nTesting move constructor: \n";
//     MyVector<int> a { 1, 2, 3, 4, 5 };
//     printVector(a);

//     MyVector b{ std::move(a) };
//     printVector(b);
//     printVector(a);
// }

// void testFrontBack()
// {
//     std::cout << "\nTesting front() and back():\n";
//     MyVector<int> a{ 1, 2, 3, 4, 5 };
//     printVector(a);

//     std::cout << "Front: "  << a.front() << "\nBack: " << a.back() << '\n';

//     const MyVector<int> b{ 1, 2, 3, 4, 5 };
//     printVector(b);

//     std::cout << "Front: " << b.front() << "\nBack: " << b.back() << '\n';
// }

// void testEmpty()
// {
//     std::cout << "\nTesting empty():\n";
//     std::cout << std::boolalpha;
//     MyVector<int> a;
//     printVector(a);
//     std::cout << a.empty() << '\n';

//     MyVector<int> b(1);
//     printVector(b);
//     std::cout << b.empty() << '\n';
//     std::cout << std::noboolalpha;
// }

// void testIndexing()
// {
//     std::cout << "\nTesting indexing with []:\n";

//     MyVector<int> a{ 1, 2, 3, 4, 5 };
//     int n = a.size();

//     for (int i { -n } ; i < n; ++i)
//         std::cout << a[i] << ' ';

//     try
//     {
//         std::cout << a[-n-1] << '\n';
//     }
//     catch (const std::exception& e)
//     {
//         std::cout << e.what() << '\n';
//     }

//     try
//     {
//         std::cout << a[n] << '\n';
//     }
//     catch (const std::exception& e)
//     {
//         std::cout << e.what() << '\n';
//     }
// }

// void testReserve()
// {
//     std::cout << "\nTesting reserve():\n";
//     MyVector<int> a;
//     a.reserve(5);
//     printVector(a);

//     MyVector<int> b{ 1, 2, 3, 4, 5 };
//     b.reserve(3);
//     printVector(b);

//     MyVector<int> c{ 1, 2, 3 };
//     c.reserve(6);
//     printVector(c);

//     MyVector<int> d{ 1, 2, 3 };
//     d.reserve(3);
//     printVector(d);
// }

// void testResize()
// {
//     std::cout << "\nTesting resize():\n";
//     MyVector<int> a;
//     a.resize(5);
//     printVector(a);

//     MyVector<int> e{ 1 };
//     e.resize(5);
//     printVector(e);

//     MyVector<int> b{ 1, 2, 3, 4, 5 };
//     b.resize(3);
//     printVector(b);

//     MyVector<int> c{ 1, 2, 3 };
//     c.resize(6);
//     printVector(c);

//     MyVector<int> d{ 1, 2, 3 };
//     d.resize(3);
//     printVector(d);
// }

// void testPushback()
// {
//     std::cout << "\nTesting push_back():\n";
//     MyVector<int> a;
//     printVector(a);
//     for (int i { 1 }; i <= 5; ++i)
//     {
//         a.push_back(i);
//         printVector(a);
//     }

//     MyVector<int> c;
//     printVector(c);

//     c.push_back(1);
//     printVector(c);
//     c.push_back(2);
//     printVector(c);
//     c.push_back(3);
//     printVector(c);
//     c.push_back(4);
//     printVector(c);
//     c.push_back(5);
//     printVector(c);

//     MyVector<int> b;
//     b.reserve(5);
//     printVector(b);
//     for (int i { 1 }; i <= 5; ++i)
//     {
//         b.push_back(i);
//         printVector(b);
//     }
// }

// void testPop()
// {
//     std::cout << "\nTesting pop():\n";
//     MyVector<int> a{ 1, 2, 3, 4, 5 };
//     printVector(a);

//     while (true)
//     {
//         try
//         {
//             std::cout << a.pop() << '\n';
//             printVector(a);
//         }
//         catch (const std::exception& e)
//         {
//             std::cout << e.what() << '\n';
//             break;
//         }
//     }
// }

// void testClear()
// {
//     std::cout << "\nTesting clear():\n";
//     MyVector<int> a{ 1, 2, 3, 4, 5 };
//     printVector(a);

//     a.clear();
//     printVector(a);
// }

// #endif
