ALL: COMPILE RUN
 
COMPILE:
	g++ -I ./include/ -o ./lib/Dna.o -c ./src/Dna.cpp
	g++ -I ./include/ -o ./lib/Kromozom.o -c ./src/Kromozom.cpp
	g++ -I ./include/ -o ./lib/Gen.o -c ./src/Gen.cpp
	g++ -I ./include/ -o ./bin/program ./lib/Gen.o ./lib/Kromozom.o ./lib/Dna.o ./src/main.cpp
RUN:
	./bin/program