#include <bits/stdc++.h>
#include <stdlib.h>
#define MAX_SIZE 1000
using namespace std;
class Book
{
private:
    string title;
    string author;
    bool available;

public:
    Book(const string &t, const string &a) : title(t), author(a), available(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void setAvailability(bool status) { available = status; }

    void saveToFile(ofstream &outFile) const
    {
        outFile << title << ',' << author << ',' << available << endl;
    }
};

class Student
{
private:
    string name;
    int id;

public:
    Student(const string &n, int i) : name(n), id(i) {}

    string getName() const { return name; }
    int getId() const { return id; }
};

class Library
{
private:
    vector<Book> books;
    vector<pair<int, string>> borrowRecords;

public:
    void addBook(const Book &book)
    {
        books.push_back(book);
        ofstream outFile("books.txt", ios::app);
        if (outFile.is_open())
        {
            book.saveToFile(outFile);
            outFile.close();
        }
        else
        {
            cout << "Unable to open file for saving.\n";
        }
    }

    void loadBooksFromFile()
    {
        ifstream inFile("books.txt");
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                size_t pos = line.find(',');
                if (pos != string::npos)
                {
                    string title = line.substr(0, pos);
                    size_t nextPos = line.find(',', pos + 1);
                    if (nextPos != string::npos)
                    {
                        string author = line.substr(pos + 1, nextPos - pos - 1);
                        bool available = stoi(line.substr(nextPos + 1));
                        Book newBook(title, author);
                        newBook.setAvailability(available);
                        books.push_back(newBook);
                    }
                }
            }
            inFile.close();
        }
        else
        {
            cout << "Unable to open file for loading.\n";
        }
    }

    void displayAvailableBooks()
    {
        cout << "Available Books:\n";
        for (const auto &book : books)
        {
            if (book.isAvailable())
            {
                cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << endl;
            }
        }
    }

    void borrowBook(int studentId, const string &title)
    {
        for (auto &book : books)
        {
            if (book.getTitle() == title && book.isAvailable())
            {
                book.setAvailability(false);
                cout << "Book '" << title << "' borrowed by student with ID: " << studentId << endl;
                borrowRecords.push_back(make_pair(studentId, title));
                saveBorrowRecords();
                return;
            }
        }
        cout << "Book '" << title << "' is not available for borrowing." << endl;
    }

    void returnBook(const string &title)
    {
        for (auto &book : books)
        {
            if (book.getTitle() == title)
            {
                book.setAvailability(true);
                cout << "Book '" << title << "' returned." << endl;
                for (auto it = borrowRecords.begin(); it != borrowRecords.end(); ++it)
                {
                    if (it->second == title)
                    {
                        borrowRecords.erase(it);
                        saveBorrowRecords();
                        break;
                    }
                }
                return;
            }
        }
        cout << "Book '" << title << "' not found." << endl;
    }

    vector<pair<int, string>> getBorrowRecords() const
    {
        return borrowRecords;
    }

    void loadBorrowRecordsFromFile()
    {
        ifstream inFile("borrow_records.txt");
        if (inFile.is_open())
        {
            int studentId;
            string bookTitle;
            while (inFile >> studentId >> bookTitle)
            {
                borrowRecords.push_back(make_pair(studentId, bookTitle));
            }
            inFile.close();
        }
        else
        {
            cout << "Unable to open file for loading.\n";
        }
    }

    void saveBorrowRecords()
    {
        ofstream outFile("borrow_records.txt");
        if (outFile.is_open())
        {
            for (const auto &record : borrowRecords)
            {
                outFile << record.first << " " << record.second << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Unable to open file for saving.\n";
        }
    }
};

void heading()
{
    cout << "\t\t\t|--------------------------------------------------------------|" << endl;
    cout << "\t\t\t|```````````````` Library Management Software `````````````````|" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|" << endl;
}
int Faculty_of_Bsc_in_Textile()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();
    heading();
    ;
    int studentId;

    cout << "Enter your student ID: ";
    cin >> studentId;

    Student student("Anonymous", studentId);

    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_Bsc_in_EEE()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();
    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);
    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_BBA()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();
    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);
    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_Bsc_in_CSE()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);
    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_BA_in_English()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);

    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_BA_in_Bangla()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);
    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_B_Pharma()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);

    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
