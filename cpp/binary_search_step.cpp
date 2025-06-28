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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: binary_search_step <sorted_csv_file> <target_number>\n";
        return 1;
    }

    string csvPath = argv[1];
    int target = stoi(argv[2]);

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

    filesystem::path outputDir = filesystem::absolute("cpp_output");
    filesystem::create_directory(outputDir);
    string outFile = "binary_search_step_" + to_string(target) + ".txt";
    ofstream outfile(outputDir / outFile);

    int left = 0, right = records.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        outfile << "Compare: " << records[mid].number << " (row " << mid << ")\n";

        if (records[mid].number == target) {
            outfile << "Found at row " << mid << ": " << records[mid].number << "," << records[mid].text << endl;
            break;
        } else if (records[mid].number < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (left > right) {
        outfile << "Not found in dataset.\n";
    }

    outfile.close();
    cout << "Search path written to " << (outputDir / outFile).string() << endl;
    return 0;
}

// .\cpp\binary_search_step.exe cpp_output/merge_sort_dataset_60000000.csv 166975706