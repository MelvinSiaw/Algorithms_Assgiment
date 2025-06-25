// ==========================================
// File: merge_sort.cpp
// Desc: Perform Merge Sort and record execution time
// Output: cpp_output/merge_sort_<n>.csv
// ==========================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
using namespace std;
using namespace std::chrono;

struct Record {
    int number;
    string text;
};

Record parseCSVLine(const string& line) {
    stringstream ss(line);
    string numStr, text;
    getline(ss, numStr, ',');
    getline(ss, text);
    return { stoi(numStr), text };
}

void merge(vector<Record>& arr, int left, int mid, int right) {
    vector<Record> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<Record> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while (i < L.size() && j < R.size()) {
        if (L[i].number <= R[j].number) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<Record>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: merge_sort <input_csv>\n";
        return 1;
    }

    string csvPath = argv[1];
    ifstream infile(csvPath);
    if (!infile.is_open()) {
        cerr << "Failed to open file: " << csvPath << endl;
        return 1;
    }

    vector<Record> records;
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            records.push_back(parseCSVLine(line));
        }
    }
    infile.close();

    auto start = high_resolution_clock::now();
    mergeSort(records, 0, records.size() - 1);
    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;
    cout << "Merge Sort completed in " << duration.count() << " seconds.\n";

    string filename = filesystem::path(csvPath).filename().string();
    string outFile = "merge_sort_" + filename;
    filesystem::create_directory("cpp_output");
    ofstream outfile("cpp_output/" + outFile);
    for (const auto& r : records) {
        outfile << r.number << "," << r.text << "\n";
    }
    outfile.close();

    cout << "Output written to cpp_output/" << outFile << endl;
    return 0;
}

// .\cpp\merge_sort.exe data/dataset_60000000.csv
