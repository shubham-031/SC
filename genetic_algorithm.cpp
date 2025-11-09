#include <bits/stdc++.h>
using namespace std;

#define POP_SIZE 10
#define CHROM_LEN 8
#define CROSS_RATE 0.7
#define MUT_RATE 0.01

struct Individual {
    string chrom;
    double fitness;
};

int binToInt(string s) {
    int val = 0;
    for (char c : s) val = (val << 1) + (c - '0');
    return val;
}

double fitness(string c) {
    int x = binToInt(c);
    return x * x;  // f(x) = x²
}

string randomChrom() {
    string c;
    for (int i = 0; i < CHROM_LEN; i++)
        c += (rand() % 2) + '0';
    return c;
}

string crossover(string a, string b) {
    int point = rand() % CHROM_LEN;
    return a.substr(0, point) + b.substr(point);
}

void mutate(string &c) {
    for (char &bit : c)
        if ((rand() / (double)RAND_MAX) < MUT_RATE)
            bit = (bit == '0') ? '1' : '0';
}

int main() {
    srand(time(0));
    vector<Individual> pop(POP_SIZE);
    for (auto &i : pop) i = {randomChrom(), 0};

    for (int gen = 1; gen <= 10; gen++) {
        for (auto &i : pop) i.fitness = fitness(i.chrom);

        sort(pop.begin(), pop.end(), [](auto &a, auto &b) {
            return a.fitness > b.fitness;
        });

        cout << "Gen " << gen << " Best: " << pop[0].chrom
             << " -> f=" << pop[0].fitness << endl;

        vector<Individual> newPop;
        newPop.push_back(pop[0]); // elitism

        while (newPop.size() < POP_SIZE) {
            int p1 = rand() % (POP_SIZE / 2);
            int p2 = rand() % (POP_SIZE / 2);
            string child = crossover(pop[p1].chrom, pop[p2].chrom);
            mutate(child);
            newPop.push_back({child, 0});
        }
        pop = newPop;
    }
}
