import csv
import time
import os
from typing import List, Tuple


# ===== Configuration =====
csv_path = "output/merge_sort_60M.csv"  # Sorted CSV file
output_name = "binary_search_60M.txt"
# ==========================


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
    os.makedirs("output", exist_ok=True)

    print(f"Reading {csv_path}...")
    data = read_csv(csv_path)
    n = len(data)
    print(f"Loaded {n:,} records")

    # Targets
    best_target = data[n // 2][0]         # Best: middle
    average_target = data[n // 3][0]      # Average: not optimal, not terrible
    worst_target = -1                     # Worst: guaranteed not found

    # Measure times
    best_time = measure_search_time(data, best_target)
    average_time = measure_search_time(data, average_target)
    worst_time = measure_search_time(data, worst_target)

    # Output
    output_path = f"output/{output_name}"
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(f"Best case: {best_time:.6f} seconds\n")
        f.write(f"Average case: {average_time:.6f} seconds\n")
        f.write(f"Worst case: {worst_time:.6f} seconds\n")

    print(f"✔ Binary search analysis written to {output_path}")


if __name__ == "__main__":
    main()
