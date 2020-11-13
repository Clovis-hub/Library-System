//
// Created by shadowbox on 7/16/20.
//

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H
#include <set>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Book {
public:

    Book();
    Book(string  author ,string  title);

    [[maybe_unused]] [[nodiscard]] const  string& author() const {return m_author;}

    [[maybe_unused]] [[nodiscard]] const string& title() const {return m_title;}
    void read(ifstream& inStream);
    void write(ofstream& outStream) const ;
    void borrowBook(int customerId);
    int reserveBook(int customerId);
    void unReserveBook(int customerId);
    void returnBook();
    [[nodiscard]] int bookId()const {return m_bookId;}
    [[nodiscard]] bool borrowed()const {return m_bookId;}
    [[nodiscard]] int customerId()const {return m_customerId;}
    list<int>& reservationList(){return m_reservationList;}
    static int MaxBookId;
    friend ostream& operator<<(ostream& outStream,const Book& book);

private:
    bool m_borrowed= false;
    int m_bookId{},m_customerId{};
    string m_author,m_title;
    list<int> m_reservationList;
};


#endif //LIBRARY_BOOK_H
