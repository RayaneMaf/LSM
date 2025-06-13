#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
#include <ctime>
#include "Json/json.hpp"
using json = nlohmann::json;
using namespace std;

enum class ReservationStatus
{
    Pending,
    Fulfilled,
    Canceled,
};

class Reservation
{
private:
    string reservationId;
    string userId;
    string resourceId;
    time_t reservationDate;
    time_t fulfillmentDate; // 0 means no fulfillment yet
    ReservationStatus status;

    // Helper validation methods
    bool isValidReservationId(const string &reservationId) const;
    bool isValidId(const string &id) const;
    bool isValidDate(time_t date) const;

public:
    Reservation(const string & = "", const string & = "", const string & = "", time_t = 0);
    ~Reservation() = default;

    const string &getReservationId() const;
    const string &getUserId() const;
    const string &getResourceId() const;
    time_t getReservationDate() const;
    time_t getFulfillmentDate() const;
    ReservationStatus getReservationStatus() const;

    void cancel();
    void fulfill();
    bool isPending() const;
    bool isCanceled() const;
    bool isFulfilled() const;

    // Json
    json toJson() const;
    static Reservation fromJson(const json &);
};

#endif