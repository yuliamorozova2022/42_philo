# 42_philo
Dining philosophers problem

## Overview  

- One or more philosophers sit at a round table with a large bowl of spaghetti in the middle.  
- Philosophers take turns **eating**, **thinking**, and **sleeping**:  
  - While eating, they are neither thinking nor sleeping.  
  - While thinking, they are neither eating nor sleeping.  
  - While sleeping, they are neither eating nor thinking.  
- The table has as many forks as there are philosophers.  
- Since eating spaghetti with just one fork is impractical, a philosopher must pick up both the fork to their right and the fork to their left before eating.  
- Once a philosopher finishes eating, they put their forks back on the table and start sleeping. After waking up, they resume thinking.  
- The simulation stops when a philosopher dies of starvation.  

## Rules  

- Every philosopher needs to eat and should never starve.  
- Philosophers do not communicate with each other.  
- Philosophers do not know if another philosopher is about to die.  
- Philosophers should avoid dying whenever possible.  

## Program Constraints  

- **Global variables are forbidden.**  
- The program must take the following arguments:  

  ```sh
  ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

- **`number_of_philosophers`** – The number of philosophers and the number of forks.  
- **`time_to_die`** (in milliseconds) – If a philosopher has not started eating within this time since their last meal or the start of the simulation, they die.  
- **`time_to_eat`** (in milliseconds) – The time it takes for a philosopher to eat. During this time, they must hold two forks.  
- **`time_to_sleep`** (in milliseconds) – The time a philosopher spends sleeping.  
- **`number_of_times_each_philosopher_must_eat`** *(optional)* – If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation stops when a philosopher dies.  

## Additional Details

- Each philosopher is assigned a number ranging from `1` to `number_of_philosophers`.  
- **Philosopher 1 sits next to philosopher `number_of_philosophers`**. Any other philosopher `N` sits between philosophers `N-1` and `N+1`.  
- **State messages should not overlap** with each other.  
- A message announcing a philosopher’s death must be displayed **within 10 milliseconds** of their actual death.  
