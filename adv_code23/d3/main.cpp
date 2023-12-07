#include <bits/stdc++.h>
using namespace std;

int check_parts(vector<string> map, int i, int j){
    for (int di = -1; di <= 1; di++){
        for (int dj = -1; dj <= 1; dj++){
            if ((0 <= i+di && i+di < map.size()) && 
                (0 <= j+dj && j+dj < map[i].length()) &&
                (map[i+di][j+dj] != '.') &&
                !('0' <= map[i+di][j+dj] && map[i+di][j+dj] <= '9'))
                return 1;
        }
    }

    return 0;
}

void part1(){
    vector<string> map;
    string line;
    size_t num, sum;
    char p;
    int is_part_number;
    sum = 0;
    while(getline(cin, line))
        map.push_back(line);
    for (int i = 0; i < map.size(); i++){
        num = 0;
        is_part_number = 0;
        for (int j = 0; j < map[i].length(); j++){
            p = map[i][j];
            if ('0' <= p && p <= '9'){
                num = num*10 + p-'0';
                if (!is_part_number && check_parts(map, i, j))
                    is_part_number = 1;
            }else{
                if (is_part_number){
                    sum += num;
                }
                is_part_number = 0;
                num = 0;
            }
        }
        if (is_part_number){
            sum += num;
        }
    }
    cout << "part1: " << sum << endl;
}

int is_gear(vector<vector<int>> part_map, int i, int j){
    int counter = 0;
    map<int, int> nums;
    for (int di = -1; di <= 1; di++){
        for (int dj = -1; dj <= 1; dj++){
            if ((0 <= i+di && i+di < part_map.size()) && 
                (0 <= j+dj && j+dj < part_map[i].size()) &&
                (part_map[i+di][j+dj] != 0) &&
                (nums[part_map[i+di][j+dj]] != 1)){
                    nums[part_map[i+di][j+dj]] = 1;
                    counter++;
            }
        }
    }

    return counter == 2;
}

size_t gear_ratio(vector<vector<int>> part_map, int i, int j){
    size_t counter = 1;
    map<int, int> nums;
    for (int di = -1; di <= 1; di++){
        for (int dj = -1; dj <= 1; dj++){
            if ((0 <= i+di && i+di < part_map.size()) && 
                (0 <= j+dj && j+dj < part_map[i].size()) &&
                (part_map[i+di][j+dj] != 0) &&
                (nums[part_map[i+di][j+dj]] != 1)){
                    nums[part_map[i+di][j+dj]] = 1;
                    counter*=part_map[i+di][j+dj];
            }
        }
    }

    return counter;
}

void part2(){
    size_t sum = 0;
    size_t num, start, end, found;
    vector<string> map;
    string line;
    while(getline(cin, line))
        map.push_back(line);
    vector<vector<int>> part_map(map.size(), vector<int>(map[0].length(), 0));
    for (int i = 0; i < map.size(); i++){
        start = map[i].find_first_of("0123456789", 0);
        while (start != string::npos){
            num = 0;
            end = map[i].find_first_not_of("0123456789", start);
            for (size_t k = start; k < map[i].length() && k < end; k++)
                num = num*10 + map[i][k]-'0';
            for (size_t k = start; k < map[i].length() && k < end; k++)
                part_map[i][k] = num;
            start = map[i].find_first_of("0123456789", end);
        }
    }
    for (int i = 0; i < part_map.size(); i++){
        found = map[i].find("*");
        while(found != string::npos){
            if (is_gear(part_map, i, found))
                sum += gear_ratio(part_map, i, found);
            found = map[i].find("*", found+1);
        }
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
