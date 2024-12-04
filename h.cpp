#include<iostream>
#include<string>
using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
    string email;
    Contact *prev, *next;
    
    // Constructor to initialize the contact
    Contact(string n, string p, string e) {
        name = n;
        phoneNumber = p;
        email = e;
        next = nullptr;
        prev = nullptr;
    }

    friend class ContactList;
};

class ContactList {
    Contact *head, *temp, *current;
    
public:
    ContactList() {
        head = nullptr;
    }

    // Function to add a new contact
    void addContact();

    // Function to display the contact list
    void displayContacts();

    // Function to search a contact by name
    void searchByName(const string& name);

    // Function to search a contact by phone number
    void searchByPhoneNumber(const string& number);

    // Function to search a contact by email
    void searchByEmail(const string& email);

    // Function to delete a contact by name
    void deleteContactByName(const string& name);

    // Function to delete contacts with the same name
    void deleteContactsByName();

    // Function to delete contacts with the same phone number
    void deleteContactsByPhoneNumber();

    // Function to update contact details
    void updateContactDetails(const string& name);

    // Function to handle user input and add contacts
    void inputContacts();

    // Function to sort contacts by name
    void sortContacts();
};

// Function to add a new contact to the list
void ContactList::addContact() {
    string name, phoneNumber, email;
    char continueInput;
    
    do {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        while (phoneNumber.length() != 10) {
            cout << "Enter a valid 10-digit phone number: ";
            cin >> phoneNumber;
        }
        cout << "Enter Email: ";
        cin >> email;
        
        temp = new Contact(name, phoneNumber, email);
        
        if (head == nullptr) {
            head = temp;
        } else {
            current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = temp;
            temp->prev = current;
        }

        cout << "Do you want to continue adding contacts? (y/n): ";
        cin >> continueInput;
    } while (continueInput == 'y');
}

// Function to display all contacts
void ContactList::displayContacts() {
    current = head;
    while (current != nullptr) {
        cout << "\nName: " << current->name;
        cout << "\nPhone Number: " << current->phoneNumber;
        cout << "\nEmail: " << current->email << endl;
        current = current->next;
    }
}

