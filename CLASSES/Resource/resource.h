#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <memory>
#include <stdexcept>
#include "Json/json.hpp"
using json = nlohmann::json;
using namespace std;

class Resource
{
private:
    string title;
    string author;
    string resourceId;
    string category;
    int publicationYear;
    bool isAvailable;

public:
    // Constructor
    Resource(const string & = "", const string & = "", const string & = "", const string & = "", int = -1);
    virtual ~Resource() = default;

    // Methods
    virtual void displayInfo() const = 0;
    virtual const string &getType() const = 0;

    // Validation methods
    bool isValidResourceId(const string &id) const;
    bool isValidYear(int year) const;
    bool isValidTitle(const string &title) const;
    bool isValidAuthor(const string &author) const;

    // Setters & Getters
    void setTitle(const string & = "");
    const string &getTitle() const;
    void setAuthor(const string & = "");
    const string &getAuthor() const;
    void setResourceId(const string & = "");
    const string &getResourceId() const;
    void setCategory(const string & = "");
    const string &getCategory() const;
    void setPublicationYear(int = 0);
    int getPublicationYear() const;
    void setAvailable(bool = true);
    bool getAvailable() const;

    // Helper methods
    string toLower(const string &str) const;
    bool contains(const string &str, const string &substr) const;

    // Search and comparison methods
    bool matchesKeyword(const string &keyword) const;
    bool matchesCategory(const string &cat) const;
    bool matchesAuthor(const string &auth) const;

    // Operator overloading for comparison
    bool operator==(const Resource &other) const;
    bool operator!=(const Resource &other) const;

    // Json
    virtual json toJson() const = 0;
    static unique_ptr<Resource> fromJson(const json &);
};
#endif