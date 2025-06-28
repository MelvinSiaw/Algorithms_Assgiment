import csv
import time
import os
import sys
from typing import List, Tuple

def read_csv(filepath: str) -> List[Tuple[int, str]]:
    data = []
    with open(filepath, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            num = int(row[0])
            text = row[1]
            data.append((num, text))
    return data

def merge_sort(arr: List[Tuple[int, str]]) -> List[Tuple[int, str]]:
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i][0] < right[j][0]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def write_csv(data: List[Tuple[int, str]], path: str) -> None:
    with open(path, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for row in data:
            writer.writerow(row)

def main():
    if len(sys.argv) != 3:
        print("Usage: python merge_sort.py <input_csv_path> <output_filename>")
        sys.exit(1)

    csv_path = sys.argv[1]
    output_name = sys.argv[2]

    os.makedirs("output", exist_ok=True)
    print(f"Reading data from {csv_path}...")
    data = read_csv(csv_path)

    print(f"Sorting {len(data):,} items using Merge Sort...")
    start_time = time.time()
    sorted_data = merge_sort(data)
    end_time = time.time()

    duration = end_time - start_time
    print(f"✔ Merge Sort completed in {duration:.2f} seconds.")

    output_path = f"output/{output_name}"
    write_csv(sorted_data, output_path)
    print(f"✔ Output written to {output_path}")

if __name__ == "__main__":
    main()
