#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class bank
{
private:
    static int totalAccounts;
    int initialSetup();
    void printChoices();
    int generateAccountNo();
    void showBalance();
    void depositAmount();
    void withdrawAmount();
    void showFullDetails();
    void createBankAccount();

public:
    bank()
    {
        totalAccounts = initialSetup();
    }
    void systemRunner();
};

int bank::totalAccounts = 0;

int bank::initialSetup()
{
    std::string totalAccountsBuffer;
    std::ifstream totalAccountsFile("totalAccounts.txt");

    getline(totalAccountsFile, totalAccountsBuffer);
    totalAccountsFile.close();

    return (std::stoi(totalAccountsBuffer));
}

void bank::systemRunner()
{
    // This function handles user inputs
    while (true)
    {
        int choice;
        printChoices();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 0:
            exit(0);
            break;
        case 1:
            showBalance();
            break;
        case 2:
            depositAmount();
            break;
        case 3:
            withdrawAmount();
            break;
        case 4:
            showFullDetails();
            break;
        case 5:
            createBankAccount();
            break;
        default:
            break;
        }
    }
}

int bank::generateAccountNo()
{
    // Generate an account no. using given function
    std::ifstream totalAccountsFile("totalAccounts.txt");
    std::string totalAccountsVar;
    totalAccountsFile >> totalAccountsVar;

    int totAccounts = (std::stoi(totalAccountsVar) + 1);
    totalAccountsFile.close();

    std::ofstream totalAccountsFile2("totalAccounts.txt");
    totalAccountsFile2 << std::to_string(totAccounts);
    totalAccountsFile2.close();

    return totAccounts;
}

void bank::printChoices()
{
    std::cout << "Our services: " << std::endl;
    std::cout << "1. View balance" << std::endl
              << "2. Deposit" << std::endl
              << "3. Withdrawal" << std::endl
              << "4. View account details" << std::endl
              << "5. Create a new account" << std::endl
              << "0. Exit" << std::endl;
}

void bank::showBalance()
{
    // The details of user are account no., holder name, balance available;
    int accountNo, balance;
    int accountNoTemp;
    std::string temp;
    int i = 0, j = 0;
    int srNo = 0;
    bool isAcNoValid = false;

    std::ifstream allDetailsFile("allDetails.txt");
    std::cout << "Enter the account no.: ";
    std::cin >> accountNo;

    while (allDetailsFile.eof() == 0)
    {
        allDetailsFile >> accountNoTemp;
        if (accountNo == accountNoTemp)
        {
            isAcNoValid = true;
            srNo++;
            break;
        }
        while (i < 2)
        {
            allDetailsFile >> temp;
            i++;
        }

        if (i == 2)
        {
            i = 0;
        }
        srNo++;
    }
    allDetailsFile.close();
    if (isAcNoValid == false)
    {
        std::cout << "Account no. entered is invalid" << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        i = 0;
        std::ifstream allDetailsFileAgain("allDetails.txt");

        while (i < srNo)
        {
            allDetailsFileAgain >> temp;
            allDetailsFileAgain >> temp;
            allDetailsFileAgain >> balance;
            i++;
        }
        std::cout << "Your balance is " << balance << std::endl;
    }
}

void bank::depositAmount()
{
    std::vector<int> accountNosToBeWritten;
    std::vector<std::string> accountHolderNamesToBeWritten;
    std::vector<int> balanceArrayToBeWritten;
    int accountNoTemp;
    int accountNo;
    int i = 0;
    bool isAcNoValid = false;
    int srNo = 0;
    std::string tempString;
    int tempInt;
    int depositAmount;
    std::ifstream allDetailsFile("allDetails.txt");

    std::cout << "Enter account no.: ";
    std::cin >> accountNo;

    while (allDetailsFile.eof() == 0)
    {
        allDetailsFile >> accountNoTemp;
        if (accountNo == accountNoTemp)
        {
            isAcNoValid = true;
            srNo++;
            break;
        }
        while (i < 2)
        {
            allDetailsFile >> tempString;
            i++;
        }

        if (i == 2)
        {
            i = 0;
        }
        srNo++;
    }
    allDetailsFile.close();
    if (isAcNoValid == false)
    {
        std::cout << "Account no. entered is invalid" << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        i = 0;
        std::ifstream allDetailsFileAgain("allDetails.txt");

        while (i < totalAccounts)
        {
            allDetailsFileAgain >> tempInt;
            accountNosToBeWritten.push_back(tempInt);
            allDetailsFileAgain >> tempString;
            accountHolderNamesToBeWritten.push_back(tempString);
            allDetailsFileAgain >> tempInt;
            balanceArrayToBeWritten.push_back(tempInt);
            i++;
        }

        std::cout << "Enter the amount you want to deposit: ";
        std::cin >> depositAmount;
        balanceArrayToBeWritten[srNo - 1] += depositAmount;

        allDetailsFileAgain.close();

        std::ofstream allDetailsFileOnceAgain("allDetails.txt");
        i = 0;
        while (i < totalAccounts)
        {
            allDetailsFileOnceAgain << accountNosToBeWritten[i] << " " << accountHolderNamesToBeWritten[i] << " " << balanceArrayToBeWritten[i] << "\n";
            i++;
        }
        allDetailsFileOnceAgain.close();
    }
}

