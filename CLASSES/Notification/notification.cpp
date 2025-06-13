#include "notification.h"

Notification::Notification(const string &notificationId, const string &userId, const string &message, time_t sentDate, bool readFlag)
    : notificationId(notificationId), userId(userId), message(message), sentDate(sentDate), readFlag(readFlag)
{
    validateNotificationId(notificationId);
    validateUserId(userId);
    validateMessage(message);
    validateSentDate(sentDate);
}

void Notification::validateNotificationId(const string &id) const
{
    if (id.empty())
    {
        throw invalid_argument("Notification ID cannot be empty");
    }
    if (id.length() > 50)
    {
        throw invalid_argument("Notification ID too long (max 50 characters)");
    }
    for (char c : id)
    {
        if (!isalnum(c) && c != '-' && c != '_')
        {
            throw invalid_argument("Notification ID contains invalid characters");
        }
    }
}

void Notification::validateUserId(const string &id) const
{
    if (id.empty())
    {
        throw invalid_argument("User ID cannot be empty");
    }
    if (id.length() > 30)
    {
        throw invalid_argument("User ID too long (max 30 characters)");
    }
    for (char c : id)
    {
        if (!isalnum(c) && c != '-' && c != '_')
        {
            throw invalid_argument("User ID contains invalid characters");
        }
    }
}

void Notification::validateMessage(const string &msg) const
{
    if (msg.empty())
    {
        throw invalid_argument("Message cannot be empty");
    }
    if (msg.length() > 500)
    {
        throw invalid_argument("Message too long (max 500 characters)");
    }
}

void Notification::validateSentDate(time_t date) const
{
    if (date < 0)
    {
        throw invalid_argument("Invalid sent date");
    }
    time_t currentTime = time(nullptr);
    if (date > currentTime + 86400)
    { // Allow 1 day future for time zone differences
        throw invalid_argument("Sent date cannot be in the future");
    }
}

const string &Notification::getNotificationId() const
{
    return notificationId;
}

const string &Notification::getUserId() const
{
    return userId;
}

const string &Notification::getMessage() const
{
    return message;
}

time_t Notification::getSentDate() const
{
    return sentDate;
}

bool Notification::isRead() const
{
    return readFlag;
}

void Notification::markRead()
{
    readFlag = true;
}

// Json
json Notification::toJson() const
{
    try
    {
        return json{
            {"notificationId", notificationId},
            {"userId", userId},
            {"message", message},
            {"sentDate", sentDate},
            {"readFlag", readFlag}};
    }
    catch (const exception &e)
    {
        throw runtime_error("Failed to serialize notification to JSON: " + string(e.what()));
    }
}

Notification Notification::fromJson(const json &j)
{
    try
    {
        if (!j.contains("notificationId") || !j.contains("userId") ||
            !j.contains("message") || !j.contains("sentDate") || !j.contains("readFlag"))
        {
            throw invalid_argument("Missing required fields in JSON");
        }

        return Notification{
            j.at("notificationId").get<string>(),
            j.at("userId").get<string>(),
            j.at("message").get<string>(),
            j.at("sentDate").get<time_t>(),
            j.at("readFlag").get<bool>()};
    }
    catch (const json::exception &e)
    {
        throw runtime_error("JSON parsing error: " + string(e.what()));
    }
    catch (const exception &e)
    {
        throw runtime_error("Failed to create notification from JSON: " + string(e.what()));
    }
}