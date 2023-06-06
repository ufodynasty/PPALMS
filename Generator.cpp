#include "Generator.h"

vector<Question> Generator::GenerateQuestions(Settings* settings) {
    vector<Question> output;

    // Checks to make sure settings have been configured.
    if(settings->GetPath().empty() || 
       settings->GetType().empty() ||
       settings->GetLines().size() == 0) {
        return output;
    }

    // Grabs all lines from the requested file.
    LineGrabber grabber;
    vector<vector<string>> lines = grabber.GrabLines(settings->GetPath(), settings->GetLines());
    
    if(lines.size() != 0) {
        if(settings->GetType().compare("rearrange") == 0) {
            output = GenerateRearrange(settings, lines);
        }
        else if(settings->GetType().compare("FITB") == 0) {
            output = GenerateFITB(settings, lines);
        }
        else if(settings->GetType().compare("MC") == 0) {
            output = GenerateMC(settings, lines);
        }
    }
    
    // Returns a blank question vector on error.
    return output;
}

vector<Question> Generator::GenerateRearrange(Settings* settings, vector<vector<string>> lines) {
    vector<Question> questions;

    for(int m = 0; m < settings->GetMutations(); m++) {
        Question question;
        question.type = "rearrange";
        question.correctAnswers = lines;

        // Places all lines in a single vector.
        vector<string> scrambled;
        for(int i = 0; i < lines.size(); i++) {
            for(int j = 0; j < lines.at(i).size(); j++) {
                scrambled.push_back(lines.at(i).at(j));
            }
        }

        // Scrambles the vector.
        for(int i = 0; i < scrambled.size(); i++) {
            int randIndex = rand() % scrambled.size();

            if(i != randIndex) {
                string temp = scrambled.at(i);
                scrambled.at(i) = scrambled.at(randIndex);
                scrambled.at(randIndex) = temp;
            }
        }

        for(int i = 0; i < scrambled.size(); i++) {
            question.questionText.append(scrambled.at(i));
            question.questionText.append("\n");
        }
        
        questions.push_back(question);
    }

    return questions;
}

vector<Question> Generator::GenerateFITB(Settings* settings, vector<vector<string>> lines) {
    vector<Question> questions;

    for(int m = 0; m < settings->GetMutations(); ) {
        for(int i = 0; i < lines.size(); i++) {
            for(int j = 0; j < lines.at(i).size(); j++) {
                if(m >= settings->GetMutations()) {
                    continue;
                }

                string line = lines.at(i).at(j);

                if(line.size() == 0) {
                    continue;
                }

                Question question;
                question.type = "FITB";

                int start = 0;
                int length = 0;
                vector<int> starts;
                vector<int> lengths;

                // Finds all words and numbers in a line.
                for(int k = 0; k < line.size(); k++) {
                    if(isalpha(line.at(k)) || isdigit(line.at(k))) {
                        length++;
                    }
                    else if (length != 0) {
                        starts.push_back(start);
                        lengths.push_back(length);
                        length = 0;
                        start = k + 1;
                    }
                    else {
                        start = k + 1;
                    }
                }

                // Randomly selects from one of the words/numbers.
                if(starts.size() > 0) {
                     int choice = rand() % starts.size();
                    string modified = line.substr(starts.at(choice), lengths.at(choice));

                    // Removes the selected word/number/symbol from the line.
                    string text = line.substr(0, starts.at(choice));
                    for(int k = 0; k < lengths.at(choice); k++) {
                        text.append("_");
                    }
                    text.append(line.substr(starts.at(choice) + lengths.at(choice), line.size() - text.size()));

                    question.questionText = text;  // Modify this with blank.

                    vector<string> answer;
                    answer.push_back(modified);
                    question.correctAnswers.push_back(answer);

                    questions.push_back(question);
                    m++;
                }  
            }
        }
    }

    return questions;
}

