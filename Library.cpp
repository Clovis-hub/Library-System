//
// Created by shadowbox on 7/16/20.
//

#include "Library.h"

string Library::s_binaryPath("Library.bin");
map<int,Book>Library::s_bookMap;
map<int,Customer>Library::s_customerMap;

Library::Library(){
    load();
    bool quit=false;
    while(!quit){
        cout << "1. Add Book" << endl
             << "2. Delete Book" << endl
             << "3. List Books" << endl
             << "4. Add Customer" << endl
             << "5. Delete Customer" << endl
             << "6. List Customers" << endl
             << "7. Borrow Book" << endl
             << "8. Reserve Book" << endl
             << "9. Return Book" << endl
             << "0. Quit" << endl
             << ": ";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                listBooks();
                break;
            case 4:
                addCustomer();
                break;
            case 5:
                deleteCustomer();
                break;
            case 6:
                listCustomer();
                break;
            case 7:
                borrowBook();
                break;
            case 8:
                reserveBook();
                break;
            case 9:
                returnBook();
                break;
            case 0:
                quit= true;
                break;
            default:
                cout<<"error"<<endl;
        }
        cout<<endl;
    }
save();
}
bool Library::lookupBook(const string &author, const string &title) {
    return false;
}

bool Library::lookupCustomer(const string &name, const string &address) {
    return false;
}

void Library::addBook() {
    string author{"\n"};
    cout << "Author: ";
    cin>>author;

    string title;
    cout << "Title: ";
    cin>>title;
if (lookupBook(author, title)){
    cout<<endl<<"The Book  "<<title<<" by "<<author<<"already exists."<<endl;
    return;
}
Book book(author, title);
s_bookMap[book.bookId()]= book;
cout << endl << "Added." << endl;
}

void Library::deleteBook() {
    string author;
    cout << "Author: ";
    cin>> author;

    string title;
    cout << "Title: ";
    cin>>title;
    Book book;
    if (lookupBook(author, title)) {
        cout << endl << "There is no book " << title << " by "
             << "author " << author << "." << endl;
        return;
    }
    for (pair<int,Customer> entry : s_customerMap) {
        Customer& customer = entry.second;
        customer.returnBook(book.bookId());
        customer.unReserveBook(book.bookId());
        s_customerMap[customer.id()] = customer;
        s_bookMap.erase(book.bookId());
        cout << endl << "Deleted." << endl;
    }
}

void Library::listBooks() {
    if (s_bookMap.empty()) {
        cout << "No books." << endl;
        return;
    }

    for (pair< const int,Book>& entry : s_bookMap) {
        const Book& book = entry.second;
        cout << book.title()<<" by "<<book.author()<< endl;
    }
}

void Library::addCustomer() {
    string name;
    cout << "Name: ";
    cin>>name;

    string address;
    cout << "Address: ";
    cin>>address;
    if (lookupCustomer(name, address)) {
        cout << endl << "A customer with name " << name
             << " and address " << address << " already exists."
             << endl;
        return;
    }
    Customer customer(name, address);
    s_customerMap[customer.id()] = customer;
    cout << endl << "Added." << endl;
}

void Library::deleteCustomer() {
    string name;
    cout << "Name: ";
    cin>>name;

    string address;
    cout << "Address: ";
    cin>> address;

    Customer customer;
    if (lookupCustomer(name, address)) {
        cout << endl << "There is no customer with name " << name
             << " and address " << address << "." << endl;
        return;
    }
    if (customer.hasBorrowed()) {
        cout << "Customer " << name << " has borrowed at least "
             << "one book and cannot be deleted." << endl;
        return;
    }
    for (pair<int,Book> entry : s_bookMap) {
        Book& book = entry.second;
        book.unReserveBook(customer.id());
        s_bookMap[book.bookId()] = book;
    }

    cout << endl << "Deleted." << endl;
    s_customerMap.erase(customer.id());

}
void Library::listCustomer() {
    if (s_customerMap.empty()) {
        cout << "No customers." << endl;
        return;
    }

    for ( pair<const int,Customer>& entry : s_customerMap) {
        const Customer& customer = entry.second;
        cout << customer << endl;
    }
}

