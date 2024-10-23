import pandas as pd


class Bank:
    @staticmethod
    def __modify_row(
        file_name,
        account_no=-1,
        name=None,
        balance=float(-1),
        new_account_creation=False,
    ):
        df = pd.read_csv(file_name)
        if new_account_creation:
            df.loc[len(df)] = [account_no, name, balance]
        else:
            customer_index = df[df["account_no"] == account_no].index[0]
            if balance != -1:
                df.at[customer_index, "balance"] = balance
            if name is not None:
                df.at[customer_index, "name"] = name

        df.to_csv(file_name, index=False)

    @staticmethod
    def _create_account():
        df = pd.read_csv("data.csv")
        name = input("Enter your name: ")
        balance = float(input("Enter your initial balance: "))
        account_no = int(df.shape[0]) + 1

        Bank.__modify_row(
            "data.csv",
            account_no=account_no,
            name=name,
            balance=balance,
            new_account_creation=True,
        )

        print("Account created!")
        print("Your new account no. is:", account_no)

    @staticmethod
    def _delete_account():
        df = pd.read_csv("data.csv")
        account_no = int(input("Enter your account no: "))

        if account_no not in df["account_no"].values:
            print("Account does not exist!")
        else:
            customer_index_no = df[df["account_no"] == account_no].index[0]
            df = df.drop(customer_index_no)
            df.to_csv("data.csv", index=False)
            print("Account deleted!")

    @staticmethod
    def _update_existing_account():
        df = pd.read_csv("data.csv")
        account_no = int(input("Enter your account number: "))
        if account_no not in df["account_no"].values:
            print("Account does not exist!")
        else:
            customer_index = df[df["account_no"] == account_no].index[0]
            new_name = input("Enter new name: ")
            Bank.__modify_row(
                "data.csv",
                account_no=account_no,
                name=new_name,
                balance=-1,
                new_account_creation=False,
            )
            print("Account updated!")

    def _update_account_details(self):
        print("What do you want to do?")
        print("1. Update existing account details")
        print("2. Creating a new account")
        choice = input("Enter your choice: ")
        if choice == "1":
            self._update_existing_account()
        elif choice == "2":
            self._create_account()
        else:
            print("Invalid choice")

    @staticmethod
    def _deposit():
        df = pd.read_csv("data.csv")
        account_no = int(input("Enter your account number: "))
        if account_no not in df["account_no"].values:
            print("Account does not exist!")
        else:
            customer_index = df[df["account_no"] == account_no].index[0]
            deposit_amount = float(input("Enter your deposit amount: "))

            prev_balance = float(df.at[customer_index, "balance"])

            Bank.__modify_row(
                "data.csv",
                account_no=account_no,
                name=None,
                balance=prev_balance + deposit_amount,
                new_account_creation=False,
            )
            print("Amount deposited!")

    @staticmethod
    def _withdrawal():
        df = pd.read_csv("data.csv")
        account_no = int(input("Enter your account number: "))
        if account_no not in df["account_no"].values:
            print("Account does not exist!")
        else:
            customer_index = df[df["account_no"] == account_no].index[0]
            prev_balance = float(df.at[customer_index, "balance"])
            print("Your current balance is:", prev_balance)
            withdrawal_amt = float(input("Enter your withdrawal amount: "))

            if withdrawal_amt <= prev_balance:
                Bank.__modify_row(
                    "data.csv",
                    account_no=account_no,
                    name=None,
                    balance=prev_balance - withdrawal_amt,
                    new_account_creation=False,
                )
                print("Amount withdrawn!")
            else:
                print("Insufficient funds!")

    @staticmethod
    def facilities():
        print("What do you want to do?")
        print("1. Account creation/updation")
        print("2. Account deletion")
        print("3. Deposit")
        print("4. Withdrawal")
        print("5. Exit")
        choice = input("Enter your choice: ")
        return choice

    def __init__(self):
        while True:
            operation = self.facilities()
            if operation == "1":
                self._update_account_details()
            elif operation == "2":
                self._delete_account()
            elif operation == "3":
                self._deposit()
            elif operation == "4":
                self._withdrawal()
            else:
                exit()


if __name__ == "__main__":
    customer = Bank()
