# Behaivour Tree

[Twitter](https://twitter.com/conPdePABLO)

[LinkedIn](https://www.linkedin.com/in/parequena/)

[GitHub](https://github.com/parequena)

## Features

- C++20's concepts.
- CMake basic structure.
- constexpr all things.
- Templatized structures/functions.
- Memory pool / memory arena.
- Tiny Behaivour tree example: 
```
    Steps:
    1 . BTBoolean = false, so return FAIL.
    2 . Sequence fails, so return FAIL.
    3 . Selector its gonna look next branch.
    4 . Sequence returns SUCCESS.
    5 . BTBoolean = true, return SUCCESS.
    6 . Return SUCCESS.

                    SELECTOR
                /           \
            SEQUENCE         SEQUENCE
        /        \         /      \
    BOOLEAN   SAY_NAME   MOVE      MOVE
```

## File / Class Structure
- **include**
    - BehaivourTree.hpp  : Behaivour tree class.
    - BTNode.hpp         : BTNode created (Selector and Sequence templatized)
    - BTNodeSelector.hpp : Specialization selector.
    - BTNodeSequence.hpp : Specialization sequence.
    - Node.hpp           : Node class to derive and use on our Behaivour tree.

- **src:** Main and helper functions.
- **CMakeLists:**  Generation / Compilation file.
 
## Installation and compilation
1. Clone this repositoy `git clone https://github.com/parequena/BehaviourTree`
2. Get into our folder `cd BehaviourTree`
3. Create build folder `mkdir build && cd build`
4. Generate the project `cmake .. # Add as much variables as you want`
5. Compile and execute `make && ./BehaviourTree`
