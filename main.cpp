#include <iostream>
#include <cstdlib>
#include <vector>

typedef int KeyT;

//R1 node
class R1Node {
private:
	KeyT key;
	KeyT parentNodeKey;
	
public:
	R1Node(KeyT key, KeyT parentNodeKey) {
		this->key = key;
		this->parentNodeKey = parentNodeKey;
	}
	
	KeyT getKey() {
		return this->key;
	}

	KeyT getParentNodeKey() {
		return this->parentNodeKey;
	}

};

//R1 tree
class R1Tree {
	std::vector<R1Node*> listOfNodes;

public:
	R1Tree(const std::vector<KeyT> &listOfParentKeys) {				//const to ensure the input vector is unchanged
		this->listOfNodes.resize(listOfParentKeys.size());			//& - used to ensure that we will not copy the whole vector, but only its reference
		for (int i = 0; i < listOfParentKeys.size(); i++) {
			listOfNodes[i] = new R1Node(i + 1, listOfParentKeys[i]);
		}
	}

	void printListOfParents(std::ostream& output) {
		for (int i = 0; i < this->listOfNodes.size(); i++) {
			output << this->listOfNodes[i]->getKey() << " " 
				   << this->listOfNodes[i]->getParentNodeKey() 
				   << std::endl;
		}
	}
};

//R2 multi-way tree node
class R2Node{
	KeyT key;
	std::vector<R2Node*> children;

	R2Node(KeyT key) {
		this->key = key;
	}

	void addChild(R2Node* node) {
		this->children.push_back(node);
	}
};

//binary tree node
class R3Node {
	KeyT key;
	R3Node* nextSibling;		//leftChild in a normal BT
	R3Node* firstChild;			//rightChild in a normal BT

	R3Node(KeyT Key) {
		this->key = Key;
	}

	void setNextSibling(R3Node* Node) {
		this->nextSibling = Node;
	}

	void setFirstChild(R3Node* Node) {
		this->firstChild = Node;
	}
};



int demo() {
	const std::vector<KeyT> listOfParents({ 2, 7, 5, 2, 7, 7, -1, 5, 2 });
	R1Tree treeR1(listOfParents);

	treeR1.printListOfParents(std::cout);

	return 0;
}

int main() {
	demo();
	return 0;
}