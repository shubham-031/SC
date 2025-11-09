#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric> // for accumulate
using namespace std;

// ----- Display Population -----
void displayPopulation(const vector<string>& pop, const vector<int>& fit) {
    cout << "\nPopulation and Fitness:\n";
    for (int i = 0; i < pop.size(); i++)
        cout << " " << pop[i] << " (Fitness = " << fit[i] << ")\n";
}

// ----- 1. Roulette Wheel Selection -----
void rouletteWheelSelection(vector<string> pop, vector<int> fit, int n_select = 4) {
    float total = accumulate(fit.begin(), fit.end(), 0.0f);
    vector<float> prob;
    for (int f : fit) prob.push_back(f / total);

    vector<string> selected;
    for (int i = 0; i < n_select; i++) {
        float r = static_cast<float>(rand()) / RAND_MAX;
        float sum = 0;
        for (int j = 0; j < pop.size(); j++) {
            sum += prob[j];
            if (r <= sum) {
                selected.push_back(pop[j]);
                break;
            }
        }
    }

    cout << "\n[ Roulette Wheel Selection ]\nProbabilities: ";
    for (float p : prob) cout << p << " ";
    cout << "\nSelected: ";
    for (auto s : selected) cout << s << " ";
    cout << endl;
}

// ----- 2. Rank Selection -----
void rankSelection(vector<string> pop, vector<int> fit, int n_select = 4) {
    vector<int> rank(fit.size());
    iota(rank.begin(), rank.end(), 0);
    sort(rank.begin(), rank.end(), [&](int a, int b) { return fit[a] < fit[b]; });

    vector<float> prob(fit.size());
    float sumRanks = (fit.size() * (fit.size() + 1)) / 2.0;
    for (int i = 0; i < fit.size(); i++)
        prob[rank[i]] = (i + 1) / sumRanks;

    vector<string> selected;
    for (int i = 0; i < n_select; i++) {
        float r = static_cast<float>(rand()) / RAND_MAX;
        float sum = 0;
        for (int j = 0; j < pop.size(); j++) {
            sum += prob[j];
            if (r <= sum) {
                selected.push_back(pop[j]);
                break;
            }
        }
    }

    cout << "\n[ Rank Selection ]\nProbabilities: ";
    for (float p : prob) cout << p << " ";
    cout << "\nSelected: ";
    for (auto s : selected) cout << s << " ";
    cout << endl;
}

// ----- 3. Tournament Selection -----
void tournamentSelection(vector<string> pop, vector<int> fit, int k = 2, int n_select = 4) {
    vector<string> selected;
    for (int i = 0; i < n_select; i++) {
        int best = rand() % pop.size();
        for (int j = 1; j < k; j++) {
            int idx = rand() % pop.size();
            if (fit[idx] > fit[best])
                best = idx;
        }
        selected.push_back(pop[best]);
    }
    cout << "\n[ Tournament Selection ] (k=" << k << ")\nSelected: ";
    for (auto s : selected) cout << s << " ";
    cout << endl;
}

// ----- 4. Canonical (Deterministic) Selection -----
void canonicalSelection(vector<string> pop, vector<int> fit, int n_select = 4) {
    vector<pair<int, string>> paired;
    for (int i = 0; i < pop.size(); i++)
        paired.push_back({fit[i], pop[i]});
    sort(paired.rbegin(), paired.rend());

    cout << "\n[ Canonical (Deterministic) Selection ]\nSelected: ";
    for (int i = 0; i < n_select && i < paired.size(); i++)
        cout << paired[i].second << " ";
    cout << endl;
}

// ----- 5. Steady-State Selection -----
void steadyStateSelection(vector<string> pop, vector<int> fit, int num_replace = 2) {
    vector<pair<int, string>> paired;
    for (int i = 0; i < pop.size(); i++)
        paired.push_back({fit[i], pop[i]});
    sort(paired.rbegin(), paired.rend());

    vector<string> survivors;
    for (int i = 0; i < pop.size() - num_replace; i++)
        survivors.push_back(paired[i].second);

    vector<string> newInd;
    for (int i = 0; i < num_replace; i++)
        newInd.push_back("NewC" + to_string(i + 1));

    cout << "\n[ Steady-State Selection ]\nSurvivors: ";
    for (auto s : survivors) cout << s << " ";
    cout << "\nNew Individuals: ";
    for (auto n : newInd) cout << n << " ";
    cout << endl;
}

// ----- 6. Stochastic Universal Sampling (SUS) -----
void susSelection(vector<string> pop, vector<int> fit, int n_select = 4) {
    float total = accumulate(fit.begin(), fit.end(), 0.0f);
    vector<float> prob;
    for (int f : fit) prob.push_back(f / total);
    vector<float> cum(prob.size());
    partial_sum(prob.begin(), prob.end(), cum.begin());

    float start = static_cast<float>(rand()) / RAND_MAX / n_select;
    vector<float> pointers;
    for (int i = 0; i < n_select; i++)
        pointers.push_back(start + i * (1.0f / n_select));

    vector<string> selected;
    int i = 0;
    for (float p : pointers) {
        while (p > cum[i]) i++;
        selected.push_back(pop[i]);
    }

    cout << "\n[ Stochastic Universal Sampling (SUS) ]\nProbabilities: ";
    for (float p : prob) cout << p << " ";
    cout << "\nSelected: ";
    for (auto s : selected) cout << s << " ";
    cout << endl;
}

// ----- 7. Elitism Selection -----
void elitismSelection(vector<string> pop, vector<int> fit, int elite_size = 2) {
    vector<pair<int, string>> paired;
    for (int i = 0; i < pop.size(); i++)
        paired.push_back({fit[i], pop[i]});
    sort(paired.rbegin(), paired.rend());

    cout << "\n[ Elitism Selection ]\nElite Chromosomes: ";
    for (int i = 0; i < elite_size && i < paired.size(); i++)
        cout << paired[i].second << " ";
    cout << endl;
}

// ----- Main -----
int main() {
    srand(time(0));

    vector<string> population = {"C1", "C2", "C3", "C4"};
    vector<int> fitness = {80, 10, 6, 4};

    int choice;
    do {
        cout << "\n======================================";
        cout << "\n   GENETIC ALGORITHM SELECTION MENU   ";
        cout << "\n======================================";
        cout << "\n1. Roulette Wheel Selection";
        cout << "\n2. Rank Selection";
        cout << "\n3. Tournament Selection";
        cout << "\n4. Canonical (Deterministic) Selection";
        cout << "\n5. Steady-State Selection";
        cout << "\n6. Stochastic Universal Sampling (SUS)";
        cout << "\n7. Elitism Selection";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        displayPopulation(population, fitness);

        switch (choice) {
        case 1: rouletteWheelSelection(population, fitness); break;
        case 2: rankSelection(population, fitness); break;
        case 3: {
            int k;
            cout << "Enter tournament size (k): ";
            cin >> k;
            tournamentSelection(population, fitness, k);
            break;
        }
        case 4: canonicalSelection(population, fitness); break;
        case 5: steadyStateSelection(population, fitness); break;
        case 6: susSelection(population, fitness); break;
        case 7: elitismSelection(population, fitness); break;
        case 8: cout << "\nExiting... Thank you!\n"; break;
        default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}              
