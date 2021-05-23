'''
sudoku = [
    4, 7, 3, 0, 0, 0, 0, 1, 0,
    5, 6, 9, 0, 0, 0, 7, 0, 0,
    0, 1, 0, 0, 7, 0, 6, 0, 0,
    8, 0, 0, 4, 0, 5, 0, 0, 0,
    1, 2, 0, 0, 0, 0, 0, 4, 8,
    0, 0, 0, 8, 0, 1, 0, 0, 9,
    0, 0, 7, 0, 6, 0, 0, 5, 0,
    0, 0, 2, 0, 0, 0, 4, 3, 6,
    0, 8, 0, 0, 0, 0, 9, 2, 7,
]

sudoku = [
    0, 0, 0, 0, 0, 0, 5, 6, 9,
    0, 0, 0, 6, 1, 2, 0, 0, 0,
    8, 3, 6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 5, 0, 0, 7, 0,
    0, 5, 9, 0, 0, 0, 1, 3, 0,
    0, 2, 0, 0, 3, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 4, 6,
    0, 0, 0, 8, 2, 7, 0, 0, 0,
    2, 1, 3, 0, 0, 0, 0, 0, 0,
]
'''

sudoku = [
    0, 0, 0, 0, 0, 0, 7, 8, 2,
    0, 0, 0, 5, 2, 9, 0, 0, 0,
    3, 6, 2, 0, 0, 0, 0, 0, 0,
    8, 0, 9, 0, 5, 0, 0, 0, 0,
    0, 3, 0, 0, 4, 0, 0, 5, 0,
    0, 0, 0, 0, 7, 0, 2, 0, 1,
    0, 0, 0, 0, 0, 0, 9, 4, 3,
    0, 0, 0, 1, 9, 6, 0, 0, 0,
    9, 2, 5, 0, 0, 0, 0, 0, 0,
]


def print_sudoku(sudoku):
    matrix = ""
    for l in range(9):
        line = ""
        for r in range(9):
            # wenn das Element nicht 0 ist, füge es an, sonst füge einen Punkt an
            line += str(sudoku[9 * l + r]).center(3) if sudoku[9 * l + r] else ".".center(3)
        matrix += line + ("\n" if l < 8 else "")
    print(matrix)


def get_line(sudoku, line):
    return sudoku[9 * line: 9 * line + 9]


def get_row(sudoku, row):
    return sudoku[row::9]


def get_field(sudoku, field):
    return [sudoku[(field // 3) * 3 * 9 + (field % 3) * 3 + (i // 3) * 9 + (i % 3)] for i in range(9)]



if __name__ == "__main__":
    print_sudoku(sudoku)
    print()

    while 0 in sudoku:
        found_an_element = False
        pattern = []

        for idx, element in enumerate(sudoku):
            if element:
                pattern.append([element])
            else:
                possibilities = []
                for i in range(1, 10):
                    if i in get_line(sudoku, idx // 9): continue
                    if i in get_row(sudoku, idx % 9): continue
                    if i in get_field(sudoku, (idx // (3*9)) * 3 + (idx % 9) // 3): continue
                    possibilities.append(i)
                
                if not possibilities:
                    print(f"ERROR :: no possibilities in line {idx // 9}, row {idx % 9}")
                    exit(-1)
                elif len(possibilities) == 1:
                    sudoku[idx] = possibilities[0]
                    found_an_element = True
                    print(f"({idx // 9 + 1}/{idx % 9 + 1}) : {possibilities[0]}")
                    break
                pattern.append(possibilities)
                
        if found_an_element: continue

        for idx, element in enumerate(pattern):
            if len(element) <= 1: continue

            final_element = 0
            for e in element:
                # Überprüfe, ob die mögliche Zahl e in der Zeile, in der Spalte und in dem Block mehrfach möglich ist
                if [j for i in get_line(pattern, idx // 9) for j in i].count(e) > 1 and [j for i in get_row(pattern, idx % 9) for j in i].count(e) > 1 and [j for i in get_field(pattern, (idx // (3*9)) * 3 + (idx % 9) // 3) for j in i].count(e) > 1: continue
                final_element = e
                break

            if final_element:
                sudoku[idx] = final_element
                found_an_element = True
                print(f"({idx // 9 + 1}/{idx % 9 + 1}) : {final_element}")
                break

        if not found_an_element:
            print("ERROR :: multible solutions possible")
            break

    print()
    print_sudoku(sudoku)