int Faculty_of_LLB()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();
    heading();

    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    cin.ignore();

    Student student("Anonymous", studentId);

    while (true)
    {

        cout << "\n\t\t\t---------------------------Student Menu:-----------------------------\n";
        cout << "\t\t________________________________________________________________________________\n";
        cout << "\t\t--------------------------- 1.View Available Books -----------------------------\n";
        cout << "\t\t--------------------------- 2.Borrow a Book-------------------------------------\n";
        cout << "\t\t--------------------------- 3.Return a Book ------------------------------------\n";
        cout << "\t\t--------------------------- 4.Exit Student Menu --------------------------------\n";
        cout << "Enter your choice: ";

        int studentChoice;
        cin >> studentChoice;
        cin.ignore();

        switch (studentChoice)
        {
        case 1:
            heading();
            system("cls");
            library.displayAvailableBooks();
            break;
        case 2:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to borrow: ";
            getline(cin, title);
            library.borrowBook(student.getId(), title);
            break;
        }
        case 3:
        {
            heading();
            system("cls");
            string title;
            cout << "Enter the title of the book to return: ";
            getline(cin, title);
            library.returnBook(title);
            break;
        }
        case 4:

            cout << "Exiting Student Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (studentChoice == 4)
            break;
    }
}
void userHomePage()
{

    cout << "\t\t\t``````````````````` Book's Categories ``````````````````````````" << endl;
    cout << "\t\t\t----------------------------------------------------------------" << endl
         << endl;
    cout << "\t\t\t 1. Bachelor of Science in Textile Engineering & Management.\n";
    cout << "\t\t\t 2. Electrical and Electronics Engineering.\n";
    cout << "\t\t\t 3. Bachelor of Business Administration.\n";
    cout << "\t\t\t 4. Computer Science & Engineering.\n";
    cout << "\t\t\t 5. English Language & Literature.\n";
    cout << "\t\t\t 6. Bangla Language & Literature.\n";
    cout << "\t\t\t 7. Bachelor of Pharmacy.\n";
    cout << "\t\t\t 8. Bachelor of Laws.\n";
    cout << "\n\t\t Which Faculty Book Do You Need? " << endl;
    cout << "\n\t\t Please Say........... ? :  ";
    int option;
    cin >> option;
    if (option == 1)
    {
        system("cls");
        Faculty_of_Bsc_in_Textile();
    }
    else if (option == 2)
    {
        system("cls");
        Faculty_of_Bsc_in_EEE();
    }
    else if (option == 3)
    {
        system("cls");
        Faculty_of_BBA();
    }
    else if (option == 4)
    {
        system("cls");
        Faculty_of_Bsc_in_CSE();
    }
    else if (option == 5)
    {
        system("cls");
        Faculty_of_BA_in_English();
    }
    else if (option == 6)
    {
        system("cls");
        Faculty_of_BA_in_Bangla();
    }
    else if (option == 7)
    {
        system("cls");
        Faculty_of_B_Pharma();
    }
    else if (option == 8)
    {
        system("cls");
        Faculty_of_LLB();
    }
    else
    {
        return;
    }
}

int registerUser(const string &username, const string &password)
{
    ofstream outFile("users.txt", ios::app);
    if (!outFile.is_open())
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    outFile << username << " " << password << "\n";
    outFile.close();
    return 0;
}

