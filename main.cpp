/*Lab Work 6 - Bogdan Szasz - 30424
* Multi-way Trees
* 
* ASSUMPTION: The keys of the nodes are a continuous series (the nodes are denoted by 1, 2, 3, 4, 5, 6 etc.)
*
* The T2 tree is created by traversing the T1 tree. As we visit every node, we copy every node into T2 tree.
* For every node that is inserted into T2 tree, we create an edge, except the root. Every node has an edge that leads to a higher level
* The current node is the child, and we get the parent from traversing T1.
* 
*/

#include <iostream>
#include <cstdlib>
#include <vector>

typedef int KeyT;
const KeyT VOID_KEY = -1;

//R1 node - key and parentKey
class R1Node {
private:
	KeyT key;
	KeyT parentNodeKey;
	
public:
	R1Node() {
		this->key = VOID_KEY;
		this->parentNodeKey = VOID_KEY;
	}

	R1Node(KeyT key, KeyT parentNodeKey) {
		this->key = key;
		this->parentNodeKey = parentNodeKey;
	}
	
	void setKeys(KeyT key, KeyT parentKey) {
		this->key = key;
		this->parentNodeKey = parentKey;
	}

	KeyT getKey() const {
		return this->key;
	}

	KeyT getParentNodeKey() const {
		return this->parentNodeKey;
	}

};

typedef R1Node* R1NodeArrayT;

//R1 tree - array of nodes gotten by keys
class R1Tree {
	
	R1NodeArrayT listOfNodes;
	unsigned int numberOfNodes;
	
public:
	R1Tree(const std::vector<KeyT> &listOfParentKeys) {				//const to ensure the input vector is unchanged
		this->numberOfNodes = listOfParentKeys.size();
		//this->listOfNodes = (R1Node*)malloc(sizeof(R1Node) * this->numberOfNodes);	
		this->listOfNodes = new R1Node[this->numberOfNodes];
		for (unsigned int i = 0; i < this->numberOfNodes; i++) {
			this->listOfNodes[i].setKeys(i + 1, listOfParentKeys[i]);		//setting the keys for each node in R1Tree
		}
	}

	R1Node* getNode(KeyT key) {
		return this->listOfNodes + (key - 1);
	}

	unsigned int getNumberOfNodes() {
		return this->numberOfNodes;
	}

	R1NodeArrayT & getNodeArray() {
		return this->listOfNodes;
	}

	void printListOfParents(std::ostream& output) {
		for (unsigned int i = 0; i < this->numberOfNodes; i++) {
			output << this->listOfNodes[i].getKey() << " " 
				   << this->listOfNodes[i].getParentNodeKey() 
				   << std::endl;
		}
	}
};


//Forward declaration of R2Node, so that we can use it in the declaration of R2ArrayOfChildren
class R2Node;

typedef R2Node* R2NodePtr;
typedef R2Node** R2NodePtrArray;
//remove danger!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class R2ArrayOfNodes {
	R2NodePtrArray array;
	int size;

public:
	R2ArrayOfNodes() {
		this->array = NULL;
		this->size = 0;
	}

	~R2ArrayOfNodes() {
		if (this->array != NULL){
			for (int i = 0; i < size; i++) {
				delete(this->array[i]);
			}
			delete[] this->array;
			//for safety we reinitialize
			this->array = NULL; 
			this->size = 0;
		}
	}

	int getSize() {
		return this->size;
	}

	R2NodePtr getChild(KeyT key) {
		return this->array[key];
	}

	void addChild(R2NodePtr newChild) {
		if (this->array == NULL) {
			this->array = new R2NodePtr[1];
			this->array[0] = newChild;
			this->size++;
		}
		else {
			R2NodePtrArray temp = new R2NodePtr[(this->size) + 1];
			for (int i = 0; i < this->size; i++) {
				temp[i] = this->array[i];
			}
			temp[this->size] = newChild;
			delete[] this->array;
			this->array = temp;
			this->size++;
		}
	}
};

//R2 multi-way tree node full declaration
class R2Node{
	KeyT key;
	R2ArrayOfNodes children;
	std::vector<R2NodePtr> niceChildren;

public:
	R2Node() {
		this->key = VOID_KEY;
		
	}

	void setKey(KeyT key) {
		this->key = key;
	}

	KeyT getKey() {
		return this->key;
	}

	int getNumberOfChildren() {
		return this->children.getSize();
	}

	R2NodePtr getChild(KeyT key) {
		return this->children.getChild(key);
	}

	void addChild(R2NodePtr childNode) {
		this->children.addChild(childNode);
	}

};

//forward declaration of R2Edge that helps us create the R2ArrayOfEdges class
class R2Edge;

typedef R2Edge* R2EdgePtr;
typedef R2Edge** R2EdgePtrArray;

