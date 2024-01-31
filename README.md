--------------------------------------------------------------------------------------------------------------
**RUNNING THE CODE**
--------------------------------------------------------------------------------------------------------------
g++ 210101050_Lab1.cpp 
./a.out <input_file_name>

**THREE FILES ARE GENERATED**:
    1.**PASS_1_output.txt(contains intermediate code)**
    2.**Intermediate.txt(contains intermediate code as well but this is the one that pass2 scans)**
    3.**programme(a text file with the object code)**

--------------------------------------------------------------------------------------------------------------
**ASSUMPTIONS**:
--------------------------------------------------------------------------------------------------------------
**ENSURE***
1.**There are no paddings before any line in the assembly instructions,not even for comments**
2.**DO NOT ENTER ANY EMPTY LINE IN THE ASSEMBLY CODE->it gives segmentation fault**
3.**Label, Opcode and Operand each have a field size of exactly 10 characters (Don't use tabs for padding).**
4.**Comments must have "." symbol in the Label field.**
5.**Size of object file<30 lines can be generated**

6.**NAME OF THE VARIABLES/LABELS/OPCODES/OPERANDS SHOULD NOT HAVE WHITESPACE CHARACTER**
7.**NAME OF THE PROGRAMME MUST BE LESS THAN 20 CHARS IN LENGTH**
8.If there is no label beside START then programme is named as UNTITLED and the start address is assigned 0.
9.Restricting our programme to only the instructions as mentioned in the assignment and NOT INDULGING WITH RELOCATIONS etc.


--------------------------------------------------------------------------------------------------------------
