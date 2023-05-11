# CLI for Mathematica and Symathica

![example workflow](https://github.com/vityaman-edu/math-tool/actions/workflows/trunk.yml/badge.svg)
![Total lines](https://img.shields.io/tokei/lines/github/vityaman-edu/math-tool)

## Mathematica

- A library for abstract scientific computations and
  contains computational methods implementation.

- Uses `C++20` concepts to abstract algorithms and data structures
  on algebraic types such as `Field`, `Real` numbers and so on.

- Basic data structures as `Matrix`, `Vector`, `Polynomial` implemented.

- Solve systems of linear equations using
  `Gauss` and `Simple Iteration` methods.

- Solve equations with only variable using
  `Half-Division`, `Newton`, `Simple Iteration` methods.

- Compute an integral of one-argument continuous function
  on given interval using `Cotes` methods.

- Approximate one-argument function with `Polynomial`
  using `Least Sqares` method.

- Find some statistics such as `PCC`, `RSS`.

## Symatica

- A library for symbolic computations.

- Supports basic operations such as
  `Addition`, `Substraction`, `Multiplication`, `Division`,
  `Negation`, `Exponentiation`.

- Leaf of `Expression` is either a `Variable` or `Literal`.

- Has a `DSL` to build `Expression` tree easily.

- Use `Evaluator` visitor to set values (or other expressions)
  to variables and compute concrete value of a given `Expression`.

- Use `Optimizer` visitor to optimize expression by applying
  transformations such as `a + 0 = a`, `a * 1 = a`, `2 + 2 = 4`,
  and many-many others.

- Use `Derivativer` visitor to find an `Expression` that is
  a precise dervivative of a given `Expression`. Then you
  can optimize it using `Optimizer` and compute using
  `Evaluator`.

- Goal 1: Add custom functions (`sin`, `cos`, `ln`) and its  
  derivatives to expand the application area.

- Goal 2: Integrate it with `Mathematica` and create an
  implementation of `Field` by `Expression` tree to
  be able to run abstract algorihms on symbolic expressions.

## Build & Run

Requirements:

- `cmake`
- `clang 16`
- `clang-tidy`
- `clang-format`
- `clangd`
- `vscode`

```bash
bash ci/project/build.sh
bash ci/project/test.sh
./build/math-tool --help
```

## Reference

- [ITMO University Lab reports](./doc/itmo)
