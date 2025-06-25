import random
import string
import sys

def random_row(str_len: int = 8) -> str:
    """Generate one CSV row: <uint32>,<random alphanumeric string>."""
    num = random.randint(0, 10**9 - 1)
    s = ''.join(random.choices(string.ascii_letters + string.digits, k=str_len))
    return f"{num},{s}\n"

def generate(n: int, out_path: str, str_len: int = 8, buf_size: int = 4_000_000) -> None:
    """
    Stream-write `n` rows of CSV to `out_path`, using a large buffer for speed.
    Each row is: uint32 in [0,1e9), followed by an alphanumeric string of length `str_len`.
    """
    with open(out_path, "w", buffering=buf_size) as f:
        for _ in range(n):
            f.write(random_row(str_len))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python generate.py <row_count> <output.csv>")
        sys.exit(1)

    try:
        row_count = int(sys.argv[1])
    except ValueError:
        print("Error: <row_count> must be an integer.")
        sys.exit(1)

    output_file = sys.argv[2]
    print(f"Generating {row_count:,} rows into '{output_file}'…")
    generate(row_count, output_file)
    print(f"✔ Done: {row_count:,} rows written to '{output_file}'.")
    
    # python src\generator/generate.py 100000000 data/dataset_100000000.csv 