#include <iostream>
#include <string>
using namespace std;

struct Expense {
    string name;
    double amount;
    Expense* next;

    Expense(string n, double a) : name(n), amount(a), next(NULL) {}
};

struct Month {
    string name;
    Expense* expenses;
    Month* next;

    Month(string n) : name(n), expenses(NULL), next(NULL) {}
};

class ExpenseTracker {
    Month* head;

    Month* findMonth(const string& monthName) {
        Month* current = head;
        while (current) {
            if (current->name == monthName) return current;
            current = current->next;
        }
        return NULL;
    }

public:
    ExpenseTracker() : head(NULL) {}

    ~ExpenseTracker() {
        while (head) {
            Expense* e = head->expenses;
            while (e) {
                Expense* temp = e;
                e = e->next;
                delete temp;
            }
            Month* m = head;
            head = head->next;
            delete m;
        }
    }

    void addMonth(const string& monthName) {
        if (findMonth(monthName)) {
            cout << "Month already exists.\n";
            return;
        }
        Month* newMonth = new Month(monthName);
        newMonth->next = head;
        head = newMonth;
        cout << "Month added: " << monthName << endl;
    }

    void addExpense(const string& monthName, const string& expName, double amt) {
        Month* month = findMonth(monthName);
        if (!month) {
            cout << "Month not found.\n";
            return;
        }
        Expense* newExp = new Expense(expName, amt);
        newExp->next = month->expenses;
        month->expenses = newExp;
        cout << "Added: " << expName << " ($" << amt << ") to " << monthName << endl;
    }

    void deleteExpense(const string& monthName, const string& expName) {
        Month* month = findMonth(monthName);
        if (!month) {
            cout << "Month not found.\n";
            return;
        }
        Expense* curr = month->expenses;
        Expense* prev = NULL;

        while (curr) {
            if (curr->name == expName) {
                if (prev) prev->next = curr->next;
                else month->expenses = curr->next;
                delete curr;
                cout << "Deleted: " << expName << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Expense not found.\n";
    }

    void showAll() {
        if (!head) {
            cout << "No months added yet.\n";
            return;
        }

        Month* m = head;
        while (m) {
            cout << "\nMonth: " << m->name << "\nExpenses:\n";
            Expense* e = m->expenses;
            if (!e) {
                cout << "  (No expenses)\n";
            } else {
                double maxAmt = 0;
                string maxName = "";
                while (e) {
                    cout << "- " << e->name << ": $" << e->amount << endl;
                    if (e->amount > maxAmt) {
                        maxAmt = e->amount;
                        maxName = e->name;
                    }
                    e = e->next;
                }
                cout << "Most expensive: " << maxName << " ($" << maxAmt << ")\n";
            }
            m = m->next;
        }
    }
};

// ========= Main =========
int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n--- Expense Tracker ---\n";
        cout << "1. Add Month\n";
        cout << "2. Add Expense\n";
        cout << "3. Delete Expense\n";
        cout << "4. View All\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        string month, expense;
        double amount;

        switch (choice) {
            case 1:
                cout << "Enter month name: ";
                cin >> month;
                tracker.addMonth(month);
                break;
            case 2:
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter expense name: ";
                cin >> expense;
                cout << "Enter amount: ";
                cin >> amount;
                tracker.addExpense(month, expense, amount);
                break;
            case 3:
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter expense to delete: ";
                cin >> expense;
                tracker.deleteExpense(month, expense);
                break;
            case 4:
                tracker.showAll();
                break;
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