// Function to search a contact by name
void ContactList::searchByName(const string& name) {
    current = head;
    while (current != nullptr) {
        if (current->name == name) {
            cout << "\nContact found: ";
            cout << "\nName: " << current->name;
            cout << "\nPhone Number: " << current->phoneNumber;
            cout << "\nEmail: " << current->email << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found by name: " << name << endl;
}

// Function to search a contact by phone number
void ContactList::searchByPhoneNumber(const string& number) {
    current = head;
    while (current != nullptr) {
        if (current->phoneNumber == number) {
            cout << "\nContact found: ";
            cout << "\nName: " << current->name;
            cout << "\nPhone Number: " << current->phoneNumber;
            cout << "\nEmail: " << current->email << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found by phone number: " << number << endl;
}

// Function to search a contact by email
void ContactList::searchByEmail(const string& email) {
    current = head;
    while (current != nullptr) {
        if (current->email == email) {
            cout << "\nContact found: ";
            cout << "\nName: " << current->name;
            cout << "\nPhone Number: " << current->phoneNumber;
            cout << "\nEmail: " << current->email << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found by email: " << email << endl;
}

// Function to delete a contact by name
void ContactList::deleteContactByName(const string& name) {
    current = head;
    while (current != nullptr) {
        if (current->name == name) {
            if (current == head) {
                head = head->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (current->next == nullptr) {
                current->prev->next = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            cout << "Contact deleted successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Contact with name " << name << " not found.\n";
}

// Function to delete contacts with the same name
void ContactList::deleteContactsByName() {
    current = head;
    while (current != nullptr && current->next != nullptr) {
        Contact* tempPtr = current;
        while (tempPtr->next != nullptr) {
            if (current->name == tempPtr->next->name) {
                Contact* duplicate = tempPtr->next;
                tempPtr->next = tempPtr->next->next;
                if (tempPtr->next != nullptr) {
                    tempPtr->next->prev = tempPtr;
                }
                delete duplicate;
            } else {
                tempPtr = tempPtr->next;
            }
        }
        current = current->next;
    }
    cout << "Duplicate contacts with the same name deleted successfully.\n";
}

// Function to delete contacts with the same phone number
void ContactList::deleteContactsByPhoneNumber() {
    current = head;
    while (current != nullptr && current->next != nullptr) {
        Contact* tempPtr = current;
        while (tempPtr->next != nullptr) {
            if (current->phoneNumber == tempPtr->next->phoneNumber) {
                Contact* duplicate = tempPtr->next;
                tempPtr->next = tempPtr->next->next;
                if (tempPtr->next != nullptr) {
                    tempPtr->next->prev = tempPtr;
                }
                delete duplicate;
            } else {
                tempPtr = tempPtr->next;
            }
        }
        current = current->next;
    }
    cout << "Duplicate contacts with the same phone number deleted successfully.\n";
}

// Function to update contact details
void ContactList::updateContactDetails(const string& name) {
    current = head;
    while (current != nullptr) {
        if (current->name == name) {
            int choice;
            cout << "\nWhat do you want to update?\n1) Name\n2) Phone Number\n3) Email\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    cin >> current->name;
                    break;
                case 2:
                    cout << "Enter new phone number: ";
                    cin >> current->phoneNumber;
                    break;
                case 3:
                    cout << "Enter new email: ";
                    cin >> current->email;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
            }
            cout << "Contact details updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Contact with name " << name << " not found.\n";
}

// Function to handle input and add contacts
void ContactList::inputContacts() {
    addContact();
}

// Function to sort contacts by name
void ContactList::sortContacts() {
    Contact* i;
    Contact* j;
    string tempName;
    string tempPhoneNumber;
    string tempEmail;

    for (i = head; i != nullptr; i = i->next) {
        for (j = i->next; j != nullptr; j = j->next) {
            if (i->name > j->name) {
                // Swap contact details
                tempName = i->name;
                tempPhoneNumber = i->phoneNumber;
                tempEmail = i->email;
                i->name = j->name;
                i->phoneNumber = j->phoneNumber;
                i->email = j->email;
                j->name = tempName;
                j->phoneNumber = tempPhoneNumber;
                j->email = tempEmail;
            }
        }
    }
}

// Main function
int main() {
    ContactList contactList;
    int choice;
    string name, number, email;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Contacts\n";
        cout << "2. Add Contact\n";
        cout << "3. Update Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Delete Contacts with Same Name\n";
        cout << "6. Delete Contacts with Same Phone Number\n";
        cout << "7. Search Contacts\n";
        cout << "8. Sort Contacts\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                contactList.displayContacts();
                break;
            case 2:
                contactList.inputContacts();
                break;
            case 3:
                cout << "Enter Name to Update: ";
                cin >> name;
                contactList.updateContactDetails(name);
                break;
            case 4:
                cout << "Enter Name to Delete: ";
                cin >> name;
                contactList.deleteContactByName(name);
                break;
            case 5:
                contactList.deleteContactsByName();
                break;
            case 6:
                contactList.deleteContactsByPhoneNumber();
                break;
            case 7:
                cout << "Search By: \n1) Name\n2) Phone Number\n3) Email\n";
                int searchChoice;
                cin >> searchChoice;
                switch (searchChoice) {
                    case 1:
                        cout << "Enter Name to search: ";
                        cin >> name;
                        contactList.searchByName(name);
                        break;
                    case 2:
                        cout << "Enter Phone Number to search: ";
                        cin >> number;
                        contactList.searchByPhoneNumber(number);
                        break;
                    case 3:
                        cout << "Enter Email to search: ";
                        cin >> email;
                        contactList.searchByEmail(email);
                        break;
                }
                break;
            case 8:
                contactList.sortContacts();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nDo you want to continue? (y/n): ";
        char ans;
        cin >> ans;
        if (ans == 'n') break;
    } while (true);

    return 0;
}
