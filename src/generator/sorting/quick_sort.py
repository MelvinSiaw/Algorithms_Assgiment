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

def quick_sort(arr: List[Tuple[int, str]], low: int, high: int) -> None:
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)

def partition(arr: List[Tuple[int, str]], low: int, high: int) -> int:
    pivot = arr[high][0]
    i = low - 1
    for j in range(low, high):
        if arr[j][0] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def write_csv(data: List[Tuple[int, str]], path: str) -> None:
    with open(path, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for row in data:
            writer.writerow(row)

def main():
    if len(sys.argv) != 3:
        print("Usage: python quick_sort.py <input_csv_path> <output_filename>")
        sys.exit(1)

    csv_path = sys.argv[1]
    output_name = sys.argv[2]

    os.makedirs("output", exist_ok=True)
    print(f"Reading data from {csv_path}...")
    data = read_csv(csv_path)

    print(f"Sorting {len(data):,} items using Quick Sort...")
    start_time = time.time()
    quick_sort(data, 0, len(data) - 1)
    end_time = time.time()

    duration = end_time - start_time
    print(f"✔ Quick Sort completed in {duration:.2f} seconds.")

    output_path = f"output/{output_name}"
    write_csv(data, output_path)
    print(f"✔ Output written to {output_path}")

if __name__ == "__main__":
    main()
