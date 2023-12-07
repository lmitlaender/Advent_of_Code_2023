#include "day6.h"

void Day7_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day7.txt");
	// Line = List of Hands
	// Order based on strength of each hand
	// Order strong to weak: A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
	// types (and strength ordering): five of a kind, four of a kind, Full House, Three of a kind, two pair, one pair, highest card
	// if same type: compare first card, take stronger, if same take second, take stronger, etc..



	std::map<int, std::vector<std::string>> hand_type_vectors{};
	std::map<std::string, int> hand_to_bid{};

	for(const auto& line : input_vector){
		std::string hand{};
		std::string bid{};
		std::istringstream stringstream{line};

		stringstream >> hand >> bid;
		hand_to_bid.insert(std::pair{hand, std::stoi(bid)});

		auto hand_type = this->get_hand_type(hand);

		if(!hand_type_vectors.contains(hand_type)){
			hand_type_vectors.insert(std::pair{hand_type, std::vector<std::string>{}});
		}
		hand_type_vectors[hand_type].push_back(hand);
	}

	int rank = 1;
	int total{0};
	for (auto& entry : hand_type_vectors){
		std::cout << "\n\n\n";
		std::sort(entry.second.begin(), entry.second.end(), hand_comparator);

		for (auto& hand : entry.second){
			total += hand_to_bid[hand] * rank;
			rank++;
		}
	}

	std::cout << "Day 7 Part 1: " << total;
}


void Day7_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day7.txt");


}


Day7_2023::hand_type Day7_2023::get_hand_type(const std::string& hand){
	std::map<char, int> card_count{};

	for(const auto& c : hand){
		if (card_count.contains(c)){
			card_count[c] += 1;
		} else {
			card_count.insert(std::pair{c, 1});
		}
	}

	if (card_count.size() == 1){
		return FIVE_OF_A_KIND;
	} else if (card_count.size() == 2){
		for(auto& element : card_count){
			if (element.second == 2 || element.second == 3){
				return FULL_HOUSE;
			}
		}
		return FOUR_OF_A_KIND;
	} else if (card_count.size() == 3){
		for(auto& element : card_count){
			if (element.second == 3){
				return THREE_OF_A_KIND;
			}
		}
		return TWO_PAIR;
	}  else if (card_count.size() == 4){
		return PAIR;
	}
	return HIGH;
}

bool Day7_2023::hand_comparator(const std::string& lhs, const std::string& rhs){
	std::map<char, int> char_to_cardtype {
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'T', 10},
		{'J', 11},
		{'Q', 12},
		{'K', 13},
		{'A', 14}
	};

	for(int i = 0; i < lhs.size(); i++){

		int card_type1 = char_to_cardtype[lhs[i]];
		int card_type2 = char_to_cardtype[rhs[i]];

		if (card_type1 != card_type2){
			return card_type1 < card_type2;
		}
	}
	return false;
}