RAPIDXML_FOLDER := "../rapidxml/rapidxml-1.13/"
EM_FOLDER := "./src/"
RAPIDXML_SOURCES := $(wildcard ../rapidxml/rapidxml-1.13/*.*pp)
EM_FILES := ${shell find ./src/ -name "*.*pp"}
TEST_FILES := ${shell find ./tests/ -name "*.*pp"}

emulator: $(EM_FILES)
	g++ $(EM_FILES) -std=c++20 -o emulator -I $(RAPIDXML_FOLDER)

rapidxml: $(RAPIDXML_SOURCES)
	g++ $(RAPIDXML_SOURCES) -std=c++20 -g -o rapidxml.o

test: 
	g++ $(TEST_FILES) -std=c++20 -o testrun -I "$(EM_FOLDER) $(RAPIDXML_FOLDER)"
	./testrun
