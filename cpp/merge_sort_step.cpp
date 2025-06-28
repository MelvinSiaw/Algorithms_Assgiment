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

void merge(vector<Record>& arr, int left, int mid, int right, ofstream& out) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Record> L(n1);
    vector<Record> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].number <= R[j].number) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    writeStep(out, vector<Record>(arr.begin() + left, arr.begin() + right + 1));
}

void mergeSort(vector<Record>& arr, int left, int right, ofstream& out) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, out);
        mergeSort(arr, mid + 1, right, out);
        merge(arr, left, mid, right, out);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: merge_sort_step <csv_file> <start_row> <end_row>\n";
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
    string outFile = "merge_sort_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";
    ofstream outfile(outputDir / outFile);

    mergeSort(records, 0, records.size() - 1, outfile);
    outfile.close();

    cout << " Output written to " << (outputDir / outFile).string() << endl;
    return 0;
}

// .\cpp\merge_sort_step.exe data\dataset_60000000.csv 0 6
