#include "Settings.h"

Settings::Settings() {
    this->path = "NULL";
    this->lms = "NULL";
    this->type = "NULL";
    this->mutations = 5;
}

Settings::Settings(string path, string lms, string type, int mutations, vector<vector<int>> line_nums) {
    this->path = path;
    this->lms = lms;
    this->type = type;
    this->mutations = mutations;
    this->line_nums = line_nums;
}

string Settings::GetPath() {
    return this->path;
}

string Settings::GetLMS() {
    return this->lms;
}

string Settings::GetType() {
    return this->type;
}

int Settings::GetMutations() {
    return this->mutations;
}

vector<vector<int>> Settings::GetLines() {
    return this->line_nums;
}

int Settings::SetPath(string path) {
    struct stat file_info;
    stat (path.c_str(), &file_info);

    // Checks to make sure the path is a file and not a directory.
    if(S_ISDIR(file_info.st_mode) != 0) {
        return 1;
    }

    this->path = path;
    return 0;
}

int Settings::SetLMS(string lms) {
    if(!(lms.compare("Canvas") == 0 || lms.compare("Moodle") == 0 || lms.compare("Blackboard") == 0)) {
        return 1;
    }

    this->lms = lms;
    return 0;
}

int Settings::SetType(string type) {
    if(!(type.compare("rearrange") == 0 || type.compare("FITB") == 0 || type.compare("MC") == 0)) {
        return 1;
    }

    this->type = type;
    return 0;
}

int Settings::SetMutations(int mutations) {
    if(mutations < 0 || mutations > 100) {
        return 1;
    }

    this->mutations = mutations;
    return 0;
}

int Settings::SetLines(vector<vector<int>> lines) {
    this->line_nums = lines;
    return 0;
}
