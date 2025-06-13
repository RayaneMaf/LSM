#include "resource.h"
#include "book.h"
#include "article.h"
#include <exception>

using namespace std;

Resource::Resource(const string &title, const string &author, const string &resourceId, const string &category, int publicationYear)
{
    setTitle(title);
    setAuthor(author);
    setResourceId(resourceId);
    setCategory(category);
    setPublicationYear(publicationYear);
    setAvailable(true);
}

// Enhanced validation methods
bool Resource::isValidResourceId(const string &id) const
{
    if (id.empty() || id.length() < 3)
        return false;

    // Check if contains only letters, numbers, dashes, underscores
    for (int i = 0; i < id.length(); i++)
    {
        char c = id[i];
        bool isValid = (c >= 'a' && c <= 'z') ||
                       (c >= 'A' && c <= 'Z') ||
                       (c >= '0' && c <= '9') ||
                       c == '-' || c == '_';
        if (!isValid)
            return false;
    }
    return true;
}

bool Resource::isValidYear(int year) const
{
    return (year >= 1000 && year <= 2025);
}

bool Resource::isValidTitle(const string &title) const
{
    if (title.empty() || title.length() < 2)
        return false;

    // Check if title contains at least one letter
    for (int i = 0; i < title.length(); i++)
    {
        char c = title[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return true;
    }
    return false;
}

bool Resource::isValidAuthor(const string &author) const
{
    if (author.empty() || author.length() < 2)
        return false;

    // Check if author contains at least one letter
    for (int i = 0; i < author.length(); i++)
    {
        char c = author[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return true;
    }
    return false;
}

void Resource::setTitle(const string &title)
{
    if (!isValidTitle(title))
    {
        this->title = "Unknown Title";
        return;
    }
    this->title = title;
}

const string &Resource::getTitle() const
{
    return title;
}

void Resource::setAuthor(const string &author)
{
    if (!isValidAuthor(author))
    {
        this->author = "Unknown Author";
        return;
    }
    this->author = author;
}

const string &Resource::getAuthor() const
{
    return author;
}

void Resource::setResourceId(const string &resourceId)
{
    if (!isValidResourceId(resourceId))
    {
        this->resourceId = "INVALID_ID";
        return;
    }
    this->resourceId = resourceId;
}

const string &Resource::getResourceId() const
{
    return resourceId;
}

void Resource::setCategory(const string &category)
{
    this->category = category.empty() ? "General" : category;
}

const string &Resource::getCategory() const
{
    return category;
}

void Resource::setPublicationYear(int publicationYear)
{
    if (isValidYear(publicationYear))
    {
        this->publicationYear = publicationYear;
    }
    else
    {
        this->publicationYear = -1;
    }
}

int Resource::getPublicationYear() const
{
    return publicationYear;
}

void Resource::setAvailable(bool isAvailable)
{
    this->isAvailable = isAvailable;
}

bool Resource::getAvailable() const
{
    return isAvailable;
}

// Simple helper function to convert string to lowercase
string Resource::toLower(const string &str) const
{
    string result = str;
    for (int i = 0; i < result.length(); i++)
    {
        if (result[i] >= 'A' && result[i] <= 'Z')
        {
            result[i] = result[i] + 32;
        }
    }
    return result;
}

// Simple helper function to check if string contains substring
bool Resource::contains(const string &str, const string &substr) const
{
    if (substr.empty() || str.empty())
        return false;

    for (int i = 0; i <= str.length() - substr.length(); i++)
    {
        bool found = true;
        for (int j = 0; j < substr.length(); j++)
        {
            if (str[i + j] != substr[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    }
    return false;
}

// Search and comparison methods
bool Resource::matchesKeyword(const string &keyword) const
{
    if (keyword.empty())
        return false;

    string lowerKeyword = toLower(keyword);
    string lowerTitle = toLower(title);
    string lowerAuthor = toLower(author);
    string lowerCategory = toLower(category);

    return (contains(lowerTitle, lowerKeyword) ||
            contains(lowerAuthor, lowerKeyword) ||
            contains(lowerCategory, lowerKeyword));
}

bool Resource::matchesCategory(const string &cat) const
{
    if (cat.empty())
        return true;

    string lowerCat = toLower(cat);
    string lowerCategory = toLower(category);

    return contains(lowerCategory, lowerCat);
}

bool Resource::matchesAuthor(const string &auth) const
{
    if (auth.empty())
        return true;

    string lowerAuth = toLower(auth);
    string lowerAuthor = toLower(author);

    return contains(lowerAuthor, lowerAuth);
}

// Operator overloading
bool Resource::operator==(const Resource &other) const
{
    return (resourceId == other.resourceId);
}

bool Resource::operator!=(const Resource &other) const
{
    return !(*this == other);
}

// Json
unique_ptr<Resource> Resource::fromJson(const json &j)
{
    try
    {
        string resourceType = j.at("type").get<string>();

        if (resourceType == "Book")
            return make_unique<Book>(Book::fromJson(j));

        if (resourceType == "Article")
            return make_unique<Article>(Article::fromJson(j));

        throw runtime_error("Error: Unknown resource type '" + resourceType + "'");
    }
    catch (const json::exception &e)
    {
        throw runtime_error("Error parsing JSON: " + string(e.what()));
    }
}