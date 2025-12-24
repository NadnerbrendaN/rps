// 
// Copyright (C) 2025 NadnerbrendaN
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include <map>
#include <ctime>
#include <deque>
#include <string>
#include <vector>
#include <iostream>

const int num = 5;
const int context_lengths[] = {2, 3, 4, 5, 6};
std::map<std::deque<std::string>, std::vector<std::string>> chain;

void add(std::deque<std::string>& context, std::string next, int length) {
	if (context.size() == length) {
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

	std::deque<std::string> contexts[num];

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

		std::string out[num];
		std::string final_out;
		for (int i = 0; i < num; ++i) {
			out[i] = gen(contexts[i]);
			if (out[i] == "\n") {
				std::string outs[] = {"rock", "paper", "scissors"};
				out[i] = outs[std::rand() % 3];
			} else {
				final_out = out[i];
			}
		}
		if (final_out == "") {
			std::string outs[] = {"rock", "paper", "scissors"};
			final_out = outs[std::rand() % 3];
		}
		std::cout << "Bot: " << final_out << "\n";
		if (in == "rock" && final_out == "scissors" || in == "paper" && final_out == "rock" || in == "scissors" && final_out == "paper") {
			score++;
            std::cout << "\033[1;32mPlayer wins\033[0;0m\n";
		} else if (final_out == "rock" && in == "scissors" || final_out == "paper" && in == "rock" || final_out == "scissors" && in == "paper") {
			bot_score++;
            std::cout << "\033[1;31mBot wins\033[0;0m\n";
		} else {
            std::cout << "\033[0;33mTie\033[0;0m\n";
        }

		for (int i = 0; i < num; ++i) {
			add(contexts[i], teach, context_lengths[i]);
		}
		
		std::cout << "------\nRound " << ++rounds << "\n";
		std::cout << "Player score: " << score << "\n";
		std::cout << "Bot score: " << bot_score << "\n";
	}

	return 0;
}
