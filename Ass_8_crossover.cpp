#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // ✅ Added for sort()
using namespace std;

// Function to display chromosomes
void displayChromosome(const string &label, const vector<int> &chrom) {
    cout << label << ": ";
    for (int bit : chrom)
        cout << bit;
    cout << endl;
}

// ----- 1. Single-Point Crossover -----
void singlePointCrossover(vector<int> p1, vector<int> p2) {
    int point = rand() % p1.size();
    cout << "\nCrossover Point: " << point << endl;
    for (int i = point; i < p1.size(); i++)
        swap(p1[i], p2[i]);

    displayChromosome("Offspring 1", p1);
    displayChromosome("Offspring 2", p2);
}

// ----- 2. Two-Point Crossover -----
void twoPointCrossover(vector<int> p1, vector<int> p2) {
    int size = p1.size();
    int point1 = rand() % size;
    int point2 = rand() % size;
    if (point1 > point2) swap(point1, point2);

    cout << "\nCrossover Points: " << point1 << " and " << point2 << endl;
    for (int i = point1; i < point2; i++)
        swap(p1[i], p2[i]);

    displayChromosome("Offspring 1", p1);
    displayChromosome("Offspring 2", p2);
}

// ----- 3. Multi-Point Crossover -----
void multiPointCrossover(vector<int> p1, vector<int> p2, int numPoints) {
    int size = p1.size();
    vector<int> points;
    for (int i = 0; i < numPoints; i++)
        points.push_back(rand() % size);

    sort(points.begin(), points.end()); // ✅ Sort crossover points

    cout << "\nCrossover Points: ";
    for (int p : points) cout << p << " ";
    cout << endl;

    bool swapFlag = false;
    int last = 0;
    for (int p : points) {
        if (swapFlag) {
            for (int i = last; i < p; i++)
                swap(p1[i], p2[i]);
        }
        swapFlag = !swapFlag;
        last = p;
    }

    displayChromosome("Offspring 1", p1);
    displayChromosome("Offspring 2", p2);
}

// ----- 4. Uniform Crossover -----
void uniformCrossover(vector<int> p1, vector<int> p2) {
    vector<int> c1 = p1, c2 = p2;
    for (int i = 0; i < p1.size(); i++) {
        if (rand() % 2 == 0) // 50% probability
            swap(c1[i], c2[i]);
    }

    displayChromosome("Offspring 1", c1);
    displayChromosome("Offspring 2", c2);
}

// ----- 5. Uniform Crossover with Mask -----
void uniformCrossoverWithMask(vector<int> p1, vector<int> p2) {
    vector<int> mask(p1.size());
    for (int i = 0; i < p1.size(); i++)
        mask[i] = rand() % 2; // Generate random 0/1 mask

    cout << "\nMask: ";
    for (int bit : mask) cout << bit;
    cout << endl;

    vector<int> c1 = p1, c2 = p2;
    for (int i = 0; i < p1.size(); i++) {
        if (mask[i] == 1)
            swap(c1[i], c2[i]);
    }

    displayChromosome("Offspring 1", c1);
    displayChromosome("Offspring 2", c2);
}

// ----- Main Menu -----
int main() {
    srand(time(0));

    int n;
    cout << "Enter chromosome length: ";
    cin >> n;

    vector<int> parent1(n), parent2(n);
    cout << "Enter Parent 1 (binary): ";
    for (int i = 0; i < n; i++) cin >> parent1[i];

    cout << "Enter Parent 2 (binary): ";
    for (int i = 0; i < n; i++) cin >> parent2[i];

    int choice;
    do {
        cout << "\n===============================";
        cout << "\n BINARY CODED GA CROSSOVER MENU ";
        cout << "\n===============================";
        cout << "\n1. Single-Point Crossover";
        cout << "\n2. Two-Point Crossover";
        cout << "\n3. Multi-Point Crossover";
        cout << "\n4. Uniform Crossover";
        cout << "\n5. Uniform Crossover with Mask";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            singlePointCrossover(parent1, parent2);
            break;
        case 2:
            twoPointCrossover(parent1, parent2);
            break;
        case 3: {
            int numPoints;
            cout << "Enter number of crossover points: ";
            cin >> numPoints;
            multiPointCrossover(parent1, parent2, numPoints);
            break;
        }
        case 4:
            uniformCrossover(parent1, parent2);
            break;
        case 5:
            uniformCrossoverWithMask(parent1, parent2);
            break;
        case 6:
            cout << "\nExiting... Thank you!\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}             
