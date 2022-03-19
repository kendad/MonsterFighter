#pragma once
#include "globalVariables.h"
#include <vector>

class Node {
public:
	Node();
	Node(vec2D _position, Node* _parent = nullptr);

	int f;
	int g;
	int h;
	vec2D position;
	Node* parent;
};

class Astar {
public:
	Astar(Node* _startNode, Node* _goalNode);
	void update();

	int min_value_in_list();//return the index of the object with the min F value
	void updateWorldMatrix();
	Node* getNodeFromPosition(vec2D poisition);
	void updateOpenList(vec2D psoition, int G);
	void getNeighbours();
	bool checkWinCondition();
	void cleanWorld();

	void render();

	Node* startNode;
	Node* goalNode;

	std::vector<Node> openList;
	std::vector<Node> closedList;
};
