#include <iostream>
#include <fstream>
#include "../include/QuestionBank.h"

using namespace std;


void showMenu() {
    cout << "1. Add Question\n";
    cout << "2. Display Questions\n";
    cout << "3. Update Question\n";
    cout << "4. Delete Question\n";
    cout << "5. Exit\n";
    cout << "6. Backup Questions to File\n";
    cout << "7. Read Questions from File\n";
    cout << "8. Write Questions to File\n";
}


int getChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void acceptQuestion(Question& question) {
    int id, eval;
    string subject, title, option_a, option_b, option_c, option_d;
    char key;

    cout << "Option A: "; cin >> option_a;
    cout << "Option B: "; cin >> option_b;
    cout << "Option C: "; cin >> option_c;
    cout << "Option D: "; cin >> option_d;
    cout << "Choose Correct Answer (A/B/C/D): "; cin >> key;
    cout << "Evaluation Criteria ID: "; cin >> eval;

    question = Question(id, subject, title, option_a, option_b, option_c, option_d, key, eval);
}

int main() {
    QuestionBank questionBank;
    int choice=1;
    do {
        showMenu();
        choice = getChoice();

        switch(choice) {
            case 1:{ 
                cout << "Adding a new question...\n";
                Question newQuestion;
                acceptQuestion(newQuestion);
                questionBank.addQuestion(newQuestion);
            }
            break;

            case 2:{
                cout << "Displaying all questions...\n";
                questionBank.displayQuestions();
            }
            break;
            
            case 3:{
                cout << "Updating a question...\n";
                int id;
                cout << "Enter ID to update: ";
                cin >> id; cin.ignore();
                Question updatedQuestion;
                acceptQuestion(updatedQuestion);
                updatedQuestion.setId(id);
                questionBank.updateQuestion(id, updatedQuestion);
                cout << "Question updated successfully.\n";
                break;

            } 

            case 4:{
                cout << "Deleting a question...\n";
                int id;
                cout << "Enter ID to delete: ";
                cin >> id; cin.ignore();
                questionBank.removeQuestion(id);
                cout << "Question deleted successfully.\n";
            }
            break;

            case 5:{
                 cout << "Exiting the program...\n";
                return 0;
            }
               
            break;
            case 6:
                cout << "Backing up questions to file...\n";
            break;
            case 7:
                cout << "Reading questions from file...\n";
            break;

            case 8:
                cout << "Writing questions to file...\n";
            break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    }   
    while (choice != 5);
    cout << "Thank you for using the Question Bank System!\n";
    return 0;
}   
