# CS311_HW5_MSArray
 [Assignment 5](https://www.cs.uaf.edu/~chappell/class/2023_fall/cs311/docs/d-assn05d.html) in Data Structures and Algorithms: Marvelously Smart Array
 Lisa Jacklin && Jewel Maldonado

## Requirements:  
*Shown below are some requirements and checklist items:*  
- [ ] Exercise A - Marvelously Smart Array Class Template
    **Purpose**  
    - write a class template acts as a "smart array", alsmost as smart as `std::vector`  
    - the array will be resizable and exception safe as well as efficient  
    - the key to the assignment is exception safety, make sure the exceptions thrown by value-type operations are properly handled and that all safety guarantees are documented  
    **Instructions**  
    - All [coding standards](https://www.cs.uaf.edu/~chappell/class/2023_fall/cs311/docs/coding_std.html) now apply.
    - [ ] Name the class template "`TMSArray`" example a `TMSArray` whose items have type `double` would be declared as `TMSArray<double> `
    - [ ] implement th ecalss template in file tmsarray.hpp, since its a template there should be no associated source file.  
    **Interface is as follows:**  
    - An object of type `TMSArray<Val>` should act as if it maintains a single array with a given size and value type `Val`.  
    - A `const TMSArray` should be one that doesn not allow modification of th eitems in its array. A non-`const TMSArray` should allow such modification.  
    - **You may not create any new implicit type conversions. (Hint: 1-parameter constructors, “explicit”.)**  
    - Include the following **public member types** and no others:  
```cpp
value_type // The type of each item in the array
size_type // The type of the size of an array and an index into an array.
iterator // The type of a random-access iterator that allow modification of the item it references.
const_iterator // The type of a random-access iterator that does not allow modification of the item it references.
```
   
