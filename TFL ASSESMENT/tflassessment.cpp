#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Question {
private:
    int questionId;
    string questionText;
    vector<string> options;
    int correctAnswer;
    string evaluationCriteria;
    static int nextId;

public:
    // Constructors
    Question() : questionId(0), correctAnswer(0) {}
    
    Question(string text, vector<string> opts, int correct, string criteria) {
        questionId = nextId++;
        questionText = text;
        options = opts;
        correctAnswer = correct;
        evaluationCriteria = criteria;
    }

    // Getters
    int getQuestionId() const { return questionId; }
    string getQuestionText() const { return questionText; }
    vector<string> getOptions() const { return options; }
    int getCorrectAnswer() const { return correctAnswer; }
    string getEvaluationCriteria() const { return evaluationCriteria; }

    // Setters
    void setQuestionId(int id) { questionId = id; }
    void setQuestionText(const string& text) { questionText = text; }
    void setOptions(const vector<string>& opts) { options = opts; }
    void setCorrectAnswer(int correct) { correctAnswer = correct; }
    void setEvaluationCriteria(const string& criteria) { evaluationCriteria = criteria; }

    // toString method
    string toString() const {
        stringstream ss;
        ss << questionId << "|" << questionText << "|";
        for (const string& option : options) {
            ss << option << ";";
        }
        ss << "|" << correctAnswer << "|" << evaluationCriteria;
        return ss.str();
    }

    // Display question for test
    void displayQuestion() const {
        cout << "\nQuestion " << questionId << ": " << questionText << endl;
        for (size_t i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
    }

    // Display question with correct answer
    void displayWithAnswer() const {
        cout << "\nQuestion " << questionId << ": " << questionText << endl;
        for (size_t i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i];
            if ((int)(i + 1) == correctAnswer) {
                cout << " ← CORRECT ANSWER";
            }
            cout << endl;
        }
        cout << "Evaluation Criteria: " << evaluationCriteria << endl;
    }

    static int getNextId() { return nextId; }
    static void setNextId(int id) { nextId = id; }
};

int Question::nextId = 1;

class QuestionBank {
private:
    vector<Question> questions;
    const string filename = "QuestionBank.txt";

public:
    QuestionBank() {
        loadFromFile();
    }

    ~QuestionBank() {
        saveToFile();
    }

    void insertQuestion(const Question& theQuestion) {
        questions.push_back(theQuestion);
        cout << "Question added successfully with ID: " << theQuestion.getQuestionId() << endl;
        saveToFile();
    }

    void updateQuestion(int questionId) {
        for (Question& q : questions) {
            if (q.getQuestionId() == questionId) {
                cout << "\nCurrent Question:\n";
                q.displayWithAnswer();
                
                cout << "\nEnter new question text: ";
                cin.ignore();
                string newText;
                getline(cin, newText);
                q.setQuestionText(newText);

                cout << "Enter number of options: ";
                int numOptions;
                cin >> numOptions;
                
                vector<string> newOptions;
                for (int i = 0; i < numOptions; i++) {
                    cout << "Option " << (i + 1) << ": ";
                    cin.ignore();
                    string option;
                    getline(cin, option);
                    newOptions.push_back(option);
                }
                q.setOptions(newOptions);

                cout << "Enter correct answer (1-" << numOptions << "): ";
                int correct;
                cin >> correct;
                q.setCorrectAnswer(correct);

                cout << "Enter evaluation criteria: ";
                cin.ignore();
                string criteria;
                getline(cin, criteria);
                q.setEvaluationCriteria(criteria);

                cout << "Question updated successfully!" << endl;
                saveToFile();
                return;
            }
        }
        cout << "Question with ID " << questionId << " not found!" << endl;
    }

    void showQuestion(int questionId) const {
        for (const Question& q : questions) {
            if (q.getQuestionId() == questionId) {
                q.displayWithAnswer();
                return;
            }
        }
        cout << "Question with ID " << questionId << " not found!" << endl;
    }

