# Cycles-Nanoseconds-Counter
This project shows how to measure the performance of a C++ code by measuring the total execution time either in nanoseconds (ns) or CPU cycles. Currently its tailored for Cortex-A72 32 bits - 64 bits (both nanoseconds + CPU cycles), and Intel CPUs (nanoseconds).

The CPU cycle counter section of this repository is hugely based on the repository of Matthias J. Kannwischer (@mkannwischer) and @vincentvbh: https://github.com/mupq/pqax

## Benchmarking

First, you must enable access to the performance counters from user mode. To do so:

```
cd enable_ccr
make
make install
```
If you get an error while running `make`, then update and upgrade your system. Also, you might need to install the kernel headers. To do so, run:
```
sudo apt install raspberrypi-kernel-headers
```

## Code build and execution

The repository has two files: **Main.cpp** and **Makefile**. 

To build the code, inside the folder containing these files, just run
```
make clean
make
```
This will generate a *test* file, which you can then execute by running
```
./test
```

## Measuring CPU Cycles vs. Nanoseconds Execution Time

Inside the **Makefile** there is the following line:
```
MEASURETIME = nanoseconds
```
If you want to measure the execution time by nanoseconds, keep this code as shown. If you want to measure the cycles count, then modify it to
```
MEASURETIME = cycles
```
Then again, clean and make with
```
make clean
make
./test
```

### Note

The included **Makefile** does not have any -O2 nor -O3 flag. If you want to optimize, then add -O2 (or -O3) into the line
```
$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) -g $(EXTRACONDITIONS) -lssl -lcrypto -D $(MEASURETIME)
```
becoming
```
$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) -g $(EXTRACONDITIONS) -lssl -lcrypto -D $(MEASURETIME) -O3
```

In some cases, depedning on your code, architecture and optimization flags, you can get CPU counts really small (or 0). When you compile with -O3, unsued sections of code and variables are skipped.

If you want to check what it is happening in the assembly, just run
```
objdump -d test > test_asm
sudo nano test_asm
```

## Modifying custom code

Inside the **Main.cpp**, you will find the following code
```c
unsigned long long startTime = 0;
unsigned long long endTime = 0;
unsigned long long totalTime = 0;

startTime = get_timestamp();

//Do something. This code is just an example
for (int i = 0; i < 99999; i++) {
  int temp = (int)(i * i * i * i);
}

endTime = get_timestamp();

unsigned long long executionTime = ((unsigned long long)(endTime - startTime));
totalTime += executionTime;
```

As you can see, to measure the time (either in nanoseconds or CPU cycles), just add
```c
startTime = get_timestamp();
```
before your code, and 
```c
endTime = get_timestamp();
```
after your code. Then deduct the difference by
```
unsigned long long executionTime = ((unsigned long long)(endTime - startTime));
```
and add it to your global execution time variable as
```
totalTime += executionTime;
```

## Limitations

Originally this code only worked for Cortex A-72 CPUs. Now it works for Cortex A-72 and Intel CPUs, with the limitation that for Intel CPUs only the execution time (in nanoseconds) will be measured.

## Warnings

If you get an **Illegal instruction** error, its because you are trying to measure the CPU cycles without mounting the Kernel module. Just run
```
cd enable_ccr
make
make install
```
