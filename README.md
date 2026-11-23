# Pillow

> **Work in Progress (WIP):** Pillow is currently in active development. Expression evaluation, heap-allocated strings, and core virtual machine execution are implemented, while statements, variables, control flow, and functions are still under construction.

**Pillow** is a lightweight, stack-based bytecode interpreter and virtual machine written in C, inspired by Robert Nystrom's *Crafting Interpreters* (`clox`). It compiles source code in a single pass into custom bytecode instructions and executes them on a stack-based VM.

---

## Current Features

* **Execution Modes:** Supports an interactive Read-Eval-Print Loop (REPL) for evaluating expressions on the fly, as well as executing source files from disk.
* **Single-Pass Pratt Compiler:** Tokenizes and compiles source expressions directly into bytecode chunks with operator precedence and line-number tracking for error reporting.
* **Stack-Based Virtual Machine:** Executes bytecode instructions using a fixed 256-slot value stack (`STACK_MAX = 256`) with runtime type checking and error reporting.
* **Dynamic Types and Heap Objects:**
  * **Primitives:** Double-precision floating-point numbers (`VAL_NUMBER`), booleans (`VAL_BOOL`), and `null` (`VAL_NULL`).
  * **Heap Objects:** Managed via an intrusive linked list (`vm.objects`), currently supporting dynamic strings (`OBJ_STRING`) and string concatenation (`+`).
* **Operators and Expressions:**
  * **Arithmetic:** `+`, `-`, `*`, `/`, and floating-point remainder `%` (via `fmod`).
  * **Unary:** `-` (numeric negation) and `!` (logical NOT, treating `false` and `null` as falsey).
  * **Comparison and Equality:** `==`, `!=`, `<`, `<=`, `>`, `>=`.
* **Built-in Disassembler and Tracer:** Includes compile-time debug flags (`DEBUG_PRINT_CODE` and `DEBUG_TRACE_EXECUTION`) to disassemble bytecode chunks and trace VM stack operations during execution.

---

## Building and Running

### Prerequisites

* A C compiler supporting C99 or later (such as `gcc` or `clang`)
* The standard C math library (`-lm` on Linux/Unix systems for `fmod`)

### Compiling from Source

```bash
gcc -Wall -Wextra -O2 *.c -o pillow -lm
```

### Interactive REPL

Run the compiled binary without arguments to start the interactive REPL:

```bash
./pillow
```

Example session:

```text
> (10 + 5) % 4 == 3
true
> "hello " + "pillow"
hello pillow
> !(5 > 10)
true
```

### Running a Script File

Pass a source file path as an argument:

```bash
./pillow path/to/script.plw
```

---

## Project Architecture

| Module | Description |
| :--- | :--- |
| `main.c` | Entry point handling CLI arguments, file I/O, and the interactive REPL loop. |
| `scanner.h` / `scanner.c` | Lexer tokenizing source text into literals, operators, comments, and keywords. |
| `compiler.h` / `compiler.c` | Single-pass Pratt parser compiling token streams into bytecode chunks. |
| `chunk.h` / `chunk.c` | Dynamic bytecode arrays, `OpCode` definitions, line tracking, and constant pools. |
| `vm.h` / `vm.c` | Virtual machine execution loop, value stack management, and runtime error handling. |
| `value.h` / `value.c` | Tagged union representation for runtime values and dynamic `ValueArray` storage. |
| `object.h` / `object.c` | Heap-allocated object definitions and string allocation/printing utilities. |
| `memory.h` / `memory.c` | Dynamic memory reallocation wrappers and VM exit object cleanup. |
| `debug.h` / `debug.c` | Bytecode chunk and instruction disassembler for debugging. |
| `common.h` | Shared standard headers and debug toggle macros. |

---

## Debugging

To toggle bytecode disassembly before execution or stack tracing during VM execution, define or comment out the following macros in `common.h` before compiling:

```c
#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION
```

---

## Roadmap

Tokens for the remaining language constructs are already defined in the scanner (`val`, `func`, `ret`, `if`, `else`, `while`, `for`, `class`, `this`, `super`, `print`, `and`, `or`). Planned features include:

- [ ] `print` statements and multi-statement script execution
- [ ] Global and local variable declarations (`val`) and assignment
- [ ] Control flow (`if`/`else`, `while`, `for`) and short-circuiting logical operators (`and`, `or`)
- [ ] Functions (`func`), call frames, and return statements (`ret`)
- [ ] String interning and hash table implementation
- [ ] Mark-and-sweep garbage collection (replacing exit-time object cleanup)
- [ ] Object-oriented programming (`class`, instances, methods, `this`, and `super`)
