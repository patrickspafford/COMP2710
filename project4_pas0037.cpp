/*
File Name: project4_pas0037.cpp
Author: Patrick Spafford
How to Compile: g++ project4_pas0037.cpp
Sources Used:
Stack Overflow
	Insert Node at End of LinkedList C++ https://stackoverflow.com/questions/20125477/linked-list-insert-at-the-end-c
	Read Access Violation Visual Studio https://stackoverflow.com/questions/44276919/c-read-access-violation-in-doubly-linked-list-in-visual-studio
	Pressing Enter Twice with Cin https://stackoverflow.com/questions/13556890/why-do-i-have-to-press-enter-twice
	Cin.clear() and Cin.ignore() https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
	Using int for getline? https://stackoverflow.com/questions/5844309/trying-to-use-int-in-getline

Get Line http://www.cplusplus.com/reference/string/string/getline/
Find Length of Linked List https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
*/
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;
struct trivia_node {
	string question;
	string answer;
	int points;
	trivia_node* next = NULL;
};

typedef trivia_node *ptr_node; 

void init_question_list(ptr_node& q_list) {
	ptr_node cur_ptr = new trivia_node;

	cur_ptr->question = "How long was the shortest war on record? (Hint: how many minutes)";
	cur_ptr->answer = "38";
	cur_ptr->points = 100;
	cur_ptr->next = new trivia_node;
	ptr_node temp = cur_ptr;
	cur_ptr = cur_ptr->next;

	cur_ptr->question = "What was Bank of America's original name? (Hint: Bank or Italy or Bank of Germany)";
	cur_ptr->answer = "Bank of Italy";
	cur_ptr->points = 50;
	cur_ptr->next = new trivia_node;
	cur_ptr = cur_ptr->next;

	cur_ptr->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
	cur_ptr->answer = "Wii Sports";
	cur_ptr->points = 20;

	cur_ptr = temp;
	q_list = cur_ptr;

}

void add_question(ptr_node& q_list) {
	ptr_node new_ptr = new trivia_node;
	int points;
	int initial_length = 0;
	int final_length = 0;

	ptr_node temp = q_list;
	if (q_list != NULL) {
		initial_length++;
	}
	while (q_list->next != NULL) {
		q_list = q_list->next;
		initial_length++;
	}

	cout << "Enter a new question: ";
	getline(cin, new_ptr->question);
	cin.clear();

	cout << "Enter an answer: ";
	getline(cin, new_ptr->answer);
	cin.clear();

	cout << "Enter award points: ";
	cin >> points;
	new_ptr->points = points;
	cin.clear();
	q_list->next = new_ptr;
	

	while (q_list != NULL) {
		q_list = q_list->next;
		final_length++;
	}
	q_list = temp;
}

int ask_question(ptr_node q_list, int num_ask) {
	ptr_node cur_ptr = q_list;
	string user_answer;
	int total_points = 0;
	int num_of_questions = 0;
	while (cur_ptr != NULL) {
		cur_ptr = cur_ptr->next;
		num_of_questions++;
		
	}
	cur_ptr = q_list;
	if (cur_ptr == NULL) {
		return 0;
	}
	if (num_ask < 1) {
		cout << "Warning - the number of trivia to be asked must be equal to or be larger than 1";
		return 1;
	}
	else if (num_of_questions < num_ask) {
		cout << "Warning - There is only " << num_of_questions << " trivia in the list.";
		return 1;

	}
	else {
		for (int x = 0; x < num_ask; x++) {
			cout << "Question: " << cur_ptr->question << endl;
			cout << "Answer: ";
			getline(cin, user_answer);
			cin.clear();
			//cin.ignore(10000, '\n');
			if (user_answer.compare(cur_ptr->answer) == 0) {
				cout << "Your answer is correct. You receive " << cur_ptr->points << " points.";
				total_points += cur_ptr->points;
				cout << "\nYour total points: " << total_points << endl;
				cur_ptr = cur_ptr->next;
			}
			else {
				cout << "Your answer is wrong. The correct answer is: " << cur_ptr->answer;
				cout << "\nYour total points: " << total_points << endl;
				cur_ptr = cur_ptr->next;
			}
			
		}
		return 0;
	}
}

#define UNIT_TESTING // comment out to run trivia_quiz
#define trivia_quiz

void Unit_Test() {
	cout << "***This is a debugging version ***\n";
	ptr_node node_list = new trivia_node;
	init_question_list(node_list);
	cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
	int result1 = ask_question(node_list, 0);
	assert(result1 == 1);
	cout << "\nCase 1 Passed\n\n";
	cout << "Unit Test Case 2: Ask 1 question in the linked list. The tester enters either a correct or incorrect answer." << endl;
	int result2 = ask_question(node_list, 1);
	assert(result2 == 0);
	cout << "\nCase 2 Passed\n\n";
	cout << "Unit Test Case 3: Ask 3 questions in the linked list. The tester enters either correct or incorrect answers." << endl;
	int result3 = ask_question(node_list, 3);
	assert(result3 == 0);
	cout << "\nCase 3 Passed\n\n";
	cout << "Unit Test Case 4: Ask 5 questions in the linked list that exceeds the number of available trivia in the linked list." << endl;
	int result4 = ask_question(node_list, 5);
	assert(result4 == 1);
	cout << "\n\nCase 4 Passed\n\n";
	cout << "*** End of the Debugging Version ***\n\n";
}


int main() {
#ifdef UNIT_TESTING
	Unit_Test();
	return 0;
#endif
#ifdef trivia_quiz
	ptr_node node_list = new trivia_node;
	init_question_list(node_list);
	cout << "*** Welcome to Patrick's trivia quiz game ***\n";
	int num_of_questions = 3;
	while (cin.good()) {
		add_question(node_list);
		num_of_questions++;
		string do_continue;
		cout << "Continue? (Yes/No): ";
		cin >> do_continue;
		cin.clear();
		cin.ignore(10000, '\n');
		if (do_continue.compare("No") == 0) {
			break;
		}
	}
	ask_question(node_list, num_of_questions);
	cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n\n";
#endif

}


