#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find membership of an element in a fuzzy set
float getMembership(const vector<pair<int, float>>& set, int element) {
    for (auto& p : set) {
        if (p.first == element)
            return p.second;
    }
    return 0.0; // element not found -> membership = 0
}

// Fuzzy Union: μA∪B(x) = max(μA(x), μB(x))
void uni(const vector<pair<int, float>>& A, const vector<pair<int, float>>& B) {
    vector<int> universe;

    // Build combined universe (unique elements from both sets)
    for (auto& p : A) universe.push_back(p.first);
    for (auto& p : B)
        if (find(universe.begin(), universe.end(), p.first) == universe.end())
            universe.push_back(p.first);

    cout << "Union of two fuzzy sets -> { ";
    for (size_t i = 0; i < universe.size(); i++) {
        int elem = universe[i];
        float mu = max(getMembership(A, elem), getMembership(B, elem));
        cout << "(" << elem << ", " << mu << ")";
        if (i != universe.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

// Fuzzy Intersection: μA∩B(x) = min(μA(x), μB(x))
void inter(const vector<pair<int, float>>& A, const vector<pair<int, float>>& B) {
    vector<int> universe;

    for (auto& p : A) universe.push_back(p.first);
    for (auto& p : B)
        if (find(universe.begin(), universe.end(), p.first) == universe.end())
            universe.push_back(p.first);

    cout << "Intersection of two fuzzy sets -> { ";
    for (size_t i = 0; i < universe.size(); i++) {
        int elem = universe[i];
        float mu = min(getMembership(A, elem), getMembership(B, elem));
        cout << "(" << elem << ", " << mu << ")";
        if (i != universe.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

// Fuzzy Complement: μA′(x) = 1 − μA(x)
void complement(const vector<pair<int, float>>& A, char setName) {
    cout << "Complement of set " << setName << " -> { ";
    for (size_t i = 0; i < A.size(); i++) {
        int elem = A[i].first;
        float mu = 1 - A[i].second;
        cout << "(" << elem << ", " << mu << ")";
        if (i != A.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

int main() {
    int nA, nB;
    cout << "Enter number of elements in set A: ";
    cin >> nA;
    vector<pair<int, float>> A, B;

    cout << "Enter elements of set A (element and its membership value):\n";
    for (int i = 0; i < nA; i++) {
        int elem;
        float mem;
        cout << "Element " << i + 1 << ": ";
        cin >> elem;
        cout << "Membership value for " << elem << ": ";
        cin >> mem;
        A.push_back({elem, mem});
    }

    cout << "Enter number of elements in set B: ";
    cin >> nB;

    cout << "Enter elements of set B (element and its membership value):\n";
    for (int i = 0; i < nB; i++) {
        int elem;
        float mem;
        cout << "Element " << i + 1 << ": ";
        cin >> elem;
        cout << "Membership value for " << elem << ": ";
        cin >> mem;
        B.push_back({elem, mem});
    }

    cout << endl;
    uni(A, B);
    inter(A, B);
    complement(A, 'A');
    complement(B, 'B');

    return 0;
}