import csv
import os
from typing import List, Tuple


# ===== Configuration =====
csv_path = "output/merge_sort_60000000.csv"  # Input CSV file path (must be sorted)
target_value = 2008864030                # Integer value to search
# ==========================


def read_csv(filepath: str) -> List[Tuple[int, str]]:
    """Read all rows from the CSV file and return a list of (int, string) tuples."""
    data = []
    with open(filepath, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            num = int(row[0])
            text = row[1]
            data.append((num, text))
    return data


def binary_search_trace(data: List[Tuple[int, str]], target: int) -> List[str]:
    """Perform binary search and return trace of comparisons with index and value."""
    trace = []
    left, right = 0, len(data) - 1

    while left <= right:
        mid = (left + right) // 2
        mid_val = data[mid][0]
        trace.append(f"{mid}: {mid_val}/{data[mid][1]}")

        if mid_val == target:
            return trace
        elif mid_val < target:
            left = mid + 1
        else:
            right = mid - 1

    trace.append("-1")  # target not found
    return trace


def main():
    os.makedirs("output", exist_ok=True)

    data = read_csv(csv_path)
    trace = binary_search_trace(data, target_value)

    out_filename = f"output/binary_search_step_{target_value}.txt"
    with open(out_filename, "w", encoding="utf-8") as f:
        for line in trace:
            f.write(line + "\n")

    if trace[-1] != "-1":
        print(f"✔ Target {target_value} FOUND. Output saved to: {out_filename}")
    else:
        print(f"✘ Target {target_value} NOT FOUND. Output saved to: {out_filename}")


if __name__ == "__main__":
    main()
