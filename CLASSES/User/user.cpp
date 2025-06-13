#include "user.h"
#include <iostream>
#include <regex>
using namespace std;

User::User(const string &userId, const string &name, const string &email, UserRole role) : userId(userId), email(email), name(name), role(role) 
{
    if (!isValidUserId(userId) && !userId.empty()) {
        cerr << "Warning: Invalid User ID provided. Using empty string." << endl;
        this->userId = "";
    }
    if (!isValidName(name) && !name.empty()) {
        cerr << "Warning: Invalid name provided. Using empty string." << endl;
        this->name = "";
    }
    if (!isValidEmail(email) && !email.empty()) {
        cerr << "Warning: Invalid email provided. Using empty string." << endl;
        this->email = "";
    }
}

const string &User::getEmail() const
{
    return email;
}

const string &User::getName() const
{
    return name;
}

const string &User::getUserId() const
{
    return userId;
}

UserRole User::getUserRole() const
{
    return role;
}

void User::setEmail(const string &email)
{
    if (email.empty()) {
        this->email = email;
        return;
    }
    
    if (!isValidEmail(email)) {
        cerr << "Error: Invalid email format. Email not updated." << endl;
        return;
    }
    this->email = email;
}

void User::setName(const string &name)
{
    if (name.empty()) {
        this->name = name;
        return;
    }
    
    if (!isValidName(name)) {
        cerr << "Error: Invalid name format. Name not updated." << endl;
        return;
    }
    this->name = name;
}

void User::setUserId(const string &userId)
{
    if (userId.empty()) {
        this->userId = userId;
        return;
    }
    
    if (!isValidUserId(userId)) {
        cerr << "Error: Invalid User ID format. User ID not updated." << endl;
        return;
    }
    this->userId = userId;
}

void User::setUserRole(UserRole role)
{
    this->role = role;
}

bool User::isValidEmail(const string &email) const
{
    if (email.empty()) return false;
    if (email.length() > 100) return false;
    
    regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

bool User::isValidUserId(const string &userId) const
{
    if (userId.empty()) return false;
    if (userId.length() < 3 || userId.length() > 20) return false;
    
    for (char c : userId) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool User::isValidName(const string &name) const
{
    if (name.empty()) return false;
    if (name.length() > 50) return false;
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
    }
    return true;
}

// Json
json User::toJson() const
{
    return json{
        {"userId", userId},
        {"name", name},
        {"email", email},
        {"role", role}};
}

User User::fromJson(const json &j)
{
    try {
        return User(j.at("userId").get<string>(), j.at("name").get<string>(), j.at("email").get<string>(), j.at("role").get<UserRole>());
    } catch (const exception &e) {
        cerr << "Error parsing User from JSON: " << e.what() << endl;
        return User();
    }
}