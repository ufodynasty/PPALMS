#include "LineGrabber.h"
#include <string.h>
#include <stdio.h>

vector<vector<string>> LineGrabber::GrabLines(string path, vector<vector<int>> line_nums) {
    vector<vector<string>> set;

    ifstream fp;
    fp.open(path);

    if(fp.is_open()) {
        vector<string> all_lines;
        string line;

        // Reads in every line from the given file path.
        while(getline(fp, line)) {
            int noComment = line.find("//");
            if(noComment != std::string::npos) {
                all_lines.push_back(line.substr(0, noComment));
            }
            else {
                all_lines.push_back(line);
            }
        }

        fp.close();

        // Grabs all lines listed under line_nums.
        for(int i = 0; i < line_nums.size(); i++) {
            vector<string> tuple;
            int first = line_nums.at(i).at(0);
            int second = first;

            // If a second number exists in the tuple, second becomes that number.
            if(line_nums.at(i).size() == 2) {
                second = line_nums.at(i).at(1);
            }

            // Loop through all lines in a tuple or just a single value.
            for(int j = first; j <= second; j++) {
                if(j > 0 && j < all_lines.size() + 1) {
                    tuple.push_back(all_lines.at(j - 1));
                }
            }

            // Adds line tuple to the set of line tuples if the tuple is valid.
            if(tuple.size() > 0)
                set.push_back(tuple);
        }
    }
    else {
        // Error.
        cout << "Unable to open \"" << path << "\"" << endl;
    }

    return set;
}
