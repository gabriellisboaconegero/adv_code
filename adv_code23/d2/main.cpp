#include <bits/stdc++.h>
using namespace std;

void part1(){
    string line;
    int sum = 0;
    size_t found, i;
    int game_id;
    int max_r = 12;
    int max_g = 13;
    int max_b = 14;
    int n, invalid;
    while (getline(cin, line)){
        found  = line.find(":");
        game_id = stoi(line.substr(5, found));
        line.erase(0, found+2);
        invalid = 0;
        sum += game_id;
        while(!invalid){
            i = 0;
            while ('0' <= line[i] && line[i] <= '9'){
                i++;
            }
            n = stoi(line.substr(0, i));
            switch (line[i+1]){
                case 'r': 
                    if (n > max_r){
                        sum -= game_id;
                        invalid = 1;
                    }
                    break;
                case 'g': 
                    if (n > max_g){
                        sum -= game_id;
                        invalid = 1;
                    }
                    break;
                case 'b': 
                    if (n > max_b){
                        sum -= game_id;
                        invalid = 1;
                    }
                    break;
            }
            while (!('0' <= line[i] && line[i] <= '9') && i < line.length()){
                i++;
            }
            if (i >= line.length())
                break;
            line.erase(0, i);
        }
    }
    cout << "part1: " << sum << endl;
}

void part2(){
    string line;
    int sum = 0;
    size_t found, i;
    int max_r, max_g, max_b;
    int n;
    while (getline(cin, line)){
        found  = line.find(":");
        line.erase(0, found+2);
        max_r = max_g = max_b = 0;
        while(1){
            i = 0;
            while ('0' <= line[i] && line[i] <= '9'){
                i++;
            }
            n = stoi(line.substr(0, i));
            switch (line[i+1]){
                case 'r': 
                    max_r = max(max_r, n);
                    break;
                case 'g': 
                    max_g = max(max_g, n);
                    break;
                case 'b': 
                    max_b = max(max_b, n);
                    break;
            }
            while (!('0' <= line[i] && line[i] <= '9') && i < line.length()){
                i++;
            }
            if (i >= line.length())
                break;
            line.erase(0, i);
        }
        sum += max_r * max_g * max_b;
    }
    cout << "part2: " << sum << endl;
}

int main(){
    part1();
    cin.clear();
    cin.seekg(0);
    part2();
    return 0;
}
