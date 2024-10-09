#include <iostream>
#include <vector>
#include <string>

class Transaction {
private:
    std::string type; // "income" or "expense"
    std::string category;
    double amount;
    std::string date; // e.g., "YYYY-MM-DD"
    std::string description;

public:
    Transaction(std::string type, std::string category, double amount, std::string date, std::string description)
        : type(type), category(category), amount(amount), date(date), description(description) {}

    void displayTransaction() const {
        std::cout << "[" << date << "] " << type << ": " << amount << " (" << category << ") - " << description << "\n";
    }

    double getAmount() const { return amount; }
    void setAmount(double newAmount) { amount = newAmount; }
};

class User {
private:
    std::string username;
    std::string password;
    std::vector<Transaction> transactions;

public:
    User(std::string username, std::string password) : username(username), password(password) {}

    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    void viewTransactions() const {
        std::cout << "Transactions for " << username << ":\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            std::cout << i + 1 << ". ";
            transactions[i].displayTransaction();
        }
    }

    void editTransaction(int index) {
        if (index >= 0 && index < transactions.size()) {
            Transaction& transaction = transactions[index];
            double newAmount;
            std::cout << "Edit transaction (Amount: " << transaction.getAmount() << "):\n";
            std::cout << "Enter new amount: ";
            std::cin >> newAmount;
            transaction.setAmount(newAmount);
            std::cout << "Transaction updated.\n";
        } else {
            std::cout << "Invalid transaction index.\n";
        }
    }

    void deleteTransaction(int index) {
        if (index >= 0 && index < transactions.size()) {
            transactions.erase(transactions.begin() + index);
            std::cout << "Transaction deleted.\n";
        } else {
            std::cout << "Invalid transaction index.\n";
        }
    }

    std::string getUsername() const { return username; }

    bool verifyPassword(const std::string& passwordToCheck) const {
        return password == passwordToCheck;
    }
};

class Budget {
private:
    std::string category;
    double limit;
    double spent;

public:
    Budget(std::string category, double limit) : category(category), limit(limit), spent(0) {}

    void addSpent(double amount) {
        spent += amount;
    }

    void displayBudget() const {
        std::cout << "Category: " << category << " | Limit: " << limit << " | Spent: " << spent << "\n";
    }
};

void registerUser(std::vector<User>& users) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    users.emplace_back(username, password);
    std::cout << "User registered successfully!\n";
}

User* loginUser(std::vector<User>& users) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (auto& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            return &user;
        }
    }
    std::cout << "Invalid credentials.\n";
    return nullptr;
}

void displayMainMenu(User& user) {
    int choice;
    do {
        std::cout << "\n--- Personal Finance Tracker ---\n";
        std::cout << "1. Add Transaction\n";
        std::cout << "2. View Transactions\n";
        std::cout << "3. Edit Transaction\n";
        std::cout << "4. Delete Transaction\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string type, category, date, description;
                double amount;
                std::cout << "Enter type (income/expense): ";
                std::cin >> type;
                std::cout << "Enter category: ";
                std::cin >> category;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                std::cout << "Enter date (YYYY-MM-DD): ";
                std::cin >> date;
                std::cout << "Enter description: ";
                std::cin.ignore();
                std::getline(std::cin, description);
                user.addTransaction(Transaction(type, category, amount, date, description));
                break;
            }
            case 2:
                user.viewTransactions();
                break;
            case 3: {
                int index;
                std::cout << "Enter transaction index to edit: ";
                std::cin >> index;
                user.editTransaction(index - 1);
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter transaction index to delete: ";
                std::cin >> index;
                user.deleteTransaction(index - 1);
                break;
            }
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);
}

int main() {
    std::vector<User> users;
    int choice;

    do {
        std::cout << "\n--- Welcome to Personal Finance Tracker ---\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2: {
                User* loggedInUser = loginUser(users);
                if (loggedInUser) {
                    displayMainMenu(*loggedInUser);
                }
                break;
            }
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
