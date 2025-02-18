#include <bits/stdc++.h>
using namespace std;

class GeneticAlgorithm
{
private:
public:
    static int size;
    const static int m = 10;
    static const vector<int> beta; // declare beta here
    static const vector<vector<double>> C ;
    
    static double f(vector<double> x){
        double reverse_sum = 0;
        for(int i = 0; i < m; i++){
            double sum = 0;
            for(int j = 0; j < 4; j++){
                sum += (x[j] - C[j][i])*(x[j] - C[j][i]) + beta[i]/(double)10;
            }
            reverse_sum += 1/sum;
        }

        return -reverse_sum;
    }
    GeneticAlgorithm();
    static int makeChromosome(vector<double> x){
        int chromosome = 0;
        int shift = 0;
        for(int i = 0; i < x.size(); i++){
            chromosome = chromosome | ((int)(x[i]) << shift);
            shift += 4;
        }
        return chromosome;
    }

    static vector<double> decodeChromosome(int chromosome){
        vector<double> x;
        int shift = 0;
        for(int i = 0; i < 4; i++){
            x.push_back((double)((chromosome >> shift) & 15));
            shift += 4;
        }
        return x;
    }

    static int mutateChromosome(int chromosome){
        return chromosome ^ (rand() % 16);
    }

    static pair<int, int> crossoverChromosome(int chromosome1, int chromosome2){
        int mask = rand() % 16;
        if(chromosome1 & (1 << mask) != chromosome1 & (1 << mask)){
            return {chromosome1 ^ (1 << mask), chromosome2 ^ (1 << mask)};
        }
        return {chromosome1, chromosome2};
    }
    static vector<int> getPopulation(){
        vector<int> population;
        for(int i = 0; i < size; i++){
            vector<double> chromosome;
            for(int j = 0; j< 4; j++){
                chromosome.push_back((double)(rand()%16));
            }
            population.push_back(makeChromosome(chromosome));
        }
        return population;
    }

    static vector<int> getBestChromosomes(vector<int> population){ // may be use sorting instead of heap
        priority_queue<pair<double, int>> pq;
        for(int chromosome: population){
            double value = f(decodeChromosome(chromosome));
            pq.push({value, chromosome});
        }

        vector<int> bestChromosomes;
        for(int i = 0; i < size/2; i++){
            bestChromosomes.push_back(pq.top().second);
            pq.pop();
        }
        return bestChromosomes;
    }

    static vector<int> generateNextPopulation(vector<int> population){
        vector<int> nextPopulation;
        
        int size = GeneticAlgorithm::size - 1;
        // the best in the population goes to the next generation
        nextPopulation.insert(nextPopulation.end(), population.begin(), population.begin() + 1);

        for(int i = 0; i < size; i++){
            // on probability of 0.1 we put a mutated chromosome
            int r = rand() % 10;
            if(r == 1) {
                nextPopulation.push_back(mutateChromosome(population[i]));
                size--;
                if(size == 0) return nextPopulation;
            } 
            for(int j = 0; j < size; j++){
                if(i == j) continue;
                // on probability of 0.5 we put a crossover chromosome
                if(r < 5){
                    pair<int, int> chromosomes = crossoverChromosome(population[i], population[j]);
                    nextPopulation.push_back(chromosomes.first);
                    size -= 1;
                    if(size == 0) return nextPopulation;
                    nextPopulation.push_back(chromosomes.second);
                    size -= 1;
                    if(size == 0) return nextPopulation;
                }
            }
        }
        if(size != 0) nextPopulation.insert(nextPopulation.end(), population.begin(), population.begin() + size);
        return nextPopulation;
    }

    static double population_mean(vector<int> population){
        double sum = 0;
        for(int i: population){
            sum += f(decodeChromosome(i));
        }
        return sum / population.size();
    }

    static double population_variance(vector<int> population){
        double mean = GeneticAlgorithm::population_mean(population);
        double sum2 = 0;
        for(int i: population){
            double val = f(decodeChromosome(i));
            sum2 += (val - mean) * (val - mean);
        }
        return sum2 / population.size();
    }

    static double population_median(vector<int> population){
        sort(population.begin(), population.end(), [](int a, int b){return f(decodeChromosome(a)) < f(decodeChromosome(b));});
        return f(decodeChromosome(population[population.size()/2]));
    }

    static void runEvolution(){
        vector<int> population = getPopulation();
        int generations = 0;
        int maxGenerations = 100; 
        while(true){
            vector<int> bestChromosomes = getBestChromosomes(population);
            vector<int> nextPopulation = generateNextPopulation(bestChromosomes);
            population = nextPopulation;
            if(population.size() == 1) break;
            
            cout<<"Mean: "<<population_mean(population)<<" ";
            cout<<"Variance: "<<population_variance(population)<<" ";
            cout<<"Median: "<<population_median(population)<<endl;
            generations++;
            if(generations == maxGenerations) break;
        }
        cout<<"Best Chromosome: "<<" ";
        vector<double> chromosome = decodeChromosome(population[0]);
        for(int i = 0; i < 4; i++){
            cout<<(int)chromosome[i]<<" ";
        }
        cout<<endl;

        cout<<"fitness: "<< f(chromosome)<<endl;
    }

};
int GeneticAlgorithm::size = 20;
const vector<int> GeneticAlgorithm::beta = {1,2,2,4,4,6,3,7,5,5};
const vector<vector<double>> GeneticAlgorithm::C = {{4,1,8,6,3,2,5,8,6,7},{4,1,8,6,7,9,3,1,2,3.6},{4,1,8,6,3,2,5,8,6,7},{4,1,8,6,7,9,3,1,2,3.6}};

int main(){
    GeneticAlgorithm::runEvolution();
    return 0;
}