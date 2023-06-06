PPALMS: project.o Generator.o LineGrabber.o Settings.o QuestionBank.o
	g++ -o $@ $^

UnitTests: UnitTests.o Generator.o LineGrabber.o Settings.o QuestionBank.o
	g++ -o $@ $^ -lgtest -lgtest_main -pthread
	
project.o: project.cpp
	g++ -c project.cpp

UnitTests.o: UnitTests.cpp
	g++ -c UnitTests.cpp

Generator.o: Generator.cpp Generator.h
	g++ -c Generator.cpp

LineGrabber.o: LineGrabber.cpp LineGrabber.h
	g++ -c LineGrabber.cpp

Settings.o: Settings.cpp Settings.h
	g++ -c Settings.cpp

QuestionBank.o: QuestionBank.cpp QuestionBank.h
	g++ -c QuestionBank.cpp

clean:
	rm -f *.o PPALMS UnitTests