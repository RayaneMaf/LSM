#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <ctime>
#include <stdexcept>
#include "Json/json.hpp"

using namespace std;
using json = nlohmann::json;

class Notification
{
private:
    string notificationId;
    string userId;
    string message;
    time_t sentDate;
    bool readFlag;

    // Validation helpers
    void validateNotificationId(const string &id) const;
    void validateUserId(const string &id) const;
    void validateMessage(const string &msg) const;
    void validateSentDate(time_t date) const;

public:
    // Constructor/Destructor
    Notification(const string & = "", const string & = "", const string & = "", time_t = 0, bool = false);
    ~Notification() = default;

    // Getters
    const string &getNotificationId() const;
    const string &getUserId() const;
    const string &getMessage() const;
    time_t getSentDate() const;
    bool isRead() const;

    void markRead();

    // Json
    json toJson() const;
    static Notification fromJson(const json &j);
};

#endif