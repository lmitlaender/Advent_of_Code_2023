#include "day16.h"

void Day17_2023::Part1()
{
	this->input_vector = get_input("2023/Inputs/Day17.txt");
	constexpr node start_node{ 0, {1, 0}, 1, 0, 0 };
	constexpr node start_node2{ 0, {0, 1}, 1, 0, 0 };
	std::priority_queue<node, std::vector<node>, node_comparator> nodes{};
	nodes.push(start_node);
	nodes.push(start_node2);

	auto result = this->dijkstra_for_pos(nodes);

	//this->print_thing(nodes);
	std::cout << result << "\n\n";
}

void Day17_2023::Part2()
{
	this->input_vector = get_input("2023/Inputs/Day17.txt");
	constexpr node start_node{ 0, {1, 0}, 1, 0, 0 };
	constexpr node start_node2{ 0, {0, 1}, 1, 0, 0 };
	std::priority_queue<node, std::vector<node>, node_comparator> nodes{};
	nodes.push(start_node);
	nodes.push(start_node2);

	auto result = this->dijkstra_for_pos_part_2(nodes);

	//this->print_thing(nodes);
	std::cout << result << "\n\n";
}

int Day17_2023::dijkstra_for_pos(std::priority_queue<node, std::vector<node>, node_comparator>& queue)
{
	node next_shortest{};
	struct hasher {
		std::size_t operator() (const node& state) const {
			return state.x + state.y;
		}
	};

	std::unordered_set<node, hasher> node_set{};
	constexpr std::pair<int, int> left{ -1, 0 };
	constexpr std::pair<int, int> right{ 1, 0 };
	constexpr std::pair<int, int> up{ 0, -1 };
	constexpr std::pair<int, int> down{ 0, 1 };
	node curr;

	while(!queue.empty())
	{
		curr = queue.top();
		queue.pop();

		if (node_set.contains(curr))
		{
			continue;
		}

		node_set.insert(curr);

		if (curr.x == this->input_vector[0].size() - 1 && curr.y == this->input_vector.size() - 1)
		{
			return curr.cost;
		}

		// left
		if(curr.x - 1 > -1 && (curr.direction.first != -1 || curr.repeated_moves < 3) && curr.direction.first != 1)
		{
			node new_node{};
			new_node.x = curr.x - 1;
			new_node.y = curr.y;
			new_node.cost = curr.cost + (this->input_vector[curr.y][curr.x - 1] - '0');
			new_node.direction = left;
			if (curr.direction.first != -1)
			{
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			queue.push(new_node);
		}

		// right
		if (curr.x + 1 < this->input_vector[0].size() && (curr.direction.first != 1 || curr.repeated_moves < 3) && curr.direction.first != -1)
		{
			node new_node{};
			new_node.x = curr.x + 1;
			new_node.y = curr.y;
			new_node.cost = curr.cost + (this->input_vector[curr.y][curr.x + 1] - '0');
			new_node.direction = right;
			if (curr.direction.first != 1)
			{
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			queue.push(new_node);
		}

		// up
		if (curr.y - 1 > -1 && (curr.direction.second != -1 || curr.repeated_moves < 3) && curr.direction.second != 1)
		{
			node new_node{};
			new_node.x = curr.x;
			new_node.y = curr.y - 1;
			new_node.cost = curr.cost + (this->input_vector[curr.y - 1][curr.x] - '0');
			new_node.direction = up;
			if (curr.direction.second != -1)
			{
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			queue.push(new_node);
		}

		//down
		if (curr.y + 1 < this->input_vector.size() && (curr.direction.second != 1 || curr.repeated_moves < 3) && curr.direction.second != -1)
		{
			node new_node{};
			new_node.x = curr.x;
			new_node.y = curr.y + 1;
			new_node.cost = curr.cost + (this->input_vector[curr.y + 1][curr.x] - '0');
			new_node.direction = down;
			if (curr.direction.second != 1)
			{
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			queue.push(new_node);
		}
	}
}

int Day17_2023::dijkstra_for_pos_part_2(std::priority_queue<node, std::vector<node>, node_comparator>& queue)
{
	node next_shortest{};
	struct hasher {
		std::size_t operator() (const node& state) const {
			return state.x + state.y;
		}
	};

	std::unordered_set<node, hasher> node_set{};
	std::pair<int, int> left{ -1, 0 };
	std::pair<int, int> right{ 1, 0 };
	std::pair<int, int> up{ 0, -1 };
	std::pair<int, int> down{ 0, 1 };
	int max{ 10 };
	int min{ 4 };

	node curr;

	while (!queue.empty())
	{
		curr = queue.top();
		queue.pop();

		if (node_set.contains(curr))
		{
			continue;
		}

		node_set.insert(curr);

		if (curr.x == this->input_vector[0].size() - 1 && curr.y == this->input_vector.size() - 1 && curr.repeated_moves >= min)
		{
			return curr.cost;
		}

		// left
		if (curr.x - 1 > -1 && (curr.direction.first != -1 || curr.repeated_moves < max) && curr.direction.first != 1 )
		{
			node new_node;
			if (curr.direction.first != -1)
			{
				if (curr.repeated_moves < min)
				{
					goto right;
				}
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			new_node.x = curr.x - 1;
			new_node.y = curr.y;
			new_node.cost = curr.cost + (this->input_vector[curr.y][curr.x - 1] - '0');
			new_node.direction = left;

			queue.push(new_node);
		}

		// right
		right:
		if (curr.x + 1 < this->input_vector[0].size() && (curr.direction.first != 1 || curr.repeated_moves < max) && curr.direction.first != -1)
		{
			node new_node;
			if (curr.direction.first != 1)
			{
				if (curr.repeated_moves < min)
				{
					goto up;
				}
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			new_node.x = curr.x + 1;
			new_node.y = curr.y;
			new_node.cost = curr.cost + (this->input_vector[curr.y][curr.x + 1] - '0');
			new_node.direction = right;
			queue.push(new_node);
		}

		// up
		up:
		if (curr.y - 1 > -1 && (curr.direction.second != -1 || curr.repeated_moves < max) && curr.direction.second != 1)
		{
			node new_node;
			if (curr.direction.second != -1)
			{
				if (curr.repeated_moves < min)
				{
					goto down;
				}
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			new_node.x = curr.x;
			new_node.y = curr.y - 1;
			new_node.cost = curr.cost + (this->input_vector[curr.y - 1][curr.x] - '0');
			new_node.direction = up;
			queue.push(new_node);
		}

		//down
		down:
		if (curr.y + 1 < this->input_vector.size() && (curr.direction.second != 1 || curr.repeated_moves < max) && curr.direction.second != -1)
		{
			node new_node;
			if (curr.direction.second != 1)
			{
				if (curr.repeated_moves < min)
				{
					continue;
				}
				new_node.repeated_moves = 1;
			}
			else
			{
				new_node.repeated_moves = curr.repeated_moves + 1;
			}
			new_node.x = curr.x;
			new_node.y = curr.y + 1;
			new_node.cost = curr.cost + (this->input_vector[curr.y + 1][curr.x] - '0');
			new_node.direction = down;
			queue.push(new_node);
		}
	}
}


void Day17_2023::print_thing(std::vector<node>& visited)
{
	std::pair<int, int> left{ -1, 0 };
	std::pair<int, int> right{ 1, 0 };
	std::pair<int, int> up{ 0, -1 };
	std::pair<int, int> down{ 0, 1 };

	std::vector<std::vector<char>> print_array{};

	for (auto& line : this->input_vector)
	{
		print_array.emplace_back();
		for (auto& c : line)
		{
			(print_array.end() - 1)->emplace_back('.');
		}
	}


	for (auto& point : visited)
	{
		if (point.direction.first == -1)
		{
			print_array[point.y][point.x] = '<';
		}
		else if (point.direction.first == 1)
		{
			print_array[point.y][point.x] = '>';
		}
		else if (point.direction.second == 1)
		{
			print_array[point.y][point.x] = 'v';
		} else if (point.direction.second == -1)
		{
			print_array[point.y][point.x] = '^';
		}
	}

	std::string result{};

	for (auto& line : print_array)
	{
		std::cout << "\n";
		for (auto& c : line)
		{
			std::cout << c;
		}
	}
}