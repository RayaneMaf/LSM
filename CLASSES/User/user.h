#ifndef USER_H
#define USER_H
#include <string>
#include "Json/json.hpp"
using json = nlohmann::json;
using namespace std;

enum class UserRole
{
    Student,
    Teacher,
    LibraryEmployee,
    LibraryAdmin,
};

class User
{
private:
    string userId;
    string name;
    string email;
    UserRole role;

    // Helper validation methods
    bool isValidEmail(const string &email) const;
    bool isValidUserId(const string &userId) const;
    bool isValidName(const string &name) const;

public:
    // Constructor/Destructor
    User(const string & = "", const string & = "", const string & = "", UserRole = UserRole::Student);
    ~User() = default;

    // Setters
    void setUserId(const string & = "");
    void setName(const string & = "");
    void setEmail(const string & = "");
    void setUserRole(UserRole = UserRole::Student);

    // Getters
    const string &getUserId() const;
    const string &getName() const;
    const string &getEmail() const;
    UserRole getUserRole() const;

    // Json
    json toJson() const;
    static User fromJson(const json &);
};

#endif