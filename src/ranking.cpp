#include "ranking.hpp"

#include <vector>
#include <stdlib.h>

using namespace std;

vector<pair<string, int>> merge(vector<pair<string, int>>& left, vector<pair<string, int>>& right) {

    vector<pair<string, int>> result;

    int i = 0;
    int j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i].second > right[j].second) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    if (i < left.size()) {
        while(i < left.size()) {
            result.push_back(left[i++]);
        }
    }

    if (j < right.size()) {
        while(j < right.size()) {
            result.push_back(right[j++]);
        }
    }

    return result;
}

void merge_sort(vector<pair<string, int>>& ranking_score) {

    if (ranking_score.size() == 1) return;

    int l = 0;
    int r = ranking_score.size();
    int middle = l + (r - l) / 2;

    vector<pair<string, int>> left = vector<pair<string, int>>(ranking_score.begin(), ranking_score.begin() + middle);
    vector<pair<string, int>> right = vector<pair<string, int>>(ranking_score.begin() + middle, ranking_score.end());

    thread left_thread(merge_sort, ref(left));
    thread right_thread(merge_sort, ref(right));

    left_thread.join();
    right_thread.join();

    ranking_score = merge(left, right);
}

void update_ranking() {

    ifstream file("ranking.txt");
    string line;
    vector<string> ranking;
    while (getline(file, line)) {
        ranking.push_back(line);
    }
    file.close();

    vector<pair<string, int>> ranking_score;

    for(auto& player : ranking) {
        string name = player.substr(0, player.find(','));
        string score = player.substr(player.find(',') + 1, player.size());
        ranking_score.push_back(make_pair(name, stoi(score)));
    }

    merge_sort(ranking_score);

    ofstream file2("ranking_final.txt");
    if(!file2.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    for (size_t i = 0; i < ranking_score.size(); i++) {
        file2 << ranking_score[i].first << ',' << ranking_score[i].second << endl;
    }
    file2.close();
}