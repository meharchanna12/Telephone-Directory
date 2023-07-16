#include <bits/stdc++.h>
using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;
    Contact* prev;
    Contact* next;

public:
    Contact(const string& name, const string& phoneNumber) {
        this->name = name;
        this->phoneNumber = phoneNumber;
        prev = nullptr;
        next = nullptr;
    }

    string getName() const {
        return name;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    Contact* getPrev() const {
        return prev;
    }

    void setPrev(Contact* prev) {
        this->prev = prev;
    }

    Contact* getNext() const {
        return next;
    }

    void setNext(Contact* next) {
        this->next = next;
    }
};

class TelephoneDirectory {
private:
    Contact* head;
    Contact* tail;

public:
    TelephoneDirectory() {
        head = nullptr;
        tail = nullptr;
    }

    void addContact(const string& name, const string& phoneNumber) {
        Contact* newContact = new Contact(name, phoneNumber);

        if (head == nullptr) {
            head = newContact;
            tail = newContact;
        } else {
            tail->setNext(newContact);
            newContact->setPrev(tail);
            tail = newContact;
        }
    }

    void deleteContact(const string& name) {
        Contact* current = head;

        while (current != nullptr) {
            if (current->getName() == name) {
                if (current == head && current == tail) {
                    // Only one contact in the directory
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    // Deleting the first contact
                    head = head->getNext();
                    head->setPrev(nullptr);
                } else if (current == tail) {
                    // Deleting the last contact
                    tail = tail->getPrev();
                    tail->setNext(nullptr);
                } else {
                    // Deleting a contact in the middle
                    current->getPrev()->setNext(current->getNext());
                    current->getNext()->setPrev(current->getPrev());
                }

                delete current;
                cout << "Contact deleted: " << name << endl;
                return;
            }

            current = current->getNext();
        }

        cout << "Contact not found: " << name << endl;
    }

    void displayContacts() {
        if (head == nullptr) {
            cout << "Telephone directory is empty." << endl;
            return;
        }

        cout << "Telephone directory:" << endl;
        Contact* current = head;

        while (current != nullptr) {
            cout << "Name: " << current->getName() << ", Phone: " << current->getPhoneNumber() << endl;
            current = current->getNext();
        }
    }
};

int main() {
    TelephoneDirectory directory;

    while (true) {
        cout << "----------------------------------------" << endl;
        cout << "Telephone Directory Menu:" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Display Contacts" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phoneNumber;
                cout << "Enter the name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter the phone number: ";
                getline(cin, phoneNumber);
                directory.addContact(name, phoneNumber);
                cout << "Contact added successfully." << endl;
                break;
            }
            case 2: {
                string name;
                cout << "Enter the name of the contact to delete: ";
                cin.ignore();
                getline(cin, name);
                directory.deleteContact(name);
                break;
            }
            case 3:
                directory.displayContacts();
                break;
            case 4:
                cout << "Exiting.." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
