A template for a C based project (using C++ mostly for template)

## Compilation commands :

- Place yourself at the parent folder of `src`
- Don't forget to create a `bin` directory in the same folder as `src`

- Fast Compilation :

```shell
g++ -O0 -g -DIS_IN_DEBUG=1 -DTRACK_MEMORY=1 ./src/betterCPP/*.c* ./src/betterCPP/core/*.c* ./src/betterCPP/low_level/*.c* ./src/betterCPP/simulation/*.c* ./src/betterCPP/mersenne_twister/*.c* ./src/betterCPP/math/*.c* ./src/betterCPP/text/*.c* ./src/*.c* -o ./bin/test.exe -Wall -Wextra -Wcomment -Wno-unknown-pragmas
```

- Optimized Compilation :

```shell
g++ -O3 ./src/betterCPP/*.c* ./src/betterCPP/core/*.c* ./src/betterCPP/low_level/*.c* ./src/betterCPP/math/*.c* ./src/betterCPP/text/*.c* ./src/betterCPP/simulation/*.c* ./src/betterCPP/mersenne_twister/*.c* ./src/*.c* -o ./bin/test.exe -Wall -Wextra -Wcomment -Wno-unknown-pragmas
```

Run :

```shell
./bin/test.exe
```