#include<iostream>
#include<queue>
#include<stack>
using namespace std;


    stack <int> frontier_stack;
    queue <int> frontier_queue;
    int adj_mat[6][6] = {
    {0,1,0,0,0,0},
    {1,0,1,1,0,0},
    {0,1,0,0,1,0},
    {0,1,0,0,0,1},
    {0,0,1,0,0,0},
    {0,0,0,1,0,0}
    };
    char put(int a) {
        char arr[] = { 'A','B','C','D','E','F' };
            return arr[a];
        
    }
    bool explored_node[6] = {0,0,0,0,0,0};
    
    void DFS(int source, int destination) {
        int result = source;
        frontier_stack.push(source);
        cout << put(source) << " was added to frontear" << endl;
        while (1) {
            if (frontier_stack.empty()) {
                cout << "no solution" << endl;
                break;
            }
            result = frontier_stack.top();
            frontier_stack.pop();
            cout << put(result) << " was removed from frontear" << endl;
            explored_node[result] = 1;
            cout << "                           " << put(result)<<"is explored" << endl;

            if (result == destination) {
                cout << put(result) << " found" << endl;
                break;
            }
            else {
                for (int i = 0; i != 6; i++) {
                    if (adj_mat[result][i] == 1 && explored_node[i] == 0) {
                        frontier_stack.push(i);
                        cout << put(i) << " was added to frontear" << endl;
                    }
                }
            }

        }
    }
    void BFS(int source, int destination) {
        int result = source;
        frontier_queue.push(source);
        cout << put(source) << " was added to frontear" << endl;
        while (1) {
            if (frontier_queue.empty()) {
                cout << "no solution" << endl;
                break;
            }
            result = frontier_queue.front();
            frontier_queue.pop();
            cout << put(result) << " was removed from frontear" << endl;
            explored_node[result] = 1;
            cout << "                           " << put(result) << "is explored" << endl;

            if (result == destination) {
                cout << put(result) << " found" << endl;
                break;
            }
            else {
                for (int i = 0; i != 6; i++) {
                    if (adj_mat[result][i] == 1 && explored_node[i] == 0) {
                        frontier_queue.push(i);
                        cout << put(i) << " was added to frontear" << endl;
                    }
                }
            }

        }
    }
    
     


int main()
{
    DFS(0, 4);
    cout << "\n\n\n";
    BFS(0, 4);
    return 0;
}
