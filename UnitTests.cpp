#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "Generator.h"
#include "LineGrabber.h"
#include "Settings.h"
#include "Question.h"
#include "QuestionBank.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    if (argc == 2) {
        std::string test_suite = argv[1];
        if (test_suite.compare("settings") == 0) {
            ::testing::GTEST_FLAG(filter) = "SettingsTests.*";
        } else if (test_suite.compare("linegrabber") == 0) {
            ::testing::GTEST_FLAG(filter) = "LineGrabberTests.*";
        } else if (test_suite.compare("generator") == 0) {
            ::testing::GTEST_FLAG(filter) = "GeneratorTests.*";
        } else if (test_suite.compare("questionbank") == 0) {
            ::testing::GTEST_FLAG(filter) = "QuestionBankTests.*";
        } else if (test_suite.compare("all") == 0) {
            ::testing::GTEST_FLAG(filter) = "*";
        } else {
            cout << "Usage: ./UnitTests <test_suite>" << endl;
            exit(-1);
        }
    } else if (argc > 2) {
        cout << "Usage: ./UnitTests <test_suite>" << endl;
        exit(-1);
    }
    
    return RUN_ALL_TESTS();
}

// Test Case(s): SETTINGS-01 through SETTINGS-04
TEST(SettingsTests, DefaultConstructor) {
    Settings *settings = new Settings();
    //Assert
    EXPECT_EQ("NULL", settings->GetPath());
    EXPECT_EQ("NULL", settings->GetLMS());
    EXPECT_EQ("NULL", settings->GetType());
    EXPECT_EQ(5, settings->GetMutations());

    delete settings;
}

// Test Case(s): SETTINGS-05 through SETTINGS-09
TEST(SettingsTests, ParameterizedConstructor) {

    vector<vector<int>> line_nums;
    vector<int> t1, t2;
    t1.push_back(1);
    t2.push_back(3);
    t2.push_back(5);
    line_nums.push_back(t1);
    line_nums.push_back(t2);
    Settings *settings = new Settings("./LineGrabber.cpp", "Canvas", "rearrange", 20, line_nums);
    
    EXPECT_EQ("./LineGrabber.cpp", settings->GetPath());
    EXPECT_EQ("Canvas", settings->GetLMS());
    EXPECT_EQ("rearrange", settings->GetType());
    EXPECT_EQ(20, settings->GetMutations());
    EXPECT_EQ(line_nums, settings->GetLines());

    delete settings;
}

// Test Case(s): SETTINGS-10 through SETTINGS-11
TEST(SettingsTests, Setters) {
    Settings *settings = new Settings();
    vector<vector<int>> line_nums;
    vector<int> t1, t2;
    t1.push_back(1);
    t2.push_back(3);
    t2.push_back(5);
    line_nums.push_back(t1);
    line_nums.push_back(t2);
    
    settings->SetPath("./LineGrabber.cpp");
    settings->SetLMS("Canvas");
    settings->SetType("rearrange");
    settings->SetMutations(10);
    settings->SetLines(line_nums);

    EXPECT_EQ("./LineGrabber.cpp", settings->GetPath());
    EXPECT_EQ("Canvas", settings->GetLMS());
    EXPECT_EQ("rearrange", settings->GetType());
    EXPECT_EQ(10, settings->GetMutations());
    EXPECT_EQ(line_nums, settings->GetLines());

    delete settings;
}

// Test Case(s): GENERATOR-01
TEST(GeneratorTests, CatchInvalidPath) {
    vector<vector<int>> line_nums;
    vector<int> t1; 
    vector<int> t2; 
    t1.push_back(1);
    t2.push_back(3);
    t2.push_back(5);
    line_nums.push_back(t1);
    line_nums.push_back(t2);

    Generator* generator = new Generator();
    Settings* settings = new Settings(" ", "Canvas", "rearrange", 20, line_nums);
    EXPECT_EQ(0, generator->GenerateQuestions(settings).size());     // should return a 0 lenth vector when path is invalid
    delete generator;
    delete settings;
}

// Test Case(s): GENERATOR-02 and GENERATOR-03
TEST(GeneratorTests, CatchInvalidType) {
    vector<vector<int>> line_nums;
    vector<int> t1; 
    vector<int> t2; 
    t1.push_back(1);
    t2.push_back(3);
    t2.push_back(5);
    line_nums.push_back(t1);
    line_nums.push_back(t2);

    Generator* generator = new Generator();
    Settings* settings = new Settings("./LineGrabber.cpp", "Canvas", " ", 20, line_nums);
    EXPECT_EQ(0, generator->GenerateQuestions(settings).size());       // should return a 0 lenth vector when type is not rearrange(in ver.1)
    delete generator;
    delete settings;
}

