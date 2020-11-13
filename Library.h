//
// Created by shadowbox on 7/16/20.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H
#include "Book.h"
#include "Customer.h"
#include <algorithm>


class Library {
public:
    Library();

    static map<int,Customer> s_customerMap;
    static map<int,Book> s_bookMap;
private:
    static string s_binaryPath;
    static bool lookupBook(const string &author, const string &title);
    static bool lookupCustomer(const string &name, const string &address);
    static void addBook();
    static void deleteBook();
    static void listBooks();
    static void addCustomer();
    static void deleteCustomer();
    static void listCustomer();
    static void borrowBook();
    static void reserveBook();
    static void returnBook();
    static void load();
    static void save();

};


#endif //LIBRARY_LIBRARY_H
