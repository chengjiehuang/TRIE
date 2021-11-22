//
//  trie.cpp
//
//  Created by Chengjie Huang on 22/11/21.
//

#include <iostream>
#include <vector>

#define INT_BIT_SIZE 32

// TRIE Node
struct Node {
    int value;
    Node* children[2];
};

Node* create_a_new_node() {
    Node* newNode = new Node;
    newNode->value = 0;
    newNode->children[0] = nullptr;
    newNode->children[1] = nullptr;
    return newNode;
}

void insert(Node* root, int val) {
    Node* temp = root;
    for (int i = INT_BIT_SIZE - 1; i >= 0; --i) {
	bool current_bit = (val & (1 << i));

	if (temp->children[current_bit] == nullptr)
	    temp->children[current_bit] = create_a_new_node();

	temp = temp->children[current_bit];
    }

    temp->value = val;
}

int find_min_xor(Node* root, int key) {
    Node* temp = root;
    for (int i = INT_BIT_SIZE - 1; i >= 0; --i) {
	bool current_bit = (key & (1 << i));

	if (temp->children[current_bit] != nullptr)
	    temp = temp->children[current_bit];
	else if (temp->children[1 - current_bit] != nullptr)
	    temp = temp->children[1 - current_bit];
    }
    return key ^ temp->value;
}

std::vector<int32_t> minXOR(const std::vector<int32_t>& input) {
    std::vector<int32_t> ret;
    ret.reserve(input.size());
    if (input.empty()) return ret;

    Node* root = create_a_new_node();
    ret.push_back(input[0]);
    insert(root, input[0]);

    if (input.size() == 1) return ret;

    for (size_t i = 1; i < input.size(); ++i) {
	ret.push_back(find_min_xor(root, input[i]));
	insert(root, input[i]);
    }
    return ret;
}

int main() {
    std::vector<int32_t> arr = {26, 10, 4, 2};
    auto ret = minXOR(arr);
    for (auto i : ret) {
	std::cout << i << std::endl;
    }
    return 0;
}

