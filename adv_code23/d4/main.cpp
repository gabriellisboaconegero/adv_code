#include <bits/stdc++.h>
using namespace std;

void part1(char *input){
    ifstream file;
    string line;
    size_t sum = 0;

    file.open(input);

    while(getline(file, line)){
        vector<int> winning;
        vector<int> mynums;
        vector<int>::iterator it;
        int n;
        size_t pos, div;
        line.erase(0, line.find_first_of("0123456789", line.find(":")));
        while ((pos = line.find(" ")) <= (div = line.find("|"))){
            n = stoi(line.substr(0, pos));
            winning.push_back(n);
            line.erase(0, min(div, line.find_first_of("0123456789", pos)));
        }
        line.erase(0, line.find_first_of("0123456789"));
        while ((pos = line.find(" ")) != string::npos){
            n = stoi(line.substr(0, pos));
            mynums.push_back(n);
            line.erase(0, line.find_first_of("0123456789", pos));
        }
        n = stoi(line.substr(0, line.length()));
        mynums.push_back(n);

        vector<int> res(mynums.size() + winning.size());
        sort(winning.begin(), winning.end());
        sort(mynums.begin(), mynums.end());

        it = set_intersection(winning.begin(), winning.end(), mynums.begin(), mynums.end(), res.begin());
        res.resize(it-res.begin());

        if (res.size() != 0)
            sum += 1<<(res.size()-1);
    }

    file.close();
    cout << "part1: " << sum << endl;
}

void part2(char *input){
    ifstream file;
    string line;
    string s;
    int num;

    file.open(input);

    while (getline(file, line)){
        vector<int> winning;
        vector<int> mynums;
        istringstream iss(line);
        iss >> s;

        iss >> s;
        while(!(iss >> num))
            winning.push_back(num);
        return;
        while (!(iss >> num))
            mynums.push_back(num);

        for (auto i : winning)
            cout << i << " ";
        cout << endl;
        for (auto i : mynums)
            cout << i << " ";
        cout << endl;
    }
    
    file.close();
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