void Library::borrowBook() {
    string author;
    cout << "Author: ";
    cin >> author;

    string title;
    cout << "Title: ";
    cin>>title;
    Book book;
    if (lookupBook(author, title)) {
        cout << endl << "There is no book " << title << " by "
             << "author " << author << "." << endl;
        return;
    }
    if (book.borrowed()) {
        cout << endl << "The book " << title << " by " << author
             << " has already been borrowed." << endl;
        return;
    }
    string name;
    cout << "Customer name: ";
    cin>>name;

    string address;
    cout << "Address: ";
    cin>>address;
    Customer customer;
    if (lookupCustomer(name, address)) {
        cout << endl << "There is no customer with name " << name
             << " and address " << address << "." << endl;
        return;
    }
    book.borrowBook(customer.id());
    customer.borrowBook(book.bookId());
    s_bookMap[book.bookId()] = book;
    s_customerMap[customer.id()] = customer;
    cout << endl << "Borrowed." << endl;
}

void Library::reserveBook() {
    string author;
    cout << "Author: ";
    cin >>author;

    string title;
    cout << "Title: ";
    cin >>title;
    Book book;
    if (lookupBook(author, title)) {
        cout << endl << "There is no book " << title << " by "
             << "author " << author << "." << endl;
        return;
    }
    if (book.borrowed()) {
        cout << endl << "The book with author " << author
             << " and title " << title << " has not been "
             << "borrowed. Please borrow the book instead." << endl;
        return;
    }
    string name;
    cout << "Customer name: ";
    cin >>name;

    string address;
    cout << "Address: ";
    cin >>address;
    Customer customer;
    if (lookupCustomer(name, address)) {
        cout << endl << "No customer with name " << name
             << " and address " << address << " exists." << endl;
        return;
    }
    if (book.customerId() == customer.id()) {
        cout << endl << "The book has already been borrowed by "
             << name << "." << endl;
        return;
    }
    customer.reserveBook(book.bookId());
    int position = book.reserveBook(customer.id());
    s_bookMap[book.bookId()] = book;
    s_customerMap[customer.id()] = customer;
    cout << endl << position << "nd reserve." << endl;
}

void Library::returnBook() {
    string author;
    cout << "Author: ";
    cin>>author;

    string title;
    cout << "Title: ";
    cin>>title;
    Book book;
    if (lookupBook(author, title)) {
        cout << endl << "No book " << title
             << " by " << author << " exists." <<endl;
        return;
    }
    if (!book.borrowed()) {
        cout << endl << "The book " << title
             <<  "by " << author
                << " has not been borrowed." << endl;
        return;
    }
    book.returnBook();
    cout << endl << "Returned." << endl;

    Customer customer = s_customerMap[book.customerId()];
    customer.returnBook(book.bookId());
    s_customerMap[customer.id()] = customer;
    list<int>& reservationList = book.reservationList();

    if (!reservationList.empty()) {
        int newCustomerId = reservationList.front();
        reservationList.erase(reservationList.begin());
        book.borrowBook(newCustomerId);

        Customer newCustomer = s_customerMap[newCustomerId];
        newCustomer.borrowBook(book.bookId());

        s_customerMap[newCustomerId] = newCustomer;
        cout << endl << "Borrowed by " << newCustomer.name() << endl;
    }

    s_bookMap[book.bookId()] = book;

}

void Library::load() {
    ifstream inStream(s_binaryPath);
    if (inStream) {
        int numberOfBooks;
        inStream.read((char*) &numberOfBooks, sizeof numberOfBooks);
        for (int count = 0; count < numberOfBooks; ++count) {
            Book book;
            book.read(inStream);
            s_bookMap[book.bookId()] = book;
            Book::MaxBookId = max(Book::MaxBookId, book.bookId());
        }
        int numberOfCustomers;
        inStream.read((char*) &numberOfCustomers,sizeof numberOfCustomers);
        for (int count = 0; count < numberOfCustomers; ++count) {
            Customer customer;
            customer.read(inStream);
            s_customerMap[customer.id()] = customer;
            Customer::MaxCustomerId =
                    max(Customer::MaxCustomerId, customer.id());
        }
    }
}

void Library::save() {

    ofstream inStream(s_binaryPath);
    if (inStream) {
        int numberOfBooks = s_bookMap.size();
        inStream.write((char*) &numberOfBooks, sizeof numberOfBooks);

        for (pair< const int,Book> &entry : s_bookMap) {
            const Book& book = entry.second;
            book.write(inStream);
        }
        int numberOfCustomers = s_customerMap.size();
        inStream.write((char*) &numberOfCustomers,
                        sizeof numberOfCustomers);

        for (pair< const int,Customer> &entry : s_customerMap) {
            const Customer& customer = entry.second;
            customer.write(inStream);
        }
    }
}
