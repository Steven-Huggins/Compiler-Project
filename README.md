# Compiler Project

A small compiler front-end project written in C. The current implementation focuses on lexical analysis and symbol table construction. It reads a source file, scans it into tokens, prints the token stream, stores identifiers in a symbol table, and displays the final symbol table.

## Features

* Lexical analysis for a small custom language
* Token recognition for:

  * Keywords: `bool`, `nat`, `fun`
  * Identifiers
  * Natural number literals
  * Boolean literals: `T`, `F`
  * Operators: `+`, `&`, `<`, `=`, `?`, `:`, `;`, `,`, `->`
  * Brackets and parentheses
* Comment skipping for text enclosed in square brackets
* Lexical error reporting with line numbers
* Symbol table construction for identifiers
* Tree-based symbol table implementation
* Sample input file for testing valid tokens

## Project Structure

```text id="zjr6px"
.
├── func.c              # Main program entry point
├── lexer.c             # Lexer implementation
├── lexer.h             # Token types, lexer state definitions, and lexer API
├── symbol_table.c      # Symbol table implementation
├── symbol_table.h      # Symbol table data structure and function declarations
└── sample.txt          # Sample input used for testing the lexer
```

## How It Works

The program performs the following steps:

1. Opens the sample source file.
2. Initializes the lexer.
3. Reads tokens one by one.
4. Prints each lexeme and its token type.
5. Inserts identifier tokens into the symbol table.
6. Prints the final symbol table.
7. Frees the symbol table and closes the input file.

## Supported Token Types

| Lexeme Example                               | Token Type                  |
| -------------------------------------------- | --------------------------- |
| `bool`                                       | Boolean type keyword        |
| `nat`                                        | Natural number type keyword |
| `fun`                                        | Function keyword            |
| `id`, `lit`, `abc123`                        | Identifier                  |
| `123`, `0`                                   | Natural number literal      |
| `T`, `F`                                     | Boolean literal             |
| `+`, `&`, `<`, `=`, `?`, `:`, `;`, `,`, `->` | Operator                    |
| `(`, `)`, `[`, `]`                           | Bracket / delimiter         |
| Invalid characters                           | Lexical error               |

## Sample Input

The repository includes a sample file:

```text id="ydw4y9"
bool nat fun ( ? : ) ; [ ] id lit T F 123 0 + & < = ->
[This file tests all valid keywords, ids, lits, and operators.]
```

## Build Instructions

### Using GCC

```bash id="8j253l"
gcc -c lexer.c
gcc -c symbol_table.c
gcc func.c lexer.o symbol_table.o -o compiler
```

On Windows, the executable may be generated as:

```bash id="qs1sa2"
compiler.exe
```

On macOS or Linux, run:

```bash id="bst2wb"
./compiler
```

On Windows, run:

```bash id="ed63z6"
compiler.exe
```

## Important Setup Note

The current `func.c` file opens `sample.txt` using a hard-coded absolute Windows path. Before running the program on another computer, change the file path in `func.c` to a relative path:

```c id="8q4the"
FILE* source_file = fopen("sample.txt", "r");
```

After making this change, place `sample.txt` in the same directory as the executable or run the program from the project root.

## Expected Output

The program prints a table of lexemes and token types. A typical output format looks like this:

```text id="qgkeqx"
Lexme            Token
-----------------------
"bool"           Bool
"nat"            nat
"fun"            fun
"id"             identifier
"lit"            identifier
"123"            literal(natural)
"0"              literal(natural)
"+"              +
"&"              &
"<"              <
"="              =
"->"             ->

Symbol Table:
Name: id   , type: NULL
Name: lit  , type: NULL
```

The exact symbol table order may vary depending on insertion and tree traversal behavior.

## Main Components

### Lexer

The lexer reads characters from the source file and groups them into tokens. It uses lexer states and character classes to identify identifiers, keywords, numbers, operators, boolean literals, comments, and invalid tokens.

### Symbol Table

The symbol table stores identifier tokens. It is implemented as a tree structure with helper functions for insertion, lookup, deletion, cleanup, and printing.

### Main Program

The main program connects the lexer and symbol table. It scans the input file, prints tokens, stores identifiers, and prints the final table.

## Limitations

* The project currently focuses on lexical analysis and symbol table construction.
* There is no full parser or code generation stage yet.
* The input path is currently hard-coded and should be changed to a relative path.
* The program does not currently accept command-line input files.
* Some symbol table functions are incomplete or partially commented out.
* Error handling is basic and intended for course-project testing.

## Possible Improvements

* Add command-line file input, for example: `compiler sample.txt`
* Add a Makefile or CMake build file
* Complete symbol table deletion and lookup logic
* Add parser support
* Add AST construction
* Add semantic analysis
* Add better test cases for invalid input
* Add automated tests
* Improve memory management for token strings
* Add documentation for the custom language grammar

## License

No license file is currently included in this repository. Add a license before distributing or reusing this project.

## Author

Steven Huggins
