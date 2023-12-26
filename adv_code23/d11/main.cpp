#include <bits/stdc++.h>
using namespace std;

#define u64 uint64_t
#define i64 int64_t

struct galaxy_t {
    int x;
    int y;
    string rep(){
        return "("+to_string(x)+", "+to_string(y)+")";
    }
};

u64 dist(struct galaxy_t a, struct galaxy_t b, vector<bool> &warpRow, vector<bool> &warpCol, int warp){
    int maxX = max(a.x, b.x);
    int minX = min(a.x, b.x);
    int maxY = max(a.y, b.y);
    int minY = min(a.y, b.y);
    u64 res = maxX - minX + maxY - minY;

    for (int i = minX; i < maxX; i++){
        if (warpCol[i])
            res += warp-1;
    }

    for (int i = minY; i < maxY; i++){
        if (warpRow[i])
            res += warp-1;
    }

    return res;
}

void part1_2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    vector<struct galaxy_t> galaxys;
    vector<bool> warpCol(10000, true);
    vector<bool> warpRow(10000, true);
    string line;
    int y, x;
    y = x = 0;
    while (getline(file, line)){
        x = 0;
        for (auto c : line){
            switch (c){
                case '#':
                    warpCol[x] = false;
                    warpRow[y] = false;
                    galaxys.push_back((struct galaxy_t){.x=x, .y=y});
                    break;
            }
            x++;
        }
        y++;
    }

    u64 res1 = 0;
    u64 res2 = 0;
    for (size_t i = 0; i < galaxys.size()-1; i++){
        for (size_t j = i + 1; j < galaxys.size(); j++){
            u64 d1 = dist(galaxys[i], galaxys[j], warpRow, warpCol, 2);
            u64 d2 = dist(galaxys[i], galaxys[j], warpRow, warpCol, 1000000);
            //cout << "(" << i+1 << ", " << j+1 << ")" << ": " << d << endl;
            res1 += d1;
            res2 += d2;
        }
    }
    
    cout << "Part1: " << res1 << endl;
    cout << "Part2: " << res2 << endl;
}

int main(int argc, char **argv){
    part1_2(argv[1]);

    return 0;
}
