#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

struct pos_t {
    i64 x;
    i64 y;

    bool operator==(const struct pos_t &p) const{
        return x == p.x && y == p.y;
    }
    bool operator!=(const struct pos_t &p) const{
        return !(x == p.x && y == p.y);
    }
};

#define N 0
#define L 1
#define S 2
#define O 3
i64 DIR_Y[4] = {
    [N]=-1,
    [L]=0,
    [S]=1,
    [O]=0
};
i64 DIR_X[4] = {
    [N]=0,
    [L]=1,
    [S]=0,
    [O]=-1
};

struct state_t {
    struct pos_t pos;
    int dir;
    int steps;

    bool operator==(const struct state_t &s) const {
        return pos == s.pos && dir == s.dir && steps == s.steps;
    }
    bool operator!=(const struct state_t &s) const {
        return !(pos == s.pos && dir == s.dir && steps == s.steps);
    }
    bool operator<(const struct state_t &s) const {
        return pos.x < s.pos.x || (pos.x == s.pos.x && pos.y < s.pos.y);
    }
};

struct info_t {
    struct state_t parent;
    bool closed;
    i64 g;
    i64 f;
};

struct state_map_t {
    vector<vector<vector<vector<struct info_t>>>> data;

    struct info_t &operator[](struct state_t a){
        struct info_t &t = data[a.pos.y][a.pos.x][a.dir][a.steps];
        return t;
    }
};


i64 h(struct pos_t s, struct pos_t e){
    return e.x - s.x + e.y - s.y;
}

vector<struct state_t> neighbors(struct state_t s, vector<vector<int>> &grid){
    vector<struct state_t> res;
    struct state_t r = s;

    // Seguir mesma direção
    if (s.steps < 3){
        r.pos.x += DIR_X[r.dir];
        r.pos.y += DIR_Y[r.dir];
        r.steps++;
        if (0 <= r.pos.x && r.pos.x < grid.front().size() &&
            0 <= r.pos.y && r.pos.y < grid.size())
            res.push_back(r);
    }

    // Vira esquerda
    r = s;
    r.dir = (r.dir + 1) % 4;
    r.pos.x += DIR_X[r.dir];
    r.pos.y += DIR_Y[r.dir];
    r.steps = 1;
    if (0 <= r.pos.x && r.pos.x < grid.front().size() &&
        0 <= r.pos.y && r.pos.y < grid.size())
        res.push_back(r);

    // Vira direita
    r = s;
    r.dir = (r.dir + 3) % 4;
    r.pos.x += DIR_X[r.dir];
    r.pos.y += DIR_Y[r.dir];
    r.steps = 1;
    if (0 <= r.pos.x && r.pos.x < grid.front().size() &&
        0 <= r.pos.y && r.pos.y < grid.size())
        res.push_back(r);

    return res;
}

vector<struct pos_t> reconstruct_path(struct state_t c, struct pos_t start, struct state_map_t details){
    vector<struct pos_t> res;
    while (c.pos != start){
        res.push_back(c.pos);
        c = details[c].parent;
    }

    return res;
}

vector<struct pos_t> a_star(vector<vector<int>> grid, struct pos_t start, struct pos_t end){
    vector<pair<i64, struct state_t>> openSet;
    struct state_map_t details;
    for (size_t y = 0; y < grid.size(); y++){
        vector<vector<vector<struct info_t>>> a;
        for (size_t x = 0; x < grid.front().size(); x++){
            vector<vector<struct info_t>> b;
            for (size_t d = 0; d < 4; d++){
                vector<struct info_t> c;
                for (size_t s = 0; s < 4; s++){
                    c.push_back({{-1, -1, 0, 0}, false, numeric_limits<i64>::max(), numeric_limits<i64>::max()});
                }
                b.push_back(c);
            }
            a.push_back(b);
        }
        details.data.push_back(a);
    }

    auto heap_comp = [](const pair<i64, struct state_t> &a, const pair<i64, struct state_t> &b){
        return a.first > b.first;
    };

    struct state_t q;
    q.pos.x = start.x;
    q.pos.y = start.y;
    q.dir = L;
    q.steps = 3;
    struct state_t start_state = q;

    details[q].parent = {-1, -1, L, 1};
    details[q].g = 0;
    details[q].f = details[q].g + h(start, end);

    openSet.push_back(make_pair(details[q].f, q));

    q.dir = S;
    details[q].parent = {-1, -1, S, 1};
    details[q].g = 0;
    details[q].f = details[q].g + h(start, end);
    openSet.push_back(make_pair(details[q].f, q));
    push_heap(openSet.begin(), openSet.end(), heap_comp);

    while(!openSet.empty()){
        pop_heap(openSet.begin(), openSet.end(), heap_comp);
        const pair<i64, struct state_t> pq = openSet.back();
        q = pq.second;
        openSet.pop_back();

        if (q.pos == end){
            return reconstruct_path(q, start, details);
        }
        details[q].closed = true;

        for (auto nei : neighbors(q, grid)){
            // overload details[]
            struct info_t nq;
            nq.g = details[q].g + grid[nei.pos.y][nei.pos.x];
            nq.f = nq.g + h(nei.pos, end);
            nq.parent = q;

            if (!details[nei].closed && nq.g < details[nei].g){
                details[nei].parent = q;
                details[nei].f = nq.f;
                details[nei].g = nq.g;
                auto it = find_if(openSet.begin(), openSet.end(), [nei](auto a){return a.second == nei;});
                if (it == openSet.end()){
                    openSet.push_back(make_pair(nq.f, nei));
                    push_heap(openSet.begin(), openSet.end(), heap_comp);
                }else{
                    it->first = nq.f;
                    make_heap(openSet.begin(), openSet.end(), heap_comp);
                }
            }
        }
    }

    return reconstruct_path(q, start, details);
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;
    vector<vector<int>> grid;
    string line;
    while (getline(file, line)){
        grid.push_back(vector<int>());
        for (auto c : line)
            grid.back().push_back(c - '0');
    }
    file.close();

    i64 res = 0;
    for (auto s : a_star(grid, {0, 0}, {grid.front().size()-1, grid.size()-1})){
        res += grid[s.y][s.x];
    }

    cout << "Part1: " << res << endl;

}

int main(int argc, char **argv){
    part1(argv[1]);

    return 0;
}
