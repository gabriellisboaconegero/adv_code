#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

#define Pos_t pair<size_t, size_t>
#define N 0
#define L 1
#define S 2
#define O 3
struct pipe_t {
    bool is_start;
    bool visited;
    char c;
    //   N 
    // O   L   -> {N, L, S, O}
    //   S
    bool edges[4];
};


#define START (struct pipe_t){.is_start=true, .visited=false, .edges={true, true, true, true}}
#define GROUND (struct pipe_t){.is_start=false, .visited=false, .edges={false, false, false, false}}
#define OL (struct pipe_t){.is_start=false, .visited=false, .edges={false, true, false, true}}
#define SN (struct pipe_t){.is_start=false, .visited=false, .edges={true, false, true, false}}
#define SO (struct pipe_t){.is_start=false, .visited=false, .edges={false, false, true, true}}
#define SL (struct pipe_t){.is_start=false, .visited=false, .edges={false, true, true, false}}
#define NL (struct pipe_t){.is_start=false, .visited=false, .edges={true, true, false, false}}
#define NO (struct pipe_t){.is_start=false, .visited=false, .edges={true, false, false, true}}

map<char, struct pipe_t> pipe_map = {
    {'S', START},
    {'.', GROUND},
    {'-', OL},
    {'|', SN},
    {'7', SO},
    {'F', SL},
    {'L', NL},
    {'J', NO}
};

map<char, string> map_char = {
    {'-', "─"},
    {'|', "│"},
    {'L', "└"},
    {'J', "┘"},
    {'7', "┐"},
    {'F', "┌"}
};

bool valid_pos(size_t x, size_t y, size_t my, size_t mx){
    return (0 <= x && x < mx) && (0 <= y && y < my);
}

bool next_pos(Pos_t &p, vector<vector<struct pipe_t>> &maze){
    size_t x = p.second;
    size_t y = p.first;
    struct pipe_t h = maze[y][x];
    maze[y][x].visited = true;
    if (h.edges[N] &&
            valid_pos(x, y-1, maze.size(), maze.front().size()) &&
            !maze[y-1][x].visited &&
            maze[y-1][x].edges[S])
    {
        p.first--;
        return true;
    }
    if (h.edges[S] &&
            valid_pos(x, y+1, maze.size(), maze.front().size()) &&
            !maze[y+1][x].visited &&
            maze[y+1][x].edges[N])
    {
        p.first++;
        return true;
    }
    if (h.edges[L] &&
            valid_pos(x+1, y, maze.size(), maze.front().size()) &&
            !maze[y][x+1].visited &&
            maze[y][x+1].edges[O])
    {
        p.second++;
        return true;
    }
    if (h.edges[O] &&
            valid_pos(x-1, y, maze.size(), maze.front().size()) &&
            !maze[y][x-1].visited &&
            maze[y][x-1].edges[L])
    {
        p.second--;
        return true; 
    }

    return false;
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;
    u64 res = 1;

    string line;
    vector<vector<struct pipe_t>> maze;
    Pos_t pos;
    while (getline(file, line)){
        maze.push_back(vector<struct pipe_t>());
        for (auto c : line){
            struct pipe_t pi = pipe_map[c];
            pi.c = c;
            maze.back().push_back(pi);
            if (c == 'S')
                pos = make_pair(maze.size()-1, maze.back().size()-1);
        }
    }

    while(next_pos(pos, maze)){
        res++;
    };

    cout << "Part1: " << res << ", " << res/2 << endl;
}

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;
    u64 res = 0;

    string line;
    vector<vector<struct pipe_t>> maze;
    Pos_t pos;
    while (getline(file, line)){
        maze.push_back(vector<struct pipe_t>());
        for (auto c : line){
            struct pipe_t pi = pipe_map[c];
            pi.c = c;
            maze.back().push_back(pi);
            if (c == 'S')
                pos = make_pair(maze.size()-1, maze.back().size()-1);
        }
    }

    Pos_t start = pos;
    while(next_pos(pos, maze));
    bool start_edges[4] = {false};
    start_edges[N] = maze[start.first-1][start.second].edges[S];
    start_edges[L] = maze[start.first][start.second+1].edges[O];
    start_edges[S] = maze[start.first+1][start.second].edges[N];
    start_edges[O] = maze[start.first][start.second-1].edges[L];

    maze[start.first][start.second].edges[N] = start_edges[N];
    maze[start.first][start.second].edges[L] = start_edges[L];
    maze[start.first][start.second].edges[S] = start_edges[S];
    maze[start.first][start.second].edges[O] = start_edges[O];

    bool is_in = false;
    for (auto v : maze){
        for (auto cell : v){
            if (is_in && !cell.visited){
                res++;
                cout << "\x1b[1;92mI\x1b[0m";
                continue;
            }
            if (cell.visited && cell.edges[S])
                is_in = !is_in;

            if (cell.is_start)
                cout << "\x1b[1;91mS\x1b[0m";
            else if (!is_in && !cell.visited)
                cout << "\x1b[1;94mO\x1b[0m";
            else
                cout << map_char[cell.c];
        }
        cout << endl;
    }

    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
