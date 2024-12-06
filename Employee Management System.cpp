#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_EMPLOYEE = 50;

int employeeIds[MAX_EMPLOYEE];
string employeeNames[MAX_EMPLOYEE];
string employeePosition[MAX_EMPLOYEE];
double employeeSalary[MAX_EMPLOYEE];
int employeeCount = 0;

void addEmployee(); 
void displayEmployees();
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
    cout << "||\t\t\t4. Modify Employee's Position & Salary\t\t||\n";
    cout << "||\t\t\t5. Remove Employee's\t\t\t\t||\n";
    cout << "||\t\t\t6. Exit\t\t\t\t\t\t||\n";
    cout << "==========================================================================\n";
    cout << "Please Enter your choice (1-6): ";
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEE) {
        cout << "Error: Maximum employee's limit has been REACHED!.\n";
        return;
    }{

    cout << "Enter Employee's ID Number: ";
    cin >> employeeIds[employeeCount];
    while (employeeIds[employeeCount] < 0 || employeeIds[employeeCount] > 99) {
        cout << "Invalid Input!!!\nEmployee's ID must be a 2-digit number only\n";
        cout << "Enter Employee's ID Number: ";
        cin >> employeeIds[employeeCount];
    }
    for (int i = 0; i < employeeCount; ++i) {
        if (employeeIds[i] == employeeIds[employeeCount]) {
            cout << "Error the Employee ID " << employeeIds[employeeCount] << " is already exists. Please enter a unique ID.\n";
            return; 
        }
    }
    
    cin.ignore();

    cout << "Enter Employee's Name: ";
    getline(cin, employeeNames[employeeCount]);

    cout << "Enter Employee's Position: ";
    getline(cin,employeePosition[employeeCount]);

    cout << "Enter Employee's Salary: ";
    cin >> employeeSalary[employeeCount];
    while (employeeSalary[employeeCount] < 0) {
        cin.ignore();
        cout << "Invalid Salary!!!\nPlease Enter a Positive Number\n";
        cout << "Enter Employee's Salary: ";
        cin >> employeeSalary[employeeCount];
    }

    employeeCount++;
    cout << "Employee's has been added successfully!\n";
    }
}

void displayEmployees() {
    if (employeeCount == 0) {
        cout << "No employees to display.\n";
        return;
    }

    for (int i = 0; i < employeeCount; ++i) {
        cout << fixed << setprecision(2) << "Employee's ID: " << employeeIds[i] << ", Name: " << employeeNames[i] << ", Position: " << employeePosition[i] << ", Salary: ₱" << employeeSalary[i] << '\n';
            
    }
}

void displayEmployee(int employeeId) {
    int index = searchEmployee(employeeId);
    if (index == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
    } else {
        cout << fixed << setprecision(2) << "Employee ID: " << employeeIds[index] << ", Name: " << employeeNames[index] << ", Position: " << employeePosition[index] << ", Salary: ₱" << employeeSalary[index] << '\n';
                
    }
}

int searchEmployee(int employeeId, int index) {
    if (index >= employeeCount) {
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
        cout << fixed << setprecision(2) << "Salary has been updated successfully! The New Salary is: ₱" << employeeSalary[index] << '\n';
    } else {
        cout << "Invalid salary.\n";
    }
}

// Delete an employee
void deleteEmployee(int employeeId) {
    int index = searchEmployee(employeeId);
    if (index == -1) {
        cout << "Employee with ID " << employeeIds << " not found.\n";
        return;
    }

    // Shift all employees after the deleted one
    for (int i = index; i < employeeCount - 1; ++i) {
        employeeIds[i] = employeeIds[i + 1];
        employeeNames[i] = employeeNames[i + 1];
        employeePosition[i] = employeePosition[i + 1];
        employeeSalary[i] = employeeSalary[i + 1];
    }

    employeeCount--;
    cout << "Employee has been deleted successfully!\n";
}

using namespace std;

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
