#include <map>
#include <ctime>
#include <deque>
#include <string>
#include <vector>
#include <iostream>

const int context_length = 2;
std::map<std::deque<std::string>, std::vector<std::string>> chain;

void add(std::deque<std::string>& context, std::string next) {
	if (context.size() == context_length) {
		chain[context].push_back(next);
		context.pop_front();
	}
	context.push_back(next);
}

std::string gen(std::deque<std::string> context) {
	std::vector<std::string> next = chain[context];
	if (next.size() != 0) {
		return next[std::rand() % next.size()];
	} else {
		return "\n";
	}
}

int main() {
	int rounds = 0;
	int score = 0;
	int bot_score = 0;

	std::deque<std::string> context;

	std::srand(time(NULL));

	bool play = true;
	std::string in;
	while (play) {
		std::cout << "Player move: ";
		std::cin >> in;

		if (in == "quit" || in == "exit") {
			play = false;
			continue;
		}

		std::string teach = "\n";
		if (in == "rock") {
			teach = "paper";
		} else if (in == "paper") {
			teach = "scissors";
		} else if (in == "scissors") {
			teach = "rock";
		} else {
			std::cout << "input not recognized\n";
			continue;
		}

		std::string out = gen(context);
		if (out == "\n") {
			std::string outs[] = {"rock", "paper", "scissors"};
			out = outs[std::rand() % 3];
			std::cout << "(Picked Randomly)";
		}
		std::cout << "Bot: " << out << "\n";

		add(context, teach);
		
		std::cout << "------\nRound " << ++rounds << "\n";
		if (in == "rock" && out == "scissors" || in == "paper" && out == "rock" || in == "scissors" && out == "paper") {
			score++;
		}
		if (out == "rock" && in == "scissors" || out == "paper" && in == "rock" || out == "scissors" && in == "paper") {
			bot_score++;
		}
		std::cout << "Player score: " << score << "\n";
		std::cout << "Bot score: " << bot_score << "\n";
	}

	return 0;
}
