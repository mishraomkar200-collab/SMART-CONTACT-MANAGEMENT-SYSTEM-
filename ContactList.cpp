#include "ContactList.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

ContactList::ContactList() : head_(nullptr), nextId_(1), size_(0) {}

ContactList::~ContactList() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int ContactList::count() const { return size_; }
bool ContactList::isEmpty() const { return head_ == nullptr; }

std::string ContactList::normalizePhone(const std::string& phone) {
    std::string result;
    for (unsigned char ch : phone) {
        if (std::isdigit(ch)) result.push_back(static_cast<char>(ch));
    }
    return result;
}

std::string ContactList::escapeField(const std::string& value) {
    std::string result;
    for (char ch : value) {
        if (ch == '\\' || ch == '|') result.push_back('\\');
        if (ch == '\n') { result += "\\n"; continue; }
        if (ch == '\r') { result += "\\r"; continue; }
        result.push_back(ch);
    }
    return result;
}

bool ContactList::unescapeField(const std::string& value, std::string& output) {
    output.clear();
    for (std::size_t i = 0; i < value.size(); ++i) {
        if (value[i] != '\\') {
            output.push_back(value[i]);
            continue;
        }
        if (i + 1 >= value.size()) return false;
        char next = value[++i];
        if (next == 'n') output.push_back('\n');
        else if (next == 'r') output.push_back('\r');
        else if (next == '|' || next == '\\') output.push_back(next);
        else return false;
    }
    return true;
}

bool ContactList::parseRecord(const std::string& line, Contact& contact) {
    std::vector<std::string> fields;
    std::string field;
    bool escaped = false;
    for (char ch : line) {
        if (escaped) {
            field.push_back('\\');
            field.push_back(ch);
            escaped = false;
        } else if (ch == '\\') {
            escaped = true;
        } else if (ch == '|') {
            fields.push_back(field);
            field.clear();
        } else {
            field.push_back(ch);
        }
    }
    if (escaped) return false;
    fields.push_back(field);
    if (fields.size() != 6) return false;

    std::string decoded[5];
    for (int i = 1; i < 6; ++i) {
        if (!unescapeField(fields[i], decoded[i - 1])) return false;
    }
    try {
        std::size_t used = 0;
        int id = std::stoi(fields[0], &used);
        if (used != fields[0].size() || id <= 0 || decoded[0].empty()) return false;
        contact = Contact(id, decoded[0], decoded[1], decoded[2], decoded[3], decoded[4]);
        return true;
    } catch (...) {
        return false;
    }
}

int ContactList::addContact(const std::string& name, const std::string& phone,
                            const std::string& email, const std::string& city,
                            const std::string& notes, std::string& message) {
    if (name.empty()) { message = "Name cannot be empty."; return -1; }
    const std::string normalized = normalizePhone(phone);
    if (normalized.size() < 7 || normalized.size() > 15) {
        message = "Phone number must contain 7 to 15 digits."; return -1;
    }
    for (Node* current = head_; current != nullptr; current = current->next) {
        if (normalizePhone(current->contact.getPhone()) == normalized) {
            message = "A contact with this phone number already exists."; return -1;
        }
    }

    Contact value(nextId_, name, phone, email, city, notes);
    Node* node = new Node(value);
    if (head_ == nullptr) head_ = node;
    else {
        Node* tail = head_;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = node;
    }
    ++size_;
    message = "Contact created successfully with ID " + std::to_string(nextId_) + ".";
    return nextId_++;
}

bool ContactList::displayAll() const {
    if (isEmpty()) {
        std::cout << "No contacts are currently saved.\n";
        return false;
    }
    std::cout << "\n";
    std::cout << "ID | Name | Phone | Email | City | Notes\n";
    std::cout << "--------------------------------------------------------------------------\n";
    for (Node* current = head_; current != nullptr; current = current->next) {
        const Contact& c = current->contact;
        std::cout << c.getId() << " | " << c.getName() << " | " << c.getPhone()
                  << " | " << c.getEmail() << " | " << c.getCity()
                  << " | " << c.getNotes() << "\n";
    }
    std::cout << "Total contacts: " << size_ << "\n";
    return true;
}

const Contact* ContactList::searchById(int id) const {
    for (Node* current = head_; current != nullptr; current = current->next)
        if (current->contact.getId() == id) return &current->contact;
    return nullptr;
}

bool ContactList::searchByName(const std::string& name) const {
    bool found = false;
    for (Node* current = head_; current != nullptr; current = current->next) {
        if (current->contact.getName().find(name) != std::string::npos) {
            const Contact& c = current->contact;
            std::cout << c.getId() << " | " << c.getName() << " | " << c.getPhone()
                      << " | " << c.getEmail() << " | " << c.getCity() << "\n";
            found = true;
        }
    }
    return found;
}

