Test Plan — Smart Contact Management System
Record the actual result and Pass/Fail status after running each test locally.
TC ID
Scenario
Input / Steps
Expected result
Actual result
Status
TC-01
Add valid contact
Add name, valid phone, email, city, notes
Contact created; generated ID shown
To be recorded
Pending
TC-02
Empty name
Submit blank name
Prompt repeats; no record created
To be recorded
Pending
TC-03
Invalid phone length
Phone has fewer than 7 digits
Validation message; contact rejected
To be recorded
Pending
TC-04
Duplicate phone
Add phone already in records, even with separators changed
Duplicate rejected
To be recorded
Pending
TC-05
View list
Select View with contacts present
All contacts and total shown
To be recorded
Pending
TC-06
Empty list view
Start with empty data file and view
Graceful “No contacts” message
To be recorded
Pending
TC-07
Search by ID
Search existing ID
Contact details shown
To be recorded
Pending
TC-08
Search missing ID
Search unknown ID
Contact not found message
To be recorded
Pending
TC-09
Search partial name
Search substring of a name
All matching records shown
To be recorded
Pending
TC-10
Search by phone
Search existing phone
Matching contact shown
To be recorded
Pending
TC-11
Update contact
Change selected fields by ID
Updated values displayed/saved
To be recorded
Pending
TC-12
Update duplicate phone
Change phone to another contact's number
Update rejected; original remains
To be recorded
Pending
TC-13
Delete first node
Delete ID of first record
Record removed; list remains valid
To be recorded
Pending
TC-14
Delete last node
Delete tail record
Record removed; list remains valid
To be recorded
Pending
TC-15
Delete sole node
Delete only contact
List becomes empty safely
To be recorded
Pending
TC-16
Cancel delete
Enter N at confirmation
Record remains
To be recorded
Pending
TC-17
Sort by name
Select name sort then view
Alphabetical order
To be recorded
Pending
TC-18
Sort by ID
Select ID sort then view
Ascending IDs
To be recorded
Pending
TC-19
Persistence
Save, exit, relaunch, view
Saved records reload
To be recorded
Pending
TC-20
Malformed file row
Add malformed row to data file then launch
Row skipped; app continues
To be recorded
Pending
TC-21
File write failure
Temporarily make data path unwritable
Clear save error
To be recorded
Pending
TC-22
Invalid menu choice
Enter text or out-of-range number
Input rejected/re-prompt or invalid choice message
To be recorded
Pending
TC-23
One-node list operations
Add one, search, update, sort, delete
All operations safe
To be recorded
Pending
Demonstration sequence
Launch and show initial data loading.
Add a contact; show generated unique ID.
Search by ID, name fragment, and phone.
Update a contact; show duplicate-phone rejection if applicable.
Sort by name and ID.
Delete one record after confirmation.
Save and exit; launch again to show persistence.
Explain linked-list node, linear search O(n), insertion sort O(n²), and file escape format.