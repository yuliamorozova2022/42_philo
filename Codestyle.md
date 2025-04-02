Since project is part of 42 core curriculum there are code style rules. Here are the most important of them.

- Each function must be at most 25 lines long, not counting the function’s own braces.

- Each line must be at most 80 columns wide, comments included. Warning: a tabulation doesn’t count as a single column, but as the number of spaces it represents.

- Declarations must be at the beginning of a function.

- All variable names must be indented on the same column in their scope. Note: types are already indented by the containing block.

- One single variable declaration per line.

- Declaration and initialization cannot be on the same line, except for global variables (when allowed), static variables, and constants.

- A function can take 4 named parameters at most.

- A function that doesn’t take arguments must be explicitly prototyped with the word `void` as the argument.

- Parameters in functions’ prototypes must be named.

- You can’t declare more than 5 variables per function.

- Return of a function has to be between parenthesis, unless the function returns nothing.

### 🚫 Forbidden:
  
- `for`
- `do...while`
- `switch`
- `case`
- `goto`
- Ternary operators such as `?`.
- VLAs - Variable Length Arrays.
- Implicit type in variable declarations.
