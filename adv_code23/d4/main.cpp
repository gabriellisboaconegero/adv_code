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
    vector<int> cards(500, 1);
    int num, card_id = 0;
    size_t sum = 0;

    file.open(input);

    while (getline(file, line)){
        vector<int> winning;
        vector<int> mynums;
        vector<int>::iterator it;

        s = line.substr(line.find(":")+2);
        istringstream iss(s.substr(0, s.find("|")));
        while(iss >> num)
            winning.push_back(num);
        istringstream iss1(s.substr(s.find("|")+2));
        while (iss1 >> num)
            mynums.push_back(num);

        vector<int> res(mynums.size() + winning.size());
        sort(winning.begin(), winning.end());
        sort(mynums.begin(), mynums.end());
        it = set_intersection(winning.begin(), winning.end(), mynums.begin(), mynums.end(), res.begin());
        res.resize(it-res.begin());

        sum += cards[card_id];
        for (size_t i = 1; i <= res.size(); i++){
            cards[card_id+i] += cards[card_id];
        }

        card_id++;
    }
    
    file.close();
    cout << "part2: " << sum << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
