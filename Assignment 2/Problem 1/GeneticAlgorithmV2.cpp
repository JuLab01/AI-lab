#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

class GeneticAlgorithm
{
private:
public:
    static int size;
    const static int m = 10;
    static const vector<int> beta; // declare beta here
    static const vector<vector<double>> C ;

    static const int lower_bound = 0;
    static const int upper_bound = 10;
    static const int bit_cnt = 10;
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

    static string makeChromosome(vector<double> vx){
        string chromosome = "";
        function<string(double)> encode = [&](double x){
            double norm = (x - lower_bound)/(upper_bound - lower_bound);
            double quant = floor(norm * (pow(2, bit_cnt) - 1));
            string binary = bitset<bit_cnt>(quant).to_string();
            return binary;
        };
        for(double x: vx){
            chromosome += encode(x);
        }
        return chromosome;
    }

    static vector<double> decodeChromosome(string chromosome){
        vector<double> vx;
        function<double(string)> decode = [&](string binary){
          int quant = stoll(binary, nullptr, 2);  
          double norm = quant /(pow(2, bit_cnt) - 1);
          double x = norm * (upper_bound - lower_bound) + lower_bound;
          return x;
        };

        for(int i = 0; i < 4; i++){
            vx.push_back(decode(chromosome.substr(i*bit_cnt, bit_cnt)));
        }
        return vx;
    }

    static void test(){
        vector<double> x = {1,2,3,4};

        string chromosome = makeChromosome(x);
        cout << chromosome << endl;

        vector<double> vx = decodeChromosome(chromosome);
        for(double a: vx) cout<<a<<" ";
    }

    static string mutateChromosome(string chromosome){
        int n = chromosome.length();
        int pos = rand() % n;
        chromosome[pos] = chromosome[pos] == '0' ? '1' : '0';
        return chromosome;
    }

    static pair<string, string> crossoverChromosome(string chromosome1, string chromosome2){
        int n = chromosome1.length();
        int pos = rand() % n;

        return {chromosome1.substr(0, pos) + chromosome2.substr(pos), chromosome2.substr(0, pos) + chromosome1.substr(pos)};    
        
    }


    static vector<string> getPopulation(){
        vector<string> population;
        for(int i = 0; i < size; i++){
            vector<double> chromosome;
            for(int j = 0; j< 4; j++){
                chromosome.push_back((double)(rand()%(upper_bound - lower_bound)));
            }
            population.push_back(makeChromosome(chromosome));
        }
        return population;
    }


    static vector<string> getBestChromosomes(vector<string> population){ // may be use sorting instead of heap
        vector<pair<double, string>> pq;
        for(string chromosome: population){
            double value = f(decodeChromosome(chromosome));
            pq.push_back({value, chromosome});
        }

        sort(pq.begin(), pq.end(), [](pair<double, string> a, pair<double, string> b){
            return a.first > b.first;
        });

        vector<string> bestChromosomes;
        for(int i = 0; i < size/2; i++){
            bestChromosomes.push_back(pq[i].second);
        }
        return bestChromosomes;
    }



    static vector<string> generateNextPopulation(vector<string> population) {
        vector<string> nextPopulation;
        int size = GeneticAlgorithm::size - 1;
        // The best in the population goes to the next generation
        nextPopulation.push_back(population[0]);
    
        // Calculate fitness sum for roulette wheel selection
        double totalFitness = 0;
        vector<double> fitnessValues;
        for (const string &chromosome : population) {
            double fitness = f(decodeChromosome(chromosome));
            fitnessValues.push_back(fitness);
            totalFitness += fitness;
        }
    
        auto rouletteSelect = [&](double totalFitness) {
            double r = (double)rand() / RAND_MAX * totalFitness;
            double runningSum = 0;
            for (int i = 0; i < population.size(); i++) {
                runningSum += fitnessValues[i];
                if (runningSum >= r) {
                    return population[i];
                }
            }
            return population.back();
        };
    
        while (nextPopulation.size() < GeneticAlgorithm::size) {
            string parent1 = rouletteSelect(totalFitness);
            string parent2 = rouletteSelect(totalFitness);
    
            // Crossover with probability 0.5
            if ((double)rand() / RAND_MAX < 0.5) {
                pair<string, string> offspring = crossoverChromosome(parent1, parent2);
                nextPopulation.push_back(offspring.first);
                if (nextPopulation.size() < GeneticAlgorithm::size) {
                    nextPopulation.push_back(offspring.second);
                }
            } else {
                nextPopulation.push_back(parent1);
            }
    
            // Mutation with probability 0.1
            if ((double)rand() / RAND_MAX < 0.1) {
                nextPopulation.back() = mutateChromosome(nextPopulation.back());
            }
        }
    
        return nextPopulation;
    }
    

    static double population_mean(vector<string> population){
        double sum = 0;
        for(string i: population){
            sum += f(decodeChromosome(i));
        }
        return sum / population.size();
    }

    static double population_variance(vector<string> population){
        double mean = GeneticAlgorithm::population_mean(population);
        double sum2 = 0;
        for(string i: population){
            double val = f(decodeChromosome(i));
            sum2 += (val - mean) * (val - mean);
        }
        return sum2 / population.size();
    }

    static double population_median(vector<string> population){
        sort(population.begin(), population.end(), [](string a, string b){return f(decodeChromosome(a)) < f(decodeChromosome(b));});
        return f(decodeChromosome(population[population.size()/2]));
    }

    static void printVec(vector<double> v){
        for(int i = 0; i < 4; i++){
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }

    static void runEvolution() {
        vector<string> population = getPopulation();
        int generations = 0;
        int maxGenerations = 100;
        cout << fixed << setprecision(4); // Set precision for floating-point output
    
        while (true) {
            vector<string> bestChromosomes = getBestChromosomes(population);
            cout << "Best Chromosome (decoded): ";
            printVec(decodeChromosome(bestChromosomes[0]));
    
            vector<string> nextPopulation = generateNextPopulation(bestChromosomes);
            population = nextPopulation;
            if (population.size() == 1) break;
    
            cout << left << setw(12) << "Mean:" << setw(10) << population_mean(population);
            cout << left << setw(12) << "Variance:" << setw(10) << population_variance(population);
            cout << left << setw(12) << "Median:" << setw(10) << population_median(population) << endl;
    
            generations++;
            if (generations == maxGenerations) break;
        }
    
        cout << "Best Chromosome: ";
        vector<double> params = decodeChromosome(population[0]);
        printVec(params);
        cout << "Fitness: " << f(params) << endl;
    }
};

int GeneticAlgorithm::size = 20;
const vector<int> GeneticAlgorithm::beta = {1,2,2,4,4,6,3,7,5,5};
const vector<vector<double>> GeneticAlgorithm::C = {{4,1,8,6,3,2,5,8,6,7},{4,1,8,6,7,9,3,1,2,3.6},{4,1,8,6,3,2,5,8,6,7},{4,1,8,6,7,9,3,1,2,3.6}};


int main(){
    // GeneticAlgorithm::test();
    GeneticAlgorithm::runEvolution();
}