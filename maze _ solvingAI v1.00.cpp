
#include<iostream>
#include<queue>
#include<stack>
#include<thread>
#include<stdlib.h>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

class node {
public:
	int connection[4];
	bool is_wall=false;
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
	maze(int width, int hight,int* maze_matrix) {
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
		make_maze(maze_matrix);
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



	void add_wall(int pos) {
		node_list[pos].is_wall= true;

	}



	void make_maze(int* maze_matrix) {
		for (int i = 0; i != no_node; i++) {
			
				if (maze_matrix[i] == 1) {
					int pos = i;
					add_wall(pos);
				}
			
		}
	}




	void BFS(int source, int destination) {
		queue <int> frontier_queue;
		bool* visited_node = new bool[no_node];
		bool* explored_node = new bool[no_node];
		for (int i = 0; i != no_node; i++) {
			visited_node[i] = 0;
			explored_node[i] = 0;
		}
		int result = source;


		frontier_queue.push(source);
		//cout << source << " was added to frontear" << endl;
		disp_maze(explored_node, source, destination);
		sleep_until(system_clock::now() + 2s);
		while (1) {
			if (frontier_queue.empty()) {
				//system("Color 04");
				cout << "no solution !!" << endl;
				break;
			}
			result = frontier_queue.front();
			explored_node[result] = 1;
			frontier_queue.pop();
			cout << result << " was removed from frontear" << endl;

			cout << "visited nodes are:  ";
			for (int i = 0; i != no_node; i++) {
				if (visited_node[i] == 1) {
					cout << i << "  ";
				}

			}
			cout << endl;

			disp_maze(explored_node, source, destination);
			visited_node[result] = 1;
			if (result == destination) {

				cout << endl << result << " found !!" << endl;
				//system("Color 04");
				break;
			}
			else {
				for (int i = 0; i != 4; i++) {
					int adj_node = node_list[result].connection[i];

					cout << endl;
					if (adj_node != -1 && visited_node[adj_node] != 1 && node_list[result].is_wall == false) {
						frontier_queue.push(adj_node);
						visited_node[adj_node] = 1;
						cout << adj_node << " was added to frontear" << endl;
					}

				}
			}
			
			sleep_until(system_clock::now() + 200ns);
			system("cls");

		}
	}
	void DFS(int source, int destination) {
		stack <int> frontier_queue;
		bool* visited_node = new bool[no_node];
		bool* explored_node = new bool[no_node];
		for (int i = 0; i != no_node; i++) {
			visited_node[i] = 0;
			explored_node[i] = 0;
		}
		int result = source;


		frontier_queue.push(source);
		//cout << source << " was added to frontear" << endl;
		disp_maze(explored_node, source, destination);
		sleep_until(system_clock::now() + 2s);
		while (1) {
			system("cls");
			if (frontier_queue.empty()) {
				//system("Color 04");
				cout << "no solution !!" << endl;
				break;
			}
			result = frontier_queue.top();
			explored_node[result] = 1;
			frontier_queue.pop();
			cout << result << " was removed from frontear" << endl;

			/*cout << "visited nodes are:  ";
			for (int i = 0; i != no_node; i++) {
				if (visited_node[i] == 1) {
					cout << i << "  ";
				}

			}*/
			cout << endl;
			

			disp_maze(explored_node, source, destination);
			visited_node[result] = 1;
			if (result == destination) {

				cout << endl <<"Destination found in :"<< result << " found !!" << endl;
				system("Color 06");
				break;
			}
			else {
				for (int i = 0; i != 4; i++) {
					int adj_node = node_list[result].connection[i];

					cout << endl;
					if (adj_node != -1 && visited_node[adj_node] != 1 && node_list[result].is_wall == false) {
						frontier_queue.push(adj_node);
						visited_node[adj_node] = 1;
						//cout << adj_node << " was added to frontear" << endl;
					}

				}
			}
			
			sleep_until(system_clock::now() + 900ns);
			

		
		}
	}


	void disp_maze(bool explored_node[],int source,int destination) {
		
		
			for (int i = 0; i != no_node; i++) {
				if (i % maze_width == 0) {
					cout << endl;
				}
				if (node_list[i].is_wall) {
					//cout << " # ";
					cout << char(219) << char(219);
				}
				else if (explored_node[i]) {
					if (i == destination) {
						cout << " D";
					}
					else if (i == source) {
						cout << " S";
					}
					else {
						//cout << " * ";
						cout << char(176) << char(176);
					}
						
				}
				else {
					if (i == destination) {
						cout << " D";
					}
					else if (i == source) {
						cout << " S";
					}
					else {
						cout << "  ";
					}
					
				}
			}
 		cout << endl;
			
	}
	
};


int main() {
	int maze_matrix[10][13] =
	{ {1,1,1,1,1,1,1,1,1,1,1,1,1},
	  {1,0,1,0,1,0,1,0,0,0,0,0,1},
	  {1,0,1,0,0,0,1,0,1,1,1,0,1},
	  {1,0,0,0,1,1,1,0,0,0,0,0,1},
	  {1,0,1,0,0,0,0,0,1,1,1,0,1},
	  {1,0,1,0,1,1,1,0,1,0,0,0,1},
	  {1,0,1,0,1,0,0,0,1,1,1,0,1},
	  {1,0,1,0,1,1,1,0,1,0,1,0,1},
	  {1,0,0,0,0,0,0,0,0,0,1,0,1},
	  {1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	maze M(13,10,&maze_matrix[0][0]);
	
	
	M.DFS(14, 107);


}
