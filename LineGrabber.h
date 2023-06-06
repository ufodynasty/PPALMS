#ifndef LINEGRABBER_H_
#define LINEGRABBER_H_

#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

class LineGrabber {
 public:
  vector<vector<string>> GrabLines(string path, vector<vector<int>> line_nums);
};

#endif  // LINEGRABBER_H_
