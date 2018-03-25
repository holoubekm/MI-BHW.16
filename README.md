# MI-PAA Course
## Problémy a algoritmy
### CTU / ČVUT FIT

#### Task 1 - Differential power analysis
#### Task 2 - Implementation of PRESENT cipher for ATmega163
#### Task 3 - Implementation of EC over GF(p) for Arduino
Task was to implement operations necessary to add two point on the given Elliptic Curve. Implemented is custom fixed length arithmetic over the GF(p). Furthermore the Montgomery domain is implemented to speed-up computation efficiently avoiding the multiplicative inversion.

##### How to modify
```
# Due to memory limitation all computation is done in fixed length arithmetic
# Please change the following values in poly.h to according your needs
#define BYTES_CNT 10
#define BITS_CNT 80
#define PRIME_BITS 80

# The prime number used as a modulus can be changed in ECinit in the ec.cpp

```

The program waits for user input, then adds those two points and waits in an endless loop.

**Warning:** there is not check whether points lie on the curve!

##### How to compile and run
You can use Arduino IDE to compile solution in this folder and use it to flash it to the Arduino.

#### Task 4 - Implementation of Diffie - Hellman over EC(GF(p)) for Arduino
This is an extension of previous task. Now the user is asked to insert a point `P` and number `n`, then the `Y = nP` is computed and printed over serial line.

##### How to modify
```
# Due to memory limitation all computation is done in fixed length arithmetic
# Please change the following values in poly.h to according your needs
#define BYTES_CNT 10
#define BITS_CNT 80
#define PRIME_BITS 80

# The prime number used as a modulus can be changed in ECinit in the ec.cpp
```

The program waits for user input, then adds point `P` `n` times with itself and waits in an endless loop.

**Warning:** there is not check whether points lie on the curve!

##### How to compile and run
You can use Arduino IDE to compile solution in this folder and use it to flash it to the Arduino.