    void removeQuestion(int questionId) {
        auto it = remove_if(questions.begin(), questions.end(),
                           [questionId](const Question& q) { return q.getQuestionId() == questionId; });
        
        if (it != questions.end()) {
            questions.erase(it, questions.end());
            cout << "Question removed successfully!" << endl;
            saveToFile();
        } else {
            cout << "Question with ID " << questionId << " not found!" << endl;
        }
    }

    void showAllQuestions() const {
        if (questions.empty()) {
            cout << "No questions in the bank!" << endl;
            return;
        }
        
        cout << "\n========== QUESTION BANK ==========\n";
        for (const Question& q : questions) {
            q.displayWithAnswer();
            cout << "-----------------------------------\n";
        }
    }

    vector<Question> getQuestions() const { return questions; }

    vector<Question> selectQuestionsForTest(const vector<int>& questionIds) const {
        vector<Question> testQuestions;
        for (int id : questionIds) {
            for (const Question& q : questions) {
                if (q.getQuestionId() == id) {
                    testQuestions.push_back(q);
                    break;
                }
            }
        }
        return testQuestions;
    }

private:
    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            file << Question::getNextId() << endl; // Save next ID
            for (const Question& q : questions) {
                file << q.toString() << endl;
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                Question::setNextId(stoi(line)); // Load next ID
            }
            
            while (getline(file, line)) {
                Question q = parseQuestion(line);
                questions.push_back(q);
            }
            file.close();
        }
    }

    Question parseQuestion(const string& line) {
        Question q;
        stringstream ss(line);
        string part;
        int partIndex = 0;

        while (getline(ss, part, '|')) {
            switch (partIndex) {
                case 0: q.setQuestionId(stoi(part)); break;
                case 1: q.setQuestionText(part); break;
                case 2: {
                    vector<string> options;
                    stringstream optionStream(part);
                    string option;
                    while (getline(optionStream, option, ';')) {
                        if (!option.empty()) {
                            options.push_back(option);
                        }
                    }
                    q.setOptions(options);
                    break;
                }
                case 3: q.setCorrectAnswer(stoi(part)); break;
                case 4: q.setEvaluationCriteria(part); break;
            }
            partIndex++;
        }
        return q;
    }
};

class TestResult {
public:
    int questionId;
    int givenAnswer;
    int correctAnswer;
    bool isCorrect;
    
    TestResult(int qId, int given, int correct) 
        : questionId(qId), givenAnswer(given), correctAnswer(correct) {
        isCorrect = (given == correct);
    }
};

class AssessmentSystem {
private:
    QuestionBank questionBank;

public:
    void addQuestion() {
        cout << "\n========== ADD NEW QUESTION ==========\n";
        cout << "Enter question text: ";
        cin.ignore();
        string questionText;
        getline(cin, questionText);

        cout << "Enter number of options: ";
        int numOptions;
        cin >> numOptions;

        vector<string> options;
        for (int i = 0; i < numOptions; i++) {
            cout << "Option " << (i + 1) << ": ";
            cin.ignore();
            string option;
            getline(cin, option);
            options.push_back(option);
        }

        cout << "Enter correct answer (1-" << numOptions << "): ";
        int correctAnswer;
        cin >> correctAnswer;

        cout << "Enter evaluation criteria: ";
        cin.ignore();
        string criteria;
        getline(cin, criteria);

        Question newQuestion(questionText, options, correctAnswer, criteria);
        questionBank.insertQuestion(newQuestion);
    }

    void createTest() {
        cout << "\n========== CREATE TEST ==========\n";
        questionBank.showAllQuestions();
        
        if (questionBank.getQuestions().empty()) {
            cout << "No questions available to create test!" << endl;
            return;
        }

        cout << "\nEnter question IDs for the test (space-separated, -1 to finish): ";
        vector<int> questionIds;
        int id;
        while (cin >> id && id != -1) {
            questionIds.push_back(id);
        }

        if (questionIds.empty()) {
            cout << "No questions selected!" << endl;
            return;
        }

        vector<Question> testQuestions = questionBank.selectQuestionsForTest(questionIds);
        if (testQuestions.empty()) {
            cout << "No valid questions found!" << endl;
            return;
        }

        takeTest(testQuestions);
    }

