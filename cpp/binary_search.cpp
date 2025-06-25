#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <random>
#include <filesystem>
#include <algorithm>  
using namespace std;
namespace fs = std::filesystem;

struct Record {
    int number;
    string text;
};

// Load sorted CSV file
vector<Record> loadData(const string& path) {
    vector<Record> data;
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << path << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string numStr, txt;
        if (getline(ss, numStr, ',') && getline(ss, txt)) {
            Record r{stoi(numStr), txt};
            data.push_back(r);
        }
    }

    file.close();
    return data;
}

// Standard binary search function
int binarySearch(const vector<Record>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].number == target) return mid;
        else if (arr[mid].number < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: binary_search <sorted_csv_path>" << endl;
        return 1;
    }

    string inputPath = argv[1];
    string fileName = fs::path(inputPath).stem().string();  // dataset_n (remove .csv)
    string outputFile = "cpp_output/binary_search_" + fileName + ".txt";
    fs::create_directory("cpp_output");

    // Load data
    vector<Record> records = loadData(inputPath);
    if (records.empty()) return 1;

    // Generate random search targets from dataset
    vector<int> targets;
    mt19937 rng(42); // fixed seed
    uniform_int_distribution<size_t> dist(0, records.size() - 1);
    for (size_t i = 0; i < records.size(); ++i) {
        targets.push_back(records[dist(rng)].number);
    }

    // Perform n binary searches and time them
    vector<double> durations;
    for (int target : targets) {
        auto start = chrono::high_resolution_clock::now();
        binarySearch(records, target);
        auto end = chrono::high_resolution_clock::now();
        durations.push_back(chrono::duration<double>(end - start).count());
    }

    // Calculate min, max, avg
    double best = *min_element(durations.begin(), durations.end());
    double worst = *max_element(durations.begin(), durations.end());
    double total = 0;
    for (double t : durations) total += t;
    double avg = total / durations.size();

    // Output result
    ofstream out(outputFile);
    out << "Best case: " << best << " seconds\n";
    out << "Average case: " << avg << " seconds\n";
    out << "Worst case: " << worst << " seconds\n";
    out.close();

    cout << "Binary Search completed over " << durations.size() << " targets\n";
    cout << "Output written to " << outputFile << endl;
    return 0;
}

// .\cpp\binary_search.exe cpp_output/merge_sort_dataset_60000000.csv