int authenticate(const string &username, const string &password)
{
    ifstream inFile("users.txt");
    if (!inFile.is_open())
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    string storedUser, storedPass;
    while (inFile >> storedUser >> storedPass)
    {
        if (storedUser == username && storedPass == password)
        {
            inFile.close();
            return 1; // Authentication successful
        }
    }

    inFile.close();
    return 0; // Authentication failed
}
int user_signUp_signIn_page(int &count)
{
    int choice;
    string gmail, newPassword;
    heading();

    cout << "Choose an option:\n";
    cout << "\t\t\t\t\t     1.Sign-Up" << endl;
    cout << "\t\t\t\t\t     2.Sign-in" << endl;
    cin >> choice;

    if (choice == 1)
    {
        cout << "\n\t\t\t\t\t  Enter the Email    : ";
        cin >> gmail;
        cout << "\t\t\t\t\t  Enter the Password : ";
        cin >> newPassword;
        if (registerUser(gmail, newPassword) == 0)
        {
            system("cls");
            cout << "Sign-Up successful!, Please Sign-In............,,,\n";

            user_signUp_signIn_page(count);
        }
        else
        {
            system("cls");
            cout << "Registration failed,,, Try Again,,,,,,\n";

            user_signUp_signIn_page(count);
        }
    }
    else if (choice == 2)
    {
        cout << "\n\t\t\t\t\t  Enter the Email    : ";
        cin >> gmail;
        cout << "\t\t\t\t\t  Enter the Password : ";
        cin >> newPassword;
        if (authenticate(gmail, newPassword) == 1)
        {
            system("cls");
            cout << "Login successful!\n";
            heading();
            userHomePage();
        }
        else
        {
            if (count == 3)
            {

                cout << endl
                     << "\t\t\t\t To Much Use Wrong Passward.";
                return 0;
            }
            system("cls");
            cout << "Login failed.\n";
            count++;

            user_signUp_signIn_page(count);
        }
    }
    else
    {
        system("cls");
        cout << "Invalid choice......., Try to right Select.\n";

        user_signUp_signIn_page(count);
    }
}

