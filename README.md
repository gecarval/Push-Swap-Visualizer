<div align="center">

# Push Swap Visualizer

### Watch your push_swap sort, then rewind it and find the move that went wrong.

![Visualizer](https://github.com/user-attachments/assets/5251028c-11f7-44cc-acd4-01acafe129a6)

<p>
<img alt="C" src="https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=black" />
<img alt="MiniLibX" src="https://img.shields.io/badge/MiniLibX-X11-555" />
<img alt="License" src="https://img.shields.io/github/license/gecarval/Push-Swap-Visualizer?color=green" />
<img alt="Code size" src="https://img.shields.io/github/languages/code-size/gecarval/Push-Swap-Visualizer?color=lightblue" />
<img alt="Last commit" src="https://img.shields.io/github/last-commit/gecarval/Push-Swap-Visualizer?color=green" />
</p>

[Quick start](#quick-start) · [Controls](#controls) · [Examples](#example-algorithms) · [push_swap in 30 seconds](#push_swap-in-30-seconds)

</div>

---

A debugging tool for the 42 **push_swap** project. Give it the starting numbers and the list of operations your program printed, and it plays them back as two animated stacks: **A** on the left, **B** on the right, each number a bar coloured by its value. You can play, pause, **step one operation at a time, and go backwards**, while the window shows the operation count, the current operation and the next two.

## Quick start

You need a C compiler, `make`, and the X11 development headers (`libx11` and `libxext`; on Debian/Ubuntu, `libx11-dev libxext-dev`). MiniLibX and libft are bundled.

```bash
git clone https://github.com/gecarval/Push-Swap-Visualizer.git
cd Push-Swap-Visualizer
make
```

Clone it inside your push_swap project folder, so that `../push_swap` is your program. Then shuffle some numbers, run your program on them, and open the result:

```bash
ARG=$(seq -50 50 | shuf | tr '\n' ' ')
echo "$ARG" > input.txt
../push_swap "$ARG" > result.txt
./push_swap_visualizer "$ARG"
```

### Ways to run it

| Command | Reads |
|---|---|
| `./push_swap_visualizer "3 1 2"` | numbers from one string, operations from `./result.txt` |
| `./push_swap_visualizer 3 1 2` | numbers as separate arguments, operations from `./result.txt` |
| `./push_swap_visualizer "$(cat input.txt)" path/to/ops.txt` | numbers from a string, operations from the given file |

The operations file has one operation per line, exactly as push_swap prints them. Duplicate numbers are rejected.

## Controls

| Key | Action | Key | Action |
|---|---|---|---|
| `Space` | play / pause | `[` / `]` | slower / faster |
| `N` | play forward | `V` | play **backward** |
| `D` | one step forward | `A` | one step **back** |
| `1` | clear the screen | `Esc` | quit |

The fastest way to find a bug: play until the stacks look wrong, pause, then press `A` until you reach the operation that broke them. The panel in the middle shows which one it is.

## Example algorithms

The `algos/` folder has two real runs you can open right away.

### Quick Selection Sort: 100 numbers, 727 operations

![Quick Selection Sort](https://github.com/user-attachments/assets/5119e3c5-1b33-407b-816f-a20001373f99)

Quicksort combined with selection sort, written with [gkomba](https://github.com/gkomba). It needs around 750 operations for 100 numbers, about 850 in the worst case. It uses every kind of operation: `pa`/`pb` 153 each, `ra` 151, `rb` 109, `rra` 64, `rrb` 57, `sa`/`sb` 20 each.

```bash
./push_swap_visualizer "$(cat algos/input_quickselection.txt)" algos/result_quickselection.txt
```

### Merge Sort: 500 numbers, 6 265 operations

![Merge Sort](https://github.com/user-attachments/assets/18fc3b5c-c76e-4515-bc02-8ba9f0cdc52e)

A merge sort on two stacks, possibly the first one written at any 42 campus. It pays off above about 150 numbers, and it always needs the same number of operations for a given count, whatever the starting order. It only pushes and rotates: `pa`/`pb` 1 132 each, `ra` 2 214, `rb` 1 787.

```bash
./push_swap_visualizer "$(cat algos/input_merge.txt)" algos/result_merge.txt
```

## push_swap in 30 seconds

You get a stack **A** of distinct integers and an empty stack **B**. Sort A in ascending order (smallest on top) with as few of these operations as possible:

| Operation | Effect |
|---|---|
| `sa` / `sb` / `ss` | swap the top two of A / of B / of both |
| `pa` / `pb` | move the top of B onto A / the top of A onto B |
| `ra` / `rb` / `rr` | rotate A / B / both up: the top goes to the bottom |
| `rra` / `rrb` / `rrr` | rotate A / B / both down: the bottom goes to the top |

At the end A must be sorted and B empty. The fewer operations, the better the grade.

## Inside

```
main.c, calls.c, reads.c   window, buttons, argument parsing
push_swap.c                stacks, the 11 operations (forward and reverse), colours
visualizer.c               drawing the two stacks
tools.c                    input, animation loop, info panel
bresenham/                 line drawing
algos/                     example inputs and operation lists
```

Going backwards works because every operation has an inverse (`sa` undoes itself, `pa` undoes `pb`, `ra` undoes `rra`, and so on), so the visualizer never has to store old states.

---

<div align="center">

Released under the [BSD 2-Clause License](./LICENSE) · Made by [Gerson Carvalho](https://github.com/gecarval) at 42

</div>
