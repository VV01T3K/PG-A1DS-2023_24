1. Install Valgrind. On Ubuntu, you can do this with the following command:

```bash
sudo apt install valgrind
```

2. Build your project with debugging symbols. If you're using g++, you can do this by adding the -g flag:

```bash
g++ -g -o code Project/*.c
```

3. Run your program with Valgrind:

```bash
valgrind --leak-check=full ./code < input.txt
```