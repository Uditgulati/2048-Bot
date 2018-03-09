#include <bits/stdc++.h>

using namespace std;


struct board {
    int arr[4][4];
};

double weight[4][4] = {
                        {13.5, 12.1, 10.2, 9.9},
                        {9.9, 8.8, 7.6, 7.2},
                        {6.0, 5.6, 3.7, 1.6},
                        {1.2, 0.9, 0.5, 0.3}
                    };

int values[2] = {1, 2};
double probs[2] = {0.9, 0.1};

bool inline isSame(board grid1, board grid2) {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(grid1.arr[i][j] != grid2.arr[i][j])
                return false;
    return true;
}

void inline move_line(int cells[4]) {
    int target = 0;
    for(int i = 1; i < 4; i++) {
        int targetVal = cells[target];
        int currVal = cells[i];
        if(currVal) {   //currVal != 0
            if(!targetVal)  //targetVal == 0
                cells[target] = currVal, cells[i] = 0;
            else {
                if(targetVal == currVal)
                    cells[i] = 0, cells[target]++;
                else
                    cells[i] = 0, cells[target + 1] = currVal;
                target++;
            }
        }
    }
}

board inline move_left(board grid) {
    board grid1;
    for(int i = 0; i < 4; i++) {
        int temp[4];
        for(int j = 0; j < 4; j++)
            temp[j] = grid.arr[i][j];
        move_line(temp);
        for(int j = 0; j < 4; j++)
            grid1.arr[i][j] = temp[j];
    }
    return grid1;
}

board inline move_right(board grid) {
    board grid1;
    for(int i = 0; i < 4; i++) {
        int temp[4];
        for(int j = 0; j < 4; j++)
            temp[j] = grid.arr[i][3 - j];
        move_line(temp);
        for(int j = 0; j < 4; j++)
            grid1.arr[i][3 - j] = temp[j];
    }
    return grid1;
}

board inline move_up(board grid) {
    board grid1;
    for(int j = 0; j < 4; j++) {
        int temp[4];
        for(int i = 0; i < 4; i++)
            temp[i] = grid.arr[i][j];
        move_line(temp);
        for(int i = 0; i < 4; i++)
            grid1.arr[i][j] = temp[i];
    }
    return grid1;
}

board inline move_down(board grid) {
    board grid1;
    for(int j = 0; j < 4; j++) {
        int temp[4];
        for(int i = 0; i < 4; i++)
            temp[i] = grid.arr[3 - i][j];
        move_line(temp);
        for(int i = 0; i < 4; i++)
            grid1.arr[3 - i][j] = temp[i];
    }
    return grid1;
}

board inline moveGrid(board grid, int ind) {
    if(ind == 0)
        return move_left(grid);
    else if(ind == 1)
        return move_right(grid);
    else if(ind == 2)
        return move_up(grid);
    else if(ind == 3)
        return move_down(grid);
}

double inline currScore(board grid) {
    double tot = -1e9;
    double s0 = 0, s1 = 0, s2 = 0, s3 = 0;
    double sc0 = 0, sc1 = 0, sc2 = 0, sc3 = 0;
    double grid1[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) {
            if(!grid.arr[i][j])
                grid1[i][j] = 0;
            else
                grid1[i][j] = pow(2, grid.arr[i][j]);
        }

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[i][j]);
    tot = max(tot, s0);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[j][i]);
    tot = max(tot, sc0);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[i][3 - j]);
    tot = max(tot, s1);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[j][3 - i]);
    tot = max(tot, sc1);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[3 - i][j]);
    tot = max(tot, s2);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[j][3 - i]);
    tot = max(tot, sc2);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[3 - i][3 - j]);
    tot = max(tot, s3);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            s0 += (grid1[i][j] * weight[3 - j][3 - i]);
    tot = max(tot, sc3);

    return tot;
}

double expectiMax(board grid, int depth) {
    if(depth == 0)
        return currScore(grid);

    double score = 0;
    double tot_prob = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(!grid.arr[i][j]) {
                for(int ind = 0; ind < 2; ind++) {
                    board grid1 = grid;
                    grid1.arr[i][j] = values[ind];

                    double best = -1e9;
                    int direction = -1;

                    for(int dir = 0; dir < 4; dir++) {
                        board grid2 = moveGrid(grid1, dir);
                        if(!isSame(grid2, grid1)) {
                            double score1 = expectiMax(grid2, depth - 1);
                            if(score1 > best)
                                best = score1, direction = dir;
                        }
                    }

                    if(direction != -1)
                        score += (probs[ind] * best);
                    else
                        score += (probs[ind] * currScore(grid1));
                    tot_prob += probs[ind];
                }
            }
        }
    }


    return (score / tot_prob);
}

int inline blankNum(board grid) {
    int num = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(!grid.arr[i][j])
                num++;
    return num;
}

int inline bestMove(board grid, int depth) {
    int move = 0;
    double highestScore = -1e9;

    for(int i = 0; i < 4; i++) {
        board grid1 = moveGrid(grid, i);
        if(!isSame(grid, grid1)) {
            double score1 = expectiMax(grid1, depth);
            if(score1 > highestScore)
                highestScore = score1, move = i;
            //cout << "Score1 " << i << ": " << score1 << endl;
        }
    }

    return move;
}

bool isOver(board grid) {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(grid.arr[i][j] == 0)
                return false;
    return true;
}

int main(int argc ,char * argv[]) {
    srand(time(NULL));
    //cout << argv[1] << endl;
    vector <int> vec;
    for(int i = 0; i < 16; i++) {
        int a = argv[1][2 * i] - 48;
        int b = argv[1][2 * i + 1] - 48;
        int num = (10 * a) + b;
        //cout << num << endl;
        vec.push_back(num);
    }
    board matrix;
    int ind = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            matrix.arr[i][j] = vec[ind++];
    int depth = 2;
    
    int soFar = 1;

    int move = bestMove(matrix, depth);   //move to be printed

    printf("%d", move);

    /*while(true) {
        int move = bestMove(matrix, depth);   //move to be printed
        cout << "Move: " << move << endl;
        cout << "Moves so far: " << soFar++ << endl;
        cout << endl;
        matrix = moveGrid(matrix, move);
        int count1 = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(!matrix.arr[i][j])
                    count1++, cout << "0 ";
                else
                    cout << pow(2, matrix.arr[i][j]) << " ";
            }
            cout << endl;
        }
        if(isOver(matrix))
            break;
        int pos1 = rand() % count1;
        int val = rand() % 10 + 1, val1;
        if(val == 10)
            val1 = 2;
        else
            val1 = 1;
        int ind = 0;
        cout << "Random: ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++) {
                if(ind == pos1 && !matrix.arr[i][j]) {
                    matrix.arr[i][j] = val1, ind++;
                    cout << val1 << " (" << i << ", " << j << ")" << endl;
                }
                if(!matrix.arr[i][j])
                    ind++;
            }
    }*/
    return 0;
}