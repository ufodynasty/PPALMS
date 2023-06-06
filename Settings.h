#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Settings {
 public:
  Settings();
  Settings(string path, string lms, string type, int mutations, vector<vector<int>> line_nums);
  string GetPath();
  string GetLMS();
  string GetType();
  int GetMutations();
  vector<vector<int>> GetLines();

  int SetPath(string path);
  int SetLMS(string lms);
  int SetType(string type);
  int SetMutations(int mutations);
  int SetLines(vector<vector<int>> lines);

 private:
  string path;
  string lms;
  string type;
  int mutations = 5;
  vector<vector<int>> line_nums;
};

#endif  // SETTINGS_H_