const Contact* ContactList::searchByPhone(const std::string& phone) const {
    const std::string normalized = normalizePhone(phone);
    for (Node* current = head_; current != nullptr; current = current->next)
        if (normalizePhone(current->contact.getPhone()) == normalized) return &current->contact;
    return nullptr;
}

bool ContactList::updateContact(int id, const std::string& name, const std::string& phone,
                                const std::string& email, const std::string& city,
                                const std::string& notes, std::string& message) {
    Node* target = head_;
    while (target != nullptr && target->contact.getId() != id) target = target->next;
    if (target == nullptr) { message = "Contact ID not found."; return false; }
    if (name.empty()) { message = "Name cannot be empty."; return false; }

    const std::string normalized = normalizePhone(phone);
    if (normalized.size() < 7 || normalized.size() > 15) {
        message = "Phone number must contain 7 to 15 digits."; return false;
    }
    for (Node* current = head_; current != nullptr; current = current->next) {
        if (current != target && normalizePhone(current->contact.getPhone()) == normalized) {
            message = "Another contact already uses this phone number."; return false;
        }
    }
    target->contact.setName(name);
    target->contact.setPhone(phone);
    target->contact.setEmail(email);
    target->contact.setCity(city);
    target->contact.setNotes(notes);
    message = "Contact updated successfully.";
    return true;
}

bool ContactList::deleteContact(int id) {
    Node* current = head_;
    Node* previous = nullptr;
    while (current != nullptr && current->contact.getId() != id) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) return false;
    if (previous == nullptr) head_ = current->next;
    else previous->next = current->next;
    delete current;
    --size_;
    return true;
}

void ContactList::sortByName() {
    // Insertion sort over node pointers; node links and ownership remain unchanged.
    std::vector<Node*> nodes;
    for (Node* current = head_; current != nullptr; current = current->next) nodes.push_back(current);
    for (std::size_t i = 1; i < nodes.size(); ++i) {
        Contact key = nodes[i]->contact;
        std::size_t j = i;
        while (j > 0 && key.getName() < nodes[j - 1]->contact.getName()) {
            nodes[j]->contact = nodes[j - 1]->contact;
            --j;
        }
        nodes[j]->contact = key;
    }
}

void ContactList::sortById() {
    std::vector<Node*> nodes;
    for (Node* current = head_; current != nullptr; current = current->next) nodes.push_back(current);
    for (std::size_t i = 1; i < nodes.size(); ++i) {
        Contact key = nodes[i]->contact;
        std::size_t j = i;
        while (j > 0 && key.getId() < nodes[j - 1]->contact.getId()) {
            nodes[j]->contact = nodes[j - 1]->contact;
            --j;
        }
        nodes[j]->contact = key;
    }
}

bool ContactList::saveToFile(const std::string& path, std::string& message) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out) { message = "Could not open data file for writing."; return false; }
    for (Node* current = head_; current != nullptr; current = current->next) {
        const Contact& c = current->contact;
        out << c.getId() << "|" << escapeField(c.getName()) << "|"
            << escapeField(c.getPhone()) << "|" << escapeField(c.getEmail()) << "|"
            << escapeField(c.getCity()) << "|" << escapeField(c.getNotes()) << "\n";
    }
    if (!out.good()) { message = "An error occurred while writing the data file."; return false; }
    message = "All contacts saved to " + path + ".";
    return true;
}

bool ContactList::loadFromFile(const std::string& path, std::string& message) {
    std::ifstream in(path);
    if (!in) {
        // A missing file is normal on the first run.
        message = "Data file not found. Starting with an empty contact list.";
        return true;
    }

    Node* newHead = nullptr;
    Node* tail = nullptr;
    int loadedCount = 0;
    int maxId = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Contact c;
        if (!parseRecord(line, c)) continue; // Skip malformed rows safely.
        bool duplicate = false;
        for (Node* scan = newHead; scan != nullptr; scan = scan->next) {
            if (scan->contact.getId() == c.getId() ||
                normalizePhone(scan->contact.getPhone()) == normalizePhone(c.getPhone())) {
                duplicate = true; break;
            }
        }
        if (duplicate) continue;
        Node* node = new Node(c);
        if (newHead == nullptr) newHead = node;
        else tail->next = node;
        tail = node;
        ++loadedCount;
        if (c.getId() > maxId) maxId = c.getId();
    }
    // Replace existing list only after the new data has been parsed.
    Node* old = head_;
    while (old != nullptr) {
        Node* next = old->next;
        delete old;
        old = next;
    }
    head_ = newHead;
    size_ = loadedCount;
    nextId_ = maxId + 1;
    message = "Loaded " + std::to_string(size_) + " contact(s) from " + path + ".";
    return true;
}
