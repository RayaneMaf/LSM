#include "article.h"
#include <iostream>
using namespace std;

Article::Article(const string &title, const string &author, const string &resourceId, const string &category, int publicationYear, const string &magazine, int volume, int issue, const string &doi, int startPage, int endPage)
    : Resource(title, author, resourceId, category, publicationYear)
{
    setMagazine(magazine);
    setVolume(volume);
    setIssue(issue);
    setDOI(doi);
    setPageRange(startPage, endPage);
}

void Article::displayInfo() const
{
    // common Resource fields
    cout << "----- " << getType() << " -----\n";
    cout << "ID:           " << getResourceId() << "\n";
    cout << "Title:        " << getTitle() << "\n";
    cout << "Author:       " << getAuthor() << "\n";
    cout << "Year:         " << getPublicationYear() << "\n";
    cout << "Category:     " << getCategory() << "\n";
    cout << "Available:    " << (getAvailable() ? "Yes" : "No") << "\n";

    // Article-specific fields
    cout << "Magazine:     " << magazine << "\n";
    cout << "Volume:       " << volume << "\n";
    cout << "Issue:        " << issue << "\n";

    if (hasPageRange())
        cout << "Pages:        " << startPage << "-" << endPage << "\n";

    if (hasDOI())
        cout << "DOI:          " << doi << "\n";

    cout << "----------------------\n";
}

const string &Article::getType() const
{
    static const string type = "Article";
    return type;
}

// Validation methods
bool Article::isValidVolume(int vol) const
{
    return (vol > 0 && vol <= 1000);
}

bool Article::isValidIssue(int iss) const
{
    return (iss > 0 && iss <= 100);
}

bool Article::isValidDOI(const string &doi) const
{
    if (doi.empty() || doi == "N/A")
        return true;

    return (doi.length() > 3 && doi.substr(0, 3) == "10.");
}

bool Article::isValidPageRange(int start, int end) const
{
    if (start == -1 || end == -1)
        return true;

    return (start > 0 && end > 0 && start <= end && end - start < 1000);
}

void Article::setMagazine(const string &magazine)
{
    this->magazine = magazine.empty() ? "Unknown Magazine" : magazine;
}

const string &Article::getMagazine() const
{
    return magazine;
}

void Article::setVolume(int volume)
{
    if (isValidVolume(volume))
    {
        this->volume = volume;
    }
    else
    {
        this->volume = -1;
    }
}

int Article::getVolume() const
{
    return volume;
}

void Article::setIssue(int issue)
{
    if (isValidIssue(issue))
    {
        this->issue = issue;
    }
    else
    {
        this->issue = -1;
    }
}

int Article::getIssue() const
{
    return issue;
}

void Article::setDOI(const string &doi)
{
    if (isValidDOI(doi))
    {
        this->doi = doi;
    }
    else
    {
        this->doi = "N/A";
    }
}

const string &Article::getDOI() const
{
    return doi;
}

void Article::setPageRange(int start, int end)
{
    if (isValidPageRange(start, end))
    {
        this->startPage = start;
        this->endPage = end;
    }
    else
    {
        this->startPage = -1;
        this->endPage = -1;
    }
}

int Article::getStartPage() const
{
    return startPage;
}

int Article::getEndPage() const
{
    return endPage;
}

// Additional methods
bool Article::hasDOI() const
{
    return (!doi.empty() && doi != "N/A");
}

bool Article::hasPageRange() const
{
    return (startPage > 0 && endPage > 0);
}

string Article::getVolumeIssueInfo() const
{
    string info = "";
    if (volume > 0)
        info += "Vol. " + to_string(volume);
    if (issue > 0)
    {
        if (!info.empty())
            info += ", ";
        info += "Issue " + to_string(issue);
    }
    return info.empty() ? "N/A" : info;
}

bool Article::matchesKeyword(const string &keyword) const
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

    string lowerMagazine = "";
    for (int i = 0; i < magazine.length(); i++)
    {
        char c = magazine[i];
        if (c >= 'A' && c <= 'Z')
            lowerMagazine += (c + 32);
        else
            lowerMagazine += c;
    }

    string lowerDOI = "";
    for (int i = 0; i < doi.length(); i++)
    {
        char c = doi[i];
        if (c >= 'A' && c <= 'Z')
            lowerDOI += (c + 32);
        else
            lowerDOI += c;
    }

    bool foundInMagazine = false;
    if (lowerMagazine.length() >= lowerKeyword.length())
    {
        for (int i = 0; i <= lowerMagazine.length() - lowerKeyword.length(); i++)
        {
            bool match = true;
            for (int j = 0; j < lowerKeyword.length(); j++)
            {
                if (lowerMagazine[i + j] != lowerKeyword[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                foundInMagazine = true;
                break;
            }
        }
    }

    bool foundInDOI = false;
    if (lowerDOI.length() >= lowerKeyword.length())
    {
        for (int i = 0; i <= lowerDOI.length() - lowerKeyword.length(); i++)
        {
            bool match = true;
            for (int j = 0; j < lowerKeyword.length(); j++)
            {
                if (lowerDOI[i + j] != lowerKeyword[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                foundInDOI = true;
                break;
            }
        }
    }

    return (foundInMagazine || foundInDOI);
}

// Json
json Article::toJson() const
{
    return json{
        {"title", getTitle()},
        {"author", getAuthor()},
        {"resourceId", getResourceId()},
        {"category", getCategory()},
        {"publicationYear", getPublicationYear()},
        {"isAvailable", getAvailable()},
        {"magazine", magazine},
        {"volume", volume},
        {"issue", issue},
        {"doi", doi},
        {"startPage", startPage},
        {"endPage", endPage},
        {"type", getType()}};
}

Article Article::fromJson(const json &j)
{
    try
    {
        Article article(
            j.at("title").get<string>(),
            j.at("author").get<string>(),
            j.at("resourceId").get<string>(),
            j.at("category").get<string>(),
            j.at("publicationYear").get<int>(),
            j.at("magazine").get<string>(),
            j.at("volume").get<int>(),
            j.at("issue").get<int>(),
            j.value("doi", "N/A"),
            j.value("startPage", -1),
            j.value("endPage", -1));

        article.setAvailable(j.at("isAvailable").get<bool>());
        return article;
    }
    catch (const json::exception &e)
    {
        throw runtime_error("Error parsing Article JSON: " + string(e.what()));
    }
}