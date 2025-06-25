#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct Record {
    int number;
    string text;
};

void quickSort(vector<Record>& arr, int low, int high) {
    if (low < high) {
        Record pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j].number <= pivot.number) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

vector<Record> readCSV(const string& filePath) {
    vector<Record> records;
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return records;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string numStr, text;
        if (getline(ss, numStr, ',') && getline(ss, text)) {
            Record r;
            r.number = stoi(numStr);
            r.text = text;
            records.push_back(r);
        }
    }

    file.close();
    return records;
}

void writeCSV(const string& filePath, const vector<Record>& records) {
    ofstream out(filePath);
    for (const auto& r : records) {
        out << r.number << "," << r.text << "\n";
    }
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: quick_sort <input_csv>" << endl;
        return 1;
    }

    string inputPath = argv[1];
    string fileName = fs::path(inputPath).filename().string();
    string outputPath = "cpp_output/quick_sort_" + fileName;

    // Read
    vector<Record> records = readCSV(inputPath);
    if (records.empty()) return 1;

    // Sort
    auto start = chrono::high_resolution_clock::now();
    quickSort(records, 0, records.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Write
    fs::create_directory("cpp_output");
    writeCSV(outputPath, records);

    // Done
    cout << "Quick Sort completed in " << elapsed.count() << " seconds." << endl;
    cout << "Output written to " << outputPath << endl;
    return 0;
}


// .\cpp\quick_sort.exe data/dataset_60000000.csv
