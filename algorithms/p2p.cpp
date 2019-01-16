#include <ostream>
#include <iostream>
#include <vector>
#include <functional> 
#include <memory>
#include <utility>
#include <unordered_map>
#include <climits>

namespace utils{
	int current_id = 0;
	int size_hash = 32;
	int generate_hash() {
		current_id += 1;
		return current_id;
	}
}

class Node;
std::shared_ptr<Node> get_node(std::pair<int, std::string> & info_node );
void set_node(std::pair<int, std::string> & info_node ,std::shared_ptr<Node> & node);


class Node {
	public:
		std::string address;
		int id;
		std::pair<int, std::string> predecessor_id;
		std::vector<std::pair<int, std::string>> finger_table;
	Node() {
		auto new_id = utils::generate_hash();
		this->id = new_id;
		this->predecessor_id = std::make_pair(new_id, std::string());
		this->finger_table.reserve(utils::size_hash);
		for (int i = 0; i < utils::size_hash; i++) {
			auto pair = std::make_pair(0, std::string());
			this->finger_table.push_back(pair);
		}
		auto succ = std::make_pair(new_id, address);
		this->set_successor_id(succ);
	}

	Node(int id_, std::pair<int,std::string> predecessor_id_, std::vector<std::pair<int, std::string>> finger_table_): 
				id(id_), predecessor_id(predecessor_id_), finger_table(finger_table_) {};
	inline Node clone() {
		return Node(this->id, this->predecessor_id, this->finger_table);
	}
	inline void set_successor_id(std::pair<int,std::string> & info) {
		this->finger_table[0] = info;
	}
	inline std::pair<int,std::string> get_successor_id() {
		return this->finger_table[0];
	}
	inline std::vector<std::pair<int, std::string>> get_finger_table_from(std::pair<int, std::string> & info_node ) {
		auto id = info_node.first;
		if (this->id == id) {
			return this->finger_table;
		}
		std::shared_ptr<Node> found_node = get_node(info_node);
		return found_node->finger_table;
	}
	inline int distance(int id1, int id2) {
		return std::abs(id1 - id2);
	}

	void join(const std::shared_ptr<Node> & node_in) {
		//TODO remote search
		std::pair<int, std::string> info_node = node_in->search(this->id);
		auto new_successor = get_node(info_node);
		
		std::pair<int, std::string> new_predecessor_info = new_successor->predecessor_id;
		this->predecessor_id = new_predecessor_info;
		this->set_successor_id(info_node);
		auto my_info = std::make_pair(this->id, this->address);
		new_successor->predecessor_id = my_info;
		auto new_predecessor = get_node(new_predecessor_info);
		new_predecessor->set_successor_id(my_info);
		set_node(info_node, new_successor);
		set_node(new_predecessor_info, new_predecessor);

	}
	std::pair<int, std::string> search(int id) {
		bool found = true;
		//TODO add guard to check if it has been included in the network
		int id_to_get = this->id;
		//TODO ADD MY ADDRESS
		auto near_value = std::make_pair(this->id, this->address);
		auto dist = distance(id, near_value.first);
		while (found) {	
			auto finger_table = get_finger_table_from(near_value);
			found = false;
			for (auto id_table: finger_table) {
				if (id_table.first == 0)  {
					break;
				}
				auto new_dist = distance(id, id_table.first);
				if (new_dist < dist && id < id_table.first) {
					near_value = id_table;
					dist = new_dist;
					found=true;
				}	
			}
		}
		return near_value;
	}
	void set_up_finger_table() {
		//TODO update successor
		auto succ = this->get_successor_id();
		auto searcher = get_node(succ);
		for (int i = 1; i < utils::size_hash; i++) {
			//TODO  cambiar a UINT
			auto id_to_analyse = (this->id + (2 << (i - 1))) %  INT_MAX;
			auto new_entry = searcher->search(id_to_analyse);
			this->finger_table[i] = new_entry;
		}
	}
};

std::unordered_map<int, std::shared_ptr<Node>> nodes;
std::shared_ptr<Node> get_node(std::pair<int,std::string> & node) {
	return nodes[node.first];
}

void set_node(std::pair<int, std::string> & info_node ,std::shared_ptr<Node> & node) {
	nodes[node->id] = node;
}

std::ostream & operator<< (std::ostream  &strm, const Node &node) {
		return strm << "Node( my_id="<< node.id   <<" successor_id="<<node.finger_table[0].first <<  " predecessor_id="<<node.predecessor_id.first<< ")";
}
int main () {

	std::shared_ptr<Node> node = std::make_shared<Node>();
	std::shared_ptr<Node> node2 = std::make_shared<Node>();
	std::shared_ptr<Node> node3 = std::make_shared<Node>();
	std::shared_ptr<Node> node4 = std::make_shared<Node>();
	nodes[node->id] = node;
	node2->join(node);
	nodes[node2->id] = node2;
	node4->join(node);
	nodes[node4->id] = node4;
	node3->join(node);
	nodes[node3->id] = node3;
	std::cout << *node << "\n";
	std::cout << *node2 << "\n";
	std::cout << *node3 << "\n";
	std::cout << *node4 << "\n";
}
