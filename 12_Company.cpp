#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

const char *fileName = "Employee.txt";

class Employee
{
private:
    int EmpID;
    char EmpName[50], Post[50], Department[10];
    float Salary;

public:
    void ReadData();
    int GetID();
    void DisplayRecord();
    char *GetDepartment();
};

void Employee::ReadData()
{
    cout << "\nEmployee ID: ";
    cin >> EmpID;
    cout << "Employee Name: ";
    cin >> EmpName;
    cout << "Employee's Post: ";
    cin >> Post;
    cout << "Employee's Department: ";
    cin >> Department;
    cout << "Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord()
{
    cout << "\n-----------------------------------------------";
    cout << "\n"
         << setw(5) << EmpID << setw(15) << EmpName << setw(15) << Post << setw(15) << Department << setw(10) << Salary;
}

int Employee::GetID()
{
    return EmpID;
}

char *Employee::GetDepartment()
{
    return Department;
}

int main()
{
    Employee emp, e;
    char option, ch, Dept[50];
    int ID, isFound;

    fstream file;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file)
    {
        // If file does not exist, create it
        file.open(fileName, ios::out | ios::binary);
        file.close();
        file.open(fileName, ios::in | ios::out | ios::binary);
    }

    do
    {
        cout << "\n********* Menu *********";
        cout << "\n1 => Add a new record";
        cout << "\n2 => Search record from employee id";
        cout << "\n3 => List Employees of a particular department";
        cout << "\n4 => Display all employees";
        cout << "\n5 => Update record of an employee";
        cout << "\n6 => Delete record of particular employee";
        cout << "\n7 => Exit from the program";
        cout << "\nEnter your option: ";
        cin >> option;

        switch (option)
        {
        case '1':
            emp.ReadData();
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            while (file.read((char *)&e, sizeof(e)))
            {
                if (e.GetID() == emp.GetID())
                {
                    cout << "This ID already exists. Try another ID.\n";
                    isFound = 1;
                    break;
                }
            }
            if (!isFound)
            {
                file.clear();
                file.seekp(0, ios::end);
                file.write((char *)&emp, sizeof(emp));
                cout << "\nNew record has been added successfully.\n";
            }
            break;

        case '2':
            cout << "\nEnter ID of employee to be searched: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            while (file.read((char *)&e, sizeof(e)))
            {
                if (e.GetID() == ID)
                {
                    cout << "\nRecord found:\n";
                    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(10) << "Salary";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound)
                cout << "\nData not found for employee ID #" << ID;
            break;

        case '3':
            cout << "\nEnter department name to list employees: ";
            cin >> Dept;
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(10) << "Salary";
            while (file.read((char *)&e, sizeof(e)))
            {
                if (strcmp(e.GetDepartment(), Dept) == 0)
                {
                    e.DisplayRecord();
                    isFound = 1;
                }
            }
            if (!isFound)
                cout << "\nNo data found for department: " << Dept;
            break;

        case '4':
            cout << "\nEmployee Records:\n";
            file.clear();
            file.seekg(0, ios::beg);
            cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(10) << "Salary";
            while (file.read((char *)&e, sizeof(e)))
            {
                e.DisplayRecord();
            }
            break;

        case '5':
            cout << "\nEnter employee ID to update: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            int pos;
            while (file.read((char *)&e, sizeof(e)))
            {
                if (e.GetID() == ID)
                {
                    pos = static_cast<int>(file.tellg()) - static_cast<int>(sizeof(e));

                    isFound = 1;
                    cout << "\nOld record:";
                    e.DisplayRecord();
                    break;
                }
            }
            if (!isFound)
            {
                cout << "\nData not found for employee ID #" << ID;
                break;
            }
            emp.ReadData();
            file.clear();
            file.seekp(pos);
            file.write((char *)&emp, sizeof(emp));
            cout << "\nRecord updated successfully.";
            break;

        case '6':
        {
            cout << "\nEnter employee ID to delete: ";
            cin >> ID;
            fstream temp("temp.txt", ios::out | ios::binary);
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            while (file.read((char *)&e, sizeof(e)))
            {
                if (e.GetID() != ID)
                    temp.write((char *)&e, sizeof(e));
                else
                    isFound = 1;
            }
            file.close();
            temp.close();
            if (!isFound)
            {
                cout << "\nNo record found for ID #" << ID;
            }
            else
            {
                remove(fileName);
                rename("temp.txt", fileName);
                file.open(fileName, ios::in | ios::out | ios::binary);
                cout << "\nRecord deleted successfully.";
            }
            break;
        }

        case '7':
            cout << "Exiting...";
            file.close();
            exit(0);
            break;

        default:
            cout << "Invalid option. Try again.";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ch;

    } while (ch != 'n');

    file.close();
    return 0;
}