// Test Case(s): GENERATOR-04
TEST(GeneratorTests, CatchEmptyFile) {
    Generator* generator = new Generator();
    Settings* settings = new Settings("./LineGrabber.cpp", "Canvas", "rearrange", 20, vector<vector<int>>());
    EXPECT_EQ(0, generator->GenerateQuestions(settings).size());       // should return a 0 length vector when file is blank
    
    settings->SetType("FITB");
    EXPECT_EQ(0, generator->GenerateQuestions(settings).size());       // should return a 0 length vector when file is blank

    delete generator;
    delete settings;
}

// Test Case(s): GENERATOR-05
TEST(GeneratorTests, ValidSettings) {
    vector<vector<int>> line_nums;
    vector<int> t1; 
    vector<int> t2; 
    t1.push_back(1);
    t2.push_back(3);
    t2.push_back(5);
    line_nums.push_back(t1);
    line_nums.push_back(t2);

    Generator* generator = new Generator();
    Settings* settings = new Settings("./LineGrabber.cpp", "Canvas", "rearrange", 20, line_nums);
    EXPECT_GT(generator->GenerateQuestions(settings).size(), 0);

    settings->SetType("FITB");
    EXPECT_GT(generator->GenerateQuestions(settings).size(), 0);

    settings->SetType("MC");
    EXPECT_GT(generator->GenerateQuestions(settings).size(),0);

    delete generator;
    delete settings;
}

// Test Case(s): GRABBER-01 and GRABBER-02
TEST(LineGrabberTests, InvalidArguments) {
    LineGrabber* grabber = new LineGrabber();
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;

    lines = grabber->GrabLines("NULL", line_nums);              // Given file path is invalid.
    EXPECT_EQ(0, lines.size());                                 // lines should be empty.
    
    lines = grabber->GrabLines("empty.txt", line_nums);         // File is empty.
    EXPECT_EQ(0, lines.size());

    delete grabber; 
}

// Test Case(s): GRABBER-03
TEST(LineGrabberTests, SingleValBelowLB) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<int> line_tuple2;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;
    string line;

    line_tuple.push_back(-1);
    line_tuple2.push_back(0);
    line_nums.push_back(line_tuple);
    line_nums.push_back(line_tuple2);
    lines = grabber->GrabLines("numbers.txt", line_nums);       // line_nums contains invalid line numbers.
    EXPECT_EQ(0, lines.size());                                 // lines should be empty.
    delete grabber; 
}

// Test Case(s): GRABBER-04
TEST(LineGrabberTests, TupleBelowLB) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;
    string line;

    line_tuple.push_back(-1);
    line_tuple.push_back(1);
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums);      // line_nums contains a single valid number.
    EXPECT_EQ(1, lines.size());                                // lines should hold one vector of one string.
    delete grabber;  
}

// Test Case(s): GRABBER-05
TEST(LineGrabberTests, OnLowerBound) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;
    string line;

    line_tuple.push_back(1);
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums); 
    EXPECT_EQ(1, lines.size());                                 // should be size 1 as the bounds are included in valid input range
    delete grabber; 
}

// Test Case(s): GRABBER-06
TEST(LineGrabberTests, FirstLineOfText) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;
    string buffer;

    ifstream fp;
    fp.open("numbers.txt");
    getline(fp, buffer);

    line_tuple.push_back(1);
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums);
    EXPECT_EQ(0, buffer.compare(lines.at(0).at(0)));            // lines should hold the first line of text from the file.
    delete grabber;
    fp.close();
}

// Test Case(s): GRABBER-07
TEST(LineGrabberTests, SingleValAboveUB) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<int> line_tuple2;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;

    line_tuple.push_back(15);
    line_tuple2.push_back(17);
    line_nums.push_back(line_tuple);
    line_nums.push_back(line_tuple2); 
    lines = grabber->GrabLines("numbers.txt", line_nums); 
    EXPECT_EQ(1, lines.size());                                 // only line 15 should be included, so size 1 expected
    delete grabber; 
}

