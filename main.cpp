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
    void showBalance();
    void createBankAccount();
    int generateAccountNo();
    void depositAmount();
    void pushDetailsToRespectiveFiles(int, int, std::string &);
    void withdrawAmount();
    void showFullDetails();

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

void bank::createBankAccount()
{
    // The given function is reponsible for creating a bank account
    int accountNo;
    std::string holderName;
    int deposit = 0;
    int choice = 0;

    std::cout << "Do you want to deposit initially(1 or 0)? ";
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Enter the deposit amount: ";
        std::cin >> deposit;
    }

    // Generate an account no.
    accountNo = generateAccountNo();
    std::cout << "Account no generated" << std::endl;
    std::cout << "The account no. is " << accountNo << std::endl;

    // Pass all details to function so that a record can be maintained
    pushDetailsToRespectiveFiles(accountNo, deposit, holderName);

    std::cout << "Account created" << std::endl
              << std::endl;
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

void bank::pushDetailsToRespectiveFiles(int acNo, int depo, std::string &holderName)
{
    std::ofstream acNosFile("accountNos.txt", std::ios::app);       // Create an account no file object
    std::ofstream balanceFile("balances.txt", std::ios::app);       // Create a balance file object
    std::ofstream holderNameFile("holderNames.txt", std::ios::app); // Create an account holder name file object

    std::cout << "Enter your name(Seperate first name, middle name and last name with an underscore): ";
    std::cin >> holderName;

    acNosFile << acNo << " ";
    balanceFile << depo << " ";
    holderNameFile << holderName << " ";

    acNosFile.close();
    balanceFile.close();
    holderNameFile.close();
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
    // This function is responsible for displaying the balance in account if user enters correct account no.
    std::ifstream accountNoFile("accountNos.txt");
    int accountNoTemp;
    int srNo = 0;
    int i = 0;
    int accountNo;
    int balance;
    bool isAcNoValid = false;

    std::cout << "Enter your account no: ";
    std::cin >> accountNo;

    while (accountNoFile.eof() == 0)
    {
        // Open accounts file and check whether the entered account no exists or not
        accountNoFile >> accountNoTemp;
        if (accountNoTemp == accountNo)
        {
            // If account no is found, break out of the loop
            isAcNoValid = true;
            srNo++;
            break;
        }
        srNo++;
    }
    accountNoFile.close(); // Close accounts file
    if (isAcNoValid == true)
    {
        // If account no. is found, open balance file
        std::ifstream balanceFile("balances.txt");
        while (i < srNo)
        {
            // Keep inputting balances until users balance is not found.
            balanceFile >> balance;
            i++;
        }
        // Output balance
        std::cout << "The balance in your account is Rs. " << balance << std::endl
                  << std::endl;
        balanceFile.close();
    }
    else if (isAcNoValid == false)
    {
        // Return to the calling function if account not found.
        std::cout << "Account no entered not found." << std::endl
                  << std::endl;
        return;
    }
}

void bank::depositAmount()
{
    // The below function is responsible for depositing amount to specified account no.
    int accountNo, amountDeposit, accountNoBuffer, srNo = 0, i = 0;
    bool isAcNoValid = false;
    int balanceBuffer;
    std::vector<int> balanceArray; // Vector responsible for holding data to write it again to balance file

    // Open account file to check whether account no. user will enter exists or not.
    std::ifstream accountNoFile("accountNos.txt");

    std::cout << "Enter your account no.: ";
    std::cin >> accountNo;

    while (accountNoFile.eof() == 0)
    {
        // Keep entering account no. until users account no. is not found
        accountNoFile >> accountNoBuffer;
        if (accountNo == accountNoBuffer)
        {
            // As soon as account no. is found, break out of this loop
            isAcNoValid = true;
            srNo++;
            break;
        }
        srNo++;
    }
    accountNoFile.close();
    if (isAcNoValid == false)
    {
        // Return to the calling function in case entered account no is invalid
        std::cout << "Account no. not found" << std::endl
                  << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        // If entered account no is found, open balance file
        std::ifstream balanceFile("balances.txt");

        while (i < totalAccounts)
        {
            // Keep entering balances until total no of account not reached
            balanceFile >> balanceBuffer;
            balanceArray.push_back(balanceBuffer);
            i++;
        }
        std::cout << "Enter the amount you want to deposit: ";
        std::cin >> amountDeposit;

        // balanceArray[srNo-1] represents balance of user who wants to deposit
        balanceArray[srNo - 1] = balanceArray[srNo - 1] + amountDeposit; // Modify the balance of user
        balanceFile.close();

        // Clear the balance file to write to it
        std::ofstream clearBalanceFile("balances.txt");
        clearBalanceFile.close();

        // Again open balance file in append mode
        std::ofstream balanceFileAgain("balances.txt", std::ios::app);
        i = 0;
        while (i < totalAccounts)
        {
            // Write the data to balance file
            balanceFileAgain << balanceArray[i] << " ";
            i++;
        }
        std::cout << std::endl;
        balanceFileAgain.close();
    }
}

