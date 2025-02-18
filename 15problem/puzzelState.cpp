#include<bits/stdc++.h>
using namespace std;

class Puzzle{
    public:
    vector<vector<int>> puzzle;
    pair<int,int> blank;
    Puzzle(){} ;
    Puzzle(vector<vector<int>> puzzle){

        if(puzzle.size() != 4) return;
        this->puzzle = puzzle;

        for(int i =0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(puzzle[i][j] == 0){
                    blank = {i,j};
                }
            }
        }
    }

    int getCost1() const{
        int cost = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int val = puzzle[i][j];
                if(val == 0) val = 16;
                int expectedVal = i * 4 + j + 1;
                if(val != expectedVal) cost++;
            }
        }

        return cost;
    }
    int getCost2() const {
        int cost = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int val = puzzle[i][j];
                if(val == 0) continue;
                int expectedVal = i * 4 + j + 1;
                int expI = (val-1)/4;
                int expJ = (val-1)%4;
                cost += abs(expI - i) + abs(expJ - j);
            }
        }

        return cost;
    }


    bool operator<(const Puzzle& other) const {
        return getCost1() < other.getCost1();
    }
    bool canMoveLeft(){
        if(blank.second == 0) return false;
        return true;
    }
    bool canMoveRight(){
        if(blank.second == 3) return false;
        return true;
    }
    bool canMoveUp(){
        if(blank.first == 0) return false;
        return true;
    }
    bool canMoveDown(){
        if(blank.first == 3) return false;
        return true;
    }

    void moveLeft(){
        if(!canMoveLeft()) return;
        swap(puzzle[blank.first][blank.second], puzzle[blank.first][blank.second - 1]);
        blank.second--;
    }
    void moveRight(){
        if(!canMoveRight()) return;
        swap(puzzle[blank.first][blank.second], puzzle[blank.first][blank.second + 1]);
        blank.second++;
    }

    void moveUp(){
        if(!canMoveUp()) return;
        swap(puzzle[blank.first][blank.second], puzzle[blank.first - 1][blank.second]);
        blank.first--;
    }
    void moveDown(){
        if(!canMoveDown()) return;
        swap(puzzle[blank.first][blank.second], puzzle[blank.first + 1][blank.second]);
        blank.first++;
    }

    void move(int dx, int dy){
        if(dx == 0 and dy == 0) return;
        if(dx == 0 and dy == 1) moveRight();
        if(dx == 0 and dy == -1) moveLeft();
        if(dx == 1 and dy == 0) moveDown();
        if(dx == -1 and dy == 0) moveUp();
    }
    void printPuzzle(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                cout<<setw(3)<<puzzle[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    string getHsh(){
        string s = "";
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                s += to_string(puzzle[i][j]);
            }
        }

        return s;
    }
};


