# Exact Cover Solver

A C program that solves the **exact cover problem** using recursive backtracking (a variant of [Algorithm X](https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X)). Given a set of fixed-width rows where `_` marks an empty position, the solver finds all subsets of rows that together cover every column exactly once, then prints the results filtered by selected columns.

## How It Works

1. **Read filter** - the first line of input contains `+` and `-` characters, one per column. This determines the output width and which columns are displayed.
2. **Read data rows** - each subsequent line is a fixed-width row of the same length as the filter. Characters other than `_` are values; `_` marks an uncovered position.
3. **Recursive backtracking** - the algorithm:
   - Finds the first uncovered column (leftmost `_` in the result)
   - Tries each row that has a non-empty value in that column
   - Rejects rows that **collide** with already-selected values (two non-`_` characters in the same column)
   - If all columns are covered → a solution is found
   - Otherwise, **backtracks** and tries the next candidate row
4. **Filter & print** - for each complete cover, only columns marked `+` are printed.

> Columns marked `-` still participate in the covering logic - they are only omitted from the output.

## Build

```sh
gcc -std=c11 -Wall -Wextra -O2 main.c -o exact-cover-solver
```

Works with any C11-compatible compiler.

## Usage

```sh
./exact-cover-solver < input.txt
```

On Windows:

```powershell
.\exact-cover-solver.exe < input.txt
```

The program reads from **stdin** and writes all found covers to **stdout** (one per line). If no exact cover exists, nothing is printed.

## Input Format

```
<filter line>      ← '+' or '-' for each column
<data row 1>       ← same length as filter, '_' = empty
<data row 2>
...
```

- **Filter characters**: `+` (include column in output) or `-` (exclude from output)
- **Data row characters**: any character is a value, `_` means the position is empty
- All rows must have **exactly the same width** as the filter line

## Examples

### Basic - 3 columns, 3 rows

**Input:**
```text
+++
A__
_B_
__C
```

**Output:**
```text
ABC
```

All three rows are needed to cover every column. Since all columns have `+`, the entire cover is printed.

### With filter - hiding columns

**Input:**
```text
+-+
A__
_B_
__C
```

**Output:**
```text
AC
```

Column 2 (marked `-`) is still used to find the cover but is excluded from the output.

### Multiple solutions

**Input:**
```text
++
AB
BA
```

**Output:**
```text
AB
BA
```

Each row alone covers both columns, so there are two valid exact covers.

### No solution

**Input:**
```text
+++
A__
_B_
```

No output - two rows cannot cover three columns.

## Limits

| Constant | Value | Description |
|---|---|---|
| `MAX_WIER` | 200 | Maximum number of data rows |
| `MAX_KOL` | 300 | Maximum number of columns |

These are compile-time constants defined in `main.c`. Adjust them if larger inputs are needed.

## Algorithm

The solver implements a simplified variant of **Knuth's Algorithm X** without the Dancing Links optimization. The core function `pokrycia()` works as follows:

```
POKRYCIA(result, data_rows):
    pos ← first column where result[pos] == '_'
    if pos == num_columns:
        PRINT result (filtered)
        return
    for each row w in data_rows:
        if row w has a value at column pos:
            if row w does NOT collide with result:
                APPLY row w to result
                POKRYCIA(result, data_rows)     ← recurse
                UNDO row w from result          ← backtrack
```

## Project Structure

```
.
├── main.c        # Complete source code (188 lines)
└── README.md     # This file
```

## Author

**Anna Koziara**  
ak479522@students.mimuw.edu.pl
