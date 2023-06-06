// PPALMS - Version 0.1

#include "Generator.h"
#include "LineGrabber.h"
#include "Settings.h"
#include "QuestionBank.h"
#include <assert.h>

using namespace std;


void RunContinuousProgram();


int main(int argc, char **argv) {
    if(argc == 1) {
        RunContinuousProgram();
        exit(-1);
    }
    else if(argc < 6) {
        cout << "Usage: ./PPALMS file_path lms question_type mutations line_nums" << endl;
        exit(-1);
    }

    srand(time(NULL));

    string file_path = argv[1];
    string lms = argv[2];
    string type = argv[3];
    int mutants = atoi(argv[4]);
    vector<vector<int>> line_nums;

    // Get all line numbers.
    for(int i = 5; i < argc; i++) {
        vector<int> tuple;
        int ind;
        string arg = argv[i];

        if((ind = arg.find("-")) != string::npos) {
            tuple.push_back(stoi(arg.substr(0, ind)));
            tuple.push_back(stoi(arg.substr(ind + 1, arg.size() - ind - 1)));
        }
        else {
            tuple.push_back(stoi(arg));
        }

        line_nums.push_back(tuple);
    }

    // Generates questions and exports.
    Settings* settings = new Settings(file_path, lms, type, mutants, line_nums);
    Generator* generator = new Generator();
    QuestionBank* bank = new QuestionBank();
    bank->AddQuestions(generator->GenerateQuestions(settings));
    
    if(bank->ExportQuestions() == 1) {
        cout << "-- Successfully generated " << type << " problems to qti.txt --" << endl;
    }
    else {
        cout << "-- Failure --" << endl;
    }
  
    // Clean up.
    delete settings;
    delete generator;
    delete bank;
}

void RunContinuousProgram() {
    Settings* settings = new Settings();
    Generator* generator = new Generator();
    QuestionBank* bank = new QuestionBank();
    string cmd;

    cout << "Welcome to PPALMS\n" << endl;
    cout << "Commands:" << endl;
    cout << "  path <file_path>              Changes the current input file path" << endl;
    cout << "                                   e.g., path: ./project.cpp" << endl;
    cout << "  lms <lms>                     Changes the intended LMS target" << endl;
    cout << "                                   (Canvas, Moodle, or Blackboard)" << endl;
    cout << "  type <question_type>          Changes question type to generate" << endl;
    cout << "                                   (FITB, MC, or rearrange)" << endl;
    cout << "  mutations <mutations>         Changes number of questions to generate" << endl;
    cout << "                                   (Integer between 1 and 100)" << endl;
    cout << "  lines <line_tuples> ... end   Changes line tuples to generate from" << endl;
    cout << "                                   e.g., lines: 1-2 6 9 45-48 end" << endl;
    cout << "                                   Note: Must end with \"end\"" << endl;
    cout << "  generate                       Generate questions with current settings" << endl;
    cout << "  erase                          Erase all generated questions" << endl;
    cout << "  export                         Exports saved questions to qti.txt" << endl;
    cout << "  exit                           Exits PPALMS\n" << endl;

    while(1) {
        cout << "Command: ";
        cin >> cmd;
        
        if(cmd.compare("path") == 0) {
            string path;
            cin >> path;
            if(settings->SetPath(path) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Could not set path. --" << endl;
            }
        }
        else if(cmd.compare("lms") == 0) {
            string lms;
            cin >> lms;
            if(settings->SetLMS(lms) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Could not set LMS. --" << endl;
            }
        }
        else if(cmd.compare("type") == 0) {
            string type;
            cin >> type;
            if(settings->SetType(type) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Could not set question type. --" << endl;
            }
        }
        else if(cmd.compare("mutations") == 0) {
            int mutations;
            cin >> mutations;
            if(settings->SetMutations(mutations) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Could not set mutations. --" << endl;
            }
        }
        else if(cmd.compare("lines") == 0) {
            vector<vector<int>> line_nums;
            string lines;

            while(cin >> lines) {
                if(lines.compare("end") == 0) {
                    break;
                }

                vector<int> tuple;
                int ind;

                if((ind = lines.find("-")) != string::npos) {
                    tuple.push_back(stoi(lines.substr(0, ind)));
                    tuple.push_back(stoi(lines.substr(ind + 1, lines.size() - ind - 1)));
                }
                else {
                    tuple.push_back(stoi(lines));
                }

                line_nums.push_back(tuple);
            }

            if(settings->SetLines(line_nums) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Could not set lines. --" << endl;
            }
        }
        else if(cmd.compare("generate") == 0) {
            if(bank->AddQuestions(generator->GenerateQuestions(settings)) == 0) {
                cout << "-- Success --" << endl;
            }
            else {
                cout << "-- Failure: Cannot generate questions. --" << endl;
            }
        }
        else if(cmd.compare("erase") == 0) {
            bank->EraseQuestions();
            cout << "-- Success --" << endl;
        }
        else if(cmd.compare("export") == 0) {
            int ret = bank->ExportQuestions();
            if(ret == 1)
                cout << "-- Success --" << endl;
            else
                cout << "-- Failure: Could not output to a file. --" << endl;
        }
        else if(cmd.compare("exit") == 0) {
            break;
        }
    }

    delete settings;
    delete generator;
    delete bank;
}
