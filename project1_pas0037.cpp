/*
File Name: project1_pas0037.cpp
Author: Patrick Spafford (pas0037)
How to compile: use the command "g++ project1_pas0037.cpp"
				I have the out file saved as project1_pas0037_out.out
Sources Used:
- C++ Programming 5th Edition by McGrath --- helped me with basic syntax
- Stack Overflow:
	"How can I easily format my data table in C++?" --- helped me format the output as a table.
	"C++ Walkthrough cout.setf(ios::fixed); and cout.precision();" --- helped me format the doubles properly.
	"www.cplusplus.com, <iomanip> and setprecision" --- was supplementary in formatting the output values.
*/
#include <iostream>
#include <iomanip>
using namespace std;
using std::ios_base;
class Loan
{
public:
	const static int width = 10;
	const static int month_width = 7;
	const static int precision = 2;
	const static char separator = ' ';
	int month_counter;
	double amount;
	double monthly_payment;
	double monthly_interest;
	double interest_rate;
	double interest_sum;
	double principal;
	Loan() {
		month_counter = 0;
		amount = 0;
		monthly_payment = 0;
		monthly_interest = 0;
		interest_rate = 0;
		interest_sum = 0;
		principal = 0;
		bool valid_loan_input = false;
		bool valid_interest_input = false;
		bool valid_payment_input = false;
		do {
			cout << "Loan Amount: "; // Retrieve loan amount
			cin >> amount;
			if (amount > 0) {
				valid_loan_input = true;
			}
			else {
				invalid_parameters_message();
			}
		} while (!valid_loan_input);
		do {
			cout << "Interest Rate (% per year): "; // Retrieve interest rate
			cin >> interest_rate;
			if (interest_rate > 0) {
				valid_interest_input = true;
			}
			else {
				invalid_parameters_message();
			}
		} while (!valid_interest_input);
		do {
			cout << "Monthly Payments: "; // Retrieve the monthly payment
			cin >> monthly_payment;
			cout << endl;
			if (monthly_payment > 0) {
				valid_payment_input = true;
			}
			else {
				invalid_parameters_message();
			}
		} while (!valid_payment_input);
	}
	double get_monthly_interest() {
		return monthly_interest;
	}
	void set_monthly_interest() {
		monthly_interest = (interest_rate / 12) * amount / 100;
		return;
	}
	void set_monthly_interest(double input_amount) {
		monthly_interest = (interest_rate / 12) * input_amount / 100;
		return;
	}
	double handle_principal() {
		principal = monthly_payment - monthly_interest;
		interest_sum += monthly_interest;
		return principal;
	}
	void subtract_principal() {
		amount = amount - principal;
		return;
	}
	static bool is_valid_loan(double input_monthly_interest, double input_monthly_payment) {
		return (input_monthly_payment > input_monthly_interest);
	}
	void print_record() {
		cout << left << setw(month_width) << fixed << showpoint << setprecision(precision) << setfill(separator) << month_counter;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << amount;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << monthly_payment;
		cout << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << (interest_rate / 12);
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << get_monthly_interest();
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << principal << endl;
	}
	void initialize_table() {
		cout << "********************************************************" << endl;
		cout << "\tAmortization Table" << endl;
		cout << "********************************************************" << endl;
		cout << left << setw(month_width) << setfill(separator) << "Month";
		cout << left << setw(width) << setfill(separator) << "Balance";
		cout << left << setw(width) << setfill(separator) << "Payment";
		cout << left << setw(width) << setfill(separator) << "Rate";
		cout << left << setw(width) << setfill(separator) << "Interest";
		cout << left << setw(width) << setfill(separator) << "Principal";
		cout << endl;

		cout << left << setw(month_width) << setfill(separator) << month_counter;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << amount;
		cout << left << setw(width) << setfill(separator) << "N/A";
		cout << left << setw(width) << setfill(separator) << " N/A";
		cout << left << setw(width) << setfill(separator) << " N/A";
		cout << left << setw(width) << setfill(separator) << "  N/A" << endl;
	}
	void increment_month_counter() {
		month_counter++;
	}
	void print_final_month() {
		double new_amount = monthly_payment + amount;
		set_monthly_interest(new_amount);
		principal = new_amount - monthly_interest;
		cout << setw(month_width) << fixed << showpoint << setprecision(precision) << setfill(separator) << month_counter;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << 0.00;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << new_amount;
		cout << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << interest_rate / 12;
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << get_monthly_interest();
		cout << "$" << left << setw(width) << fixed << showpoint << setprecision(precision) << setfill(separator) << principal << endl;
	}
	void final_report() {
		cout << left << "********************************************************\n" << endl;
		cout << left << "It takes " << month_counter << " months to pay off the loan." << endl;
		cout << left << "Total interest paid is: " << "$" << interest_sum << endl;
	}
	void invalid_parameters_message() {
		cout << "Invalid Parameters. Please try again with different ones." << endl;
	}
};

int main() {
	bool canFinish = false;
	while (!canFinish) {
		Loan loan = Loan();
		loan.set_monthly_interest();
		if (Loan::is_valid_loan(loan.monthly_interest, loan.monthly_payment)) {
			canFinish = true;
			loan.initialize_table();
			while (loan.amount > 0) {
				loan.increment_month_counter();
				loan.set_monthly_interest();
				loan.handle_principal();
				loan.subtract_principal();
				if (loan.amount <= 0) {
					loan.print_final_month();
				}
				else {
					loan.print_record();
				}
			}
			loan.final_report();
		}
		else {
			loan.invalid_parameters_message();
		}
	}
	return 0;
};




