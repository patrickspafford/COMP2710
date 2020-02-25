/*
File Name: project2_pas0037.cpp
How to Compile: g++ project2_pas0037.cpp
Author: Patrick Spafford (pas0037)

Sources Used: Geeks for Geeks https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
		This helped me figure out how to make each iteration of my for loop return different random numbers.





*/




#include <iostream>
#include <ctime>
#include <assert.h>
#include <stdlib.h>

using namespace std;

class Duel
{
public:
	static const int number_of_runs = 10000;
	static const int Aaron_accuracy1 = 33;
	static const int Bob_accuracy = 50;
	static const int Charlie_accuracy = 100;

	bool Aaron_alive;
	bool Bob_alive;
	bool Charlie_alive;

	Duel() {
		Aaron_alive = true;
		Bob_alive = true;
		Charlie_alive = true;
	}
	// prototypes
	bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
		if (A_alive && B_alive) {
			return true;
		}
		if (A_alive && C_alive) {
			return true;
		}
		if (B_alive && C_alive) {
			return true;
		}
		return false;
	}
	void Aaron_shoots1(bool &B_alive, bool &C_alive) {
		if (Aaron_alive) {
			int  shoot_target_result_A1 = rand() % 100;
			if (shoot_target_result_A1 <= Aaron_accuracy1) {
				if (B_alive && C_alive) {
					Charlie_alive = false;
					return;

				}
				if (!B_alive && C_alive) {
					Charlie_alive = false;
					return;
				}
				if (B_alive && !C_alive) {
					Bob_alive = false;
					return;
				}
			}
		}
	}
	void Bob_shoots(bool& A_alive, bool& C_alive) {
		if (Bob_alive) {
			int shoot_target_resultB = rand() % 100;
			if (shoot_target_resultB <= Bob_accuracy) {
				if (A_alive && C_alive) {
					Charlie_alive = false;
					return;
				}
				if (!A_alive && C_alive) {
					Charlie_alive = false;
					return;
				}
				if (A_alive && !C_alive) {
					Aaron_alive = false;
					return;
				}
			}
		}
	}
	void Charlie_shoots(bool& A_alive, bool& B_alive) {
		if (Charlie_alive) {
			if (A_alive && B_alive) {
				Bob_alive = false;
				return;
			}
			if (!A_alive && B_alive) {
				Bob_alive = false;
				return;
			}
			if (A_alive && !B_alive) {
				Aaron_alive = false;
				return;
			}
		}
	}
	void Aaron_shoots2(bool& B_alive, bool& C_alive) {
		return;
	}
	void press_any_key() {
		cout << "Press any key to continue...";
		cin.ignore().get();
	}
	// test drivers
	void test_at_least_two_alive(bool A, bool B, bool C) {
		A = true;
		B = true;
		C = true;
		cout << "Unit Testing 1: Function - at_least_two_alive()" << endl;
		cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive" << endl;
		bool all_alive_case = at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive);
		assert(all_alive_case);
		if (all_alive_case) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive" << endl;
		bool Aaron_not_alive_case = at_least_two_alive(!Aaron_alive, Bob_alive, Charlie_alive);
		assert(Aaron_not_alive_case);
		if (Aaron_not_alive_case) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive" << endl;
		bool Bob_not_alive_case = at_least_two_alive(Aaron_alive, !Bob_alive, Charlie_alive);
		assert(Bob_not_alive_case);
		if (Bob_not_alive_case) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead" << endl;
		bool Charlie_not_alive_case = at_least_two_alive(Aaron_alive, Bob_alive, !Charlie_alive);
		assert(Charlie_not_alive_case);
		if (Charlie_not_alive_case) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive" << endl;
		bool AB_not_alive = at_least_two_alive(!Aaron_alive, !Bob_alive, Charlie_alive);
		assert(!AB_not_alive);
		if (!AB_not_alive) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead" << endl;
		bool AC_not_alive = at_least_two_alive(!Aaron_alive, Bob_alive, !Charlie_alive);
		assert(!AC_not_alive);
		if (!AC_not_alive) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead" << endl;
		bool BC_not_alive = at_least_two_alive(Aaron_alive, !Bob_alive, !Charlie_alive);
		assert(!BC_not_alive);
		if (!BC_not_alive) {
			cout << "\tCase passed ..." << endl;
		}
		cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead" << endl;
		bool none_alive = at_least_two_alive(!Aaron_alive, !Bob_alive, !Charlie_alive);
		assert(!none_alive);
		if (!none_alive) {
			cout << "\tCase passed ..." << endl;
		}
	} // complete
	void test_Aaron_shoots1() {
		bool B = true;
		bool C = true;
		bool notB = false;
		bool notC = false;
		cout << "Unit Testing 2: Function - Aaron_shoots1(Bob_alive, Charlie_alive)" << endl;
		cout << "\tCase 1: Bob alive, Charlie alive" << endl;
		while (Charlie_alive) {
			Aaron_shoots1(B, C);
		}
		assert(true);
		cout << "\t\tAaron is shooting at Charlie" << endl;
		cout << "\tCase 2: Bob dead, Charlie alive" << endl;
		Charlie_alive = true;
		while (Charlie_alive) {
			Aaron_shoots1(notB, C);
		}
		assert(true);
		cout << "\t\tAaron is shooting at Charlie" << endl;
		cout << "\tCase 3: Bob alive, Charlie dead" << endl;
		Charlie_alive = true;
		while (Bob_alive) {
			Aaron_shoots1(B, notC);
		}
		assert(true);
		cout << "\t\tAaron is shooting at Bob" << endl;
		Bob_alive = true;
	}
	void test_Bob_shoots(void) {
		bool A = true;
		bool C = true;
		bool notA = false;
		bool notC = false;
		cout << "Unit Testing 3: Function - Bob_shoots(Aaron_alive, Charlie_alive)" << endl;
		cout << "\tCase 1: Aaron alive, Charlie alive" << endl;
		while (Charlie_alive) {
			Bob_shoots(A, C);
		}
		assert(true);
		cout << "\t\tBob is shooting at Charlie" << endl;
		cout << "\tCase 2: Aaron dead, Charlie alive" << endl;
		Charlie_alive = true;
		while (Charlie_alive) {
			Bob_shoots(notA, C);
		}
		assert(true);
		cout << "\t\tBob is shooting at Charlie" << endl;
		Charlie_alive = true;
		cout << "\tCase 3: Aaron alive, Charlie dead" << endl;
		while (Aaron_alive) {
			Bob_shoots(A, notC);
		}
		assert(true);
		cout << "\t\tBob is shooting at Aaron" << endl;

	}
	void test_Charlie_shoots(void) {
		bool A = true;
		bool B = true;
		bool notA = false;
		bool notB = false;

		cout << "Unit Testing 4: Function - Charlie_shoots(Aaron_alive, Bob_alive)" << endl;

		cout << "\tCase 1: Aaron alive, Bob alive" << endl;
		while (Bob_alive) {
			Charlie_shoots(A, B);
		}
		assert(true);
		cout << "\t\tCharlie is shooting at Bob" << endl;
		Bob_alive = true;


		cout << "\tCase 2: Aaron dead, Bob alive" << endl;
		while (Bob_alive) {
			Charlie_shoots(notA, B);
		}
		assert(true);
		cout << "\t\tCharlie is shooting at Bob" << endl;
		Bob_alive = true;


		cout << "\tCase 3: Aaron alive, Bob dead" << endl;
		while (Aaron_alive) {
			Charlie_shoots(A, notB);
		}
		assert(true);
		cout << "\t\tCharlie is shooting at Aaron" << endl;
		Aaron_alive = true;

	}
	void test_Aaron_shoots2(void) {
		bool B = true;
		bool C = true;
		bool notB = false;
		bool notC = false;
		cout << "Unit Testing 5: Function - Aaron_shoots2(Bob_alive, Charlie_alive)" << endl;
		cout << "\tCase 1: Bob alive, Charlie alive" << endl;
		for (int i = 0; i < 50; i++) {
			Aaron_shoots2(B, C);
		}
		assert(Charlie_alive);
		cout << "\t\tAaron is shooting at Charlie" << endl;
		cout << "\tCase 2: Bob dead, Charlie alive" << endl;
		for (int i = 0; i < 50; i++) {
			Aaron_shoots2(notB, C);
		}
		assert(Charlie_alive);
		cout << "\t\tAaron is shooting at Charlie" << endl;
		cout << "\tCase 3: Bob alive, Charlie dead" << endl;
		for (int i = 0; i < 50; i++) {
			Aaron_shoots2(B, notC);
		}
		assert(Bob_alive);
		cout << "\t\tAaron is shooting at Bob" << endl;

	}
};


