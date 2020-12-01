#include<iostream>
using namespace std;


class TicTacToe {
public:
	char player_mat[3][3] = { {' ',' ',' '},{' ',' ',' '},{' ',' ',' '} };

	void game() {
		//game loop
		while (true) {
			input();
			draw();
			//check if termainal state
			if (check('X')) {
				system("Color 02");
				cout << " X won! Congralutations :) " << endl;
				break;
			}
			computers_move();
			draw();
			if (check('O')) {
				system("Color 04");
				cout << " O won, You loose :( " << endl;
				break;
			}
			if (!(move_left())) {
				cout << "It's a draw" << endl;
			}
		}
	}
	//check if board is full
	bool move_left() {
		for (int i = 0; i != 3; i++) {
			for (int j = 0; j != 3; j++) {
				if (player_mat[i][j] == ' ')return true;
			}
		}
		return false;
	}
	//checks for terminal state
    bool check(char player) {
        for (int i = 0; i != 3; i++) 
            if (player_mat[i][0] == player_mat[i][1] && player_mat[i][0] == player_mat[i][2] && player_mat[i][0] == player) return true;
     
        for (int j = 0; j != 3; j++) 
            if (player_mat[0][j] == player_mat[1][j] && player_mat[0][j] == player_mat[2][j] && player_mat[0][j] == player) return true;
        
        if (player_mat[0][0] == player_mat[1][1] && player_mat[0][0] == player_mat[2][2]&& player_mat[0][0] == player) return true;
        if (player_mat[0][2] == player_mat[1][1] && player_mat[0][2] == player_mat[2][0] && player_mat[0][2] == player) return true;
        return false;
    }
	//takes input
    void input(){
        
		int x, y;
		do {
			cout << "Enter coordinate where you want to place your mark(Example :1 1 to represent center): " << endl;
			cin >> x;
			cin >> y;
		} while (!(x < 3 && y < 3 && x >-1 && y >-1 &&player_mat[x][y]==' ') );
        player_mat[x][y] = 'X';
    }
	//implementation of min max
    int MinMax(bool isMaxPlayer) { //returns the value of the board
		
		if (check('O')) return 1;
		if (check('X')) return -1;
		if (move_left()==false) return 0;

		if (isMaxPlayer) {
			int best = -100000;
			for (int i = 0; i != 3; i++) {
				for (int j = 0; j != 3; j++) {
					if (player_mat[i][j] == ' ') {
						player_mat[i][j] = 'X';
						best = max(best, MinMax(false));//recursively find outs best value;
						player_mat[i][j] = ' '; //undo change made in board
					}
				}
			}
			return best;
		}
		else {
			int best = 100000;
			for (int i = 0; i != 3; i++) {
				for (int j = 0; j != 3; j++) {
					if (player_mat[i][j] == ' ') {
						player_mat[i][j] = 'O';
						best = min(best, MinMax(true));//recursively find outs best value;
						player_mat[i][j] = ' '; //undo change made in board
					}
				}
			}
			return best;
		}
	}
	//bot
	void computers_move() {
		int best_value = -1000;
		int best_move=-1;
		
		for (int i = 0; i != 3; i++) {
			for (int j = 0; j != 3; j++) {
				if (player_mat[i][j] == ' ') {
					player_mat[i][j] = 'O';
					int move_value = MinMax(true);//O is maximixing player;
					if (move_value > best_value) {
						best_value = move_value;
						best_move = i * 3 + j;//converting 2D representation to 1D
					}
					player_mat[i][j] = ' '; //undo change made in board
				}
			}
		}
		player_mat[best_move / 3][best_move % 3]='O'; //making best move //again converting 1D indexing to 2D
		std::cout << "Computers move is :" << best_move / 3 << ","<< best_move % 3 << std::endl <<"Best value is:"<< best_value << std::endl;
	}
	//draws board
	void draw() {
		cout << flush;
		system("cls");
		cout << "     |     |     " << endl;
		cout << "  " << player_mat[0][0] << "  |  " << player_mat[0][1] << "  |  " << player_mat[0][2] << endl;

		cout << "_____|_____|_____" << endl;
		cout << "     |     |     " << endl;

		cout << "  " << player_mat[1][0] << "  |  " << player_mat[1][1] << "  |  " << player_mat[1][2] << endl;

		cout << "_____|_____|_____" << endl;
		cout << "     |     |     " << endl;

		cout << "  " << player_mat[2][0] << "  |  " << player_mat[2][1] << "  |  " << player_mat[2][2] << endl;

		cout << "     |     |     " << endl << endl;
	}

};
int main() {
   
	TicTacToe demo;
	demo.game();
	return 0;

}
