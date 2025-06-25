import csv
import os
from typing import List, Tuple


# ===== Configuration =====
csv_path = "data/dataset_60000000.csv"  # Input CSV file path
start_row = 0                  # Start row index (inclusive)
end_row = 6                    # End row index (inclusive)
# ==========================


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


def quick_sort_trace(arr: List[Tuple[int, str]], low: int, high: int, trace: List[str]) -> None:
    """Quick Sort with step tracing using the last element as pivot."""
    if low < high:
        pi = partition(arr, low, high, trace)
        trace.append(f"pi={pi} " + format_row(arr))
        quick_sort_trace(arr, low, pi - 1, trace)
        quick_sort_trace(arr, pi + 1, high, trace)


def partition(arr: List[Tuple[int, str]], low: int, high: int, trace: List[str]) -> int:
    pivot = arr[high][0]
    i = low - 1
    for j in range(low, high):
        if arr[j][0] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def format_row(row: List[Tuple[int, str]]) -> str:
    return "[" + ", ".join(f"{x}/{s}" for x, s in row) + "]"


def main():
    os.makedirs("output", exist_ok=True)

    data = read_csv_subset(csv_path, start_row, end_row)
    trace = []
    trace.append(format_row(data))  # initial array before sorting

    quick_sort_trace(data, 0, len(data) - 1, trace)

    out_filename = f"output/quick_sort_step_{start_row}_{end_row}.txt"
    with open(out_filename, "w", encoding="utf-8") as f:
        for line in trace:
            f.write(line + "\n")

    print(f"✔ Quick sort completed! Output saved to: {out_filename}")


if __name__ == "__main__":
    main()
