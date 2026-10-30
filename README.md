# HW5: Dijkstra's Algorithm

Finds the cost of the shortest path between two nodes in a directed, weighted graph, using a hand-written `Graph` and a `BetterPriorityQueue` that extends `std::priority_queue` with `Contains()` and `Update()`.

## Compile

```
make
```

This builds three programs. `make clean` removes them.

| Program | Sources | What it tests |
|---|---|---|
| `graph-tests` | `Graph.cpp`, `GraphTests.cpp` | Graph |
| `bpq-tests` | `Graph.cpp`, `BetterPriorityQueue.cpp`, `BPQTests.cpp` | Priority queue |
| `dijkstra` | `Graph.cpp`, `BetterPriorityQueue.cpp`, `Dijkstra.cpp`, `DijkstraTests.cpp` | Dijkstra's algorithm |

## Run

```
./graph-tests
./bpq-tests
./dijkstra
```

Each program prints `ALL TESTS PASSED` when it finishes, and stops on a failed assert otherwise.

To check for memory leaks:

```
valgrind --leak-check=full ./graph-tests
```

## Behavior notes

- `dijkstra()` returns `INT_MAX` when there is no path from `start` to `end`, because an unreachable node's distance stays infinite.
- `Update()` only lowers a priority. A larger or equal priority is ignored and it returns `false`, because Dijkstra only ever lowers a distance.

## Sources

- Tests, `Graph.h` public interface, and `BPQNode` provided by the professor.
- Used Claude (Anthropic) to explain concepts, review code, generate method stubs, and write this README, the additional tests, the copy constructor, the unreachable-node check, and the Big-O comment. File headers list the specifics.
