#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>
#include <string>
#include <filesystem>
#include <iomanip>

using namespace std;

string randomString(size_t length = 8) {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, chars.size() - 1);

    string result;
    for (size_t i = 0; i < length; ++i) {
        result += chars[dis(gen)];
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <row_count>\n";
        return 1;
    }

    int n = stoi(argv[1]);
    filesystem::create_directory("data");
    string out_path = "data/dataset_" + to_string(n) + ".csv";
    ofstream out(out_path);
    if (!out.is_open()) {
        cerr << "❌ Failed to open output file.\n";
        return 1;
    }

    unordered_set<uint32_t> used;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint32_t> dis(1, 1'000'000'000);

    for (int i = 0; i < n; ++i) {
        uint32_t number;
        do {
            number = dis(gen);
        } while (used.count(number));
        used.insert(number);

        out << number << "," << randomString(8) << "\n";
    }

    out.close();
    cout << "Dataset of " << n << " rows written to '" << out_path << "'\n";
    return 0;
}

// .\cpp\dataset_generator.exe 75000000

