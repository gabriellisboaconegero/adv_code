#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

#define VERT 0
#define HORI 1
struct cell_t {
    bool is_ray[2];
    bool has_light;
    char ch;
};

complex<int> rotate_left(complex<int> n){
    return n*complex<int>(0, 1);
}

complex<int> rotate_right(complex<int> n){
    return n*complex<int>(0, -1);
}

void simulate_ray(vector<vector<struct cell_t>> &grid, complex<int> pos, complex<int> dir){
    pos += dir;
    if (!(0 <= pos.real() && pos.real() < grid[0].size()) ||
        !(0 <= pos.imag() && pos.imag() < grid.size()) ||
        grid[pos.imag()][pos.real()].is_ray[dir.real() != VERT])
        return;

    while (0 <= pos.real() && pos.real() < grid[0].size() &&
           0 <= pos.imag() && pos.imag() < grid.size() &&
           grid[pos.imag()][pos.real()].ch == '.')
    {
        grid[pos.imag()][pos.real()].is_ray[dir.real() != VERT] = true;
        pos += dir;
    }

    if (!(0 <= pos.real() && pos.real() < grid[0].size()) ||
        !(0 <= pos.imag() && pos.imag() < grid.size()))
        return;

    grid[pos.imag()][pos.real()].has_light = true;
    switch (grid[pos.imag()][pos.real()].ch){
        case '|':
            if (dir.imag())
                simulate_ray(grid, pos, dir);
            else {
                simulate_ray(grid, pos, rotate_right(dir));
                simulate_ray(grid, pos, rotate_left(dir));
            }
            break;
        case '-':
            if (dir.real())
                simulate_ray(grid, pos, dir);
            else {
                simulate_ray(grid, pos, rotate_right(dir));
                simulate_ray(grid, pos, rotate_left(dir));
            }
            break;
        case '/':
            if (dir.imag())
                simulate_ray(grid, pos, rotate_left(dir));
            else
                simulate_ray(grid, pos, rotate_right(dir));
            break;
        case '\\':
            if (dir.real())
               simulate_ray(grid, pos, rotate_left(dir));
            else
               simulate_ray(grid, pos, rotate_right(dir));
            break;
    }
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    vector<vector<struct cell_t>> grid;
    string line;
    while (getline(file, line)){
        grid.push_back(vector<struct cell_t>());
        for (auto c : line){
            struct cell_t cell = {0};
            cell.ch = c;
            grid.back().push_back(cell);
        }
    }
    file.close();

    simulate_ray(grid, complex<int>(-1, 0), complex<int>(1, 0));
    int res = 0;
    for (auto row : grid)
        res += count_if(row.begin(), row.end(), 
                [](struct cell_t c){return c.is_ray[VERT] || c.is_ray[HORI] || c.has_light;});
    
    cout << "Part1: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);

    return 0;
}
