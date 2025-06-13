#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

// Include all your headers
#include "User/user.h"
#include "Resource/resource.h"
#include "Resource/book.h"
#include "Resource/article.h"
#include "Resource/thesis.h"
#include "Loan/loan.h"
#include "Reservation/reservation.h"
#include "Notification/notification.h"
#include "LibraryEvent/libraryevent.h"
#include "Persistence/persistence.h"

using namespace std;

class LibrarySystem
{
private:
    vector<User> users;
    vector<unique_ptr<Resource>> resources;
    vector<Loan> loans;
    vector<Reservation> reservations;
    vector<Notification> notifications;
    vector<LibraryEvent> events;

    string currentUserId;
    const string DATA_FILE = "library_data.json";

    // Helper methods
    string generateId(const string &prefix);
    User *findUser(const string &userId);
    Resource *findResource(const string &resourceId);
    Loan *findActiveLoan(const string &userId, const string &resourceId);
    void displayMenu();
    void displayUserMenu();
    void displayAdminMenu();

    // User operations
    void registerUser();
    void loginUser();
    void logout();

    // Resource operations
    void addResource();
    void searchResources();
    void displayAllResources();
    void removeResource();

    // Loan operations
    void borrowResource();
    void returnResource();
    void renewLoan();
    void viewMyLoans();
    void viewAllLoans();

    // Reservation operations
    void makeReservation();
    void cancelReservation();
    void viewMyReservations();
    void fulfillReservation();

    // Notification operations
    void sendNotification();
    void viewMyNotifications();
    void markNotificationRead();

    // Event operations
    void createEvent();
    void viewEvents();

    // Utility methods
    void saveData();
    void loadData();
    bool isAdmin();
    string getCurrentTimestamp();
    void checkOverdueLoans();

public:
    LibrarySystem();
    ~LibrarySystem();

    void run();
};

// Implementation
LibrarySystem::LibrarySystem()
{
    loadData();

    // Create default admin user if no users exist
    if (users.empty())
    {
        User admin("admin001", "System Administrator", "admin@library.com", UserRole::LibraryAdmin);
        users.push_back(admin);
        cout << "Default admin user created: admin001\n";
    }
}

LibrarySystem::~LibrarySystem()
{
    saveData();
}

string LibrarySystem::generateId(const string &prefix)
{
    static int counter = 1000;
    return prefix + to_string(++counter);
}

User *LibrarySystem::findUser(const string &userId)
{
    auto it = find_if(users.begin(), users.end(),
                      [&userId](const User &user)
                      { return user.getUserId() == userId; });
    return (it != users.end()) ? &(*it) : nullptr;
}

Resource *LibrarySystem::findResource(const string &resourceId)
{
    auto it = find_if(resources.begin(), resources.end(),
                      [&resourceId](const unique_ptr<Resource> &resource)
                      {
                          return resource->getResourceId() == resourceId;
                      });
    return (it != resources.end()) ? it->get() : nullptr;
}

Loan *LibrarySystem::findActiveLoan(const string &userId, const string &resourceId)
{
    auto it = find_if(loans.begin(), loans.end(),
                      [&userId, &resourceId](const Loan &loan)
                      {
                          return loan.getUserId() == userId &&
                                 loan.getResourceId() == resourceId &&
                                 !loan.getIsReturned();
                      });
    return (it != loans.end()) ? &(*it) : nullptr;
}