void bank::withdrawAmount()
{
    std::vector<int> accountNosToBeWritten;
    std::vector<std::string> accountHolderNamesToBeWritten;
    std::vector<int> balanceArrayToBeWritten;
    int accountNoTemp;
    int accountNo;
    int i = 0;
    bool isAcNoValid = false;
    int srNo = 0;
    std::string tempString;
    int tempInt;
    int depositAmount;
    std::ifstream allDetailsFile("allDetails.txt");

    std::cout << "Enter account no.: ";
    std::cin >> accountNo;

    while (allDetailsFile.eof() == 0)
    {
        allDetailsFile >> accountNoTemp;
        if (accountNo == accountNoTemp)
        {
            isAcNoValid = true;
            srNo++;
            break;
        }
        while (i < 2)
        {
            allDetailsFile >> tempString;
            i++;
        }

        if (i == 2)
        {
            i = 0;
        }
        srNo++;
    }
    allDetailsFile.close();
    if (isAcNoValid == false)
    {
        std::cout << "Account no. entered is invalid" << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        i = 0;
        std::ifstream allDetailsFileAgain("allDetails.txt");

        while (i < totalAccounts)
        {
            allDetailsFileAgain >> tempInt;
            accountNosToBeWritten.push_back(tempInt);
            allDetailsFileAgain >> tempString;
            accountHolderNamesToBeWritten.push_back(tempString);
            allDetailsFileAgain >> tempInt;
            balanceArrayToBeWritten.push_back(tempInt);
            i++;
        }

        std::cout << "The balance in your account is: " << balanceArrayToBeWritten[srNo - 1] << std::endl;

        std::cout << "Enter the amount you want to withdraw: ";
        std::cin >> depositAmount;

        if (balanceArrayToBeWritten[srNo - 1] - depositAmount >= 0)
        {
            balanceArrayToBeWritten[srNo - 1] -= depositAmount;
        }
        else
        {
            std::cout << "Insufficient balance." << std::endl;
        }

        allDetailsFileAgain.close();

        std::ofstream clearAllDetailsFile("allDetails.txt");
        clearAllDetailsFile.close();

        std::ofstream allDetailsFileOnceAgain("allDetails.txt", std::ios::app);
        i = 0;
        while (i < totalAccounts)
        {
            allDetailsFileOnceAgain << accountNosToBeWritten[i] << " " << accountHolderNamesToBeWritten[i] << " " << balanceArrayToBeWritten[i] << "\n";
            i++;
        }
        allDetailsFileOnceAgain.close();
    }
}

void bank::showFullDetails()
{
    int accountNo, accountNoBuffer, srNo = 0, i = 0;
    std::ifstream accountNoFile("allDetails.txt");
    bool isAcNoValid = false;
    int balance;
    std::string temp;
    std::string holderName;

    std::cout << "Enter your account no.: ";
    std::cin >> accountNo;

    while (accountNoFile.eof() == 0)
    {
        accountNoFile >> accountNoBuffer;
        if (accountNoBuffer == accountNo)
        {
            srNo++;
            isAcNoValid = true;
            break;
        }

        accountNoFile >> temp;
        accountNoFile >> temp;
        srNo++;
    }
    accountNoFile.close(); // Close accounts file

    if (isAcNoValid == false)
    {
        std::cout << "The account no. entered is invalid." << std::endl
                  << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        std::ifstream allDetailsFileAgain("allDetails.txt");
        while (i < srNo)
        {
            allDetailsFileAgain >> accountNo;
            allDetailsFileAgain >> holderName;
            allDetailsFileAgain >> balance;
            i++;
        }
        std::cout << "Your account no. is " << accountNo << std::endl;
        std::cout << "Your name is " << holderName << std::endl;
        std::cout << "Your balance is " << balance << std::endl
                  << std::endl;
    }
}

void bank::createBankAccount()
{
    int depositAmount = 0;
    bool choice = false;
    int accountNo;
    std::string holderName;
    std::ofstream allDetailsFile("allDetails.txt", std::ios::app);

    std::cout << "Do you want to deposit initially?(1 or 0): ";
    std::cin >> choice;

    if (choice == false)
    {
        depositAmount = 0;
    }
    else if (choice == true)
    {
        std::cout << "Enter the deposit amount: ";
        std::cin >> depositAmount;
    }
    std::cout << "Enter your name(Enter first name, middle name and last name seperated with underscore): ";
    std::cin >> holderName;

    accountNo = generateAccountNo();

    allDetailsFile << accountNo << " " << holderName << " " << depositAmount << "\n";
    allDetailsFile.close();
}

int main()
{
    bank customer;
    customer.systemRunner();

    return 0;
}