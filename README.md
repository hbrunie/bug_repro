# bug_repro

Reproduce gotcha bug on wrapping dgemm\_ from intel.

git clone https://github.com/LLNL/GOTCHA.git
mkdir -p ./GOTCHA/build/
cd ./GOTCHA/build/

`cmake .. -DCMAKE_INSTALL_PREFIX=${PWD}`

I Compiled testGotcha with

`g++ testGotcha.cpp -I ./GOTCHA/include/ -L ./GOTCHA/build/ -lgotcha -shared -fPIC -o ./libtest_gotcha.so -g`

testGEMM to test GOTCHA with

`icpc testDGEMM.cpp -L./ -ltest_gotcha -mkl -g -o testDGEMM-withGOTCHA`

execute with

`./testDGEMM-withGOTCHA`

Erro msg:
```
Start test
Before wrappee dgemm call
./testDGEMM-withGOTCHA: symbol lookup error: /opt/intel/compilers_and_libraries_2019.3.199/linux/compiler/lib/intel64/libiomp5.so: undefined symbol: ompt_start_tool```

**Testing dlsym without GOTCHA**

I compiled the wrapper with

`g++ test_wrapSymbol.c -fPIC -shared -o libtest_wrapSymbol.so -ldl`

warning at compile:

```
test_wrapSymbol.c:1:0: warning: "_GNU_SOURCE" redefined
 #define _GNU_SOURCE
<command-line>:0:0: note: this is the location of the previous definition
```

testGEMM to test the simple wrapper with

`icpc testDGEMM.cpp -L./ -ltest_wrapSymbol -mkl -g -o testDGEMM-withoutGOTCHA`

execute with:

`LD_PRELOAD=./libtest_wrapSymbol.so ./testDGEMM-withoutGOTCHA`

Output:

```
start0...
start1 0x2aaaab069140
TRY WRAP...
WRAP SUCCESS
C[0] = 2850.000000
C[1] = 7350.000000
C[2] = 11850.000000
SUCCESS: 5.08883e+276
```
