#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int HEADER_LINES = 3;
const int SCREEN_BOTTOM = 30;
int currentLine = HEADER_LINES;
bool Button = 1;
string Login_temp[2];
int* Ids = nullptr;
string* Names = nullptr;
string* Passwords = nullptr;
int* Amounts = nullptr;
int TotalUsers = 0;

void BankName();
void Mover(int x, int y);
void Painter(int color=15);
void Sweeper(int header_lines = HEADER_LINES);
void Pen(const string& msg, int color = 15,int eddy=0);
void LoginPage();
void LoginOption();
void RegisterationOption();
void ExitOption();
void alert(int aaa = 0);
void Entry();
void Bankfilewriting();
void Bankfilereading();
void IncArrays();
int UniqueID();

void Admin_page();
void View_record(int Id);
void View_all_record();
void Give_money(int Id);
void Give_money_to_all();
void Delete_record(int Id);
void Delete_all_records();
void Back();

void UserPage();
void View_Account();
void Withdrawl_Money();
void Delete_Account();
void Send_Money();

void alert(int aaa){
    ofstream alerte("Logs.txt", ios::app);
    alerte << aaa << " ";
    alerte.close();
}

void BankName() {
    Painter(2+19);
    Mover(0, 0); cout << "===============================================================";
    Painter(11);
    Mover(0, 1); cout << "              BANK Al SHAIGAN LIMITED (CLI)         ";
    Painter(2+19);
    Mover(0, 2); cout << "===============================================================";
    Painter(15);
}

