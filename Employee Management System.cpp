#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> employeeIds;
vector<string> employeeNames;
vector<string> employeePosition;
vector<double> employeeSalary;

void addEmployee();
void displayEmployees();
void sortEmployees();
void displayEmployee(int employeeId);
void updateEmployee(int employeeId);
void deleteEmployee(int employeeId);
int searchEmployee(int employeeId, int index = 0);  

void display() {
    cout << "==========================================================================\n";
    cout << "||\t\t\tEmployee Management System\t\t\t||\n";
    cout << "==========================================================================\n";
    cout << "||\t\t\t1. Add New Employee's\t\t\t\t||\n";
    cout << "||\t\t\t2. Display All Employees\t\t\t||\n";
    cout << "||\t\t\t3. Search Employee's by ID Number\t\t||\n";
    cout << "||\t\t\t4. Update Employee's Position & Salary\t\t||\n";
    cout << "||\t\t\t5. Remove Employee's\t\t\t\t||\n";
    cout << "||\t\t\t6. Exit\t\t\t\t\t\t||\n";
    cout << "==========================================================================\n";
    cout << "Please Enter your choice (1-6): ";
}

void addEmployee() {
    cout << "Enter Employee's ID Number: ";
    int employeeId;

    while (true) {
        cin >> employeeId;

        if (cin.fail()) {
            cin.clear();  
            cin.ignore(1000, '\n');  
            cout << "Invalid input! Employee's ID must be a number. Please enter again: ";
            continue;
        }   

       bool exists = false;
        for (int existingId : employeeIds) {
        if (existingId == employeeId) {
            exists = true;
            break;
        }
     }

         if (exists) {
        cout << "Error: Employee ID " << employeeId 
             << " already exists. Please enter another ID: ";
     } else {
    
        break;
      }
    }

    employeeIds.push_back(employeeId);

    cin.ignore();
    cout << "Enter Employee's Name: ";
    string name;

    while (true) {
        getline(cin, name);
        bool namevalid = true;
        for (char a : name) {
         if (!( (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || a == ' ' )) {
            namevalid = false;

            break;
        }
      }

      if(namevalid){
        employeeNames.push_back(name);

        break;

      } else{
        cout << "Error: Name must contain only letters and space: ";
      }
    }

    cout << "Enter Employee's Position: ";
    string position;
    getline(cin, position);
    employeePosition.push_back(position);

    cout << "Enter Employee's Salary: ";
    double salary;
    cin >> salary;
    while (salary < 0) {
        cout << "Invalid Salary!!! Please enter a positive number.\n";
        cout << "Enter Employee's Salary: ";
        cin >> salary;
    }
    employeeSalary.push_back(salary);

    sortEmployees();
    cout << "Employee has been added successfully!\n";
}

void sortEmployees() {
    for (int i = 0; i < employeeIds.size() - 1; ++i) {
        for (int j = 0; j < employeeIds.size() - i - 1; ++j) {
            if (employeeIds[j] > employeeIds[j + 1]) {
                swap(employeeIds[j], employeeIds[j + 1]);
                swap(employeeNames[j], employeeNames[j + 1]);
                swap(employeePosition[j], employeePosition[j + 1]);
                swap(employeeSalary[j], employeeSalary[j + 1]);
            }
        }
    }
}

void displayEmployees() {
    if (employeeIds.empty()) {
        cout << "No employees to display.\n";
        return;
    }

    cout << "-------------------------------------------------------------------------\n";
    cout << "|\t" << left << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(20) << "Position" 
         << setw(7) << "Salary"
         << "\t|\n";
    cout << "-------------------------------------------------------------------------\n";

    for (int i = 0; i < employeeIds.size(); ++i) {
        cout << "|\t" << left << setw(10)
             << employeeIds[i]
             << setw(20) << employeeNames[i]
             << setw(20) << employeePosition[i]
             << fixed << setprecision(2) << "₱" << employeeSalary[i] 
            << "\t|" << endl;
    }

    cout << "-------------------------------------------------------------------------\n";
}

void displayEmployee(int employeeId) {
    int index = searchEmployee(employeeId);
    if (index == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
    } else {
        cout << fixed << setprecision(2) 
             << "Employee ID: " 
             << employeeIds[index] 
             << ", Name: " << employeeNames[index] 
             << ", Position: " << employeePosition[index]
             << ", Salary: ₱" << employeeSalary[index] << '\n';
    }
}

int searchEmployee(int employeeId, int index) {
    if (index >= employeeIds.size()) {
        return -1;  // Not found
    }
    if (employeeIds[index] == employeeId) {
        return index;  // Found
    }
    return searchEmployee(employeeId, index + 1);  // Recursive call
}

// Update an employee's salary
void updateEmployee(int employeeId) {
    int index = searchEmployee(employeeId);
    if (index == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
        return;
    }

    cout << "Enter new Position for " << employeeNames[index] << ": ";
    cin.ignore();
    getline(cin, employeePosition[index]);

    double newSalary;
    cout << "Enter new salary for " << employeeNames[index] << ": ";
    cin >> newSalary;

    if (newSalary >= 0) {
        employeeSalary[index] = newSalary;
        cout << fixed << setprecision(2) 
             << "Salary has been updated successfully! The New Salary is: ₱" 
             << employeeSalary[index] << '\n';
    } else {
        cout << "Invalid salary.\n";
    }
}

void deleteEmployee(int employeeId) {
    int index = searchEmployee(employeeId);
    if (index == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
        return;
    }

    // Remove the employee from the vectors
    employeeIds.erase(employeeIds.begin() + index);
    employeeNames.erase(employeeNames.begin() + index);
    employeePosition.erase(employeePosition.begin() + index);
    employeeSalary.erase(employeeSalary.begin() + index);

    cout << "Employee has been deleted successfully!\n";
}

int main() {
    int choice, employeeId;

    while (true) {
        display();
        cin >> choice;
    
        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            cout << "Enter Employee ID to search: ";
            cin >> employeeId;
            displayEmployee(employeeId);
            break;
        case 4:
            cout << "Enter Employee ID to update Position & Salary: ";
            cin >> employeeId;
            updateEmployee(employeeId);
            break;
        case 5:
            cout << "Enter Employee ID to delete: ";
            cin >> employeeId;
            deleteEmployee(employeeId);
            break;
        case 6:
            cout << "Exiting the Employee Management System.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

