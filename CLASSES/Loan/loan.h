#ifndef LOAN_H
#define LOAN_H
#include <string>
#include <ctime>
#include "Json/json.hpp"
using namespace std;
using json = nlohmann::json;

class Loan
{
private:
    string loanId;
    string userId;
    string resourceId;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate; // 0 means no return yet
    bool isReturned;
    int renewalCount;
    static int maxRenewals;
    static int loanPeriod; // in seconds

    // Helper validation methods
    bool isValidLoanId(const string &loanId) const;
    bool isValidId(const string &id) const;
    bool isValidDate(time_t date) const;

public:
    Loan(const string & = "", const string & = "", const string & = "", time_t = 0, time_t = 0);
    ~Loan() = default;

    const string &getLoanId() const;
    const string &getUserId() const;
    const string &getResourceId() const;
    time_t getBorrowDate() const;
    time_t getDueDate() const;
    time_t getReturnDate() const;
    bool getIsReturned() const;
    int getRenewalCount() const;
    static int getMaxRenewals();
    static int getLoanPeriod();

    bool isOverdue() const;
    bool renew();
    void markReturned();
    static void setMaxRenewals(int = 2);
    static void setLoanPeriod(int = 1209600); // 14 days as default

    // Json
    json toJson() const;
    static Loan fromJson(const json &);
};

#endif