// Test Case(s): GRABBER-09
TEST(LineGrabberTests, TupleAboveUB) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;

    line_tuple.push_back(15);
    line_tuple.push_back(17); 
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums); 
    EXPECT_EQ(1, lines.size());                                 // only line 15 should be included, so size 1 expected
    delete grabber;
}

// Test Case(s): GRABBER-08
TEST(LineGrabberTests, OnUpperBound) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;

    line_tuple.push_back(16);
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums); 
    EXPECT_EQ(0, lines.size());                                // 16 is outside valid input range for given file so should be size 0
    delete grabber;
}

// Test Case(s): GRABBER-09 through GRABBER-12
TEST(LineGrabberTests, MultipleTuples) {
    LineGrabber* grabber = new LineGrabber();
    vector<int> line_tuple;
    vector<vector<int>> line_nums;
    vector<vector<string>> lines;
    
    line_tuple.push_back(0);
    line_tuple.push_back(1);
    line_nums.push_back(line_tuple);
    line_tuple.clear();
    line_tuple.push_back(10);
    line_tuple.push_back(16);
    line_nums.push_back(line_tuple);
    lines = grabber->GrabLines("numbers.txt", line_nums);
    EXPECT_EQ(2, lines.size());                                     // lines should contain 2 tuples.
    EXPECT_EQ(1, lines.at(0).size());                               // First tuple should only contain 1 line (line 1).
    EXPECT_EQ(6, lines.at(1).size());                               // Second tuple should contain 6 lines (lines 10-15).

    for (int i = 0; i < lines.at(1).size(); i++) {
        EXPECT_EQ(10 + i, stoi(lines.at(1).at(i)));                 // Checks that the lines hold the correct values.
    }
    delete grabber;
}

// Test Case(s): BANK-01 and BANK-02
TEST(QuestionBankTests, EraseEmptyBank) {
    QuestionBank* bank = new QuestionBank();
    vector<Question> questions;
    Question question;
    vector<vector<string>> answers;
    vector<string> answer;

    EXPECT_EQ(0, bank->ExportQuestions());  // Newly initialized bank should be empty.
    bank->EraseQuestions();
    EXPECT_EQ(0, bank->ExportQuestions());  // Erase questions should not cause errors on empty banks.

    delete bank;
}

// Test Case(s): BANK-03
TEST(QuestionBankTests, AddBlankQuestion) {
    QuestionBank* bank = new QuestionBank();
    vector<Question> questions;
    Question question;
    vector<vector<string>> answers;
    vector<string> answer;

    bank->AddQuestions(questions);
    EXPECT_EQ(0, bank->ExportQuestions());     // Adding a blank questions vector should do nothing.

    delete bank;
}

// Test Case(s): BANK-04 and BANK-05
TEST(QuestionBankTests, AddAndRemoveQuestion) {
    QuestionBank* bank = new QuestionBank();
    vector<Question> questions;
    Question question;
    vector<vector<string>> answers;
    vector<string> answer;

    questions.push_back(question);
    bank->AddQuestions(questions);
    EXPECT_EQ(1, bank->ExportQuestions());     // Adding a single question should change size to 1.
    bank->EraseQuestions();
    EXPECT_EQ(0, bank->ExportQuestions());     // Removing the questions should change size to 0.
    questions.clear();

    delete bank;
}

// Test Case(s): BANK-06
TEST(QuestionBankTests, ExportSingleQuestion) {
    QuestionBank* bank = new QuestionBank();
    vector<Question> questions;
    Question question;
    vector<vector<string>> answers;
    vector<string> answer;

    question.type = "rearrange";
    question.questionText = "SecondLineOfText\nFirstLineOfText";
    answer.push_back("FirstLineOfText\nSecondLineOfText");
    answers.push_back(answer);
    question.correctAnswers = answers;
    questions.push_back(question);
    bank->AddQuestions(questions);
    EXPECT_EQ(1, bank->ExportQuestions());     // Question is exported successfully.

    delete bank;
}

// Test Case(s): BANK-07
TEST(QuestionBankTests, ExportMultipleQuestions) {
    QuestionBank* bank = new QuestionBank();
    vector<Question> questions;
    Question question;
    vector<vector<string>> answers;
    vector<string> answer;
    
    questions.push_back(question);
    bank->AddQuestions(questions);
    EXPECT_EQ(1, bank->ExportQuestions());            // qti.txt should contain 3 questions.

    delete bank;
}
