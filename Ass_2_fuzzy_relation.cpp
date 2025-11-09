#include <iostream>
#include <algorithm>
using namespace std;

class FuzzyRelation {
    int rows, cols;
    float rel[10][10];
public:
    void input() {
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;

        cout << "Enter membership values (0 to 1):\n";
        for(int i=0;i<rows;i++) {
            for(int j=0;j<cols;j++) {
                cout << "Element [" << i+1 << "][" << j+1 << "]: ";
                cin >> rel[i][j];
                if(rel[i][j]<0 || rel[i][j]>1) {
                    cout << "Invalid! Must be between 0 and 1.\n";
                    j--; // re-enter
                }
            }
        }
    }

    void display() {
        for(int i=0;i<rows;i++) {
            cout << "{ ";
            for(int j=0;j<cols;j++) {
                cout << rel[i][j] << " ";
            }
            cout << "}\n";
        }
    }

    int getRows() { return rows; }
    int getCols() { return cols; }
    float get(int i, int j) { return rel[i][j]; }

    // Complement
    void complement() {
        cout << "Complement:\n";
        for(int i=0;i<rows;i++) {
            cout << "{ ";
            for(int j=0;j<cols;j++) {
                cout << 1 - rel[i][j] << " ";
            }
            cout << "}\n";
        }
    }

    // Union
    static void unionRel(FuzzyRelation R, FuzzyRelation S) {
        if(R.rows!=S.rows || R.cols!=S.cols) {
            cout << "Relations must be of same size!\n"; return;
        }
        cout << "Union:\n";
        for(int i=0;i<R.rows;i++) {
            cout << "{ ";
            for(int j=0;j<R.cols;j++) {
                cout << max(R.rel[i][j], S.rel[i][j]) << " ";
            }
            cout << "}\n";
        }
    }

    // Intersection
    static void intersectionRel(FuzzyRelation R, FuzzyRelation S) {
        if(R.rows!=S.rows || R.cols!=S.cols) {
            cout << "Relations must be of same size!\n"; return;
        }
        cout << "Intersection:\n";
        for(int i=0;i<R.rows;i++) {
            cout << "{ ";
            for(int j=0;j<R.cols;j++) {
                cout << min(R.rel[i][j], S.rel[i][j]) << " ";
            }
            cout << "}\n";
        }
    }

    // Composition (max-min method)
    static void composition(FuzzyRelation R, FuzzyRelation S) {
        if(R.cols != S.rows) {
            cout << "Invalid dimensions for composition!\n"; return;
        }
        cout << "Composition (R ∘ S):\n";
        for(int i=0;i<R.rows;i++) {
            cout << "{ ";
            for(int j=0;j<S.cols;j++) {
                float val = 0.0;
                for(int k=0;k<R.cols;k++) {
                    val = max(val, min(R.rel[i][k], S.rel[k][j]));
                }
                cout << val << " ";
            }
            cout << "}\n";
        }
    }
};

int main() {
    FuzzyRelation R, S;
    int choice;
    cout << "Enter Relation R:\n";
    R.input();
    cout << "Enter Relation S:\n";
    S.input();

    do {
        cout << "\n--- Fuzzy Relational Operations Menu ---\n";
        cout << "1. Display Relations\n";
        cout << "2. Union (R U S)\n";
        cout << "3. Intersection (R ∩ S)\n";
        cout << "4. Complement of R\n";
        cout << "5. Complement of S\n";
        cout << "6. Composition (R o S)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Relation R:\n"; R.display();
                cout << "Relation S:\n"; S.display();
                break;
            case 2:
                FuzzyRelation::unionRel(R,S);
                break;
            case 3:
                FuzzyRelation::intersectionRel(R,S);
                break;
            case 4:
                R.complement();
                break;
            case 5:
                S.complement();
                break;
            case 6:
                FuzzyRelation::composition(R,S);
                break;
            case 0:
                cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    return 0;
}