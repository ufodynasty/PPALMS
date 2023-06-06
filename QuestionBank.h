#ifndef QUESTIONBANK_H_
#define QUESTIONBANK_H_

#include "Question.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class QuestionBank {
 public:
  int AddQuestions(vector<Question> questions);
  int ExportQuestions();
  void EraseQuestions();

 private:
  vector<Question> questions;
};

#endif  // QUESTIONBANK_H_