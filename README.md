# MI-BHW.16 Course
## Bezpečnost hardwaru
### CTU / ČVUT FIT

#### Task 1 - DPA - differential power analysis
The first task was similar to the one from the MI-HWB course. We were operating with oscilloscopes measuring power consumption of a small java card device. This java card was encrypting accepted data using AES with an unknown hardcoded key. Our task was to break the cipher and get the key providing plain and corresponding cipher texts.

Power analysis takes an advantage from correlation analysis of power consumption measurements. The attack exploits biases varying power consumption of microprocessors or other hardware while performing operations using secret keys.

You can find `Matlab` and `GNU Octave` source codes in the directory.

#### Task 2 - implementation of the PRESENT cipher
My assignment was to implement the PRESETNT cipher for AVR with atmega163 CPU. The destination device was a simple AVR-based card controlled by sending signals using USB client application.

Actual implementation was inspired by an open-source implementation taken from the github. It takes place in the `example_PRESENT.c` file. You can change the hardcoded key in `crypt.h`.

To build a solution please use `AVR studio` and proceed as usually.
##### How to run
1. Using the AVR studio build the project
2. Flash the output
3. Connect the card to a computer using the Java Smart Card client
4. Call the encryption method via: `CLA: 0x80` and `INS: 0x60`

#### Task 3 - implementation of poin addition over Elliptic curve over GF(p)
My task task to implement Elliptic curve operations necessary for adding two points. Prior to that I had to implement `GF(p)` operations such as `addition`, `multiplication`, `inversion` and `comparison`. Every result of each operation is a residual of division with prime number as a modulus. I have implemented operation over `Montgomery domain` as well. Montgomety domain is a special domain created to avoid inversion as the most expensive operation in terms of runtime.

All operations are done in fixed length arighmetics - to change the length change the following lines in `poly.h`:
```c
#define BYTES_CNT 10
#define BITS_CNT 80
```

The prime number can be set in the function `ECinit` `ec.cpp`.

##### How to run
1. Using the Arduino IDE build and flash Arduino
2. Connect the device via serial port and wait for instructions
3. Output of the point addition should be sent back

#### Task 4 - implementation of Diffie - Hellman over EC(GF(p))
This task was an extension over the previous one. I had to implementan addition operations allowing user to compute scalar sum of the chosen point `A = n*K`.

To speed up processing on such a lowend device arduino is I incorporated the `double and add` algorithm. It is very similar to the well-known `square and multiply` algo.

The rest is very similar to the previous task.


##### How to run
1. Using the Arduino IDE build and flash Arduino
2. Connect the device via serial port and wait for instructions
3. Output of the point addition should be sent back
