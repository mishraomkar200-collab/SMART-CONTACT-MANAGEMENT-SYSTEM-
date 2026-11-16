#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
private:
    int id_;
    std::string name_;
    std::string phone_;
    std::string email_;
    std::string city_;
    std::string notes_;

public:
    Contact();
    Contact(int id, const std::string& name, const std::string& phone,
            const std::string& email, const std::string& city,
            const std::string& notes);

    int getId() const;
    const std::string& getName() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    const std::string& getCity() const;
    const std::string& getNotes() const;

    void setName(const std::string& value);
    void setPhone(const std::string& value);
    void setEmail(const std::string& value);
    void setCity(const std::string& value);
    void setNotes(const std::string& value);
};

#endif
