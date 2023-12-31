#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

struct point_t {
    i64 x;
    i64 y;
};

void part1(char *input){
    ifstream file;
    file.open(input);
    if  (!file.is_open())
        return;

    string line;
    vector<struct point_t> pts(1, {0, 0});
    char dir;
    int num;
    i64 x, y, b;
    x = y = 0;
    b = 1;
    i64 h;
    while (getline(file, line)){
        struct point_t p;
        sscanf(line.data(), "%c %d (#%x)", &dir, &num, &h);
        switch (dir){
            case 'U':
                y += num;
                break;
            case 'D':
                y -= num;
                break;
            case 'R':
                x += num;
                break;
            case 'L':
                x -= num;
                break;
        }
        p.x = x;
        p.y = y;
        b += num;
        pts.push_back(p);
    }
    file.close();

    pts.push_back({0, 0});

    i64 a = 0;
    // shoelace theorem
    for (size_t k = 0; k < pts.size()-1; k++)
        a += (pts[k].y + pts[k+1].y)*(pts[k+1].x - pts[k].x);
    a /= 2;

    // pick's theorem
    i64 res = a + 1 + b/2;
    cout << "Part1: " << res << endl;
}

char dir_map[4] = {
    'R',
    'D',
    'L',
    'U'
};

void part2(char *input){
    ifstream file;
    file.open(input);
    if  (!file.is_open())
        return;

    string line;
    vector<struct point_t> pts(1, {0, 0});
    char dir;
    i64 x, y, b, num;
    x = y = 0;
    b = 1;
    i64 h;
    while (getline(file, line)){
        struct point_t p;
        sscanf(line.data(), "%c %d (#%x)", &dir, &num, &h);
        num = h / 16;
        switch (dir_map[h % 16]){
            case 'U':
                y += num;
                break;
            case 'D':
                y -= num;
                break;
            case 'R':
                x += num;
                break;
            case 'L':
                x -= num;
                break;
        }
        p.x = x;
        p.y = y;
        b += num;
        pts.push_back(p);
    }
    file.close();

    pts.push_back({0, 0});

    i64 a = 0;
    // shoelace theorem
    for (size_t k = 0; k < pts.size()-1; k++)
        a += (pts[k].y + pts[k+1].y)*(pts[k+1].x - pts[k].x);
    a /= 2;

    // pick's theorem
    i64 res = a + 1 + b/2;
    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);

    return 0;
}
