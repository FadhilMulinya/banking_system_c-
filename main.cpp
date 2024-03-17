#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class: Account
class Account {
protected:
    string accountNumber;
    double balance;

public:
    Account(string accNo, double bal) {
        accountNumber = accNo;
        balance = bal;
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "You have deposited " << amount << " to account " << accountNumber << "Your New balance is: " << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "You have withdrawn " << amount << " from the account " << accountNumber << ". Remaining balance: " << balance << endl;
        } else {
            cout << "Insufficient balance in account " << accountNumber << ". Cannot withdraw " << amount << endl;
        }
    }

    virtual void displayBalance() {
        cout << "Account Number: " << accountNumber << ", Balance: " << balance << endl;
    }

    virtual string getType() = 0; // Pure virtual function to get account type
};

// Derived class: SavingsAccount
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNo, double bal, double rate)
        : Account(accNo, bal), interestRate(rate) {}

    void calculateInterest() {
        double interest = balance * interestRate;
        deposit(interest);
        cout << "Interest of " << interest << " has been added to your savings account." << endl;
    }

    string getType() override {
        return "Savings Account";
    }
};

// Derived class: CheckingAccount
class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNo, double bal, double limit)
        : Account(accNo, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (balance >= amount) {
            Account::withdraw(amount);
        } else if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "Overdraft limit used for withdrawal of " << amount << " from account " << accountNumber << ". Remaining balance: " << balance << endl;
        } else {
            cout << "Insufficient balance and overdraft limit in account " << accountNumber << ". Cannot withdraw " << amount << endl;
        }
    }

    string getType() override {
        return "Checking Account";
    }
};

// Derived class: CreditCardAccount
class CreditCardAccount : public Account {
private:
    double creditLimit;
    double interestRate;

public:
    CreditCardAccount(string accNo, double bal, double limit, double rate)
        : Account(accNo, bal), creditLimit(limit), interestRate(rate) {}

    void withdraw(double amount) override {
        if (amount <= balance + creditLimit) {
            balance -= amount;
            cout << "Withdrew " << amount << " from account " << accountNumber << ". Remaining balance: " << balance << endl;
        } else {
            cout << "Exceeding credit limit in account " << accountNumber << ". Cannot withdraw " << amount << endl;
        }
    }

    void calculateInterest() {
        double interest = (creditLimit - balance) * interestRate;
        balance -= interest;
        cout << "Interest of " << interest << " has been charged for your credit card account." << endl;
    }

    string getType() override {
        return "Credit Card Account";
    }
};

int main() {
    vector<Account*> accounts;

    accounts.push_back(new SavingsAccount("Fadhil123", 740.0, 0.15));
    accounts.push_back(new CheckingAccount("Mwende23", 2000.0, 1000.0));
    accounts.push_back(new CreditCardAccount("Kangat345", 30,000.0, 100.0, 0.02));

    for (Account* account : accounts) {
        cout << "Account Type: " << account->getType() << endl;
        account->deposit(300.0);
        account->withdraw(150.0);
        account->displayBalance();
        cout << endl;

        // Handle specialized operations
        if (dynamic_cast<SavingsAccount*>(account)) {
            SavingsAccount* savingsAcc = dynamic_cast<SavingsAccount*>(account);
            savingsAcc->calculateInterest();
        } else if (dynamic_cast<CreditCardAccount*>(account)) {
            CreditCardAccount* creditCardAcc = dynamic_cast<CreditCardAccount*>(account);
            creditCardAcc->calculateInterest();
        }

        cout << "----------------------------" << endl;
    }

    // Clean up dynamically allocated objects
    for (Account* account : accounts) {
        delete account;
    }

    return 0;
}
