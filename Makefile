CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = main.o tokenizer.o treeNode.o parser.o tseitinTransformer.o solver.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = sat

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
