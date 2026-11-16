#include "Contact.h"

Contact::Contact() : id_(0) {}

Contact::Contact(int id, const std::string& name, const std::string& phone,
                 const std::string& email, const std::string& city,
                 const std::string& notes)
    : id_(id), name_(name), phone_(phone), email_(email), city_(city), notes_(notes) {}

int Contact::getId() const { return id_; }
const std::string& Contact::getName() const { return name_; }
const std::string& Contact::getPhone() const { return phone_; }
const std::string& Contact::getEmail() const { return email_; }
const std::string& Contact::getCity() const { return city_; }
const std::string& Contact::getNotes() const { return notes_; }

void Contact::setName(const std::string& value) { name_ = value; }
void Contact::setPhone(const std::string& value) { phone_ = value; }
void Contact::setEmail(const std::string& value) { email_ = value; }
void Contact::setCity(const std::string& value) { city_ = value; }
void Contact::setNotes(const std::string& value) { notes_ = value; }
