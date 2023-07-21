# Question 1
The GPU utilisation is 100% since there is no IO issuing.

# Question 2
Process 1 and Process engages CPU for 4 cycles and 2 cycles respectively. CPU is busy for 6 cycles. The total cycles are 4 + 6 (1 for io issuing, 5 for waiting io, 1 for io done) = 11 cycles. Thus, the utilisation is 6 / 11.

# Question 3
It takes less timestamps i.e. 7. After starting IO, Process 1 is blocked, and Process 2 can take the control of CPU.

# Question 4
It takes 11 timestapms, same to Question 2.

# Question 5
It taks 7 timestamps, same to Question 3.

# Question 6
It takes 17 timestamps. The CPU utilisation is full.

# Question 7
It should take the same timestamps as the Question 6. The data fetched from IO resides in memory, if running the process just completed IO, the data can be consumed, which reduces the memory utilisation.

# Question 8
`IO_RUN_LATER` takes less timestamps, because the deffered IO completing instruction can overlap with the other process in blocking. `SWITCH_ON_END` takes more timestamps since the the BLOCK state of the current process blocks all the other processes.