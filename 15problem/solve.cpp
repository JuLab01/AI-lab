#include<bits/stdc++.h>
#include"puzzelState.cpp"
using namespace std;

void solve(Puzzle start){
    int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
    priority_queue<pair<int,Puzzle>, vector<pair<int,Puzzle>>, greater<pair<int,Puzzle>>> pq;
    // queue<pair<int,Puzzle>> pq;
    pq.push({start.getCost1(), start});

    unordered_map<string,bool> visited;
    visited[start.getHsh()] = true;

    while(!pq.empty()){
        pair<int,Puzzle> p = pq.top(); pq.pop();
        int cost = p.first;
        Puzzle puzzle = p.second;

        if(puzzle.getCost1() == 0){
            cout<<"Goal reached"<<endl;
            puzzle.printPuzzle();
            return;
        }


        puzzle.printPuzzle();
        cout<<endl;

        for(int i = 0; i < 4; i++){
            Puzzle temp = puzzle;
            temp.move(dx[i], dy[i]);
            if(visited[temp.getHsh()]) continue;

            
            pq.push({temp.getCost1(), temp});
            visited[temp.getHsh()] = true;
        }

    }

}


int main(){
    Puzzle p({{8,7,4,12},{2,1,3,15},{6,13,5,10},{9,0,11,14}});
    // p.moveUp();
    solve(p);
}