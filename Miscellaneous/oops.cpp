#include<bits/stdc++.h>
 
using namespace std;

class Employee {
    private:  // Access specifier
        int age;
        string designation;
        int salary;
    public:  // By default, all members of a class would be private
        string name;
        Employee(string name, int age, string designation, int salary) {
            this->name = name;
            this->age = age;
            this->designation = designation;
            this->salary = salary;
        }

        int increment(int salary);

        // Declaring a friend function enables it to access private members of a class, even though it is not a member of that class
        friend int totalSalary(Employee emp[], int n); // Friend function

        void print() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Designation: " << designation << endl;
            cout << "Salary: " << salary << endl;
        }
};

// Friend function
int totalSalary(Employee emp[], int n) {
    int total = 0;
    for(int i=0; i<n; i++) {
        total += emp[i].salary; // Accessing private member
    }
    return total;
}

// Objects can be created along with class defination
// class Employee {
//     ...
// } emp1, emp2;

// Declaring a function outside class
int Employee::increment(int salary) {
    this->salary += salary;
    return this->salary;
}

// Friend class
class Complex {
    private:
        int real;
        int imaginary;
    public:
        Complex(int real, int imaginary) {
            this->real = real;
            this->imaginary = imaginary;
        }

        // Operator overloading
        Complex operator+(Complex c) {
            Complex temp(0, 0);
            temp.real = this->real + c.real;
            temp.imaginary = this->imaginary + c.imaginary;
            return temp;
        }

        void print() {
            cout << real << " + " << imaginary << "i" << endl;
        }

        // Individually friending functions of the Calculator class
        // friend int Calculator::addReal(Complex c1, Complex c2);
        // friend int Calculator::addImaginary(Complex c1, Complex c2);

        // Declaring a friend class enables its members to access private members of a class
        friend class Calculator;
};

class Calculator {
    public:
        int addReal(Complex c1, Complex c2) {
            return c1.real + c2.real;
        }

        int addImaginary(Complex c1, Complex c2) {
            return c1.imaginary + c2.imaginary;
        }
};

// Constructor overloading in C++ works even with same number of arguments but different types
class BankDeposit {
    private:
        int principal;
        int years;
        float interestRate;
        float returnValue;
    public:
        BankDeposit() {} // Default constructor is compulsory in C++ unlike Java

        BankDeposit(int p, int y, float r) {
            principal = p;
            years = y;
            interestRate = r;
            returnValue = principal;
        } // r can be 0.04 or 0.04f

        BankDeposit(int p, int y, int r) {
            principal = p;
            years = y;
            interestRate = float(r)/100;
            returnValue = principal;
        } // r can be 4 or 4f

        // When a copy constructor is not defined, the compiler creates a default copy constructor which performs a shallow copy
        BankDeposit(BankDeposit &bd) {
            principal = bd.principal;
            years = bd.years;
            interestRate = bd.interestRate;
            returnValue = bd.returnValue;
        } // Copy constructor (Deep copy)

        ~BankDeposit() {} // Destructor is compulsory in C++ unlike Java

        void caluculateReturn() {
            for(int i=0; i<years; i++) {
                returnValue = returnValue * (1 + interestRate);
            }
        }

        void show() {
            cout << "Principal amount: " << principal << endl;
            cout << "Return value after " << years << " years: " << returnValue << endl;
        }
};

int main(){
    {
        Employee emp1("John", 25, "Software Engineer", 50000);
        // emp1.salary = 100000; // Error: salary is private
        emp1.print();
        cout << "Salary after increment: " << emp1.increment(10000) << endl;
        emp1.print();
    } // exiting a block - anything created inside a block gets destoryed when the block exits


    {
        Complex c1(1, 2), c2(3, 4);
        Complex c3 = Complex(5, 6); // Explicit call to constructor
        c3.print();
    
        Calculator calc;
        cout << "Real part: " << calc.addReal(c1, c2) << endl;
        cout << "Imaginary part: " << calc.addImaginary(c1, c2) << endl;

        Complex c4 = c1 + c2 + c3; // Operator overloading
        c4.print();
    }

    {
        BankDeposit bd1, bd2, bd3;
        int p, y;
        float r;
        int R;
        cout << "Enter principal amount, the number of years and rate of interest: ";
        cin >> p >> y >> r;
        bd1 = BankDeposit(p, y, r);
        bd1.caluculateReturn();
        bd1.show();
        cout << "Enter principal amount, the number of years and rate of interest: ";
        cin >> p >> y >> R;
        bd2 = BankDeposit(p, y, R);
        bd2.caluculateReturn();
        bd2.show();
        bd3 = bd1; // Copy constructor is not called
        BankDeposit bd4 = bd1; // Copy constructor is called
        bd4.show();
        BankDeposit bd5(bd2); // Copy constructor is called
        bd5.show();
    } // Destructor is called when an object goes out of scope

    return 0;
}
