#include <bits/stdc++.h>
#include <iomanip>
#define pii pair<int,int>

using namespace std;
class GeneticAlgorithm{
    private:
    unordered_map<pair<int,int>,double> edgeToWeights;
    vector<pair<int,int>> edgeList;
    public:

        GeneticAlgorithm(vector<pair<pii,double>> edgeList){
            for (const pair<pii, double>& edgeWeight : edgeList) {
                pii edge = edgeWeight.first;
                double weight = edgeWeight.second;

            }
        }

        double f(vector<pair<int,int>> edgeList ){

        }
};