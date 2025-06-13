#include "book.h"
#include <iostream>
using namespace std;

Book::Book(const string &title, const string &author, const string &resourceId, const string &category, int publicationYear, const string &publisher, int numberOfPages, const string &isbn, const string &edition)
    : Resource(title, author, resourceId, category, publicationYear)
{
    setPublisher(publisher);
    setNumberOfPages(numberOfPages);
    setISBN(isbn);
    setEdition(edition);
}

void Book::displayInfo() const
{
    // common Resource fields
    cout << "----- " << getType() << " -----\n";
    cout << "ID:           " << getResourceId() << "\n";
    cout << "Title:        " << getTitle() << "\n";
    cout << "Author:       " << getAuthor() << "\n";
    cout << "Year:         " << getPublicationYear() << "\n";
    cout << "Category:     " << getCategory() << "\n";
    cout << "Available:    " << (getAvailable() ? "Yes" : "No") << "\n";

    // Book-specific fields
    cout << "Publisher:    " << publisher << "\n";
    cout << "Pages:        " << numberOfPages << "\n";

    if (!isbn.empty() && isbn != "N/A")
        cout << "ISBN:         " << isbn << "\n";

    if (!edition.empty() && edition != "N/A")
        cout << "Edition:      " << edition << "\n";

    cout << "----------------------\n";
}

const string &Book::getType() const
{
    static const string type = "Book";
    return type;
}

// Validation methods
bool Book::isValidPages(int pages) const
{
    return (pages > 0 && pages <= 10000);
}

bool Book::isValidISBN(const string &isbn) const
{
    if (isbn.empty() || isbn == "N/A")
        return true;

    string cleanISBN = "";
    for (int i = 0; i < isbn.length(); i++)
    {
        char c = isbn[i];
        if (c != '-' && c != ' ')
            cleanISBN += c;
    }

    if (cleanISBN.length() == 10 || cleanISBN.length() == 13)
    {
        for (int i = 0; i < cleanISBN.length() - 1; i++)
        {
            char c = cleanISBN[i];
            if (c < '0' || c > '9')
                return false;
        }
        char lastChar = cleanISBN[cleanISBN.length() - 1];
        bool lastValid = (lastChar >= '0' && lastChar <= '9') ||
                         (cleanISBN.length() == 10 && lastChar == 'X');
        return lastValid;
    }
    return false;
}

void Book::setNumberOfPages(int numberOfPages)
{
    if (isValidPages(numberOfPages))
    {
        this->numberOfPages = numberOfPages;
    }
    else
    {
        this->numberOfPages = -1;
    }
}

int Book::getNumberOfPages() const
{
    return numberOfPages;
}

void Book::setPublisher(const string &publisher)
{
    this->publisher = publisher.empty() ? "Unknown Publisher" : publisher;
}

const string &Book::getPublisher() const
{
    return publisher;
}

void Book::setISBN(const string &isbn)
{
    if (isValidISBN(isbn))
    {
        this->isbn = isbn;
    }
    else
    {
        this->isbn = "N/A";
    }
}

const string &Book::getISBN() const
{
    return isbn;
}

void Book::setEdition(const string &edition)
{
    this->edition = edition.empty() ? "N/A" : edition;
}

const string &Book::getEdition() const
{
    return edition;
}

// Additional methods
bool Book::hasISBN() const
{
    return (!isbn.empty() && isbn != "N/A");
}

string Book::getFormattedInfo() const
{
    string info = getTitle() + " by " + getAuthor();
    if (hasISBN())
        info += " (ISBN: " + isbn + ")";
    return info;
}

bool Book::matchesKeyword(const string &keyword) const
{
    if (keyword.empty())
        return false;

    if (Resource::matchesKeyword(keyword))
        return true;

    string lowerKeyword = "";
    for (int i = 0; i < keyword.length(); i++)
    {
        char c = keyword[i];
        if (c >= 'A' && c <= 'Z')
            lowerKeyword += (c + 32);
        else
            lowerKeyword += c;
    }

    string lowerPublisher = "";
    for (int i = 0; i < publisher.length(); i++)
    {
        char c = publisher[i];
        if (c >= 'A' && c <= 'Z')
            lowerPublisher += (c + 32);
        else
            lowerPublisher += c;
    }

    string lowerISBN = "";
    for (int i = 0; i < isbn.length(); i++)
    {
        char c = isbn[i];
        if (c >= 'A' && c <= 'Z')
            lowerISBN += (c + 32);
        else
            lowerISBN += c;
    }

    bool foundInPublisher = false;
    bool foundInISBN = false;

    if (lowerPublisher.length() >= lowerKeyword.length())
    {
        for (int i = 0; i <= lowerPublisher.length() - lowerKeyword.length(); i++)
        {
            bool match = true;
            for (int j = 0; j < lowerKeyword.length(); j++)
            {
                if (lowerPublisher[i + j] != lowerKeyword[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                foundInPublisher = true;
                break;
            }
        }
    }

    if (lowerISBN.length() >= lowerKeyword.length())
    {
        for (int i = 0; i <= lowerISBN.length() - lowerKeyword.length(); i++)
        {
            bool match = true;
            for (int j = 0; j < lowerKeyword.length(); j++)
            {
                if (lowerISBN[i + j] != lowerKeyword[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                foundInISBN = true;
                break;
            }
        }
    }

    return (foundInPublisher || foundInISBN);
}

// Json
json Book::toJson() const
{
    return json{
        {"title", getTitle()},
        {"author", getAuthor()},
        {"resourceId", getResourceId()},
        {"category", getCategory()},
        {"publicationYear", getPublicationYear()},
        {"isAvailable", getAvailable()},
        {"numberOfPages", numberOfPages},
        {"publisher", publisher},
        {"isbn", isbn},
        {"edition", edition},
        {"type", getType()}};
}

Book Book::fromJson(const json &j)
{
    try
    {
        Book book(
            j.at("title").get<string>(),
            j.at("author").get<string>(),
            j.at("resourceId").get<string>(),
            j.at("category").get<string>(),
            j.at("publicationYear").get<int>(),
            j.at("publisher").get<string>(),
            j.at("numberOfPages").get<int>(),
            j.value("isbn", "N/A"),
            j.value("edition", "N/A"));

        book.setAvailable(j.at("isAvailable").get<bool>());
        return book;
    }
    catch (const json::exception &e)
    {
        throw runtime_error("Error parsing Book JSON: " + string(e.what()));
    }
}