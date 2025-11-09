#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // For reverse() and random_shuffle()
using namespace std;

// Function to display chromosomes
void display(const string &label, const vector<int> &chrom) {
    cout << label << ": ";
    for (int bit : chrom)
        cout << bit;
    cout << endl; 
}

// ----- 1. Bit-Flip Mutation -----
void bitFlipMutation(vector<int> chrom) {
    int pos = rand() % chrom.size();
    cout << "\nBit flipped at position: " << pos << endl;
    chrom[pos] = 1 - chrom[pos]; // Flip bit
    display("Mutated Chromosome", chrom);
}

// ----- 2. Swap Mutation -----
void swapMutation(vector<int> chrom) {
    int pos1 = rand() % chrom.size();
    int pos2 = rand() % chrom.size();
    while (pos1 == pos2)
        pos2 = rand() % chrom.size();

    cout << "\nSwapped positions: " << pos1 << " and " << pos2 << endl;
    swap(chrom[pos1], chrom[pos2]);
    display("Mutated Chromosome", chrom);
}

// ----- 3. Inversion Mutation -----
void inversionMutation(vector<int> chrom) {
    int n = chrom.size();
    int start = rand() % n;
    int end = rand() % n;
    if (start > end)
        swap(start, end);

    cout << "\nInversion between positions: " << start << " and " << end << endl;
    reverse(chrom.begin() + start, chrom.begin() + end + 1);
    display("Mutated Chromosome", chrom);
}

// ----- 4. Scramble Mutation -----
void scrambleMutation(vector<int> chrom) {
    int n = chrom.size();
    int start = rand() % n;
    int end = rand() % n;
    if (start > end)
        swap(start, end);

    cout << "\nScramble between positions: " << start << " and " << end << endl;
    random_shuffle(chrom.begin() + start, chrom.begin() + end + 1);
    display("Mutated Chromosome", chrom);
}

// ----- 5. Uniform Mutation -----
void uniformMutation(vector<int> chrom) {
    float Pm;
    cout << "\nEnter mutation probability (0.0 - 1.0): ";
    cin >> Pm;

    for (int i = 0; i < chrom.size(); i++) {
        float r = static_cast<float>(rand()) / RAND_MAX;
        if (r < Pm)
            chrom[i] = 1 - chrom[i]; // Flip bit with probability
    }

    display("Mutated Chromosome", chrom);
}

// ----- Main Menu -----
int main() {
    srand(time(0));

    int n;
    cout << "Enter chromosome length: ";
    cin >> n;

    vector<int> chromosome(n);
    cout << "Enter chromosome (binary bits): ";
    for (int i = 0; i < n; i++)
        cin >> chromosome[i];

    int choice;
    do {
        cout << "\n====================================";
        cout << "\n  BINARY CODED GA - MUTATION MENU   ";
        cout << "\n====================================";
        cout << "\n1. Bit-Flip Mutation";
        cout << "\n2. Swap Mutation";
        cout << "\n3. Inversion Mutation";
        cout << "\n4. Scramble Mutation";
        cout << "\n5. Uniform Mutation";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        display("Original Chromosome", chromosome);

        switch (choice) {
        case 1:
            bitFlipMutation(chromosome);
            break;
        case 2:
            swapMutation(chromosome);
            break;
        case 3:
            inversionMutation(chromosome);
            break;
        case 4:
            scrambleMutation(chromosome);
            break;
        case 5:
            uniformMutation(chromosome);
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
