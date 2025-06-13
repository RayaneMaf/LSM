#ifndef THESIS_H
#define THESIS_H
#include "resource.h"
using namespace std;

enum class ThesisType
{
    Bachelor,
    Master,
    PhD,
    Research
};

class Thesis : public Resource
{
private:
    string university;
    string department;
    string supervisor;
    ThesisType thesisType;
    string degree;
    int pageCount;
    string abstractText;

public:
    // Constructor/Destructor
    Thesis(const string &title = "", const string &author = "", const string &resourceId = "",
           const string &category = "", int publicationYear = -1, const string &university = "",
           const string &department = "", const string &supervisor = "", ThesisType type = ThesisType::Bachelor,
           const string &degree = "", int pages = -1, const string &abstractText = "");
    virtual ~Thesis() = default;

    // Methods
    void displayInfo() const override;
    const string &getType() const override;

    // Validation methods
    bool isValidUniversity(const string &uni) const;
    bool isValidDepartment(const string &dept) const;
    bool isValidSupervisor(const string &supervisor) const;
    bool isValidPageCount(int pages) const;

    // setters & getters
    void setUniversity(const string &university = "");
    const string &getUniversity() const;
    void setDepartment(const string &department = "");
    const string &getDepartment() const;
    void setSupervisor(const string &supervisor = "");
    const string &getSupervisor() const;
    void setThesisType(ThesisType type = ThesisType::Bachelor);
    ThesisType getThesisType() const;
    void setDegree(const string &degree = "");
    const string &getDegree() const;
    void setPageCount(int pages = -1);
    int getPageCount() const;
    void setAbstractText(const string &abstractText = "");
    const string &getAbstractText() const;

    // Additional methods
    string getThesisTypeString() const;
    string getFormattedInfo() const;
    bool hasAbstract() const;

    // Override search method for thesis-specific fields
    bool matchesKeyword(const string &keyword) const;

    // Json
    json toJson() const override;
    static Thesis fromJson(const json &j);
};

#endif