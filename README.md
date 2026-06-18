# CPU Scheduling and Cache Simulation

This project simulates CPU task scheduling together with a three-level cache memory system. It compares First-Come, First-Served (FCFS) and Round Robin scheduling with two cache replacement approaches.

## Project Files

| File | Description |
| --- | --- |
| `FCFS.cpp` | FCFS scheduler with standard FIFO-style cache eviction. |
| `FCFS_LRU.cpp` | FCFS scheduler with an LRU-inspired cache replacement policy. |
| `RoundRobin.cpp` | Round Robin scheduler with standard FIFO-style cache eviction. |
| `RoundRobin_LRU.cpp` | Round Robin scheduler with an LRU-inspired cache replacement policy. |
| `input_task2.txt` | Sample input file containing tasks, burst times, and memory requests. |
| `results/` | Output screenshots/results for the different simulations. |

## What the Simulator Does

Each program:

1. Reads tasks from `input_task2.txt`.
2. Schedules tasks using either FCFS or Round Robin.
3. Processes memory requests through L1, L2, L3, and RAM.
4. Prints cache hits, misses, cache contents, cycle count, completed tasks, scheduler type, and RAM access count.

## Cache Model

The memory system uses three cache levels:

| Level | Capacity | Access Cost |
| --- | ---: | ---: |
| L1 | 32 blocks | 4 cycles |
| L2 | 128 blocks | 12 cycles |
| L3 | 512 blocks | 40 cycles |
| RAM | Unlimited | 200 cycles |

If a block is not found in L1, L2, or L3, it is fetched from RAM and inserted into the cache hierarchy.

## Scheduling Algorithms

### FCFS

The First-Come, First-Served scheduler runs each task completely before moving to the next task.

Implemented in:

- `FCFS.cpp`
- `FCFS_LRU.cpp`

### Round Robin

The Round Robin scheduler runs tasks with a time quantum of `3`. If a task still has remaining burst time after its quantum, it is placed back into the queue.

Implemented in:

- `RoundRobin.cpp`
- `RoundRobin_LRU.cpp`

## Input Format

Each line in `input_task2.txt` follows this format:

```text
TASK <task_id> BURST <burst_time> MEM <memory_block_1> <memory_block_2> ...
```

Example:

```text
TASK T1 BURST 5 MEM M1 M4 M7
TASK T2 BURST 3 MEM M2 M1
```

## How to Compile

Use a C++ compiler such as `g++`.

```bash
g++ FCFS.cpp -o FCFS
g++ FCFS_LRU.cpp -o FCFS_LRU
g++ RoundRobin.cpp -o RoundRobin
g++ RoundRobin_LRU.cpp -o RoundRobin_LRU
```

On Windows PowerShell, the same commands work if `g++` is installed and available in your PATH.

## How to Run

Run the executable from the project root so it can find `input_task2.txt`.

```bash
./FCFS
./FCFS_LRU
./RoundRobin
./RoundRobin_LRU
```

On Windows PowerShell:

```powershell
.\FCFS.exe
.\FCFS_LRU.exe
.\RoundRobin.exe
.\RoundRobin_LRU.exe
```

## Output

The output includes:

- Current simulation cycle
- Running task ID
- Requested memory block
- Cache hit or miss information
- L1, L2, and L3 cache contents
- Total cycles
- Number of completed tasks
- Scheduler used
- Total RAM accesses

Example final result section:

```text
=== Final Results ===
Total Cycles: 1234
Tasks Completed: 15
Scheduler: Round Robin (quantum = 3)
RAM Accesses: 10
```

## Notes

- All programs currently read from `input_task2.txt`.
- The Round Robin quantum is fixed at `3`.
- Cache capacities and access cycle costs are hardcoded in the source files.
- The LRU versions use a small recent-use tracking list to choose cache eviction candidates.