int admin_Faculty_of_Bsc_in_Textile()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_Bsc_in_EEE()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_BBA()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_Bsc_in_CSE()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_BA_in_English()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_BA_in_Bangla()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {
        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_B_Pharma()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {
        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();

        switch (adminChoice)
        {
        case 1:
        {
            system("cls");

            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}
int admin_Faculty_of_LLB()
{
    Library library;
    library.loadBooksFromFile();
    library.loadBorrowRecordsFromFile();

    while (true)
    {

        cout << "\n\t\t----------------------------------- Admin Menu: --------------------------------------\n";
        cout << "\t\t______________________________________________________________________________________\n";
        cout << "\t\t-------------------------------------1.Add Book --------------------------------------\n";
        cout << "\t\t-------------------------------------2. Remove Book ----------------------------------\n";
        cout << "\t\t-------------------------------------3. Display Books --------------------------------\n";
        cout << "\t\t-------------------------------------4. Borrow Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------5. Return Book Track ----------------------------\n";
        cout << "\t\t-------------------------------------6. Exit Admin Menu ------------------------------\n";
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;
        cin.ignore();
        switch (adminChoice)
        {
        case 1:
        {
            system("cls");
            string title, author;
            cout << "Enter title and author of the book: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            Book newBook(title, author);
            library.addBook(newBook);
            break;
        }
        case 2:
        {
            system("cls");
            string title;
            cout << "Enter title of the book to remove: ";
            getline(cin, title);
            break;
        }
        case 3:
            system("cls");
            library.displayAvailableBooks();
            break;
        case 4:
        {
            system("cls");
            cout << "Borrow Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            cout << "Return Book Track:\n";
            for (const auto &record : library.getBorrowRecords())
            {
                cout << "Student ID: " << record.first << ", Book Title: " << record.second << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Exiting Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

        if (adminChoice == 6)
            break;
    }
}

void AdminHomePage()
{
    cout << "\t\t\t``````````````````` Book's Categories ``````````````````````````" << endl;
    cout << "\t\t\t----------------------------------------------------------------" << endl
         << endl;
    cout << "\t\t\t 1. Bachelor of Science in Textile Engineering & Management.\n";
    cout << "\t\t\t 2. Electrical and Electronics Engineering.\n";
    cout << "\t\t\t 3. Bachelor of Business Administration.\n";
    cout << "\t\t\t 4. Computer Science & Engineering.\n";
    cout << "\t\t\t 5. English Language & Literature.\n";
    cout << "\t\t\t 6. Bangla Language & Literature.\n";
    cout << "\t\t\t 7. Bachelor of Pharmacy.\n";
    cout << "\t\t\t 8. Bachelor of Laws.\n";
    cout << "\n\t\t Which Faculty Book Do You Update? " << endl;
    cout << "\n\t\t Please Select This ........... ? :  ";
    int option;
    cin >> option;
    if (option == 1)
    {
        system("cls");
        admin_Faculty_of_Bsc_in_Textile();
    }
    else if (option == 2)
    {
        system("cls");
        admin_Faculty_of_Bsc_in_EEE();
    }
    else if (option == 3)
    {
        system("cls");
        admin_Faculty_of_BBA();
    }
    else if (option == 4)
    {
        system("cls");
        admin_Faculty_of_Bsc_in_CSE();
    }
    else if (option == 5)
    {
        system("cls");
        admin_Faculty_of_BA_in_English();
    }
    else if (option == 6)
    {
        system("cls");
        admin_Faculty_of_BA_in_Bangla();
    }
    else if (option == 7)
    {
        system("cls");
        admin_Faculty_of_B_Pharma();
    }
    else if (option == 8)
    {
        system("cls");
        admin_Faculty_of_LLB();
    }
    else
    {
        return;
    }
}
int admin_signUp_singIn_page(int &count)
{
    int choice;
    string gmail, newPassword;
    heading();

    cout << "Choose an option:\n";
    cout << "\t\t\t\t\t     1.Sign-Up" << endl;
    cout << "\t\t\t\t\t     2.Sign-in" << endl;
    cin >> choice;

    if (choice == 1)
    {
        cout << "\n\t\t\t\t\t  Enter the Email    : ";
        cin >> gmail;
        cout << "\t\t\t\t\t  Enter the Password : ";
        cin >> newPassword;
        if (registerUser(gmail, newPassword) == 0)
        {
            system("cls");
            cout << "Sign-Up successful!, Please Sign-In............,,,\n";

            admin_signUp_singIn_page(count);
        }
        else
        {
            system("cls");
            cout << "Registration failed,,, Try Again,,,,,,\n";

            admin_signUp_singIn_page(count);
        }
    }
    else if (choice == 2)
    {
        cout << "\n\t\t\t\t\t  Enter the Email    : ";
        cin >> gmail;
        cout << "\t\t\t\t\t  Enter the Password : ";
        cin >> newPassword;
        if (authenticate(gmail, newPassword) == 1)
        {
            system("cls");
            cout << "Login successful!\n";
            heading();
            AdminHomePage();
        }
        else
        {
            if (count == 3)
            {

                cout << endl
                     << "\t\t\t\t To Much Use Wrong Passward.";
                return 0;
            }
            system("cls");
            cout << "Login failed.\n";
            count++;

            admin_signUp_singIn_page(count);
        }
    }
    else
    {
        system("cls");
        cout << "Invalid choice......., Try to right Select.\n";

        admin_signUp_singIn_page(count);
    }
}
int main()
{
    heading();
    int d = 1;
    int *count = &d;
    cout << "\t\t\t\t\t  ------------------ \n";
    cout << "\t\t\t\t\t | User Authication |" << endl;
    cout << "\t\t\t\t\t   ------------------ \n";
    cout << "\t\t\t\t\t  ------------------ \n";
    cout << "\t\t\t\t\t | Admin Authication |" << endl;
    cout << "\t\t\t\t\t   ------------------ \n";
    cout << "\t\t\t For User Press 1" << endl;
    cout << "\t\t\t For Admin Press 2" << endl;
    int op;
    cin >> op;
    if (op == 1)
    {
        system("cls");
        user_signUp_signIn_page(*count);

        fflush(stdin);
        getchar();
    }
    else if (op == 2)
    {
        system("cls");
        admin_signUp_singIn_page(*count);

        fflush(stdin);
        getchar();
    }
    else
    {
        system("cls");
        cout << "/t/t/t Wrong Press, Please Press Enter & try Again...........," << endl;
        fflush(stdin);
        getchar();
        // main();
    }
    return 0;
}
