#include "reservation.h"
#include <iostream>

Reservation::Reservation(const string &reservationId, const string &userId, const string &resourceId, time_t reservationDate)
    : reservationId(reservationId), userId(userId), resourceId(resourceId), reservationDate(reservationDate), fulfillmentDate(0), status(ReservationStatus::Pending) 
{
    if (!reservationId.empty() && !isValidReservationId(reservationId)) {
        cerr << "Warning: Invalid reservation ID provided. Using empty string." << endl;
        this->reservationId = "";
    }
    if (!userId.empty() && !isValidId(userId)) {
        cerr << "Warning: Invalid user ID provided. Using empty string." << endl;
        this->userId = "";
    }
    if (!resourceId.empty() && !isValidId(resourceId)) {
        cerr << "Warning: Invalid resource ID provided. Using empty string." << endl;
        this->resourceId = "";
    }
    if (reservationDate != 0 && !isValidDate(reservationDate)) {
        cerr << "Warning: Invalid reservation date provided. Using current time." << endl;
        this->reservationDate = time(nullptr);
    }
    if (reservationDate == 0) {
        this->reservationDate = time(nullptr);
    }
}

const string &Reservation::getReservationId() const
{
    return reservationId;
}

const string &Reservation::getUserId() const
{
    return userId;
}

const string &Reservation::getResourceId() const
{
    return resourceId;
}

time_t Reservation::getReservationDate() const
{
    return reservationDate;
}

time_t Reservation::getFulfillmentDate() const
{
    return fulfillmentDate;
}

ReservationStatus Reservation::getReservationStatus() const
{
    return status;
}

void Reservation::cancel()
{
    if (reservationId.empty() || userId.empty() || resourceId.empty()) {
        cerr << "Error: Cannot cancel reservation with missing information." << endl;
        return;
    }
    if (isPending())
    {
        status = ReservationStatus::Canceled;
    }
    else
    {
        cerr << "Error: Can only cancel pending reservations." << endl;
    }
}

void Reservation::fulfill()
{
    if (reservationId.empty() || userId.empty() || resourceId.empty()) {
        cerr << "Error: Cannot fulfill reservation with missing information." << endl;
        return;
    }
    if (isPending())
    {
        status = ReservationStatus::Fulfilled;
        fulfillmentDate = time(nullptr);
    }
    else
    {
        cerr << "Error: Can only fulfill pending reservations." << endl;
    }
}

bool Reservation::isPending() const
{
    return status == ReservationStatus::Pending;
}

bool Reservation::isCanceled() const
{
    return status == ReservationStatus::Canceled;
}

bool Reservation::isFulfilled() const
{
    return status == ReservationStatus::Fulfilled;
}

bool Reservation::isValidReservationId(const string &reservationId) const
{
    if (reservationId.empty()) return false;
    if (reservationId.length() < 3 || reservationId.length() > 30) return false;
    
    for (char c : reservationId) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool Reservation::isValidId(const string &id) const
{
    if (id.empty()) return false;
    if (id.length() < 3 || id.length() > 20) return false;
    
    for (char c : id) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool Reservation::isValidDate(time_t date) const
{
    if (date < 0) return false;
    time_t now = time(nullptr);
    time_t pastLimit = now - (365 * 24 * 60 * 60); // 1 year ago
    time_t futureLimit = now + (365 * 24 * 60 * 60); // 1 year from now
    return date >= pastLimit && date <= futureLimit;
}

// Json
json Reservation::toJson() const
{
    string statusStr;
    switch (status)
    {
    case ReservationStatus::Pending:
        statusStr = "Pending";
        break;
    case ReservationStatus::Fulfilled:
        statusStr = "Fulfilled";
        break;
    case ReservationStatus::Canceled:
        statusStr = "Canceled";
        break;
    }
    return json{
        {"reservationId", reservationId},
        {"userId", userId},
        {"resourceId", resourceId},
        {"reservationDate", reservationDate},
        {"fulfillmentDate", fulfillmentDate},
        {"status", statusStr}};
}

Reservation Reservation::fromJson(const json &j)
{
    try {
        Reservation reservation(
            j.at("reservationId").get<string>(),
            j.at("userId").get<string>(),
            j.at("resourceId").get<string>(),
            j.at("reservationDate").get<time_t>());
        reservation.fulfillmentDate = j.at("fulfillmentDate").get<time_t>();
        
        string statusStr = j.at("status").get<string>();
        if (statusStr == "Pending") {
            reservation.status = ReservationStatus::Pending;
        } else if (statusStr == "Fulfilled") {
            reservation.status = ReservationStatus::Fulfilled;
        } else if (statusStr == "Canceled") {
            reservation.status = ReservationStatus::Canceled;
        } else {
            cerr << "Warning: Invalid status in JSON. Setting to Pending." << endl;
            reservation.status = ReservationStatus::Pending;
        }

        if (reservation.fulfillmentDate < 0) {
            cerr << "Warning: Invalid fulfillment date in JSON. Setting to 0." << endl;
            reservation.fulfillmentDate = 0;
        }

        return reservation;
    } catch (const exception &e) {
        cerr << "Error parsing Reservation from JSON: " << e.what() << endl;
        return Reservation();
    }
}