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


def binary_search(data: List[Tuple[int, str]], target: int) -> bool:
    left, right = 0, len(data) - 1
    while left <= right:
        mid = (left + right) // 2
        if data[mid][0] == target:
            return True
        elif data[mid][0] < target:
            left = mid + 1
        else:
            right = mid - 1
    return False


def measure_search_time(data: List[Tuple[int, str]], target: int, repeats: int = 1) -> float:
    start = time.time()
    for _ in range(repeats):
        binary_search(data, target)
    end = time.time()
    return (end - start) / repeats


def main():
    if len(sys.argv) != 3:
        print("Usage: python binary_search.py <sorted_csv_path> <output_txt_name>")
        sys.exit(1)

    csv_path = sys.argv[1]
    output_txt = sys.argv[2]

    os.makedirs("output", exist_ok=True)

    print(f"Reading {csv_path}...")
    data = read_csv(csv_path)
    n = len(data)
    print(f"Loaded {n:,} records")

    # Targets
    best_target = data[n // 2][0]
    average_target = data[n // 3][0]
    worst_target = -1  # Not found

    # Measure
    best_time = measure_search_time(data, best_target)
    average_time = measure_search_time(data, average_target)
    worst_time = measure_search_time(data, worst_target)

    # Output
    out_path = os.path.join("output", output_txt)
    with open(out_path, "w", encoding="utf-8") as f:
        f.write(f"Best case: {best_time:.6f} seconds\n")
        f.write(f"Average case: {average_time:.6f} seconds\n")
        f.write(f"Worst case: {worst_time:.6f} seconds\n")

    print(f"✔ Binary search analysis written to {out_path}")


if __name__ == "__main__":
    main()

## python src/generator/searching/binary_search.py output/merge_sort_60000000.csv binary_search_60000000.txt
