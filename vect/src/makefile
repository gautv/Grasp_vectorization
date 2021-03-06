# \file makefile
# \author Mohand Mezmaz
# \brief A generic makefile which automatically detects the files to compile and all the dependencies between these files.

BINARIES = ../bin/
SOURCES = ../src/
INCLUDES = ../include/
OBJECTS = $(shell ls ${SOURCES}*.cpp | sed "s/.cpp/.o/g" | sed "s/src/bin/g")
DEBUG = -g
MIC = -mmic -O2
VECTORIZED =  -qopt-report5  -fstrict-aliasing -qopt-report-phase=vec -vec-threshold0
OPTIONS = -Wall -Wno-deprecated -Wno-non-virtual-dtor -lm -I${INCLUDES}  ${MIC} ${VECTORIZED}   -qopt-report5 -qopt-report-phase=vec  -std=c++11

CXX = /opt/intel/bin/icc -openmp -fargument-noalias  -mmic -Wall -Wno-deprecated -Wno-non-virtual-dtor -O2 -qopt-report5 -I${INCLUDES} -std=c++11

#CXX = g++

${BINARIES}foudre: $(OBJECTS)
	$(CXX) $(OBJECTS) -o ${BINARIES}foudre -lpthread
${BINARIES}%.o: ${SOURCES}%.cpp
	$(CXX) -c ${SOURCES}$*.cpp -o ${BINARIES}$*.o
	echo -n ${BINARIES} > ${BINARIES}$*.d
	$(CXX) -MM ${SOURCES}$*.cpp $(OPTIONS)  >> ${BINARIES}$*.d
-include $(OBJECTS:.o=.d)
clean:
	rm -f ${BINARIES}foudre ${BINARIES}*.o ${BINARIES}*.d
