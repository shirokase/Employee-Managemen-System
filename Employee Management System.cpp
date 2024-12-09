#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

vector<int> employeeIds;
vector<string> employeeNames;
vector<string> employeePosition;
vector<double> employeeSalary;

void addEmployee();
void sortEmployees();
void displayEmployees();
void displayEmployee(int employeeId);
void updateEmployee(int employeeId);
void deleteEmployee(int employeeId);
int searchEmployee(int employeeId, int find = 0);  

void display() {
    cout << "==========================================================================\n";
    cout << "||\t\t\tApple's Employee Management System\t\t\t||\n";
    cout << "==========================================================================\n";
    cout << "||\t\t\t1. Add New Employee\t\t\t\t||\n";
    cout << "||\t\t\t2. Display All Employee's Information\t\t||\n";
    cout << "||\t\t\t3. Search Employee Information by ID Number\t||\n";
    cout << "||\t\t\t4. Update Employee Position & Salary\t\t||\n";
    cout << "||\t\t\t5. Delete Employee\t\t\t\t||\n";
    cout << "||\t\t\t6. Save & Exit as a Text File\t\t\t||\n";
    cout << "==========================================================================\n";
    cout << "Please Enter your choice (1-6): ";

}

void addEmployee() {
    cout << "Enter Employee ID Number: ";
    int employeeId;
    while (true) {
        cin >> employeeId;

        if (cin.fail()) {
            cin.clear();  
            cin.ignore(1000, '\n');  
            cout << "Invalid input! Employee ID must be a number. Please enter again: ";
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
    cout << "Enter Employee Name: ";
    string name;

    while (true) {
        getline(cin, name);
        bool namevalid = true;
        for (char a : name) {
         if (!( (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || a == ' ' || a == '.' || a == ',')) {
            namevalid = false;

            break;
        }
      }

      if(namevalid){
        employeeNames.push_back(name);

        break;

      } else{
        cout << "Error: Name must contain only letters, space, dot, and comma: ";
      }
    }

    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|\t\t\t\t\tApple's Employee Positions\t\t\t\t|\n";
    cout << "|-------------------------------------------------------------------------------------------------------|\n";
    cout << "|\t1. Intern\t\t\t6. Department Head\t\t11. Human resources manager\t|\n";
    cout << "|\t2. Junior Staff\t\t\t7. Executive Assistant\t\t12. Sales Representative\t|\n";
    cout << "|\t3. Senior Staff\t\t\t8. Sales Manager\t\t13. Business Analyst\t\t|\n";
    cout << "|\t4. Team Leader\t\t\t9. Product Manager\t\t14. Assistant Manager\t\t|\n";
    cout << "|\t5. Department Specialist\t10. Marketing Manager\t\t15. Data Analyst\t\t|\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << " Enter the choice of Employee Position (1-15): ";
    
    int selectPosition;
    string position;

    while (true) {
        cin >> selectPosition;
            if (cin.fail() || selectPosition < 1 || selectPosition > 15) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid choice! Please select a Valid Position (1-15): ";
            } else {

                vector<string> positions = {
                    "Intern", "Junior Staff", "Senior Staff", "Team Leader", "Department Specialist",
                    "Department Head", "Executive Assistant", "Sales Manager", "Product Manager",
                    "Marketing Manager", "Human Resources Manager", "Sales Representative",
                    "Business Analyst", "Assistant Manager", "Data Analyst"
                };
                 position = positions[selectPosition - 1];
                break;

            }
        
    }

    cout << "-----------------------------------------------------------\n";
    cout << " The Position of '" << position << "' has been added.\n";
    cout << "-----------------------------------------------------------\n";
    employeePosition.push_back(position);
   

    cout << "Enter Employee Salary: ";
    double salary;
    while (true) {
    cin >> salary;
    if (cin.fail() || salary < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid salary! Please enter a valid positive number: ";
    } else {
        break;
    }
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
    cout << "|                      Apple's Employees Information                    |\n";
    cout << "|-----------------------------------------------------------------------|\n";
    cout << "| " << left << setw(5) << "No"  
         << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(20) << "Position" 
         << setw(12) << "Salary"
         << "\t|\n";
    cout << "|-----------------------------------------------------------------------|\n";

    for (size_t i = 0; i < employeeIds.size(); ++i) {
        cout << "| " << left << setw(5) << i + 1   
             << setw(10) << employeeIds[i]
             << setw(20) << employeeNames[i]
             << setw(20) << employeePosition[i]
             << "₱" << fixed << setprecision(2) << setw(10) << employeeSalary[i]
             << "\t|\n";
    }

    cout << "-------------------------------------------------------------------------\n";
}

void displayEmployee(int employeeId) {
    int find = searchEmployee(employeeId);
    if (find == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
    } else {
         cout << "-------------------------------------------------------------------------\n";
         cout << "|\t\t\tApple's Employee's Information\t\t\t|\n";
         cout << "|-----------------------------------------------------------------------|\n";
         cout << "|\t" << left << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(20) << "Position" 
         << setw(14) << "Salary"
         << "|\n";
         cout << "|-----------------------------------------------------------------------|\n";


         cout << "|\t" << left << setw(10)
             << employeeIds[find] 
             << setw(20) << employeeNames[find] 
             << setw(20)  << employeePosition[find]
             << fixed << setprecision(2)  << "₱" << employeeSalary[find]
             << "\t|" << endl;
            
    }
    cout << "-------------------------------------------------------------------------\n";

}

int searchEmployee(int employeeId, int find) {
    if (find >= employeeIds.size()) {
        return -1; 
    }
    if (employeeIds[find] == employeeId) {
        return find;  
    }
    return searchEmployee(employeeId, find + 1); 
}

void updateEmployee(int employeeId) {
    int find = searchEmployee(employeeId);
    if (find == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
        return;
    }

    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|\t\t\t\t\tEmployee's Positions\t\t\t\t\t\t|\n";
    cout << "|-------------------------------------------------------------------------------------------------------|\n";
    cout << "|\t1. Intern\t\t\t6. Department Head\t\t11. Human Resources Manager\t|\n";
    cout << "|\t2. Junior Staff\t\t\t7. Executive Assistant\t\t12. Sales Representative\t|\n";
    cout << "|\t3. Senior Staff\t\t\t8. Sales Manager\t\t13. Business Analyst\t\t|\n";
    cout << "|\t4. Team Leader\t\t\t9. Product Manager\t\t14. Assistant Manager\t\t|\n";
    cout << "|\t5. Department Specialist\t10. Marketing Manager\t\t15. Data Analyst\t\t|\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "Enter the choice of Employee New Position (1-15): ";

        int selectPosition;
        string position;
        while (true) {
            cin >> selectPosition;
            if (cin.fail() || selectPosition < 1 || selectPosition > 15) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid choice! Please select a Valid Position (1-15): ";
            } else {

                vector<string> position = {
                    "Intern", "Junior Staff", "Senior Staff", "Team Leader", "Department Specialist",
                    "Department Head", "Executive Assistant", "Sales Manager", "Product Manager",
                    "Marketing Manager", "Human Resources Manager", "Sales Representative",
                    "Business Analyst", "Assistant Manager", "Data Analyst"
                };

                employeePosition[find] = position[selectPosition - 1];
                cout << "Position has been updated to: " << employeePosition[find] << endl;
                break;  
         }
     }

    double newSalary;
    cout << "Enter new salary for " << employeeNames[find] << ": ";
    cin >> newSalary;

    if (newSalary >= 0) {
        employeeSalary[find] = newSalary;
        cout << fixed << setprecision(2) 
             << "Salary has been updated successfully! The New Salary is: ₱" 
             << employeeSalary[find] << '\n';
    } else {
        cout << "Invalid salary.\n";
    }
}

void deleteEmployee(int employeeId) {
    cout << "-------------------------------------------------\n";
    int find = searchEmployee(employeeId);
    if (find == -1) {
        cout << "Employee with ID " << employeeId << " not found.\n";
        return;
    }

    employeeIds.erase(employeeIds.begin() + find);
    employeeNames.erase(employeeNames.begin() + find);
    employeePosition.erase(employeePosition.begin() + find);
    employeeSalary.erase(employeeSalary.begin() + find);

    cout << "| Employee has been deleted successfully!\t|\n";
    cout << "-------------------------------------------------\n";
}

void saveasTXTfile() {
    ofstream file("EmployeesRecords.txt"); 
    if (file.is_open()) {
        file << "-------------------------------------------------------------------------\n";
        file << left << setw(5) << "No"
                << setw(10) << "Id" 
                << setw(20) << "Name" 
                << setw(25) << "Position" 
                << "Salary\n";
        file << "-------------------------------------------------------------------------\n";

        for (int i = 0; i < employeeIds.size(); ++i) {
            file<< left << setw(5) << i + 1
                    << setw(10) << employeeIds[i]
                    << setw(20) << employeeNames[i]
                    << setw(25) << employeePosition[i]
                    << "₱" << fixed << setprecision(2) << employeeSalary[i] << "\n";
        }
        file.close();
        cout << "Employees records have been saved successfully to 'AppleRecords.txt'.\n";
    } else {
        cout << "Error: Unable to open file for saving employee records.\n";
    }
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
            cout << "Saving as a File & Exiting the Apple's Employee Management System Program.\n";
            saveasTXTfile();
            return 0;
        default:
            cout << "Invalid choice. Please try to choose from the option.\n";
        }
    }
    return 0;
}




