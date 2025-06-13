#include "loan.h"
#include <iostream>
#include <climits>

int Loan::maxRenewals = 2;
int Loan::loanPeriod = 1209600;

Loan::Loan(const string &loanId, const string &userId, const string &resourceId, time_t borrowDate, time_t dueDate)
    : loanId(loanId), userId(userId), resourceId(resourceId), borrowDate(borrowDate), dueDate(dueDate), returnDate(0), renewalCount(0), isReturned(false) 
{
    if (!loanId.empty() && !isValidLoanId(loanId)) {
        cerr << "Warning: Invalid loan ID provided. Using empty string." << endl;
        this->loanId = "";
    }
    if (!userId.empty() && !isValidId(userId)) {
        cerr << "Warning: Invalid user ID provided. Using empty string." << endl;
        this->userId = "";
    }
    if (!resourceId.empty() && !isValidId(resourceId)) {
        cerr << "Warning: Invalid resource ID provided. Using empty string." << endl;
        this->resourceId = "";
    }
    if (borrowDate != 0 && !isValidDate(borrowDate)) {
        cerr << "Warning: Invalid borrow date provided. Using 0." << endl;
        this->borrowDate = 0;
    }
    if (dueDate != 0 && !isValidDate(dueDate)) {
        cerr << "Warning: Invalid due date provided. Using 0." << endl;
        this->dueDate = 0;
    }
    if (borrowDate != 0 && dueDate != 0 && dueDate <= borrowDate) {
        cerr << "Warning: Due date must be after borrow date. Setting due date to borrow date + loan period." << endl;
        this->dueDate = borrowDate + loanPeriod;
    }
}

const string &Loan::getLoanId() const
{
    return loanId;
}

const string &Loan::getUserId() const
{
    return userId;
}

const string &Loan::getResourceId() const
{
    return resourceId;
}

time_t Loan::getBorrowDate() const
{
    return borrowDate;
}

time_t Loan::getDueDate() const
{
    return dueDate;
}

time_t Loan::getReturnDate() const
{
    return returnDate;
}

bool Loan::getIsReturned() const
{
    return isReturned;
}

int Loan::getRenewalCount() const
{
    return renewalCount;
}

int Loan::getMaxRenewals()
{
    return Loan::maxRenewals;
}

int Loan::getLoanPeriod()
{
    return Loan::loanPeriod;
}

bool Loan::isOverdue() const
{
    if (isReturned)
        return false;
    return time(nullptr) > dueDate;
}

bool Loan::renew()
{
    if (isReturned)
    {
        cerr << "Error: Cannot renew a returned loan." << endl;
        return false;
    }
    if (renewalCount >= Loan::maxRenewals)
    {
        cerr << "Error: Maximum renewal limit reached." << endl;
        return false;
    }
    time_t now = time(nullptr);
    if (now > dueDate)
    {
        cerr << "Error: Cannot renew overdue loan." << endl;
        return false;
    }
    if (loanId.empty() || userId.empty() || resourceId.empty()) {
        cerr << "Error: Cannot renew loan with missing information." << endl;
        return false;
    }
    dueDate = dueDate + Loan::loanPeriod;
    ++renewalCount;
    return true;
}

void Loan::markReturned()
{
    if (isReturned) {
        cerr << "Warning: Loan already marked as returned." << endl;
        return;
    }
    if (loanId.empty() || userId.empty() || resourceId.empty()) {
        cerr << "Error: Cannot return loan with missing information." << endl;
        return;
    }
    returnDate = time(nullptr);
    isReturned = true;
}

void Loan::setMaxRenewals(int value)
{
    if (value < 0) {
        cerr << "Warning: Invalid max renewals value. Setting to default (2)." << endl;
        Loan::maxRenewals = 2;
    }
    else if (value > 10) {
        cerr << "Warning: Max renewals too high. Setting to 10." << endl;
        Loan::maxRenewals = 10;
    }
    else
        Loan::maxRenewals = value;
}

void Loan::setLoanPeriod(int days)
{
    const int SECONDS_PER_DAY = 86400;
    if (days < 1) {
        cerr << "Warning: Invalid loan period. Setting to default (14 days)." << endl;
        days = 14;
    }
    if (days > 365) {
        cerr << "Warning: Loan period too long. Setting to 365 days." << endl;
        days = 365;
    }

    // Check for integer overflow
    if (days > INT_MAX / SECONDS_PER_DAY)
    {
        cerr << "Warning: Loan period causes overflow. Setting to maximum safe value." << endl;
        loanPeriod = INT_MAX;
    }
    else
    {
        loanPeriod = days * SECONDS_PER_DAY;
    }
}

bool Loan::isValidLoanId(const string &loanId) const
{
    if (loanId.empty()) return false;
    if (loanId.length() < 3 || loanId.length() > 30) return false;
    
    for (char c : loanId) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool Loan::isValidId(const string &id) const
{
    if (id.empty()) return false;
    if (id.length() < 3 || id.length() > 20) return false;
    
    for (char c : id) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool Loan::isValidDate(time_t date) const
{
    if (date < 0) return false;
    time_t now = time(nullptr);
    time_t maxDate = now + (365 * 24 * 60 * 60 * 10); // 10 years from now
    return date <= maxDate;
}

// Json
json Loan::toJson() const
{
    return json{
        {"loanId", loanId},
        {"userId", userId},
        {"resourceId", resourceId},
        {"borrowDate", borrowDate},
        {"dueDate", dueDate},
        {"returnDate", returnDate},
        {"isReturned", isReturned},
        {"renewalCount", renewalCount}};
}

Loan Loan::fromJson(const json &j)
{
    try {
        Loan loan(
            j.at("loanId").get<string>(),
            j.at("userId").get<string>(),
            j.at("resourceId").get<string>(),
            j.at("borrowDate").get<time_t>(),
            j.at("dueDate").get<time_t>());
        loan.returnDate = j.at("returnDate").get<time_t>();
        loan.isReturned = j.at("isReturned").get<bool>();
        loan.renewalCount = j.at("renewalCount").get<int>();

        if (loan.renewalCount < 0) {
            cerr << "Warning: Invalid renewal count in JSON. Setting to 0." << endl;
            loan.renewalCount = 0;
        }
        if (loan.renewalCount > maxRenewals) {
            cerr << "Warning: Renewal count exceeds maximum. Setting to maximum." << endl;
            loan.renewalCount = maxRenewals;
        }

        return loan;
    } catch (const exception &e) {
        cerr << "Error parsing Loan from JSON: " << e.what() << endl;
        return Loan();
    }
}