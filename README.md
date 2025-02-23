# Simple Calculator Based on MFC

## Project Description

This project is a simple calculator developed using the MFC (Microsoft Foundation Classes) framework. The calculator features a variety of functions, including basic arithmetic operations such as addition, subtraction, multiplication, and division, as well as scientific calculation functions like sine, cosine, tangent, cotangent, arcsine, arccosine, arctangent, reciprocal, square root, cube root, square, cube, logarithms (natural logarithm and common logarithm), and exponentiation. Additionally, the calculator supports a memory function, allowing users to use the result of the current calculation in the next calculation.

<br>The main features of the project are as follows:
1. **User-friendly Interface**: The calculator has 39 buttons, 2 input boxes, and a title bar, making it simple and intuitive to use.
2. **Diverse Input Methods**: Users can input numbers and operators using buttons or directly enter expressions in the input boxes.
3. **Data Validation**: During the calculation process, the program checks the correctness of the input data and provides reminders if errors are detected.
4. **Operator Precedence Recognition**: The calculator can identify and correctly handle the precedence of operators, with logarithmic operations having the highest priority.
5. **Floating-point Number Processing**: For floating-point number output, the program processes the number based on its digits. If it is an infinite decimal, it outputs up to 9 digits.
6. **Support for Special Constants**: The calculator supports the input of mathematical constants π (with a value of 3.14159265358979323846) and e (with a value of 2.71828182845904523536).
7. **Memory Function**: The result of the calculation can be added to the next calculation using the ANS key.

<br>The core algorithm of the project is implemented using a linked list structure, which abstracts the expression into linked list nodes. Each node records the value of the current operand, the operator, and its precedence. Through this method, the program can efficiently handle complex expressions and correctly calculate the results.

## Running Steps
### For exe file
Simply run the file.

### For project files
1. Extract the project to the same directory.
2. Open the `calculator.sln` file using VS2022 and run it.
  
