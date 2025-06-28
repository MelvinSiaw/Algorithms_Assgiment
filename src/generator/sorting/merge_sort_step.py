import csv
import os
import sys
from typing import List, Tuple

def read_csv_subset(filepath: str, start: int, end: int) -> List[Tuple[int, str]]:
    """Read a subset of rows from the CSV file and return a list of (int, string) tuples."""
    data = []
    with open(filepath, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for i, row in enumerate(reader):
            if i > end:
                break
            if i >= start:
                num = int(row[0])
                text = row[1]
                data.append((num, text))
    return data

def merge_sort_trace(arr: List[Tuple[int, str]], trace: List[List[Tuple[int, str]]]) -> List[Tuple[int, str]]:
    """Merge sort that records the steps of each merge into the trace list."""
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = merge_sort_trace(arr[:mid], trace)
    right = merge_sort_trace(arr[mid:], trace)

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
    trace.append(result.copy())
    return result

def format_row(row: List[Tuple[int, str]]) -> str:
    return "[" + ", ".join(f"{x}/{s}" for x, s in row) + "]"

def main():
    if len(sys.argv) != 4:
        print("Usage: python merge_sort_step.py <csv_path> <start_row> <end_row>")
        sys.exit(1)

    csv_path = sys.argv[1]
    start_row = int(sys.argv[2])
    end_row = int(sys.argv[3])

    os.makedirs("output", exist_ok=True)
    data = read_csv_subset(csv_path, start_row, end_row)
    trace = []
    merge_sort_trace(data, trace)

    out_filename = f"output/merge_sort_step_{start_row}_{end_row}.txt"
    with open(out_filename, "w", encoding="utf-8") as f:
        for step in trace:
            f.write(format_row(step) + "\n")

    print(f"✔ Merge sort completed! Output saved to: {out_filename}")

if __name__ == "__main__":
    main()