vector<char> operators = {'+','-','*','/','%','&','|','=','>','<','#'};
vector<string> reserved = { "auto", "else","long","switch","break","enum","register","typedef",
                            "case", "extern", "return", "union", "char", "float", "short", "unsigned", 
                            "const", "for", "signed", "void", "continue", "goto", "sizeof", "volatile", 
                            "default", "if", "static", "while", "do", "int", "struct", "_Packed", 
                            "double"};

vector<Question> Generator::GenerateMC(Settings* settings, vector<vector<string>> lines) {
    vector<Question> questions;
    for(int m = 0; m < settings->GetMutations(); ) {
        for(int i = 0; i < lines.size(); i++) {
            for(int j = 0; j < lines.at(i).size(); j++) {
                if(m >= settings->GetMutations()) {
                    continue;
                }
                
                Question question;
                question.type = "MC";

                string line = lines.at(i).at(j);
                int start = 0;
                int length = 0;
                vector<int> starts;
                vector<int> lengths;
                vector<bool> types; // 0:alnum strings, 1:operator strings

                if(line.size() == 0) {
                    continue;
                }

                bool isAlnum = false;
                bool isOperator = false;

                for(int k = 0; k < line.size(); k++) {
                    if((isalnum(line.at(k)) && isAlnum) || (find(operators.begin(), operators.end(), line.at(k)) != operators.end() && isOperator)) {
                        length++;
                    }
                    else if (length != 0) {
                        starts.push_back(start);
                        lengths.push_back(length);
                        types.push_back(isOperator);
                        length = 0;
                        isAlnum = 0;
                        isOperator = 0;
                    }
                    if(!isAlnum && !isOperator) {
                        if(isalnum(line.at(k))) {
                            start = k;
                            length = 1;
                            isAlnum = true;
                        }
                        else if(find(operators.begin(), operators.end(), line.at(k)) != operators.end()) {
                            start = k;
                            length = 1;
                            isOperator = true;
                        }
                    }
                }
                if (length != 0) {
                    starts.push_back(start);
                    lengths.push_back(length);
                    types.push_back(isOperator);
                    length = 0;
                    isAlnum = 0;
                    isOperator = 0;
                }

                // Randomly selects from one of the words/numbers.
                if(starts.size() > 0) {
                    int choice = rand() % starts.size();
                    string modified = line.substr(starts.at(choice), lengths.at(choice));

                    // Removes the selected word/number/symbol from the line.
                    string text = line.substr(0, starts.at(choice));
                    for(int k = 0; k < lengths.at(choice); k++) {
                        text.append("_");
                    }
                    text.append(line.substr(starts.at(choice) + lengths.at(choice), line.size() - text.size()));

                    question.questionText = text;  // Modify this with blank.
                    question.correctAnswers.push_back({modified});

                    vector<string> incorrectAnswers;

                    // Generates 3 incorrect answers
                    while(incorrectAnswers.size() < 3) {
                        string answer = "";
                        if(types.at(choice)) {
                            for (int k = 0; k < lengths.at(choice); k++) {
                                answer.push_back(operators.at(rand() % operators.size()));
                            }
                        } else if(find(reserved.begin(), reserved.end(), modified) != reserved.end()) {
                            answer = reserved.at(rand() % reserved.size());
                        } else if(starts.size() > 3) {
                            int index = rand() % starts.size();
                            answer = line.substr(starts.at(index), lengths.at(index));
                        } else {
                            // Gives up if it is impossible to generate incorrect answers in the given paramters
                            break;
                        }
                        if(answer != modified && find(incorrectAnswers.begin(), incorrectAnswers.end(), answer) == incorrectAnswers.end()) {
                            // Add the potential incorrect answer if it is both unique and incorrect
                            incorrectAnswers.push_back(answer);
                        }
                    }

                    question.incorrectAnswers.push_back(incorrectAnswers);
                    if(!(incorrectAnswers.size() < 3)){
                        // Save the question only if it did not encounter an error
                        questions.push_back(question);
                        m++;
                    }
                }
            }
        }
    }

    return questions;
}
