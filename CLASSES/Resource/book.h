#ifndef BOOK_H
#define BOOK_H
#include <string>
#include "resource.h"
using namespace std;

class Book : public Resource
{
private:
    int numberOfPages;
    string publisher;
    string isbn;
    string edition;

public:
    // Constructor/destructor
    Book(const string & = "", const string & = "", const string & = "", const string & = "", int = -1, const string & = "", int = -1, const string & = "", const string & = "");
    virtual ~Book() = default;

    // Methods
    void displayInfo() const override;
    const string &getType() const override;

    // Validation methods
    bool isValidPages(int pages) const;
    bool isValidISBN(const string &isbn) const;

    // setters & getters
    void setNumberOfPages(int = 0);
    int getNumberOfPages() const;
    void setPublisher(const string & = "");
    const string &getPublisher() const;
    void setISBN(const string & = "");
    const string &getISBN() const;
    void setEdition(const string & = "");
    const string &getEdition() const;

    // Additional methods
    bool hasISBN() const;
    string getFormattedInfo() const;

    // Override search method for book-specific fields
    bool matchesKeyword(const string &keyword) const;

    // Json
    json toJson() const override;
    static Book fromJson(const json &);
};

#endif