    void takeTest(const vector<Question>& testQuestions) {
        cout << "\n========== TAKING TEST ==========\n";
        cout << "Total Questions: " << testQuestions.size() << endl;
        cout << "Enter your answers (1, 2, 3, etc.)\n";

        vector<TestResult> results;
        
        for (const Question& q : testQuestions) {
            q.displayQuestion();
            cout << "Your answer: ";
            int answer;
            cin >> answer;
            
            TestResult result(q.getQuestionId(), answer, q.getCorrectAnswer());
            results.push_back(result);
        }

        showTestResults(testQuestions, results);
    }

    void showTestResults(const vector<Question>& testQuestions, const vector<TestResult>& results) {
        cout << "\n========== TEST RESULTS ==========\n";
        
        int correctCount = 0;
        for (const TestResult& result : results) {
            if (result.isCorrect) correctCount++;
        }

        double percentage = (double)correctCount / results.size() * 100;
        
        cout << "Score: " << correctCount << "/" << results.size() 
             << " (" << fixed << setprecision(1) << percentage << "%)" << endl;
        
        if (percentage >= 80) cout << "Grade: Excellent!" << endl;
        else if (percentage >= 60) cout << "Grade: Good" << endl;
        else if (percentage >= 40) cout << "Grade: Average" << endl;
        else cout << "Grade: Needs Improvement" << endl;

        cout << "\n========== DETAILED REVIEW ==========\n";
        for (size_t i = 0; i < testQuestions.size(); i++) {
            const Question& q = testQuestions[i];
            const TestResult& result = results[i];
            
            cout << "\nQuestion " << q.getQuestionId() << ": " << q.getQuestionText() << endl;
            
            vector<string> options = q.getOptions();
            for (size_t j = 0; j < options.size(); j++) {
                cout << (j + 1) << ". " << options[j];
                if ((int)(j + 1) == result.correctAnswer) {
                    cout << " ← CORRECT";
                }
                if ((int)(j + 1) == result.givenAnswer && result.givenAnswer != result.correctAnswer) {
                    cout << " ← YOUR ANSWER";
                }
                cout << endl;
            }
            
            if (result.isCorrect) {
                cout << "✓ CORRECT" << endl;
            } else {
                cout << "✗ INCORRECT - Your answer: " << result.givenAnswer 
                     << ", Correct answer: " << result.correctAnswer << endl;
            }
            cout << "-----------------------------------" << endl;
        }
    }

    void showMenu() {
        cout << "\n========== TFL ASSESSMENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Question to Bank\n";
        cout << "2. Edit Question\n";
        cout << "3. Show Question\n";
        cout << "4. Remove Question\n";
        cout << "5. Show All Questions\n";
        cout << "6. Create and Take Test\n";
        cout << "7. Exit\n";
        cout << "======================================================\n";
        cout << "Enter your choice: ";
    }

    void run() {
        int choice;
        do {
            showMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    addQuestion();
                    break;
                case 2: {
                    cout << "Enter question ID to edit: ";
                    int id;
                    cin >> id;
                    questionBank.updateQuestion(id);
                    break;
                }
                case 3: {
                    cout << "Enter question ID to show: ";
                    int id;
                    cin >> id;
                    questionBank.showQuestion(id);
                    break;
                }
                case 4: {
                    cout << "Enter question ID to remove: ";
                    int id;
                    cin >> id;
                    questionBank.removeQuestion(id);
                    break;
                }
                case 5:
                    questionBank.showAllQuestions();
                    break;
                case 6:
                    createTest();
                    break;
                case 7:
                    cout << "Thank you for using TFL Assessment Management System!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 7);
    }
};

int main() {
    AssessmentSystem system;
    system.run();
    return 0;
}