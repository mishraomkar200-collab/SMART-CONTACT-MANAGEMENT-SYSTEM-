Smart Contact Management System
Minor Project | C++17 + Data Structures and Algorithms
1. Overview
A menu-driven console application for maintaining contact records. The system supports contact creation, listing, searching, updating, deleting, sorting, and persistence using a local text file.
2. Features
Contact fields: unique auto-generated ID, full name, phone, email, city, optional notes.
Singly linked list with dynamic node allocation and safe cleanup.
Search by ID, exact normalized phone number, and partial name.
Duplicate ID prevention through generated IDs; duplicate phone numbers are rejected (phone digits are normalized).
Update fields by ID and delete after confirmation.
Insertion sort by name or ID (node links remain intact).
File persistence in data/contacts.txt; escaped pipe delimiter supports pipes and newlines in text fields.
Basic validation for name, phone length, email format, and numeric menu choices.
Sample data included.
3. Project structure
Smart_Contact_Management_System/
├── src/
│   ├── main.cpp
│   ├── Contact.cpp
│   └── ContactList.cpp
├── include/
│   ├── Contact.h
│   └── ContactList.h
├── data/
│   └── contacts.txt
├── test_cases/
│   └── Test_Cases.md
├── docs/
│   └── Project_Report.pdf
├── screenshots/
├── README.md
└── .gitignore
4. Prerequisites
C++17 compatible compiler (GCC 9+, Clang 10+, or a recent MSVC).
Terminal / command prompt.
5. Compile
Run from the project root:
GCC / MinGW
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/Contact.cpp src/ContactList.cpp -o smart_contacts
Run
./smart_contacts
On Windows:
smart_contacts.exe
Important: Run from the project root so the relative path data/contacts.txt resolves correctly.
6. Data rules
Contact IDs are assigned sequentially from the highest ID loaded + 1.
Phone numbers must contain 7–15 digits. Formatting symbols are permitted; duplicate checking compares digits only.
Duplicate phone numbers are rejected.
Email is optional; if supplied, a basic format check is applied.
Text persistence uses | separators and backslash escapes (\\|, \\\\, \\n, \\r).
Malformed records are skipped during load rather than terminating the application.
7. DSA and complexity
Let n be the number of contacts.
Operation
Algorithm / Structure
Time
Extra space
Add (duplicate check + append)
Linked-list traversal
O(n)
O(1)
Display all
Traversal
O(n)
O(1)
Search ID / phone
Linear search
O(n)
O(1)
Search name
Linear substring search
O(n·m) approximate, m=name length
O(1)
Update / delete
Linear search
O(n)
O(1)
Sort by name / ID
Insertion sort over node-pointer vector
O(n²) worst case
O(n)
Save / load
Sequential file traversal
O(n)
O(n) during load
The singly linked list is suitable for dynamic records and demonstrates pointer operations. A pointer vector is temporarily used by insertion sort to make the sorted-prefix comparisons straightforward; the nodes themselves are not relinked. Contact values are moved among node positions, so node ownership and next pointers remain unchanged.
8. Testing
See test_cases/Test_Cases.md for test coverage and expected results. Run the application and verify the expected behavior manually. Actual execution status should be recorded after testing in the student's environment.
9. GitHub submission
Create a public repository, add the project files, and use meaningful commits (for example: Add Contact model, Implement linked list operations, Add persistence and validation, Add tests and report). Do not upload confidential data.
10. Limitations and future work
Console interface only.
Email validation is intentionally basic.
The app uses a single local text file and does not provide multi-user locking.
Potential extensions: categories, favorites, case-insensitive search, unordered_map index, and recent-contact stack.
11. Academic note
This project package is a working draft for learning and demonstration. Compile, test, personalize the sample data, capture your own terminal screenshots, and be prepared to explain each class and algorithm during evaluation.# SMART-CONTACT-MANAGEMENT-SYSTEM-