void bank::withdrawAmount()
{
    // The below function is responsible for depositing amount to specified account no.
    int accountNo, amountToWithdraw, accountNoBuffer, srNo = 0, i = 0;
    bool isAcNoValid = false;
    bool isSufficientAmountAvailable = false;
    int balanceBuffer;
    std::vector<int> balanceArray; // Vector responsible for holding data to write it again to balance file

    // Open account file to check whether account no. user will enter exists or not.
    std::ifstream accountNoFile("accountNos.txt");

    std::cout << "Enter your account no.: ";
    std::cin >> accountNo;

    while (accountNoFile.eof() == 0)
    {
        // Keep entering account no. until users account no. is not found
        accountNoFile >> accountNoBuffer;
        if (accountNo == accountNoBuffer)
        {
            // As soon as account no. is found, break out of this loop
            isAcNoValid = true;
            srNo++;
            break;
        }
        srNo++;
    }
    accountNoFile.close();
    if (isAcNoValid == false)
    {
        // Return to the calling function in case entered account no is invalid
        std::cout << "Account no. not found" << std::endl
                  << std::endl;
        return;
    }
    else if (isAcNoValid == true)
    {
        // If entered account no is found, open balance file
        std::ifstream balanceFile("balances.txt");

        while (i < totalAccounts)
        {
            // Keep entering balances until total no of account not reached
            balanceFile >> balanceBuffer;
            balanceArray.push_back(balanceBuffer);
            i++;
        }
        std::cout << "Amount of balance available in your account is Rs. " << balanceArray[srNo - 1] << std::endl;
        std::cout << "Enter the amount you want to withdraw: ";
        std::cin >> amountToWithdraw;

        if ((balanceArray[srNo - 1] - amountToWithdraw) >= 0)
        {
            isSufficientAmountAvailable = true;
        }

        // balanceArray[srNo-1] represents balance of user who wants to withdraw
        if (isSufficientAmountAvailable == true)
        {
            balanceArray[srNo - 1] = balanceArray[srNo - 1] - amountToWithdraw; // Modify the balance of user
        }
        else if (isSufficientAmountAvailable == false)
        {
            balanceFile.close();
            std::cout << "Sufficient balance not available." << std::endl
                      << std::endl;
        }

        // Clear the balance file to write to it
        std::ofstream clearBalanceFile("balances.txt");
        clearBalanceFile.close();

        // Again open balance file in append mode
        std::ofstream balanceFileAgain("balances.txt", std::ios::app);
        i = 0;
        while (i < totalAccounts)
        {
            // Write the data to balance file
            balanceFileAgain << balanceArray[i] << " ";
            i++;
        }
        std::cout << std::endl;
        balanceFileAgain.close();
    }
}

void bank::showFullDetails()
{
    int accountNo, accountNoBuffer, srNo = 0, i = 0, balance;
    std::ifstream accountNoFile("accountNos.txt");
    bool isAcNoValid = false;
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
        // If account no. is found, open balance file
        std::ifstream balanceFile("balances.txt");
        std::ifstream accountNoFileAgain("accountNos.txt");
        std::ifstream holderNameFile("holderNames.txt");

        while (i < srNo)
        {
            // Keep inputting balances until users balance is not found.
            balanceFile >> balance;
            i++;
        }
        i = 0;
        while (i < srNo)
        {
            // Keep inputting account no. until users account is found.
            accountNoFileAgain >> accountNo;
            i++;
        }
        i = 0;
        while (i < srNo)
        {
            // Keep inputting holder names until account is found.
            holderNameFile >> holderName;
            i++;
        }

        std::cout << "Your name is: " << holderName << std::endl;
        std::cout << "Your account no. is: " << accountNo << std::endl;
        std::cout << "The balance in your account is Rs. " << balance << std::endl
                  << std::endl;
        balanceFile.close();
        accountNoFileAgain.close();
        holderNameFile.close();
    }
}

int main()
{
    bank customer;
    customer.systemRunner();

    return 0;
}