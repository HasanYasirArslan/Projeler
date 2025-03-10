ALL: COMPILE RUN
 
COMPILE:
	g++ -I ./include/ -o ./lib/LinkedList.o -c ./src/LinkedList.cpp
	g++ -I ./include/ -o ./lib/ListNode.o -c ./src/ListNode.cpp
	g++ -I ./include/ -o ./lib/BinaryTree.o -c ./src/BinaryTree.cpp
	g++ -I ./include/ -o ./lib/Queue.o -c ./src/Queue.cpp
	g++ -I ./include/ -o ./lib/TreeNode.o -c ./src/TreeNode.cpp
	g++ -I ./include/ -o ./bin/program ./lib/TreeNode.o ./lib/Queue.o ./lib/BinaryTree.o ./lib/ListNode.o ./lib/LinkedList.o ./src/main.cpp
RUN:
	./bin/program