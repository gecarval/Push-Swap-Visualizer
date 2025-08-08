# Push Swap
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/gecarval/Falling-Sand?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/gecarval/Falling-Sand?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/gecarval/Falling-Sand?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/gecarval/Falling-Sand?color=green" />
</p>
Push Swap is a 42 school project that gives you the challenge of creating a sorting algorithm for a stack with a specific set of defined operations or instructions. The objective is to create this algorithm where it organizes the stack in the crescent order (top to bottom) with the least amount of instructions, you have two stacks, A and B, where you use the B stack as an auxiliary stack to order the numbers received on the stack A, in the end you will have the ordered numbers inside the stack A with an empty B.

where the instructions are:
- `sa` : swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).
- `sb` : swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).
- `ss` : `sa` and `sb` at the same time.
- `pa` : push a - take the first element at the top of b and put it at the top of a. Do
nothing if b is empty.
- `pb` : push b - take the first element at the top of a and put it at the top of b. Do
nothing if a is empty.
- `ra` : rotate a - shift up all elements of stack a by 1. The first element becomes
the last one.
- `rb` : rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
- `rr` : `ra` and `rb` at the same time.
- `rra` : reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
- `rrb` : reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
- `rrr` : `rra` and `rrb` at the same time.

# Push Swap Visualizer
This is a project written in C using the MiniLibX as the API which shows the behavior of the operations of your 42 Push Swap project.
In the making of the push swap project this tool helps in detecting where does the program bug or even what the finishing result delivers, for example:

![Standard Screen](https://github.com/user-attachments/assets/5251028c-11f7-44cc-acd4-01acafe129a6)

> [!Note]
> On the left we have the Stack A and on the right we will have stack B.

> [!Tip]
> On the repo I have a Two inputs and result from the algorithm that I will explain, if you want to see their execution.

## Quick Selection Sort
![[Quick Selection Sort]](https://github.com/user-attachments/assets/5119e3c5-1b33-407b-816f-a20001373f99)

> [!Note]
> This is the quick sort algorithm joined with selection sort, this is a case were the algorithm is ordering 100 numbers, created with [gkomba](https://github.com/gkomba), we call it **Quick Selection Sort**, it has around 750 operations for 100 numbers and about 850 for the worst case.
``` sh
./push_swap_visualizer "$(cat ./algos/input_quickselection.txt)" "./algos/result_quickselection.txt"
```

## Merge Sort
![Merge Sort](https://github.com/user-attachments/assets/18fc3b5c-c76e-4515-bc02-8ba9f0cdc52e)

> [!Note]
> This is the merge sort algorithm, until now I saw that this was the first implementation of it in all 42 campuses, it is more efficient above 150 numbers, and the current process is doing it with 151, but with 100 numbers it does around 900 operations.

> [!Tip]
> The great thing about this algorithm is that it delivers the same amount of operations for the same amount of numbers, independent of the initial randomness of stack A.
``` sh
./push_swap_visualizer "$(cat ./algos/input_merge.txt)" "./algos/result_merge.txt"
```

# Installation
The project uses the [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) which uses the X11 Window system in the Linux System, after the instalation of all dependencies you should do as required:
``` sh
git clone https://github.com/gecarval/Push-Swap-Visualizer
```
``` sh
cd Push-Swap-Visualizer
```
``` sh
make
```
Execute the Push Swap Visualizer in his directory after doing make on your project:

First create a sequence of number in a file:
``` sh
ARG=($(seq -50 50 | shuf)) && echo "${ARG[*]}" > input.txt
```

Then we read the file with the number sequence and make your push_swap process the number sequence:
```sh
../push_swap "$(cat input.txt)" > ./result.txt
```

Then we read the file with the number sequence and the visualizer reads the **result.txt** file by default:
``` sh
./push_swap_visualizer "$(cat input.txt)"
```

The most used command for this program is one that does all the above:
``` sh
ARG=($(seq -50 50 | shuf)) && echo "${ARG[*]}" > input.txt && ../push_swap "$(cat input.txt)" > ./result.txt && ./push_swap_visualizer "$(cat input.txt)"
```

Other use cases are reading the input then a result file that you manually do the operations:
```sh
./push_swap_visualizer "$(cat path_to_input)" "path_to_result"
```
Or the default case which the visualizer reads a file with the name **result.txt**:
```sh
./push_swap_visualizer 1 4 3 2 5
```
