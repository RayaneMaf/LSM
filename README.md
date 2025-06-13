Library Management System (LMS)
Simple Library Management System for managing books, articles, theses, loans, reservations, and library events. Built with C++ and Qt.

Key Features :
 
📚 Resource management (Books, Articles, Theses)

👥 User management with different roles

🔁 Loan system with renewals

⏰ Reservation system with status tracking

🔔 Notification system

🗓️ Library event management

💾 JSON data persistence

Implementation Notes
Incomplete system.cpp - Due to time constraints, the main system integration file (system.cpp) wasn't fully completed. The AI assistant helped complete critical functionality to make the system operational.

QML-C++ Integration Challenges - I faced significant difficulties connecting the QML-based GUI with the C++ backend. The QML interface design is available in the qml/ folder but isn't fully integrated with the core system.

Key Implementation Details:

Polymorphic resource handling using base Resource class

JSON serialization for all entities

Validation methods in each class

Backup system for data persistence

Custom date/time handling using time_t

**Note: This project was developed under tight time constraints. Some features might be simplified compared to a production-ready system. The focus was on core OOP principles and data management rather than UI polish.
**
