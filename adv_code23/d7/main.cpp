#include <bits/stdc++.h>
using namespace std;

#define u64 uint64_t
#define i64 int64_t

map<char,u64> card_strength = {
    {'2', 0},
    {'3', 1},
    {'4', 2},
    {'5', 3},
    {'6', 4},
    {'7', 5},
    {'8', 6},
    {'9', 7},
    {'T', 8},
    {'J', 9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

enum HandType {
    High,
    OnePair,
    TwoPair,
    Three,
    FullHouse,
    Four,
    Five
};

struct hand_t {
    vector<u64> cards;
    enum HandType type;
    u64 bid;
};

enum HandType classify_hand(vector <u64> h){
    sort(h.begin(), h.end());
    int tb[5] = {0};
    int num = 0, i = 0;
    u64 n = h[i];
    for (i = 1; i < h.size(); i++){
        if (n != h[i]){
            tb[num]++;
            n = h[i];
            num = 0;
        }else{
            num++;
        }
    }
    tb[num]++;

    if (tb[4])
        return Five;
    if (tb[3])
        return Four;
    if (tb[2] && tb[1])
        return FullHouse;
    if (tb[2])
        return Three;
    if (tb[1] == 2)
        return TwoPair;
    if (tb[1])
        return OnePair;
    
    return High;
}

bool compare_hands(struct hand_t a, struct hand_t b){
    if (a.type != b.type)
        return a.type < b.type;
    for (size_t i = 0; i < a.cards.size(); i++){
        if (a.cards[i] != b.cards[i])
            return a.cards[i] < b.cards[i];
    }
    return false;
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if(!file.is_open())
        return;

    string line;
    vector<struct hand_t> hands;
    while (getline(file, line)){
        struct hand_t hand;
        while(line.front() != ' '){
            hand.cards.push_back(card_strength[line.front()]);
            line.erase(line.begin());
        }
        line.erase(line.begin());
        istringstream iss(line);
        u64 num;
        iss >> num;
        hand.bid = num;
        hand.type = classify_hand(hand.cards);
        hands.push_back(hand);
    }
    sort(hands.begin(), hands.end(), compare_hands);
    u64 num = 1;
    u64 res = 0;
    for (auto i : hands){
        res += num * i.bid;
        num++;
    }

    cout << "Part1: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    return 0;
}
