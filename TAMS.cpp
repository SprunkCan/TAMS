#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
using std::string;
using std::map;
using std::vector;
using std::cin; using std::cout; using std::endl;

// Variable Initialization
short grid_W = 10; // field width
short grid_H = 10; // field height
short mines = (grid_H*grid_W)/10; // mine count (10% of field tiles)
short flags = mines; // flag count, same as mines at capacity
// Set of all special stringacters for use in field
map<string, string> stringset = {
    {"mine", "#"},
    {"flag", "@"}
};

vector<vector<string>> populate(vector<vector<string>> field) {
    vector<string> mt_vec;
    for (int a=0; a<grid_H; a++) {
        field.push_back(mt_vec);
        for (int b=0; b<grid_W; b++){
            field[a].push_back(".");
        }
    }
    return field;
}

void display(vector<vector<string>> field){
    for (vector<string> row : field) {
        for (string col : row){
            cout << col << ' ';
        }
        cout << endl;
    }
}

vector<vector<string>> generate(vector<vector<string>> field) {
    vector<vector<string>> field_mines;
    field_mines = populate(field_mines);
    // generate bomb positions
    srand(time(0)); // rand seed based on time
    for (int i=0; i<mines; i++) {
        int x = rand()%grid_W;
        int y = rand()%grid_H;
        field_mines[y][x] = stringset["mine"];
    }
    // generate tile numerical values
    int adj; // count of how many bombs are adjacent to [x,y]
    int n = grid_H;
    int m = grid_W;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            adj = 0;
            for (int dx = (i > 0 ? -1 : 0); dx <= (i < n ? 1 : 0); ++dx) {
                for (int dy = (j > 0 ? -1 : 0); dy <= (j < m ? 1 : 0); ++dy) {
                    if (dx != 0 || dy != 0) {
                        if (field_mines[i + dx][j + dy] == stringset["mine"]){
                            adj++;
                        }
                    }
                }
            }
            field[i][j] = std::to_string(adj);
        }
    }

    display(field_mines);
    cout<<"-------------------------------"<<endl;

    return field;
}


int main() {
    vector<vector<string>> field_data;
    vector<vector<string>> field_vis;
    field_data = populate(field_data);
    field_vis = populate(field_vis);

    field_data = generate(field_data);
    display(field_data);
    cout<<"-------------------------------"<<endl;
    display(field_vis);
}