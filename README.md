[//]: # (A object oriented program written in C++ that solves arithmetic and boolean expressions )

# Expression solver

Made in C++ using object oriented programming :)

## Requirements
- g++ compiler

## How to run the code
1. Clone or download the repository
2. Compile the files by running:

```
g++ main.cpp -o main
```

3. Run the compiled executable file:

```
.\main.exe
```

4. Input the Expressions according to the following _input format_:

    - <font style="font-weight: 100"> 1º line: _c_ (1 &le; c &le; 100,000) </font>
    - <font style="font-weight: 100"> next _c_ lines: &lt;Expression&gt; </font>
    
- Example:
    
    - <font style="font-weight: 100"> input: </font> <br>
    ```
    7
    1
    2 + 3 * 2
    ( 2 - - -3 ) * 2
    3 / 2
    true || false == false
    ( true || false ) == false
    true + 3
    ```

    - <font style="font-weight: 100"> output: </font> <br>
    ```
    1
    8
    -2
    1
    true
    false
    error
    ```