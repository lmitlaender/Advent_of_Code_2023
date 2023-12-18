#include "day13.h"

void Day13_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day13.txt");

	std::vector<std::vector<std::string>> blocks{}; 
	blocks.emplace_back();
	int block_idx{ 0 };

	long long total{};

	for (auto& input : input_vector)
	{
		if (input.empty())
		{
			blocks.emplace_back();
			block_idx++;
			continue;
		}

		blocks[block_idx].emplace_back(input);
	}

	for (auto& block : blocks)
	{
		std::set<int> column_candidates{};
		std::set<int> row_candidates{};

		for (int i = 0; i < block[0].size() - 1; i++)
		{
			if (block[0][i] == block[0][i + 1])
			{
				bool candidate{ true };
				for(auto& line : block)
				{
					if (line[i] != line[i + 1])
					{
						candidate = false;
					}
				}
				if (candidate)
				{
					column_candidates.emplace(i);
				}
			}
		}

		for (int i = 0; i < block.size() - 1; i++)
		{
			if(block[i][0] == block[i + 1][0])
			{
				bool candidate{ true };
				for (int y = 1; y < block[i].size(); y++)
				{
					if (block[i][y] != block[i + 1][y])
					{
						candidate = false;
					}
				}
				if (candidate)
				{
					row_candidates.emplace(i);
				}
			}
		}

		total += this->get_result_for_block(block, column_candidates, row_candidates);
	}

	std::cout << "Part 1 Day 13: " << total << "\n";
}

void Day13_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day13.txt");

	std::vector<std::vector<std::string>> blocks{};
	blocks.emplace_back();
	int block_idx{ 0 };

	long long total{};

	for (auto& input : input_vector)
	{
		if (input.empty())
		{
			blocks.emplace_back();
			block_idx++;
			continue;
		}

		blocks[block_idx].emplace_back(input);
	}

	for (auto& block : blocks)
	{
		auto not_allowed = this->get_valid_candidate(block);

		int for_block{0};
		for (int line_idx = 0; line_idx < block.size(); line_idx++)
		{
			for(int char_idx = 0; char_idx < block[line_idx].size(); char_idx++)
			{
				block[line_idx][char_idx] = block[line_idx][char_idx] == '#' ? '.' : '#';

				std::set<int> column_candidates{};
				std::set<int> row_candidates{};

				for (int i = 0; i < block[0].size() - 1; i++)
				{
					if (block[0][i] == block[0][i + 1])
					{
						bool candidate{ true };
						for (auto& line : block)
						{
							if (line[i] != line[i + 1])
							{
								candidate = false;
							}
						}
						if (candidate && i != not_allowed.first)
						{
							column_candidates.emplace(i);
						}
					}
				}

				for (int i = 0; i < block.size() - 1; i++)
				{
					if (block[i][0] == block[i + 1][0])
					{
						bool candidate{ true };
						for (int y = 1; y < block[i].size(); y++)
						{
							if (block[i][y] != block[i + 1][y])
							{
								candidate = false;
							}
						}
						if (candidate && i != not_allowed.second)
						{
							row_candidates.emplace(i);
						}
					}
				}

				for_block = this->get_result_for_block(block, column_candidates, row_candidates);

				block[line_idx][char_idx] = block[line_idx][char_idx] == '#' ? '.' : '#';

				if (for_block > 0)
				{
					line_idx = block.size();
					break;
				}
			}
		}


		total += for_block;
	}

	std::cout << "Part 2 Day 13: " << total << "\n";
}

int Day13_2023::get_result_for_block(std::vector<std::string>& block, std::set<int>& column_candidates, std::set<int>& row_candidates)
{
	for (auto& candidate : column_candidates)
	{
		int to_check{ candidate >= static_cast<int>(block[0].size()) / 2 ? static_cast<int>(block[0].size()) - candidate - 2 : candidate };

		bool is_valid{ true };

		for (int i = 0; i <= to_check; i++)
		{
			for (auto& line : block)
			{
				if (line[candidate + i + 1] != line[candidate - i])
				{
					is_valid = false;
					i = to_check + 1;
					break;
				}
			}
		}

		if (is_valid)
		{
			return candidate + 1;
		}
	}

	for (auto& candidate : row_candidates)
	{
		int to_check{ candidate >= static_cast<int>(block.size()) / 2 ? static_cast<int>(block.size()) - candidate - 2: candidate };

		bool is_valid{ true };

		for (int i = 0; i <= to_check; i++)
		{
			for (int y = 0; y < block[candidate].size(); y++)
			{
				if (block[candidate + i + 1][y] != block[candidate - i][y])
				{
					is_valid = false;
					i = to_check + 1;
					break;
				}
			}
		}

		if (is_valid)
		{
			return 100 * (candidate + 1);
		}
	}

	return 0;
}

std::pair<int, int> Day13_2023::get_valid_candidate(std::vector<std::string>& block)
{
	std::set<int> column_candidates{};
	std::set<int> row_candidates{};

	for (int i = 0; i < block[0].size() - 1; i++)
	{
		if (block[0][i] == block[0][i + 1])
		{
			bool candidate{ true };
			for (auto& line : block)
			{
				if (line[i] != line[i + 1])
				{
					candidate = false;
				}
			}
			if (candidate)
			{
				column_candidates.emplace(i);
			}
		}
	}

	for (int i = 0; i < block.size() - 1; i++)
	{
		if (block[i][0] == block[i + 1][0])
		{
			bool candidate{ true };
			for (int y = 1; y < block[i].size(); y++)
			{
				if (block[i][y] != block[i + 1][y])
				{
					candidate = false;
				}
			}
			if (candidate)
			{
				row_candidates.emplace(i);
			}
		}
	}

	for (auto& candidate : column_candidates)
	{
		int to_check{ candidate >= static_cast<int>(block[0].size()) / 2 ? static_cast<int>(block[0].size()) - candidate - 2 : candidate };

		bool is_valid{ true };

		for (int i = 0; i <= to_check; i++)
		{
			for (auto& line : block)
			{
				if (line[candidate + i + 1] != line[candidate - i])
				{
					is_valid = false;
					i = to_check + 1;
					break;
				}
			}
		}

		if (is_valid)
		{
			return std::pair{candidate, -1};
		}
	}

	for (auto& candidate : row_candidates)
	{
		int to_check{ candidate >= static_cast<int>(block.size()) / 2 ? static_cast<int>(block.size()) - candidate - 2 : candidate };

		bool is_valid{ true };

		for (int i = 0; i <= to_check; i++)
		{
			for (int y = 0; y < block[candidate].size(); y++)
			{
				if (block[candidate + i + 1][y] != block[candidate - i][y])
				{
					is_valid = false;
					i = to_check + 1;
					break;
				}
			}
		}

		if (is_valid)
		{
			return std::pair{-1, candidate};
		}
	}
}