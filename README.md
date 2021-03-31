# sudoku-cli
A CLI tool for solving sudoku puzzle with a lighting fast speed.
Using optimized backtracking: reduce the decision space for each cell before backtracking, even solved the puzzle already without even backtracking.

#### Build:
Run `make` in terminal.

#### Run:
Run `./main` in terminal.

#### Example Run:
```
1
.5.......
9.41.....
....5...6
..1.27.6.
.43.....2
.9651....
.69....74
...3....9
3.....25.

.5.|...|...
9.4|1..|...
...|.5.|..6
___ ___ ___
..1|.27|.6.
.43|...|..2
.96|51.|...
___ ___ ___
.69|...|.74
...|3..|..9
3..|...|25.

652|734|198
934|168|725
817|952|436
___ ___ ___
581|427|963
743|896|512
296|513|847
___ ___ ___
169|285|374
425|371|689
378|649|251

Pre-solve count: 10
Recursive count: 0
Execution time: 0.000000
```

```
1
.......1.
4........
.2.......
....5.4.7
..8...3..
..1.9....
3..4..2..
.5.1.....
...8.6...

...|...|.1.
4..|...|...
.2.|...|...
___ ___ ___
...|.5.|4.7
..8|...|3..
..1|.9.|...
___ ___ ___
3..|4..|2..
.5.|1..|...
...|8.6|...

693|784|512
487|512|936
125|963|874
___ ___ ___
932|651|487
568|247|391
741|398|625
___ ___ ___
319|475|268
856|129|743
274|836|159

Pre-solve count: 2
Recursive count: 25333461
Execution time: 0.903000
```