void LibrarySystem::displayMenu()
{
    cout << "\n=== Library Management System ===\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. View Events\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void LibrarySystem::displayUserMenu()
{
    cout << "\n=== User Menu ===\n";
    cout << "1. Search Resources\n";
    cout << "2. Borrow Resource\n";
    cout << "3. Return Resource\n";
    cout << "4. Renew Loan\n";
    cout << "5. Make Reservation\n";
    cout << "6. Cancel Reservation\n";
    cout << "7. View My Loans\n";
    cout << "8. View My Reservations\n";
    cout << "9. View My Notifications\n";
    cout << "10. View All Resources\n";
    cout << "0. Logout\n";
    cout << "Choose an option: ";
}

void LibrarySystem::displayAdminMenu()
{
    cout << "\n=== Admin Menu ===\n";
    cout << "1. Search Resources\n";
    cout << "2. Add Resource\n";
    cout << "3. Remove Resource\n";
    cout << "4. View All Resources\n";
    cout << "5. View All Loans\n";
    cout << "6. Fulfill Reservation\n";
    cout << "7. Send Notification\n";
    cout << "8. Create Event\n";
    cout << "9. View Events\n";
    cout << "10. Check Overdue Loans\n";
    cout << "0. Logout\n";
    cout << "Choose an option: ";
}

void LibrarySystem::registerUser()
{
    string name, email;
    int roleChoice;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Select role:\n1. Student\n2. Teacher\nChoice: ";
    cin >> roleChoice;

    UserRole role = (roleChoice == 2) ? UserRole::Teacher : UserRole::Student;
    string userId = generateId("USER");

    User newUser(userId, name, email, role);
    users.push_back(newUser);

    cout << "User registered successfully! Your ID: " << userId << "\n";
}

void LibrarySystem::loginUser()
{
    string userId;
    cout << "Enter User ID: ";
    cin >> userId;

    User *user = findUser(userId);
    if (user)
    {
        currentUserId = userId;
        cout << "Login successful! Welcome, " << user->getName() << "\n";
    }
    else
    {
        cout << "User not found!\n";
    }
}

void LibrarySystem::logout()
{
    currentUserId.clear();
    cout << "Logged out successfully!\n";
}

void LibrarySystem::addResource()
{
    int type;
    cout << "Select resource type:\n1. Book\n2. Article\n3. Thesis\nChoice: ";
    cin >> type;

    string title, author, category;
    int year;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    cout << "Enter category: ";
    getline(cin, category);

    cout << "Enter publication year: ";
    cin >> year;

    string resourceId = generateId("RES");

    switch (type)
    {
    case 1:
    {
        string publisher, isbn, edition;
        int pages;

        cout << "Enter publisher: ";
        cin.ignore();
        getline(cin, publisher);

        cout << "Enter number of pages: ";
        cin >> pages;

        cout << "Enter ISBN: ";
        cin.ignore();
        getline(cin, isbn);

        cout << "Enter edition: ";
        getline(cin, edition);

        resources.push_back(make_unique<Book>(title, author, resourceId, category, year, publisher, pages, isbn, edition));
        break;
    }
    case 2:
    {
        string magazine, doi;
        int volume, issue, startPage, endPage;

        cout << "Enter magazine: ";
        cin.ignore();
        getline(cin, magazine);

        cout << "Enter volume: ";
        cin >> volume;

        cout << "Enter issue: ";
        cin >> issue;

        cout << "Enter DOI: ";
        cin.ignore();
        getline(cin, doi);

        cout << "Enter start page: ";
        cin >> startPage;

        cout << "Enter end page: ";
        cin >> endPage;

        resources.push_back(make_unique<Article>(title, author, resourceId, category, year, magazine, volume, issue, doi, startPage, endPage));
        break;
    }
    case 3:
    {
        string university, department, supervisor, degree, abstractText;
        int thesisTypeChoice, pages;

        cout << "Enter university: ";
        cin.ignore();
        getline(cin, university);

        cout << "Enter department: ";
        getline(cin, department);

        cout << "Enter supervisor: ";
        getline(cin, supervisor);

        cout << "Select thesis type:\n1. Bachelor\n2. Master\n3. PhD\n4. Research\nChoice: ";
        cin >> thesisTypeChoice;

        ThesisType thesisType = static_cast<ThesisType>(thesisTypeChoice - 1);

        cout << "Enter degree: ";
        cin.ignore();
        getline(cin, degree);

        cout << "Enter page count: ";
        cin >> pages;

        cout << "Enter abstract: ";
        cin.ignore();
        getline(cin, abstractText);

        resources.push_back(make_unique<Thesis>(title, author, resourceId, category, year, university, department, supervisor, thesisType, degree, pages, abstractText));
        break;
    }
    }

    cout << "Resource added successfully! ID: " << resourceId << "\n";
}

void LibrarySystem::searchResources()
{
    string keyword;
    cout << "Enter search keyword: ";
    cin.ignore();
    getline(cin, keyword);

    cout << "\n=== Search Results ===\n";
    bool found = false;

    for (const auto &resource : resources)
    {
        if (resource->matchesKeyword(keyword))
        {
            resource->displayInfo();
            cout << "---\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No resources found matching '" << keyword << "'\n";
    }
}

void LibrarySystem::displayAllResources()
{
    cout << "\n=== All Resources ===\n";
    for (const auto &resource : resources)
    {
        resource->displayInfo();
        cout << "---\n";
    }
}

void LibrarySystem::borrowResource()
{
    string resourceId;
    cout << "Enter Resource ID to borrow: ";
    cin >> resourceId;

    Resource *resource = findResource(resourceId);
    if (!resource)
    {
        cout << "Resource not found!\n";
        return;
    }

    if (!resource->getAvailable())
    {
        cout << "Resource is not available for borrowing!\n";
        return;
    }

    // Check if user already has this resource
    if (findActiveLoan(currentUserId, resourceId))
    {
        cout << "You already have this resource borrowed!\n";
        return;
    }

    string loanId = generateId("LOAN");
    time_t now = time(nullptr);
    time_t dueDate = now + Loan::getLoanPeriod();

    Loan newLoan(loanId, currentUserId, resourceId, now, dueDate);
    loans.push_back(newLoan);

    resource->setAvailable(false);

    cout << "Resource borrowed successfully!\n";
    cout << "Loan ID: " << loanId << "\n";
    cout << "Due Date: " << ctime(&dueDate);
}

void LibrarySystem::returnResource()
{
    string resourceId;
    cout << "Enter Resource ID to return: ";
    cin >> resourceId;

    Loan *loan = findActiveLoan(currentUserId, resourceId);
    if (!loan)
    {
        cout << "No active loan found for this resource!\n";
        return;
    }

    loan->markReturned();

    Resource *resource = findResource(resourceId);
    if (resource)
    {
        resource->setAvailable(true);
    }

    cout << "Resource returned successfully!\n";
}

void LibrarySystem::renewLoan()
{
    string resourceId;
    cout << "Enter Resource ID to renew: ";
    cin >> resourceId;

    Loan *loan = findActiveLoan(currentUserId, resourceId);
    if (!loan)
    {
        cout << "No active loan found for this resource!\n";
        return;
    }

    if (loan->renew())
    {
        cout << "Loan renewed successfully!\n";
    }
    else
    {
        cout << "Cannot renew loan. Maximum renewals reached.\n";
    }
}

void LibrarySystem::viewMyLoans()
{
    cout << "\n=== My Loans ===\n";
    bool found = false;

    for (const auto &loan : loans)
    {
        if (loan.getUserId() == currentUserId && !loan.getIsReturned())
        {
            cout << "Loan ID: " << loan.getLoanId() << "\n";
            cout << "Resource ID: " << loan.getResourceId() << "\n";
            cout << "Borrow Date: " << loan.getBorrowDate();
            cout << "Due Date: " << loan.getDueDate();
            cout << "Renewals: " << loan.getRenewalCount() << "/" << Loan::getMaxRenewals() << "\n";
            if (loan.isOverdue())
            {
                cout << "*** OVERDUE ***\n";
            }
            cout << "---\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No active loans found.\n";
    }
}

void LibrarySystem::makeReservation()
{
    string resourceId;
    cout << "Enter Resource ID to reserve: ";
    cin >> resourceId;

    Resource *resource = findResource(resourceId);
    if (!resource)
    {
        cout << "Resource not found!\n";
        return;
    }

    if (resource->getAvailable())
    {
        cout << "Resource is available. You can borrow it directly!\n";
        return;
    }

    string reservationId = generateId("RES");
    time_t now = time(nullptr);

    Reservation newReservation(reservationId, currentUserId, resourceId, now);
    reservations.push_back(newReservation);

    cout << "Reservation made successfully!\n";
    cout << "Reservation ID: " << reservationId << "\n";
}

void LibrarySystem::viewMyReservations()
{
    cout << "\n=== My Reservations ===\n";
    bool found = false;

    for (const auto &reservation : reservations)
    {
        if (reservation.getUserId() == currentUserId && reservation.isPending())
        {
            cout << "Reservation ID: " << reservation.getReservationId() << "\n";
            cout << "Resource ID: " << reservation.getResourceId() << "\n";
            cout << "Reservation Date: " << reservation.getReservationDate();
            cout << "Status: Pending\n";
            cout << "---\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No pending reservations found.\n";
    }
}

void LibrarySystem::viewMyNotifications()
{
    cout << "\n=== My Notifications ===\n";
    bool found = false;

    for (auto &notification : notifications)
    {
        if (notification.getUserId() == currentUserId)
        {
            cout << "ID: " << notification.getNotificationId() << "\n";
            cout << "Message: " << notification.getMessage() << "\n";
            cout << "Sent: " << notification.getSentDate();
            cout << "Status: " << (notification.isRead() ? "Read" : "Unread") << "\n";

            if (!notification.isRead())
            {
                cout << "Mark as read? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    notification.markRead();
                }
            }

            cout << "---\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No notifications found.\n";
    }
}

void LibrarySystem::viewEvents()
{
    cout << "\n=== Library Events ===\n";
    if (events.empty())
    {
        cout << "No events scheduled.\n";
        return;
    }

    for (const auto &event : events)
    {
        cout << "Event ID: " << event.getEventId() << "\n";
        cout << "Title: " << event.getTitle() << "\n";
        cout << "Description: " << event.getDescription() << "\n";
        cout << "Date: " << event.getEventDate();
        cout << "Location: " << event.getLocation() << "\n";
        cout << "---\n";
    }
}

bool LibrarySystem::isAdmin()
{
    User *user = findUser(currentUserId);
    return user && (user->getUserRole() == UserRole::LibraryAdmin ||
                    user->getUserRole() == UserRole::LibraryEmployee);
}

void LibrarySystem::saveData()
{
    if (Persistence::saveToFile(DATA_FILE, users, resources, loans, reservations, notifications, events))
    {
        cout << "Data saved successfully.\n";
    }
}

void LibrarySystem::loadData()
{
    if (Persistence::loadFromFile(DATA_FILE, users, resources, loans, reservations, notifications, events))
    {
        cout << "Data loaded successfully.\n";
    }
}

void LibrarySystem::run()
{
    int choice;

    while (true)
    {
        if (currentUserId.empty())
        {
            displayMenu();
            cin >> choice;

            switch (choice)
            {
            case 1:
                loginUser();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                viewEvents();
                break;
            case 0:
                cout << "Thank you for using the Library Management System!\n";
                return;
            default:
                cout << "Invalid option!\n";
            }
        }
        else
        {
            if (isAdmin())
            {
                displayAdminMenu();
            }
            else
            {
                displayUserMenu();
            }

            cin >> choice;

            switch (choice)
            {
            case 1:
                searchResources();
                break;
            case 2:
                if (isAdmin())
                {
                    addResource();
                }
                else
                {
                    borrowResource();
                }
                break;
            case 3:
                if (isAdmin())
                {
                    removeResource();
                }
                else
                {
                    returnResource();
                }
                break;
            case 4:
                if (isAdmin())
                {
                    displayAllResources();
                }
                else
                {
                    renewLoan();
                }
                break;
            case 5:
                if (isAdmin())
                {
                    viewAllLoans();
                }
                else
                {
                    makeReservation();
                }
                break;
            case 7:
                if (!isAdmin())
                {
                    viewMyLoans();
                }
                break;
            case 8:
                if (!isAdmin())
                {
                    viewMyReservations();
                }
                break;
            case 9:
                if (!isAdmin())
                {
                    viewMyNotifications();
                }
                else
                {
                    viewEvents();
                }
                break;
            case 10:
                if (!isAdmin())
                {
                    displayAllResources();
                }
                break;
            case 0:
                logout();
                break;
            default:
                cout << "Invalid option!\n";
            }
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

#endif

// Main function
int main()
{
    try
    {
        LibrarySystem library;
        library.run();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}