#pragma once

#include "data.h"

#include <string>
#include <vector>

enum class SortCriterion {
    ByName,
    ByPhoneNumber
};

bool loadAllContacts(const std::string& filePath,
                     std::vector<Contact>& targetContactList);

bool persistAllContacts(const std::string& filePath,
                        const std::vector<Contact>& contactList);

bool addNewContact(std::vector<Contact>& contactList,
                   const Contact& newContact,
                   std::string& errorMessage);

bool updateExistingContact(std::vector<Contact>& contactList,
                           const Contact& updatedContact,
                           std::string& errorMessage);