class R2Edge {
	KeyT parentKey;
	KeyT childKey;

public:
	R2Edge(KeyT parent, KeyT child) {
		this->parentKey = parent;
		this->childKey = child;
	}
};

typedef R2Node* R2NodeArrayT;

class R2Tree {
	KeyT rootKey;
	R2NodeArrayT nodes;
	
	unsigned int numberOfNodes;

public:
	R2Tree() {
		this->rootKey = VOID_KEY;
		this->nodes = NULL;
		this->numberOfNodes = 0;
	}

	R2Node* getNode(KeyT key) {
		return this->nodes + (key - 1);
	}

	unsigned int getNumberOfNodes() {
		return this->numberOfNodes;
	}

	void allocateNodes(unsigned int size) {
		this->numberOfNodes = size;
		this->nodes = new R2Node[this->numberOfNodes];
	}

	void setRootByKey(KeyT key) {
		this->rootKey = key;
	}

	KeyT getRootKey() {
		return this->rootKey;
	}

	void addEdgeByKey(KeyT parentKey, KeyT childKey) {

		R2NodePtr parentNode = this->getNode(parentKey);
		R2NodePtr childNode = this->getNode(childKey);
		parentNode->setKey(parentKey);
		childNode->setKey(childKey);
		parentNode->addChild(childNode);
	}

	void print(std::ostream& output) {
		output << "The number of nodes is " << this->numberOfNodes << std::endl;
		for (int i = 0; i < this->numberOfNodes; i++) {
			output << "Node key " << this->nodes[i].getKey() << std::endl;
			output << "Number of children = " << this->nodes[i].getNumberOfChildren() << std::endl;
			for (int j = 0; j < this->nodes[i].getNumberOfChildren(); j++) {
				output << "Child of key " << i << " number " << this->nodes[i].getChild(j)->getKey() << std::endl;
			}
			output << std::endl;
		}
	}

	void prettyPrint(std::ostream& output) {
		R2NodePtr root = this->getNode(this->rootKey);
		this->prettyPrint(output, root, 0);
	}

	void prettyPrint(std::ostream& output, R2NodePtr node, int level) {
		for (int i = 0; i <= 3 * level; i++) {
			output << " ";
		}
		output << node->getKey() << std::endl;

		int numberOfChildren = node->getNumberOfChildren();
		if (numberOfChildren != 0) {
			for (int i = 0; i < numberOfChildren; i++) {
				this->prettyPrint(output, node->getChild(i), level + 1);
			}
		}
	}

	~R2Tree() {
		if (this->nodes != NULL) {
			//delete[] this->nodes;  BIG MEMORY LEAK!!!!!!
			this->numberOfNodes = 0;
			this->rootKey = VOID_KEY;
			this->nodes = NULL;
		}
	}
};

//binary tree node
class R3Node {
	KeyT key;
	R3Node* leftChild;			//firstChild in a normal BT
	R3Node* rightChild;			//nextSibling in a normal BT

public:
	R3Node() {
		this->key = VOID_KEY;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}

	R3Node(KeyT Key) {
		this->key = Key;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}

	KeyT getKey() {
		return this->key;
	}

	void setKey(KeyT key) {
		this->key = key;
	}

	void setRightChild(R3Node* Node) {
		this->rightChild = Node;
	}

	R3Node* getRightChild() {
		return this->rightChild;
	}

	void setLeftChild(R3Node* Node) {
		this->leftChild = Node;
	}

	R3Node* getLeftChild() {
		return this->leftChild;
	}

};

typedef R3Node* R3NodePtr;
typedef R3NodePtr R3NodeArrayT;

//binary tree class
class R3Tree {
	R3NodePtr root;
	R3NodeArrayT nodes;
	unsigned int numberOfNodes;

public:
	R3Tree() {
		this->root = NULL;
		this->nodes = NULL;
		this->numberOfNodes = 0;
	}

	void allocateNodes(int size) {
		this->nodes = new R3Node[size];
		this->numberOfNodes = size;
	}

	R3Node* getNode(KeyT key) {
		return this->nodes + (key - 1);
	}

	void setRootByKey(KeyT key) {
		this->root = this->getNode(key);
	}

	unsigned int getNumberOfNodes() {
		return this->numberOfNodes;
	}

	void print(std::ostream& output) {
		output << "The number of nodes is " << this->numberOfNodes << std::endl;
		
		if (this->root != NULL) {
			output << "The root key is: " << this->root->getKey() << std::endl;
		}

		for (int i = 0; i < this->numberOfNodes; i++) {
			output << "Node key " << this->nodes[i].getKey() << std::endl;
			//output << "Left child: " << this->nodes[i].getLeftChild() << " pointer " << this->nodes[i].getLeftChild()->getKey() << " key " << std::endl;
			//output << "Right child: " << this->nodes[i].getRightChild() << " pointer " << this->nodes[i].getRightChild()->getKey() << " key " << std::endl;
			
			R3Node* leftChild = this->nodes[i].getLeftChild();
			R3Node* rightChild = this->nodes[i].getRightChild();

			if (leftChild != NULL) {
				output << "Left child key: " << leftChild->getKey() << std::endl;
			}

			if (rightChild != NULL) {
				output << "Right child key: " << rightChild->getKey() << std::endl;
			}

			//output << "Left child: " << leftChild << std::endl;
			//output << "Right child: " << rightChild << std::endl;
			output << std::endl;
		}
	}

