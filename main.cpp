#include <iostream>
#include <conio.h> // for clearing the screen "cls"
#include <fstream> // For handling file
#include <cstdio> // For fflushing buffer

using namespace std;

class contact
{
private:
    char fName[50]; // first name
    char lName[50]; // last name
    char address[50]; // address of the person
    char email[50]; // mail id
    long long phNo; // phone number

public:
    // Taking input from user
    void createContact()
    {
        cout << "Enter First Name: ";
        cin >> fName;
        cout << "Enter Last Name: ";
        cin >> lName;
        cout << "Enter Phone Number: ";
        cin >> phNo; fflush(stdin);
        cout << "Enter Address: ";
        cin.getline(address, 50); 
        cout << "Enter Mail ID: ";
        cin >> email;
    }

    // Displaying contact on the screen
    void showContact()
    {
        cout << "Name: \t\t" << fName << " " << lName << endl;
        cout << "Phone Number: \t" << phNo << endl;
        cout << "Address: \t" << address << endl;
        cout << "Mail ID: \t" << email << endl;
    }

    // Used to write the data on file
    void writeOnFile()
    {
        char ch;
        ofstream f1;                                // Used to write in a file (Output to File Stream)
        f1.open("CMS.dat", ios::binary | ios::app); // Opened file in binary mode because we are using .dat file and app mode to append the data without removing the existing data

        createContact();
        f1.write(reinterpret_cast<char *>(this), sizeof(*this));

        cout << "Contact has been created Successfully..." << endl;
        f1.close();

        /* reinterpret_cast is used to convert a pointer of some data type into a pointer of another data type. It is very dangerous
           reinterpret_cast<char*>(this), sizeof(*this) lets divide it into two parts

           1. reinterpret_cast<char*>(this)
              reinterpret_cast<A>(B) means whatever B is, treat it as A
              char* is a pointer to char
              char is basically just a byte
              this is a pointer to a current class, of whatever type

           2. sizeof(*this)
              sizeof(A) gets the number of bytes it takes to hold whatever type A is
              *this gets the value of the pointer
              this(again) is a pointer to the current class of whatever type is.
        */
    }

    // Used to read the data from file
    void readFromFile()
    {
        ifstream f2;                     // Used to read from the file (Input from the file stream)
        f2.open("CMS.dat", ios::binary); // Opened the file in binary mode

        cout << endl
             << "================================================" << endl;
        cout << "Contacts" << endl;
        cout << endl
             << "================================================" << endl;

        while (!f2.eof()) // Till the end of file
        {
            if (f2.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                cout<<endl;
                showContact();
                cout << endl
                     << "================================================" << endl;
            }
        }

        f2.close();
    }

    // Search contact from the file
    void searchFromFile()
    {
        ifstream f3;     // Used to read from the file (Input from the file stream)
        long long phone; // To take input from user to search that phone number in the data list
        f3.open("CMS.dat", ios::binary);
        cout << "Enter the phone number: ";
        cin >> phone;

        while (!f3.eof())
        {
            if (f3.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone == phNo)
                {
                    showContact();
                    f3.close(); // CHECK
                    return;
                }
            }
        }

        f3.close();
        cout << "No Contact record Found" << endl;
    }

    // Delete contact from the file
    void deleteFromFile()
    {
        long long phone;
        int flag = 0;

        ofstream f4; // Used to write in file
        ifstream f5; // Used to read from file

        cout << "Enter the Phone Number you want to delete: ";
        cin >> phone;

        f5.open("CMS.dat", ios::binary);               // Used to read the content from the file
        f4.open("temp.dat", ios::binary | ios::trunc); // Used to write the content on the file and trunc mode is used to clear any unwanted data from the file present already

        while (!f5.eof())
        {
            if (f5.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone == phNo)
                {
                    flag = 1;
                    continue;
                }
                else
                {
                    f4.write(reinterpret_cast<char *>(this), sizeof(*this));
                }
            }
        }
        if (flag == 0)
            cout << "No Contact Found..." << endl;
        else
            cout << "Contact Deleted Successfully..." << endl;

        f4.close();
        f5.close();
        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");
    }

    // Edit contact in the file
    void editContact()
    {
        long long phone;
        fstream f6;

        cout << "Edit Contact";
        cout << endl
             << "================================================" << endl;
        cout << "Enter the Phone Number to Edit: ";
        cin >> phone;

        f6.open("CMS.dat", ios::binary | ios::out | ios::in); // Used for both reading and writing
        while (!f6.eof())
        {
            if (f6.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone == phNo)
                {
                    cout << "Enter new record" << endl;
                    createContact();
                    int pos = -1 * sizeof(*this); // To go back 1 position because we want to edit the contact
                    f6.seekp(pos, ios::cur);      // seekp is used to set the pointer position at the required one. ios::cur is used for from the current pointer location
                    f6.write(reinterpret_cast<char *>(this), sizeof(*this));
                    cout << endl << endl << "Contact Updated Successfully...";
                    f6.close(); // CHECK
                    return;
                    /* Difference between seekp and seekg => seekg moves the file input pointer(position of reading frm file) while seekp moves file output pointer( position f writing to file). */
                }
            }
        }
        cout << "No Contact Found..." << endl;
        f6.close();
    }
};

int main()
{
    system("cls");
    system("Color 3F"); // "Color XY", X - backgroung color, Y - text color

    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\t\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
    getch();

    while (1)
    {
        contact c1;
        int choice;

        system("cls");
        system("Color 03");

        cout <<endl << "CONTACT MANAGEMENT SYSTEM";
        cout << endl << endl <<"MAIN MENU";
        cout << endl << "=======================" << endl;
        cout << endl <<"[1] Add a new Contact";
        cout << endl <<"[2] List all Contacts";
        cout << endl <<"[3] Search for contact";
        cout << endl <<"[4] Delete a Contact";
        cout << endl <<"[5] Edit a Contact";
        cout << endl <<"[0] Exit"<<endl;
        cout << endl <<"=======================" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            c1.writeOnFile();
            break;

        case 2:
            system("cls");
            c1.readFromFile();
            break;

        case 3:
            system("cls");
            c1.searchFromFile();
            break;

        case 4:
            system("cls");
            c1.deleteFromFile();
            break;

        case 5:
            system("cls");
            c1.editContact();
            break;

        case 0:
            system("cls");
            cout << endl << endl << endl << endl <<"\t\t\tThank you for using CMS." << endl << endl;
            exit(0);
            break;

        default:
            continue;
        }

        int opt;
        cout << endl << endl <<"::Enter the Choice::"<<endl<<"[1] Main Menu"<<endl<<"[0] Exit"<<endl<<"Choice: ";
        cin >> opt;

        switch (opt)
        {
        case 0:
            system("cls");
            cout<<"Thank you for using CMS.";
            exit(0);
            break;

        default:
            system("cls");
            continue;
        }
    }

    return 0;
}