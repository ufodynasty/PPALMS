#ifndef QUESTION_H_
#define QUESTION_H_

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Question {
 public:
  string questionText;
  string type;
  vector<vector<string>> correctAnswers;
  vector<vector<string>> incorrectAnswers;
};

#endif  // QUESTION_H_
