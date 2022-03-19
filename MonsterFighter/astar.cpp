#include "astar.h"
#include <iostream>
#include <algorithm>
#include <SDL.h>

Node::Node(vec2D _position, Node* _parent) {
	f = 0;
	g = 0;
	h = 0;
	position = _position;
	parent = _parent;
}




Astar::Astar(Node* _startNode, Node* _goalNode) {
	startNode = _startNode;
	goalNode = _goalNode;

	openList = std::vector<Node>();
	closedList = std::vector<Node>();

	openList.push_back(*startNode);
}

int Astar::min_value_in_list() {
	std::vector<int> openListVals = std::vector<int>();

	for (int i = 0; i < openList.size(); i++) {
		openListVals.push_back(openList[i].f);
	}
	int min = *std::min_element(openListVals.begin(), openListVals.end());
	auto itr = std::find(openListVals.begin(), openListVals.end(), min);
	if (itr != openListVals.end()) {
		return itr - openListVals.begin();
	}
	return -1;
}

Node* Astar::getNodeFromPosition(vec2D position) {
	for (int i = 0; i < openList.size(); i++) {
		if (openList[i].position.x == position.x && openList[i].position.y == position.y) {
			return &openList[i];
		}
	}
	return nullptr;
}

void Astar::updateOpenList(vec2D position, int G) {
	vec2D tmpVec = position;
	if (worldMatrix[tmpVec.x][tmpVec.y] == 0 || worldMatrix[tmpVec.x][tmpVec.y] == 3) {//no obstacles and not previously visited
		Node tmpNode = Node(tmpVec, &closedList[closedList.size() - 1]);
		tmpNode.g = tmpNode.parent->g + G;
		//tmpNode.h = (abs(goalNode->position.x - tmpVec.x) + abs(goalNode->position.y - tmpVec.y)) * 1000;//heuristic
		tmpNode.h = sqrt(abs(pow(goalNode->position.x - tmpVec.x, 2)) + abs(pow(goalNode->position.y - tmpVec.y, 2))) * 1000;//heuristic
		tmpNode.f = tmpNode.g + tmpNode.h;
		tmpNode.parent = &closedList[closedList.size() - 1];
		if (worldMatrix[tmpVec.x][tmpVec.y] == 3) {//the Node is in the open list
			Node* updateNode = getNodeFromPosition(tmpVec);
			int newG = G + closedList[closedList.size() - 1].g;
			if (newG < updateNode->g) {
				updateNode->parent = &closedList[closedList.size() - 1];
				updateNode->g = newG;
				updateNode->f = updateNode->g + updateNode->h;
			}
		}
		else {
			openList.push_back(tmpNode);
		}
	}
}

void Astar::getNeighbours() {
	Node currentNode = closedList[closedList.size() - 1];
	vec2D currentNodePos = currentNode.position;
	int xLimit = SCREEN_WIDTH / 10;
	int yLimit = SCREEN_HEIGHT / 10;
	//*reject neighbours IF POSITION is:-
	//1->out of bounds
	//2->if there is an obstacle-->worldMatrix[x][y]==1
	//3->if it exists in the closedList-->-->worldMatrix[x][y]==2

	//update the horizontal/vertical values
	if (currentNodePos.x + 1 < xLimit) { vec2D position = { currentNodePos.x + 1,currentNodePos.y }; updateOpenList(position, 10); }
	if (currentNodePos.x - 1 >= 0) { vec2D position = { currentNodePos.x - 1,currentNodePos.y }; updateOpenList(position, 10); }
	if (currentNodePos.y + 1 < yLimit) { vec2D position = { currentNodePos.x ,currentNodePos.y + 1 }; updateOpenList(position, 10); }
	if (currentNodePos.y - 1 >= 0) { vec2D position = { currentNodePos.x ,currentNodePos.y - 1 }; updateOpenList(position, 10); }
	//update the diagonal values
	if (currentNodePos.x - 1 >= 0 && currentNodePos.y - 1 >= 0) { vec2D position = { currentNodePos.x - 1 ,currentNodePos.y - 1 }; updateOpenList(position, 14); }
	if (currentNodePos.x + 1 < xLimit && currentNodePos.y - 1 >= 0) { vec2D position = { currentNodePos.x + 1 ,currentNodePos.y - 1 }; updateOpenList(position, 14); }
	if (currentNodePos.x + 1 < xLimit && currentNodePos.y + 1 < yLimit) { vec2D position = { currentNodePos.x + 1 ,currentNodePos.y + 1 }; updateOpenList(position, 14); }
	if (currentNodePos.x - 1 >= 0 && currentNodePos.y + 1 < yLimit) { vec2D position = { currentNodePos.x - 1 ,currentNodePos.y + 1 }; updateOpenList(position, 14); }
}

void Astar::updateWorldMatrix() {
	for (int i = 0; i < closedList.size(); i++) {
		vec2D position = closedList[i].position;
		worldMatrix[position.x][position.y] = 2;
	}
	for (int x = 0; x < SCREEN_WIDTH / 10; x++) {
		for (int y = 0; y < SCREEN_HEIGHT / 10; y++) {
			if (worldMatrix[x][y] == 3) {
				worldMatrix[x][y] = 0;
			}
		}
	}
	for (int i = 0; i < openList.size(); i++) {
		vec2D position = openList[i].position;
		worldMatrix[position.x][position.y] = 3;
	}
}

bool Astar::checkWinCondition() {
	if (closedList[closedList.size() - 1].position.x == goalNode->position.x && closedList[closedList.size() - 1].position.y == goalNode->position.y) {
		return true;
	}
	else {
		return false;
	}
}

void Astar::cleanWorld() {
	for (int x = 0; x < SCREEN_WIDTH / 10; x++) {
		for (int y = 0; y < SCREEN_HEIGHT / 10; y++) {
			if (worldMatrix[x][y] == 2 || worldMatrix[x][y] == 3) {
				worldMatrix[x][y] = 0;
			}
		}
	}
	closedList.clear();
	openList.clear();
	openList.push_back(*startNode);
}

void Astar::update() {
	while (openList.size() > 0) {
		//Find the Lowest F value on the open List and push it towards the openList
		int indexOfMinFVal = min_value_in_list();
		closedList.push_back(openList[indexOfMinFVal]);//this will be the current node
		if (checkWinCondition()) { break; }
		openList.erase(openList.begin() + indexOfMinFVal);

		updateWorldMatrix();//take all the positions in closedList and update the worldMatrix
		getNeighbours();//update the open list with the neighbours of the current Node
	}
}

void Astar::render() {
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
	for (int i = 0; i < closedList.size(); i++) {
		SDL_Rect tmpRect = { closedList[i].position.x * 10,closedList[i].position.y * 10,10,10 };
		SDL_RenderFillRect(gRenderer, &tmpRect);
	}
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
	for (int i = 0; i < openList.size(); i++) {
		SDL_Rect tmpRect = { openList[i].position.x * 10,openList[i].position.y * 10,10,10 };
		SDL_RenderFillRect(gRenderer, &tmpRect);
	}

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_Rect tmpRect = { closedList[closedList.size() - 1].position.x * 10,closedList[closedList.size() - 1].position.y * 10,10,10 };
	SDL_RenderFillRect(gRenderer, &tmpRect);

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	tmpRect = { openList[openList.size() - 1].position.x * 10,openList[openList.size() - 1].position.y * 10,10,10 };
	SDL_RenderFillRect(gRenderer, &tmpRect);

	//cleanWorld();
}