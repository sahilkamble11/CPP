#include "../include/Question.h"
#include"../include/QuestionBank.h"

int main()
{

    
    QuestionBank qb; // Create an instance of QuestionBank

    int choice;
    while (choice != 5) {
        cout << "1. Add Question\n";
        cout << "2. Remove Question\n";
        cout << "3. Display Questions\n";
        cout << "4. Update Question\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
       
    
        switch (choice) {
            case 1: {
                Question q;
                int id;
                string subject, title, option_a, option_b, option_c, option_d;
                char answer_key;

                cout << "Enter Question ID: ";
                cin >> id;
                q.setId(id);
                cin.ignore();

                cout << "Enter Subject: ";
                getline(cin, subject);
                q.setSubject(subject);

                cout << "Enter Title: ";
                getline(cin, title);
                q.setTitle(title);

                cout << "Enter Option A: ";
                getline(cin, option_a);
                q.setOptionA(option_a);

                cout << "Enter Option B: ";
                getline(cin, option_b);
                q.setOptionB(option_b);

                cout << "Enter Option C: ";
                getline(cin, option_c);
                q.setOptionC(option_c);

                cout << "Enter Option D: ";
                getline(cin, option_d);
                q.setOptionD(option_d);

                cout << "Enter Answer Key (A/B/C/D): ";
                cin >> answer_key;
                q.setAnswerKey(answer_key);

                qb.addQuestion(q);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Question ID to remove: ";
                cin >> id;
                qb.removeQuestion(id);
                break;
            }
            case 3:
                qb.displayQuestions();
                break;
            case 4: {
                int id;
                Question updatedQuestion;

                cout << "Enter Question ID to update: ";
                cin >> id;

                // Get updated details
                int new_id;
                string new_subject, new_title, new_option_a, new_option_b, new_option_c, new_option_d;
                char new_answer_key;

                cout << "Enter New Question ID: ";
                cin >> new_id;
                updatedQuestion.setId(new_id);
                
                cin.ignore();
                
                cout << "Enter New Subject: ";
                getline(cin, new_subject);
                updatedQuestion.setSubject(new_subject);

                cout << "Enter New Title: ";
                getline(cin, new_title);
                updatedQuestion.setTitle(new_title);

                cout << "Enter New Option A: ";
                getline(cin, new_option_a);
                updatedQuestion.setOptionA(new_option_a);

                cout << "Enter New Option B: ";
                getline(cin, new_option_b);
                updatedQuestion.setOptionB(new_option_b);

                cout << "Enter New Option C: ";
                getline(cin, new_option_c);
                updatedQuestion.setOptionC(new_option_c);

                cout << "Enter New Option D: ";
                getline(cin, new_option_d);
                updatedQuestion.setOptionD(new_option_d);

                
               }          
            case 5 :
               return 0;
               
    }
    
    };
}










