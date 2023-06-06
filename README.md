# PPALMS

## Unit Testing
Tests were created through the Google Tests development suite. To run the GoogleTests for PPALMS, run the following command on a linux terminal in the project directory:
```
make UnitTests
```
Then run one of the following:
```
./UnitTests
./UnitTests <test_suite>
```
The first line will run all possible tests, while the second will run tests for a given class by replacing <test_suite> with one of the following options:
```
settings
linegrabber
generator
questionbank
```

## Building
Run the following line on a linux terminal in the project directory:
```
make PPALMS
```

## Execution
```
./PPALMS
./PPALMS <file_path> <lms> <question_type> <mutations> <line_nums> ...
```
The first will run the system in the terminal and list relevant commands for use:
```
Welcome to PPALMS


Commands:
  path <file_path>              Changes the current input file path
                                   e.g., path: ./project.cpp
  lms <lms>                     Changes the intended LMS target
                                   (Canvas, Moodle, or Blackboard)
  type <question_type>          Changes question type to generate
                                   (FITB, MC, or rearrange)
  mutations <mutations>         Changes number of question mutations
                                   (Integer between 1 and 100)
  lines <line_tuples> ... end   Changes line tuples to generate from
                                   e.g., lines: 1-2 6 9 45-48 end
                                   Note: Must end with "end".
  generate                       Generate questions with current settings
  erase                          Erase all generated questions
  export                         Exports saved questions to qti.txt
  exit                           Exits PPALMS
```
You can change any of the settings while the system is running and continue to generate questions before exporting. Once all needed questions are generated, enterint the 'export' command will export them all into 'qti.txt' together. Therefore, the example general case of generating 100 each of two types of questions can be achieved through running the system through the terminal interface (./PPALMS).

The second command (./PPALMS <file_path> <lms> <question_type> <mutations> <line_nums> ...) will run the system once and generate sets of questions using the given arguments.

## Demonstrations

Video Demonstration for Terminal Interfaces: https://drive.google.com/file/d/1J8s6YkZBV-tSlraJa0MRqdsTjmIXbCTm/view?usp=share_link

The 'provided.txt' file is there as an example but any valid file consisting of text will work with PPALMS. 'provided.txt' has been included to show line numbers but any other file used will not show line numbers in the questions generated.

## GUI

The GUI version of PPALMS can be accessed in the /gui/PPALMS directory. It has its own relevant README and instructions for building there.
