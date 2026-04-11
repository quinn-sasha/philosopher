Concurrent Resource Management Simulator

## Overview

This project is a simulation demonstrating **concurrent programming**, **thread synchronization**, and **resource allocation**. It explores how to manage shared resources among multiple threads without causing deadlocks or data races, based on the classic "Dining Philosophers" problem.

## Rules and Requirements

- **Actors**: The simulation involves one or more actors (threads).
- **Actions**: Each actor repeatedly performs three exclusive actions: eating, sleeping, and thinking.
- **Routine**: After an actor finishes eating, they go to sleep. When they wake up, they start thinking.
- **Resources (Forks)**: There are exactly as many forks as actors. To eat, an actor must successfully grab both their left and right forks.
- **Starvation**: If an actor cannot eat within a specific timeframe, they will starve.
    - _Note: If there is only one actor, there is only one fork available, meaning they cannot eat and will inevitably die._
- **Constraints**:
    - Actors must not communicate with each other.
    - No actor should starve to death.
    - Multiple threads cannot access the same memory area simultaneously; therefore, each fork is protected using a **mutex**.
	
## How to Run

### 1. Build

Use the provided `Makefile` to compile the project.

```bash
make
```

### 2. Usage

Run the compiled executable with the following arguments:

```bash
./philo <number_of_actors> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_actor_must_eat]
```

#### Argument Details

- `number_of_actors`: The number of actors (and total number of forks).
- `time_to_die` (ms): Time limit for an actor to start their next meal before starving.
- `time_to_eat` (ms): Time required to finish eating (requires holding two forks).
- `time_to_sleep` (ms): Time spent sleeping after a meal.
- `number_of_times_each_actor_must_eat` (Optional): If all actors eat at least this many times, the simulation ends.

### 3. Logs

The program outputs state changes in real-time:

```plaintext
[timestamp_ms] [ID] has taken a fork
[timestamp_ms] [ID] is eating
[timestamp_ms] [ID] is sleeping
[timestamp_ms] [ID] is thinking
[timestamp_ms] [ID] died
```

_Note: Messages from different threads will not overlap, and death logs are displayed within 10ms of the event._
