bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -o bin/testHashTable testHashTable.cpp
	
bin/testBSTree: testBSTree.cpp BSNode.h BSTree.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -o bin/testBSTree testBSTree.cpp

bin/testBSTreeDict: testBSTreeDict.cpp TableEntry.h Dict.h BSTreeDict.h BSNode.h
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -o bin/testBSTreeDict testBSTreeDict.cpp

	
clean:
	rm -rf *.o *.gch bin
