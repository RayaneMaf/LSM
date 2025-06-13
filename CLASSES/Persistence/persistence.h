#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "User/user.h"
#include "Resource/resource.h"
#include "Loan/loan.h"
#include "Reservation/reservation.h"
#include "Notification/notification.h"
#include "LibraryEvent/libraryevent.h"
using namespace std;

class Persistence
{
private:
    // Validation helpers
    static void validateFilepath(const string &filepath);
    static void validateFileExtension(const string &filepath);
    static bool isValidJsonFile(const string &filepath);
    static void createBackup(const string &filepath);

public:
    // Save all data to a Json file
    static bool saveToFile(
        const string &filepath,
        const vector<User> &users,
        const vector<unique_ptr<Resource>> &resources,
        const vector<Loan> &loans,
        const vector<Reservation> &reservations,
        const vector<Notification> &notifications,
        const vector<LibraryEvent> &events);

    // Load all data from a Json file
    static bool loadFromFile(
        const string &filepath,
        vector<User> &users,
        vector<unique_ptr<Resource>> &resources,
        vector<Loan> &loans,
        vector<Reservation> &reservations,
        vector<Notification> &notifications,
        vector<LibraryEvent> &events);
};

#endif