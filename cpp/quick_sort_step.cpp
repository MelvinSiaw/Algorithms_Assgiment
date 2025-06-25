// =======================================
// File: quick_sort_step.cpp
// Desc: Read CSV rows, perform Quick Sort, and write sorting steps
// =======================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

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

void writeStep(ofstream& out, const vector<Record>& data) {
    for (const auto& r : data) {
        out << r.number << "," << r.text << " ";
    }
    out << "\n";
}

int partition(vector<Record>& arr, int low, int high, ofstream& out) {
    int pivot = arr[high].number;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].number < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    writeStep(out, vector<Record>(arr.begin() + low, arr.begin() + high + 1));
    return i + 1;
}

void quickSort(vector<Record>& arr, int low, int high, ofstream& out) {
    if (low < high) {
        int pi = partition(arr, low, high, out);
        quickSort(arr, low, pi - 1, out);
        quickSort(arr, pi + 1, high, out);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: quick_sort_step <csv_file> <start_row> <end_row>\n";
        return 1;
    }

    string csvPath = argv[1];
    int startRow = stoi(argv[2]);
    int endRow = stoi(argv[3]);

    ifstream infile(csvPath);
    if (!infile.is_open()) {
        cerr << "Failed to open file: " << csvPath << endl;
        return 1;
    }

    vector<Record> records;
    string line;
    int index = 0;
    while (getline(infile, line)) {
        if (index >= startRow && index <= endRow) {
            records.push_back(parseCSVLine(line));
        }
        ++index;
        if (index > endRow) break;
    }
    infile.close();

    filesystem::path outputDir = filesystem::absolute("cpp_output");
    filesystem::create_directory(outputDir);
    string outFile = "quick_sort_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";
    ofstream outfile(outputDir / outFile);

    quickSort(records, 0, records.size() - 1, outfile);
    outfile.close();

    cout << " Output written to " << (outputDir / outFile).string() << endl;
    return 0;
}

// .\cpp\quick_sort_step.exe data\dataset_60000000.csv 0 6
