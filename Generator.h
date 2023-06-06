#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include "LineGrabber.h"
#include "Settings.h"
#include "Question.h"

using namespace std;

class Generator {
 public:
  Generator() {};
  vector<Question> GenerateQuestions(Settings* settings);

 private:
  vector<Question> GenerateRearrange(Settings* settings, vector<vector<string>> lines);
  vector<Question> GenerateFITB(Settings* settings, vector<vector<string>> lines);
  vector<Question> GenerateMC(Settings* settings, vector<vector<string>> lines);
};

#endif  // GENERATOR_H_
