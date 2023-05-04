all:
	g++ -o fgqueue -Wall -Wextra -Wpedantic *.cpp  -lpthread -fsanitize=thread
