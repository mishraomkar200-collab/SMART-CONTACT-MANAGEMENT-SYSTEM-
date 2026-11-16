#include "ContactList.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

namespace {
const std::string DATA_FILE = "data/contacts.txt";

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int readInt(const std::string& prompt) {
    while (true) {
        std::string input = readLine(prompt);
        try {
            std::size_t used = 0;
            int value = std::stoi(input, &used);
            if (used == input.size()) return value;
        } catch (...) {}
        std::cout << "Please enter a valid whole number.\n";
    }
}

bool validEmail(const std::string& email) {
    if (email.empty()) return true; // Email is optional.
    std::size_t at = email.find('@');
    std::size_t dot = email.find('.', at == std::string::npos ? 0 : at);
    return at != std::string::npos && at > 0 && dot != std::string::npos &&
           dot > at + 1 && dot + 1 < email.size();
}

void printContact(const Contact& c) {
    std::cout << "\nContact Details\n"
              << "ID    : " << c.getId() << "\n"
              << "Name  : " << c.getName() << "\n"
              << "Phone : " << c.getPhone() << "\n"
              << "Email : " << c.getEmail() << "\n"
              << "City  : " << c.getCity() << "\n"
              << "Notes : " << c.getNotes() << "\n";
}

void addContact(ContactList& contacts) {
    std::string name;
    do { name = readLine("Full name: "); if (name.empty()) std::cout << "Name is required.\n"; } while (name.empty());
    std::string phone = readLine("Phone number (7-15 digits; separators allowed): ");
    std::string email;
    do { email = readLine("Email (optional): "); if (!validEmail(email)) std::cout << "Please enter a valid email address.\n"; } while (!validEmail(email));
    std::string city = readLine("City: ");
    std::string notes = readLine("Optional notes: ");
    std::string message;
    contacts.addContact(name, phone, email, city, notes, message);
    std::cout << message << "\n";
}

void searchContact(const ContactList& contacts) {
    std::cout << "\nSearch by: 1. ID  2. Name  3. Phone\n";
    int choice = readInt("Choice: ");
    if (choice == 1) {
        int id = readInt("Contact ID: ");
        const Contact* c = contacts.searchById(id);
        if (c) printContact(*c); else std::cout << "Contact not found.\n";
    } else if (choice == 2) {
        std::string name = readLine("Name or part of name: ");
        if (!contacts.searchByName(name)) std::cout << "No matching contact found.\n";
    } else if (choice == 3) {
        std::string phone = readLine("Phone number: ");
        const Contact* c = contacts.searchByPhone(phone);
        if (c) printContact(*c); else std::cout << "Contact not found.\n";
    } else std::cout << "Invalid search option.\n";
}

void updateContact(ContactList& contacts) {
    int id = readInt("Contact ID to update: ");
    const Contact* existing = contacts.searchById(id);
    if (!existing) { std::cout << "Contact ID not found.\n"; return; }
    printContact(*existing);
    std::cout << "Enter new values. Press Enter to keep the current value.\n";
    std::string name = readLine("Full name [" + existing->getName() + "]: ");
    std::string phone = readLine("Phone [" + existing->getPhone() + "]: ");
    std::string email = readLine("Email [" + existing->getEmail() + "]: ");
    std::string city = readLine("City [" + existing->getCity() + "]: ");
    std::string notes = readLine("Notes [" + existing->getNotes() + "]: ");
    if (name.empty()) name = existing->getName();
    if (phone.empty()) phone = existing->getPhone();
    if (email.empty()) email = existing->getEmail();
    if (city.empty()) city = existing->getCity();
    if (notes.empty()) notes = existing->getNotes();
    if (!validEmail(email)) { std::cout << "Invalid email; update cancelled.\n"; return; }
    std::string message;
    std::cout << (contacts.updateContact(id, name, phone, email, city, notes, message) ? message : message) << "\n";
}

void deleteContact(ContactList& contacts) {
    int id = readInt("Contact ID to delete: ");
    if (!contacts.searchById(id)) { std::cout << "Contact ID not found.\n"; return; }
    std::string confirmation = readLine("Delete this contact? (Y/N): ");
    if (confirmation.size() == 1 && std::toupper(static_cast<unsigned char>(confirmation[0])) == 'Y') {
        if (contacts.deleteContact(id)) std::cout << "Contact deleted.\n";
    } else std::cout << "Deletion cancelled.\n";
}
}

int main() {
    ContactList contacts;
    std::string message;
    contacts.loadFromFile(DATA_FILE, message);
    std::cout << "========================================\n"
              << "   SMART CONTACT MANAGEMENT SYSTEM\n"
              << "========================================\n"
              << message << "\n";

    bool running = true;
    while (running) {
        std::cout << "\nMAIN MENU\n"
                  << "1. Add Contact\n"
                  << "2. View All Contacts\n"
                  << "3. Search Contact\n"
                  << "4. Update Contact\n"
                  << "5. Delete Contact\n"
                  << "6. Sort Contacts by Name\n"
                  << "7. Sort Contacts by ID\n"
                  << "8. Save Data\n"
                  << "9. Exit\n";
        int choice = readInt("Enter choice: ");
        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: contacts.displayAll(); break;
            case 3: searchContact(contacts); break;
            case 4: updateContact(contacts); break;
            case 5: deleteContact(contacts); break;
            case 6: contacts.sortByName(); std::cout << "Contacts sorted by name.\n"; break;
            case 7: contacts.sortById(); std::cout << "Contacts sorted by ID.\n"; break;
            case 8:
                if (contacts.saveToFile(DATA_FILE, message)) std::cout << message << "\n";
                else std::cout << "Save failed: " << message << "\n";
                break;
            case 9:
                if (contacts.saveToFile(DATA_FILE, message)) std::cout << message << "\n";
                else std::cout << "Warning: " << message << "\n";
                std::cout << "Thank you for using Smart Contact Management System.\n";
                running = false;
                break;
            default: std::cout << "Please select an option from 1 to 9.\n";
        }
    }
    return 0;
}