void Mover(int x, int y) {
    COORD coordinates = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Painter(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Sweeper(int header_lines) {
    for (int i = header_lines; i < SCREEN_BOTTOM; i++) {
        Mover(0, i);
        cout << "                                                              ";
    }
    currentLine = HEADER_LINES + 8;
}

void Pen(const string& msg, int color,int eddy) {
    Painter(color);
    Mover(0, currentLine+eddy);
    cout << msg;
    currentLine++;
    if (currentLine >= SCREEN_BOTTOM) {
        Sweeper();
        currentLine = HEADER_LINES + 8; 
    }
    Painter(15);
}

void ExitOption(){
    Sweeper();
    Pen("Exiting System...", 12);
    Sleep(1000);
    Bankfilewriting();
    system("cls");
    exit(1);
}

void Entry(){
    Painter(6);
    Mover(0, HEADER_LINES + 6); cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _";
    Painter(5);
    Mover(0, HEADER_LINES + 7); cout << "Enter Your Preference:";
    Painter();
    currentLine = HEADER_LINES + 8; 
}

void LoginPage() {
    Sweeper();
    Painter(10);
    Mover(0, HEADER_LINES + 1); cout << "1. Login";
    Mover(0, HEADER_LINES + 2); cout << "2. User Registeration";
    Mover(0, HEADER_LINES + 3); cout << "3. Exit";
    Entry();
    Login_temp[0] = Login_temp[1] = "";
    int choice;
    cout << endl << "Choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        LoginOption();
    } 
    else if (choice == 2) {
        RegisterationOption();
    }
    else if (choice == 3) {
        Button = 0;
        ExitOption();
    } 
    else {
        Pen("Invalid", 12);
        Sleep(400);
        LoginPage();
    }
}

void Admin_page(){
    Sweeper();
    Painter(10);
    Mover(0, HEADER_LINES + 1);
    cout << "                  Administration";
    Mover(0, HEADER_LINES + 2); cout << "1. View Record                       2. View all record";
    Mover(0, HEADER_LINES + 3); cout << "3. Give Money                        4. Give Money to All";
    Mover(0, HEADER_LINES + 4); cout << "5. Delete Record                     6. Delete ALL Records";
    Mover(0, HEADER_LINES + 5); cout << "7. Back                              8. Exit";
    Painter();
    Entry();
    int choice, tempId;
    cout << endl << "Choice: ";
    cin >> choice;
    if (choice == 1) {
        Pen("Enter ID to view:", 11,3);
        cin >> tempId;
        View_record(tempId);
    } 
    else if (choice == 2) {
        View_all_record();
    }
    else if (choice == 3) {
        Pen("Enter ID to give money:", 11,3);
        cin >> tempId;
        Give_money(tempId);
    } 
    else if (choice == 4) {
        Give_money_to_all();
    }
    else if (choice == 5) {
        Pen("Enter ID to delete:", 11,3);
        cin >> tempId;
        Delete_record(tempId);
    }     
    else if (choice == 6) {
        Delete_all_records();
    }
    else if (choice == 7) {
        LoginPage();
    }     
    else if (choice == 8) {
        ExitOption();
    }
    else{
        Pen("Invalid", 12);
        Sleep(400);
        Admin_page();
    }
}

void View_record(int Id){
    Sweeper();
    Entry();
    int found = 0;
    for (int i = 0; i < TotalUsers; i++) {
        if (Ids[i] == Id) {
            Pen("ID: " + to_string(Ids[i]), 10);
            Pen("Name: " + Names[i], 10);
            Pen("Password: " + Passwords[i], 10);
            Pen("Balance: " + to_string(Amounts[i]), 10);
            found = 1;
        }
    }
    if (!found) {
        Pen("User not found.", 12);
    }
    Sleep(900);
    Admin_page();
}

void View_all_record() {
    const int startLine = 11;
    const int perPage = SCREEN_BOTTOM - startLine - 2;
    int page = 0;
    int pages = (TotalUsers + perPage - 1) / perPage;
    char cmd;
    bool quit = false;
    while (!quit) {
        for (int i = startLine; i < SCREEN_BOTTOM; i++) {
            Mover(0, i);
            cout << "                                                              ";
        }
        Mover(0, startLine);
        Painter(14);
        cout << "Viewing all records. Page " << (page + 1) << " of " << pages;
        Painter(15);
        int start = page * perPage;
        int end = min(TotalUsers, start + perPage);
        for (int i = start, line = startLine + 1; i < end; i++, line++) {
            Mover(0, line);
            Painter(10);
            cout << "ID: " << Ids[i] << " | Name: " << Names[i]
                << " | Pass: " << Passwords[i] << " | Balance: " << Amounts[i];
            Painter(15);
        }
        Mover(0, SCREEN_BOTTOM - 1);
        Painter(15);
        cout << "[N]ext [P]revious [B]ack: ";
        cin >> cmd;
        if (cmd == 'N' || cmd == 'n') {
            if (page < pages - 1) page++;
        } else if (cmd == 'P' || cmd == 'p') {
            if (page > 0) page--;
        } else if (cmd == 'B' || cmd == 'b') {
            quit = true;
        }
    }
    Admin_page();
}

void Give_money(int Id){
    Sweeper();
    Entry();
    int addAmt;
    for (int i = 0; i < TotalUsers; i++) {
        if (Ids[i] == Id) {
            Pen("Enter amount to add:", 11);
            cin >> addAmt;
            Amounts[i] += addAmt;
            Pen("Added! New balance: " + to_string(Amounts[i]), 10);
            Sleep(700);
            Admin_page();
            return;
        }
    }
    Pen("User not found!", 12);
    Sleep(700);
    Admin_page();
}

void Give_money_to_all(){
    Sweeper();
    Entry();
    int addAmt;
    Pen("Enter amount to add to all users:", 11);
    cin >> addAmt;
    for (int i = 0; i < TotalUsers; i++) {
        Amounts[i] += addAmt;
    }
    Pen("Amount added to all users!", 10);
    Sleep(900);
    Admin_page();
}

void Delete_record(int Id){
    Sweeper();
    Entry();
    for (int i = 0; i < TotalUsers; i++) {
        if (Ids[i] == Id) {
            for (int j = i; j < TotalUsers - 1; j++) {
                Ids[j] = Ids[j + 1];
                Names[j] = Names[j + 1];
                Passwords[j] = Passwords[j + 1];
                Amounts[j] = Amounts[j + 1];
            }
            TotalUsers--;
            Pen("Account deleted.", 12);
            Sleep(900);
            Admin_page();
            return;
        }
    }
    Pen("User not found.", 12);
    Sleep(900);
    Admin_page();
}

void Delete_all_records(){
    Sweeper();
    Entry();
    delete[] Ids; Ids = nullptr;
    delete[] Names; Names = nullptr;
    delete[] Passwords; Passwords = nullptr;
    delete[] Amounts; Amounts = nullptr;
    TotalUsers = 0;
    Ids = new int[1];
    Names = new string[1];
    Passwords = new string[1];
    Amounts = new int[1];
    Pen("All records deleted.", 12);
    Sleep(900);
    Admin_page();
}

void Back(){
    LoginPage();
}

void IncArrays(){
    int* newIds = new int[TotalUsers + 1];
    string* newNames = new string[TotalUsers + 1];
    string* newPasswords = new string[TotalUsers + 1];
    int* newAmounts = new int[TotalUsers + 1];
    for (int i = 0; i < TotalUsers; i++) {
        newIds[i] = Ids[i];
        newNames[i] = Names[i];
        newPasswords[i] = Passwords[i];
        newAmounts[i] = Amounts[i];
    }
    delete[] Ids;
    delete[] Names;
    delete[] Passwords;
    delete[] Amounts;
    Ids = newIds;
    Names = newNames;
    Passwords = newPasswords;
    Amounts = newAmounts;
}

void LoginOption(){
    Sweeper(10);
    Entry();
    Pen("ID: ",11);
    cin >> Login_temp[0];
    Pen("Password: ",11);
    cin >> Login_temp[1];
    if ((Login_temp[0] == "999999") && (Login_temp[1] == "999999")) {
        Admin_page();
    }
    if ((Login_temp[1].size() > 5 || Login_temp[1].size() < 1)){ 
        Sweeper(10);
        Entry();
        Pen("Invalid",4);
        Sleep(300);
        LoginPage();
        return;
    }
    for (int i = 0; i < TotalUsers; i++)
        if ((Ids[i] == stoi(Login_temp[0])) && (Passwords[i] == Login_temp[1])){
            Login_temp[0] = Names[i];
            Pen("User Found",4);
            UserPage();
            return;
        }
    Pen("Invalid",4);     
    Sleep(300);  
    LoginPage(); 
}

void UserPage(){
    Sleep(400);
    Sweeper();
    Painter(10);
    Mover(0, HEADER_LINES + 1); cout << "                        User";
    Mover(0, HEADER_LINES + 2); cout << "1. View Account                       2. Withdrawl Money";
    Mover(0, HEADER_LINES + 3); cout << "3. Delete Account                     4. Send Money";
    Mover(0, HEADER_LINES + 4); cout << "5. Back                               6. Exit";
    Painter();
    Entry();
    int choice;
    cout << endl << "Choice: ";
    cin >> choice;
    if (choice == 1) {
        View_Account();
    } 
    else if (choice == 2) {
        Withdrawl_Money();
    }
    else if (choice == 3) {
        Delete_Account();
    } 
    else if (choice == 4) {
        Send_Money();
    }
    else if (choice == 5) {
        Back();
    }     
    else if (choice == 6) {
        ExitOption();
    }
    else{
        Pen("Invalid", 12);
        Sleep(400);
        UserPage();
    }
}

void View_Account(){
    Sweeper();
    Entry();
    int i = 0;
    for (; i < TotalUsers; i++) {
        if (Names[i] == Login_temp[0]) {
            Pen("ID: " + to_string(Ids[i]), 10);
            Pen("Name: " + Names[i], 10);
            Pen("Balance: " + to_string(Amounts[i]), 10);
            Sleep(900);
            UserPage();
            return;
        }
    }
    Pen("User not found.", 12);
    Sleep(900);
    UserPage();
}

void Withdrawl_Money(){
    Sweeper();
    Entry();
    int withdraw_amt, i;
    Pen("Enter withdrawal amount:", 11);
    cin >> withdraw_amt;
    for (i = 0; i < TotalUsers; i++) {
        if (Names[i] == Login_temp[0]) {
            if ((withdraw_amt > 0) && (Amounts[i] >= withdraw_amt)) {
                Amounts[i] -= withdraw_amt;
                Pen("Withdrawn! New balance: " + to_string(Amounts[i]), 10);
            } 
            else {
                Pen("Not enough balance or invalid amount.", 12);
            }
            Sleep(900);
            UserPage();
            return;
        }
    }
    Pen("User not found.", 12);
    Sleep(700);
    UserPage();
}

void Delete_Account(){
    Sweeper();
    Entry();
    int i, j;
    for (i = 0; i < TotalUsers; i++) {
        if (Names[i] == Login_temp[0]) {
            for (j = i; j < TotalUsers - 1; j++) {
                Ids[j] = Ids[j + 1];
                Names[j] = Names[j + 1];
                Passwords[j] = Passwords[j + 1];
                Amounts[j] = Amounts[j + 1];
            }
            TotalUsers--;
            Pen("Account deleted.", 12);
            Sleep(900);
            LoginPage();
            return;
        }
    }
    Pen("User not found.", 12);
    Sleep(900);
    UserPage();
}

void Send_Money(){
    Sweeper();
    Entry();
    int rec_id, send_amt, i;
    Pen("Enter receiver ID: ", 11);
    cin >> rec_id;
    Pen("Enter amount to send: ", 11);
    cin >> send_amt;
    int sender_idx = -1, rec_idx = -1;
    for (i = 0; i < TotalUsers; i++) {
        if (Names[i] == Login_temp[0]) sender_idx = i;
        if (Ids[i] == rec_id) rec_idx = i;
    }
    if (sender_idx == -1 || rec_idx == -1) {
        Pen("User not found.", 12);
        Sleep(700);
        UserPage();
        return;
    }
    if (send_amt > 0 && Amounts[sender_idx] >= send_amt) {
        Amounts[sender_idx] -= send_amt;
        Amounts[rec_idx] += send_amt;
        Pen("Sent successfully!", 10);
    } else {
        Pen("Not enough balance or invalid amount.", 12);
    }
    Sleep(800);
    UserPage();
}

void RegisterationOption(){
    Sweeper(10);
    Entry();
    Pen("Name: ", 11);
    cin >> Login_temp[0];
    Pen("Password: ", 11);
    cin >> Login_temp[1];
    if ((Login_temp[0].size() > 7 || Login_temp[0].size() < 1) || (Login_temp[1].size() > 5 || Login_temp[1].size() < 1)){
        Sweeper(10);
        Entry();
        Pen("Invalid", 4);
        Sleep(300);
        LoginPage();
        return;
    }
    IncArrays();
    Ids[TotalUsers] = UniqueID();
    Amounts[TotalUsers] = ((rand() % 50) + 1) * 100;
    Names[TotalUsers] = Login_temp[0];
    Passwords[TotalUsers] = Login_temp[1];
    Pen("Created Successfully Id is:", 4);
    Pen(to_string(Ids[TotalUsers]), 4);
    TotalUsers++;
    Sleep(700);
    LoginPage();
}

int UniqueID(){
    int maxID = 10, i, current;
    for (i = 0; i < TotalUsers; i++) {
        current = Ids[i]; 
        if (current > maxID) 
            maxID = current;
    }
    return maxID + 1;
}

void Bankfilereading(){
    ifstream Seeker("Data.txt");
    if (!Seeker) {
        TotalUsers = 0;
        Ids = new int[0];
        Names = new string[0];
        Passwords = new string[0];
        Amounts = new int[0];
        return;
    }
    int amount, i = 0, tempUser = 0;
    string id, name, password;
    while (Seeker >> id >> name >> password >> amount) { tempUser++; }
    TotalUsers = tempUser;
    Seeker.clear();
    Seeker.seekg(0);
    Ids = new int[TotalUsers];
    Names = new string[TotalUsers];
    Passwords = new string[TotalUsers];
    Amounts = new int[TotalUsers];
    int tid;
    for (i = 0; i < TotalUsers; i++) {
        Seeker >> tid >> name >> password >> amount;
        Ids[i] = tid;
        Names[i] = name;
        Passwords[i] = password;
        Amounts[i] = amount;
    }
    Seeker.close();
}

void Bankfilewriting(){
    int i;
    ofstream Author("temp.txt");
    for(i = 0; i < TotalUsers; i++) Author << Ids[i] << " " << Names[i] << " " << Passwords[i] << " " << Amounts[i] << "\n";
    Author.close();
    remove("Data.txt");
    rename("temp.txt", "Data.txt");
    delete []Ids;
    delete []Names;
    delete []Passwords;
    delete []Amounts;
}

int main() {
    srand(time(0)); 
    system("cls");
    BankName();
    Bankfilereading();
    while(Button){
        LoginPage(); 
    }
    return 0;
}
