#include "libraryevent.h"

LibraryEvent::LibraryEvent(const string &eventId, const string &title, const string &description, time_t eventDate, const string &location)
    : eventId(eventId), title(title), description(description), eventDate(eventDate), location(location)
{
    validateEventId(eventId);
    validateTitle(title);
    validateDescription(description);
    validateEventDate(eventDate);
    validateLocation(location);
}

void LibraryEvent::validateEventId(const string &id) const
{
    if (id.empty())
    {
        throw invalid_argument("Event ID cannot be empty");
    }
    if (id.length() > 30)
    {
        throw invalid_argument("Event ID too long (max 30 characters)");
    }
    for (char c : id)
    {
        if (!isalnum(c) && c != '-' && c != '_')
        {
            throw invalid_argument("Event ID contains invalid characters");
        }
    }
}

void LibraryEvent::validateTitle(const string &title) const
{
    if (title.empty())
    {
        throw invalid_argument("Event title cannot be empty");
    }
    if (title.length() > 100)
    {
        throw invalid_argument("Event title too long (max 100 characters)");
    }
    if (title.find_first_not_of(" \t\n\r") == string::npos)
    {
        throw invalid_argument("Event title cannot be only whitespace");
    }
}

void LibraryEvent::validateDescription(const string &desc) const
{
    if (desc.empty())
    {
        throw invalid_argument("Event description cannot be empty");
    }
    if (desc.length() > 1000)
    {
        throw invalid_argument("Event description too long (max 1000 characters)");
    }
    if (desc.find_first_not_of(" \t\n\r") == string::npos)
    {
        throw invalid_argument("Event description cannot be only whitespace");
    }
}

void LibraryEvent::validateEventDate(time_t date) const
{
    if (date <= 0)
    {
        throw invalid_argument("Invalid event date");
    }
    time_t currentTime = time(nullptr);
    if (date < currentTime - 86400)
    { // Allow events from yesterday
        throw invalid_argument("Event date cannot be in the past");
    }
    // Check for reasonable future limit (1 year)
    if (date > currentTime + (365 * 24 * 3600))
    {
        throw invalid_argument("Event date too far in the future (max 1 year)");
    }
}

void LibraryEvent::validateLocation(const string &loc) const
{
    if (loc.empty())
    {
        throw invalid_argument("Event location cannot be empty");
    }
    if (loc.length() > 200)
    {
        throw invalid_argument("Event location too long (max 200 characters)");
    }
    if (loc.find_first_not_of(" \t\n\r") == string::npos)
    {
        throw invalid_argument("Event location cannot be only whitespace");
    }
}

const string &LibraryEvent::getEventId() const
{
    return eventId;
}

const string &LibraryEvent::getTitle() const
{
    return title;
}

const string &LibraryEvent::getDescription() const
{
    return description;
}

time_t LibraryEvent::getEventDate() const
{
    return eventDate;
}

const string &LibraryEvent::getLocation() const
{
    return location;
}

// Json
json LibraryEvent::toJson() const
{
    try
    {
        return json{
            {"eventId", eventId},
            {"title", title},
            {"description", description},
            {"eventDate", eventDate},
            {"location", location}};
    }
    catch (const exception &e)
    {
        throw runtime_error("Failed to serialize event to JSON: " + string(e.what()));
    }
}

LibraryEvent LibraryEvent::fromJson(const json &j)
{
    try
    {
        if (!j.contains("eventId") || !j.contains("title") ||
            !j.contains("description") || !j.contains("eventDate") || !j.contains("location"))
        {
            throw invalid_argument("Missing required fields in JSON");
        }

        return LibraryEvent{
            j.at("eventId").get<string>(),
            j.at("title").get<string>(),
            j.at("description").get<string>(),
            j.at("eventDate").get<time_t>(),
            j.at("location").get<string>()};
    }
    catch (const json::exception &e)
    {
        throw runtime_error("JSON parsing error: " + string(e.what()));
    }
    catch (const exception &e)
    {
        throw runtime_error("Failed to create event from JSON: " + string(e.what()));
    }
}