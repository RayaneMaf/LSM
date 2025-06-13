#include "persistence.h"
#include "Json/json.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

using json = nlohmann::json;
namespace fs = std::filesystem;

void Persistence::validateFilepath(const string &filepath)
{
    if (filepath.empty())
    {
        throw invalid_argument("File path cannot be empty");
    }
    if (filepath.length() > 260)
    { // Windows MAX_PATH limit
        throw invalid_argument("File path too long");
    }
    // Check for invalid characters
    string invalidChars = "<>:\"|?*";
    for (char c : invalidChars)
    {
        if (filepath.find(c) != string::npos)
        {
            throw invalid_argument("File path contains invalid characters");
        }
    }
}

void Persistence::validateFileExtension(const string &filepath)
{
    size_t dotPos = filepath.find_last_of('.');
    if (dotPos == string::npos)
    {
        throw invalid_argument("File must have an extension");
    }
    string extension = filepath.substr(dotPos);
    if (extension != ".json" && extension != ".JSON")
    {
        throw invalid_argument("File must have .json extension");
    }
}

bool Persistence::isValidJsonFile(const string &filepath)
{
    ifstream ifs(filepath);
    if (!ifs.is_open())
        return false;

    try
    {
        json j;
        ifs >> j;
        return true;
    }
    catch (const json::exception &)
    {
        return false;
    }
}

void Persistence::createBackup(const string &filepath)
{
    if (fs::exists(filepath))
    {
        string backupPath = filepath + ".backup";
        try
        {
            fs::copy_file(filepath, backupPath, fs::copy_options::overwrite_existing);
        }
        catch (const fs::filesystem_error &)
        {
            // Backup failed, but don't stop the save operation
        }
    }
}

bool Persistence::saveToFile(
    const string &filepath,
    const vector<User> &users,
    const vector<unique_ptr<Resource>> &resources,
    const vector<Loan> &loans,
    const vector<Reservation> &reservations,
    const vector<Notification> &notifications,
    const vector<LibraryEvent> &events)
{
    try
    {
        validateFilepath(filepath);
        validateFileExtension(filepath);

        // Create backup of existing file
        createBackup(filepath);

        // Ensure directory exists
        fs::path filePath(filepath);
        if (filePath.has_parent_path())
        {
            fs::create_directories(filePath.parent_path());
        }

        json j;

        // Config
        j["config"] = {
            {"maxRenewals", Loan::getMaxRenewals()},
            {"loanPeriodDays", Loan::getLoanPeriod() / (24 * 60 * 60)}};

        // Users
        try
        {
            for (const auto &u : users)
                j["users"].push_back(u.toJson());
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to serialize users: " + string(e.what()));
        }

        // Resources
        try
        {
            for (const auto &r : resources)
            {
                if (r == nullptr)
                {
                    throw runtime_error("Null resource pointer found");
                }
                j["resources"].push_back(r->toJson());
            }
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to serialize resources: " + string(e.what()));
        }

        // Loans
        try
        {
            for (const auto &l : loans)
                j["loans"].push_back(l.toJson());
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to serialize loans: " + string(e.what()));
        }

        // Reservations
        try
        {
            for (const auto &r : reservations)
                j["reservations"].push_back(r.toJson());
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to serialize reservations: " + string(e.what()));
        }

        // Notifications
        try
        {
            for (const auto &n : notifications)
                j["notifications"].push_back(n.toJson());
        }
        catch (const exception &e)
        {
            throw runtime_error("Failed to serialize notifications: " + string(e.what()));
        }

        // Events
        try
        {
            for (const auto &e : events)
                j["events"].push_back(e.toJson());
        }
        catch (const exception &ex)
        {
            throw runtime_error("Failed to serialize events: " + string(ex.what()));
        }

        ofstream ofs(filepath);
        if (!ofs.is_open())
        {
            throw runtime_error("Cannot open file for writing: " + filepath);
        }

        ofs << j.dump(2);
        if (ofs.fail())
        {
            throw runtime_error("Failed to write to file: " + filepath);
        }

        return true;
    }
    catch (const exception &e)
    {
        cerr << "Save error: " << e.what() << endl;
        return false;
    }
}

bool Persistence::loadFromFile(
    const string &filepath,
    vector<User> &users,
    vector<unique_ptr<Resource>> &resources,
    vector<Loan> &loans,
    vector<Reservation> &reservations,
    vector<Notification> &notifications,
    vector<LibraryEvent> &events)
{
    try
    {
        validateFilepath(filepath);
        validateFileExtension(filepath);

        if (!fs::exists(filepath))
        {
            throw runtime_error("File does not exist: " + filepath);
        }

        if (!isValidJsonFile(filepath))
        {
            throw runtime_error("Invalid JSON file: " + filepath);
        }

        ifstream ifs(filepath);
        if (!ifs.is_open())
        {
            throw runtime_error("Cannot open file for reading: " + filepath);
        }

        json j;
        try
        {
            ifs >> j;
        }
        catch (const json::exception &e)
        {
            throw runtime_error("JSON parsing error: " + string(e.what()));
        }

        // Clear existing data
        users.clear();
        resources.clear();
        loans.clear();
        reservations.clear();
        notifications.clear();
        events.clear();

        // Config
        if (j.contains("config"))
        {
            auto cfg = j["config"];
            if (cfg.contains("maxRenewals"))
            {
                int maxRenewals = cfg["maxRenewals"].get<int>();
                if (maxRenewals < 0 || maxRenewals > 10)
                {
                    throw invalid_argument("Invalid maxRenewals value");
                }
                Loan::setMaxRenewals(maxRenewals);
            }
            if (cfg.contains("loanPeriodDays"))
            {
                int loanPeriod = cfg["loanPeriodDays"].get<int>();
                if (loanPeriod < 1 || loanPeriod > 365)
                {
                    throw invalid_argument("Invalid loanPeriodDays value");
                }
                Loan::setLoanPeriod(loanPeriod);
            }
        }

        // Users
        if (j.contains("users"))
        {
            try
            {
                for (const auto &uj : j["users"])
                    users.push_back(User::fromJson(uj));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load users: " + string(e.what()));
            }
        }

        // Resources
        if (j.contains("resources"))
        {
            try
            {
                for (const auto &rj : j["resources"])
                    resources.push_back(Resource::fromJson(rj));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load resources: " + string(e.what()));
            }
        }

        // Loans
        if (j.contains("loans"))
        {
            try
            {
                for (const auto &lj : j["loans"])
                    loans.push_back(Loan::fromJson(lj));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load loans: " + string(e.what()));
            }
        }

        // Reservations
        if (j.contains("reservations"))
        {
            try
            {
                for (const auto &rj : j["reservations"])
                    reservations.push_back(Reservation::fromJson(rj));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load reservations: " + string(e.what()));
            }
        }

        // Notifications
        if (j.contains("notifications"))
        {
            try
            {
                for (const auto &nj : j["notifications"])
                    notifications.push_back(Notification::fromJson(nj));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load notifications: " + string(e.what()));
            }
        }

        // Events
        if (j.contains("events"))
        {
            try
            {
                for (const auto &ej : j["events"])
                    events.push_back(LibraryEvent::fromJson(ej));
            }
            catch (const exception &e)
            {
                throw runtime_error("Failed to load events: " + string(e.what()));
            }
        }

        return true;
    }
    catch (const exception &e)
    {
        cerr << "Load error: " << e.what() << endl;
        return false;
    }
}