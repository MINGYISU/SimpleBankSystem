# SimpleBankSystem
This C++ program simulates a user-side bank system. It allows users to become clients of a bank and provides functionality to create and manage bank accounts. The program utilizes object-oriented programming principles to define the "Account" class, which represents individual bank accounts.

Upon running the program, users are presented with a menu where they can choose to create a new account, log in to an existing account, or quit the program.

If the user chooses to create a new account, they are prompted to input various details such as their first name, last name, address, social insurance number (SIN), deposit amount, and a password. The account information is stored in an array of "Account" objects.

When logging in to an existing account, the user is prompted to enter their ID(While it is not a common practice, in this program, the Social Insurance Number (SIN) is utilized as the ID/Account Number for logging in. This simplification assumes that each SIN is unique, allowing for easier code implementation). The program performs a search to find the matching account. If found, the user will be asked to enter password and gain access to a menu of options to manage their account. These options include resetting the account password, making deposits, withdrawing funds, closing the account, or logout.

The program handles dynamic resizing of the account array when reaching its capacity. It doubles the capacity and creates a new array, copies the existing account data into it, and updates the account pointer accordingly.

Overall, this program provides a simulated bank system where users can create and manage their bank accounts, perform transactions, and maintain account security.
