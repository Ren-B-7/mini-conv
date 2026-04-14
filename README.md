## tempconv

Small c based library, has 1 binary and 12 symlinks.

- binary
  - conv
- symlinks
  - c2f
  - f2c
  - k2l
  - l2k
  - m2i
  - i2m
  - m2f
  - f2m
  - k2m
  - m2k
  - c2i
  - i2c
  - y2m
  - m2y

```bash
conv -t -c {celsius}      # Celsius to Fahrenheit
c2f {celsius}             # Celsius to Fahrenheit

conv -t -f {fahrenheit}   # Fahrenheit to Celsius
f2c {fahrenheit}          # Fahrenheit to Celsius

conv -w -k {kilograms}    # Kilograms to Pounds
k2l {kilograms}           # Kilograms to Pounds

conv -w -l {pounds}       # Pounds to Kilograms
l2k {pounds}              # Pounds to Kilograms

conv -d -m {metres}       # Metres to Inches
m2i {metres}              # Metres to Inches

conv -d -I {inches}       # Inches to Metres
i2m {inches}              # Inches to Metres

conv -d -M {metres}       # Metres to Feet
m2f {metres}              # Metres to Feet

conv -d -F {feet}         # Feet to Metres
f2m {feet}                # Feet to Metres

conv -d -k {kilometres}   # Kilometres to Miles
k2m {kilometres}          # Kilometres to Miles

conv -d -mi {miles}       # Miles to Kilometres
m2k {miles}               # Miles to Kilometres

conv -d -c {centimetres}  # Centimetres to Inches
c2i {centimetres}         # Centimetres to Inches

conv -d -i {inches}       # Inches to Centimetres
i2c {inches}              # Inches to Centimetres

conv -d -me {metres}      # Metres to Yards
m2y {metres}              # Metres to Yards

conv -d -y {yards}        # Yards to Metres
y2m {yards}               # Yards to Metres
```

### Build and Install

**Build:**

```bash
make
```

**Run tests:**

```bash
make test
```

**Run valgrind tests:**

```bash
make valgrind-test
```

**Install to `~/.local/bin/`:**

```bash
make install
```

**Clean build artifacts:**

```bash
make clean
```

### Further notes

To change the link names the MakeFile and the C code has to be adjusted.  
Handles double floating point operations and prints to 3 decimals.
