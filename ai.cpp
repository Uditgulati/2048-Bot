#include <bits/stdc++.h>

using namespace std;

int weight[4][4] = {
                        {6, 5, 4, 3},
                        {5, 4, 3, 2},
                        {4, 3, 2, 1},
                        {3, 2, 1, 0}
                    }

int move_left(int grid[4][4]) {
    int grid1[4][4];
    
}

int move_right(int grid[4][4]) {
    int grid1[4][4];
    
}

int move_up(int grid[4][4]) {
    int grid1[4][4];

}

int move_down(int grid[4][4]) {
    int grid1[4][4];
    
}

int currScore(int grid[4][4]) {

}

int expectiMax(int grid[4][4], int depth, int pos) {
    if(depth == 0)
        return currScore(grid);
    
    if(pos == 0) {

    }
    else {

    }
}

int bestMove(int grid[4][4], int depth, int pos) {
    int move = -1, highestScore = -1;
    int score1 = expectiMax(move_left(grid), depth - 1, !pos);
    if(score1 > highestScore)
        highestScore = score1, move = 0;
    int score1 = expectiMax(move_right(grid), depth - 1, !pos);
    if(score1 > highestScore)
        highestScore = score1, move = 1;
    int score1 = expectiMax(move_up(grid), depth - 1, !pos);
    if(score1 > highestScore)
        highestScore = score1, move = 2;
    int score1 = expectiMax(move_down(grid), depth - 1, !pos);
    if(score1 > highestScore)
        highestScore = score1, move = 3;
    return move;
}

int main(int argc ,char * argv[]) {
    cout << argv[1] << endl;
    vector <int> vec;
    for(int i = 0; i < 4; i++) {
        int a = argv[1][2 * i] - 48;
        int b = argv[1][2 * i + 1] - 48;
        int num = (10 * a) + b;
        cout << num << endl;
        vec.push_back(num);
    }
    int matrix[4][4];
    int ind = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            matrix[i][j] = vec[ind++];
    int depth = 5;
    int move = bestMove(matrix, depth, 0);   //move to be printed
    cout << move << endl;
    return 0;
}