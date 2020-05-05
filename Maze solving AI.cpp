#include<iostream>
#include<queue>
using namespace std;

class node {
public:
	int connection[4];
	void add_connection(int top, int left, int buttom, int right) {
		connection[0] = top;
		connection[1] = left;
		connection[2] = buttom;
		connection[3] = right;
	}
};
class maze {
private:
	node* node_list;
	int maze_width;
	int maze_height;
	int no_node;

public:
	maze(int width, int hight) {
		no_node = width * hight;
		maze_width = width;
		maze_height = hight;
		node_list = new node [no_node];  

		for (int i = 0; i != no_node; i++) {

			int top = i - maze_width;
			int left = i - 1;
			int buttom = i + maze_width;
			int right = i + 1;

			if ((right / maze_width) > (i / maze_width)) {
				right = -1;
			}
			if ((i / maze_width) > (left / maze_width)) {
				left = -1;
			}
			if (top < 0) {
				top = -1;
			}
			if (buttom >= no_node) {
				buttom = -1;
			}
			
		node_list[i].add_connection(top, left, buttom, right);
			
		}
	}


	void disp_connection() {
		for (int i = 0; i != no_node; i++) {
			cout <<"node "<< i << " has connections   :";
			for (int j = 0; j != 4; j++) {
				cout << node_list[i].connection[j]<<" ,";
			}
			cout << endl;
		}
	}

	void BFS(int source, int destination) {
		queue <int> frontier_queue;
		bool* visited_node = new bool[no_node];
		bool*explored_node = new bool[no_node];
		for (int i = 0; i != no_node; i++) {
			visited_node[i] = 0;
			explored_node[i] = 0;
		}
		int result = source;
		

		frontier_queue.push(source);
		cout << source << " was added to frontear" << endl;
		
		while (1) {
			if (frontier_queue.empty()) {
				cout << "no solution" << endl;
				break;
			}
			result = frontier_queue.front();
			explored_node[result] = 1;
			frontier_queue.pop();
			cout << result << " was removed from frontear" << endl;
			
			cout << "                                         visited nodes are:  ";
			for (int i = 0; i != no_node; i++) {
				if (visited_node[i] == 1) {
					cout << i << "  ";
				}
				
			}
			cout << "                           " << result << "is explored" << endl;
			disp_maze(explored_node);
			visited_node[result] = 1;
			if (result == destination) {
				cout << result << " found" << endl;
				break;
			}
			else {
				for (int i = 0; i != 4; i++) {
					int adj_node = node_list[result].connection[i];
					
					cout << endl;
					if (adj_node != -1 && visited_node[adj_node] != 1) {
						frontier_queue.push(adj_node);
						visited_node[adj_node] = 1;
						cout << adj_node << " was added to frontear" << endl;
					}
					
				}			
			}

		}
	}
	void disp_maze(bool explored_node[]) {
		
			for (int i = 0; i != no_node; i++) {
				if (i % maze_width == 0) {
					cout << endl;
				}
				if (explored_node[i]) {
					cout << " # ";
				}
				else {
					cout << " _ ";
				}
			}
			cout << endl;
		
	}

};

int main() {
	maze M(3, 3);
	M.disp_connection();
	M.BFS(0, 5);

}
