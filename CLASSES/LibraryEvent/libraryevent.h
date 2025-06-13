#ifndef LIBRARYEVENT_H
#define LIBRARYEVENT_H

#include <string>
#include <ctime>
#include <stdexcept>
#include "Json/json.hpp"
using json = nlohmann::json;
using namespace std;

class LibraryEvent
{
private:
    string eventId;
    string title;
    string description;
    time_t eventDate;
    string location;

    // Validation helpers
    void validateEventId(const string &id) const;
    void validateTitle(const string &title) const;
    void validateDescription(const string &desc) const;
    void validateEventDate(time_t date) const;
    void validateLocation(const string &loc) const;

public:
    // Constructor/Destructor
    LibraryEvent(const string & = "", const string & = "", const string & = "", time_t = 0, const string & = "");
    ~LibraryEvent() = default;

    // Getters
    const string &getEventId() const;
    const string &getTitle() const;
    const string &getDescription() const;
    time_t getEventDate() const;
    const string &getLocation() const;

    // Json
    json toJson() const;
    static LibraryEvent fromJson(const json &j);
};

#endif