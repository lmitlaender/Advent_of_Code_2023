#include "day8.h"

// Day 8 Reminds me of a graph structure with a node having a set amount of left and right paths.
// At first I was thinking of a Tree with the left and right but since the left/right can point to a predecessor again I will go with a directional graph structure.
// I probably wont be using a standard adjacency list or 2D Matrix unless it's required in Part 2, but just pointers to the left and right.

void Day8_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day8.txt");

	std::map<std::string, Node> node_map{};
	std::map<std::string, std::pair<std::string, std::string>> connections{};
	std::string str{};

	for (int i = 2; i < input_vector.size(); i++)
	{
		std::istringstream string_stream{ this->input_vector[i] };
		std::string name{};
		std::string left_name{};
		std::string right_name{};

		string_stream >> name;
		node_map.insert(std::pair{ name, Node{name} });
		string_stream >> str >> str;
		left_name = str.substr(1, str.length() - 2);

		string_stream >> str;
		right_name = str.substr(0, str.length() - 1);

		connections.insert(std::pair{ name, std::pair{left_name, right_name} });
	}

	for (auto& map_pair : node_map)
	{
		Node* node = &map_pair.second;

		auto vertice_pair = connections[map_pair.first];
		node->left = &node_map[vertice_pair.first];
		node->right = &node_map[vertice_pair.second];
	}

	Node* node = &node_map["AAA"];
	int steps{};
	bool found{ false };

	while(!found)
	{
		for (auto& c : input_vector[0])
		{

			if (c == 'L')
			{
				node = node->left;
			} else
			{
				node = node->right;
			}

			steps++;

			if (node->id == "ZZZ")
			{
				found = true;
				break;
			}
		}
	}

	std::cout << "Day 8 2023 Part 1: " << steps << " steps\n";
}

void Day8_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day8.txt");

	std::vector<Node*> starting_nodes{};
	std::map<std::string, Node*> node_map{};
	std::map<std::string, std::pair<std::string, std::string>> connections{};
	std::string str{};

	for (int i = 2; i < input_vector.size(); i++)
	{
		std::istringstream string_stream{ this->input_vector[i] };
		std::string name{};
		std::string left_name{};
		std::string right_name{};

		string_stream >> name;
		Node* node = new Node { name };
		node_map.insert(std::pair{ name, node });

		if(name[2] == 'A')
		{
			starting_nodes.push_back(node);
		}

		string_stream >> str >> str;
		left_name = str.substr(1, str.length() - 2);

		string_stream >> str;
		right_name = str.substr(0, str.length() - 1);

		connections.insert(std::pair{ name, std::pair{left_name, right_name} });
	}

	std::cout << "Day 8 2023 Part 2: ";

	for (auto& map_pair : node_map)
	{
		Node* node = map_pair.second;

		auto vertice_pair = connections[map_pair.first];
		node->left = node_map[vertice_pair.first];
		node->right = node_map[vertice_pair.second];
	}

	std::vector<std::vector<int>> steps_to_zs{};

	// Find steps until node at start node again
	for(int i = 0; i < starting_nodes.size(); i++)
	{
		steps_to_zs.emplace_back();

		Node* node = starting_nodes[i];
		int steps{};
		bool found{ false };
		std::set<std::pair<int, std::string>> node_set{};

		while (!found)
		{
			int char_count{};
			for (const auto& c : input_vector[0])
			{
				char_count++;
				if (c == 'L')
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}

				steps++;

				if (node->id[2] == 'Z')
				{
					steps_to_zs[i].push_back(steps);
				}
				else if (node_set.contains(std::pair{ char_count, node->id }))
				{
					found = true;
					break;
				}
				node_set.insert(std::pair{ char_count, node->id });
			}
		}
	}

	// Through debugging found out that each node only reaches one z end before repeating, so this works.. otherwise would have to try through all the values probably.
	long long total{ 1 };

	for (int i = 0; i < steps_to_zs.size(); i++)
	{
		total = std::lcm(total, steps_to_zs[i][0]);
	}

	// Stupid Brute Force Solution
	/*while (!found)
	{
		for (auto& c : input_vector[0])
		{
			int at_z{};
			steps++;

			for(auto& node : starting_nodes)
			{
				if (c == 'L')
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}

				if (node->id[2] == 'Z')
				{
					at_z++;
				}
			}

			if (at_z >= 4)
			{
				std::cout << at_z;
			}
			if (at_z == starting_nodes.size())
			{
				found = true;
				break;
			}
		}
	}*/

	std::cout << "Day 8 2023 Part 2: " << total << " steps\n";
}