	void prettyPrint(std::ostream& output) {
		this->prettyPrint(output, this->root, 0);
	}

	void prettyPrint(std::ostream& output, R3Node* node, int level) {
		for (int i = 0; i <= 3 * level; i++) {
			output << " ";
		}
		output << node->getKey() << std::endl;

		R3Node* nextChild = node->getLeftChild();
		
		while (nextChild != NULL) {
				this->prettyPrint(output, nextChild, level + 1);
				nextChild = nextChild->getRightChild();
		}
	}

	~R3Tree() {
		this->root = NULL;
		if (this->nodes != NULL) { 
			delete[] this->nodes; 
		}
		this->nodes = NULL;
		this->numberOfNodes = 0;
	}


};

void TransformR1toR2(R1Tree& t1, R2Tree& t2) {
	R1NodeArrayT &t1Nodes = t1.getNodeArray(); 
	unsigned int numberOfNodes = t1.getNumberOfNodes();

	t2.allocateNodes(numberOfNodes);

	//adding all the edges and linking the nodes accordingly
	for (unsigned int i = 0; i < numberOfNodes; i++) {

		//helper variables
		const R1Node& currentT1Node = t1Nodes[i];
		KeyT currentParentKey = currentT1Node.getParentNodeKey();
		KeyT currentKey = currentT1Node.getKey();
		
		t2.getNode(i + 1)->setKey(currentKey);

		if (currentParentKey != VOID_KEY) {
			t2.addEdgeByKey(currentParentKey, currentKey);
		}
		else {
			t2.setRootByKey(currentKey);
		}
	}
}

void TransformR2toR3(R2Tree& t2, R3Tree& t3) {
	

	unsigned int numberOfNodes = t2.getNumberOfNodes();

	t3.allocateNodes(numberOfNodes);

	//adding all the edges and linking the nodes accordingly
	for (unsigned int i = 1; i < numberOfNodes + 1; i++) {			//copy all T2 nodes into T3
		KeyT initialNode2Key = t2.getNode(i)->getKey();
		t3.getNode(i)->setKey(initialNode2Key);				
	}
	
	for (int i = 1; i < numberOfNodes + 1; i++) {					//linking by going node by node
		R2NodePtr node2 = t2.getNode(i);							
		int numberOfChildren = node2->getNumberOfChildren();		//get the nodes in T2, the number of their children and their keys
		KeyT node2Key = node2->getKey();
		
		R3Node* node3 = t3.getNode(node2Key);

		if (numberOfChildren > 1) {									//we treat the first node
			
			KeyT firstChildKey = node2->getChild(0)->getKey();
			R3Node* node3FirstChild = t3.getNode(firstChildKey);	//the linking goes as it follows: leftChild becomes the first child in the binary tree (and the subsequential binary subtrees)
			node3->setLeftChild(node3FirstChild);					//the rightChild becomes the next child of the leftChild
			R3Node* node3CurrentChild = node3FirstChild;

			for (int j = 1; j < numberOfChildren; j++) {			//still linear algorithm, because this is proportional to the number of nodes. It is impossible for a R2 node to have n children
				KeyT nextChildKey = node2->getChild(j)->getKey();
				R3Node* node3NextChild = t3.getNode(nextChildKey);
				node3CurrentChild->setRightChild(node3NextChild);
				node3CurrentChild = node3NextChild;
			}
		}
	}
	t3.setRootByKey(t2.getRootKey());
}

int demo() {
	const std::vector<KeyT> listOfParents({ 2, 7, 5, 2, 7, 7, -1, 5, 2 });
	R1Tree* treeR1 = new R1Tree(listOfParents);
	
	treeR1->printListOfParents(std::cout);
	std::cout << std::endl << std::endl;
	
	std::cout << "T1: " << std::endl;
	R2Tree* treeR2 = new R2Tree();
	TransformR1toR2(*treeR1, *treeR2);
	treeR2->print(std::cout);
	treeR2->prettyPrint(std::cout);

	
	//T2 (R2->R3)
	R3Tree* treeR3 = new R3Tree();
	TransformR2toR3(*treeR2, *treeR3);
	std::cout << std::endl << std::endl << std::endl << "T2:" << std::endl;
	treeR3->print(std::cout);
	treeR3->prettyPrint(std::cout);


	delete(treeR1);
	delete(treeR2);
	delete(treeR3);

	return 0;
}

int main() {
	demo();
	return 0;
}