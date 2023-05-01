TARGET:../bin/main

../bin/commons.o:../src/commons.cpp
	g++ -std=c++17 -c -I commons -o ../bin/commons.o ../src/commons.cpp

../bin/Database.o:../src/Database.cpp
	g++ -std=c++17 -c -I Database -o ../bin/Database.o ../src/Database.cpp

../bin/DatabaseManager.o:../src/DatabaseManager.cpp
	g++ -std=c++17 -c -I DatabaseManager -o ../bin/DatabaseManager.o ../src/DatabaseManager.cpp

../bin/QueryParser.o:../src/QueryParser.cpp
	g++ -std=c++17 -c -I QueryParser -o ../bin/QueryParser.o ../src/QueryParser.cpp

../bin/Storage.o:../src/Storage.cpp
	g++ -std=c++17 -c -I Storage -o ../bin/Storage.o ../src/Storage.cpp

../bin/main.o:../main.cpp
	g++ -std=c++17 -c -I main -o ../bin/main.o ../main.cpp

../bin/main:../bin/commons.o ../bin/main.o ../bin/Database.o ../bin/DatabaseManager.o ../bin/QueryParser.o ../bin/Storage.o
	g++ -std=c++17 -o ../bin/main ../bin/commons.o ../bin/main.o ../bin/Database.o ../bin/DatabaseManager.o ../bin/QueryParser.o ../bin/Storage.o

remove:
	rm -f ../bin/*.o
clean:
	make remove
	rm -f ../bin/main
