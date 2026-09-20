
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100;

class Accounts{
public:
    int accountNumber;
    string name, phone, address;
    float balance = 0;
    float loan = 0;

    void CheckBalance(){ cout << "\nBalance: Rs." << balance << endl; }

    void Deposit(){
        float amt;
        cout << "Deposit Amount: ";
        cin >> amt;
        balance += amt;
        cout << "Deposit Successful!\n";
    }

    void Withdraw(){
        float amt;
        cout << "Withdraw Amount: ";
        cin >> amt;
        if(amt <= balance){
            balance -= amt;
            cout << "Withdraw Successful!\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    void Borrow(){
        float amt;
        cout << "Loan Amount: ";
        cin >> amt;
        loan += amt;
        balance += amt;
        cout << "Loan Approved!\n";
    }

    void Return(){
        float amt;
        cout << "Return Loan Amount: ";
        cin >> amt;
        if(amt <= balance && amt <= loan){
            balance -= amt;
            loan -= amt;
            cout << "Loan Returned!\n";
        } else {
            cout << "Invalid Amount!\n";
        }
    }

    void ShowAccount(){
        cout << "\nAccount No: " << accountNumber
             << "\nName: " << name
             << "\nPhone: " << phone
             << "\nAddress: " << address
             << "\nBalance: " << balance
             << "\nLoan: " << loan << endl;
    }
};

Accounts bank[MAX];
int totalAccounts = 0;

void SaveData(){
    ofstream file("accounts.txt");
    for(int i=0;i<totalAccounts;i++){
        file << bank[i].accountNumber << " "
             << bank[i].name << " "
             << bank[i].phone << " "
             << bank[i].address << " "
             << bank[i].balance << " "
             << bank[i].loan << endl;
    }
    file.close();
}

void LoadData(){
    ifstream file("accounts.txt");
    totalAccounts = 0;
    while(file >> bank[totalAccounts].accountNumber
               >> bank[totalAccounts].name
               >> bank[totalAccounts].phone
               >> bank[totalAccounts].address
               >> bank[totalAccounts].balance
               >> bank[totalAccounts].loan){
        totalAccounts++;
    }
    file.close();
}

int FindAccount(int accNo){
    for(int i=0;i<totalAccounts;i++){
        if(bank[i].accountNumber == accNo) return i;
    }
    return -1;
}

void inputNewData(Accounts &data){
    cout << "Enter Account Number: ";
    cin >> data.accountNumber;
    cout << "Enter Name: ";
    cin >> data.name;
    cout << "Enter Phone: ";
    cin >> data.phone;
    cout << "Enter Address: ";
    cin >> data.address;
    data.balance = 0;
    data.loan = 0;
}

void inputUpgradeData(Accounts data[]){
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;
    int idx = FindAccount(acc);
    if(idx==-1){
        cout << "Account Not Found\n";
        return;
    }
    cout << "New Phone: ";
    cin >> data[idx].phone;
    cout << "New Address: ";
    cin >> data[idx].address;
    cout << "Details Updated\n";
}

void outData(Accounts data[]){
    cout << "\n----- All Accounts -----\n";
    for(int i=0;i<totalAccounts;i++){
        data[i].ShowAccount();
        cout << "----------------------\n";
    }
}

void TransferMoney(Accounts data[]){
    int from,to;
    float amt;
    cout << "Sender Account: ";
    cin >> from;
    cout << "Receiver Account: ";
    cin >> to;
    cout << "Amount: ";
    cin >> amt;

    int s = FindAccount(from);
    int r = FindAccount(to);

    if(s==-1 || r==-1){
        cout << "Invalid Account!\n";
        return;
    }

    if(data[s].balance >= amt){
        data[s].balance -= amt;
        data[r].balance += amt;
        cout << "Transfer Successful!\n";
    } else {
        cout << "Insufficient Balance!\n";
    }
}

void DeleteAccount(Accounts data[]){
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    int idx = FindAccount(acc);
    if(idx==-1){
        cout << "Account Not Found!\n";
        return;
    }

    for(int i=idx;i<totalAccounts-1;i++)
        data[i]=data[i+1];

    totalAccounts--;
    cout << "Account Deleted!\n";
}

void Menu(Accounts data[]){
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    int idx = FindAccount(acc);

    if(idx==-1){
        cout << "Account Not Found!\n";
        return;
    }

    int choice;

    do{
        cout << "\n--- Customer Menu ---\n";
        cout << "1.Check Balance\n2.Deposit\n3.Withdraw\n4.Borrow Loan\n5.Return Loan\n6.Show Profile\n7.Back\n";
        cin >> choice;

        switch(choice){
            case 1:data[idx].CheckBalance();break;
            case 2:data[idx].Deposit();break;
            case 3:data[idx].Withdraw();break;
            case 4:data[idx].Borrow();break;
            case 5:data[idx].Return();break;
            case 6:data[idx].ShowAccount();break;
        }

    }while(choice!=7);
}

void MainMenu(){
    int choice;

    do{
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Login Account\n";
        cout << "3. Update Account\n";
        cout << "4. Transfer Money\n";
        cout << "5. View All Accounts (Admin)\n";
        cout << "6. Delete Account\n";
        cout << "7. Save Data\n";
        cout << "8. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch(choice){

            case 1:
                inputNewData(bank[totalAccounts]);
                totalAccounts++;
                cout << "Account Created Successfully!\n";
                break;

            case 2:
                Menu(bank);
                break;

            case 3:
                inputUpgradeData(bank);
                break;

            case 4:
                TransferMoney(bank);
                break;

            case 5:
                outData(bank);
                break;

            case 6:
                DeleteAccount(bank);
                break;

            case 7:
                SaveData();
                cout << "Data Saved!\n";
                break;

            case 8:
                SaveData();
                cout << "Thank You!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    }while(choice!=8);
}

int main(){

    LoadData();
    MainMenu();

    return 0;
}
