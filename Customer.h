//
// Created by shadowbox on 7/16/20.
//

#ifndef LIBRARY_CUSTOMER_H
#define LIBRARY_CUSTOMER_H
#include "Book.h"

class Customer {
public:

    Customer();
    Customer(string  name,string  address);
    void read(ifstream& inStream);
    void write(ofstream& outStream) const;
    void borrowBook(int bookId);
    void reserveBook(int bookId);
    void returnBook(int bookId);
    void unReserveBook(int bookId);
    [[nodiscard]] bool hasBorrowed() const {return !m_loanSet.empty();}
    [[nodiscard]] const string& name() const { return m_name;}
    [[nodiscard]] const string& address() const {return m_address;}
    [[nodiscard]] int id() const {return m_customerId;}
    static int MaxCustomerId;
    friend ostream& operator<<(ostream& outStream,const Customer& customer);

private:
    int m_customerId{};
    string m_name,m_address;
    set<int>m_loanSet,m_reservationSet;
};


#endif //LIBRARY_CUSTOMER_H
