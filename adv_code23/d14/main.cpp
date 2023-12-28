#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    i64 res = 0;
    string line;
    vector<string> grid;
    while (getline(file, line))
        grid.push_back(line);
    file.close();

    vector<i64> dp(grid.size(), 0);
    for (size_t i = 0; i < grid.size(); i++){
        for (size_t j = 0; j < grid[i].size(); j++){
            switch (grid[i][j]){
                case 'O':
                    grid[i][j] = '.';
                    grid[dp[j]][j] = 'O';
                    res += grid.size()-dp[j];
                    dp[j]++;
                    break;
                case '#':
                    dp[j] = i+1;
                    break;
            }
        }
    }

    cout << "Part1: " << res << endl;
}

i64 cycle(vector<string> &grid){
    // norte
    vector<i64> dp(grid.size(), 0);
    for (size_t i = 0; i < grid.size(); i++){
        for (size_t j = 0; j < grid[i].size(); j++){
            switch (grid[i][j]){
                case 'O':
                    grid[i][j] = '.';
                    grid[dp[j]][j] = 'O';
                    dp[j]++;
                    break;
                case '#':
                    dp[j] = i+1;
                    break;
            }
        }
    }

    // oeste
    fill(dp.begin(), dp.end(), 0);
    for (size_t i = 0; i < grid.size(); i++){
        for (size_t j = 0; j < grid[i].size(); j++){
            switch (grid[i][j]){
                case 'O':
                    grid[i][j] = '.';
                    grid[i][dp[i]] = 'O';
                    dp[i]++;
                    break;
                case '#':
                    dp[i] = j+1;
                    break;
            }
        }
    }

    // sul
    i64 res = 0;
    fill(dp.begin(), dp.end(), grid.size()-1);
    for (i64 i = grid.size()-1; i >= 0; i--){
        for (size_t j = 0; j < grid[i].size(); j++){
            switch (grid[i][j]){
                case 'O':
                    grid[i][j] = '.';
                    grid[dp[j]][j] = 'O';
                    res+=grid.size()-dp[j];
                    dp[j]--;
                    break;
                case '#':
                    dp[j] = i-1;
                    break;
            }
        }
    }

    // leste
    fill(dp.begin(), dp.end(), grid.size()-1);
    for (size_t i = 0; i < grid.size(); i++){
        for (i64 j = grid.size()-1; j >= 0; j--){
            switch (grid[i][j]){
                case 'O':
                    grid[i][j] = '.';
                    grid[i][dp[i]] = 'O';
                    dp[i]--;
                    break;
                case '#':
                    dp[i] = j-1;
                    break;
            }
        }
    }
    return res;

}

bool grid_equal(vector<string> &g1, vector<string> &g2){
    for (size_t k = 0; k < g1.size(); k++)
        if (g1[k] != g2[k])
            return false;
    
    return true;
}

struct grid_t {
    i64 load;
    vector<string> grid;
};

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    i64 res = 0;
    string line;
    vector<string> grid;
    while (getline(file, line))
        grid.push_back(line);
    file.close();

    vector<struct grid_t> t;
    i64 start_cycle, end_cycle;
    bool found = false;
    for (size_t k = 0; k < 1000000000 && !found; k++){
        struct grid_t g;
        g.load = cycle(grid);
        g.grid = grid;
        t.push_back(g);
        for (size_t i = 0; i < t.size()-1 && !found; i++){
            for (size_t j = i+1; j < t.size() && !found; j++){
                found = grid_equal(t[i].grid, t[j].grid);
                start_cycle = i;
                end_cycle = j;
            }
        }
    }
    cout << start_cycle << ", " << end_cycle << endl;

    if (found){
        i64 cycle_size = end_cycle - start_cycle;
        cout << "Part2: " << t[start_cycle + (1000000000-start_cycle)%cycle_size - 1].load << endl;
    }
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);

    return 0;
}
