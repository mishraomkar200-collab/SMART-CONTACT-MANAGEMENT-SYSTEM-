#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include "Contact.h"
#include <string>

class ContactList {
private:
    struct Node {
        Contact contact;
        Node* next;
        explicit Node(const Contact& value) : contact(value), next(nullptr) {}
    };

    Node* head_;
    int nextId_;
    int size_;

    static std::string normalizePhone(const std::string& phone);
    static std::string escapeField(const std::string& value);
    static bool unescapeField(const std::string& value, std::string& output);
    static bool parseRecord(const std::string& line, Contact& contact);

public:
    ContactList();
    ~ContactList();

    ContactList(const ContactList&) = delete;
    ContactList& operator=(const ContactList&) = delete;

    int count() const;
    bool isEmpty() const;
    int addContact(const std::string& name, const std::string& phone,
                   const std::string& email, const std::string& city,
                   const std::string& notes, std::string& message);
    bool displayAll() const;
    const Contact* searchById(int id) const;
    bool searchByName(const std::string& name) const;
    const Contact* searchByPhone(const std::string& phone) const;
    bool updateContact(int id, const std::string& name, const std::string& phone,
                       const std::string& email, const std::string& city,
                       const std::string& notes, std::string& message);
    bool deleteContact(int id);
    void sortByName();
    void sortById();
    bool saveToFile(const std::string& path, std::string& message) const;
    bool loadFromFile(const std::string& path, std::string& message);
};

#endif