int main() {
	int Aaron_wins1 = 0;
	int Bob_wins1 = 0;
	int Charlie_wins1 = 0;

	int Aaron_wins2 = 0;
	int Bob_wins2 = 0;
	int Charlie_wins2 = 0;
	cout << "***Welcome to Patrick's Duel Simulator***\n";
	Duel test = Duel();
	test.test_at_least_two_alive(test.Aaron_alive, test.Bob_alive, test.Charlie_alive);
	test.press_any_key();
	test.test_Aaron_shoots1();
	test.press_any_key();
	test.test_Bob_shoots();
	test.press_any_key();
	test.test_Charlie_shoots();
	test.press_any_key();
	test.test_Aaron_shoots2();
	test.press_any_key();
	cout << "Ready to test strategy 1 (run 10000 times):" << endl;
	test.press_any_key();
	for (int i = 0; i < test.number_of_runs; i++) {
		srand(time(0) + i);
		Duel duel_1 = Duel();
		while (duel_1.at_least_two_alive(duel_1.Aaron_alive, duel_1.Bob_alive, duel_1.Charlie_alive)) {
			duel_1.Aaron_shoots1(duel_1.Bob_alive, duel_1.Charlie_alive);
			duel_1.Bob_shoots(duel_1.Aaron_alive, duel_1.Charlie_alive);
			duel_1.Charlie_shoots(duel_1.Aaron_alive, duel_1.Bob_alive);
		}
		if (duel_1.Aaron_alive) {
			Aaron_wins1++;
		}
		if (duel_1.Bob_alive) {
			Bob_wins1++;
		}
		if (duel_1.Charlie_alive) {
			Charlie_wins1++;
		}
	}
	// Print results
	cout << "Aaron won " << Aaron_wins1 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Aaron_wins1) / test.number_of_runs * 100 << "%" << endl;
	cout << "Bob won " << Bob_wins1 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Bob_wins1) / test.number_of_runs * 100 << "%" << endl;
	cout << "Charlie won " << Charlie_wins1 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Charlie_wins1) / test.number_of_runs * 100 << "%" << endl;
	cout << "Ready to test strategy 2 (run 10000 times):" << endl;
	test.press_any_key();
	for (int i = 0; i < test.number_of_runs; i++) {
		Duel duel_2 = Duel();
		duel_2.Aaron_shoots2(duel_2.Bob_alive, duel_2.Charlie_alive);
		while (duel_2.at_least_two_alive(duel_2.Aaron_alive, duel_2.Bob_alive, duel_2.Charlie_alive)) {
			duel_2.Bob_shoots(duel_2.Aaron_alive, duel_2.Charlie_alive);
			duel_2.Charlie_shoots(duel_2.Aaron_alive, duel_2.Bob_alive);
			duel_2.Aaron_shoots1(duel_2.Bob_alive, duel_2.Charlie_alive);
		}
		if (duel_2.Aaron_alive) {
			Aaron_wins2++;
		}
		if (duel_2.Bob_alive) {
			Bob_wins2++;
		}
		if (duel_2.Charlie_alive) {
			Charlie_wins2++;
		}
	}
	// print results
	cout << "Aaron won " << Aaron_wins2 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Aaron_wins2) / test.number_of_runs * 100 << "%" << endl;
	cout << "Bob won " << Bob_wins2 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Bob_wins2) / test.number_of_runs * 100 << "%" << endl;
	cout << "Charlie won " << Charlie_wins2 << "/" << test.number_of_runs << " duels or " << static_cast<double>(Charlie_wins2) / test.number_of_runs * 100 << "%" << endl;


	// Compare strategy 1 to strategy 2
	if (Aaron_wins1 > Aaron_wins2) {
		cout << "\nStrategy 1 is better than strategy 2." << endl;
	}
	if (Aaron_wins2 > Aaron_wins1) {
		cout << "\nStrategy 2 is better than strategy 1." << endl;
	}
	if (Aaron_wins1 == Aaron_wins2) {
		cout << "\nStrategy 1 and strategy 2 are the same.";
	}
	return 0;


};


