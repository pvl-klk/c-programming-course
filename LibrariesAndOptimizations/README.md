# Instructions for building

### Step-by-step building
`gcc -c bubble_sort.s -o bubble_sort.o`
`gcc -c main.c -o main.o`
`gcc main.o bubble_sort.o -o program`
`program`

### Build with a single command
`gcc main.c bubble_sort.s -o program && program`
