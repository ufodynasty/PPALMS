#include "QuestionBank.h"

int QuestionBank::AddQuestions(vector<Question> questions) {
    if(questions.size() == 0) {
        return 1;
    }
    
    for(int i = 0; i < questions.size(); i++) {
        this->questions.push_back(questions.at(i));
    }

    return 0;
}

int QuestionBank::ExportQuestions() {
    if(questions.size() == 0) {
        cout << "  Error: no questions to export" << endl;
        return 0;
    }

    ofstream output;
    output.open("qti.txt");

    if(output.is_open()) {
        for(int i = 0; i < this->questions.size(); i++) {
            Question question = this->questions.at(i);
            
            if(question.type == "rearrange") {
                output << "Type: F" << endl;
                output << i + 1 << ". Rearrange the lines in the correct order:" << endl;
                output << question.questionText << endl;

                char choice = 'a';
                output << choice << ". ";

                for(int j = 0; j < question.correctAnswers.size(); j++) {
                    for(int k = 0; k < question.correctAnswers.at(j).size(); k++) {
                        output << question.correctAnswers.at(j).at(k) << endl;
                    }
                }
            }
            else if(question.type == "FITB") {
                output << "Type: F" << endl;
                output << i + 1 << ". Fill in the blank: ";
                output << question.questionText << endl;
                output << "a. " << question.correctAnswers.at(0).at(0) << endl;
            }
            else if(question.type == "MC") {
                output << i + 1 << ". Select the correct answer to fill-in-the-blank." << endl;
                output << question.questionText << endl;
                char choice = 'a';
                output << "*" << choice << ". ";
                output << question.correctAnswers.at(0).at(0) << endl;
                for(int j = 0; j < question.incorrectAnswers.at(0).size(); j++) {
                    choice++;
                    output << choice << ". ";
                    output << question.incorrectAnswers.at(0).at(j) << endl;
                }
            }
        }
        
        output.close();
        return 1;
    }
    
    output.close();
    return 0;
}
  
void QuestionBank::EraseQuestions() {
    this->questions.clear();
}