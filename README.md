# Mini Compiler Project: Expression Parsing & Three-Address Code Generation (C++)

## Overview
This repository contains a **Compiler Design course project** implemented in **C++**.

The project reads a simple assignment statement with arithmetic expressions, performs:
- **Lexical analysis** (tokenization using regular expressions),
- **Parsing** using a **recursive-descent parser** for a small expression grammar,
- **Semantic actions** to generate **Three-Address Code** in the form of **quadruples**.

This project focuses on core compiler front-end concepts and intermediate code generation.

---

## Supported Input
The input is read from `code.txt` and should be **space-separated**, ending with `$`.

Example (`code.txt`):
```
x := ( a + b ) * c
```

At runtime, the program appends `$` automatically.

---

## Grammar (High-Level)
The compiler supports:
- Assignment: `ID := E`
- Expressions:
  - Parentheses `( E )`
  - Addition `+`
  - Multiplication `*`
  - Identifiers `ID`

Operator precedence:
- `*` has higher precedence than `+`
- Parentheses override precedence

---

## Tokens
Tokens are recognized using regular expressions:
- Assignment operator `:=`
- Arithmetic operators `+`, `*`
- Parentheses `(`, `)`
- Identifiers: `[_a-zA-Z][_a-zA-Z0-9]*`
- End marker `$`

---

## Output: Three-Address Code
Intermediate code is generated as **quadruples** in the form:

```
(op, arg1, arg2, result)
```

Temporary variables are introduced automatically during expression evaluation.

---

## Project Structure
- `Source.cpp` – Program entry point
- `Lexic.h` – Token definitions and regex rules
- `Grammer.h` – Recursive-descent parser and code generation
- `code.txt` – Sample input

---

## How to Build & Run

### Requirements
- C++ compiler (GCC / MSVC / Clang)

### Build
```
g++ Source.cpp -o compiler
```

### Run
```
./compiler
```

The generated quadruples are printed to standard output.

---

## Notes & Limitations
- Input must be space-separated
- No numeric literals
- No control flow (if/while)
- No optimization phase
- Designed strictly for educational purposes

---

## Academic Context
This project was developed as part of a university-level **Compiler Design** course to demonstrate lexical analysis, parsing, and intermediate code generation.

---

## Author
Milad PourAhmad

---

## License
This project is shared for educational and academic portfolio purposes.
