all: twitter

.outputFolder:
	mkdir -p out

twitter: .outputFolder
	g++ -std=c++17 twitter.cpp -Wall -Wextra -Werror -o out/twitter
	./out/twitter
