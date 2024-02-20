# cpp-warships

some description to be done later (im lazy af)

## installation

### 1. via cmake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 2. via g++

```bash
g++ src/main.cpp src/gameplay.cpp src/connection.cpp -o warships
```

## running

### by default

```bash
./warships
```

### in quick mode


```bash
./warships --mode host --address 8080 --autoplace false
./warships --mode join --address 172.0.0.1:8080 --autoplace false

```