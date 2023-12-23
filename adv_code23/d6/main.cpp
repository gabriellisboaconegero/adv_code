#include <bits/stdc++.h>
using namespace std;

#define u64 uint64_t
#define i64 int64_t

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    u64 num;

    getline(file, line);
    istringstream iss(line.substr(line.find_first_of("0123456789")));
    vector<u64> b;
    while (iss >> num)
        b.push_back(num);

    getline(file, line);
    istringstream iss2(line.substr(line.find_first_of("0123456789")));
    vector<u64> c;
    while (iss2 >> num)
        c.push_back(num);

    u64 res = 1;
    for (size_t i = 0; i < b.size(); i++){
        double delta = (b[i]*b[i] - 4*c[i]);
        i64 x1 = floor((b[i]-sqrt(delta))/2)+1;
        i64 x2 = ceil((b[i]+sqrt(delta))/2);
        res *= x2-x1;
    }


    cout << "Part1: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);

    return 0;
}
