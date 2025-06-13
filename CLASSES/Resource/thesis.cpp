#include "thesis.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Constructor
Thesis::Thesis(const string &title, const string &author, const string &resourceId,
               const string &category, int publicationYear, const string &university,
               const string &department, const string &supervisor, ThesisType type,
               const string &degree, int pages, const string &abstractText)
    : Resource(title, author, resourceId, category, publicationYear),
      university(university), department(department), supervisor(supervisor),
      thesisType(type), degree(degree), pageCount(pages), abstractText(abstractText)
{
    // Validation is handled by setters in Resource base class
}

// Display information
void Thesis::displayInfo() const
{
    cout << "=== THESIS ===" << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Author: " << getAuthor() << endl;
    cout << "Resource ID: " << getResourceId() << endl;
    cout << "University: " << university << endl;
    cout << "Department: " << department << endl;
    cout << "Supervisor: " << supervisor << endl;
    cout << "Type: " << getThesisTypeString() << endl;
    cout << "Degree: " << degree << endl;
    cout << "Publication Year: " << getPublicationYear() << endl;
    cout << "Pages: " << pageCount << endl;
    cout << "Available: " << (getAvailable() ? "Yes" : "No") << endl;
    if (hasAbstract())
    {
        cout << "Abstract: " << abstractText.substr(0, 100) << "..." << endl;
    }
    cout << "==============" << endl;
}

// Get resource type
const string &Thesis::getType() const
{
    static const string type = "Thesis";
    return type;
}

// Validation methods
bool Thesis::isValidUniversity(const string &uni) const
{
    return !uni.empty() && uni.length() >= 2 && uni.length() <= 100;
}

bool Thesis::isValidDepartment(const string &dept) const
{
    return !dept.empty() && dept.length() >= 2 && dept.length() <= 100;
}

bool Thesis::isValidSupervisor(const string &supervisor) const
{
    return !supervisor.empty() && supervisor.length() >= 2 && supervisor.length() <= 100;
}

bool Thesis::isValidPageCount(int pages) const
{
    return pages > 0 && pages <= 1000;
}

// Setters and Getters
void Thesis::setUniversity(const string &university)
{
    if (isValidUniversity(university))
    {
        this->university = university;
    }
    else
    {
        throw invalid_argument("Invalid university name");
    }
}

const string &Thesis::getUniversity() const
{
    return university;
}

void Thesis::setDepartment(const string &department)
{
    if (isValidDepartment(department))
    {
        this->department = department;
    }
    else
    {
        throw invalid_argument("Invalid department name");
    }
}

const string &Thesis::getDepartment() const
{
    return department;
}

void Thesis::setSupervisor(const string &supervisor)
{
    if (isValidSupervisor(supervisor))
    {
        this->supervisor = supervisor;
    }
    else
    {
        throw invalid_argument("Invalid supervisor name");
    }
}

const string &Thesis::getSupervisor() const
{
    return supervisor;
}

void Thesis::setThesisType(ThesisType type)
{
    this->thesisType = type;
}

ThesisType Thesis::getThesisType() const
{
    return thesisType;
}

void Thesis::setDegree(const string &degree)
{
    this->degree = degree;
}

const string &Thesis::getDegree() const
{
    return degree;
}

void Thesis::setPageCount(int pages)
{
    if (isValidPageCount(pages))
    {
        this->pageCount = pages;
    }
    else
    {
        throw invalid_argument("Invalid page count");
    }
}

int Thesis::getPageCount() const
{
    return pageCount;
}

void Thesis::setAbstractText(const string &abstractText)
{
    this->abstractText = abstractText;
}

const string &Thesis::getAbstractText() const
{
    return abstractText;
}

// Utility methods
string Thesis::getThesisTypeString() const
{
    switch (thesisType)
    {
    case ThesisType::Bachelor:
        return "Bachelor's Thesis";
    case ThesisType::Master:
        return "Master's Thesis";
    case ThesisType::PhD:
        return "PhD Dissertation";
    case ThesisType::Research:
        return "Research Thesis";
    default:
        return "Unknown";
    }
}

string Thesis::getFormattedInfo() const
{
    stringstream ss;
    ss << getTitle() << " by " << getAuthor()
       << " (" << getThesisTypeString() << ", " << university << ")";
    return ss.str();
}

bool Thesis::hasAbstract() const
{
    return !abstractText.empty();
}

// Search method override
bool Thesis::matchesKeyword(const string &keyword) const
{
    if (Resource::matchesKeyword(keyword))
    {
        return true;
    }

    string lowerKeyword = toLower(keyword);

    return contains(toLower(university), lowerKeyword) ||
           contains(toLower(department), lowerKeyword) ||
           contains(toLower(supervisor), lowerKeyword) ||
           contains(toLower(degree), lowerKeyword) ||
           contains(toLower(abstractText), lowerKeyword);
}

// JSON serialization
json Thesis::toJson() const
{
    json j = Resource::toJson();
    j["university"] = university;
    j["department"] = department;
    j["supervisor"] = supervisor;
    j["thesisType"] = static_cast<int>(thesisType);
    j["degree"] = degree;
    j["pageCount"] = pageCount;
    j["abstractText"] = abstractText;
    j["resourceType"] = "Thesis";
    return j;
}

Thesis Thesis::fromJson(const json &j)
{
    Thesis thesis;
    thesis.setTitle(j.value("title", ""));
    thesis.setAuthor(j.value("author", ""));
    thesis.setResourceId(j.value("resourceId", ""));
    thesis.setCategory(j.value("category", ""));
    thesis.setPublicationYear(j.value("publicationYear", 0));
    thesis.setAvailable(j.value("isAvailable", true));

    thesis.setUniversity(j.value("university", ""));
    thesis.setDepartment(j.value("department", ""));
    thesis.setSupervisor(j.value("supervisor", ""));
    thesis.setThesisType(static_cast<ThesisType>(j.value("thesisType", 0)));
    thesis.setDegree(j.value("degree", ""));
    thesis.setPageCount(j.value("pageCount", 0));
    thesis.setAbstractText(j.value("abstractText", ""));

    return thesis;
}