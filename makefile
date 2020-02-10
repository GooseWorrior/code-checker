CXX = g++
CXXFLAG = -std=c++14 -Wall -MMD
EXEC = checker
OBJECTS = main.o fileInfo.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}