import pandas as pd
import bcrypt
import getpass


class Bank:
    @staticmethod
    def __modify_row(
            file_name,
            account_no=-1, password=None,
            name=None,
            balance=float(-1),
            new_account_creation=False,
    ):
        df = pd.read_csv(file_name)
        if new_account_creation:
            df.loc[len(df)] = [account_no, password, name, balance]
        else:
            customer_index = df[df["account_no"] == account_no].index[0]
            if balance != -1:
                df.at[customer_index, "balance"] = balance
            if name is not None:
                df.at[customer_index, "name"] = name
            if password is not None:
                df.at[customer_index, "password"] = password

        df.to_csv(file_name, index=False)

    @staticmethod
    def _create_account():
        df = pd.read_csv("data.csv")
        name = input("Enter your name: ")
        balance = float(input("Enter your initial balance: "))
        password = getpass.getpass("Enter your password: ")
        password_bytes = password.encode('utf-8')
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password_bytes, salt)
        account_no = int(df.shape[0]) + 1

        Bank.__modify_row(
            "data.csv",
            account_no=account_no,
            name=name,
            balance=balance,
            new_account_creation=True,
            password=hashed_password,
        )

        print("Account created!")
        print("Your new account no. is:", account_no)

    @staticmethod
    def _delete_account(account_no):
        sure = input("Are you sure you want to delete the account? (y/n)")
        if sure == 'y' or sure == 'Y':
            df = pd.read_csv("data.csv")
            customer_index_no = df[df["account_no"] == account_no].index[0]
            df = df.drop(customer_index_no)
            df.to_csv("data.csv", index=False)
            print("Account deleted!")

    @staticmethod
    def _update_existing_account(account_no):
        df = pd.read_csv("data.csv")

        customer_index = df[df["account_no"] == account_no].index[0]
        new_name = input("Enter new name: ")
        new_password = getpass.getpass("Enter new password: ")

        new_password_bytes = new_password.encode("utf-8")
        salt = bcrypt.gensalt()
        new_hashed_password = bcrypt.hashpw(new_password_bytes, salt)

        Bank.__modify_row(
            "data.csv",
            account_no=account_no,
            name=new_name,
            balance=-1,
            new_account_creation=False, password=new_hashed_password,
        )
        print("Account updated!")

    @staticmethod
    def _deposit(account_no):
        df = pd.read_csv("data.csv")
        customer_index = df[df["account_no"] == account_no].index[0]
        deposit_amount = float(input("Enter your deposit amount: "))
        prev_balance = float(df.at[customer_index, "balance"])

        Bank.__modify_row(
            "data.csv",
            account_no=account_no,
            name=None,
            balance=prev_balance + deposit_amount,
            new_account_creation=False,
            password=None
        )
        print("Amount deposited!")

    @staticmethod
    def _withdrawal(account_no):
        df = pd.read_csv("data.csv")
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

    def print_existing_customer_facilities(self, account_no):
        while True:
            print("Facilities:")
            print("1. Update the account details")
            print("2. Deleting the account")
            print("3. Withdrawal")
            print("4. Deposit")
            print("5. Logout")

            operation = input("What would you like to do? ")
            if operation == "1":
                self._update_existing_account(account_no)
            elif operation == "2":
                self._delete_account(account_no)
                return
            elif operation == "3":
                self._withdrawal(account_no)
            elif operation == "4":
                self._deposit(account_no)
            elif operation == "5":
                print("Logged out successfully!")
                return
            else:
                print("Invalid option!")

    @staticmethod
    def existing_or_new_user():
        print("Are you an existing customer or new customer?")
        print("1. Existing customer")
        print("2. New customer")
        print("3. Exit")
        choice = int(input())
        return choice

    @staticmethod
    def login_existing_customer():
        account_no = int(input("Enter your account number: "))
        password = getpass.getpass("Enter your password: ")

        df = pd.read_csv("data.csv")
        if account_no not in df["account_no"].values or (
                account_no in df['account_no'] and password not in df["password"].values):
            print("Account does not exist or password is incorrect!")
            return False, None
        else:
            return True, account_no

    @staticmethod
    def new_customer():
        Bank._create_account()

    def __init__(self):
        print("Welcome to Nagpur Sahakari Bank!")
        while True:
            existing_or_new = self.existing_or_new_user()
            if existing_or_new == 1:
                is_legit, account_no = self.login_existing_customer()
                if is_legit:
                    self.print_existing_customer_facilities(account_no)
            elif existing_or_new == 2:
                self.new_customer()
            else:
                exit()


if __name__ == "__main__":
    customer = Bank()