#ifndef ARTICLE_H
#define ARTICLE_H
#include "resource.h"
using namespace std;

class Article : public Resource
{
private:
    string magazine;
    int volume;
    int issue;
    string doi;
    int startPage;
    int endPage;

public:
    // Constructor/Destructor
    Article(const string & = "", const string & = "", const string & = "", const string & = "", int = -1, const string & = "", int = -1, int = -1, const string & = "", int = -1, int = -1);
    virtual ~Article() = default;

    // Methods
    void displayInfo() const override;
    const string &getType() const override;

    // Validation methods
    bool isValidVolume(int vol) const;
    bool isValidIssue(int iss) const;
    bool isValidDOI(const string &doi) const;
    bool isValidPageRange(int start, int end) const;

    // Enhanced setters & getters
    void setMagazine(const string & = "");
    const string &getMagazine() const;
    void setVolume(int = -1);
    int getVolume() const;
    void setIssue(int = -1);
    int getIssue() const;
    void setDOI(const string & = "");
    const string &getDOI() const;
    void setPageRange(int start = -1, int end = -1);
    int getStartPage() const;
    int getEndPage() const;

    // Additional methods
    bool hasDOI() const;
    bool hasPageRange() const;
    string getVolumeIssueInfo() const;

    // Override search method for article-specific fields
    bool matchesKeyword(const string &keyword) const;

    // Json
    json toJson() const override;
    static Article fromJson(const json &);
};

#endif