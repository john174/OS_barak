#!/bin/bash
<<<<<<< HEAD
make
if [ -f "./MyShell" ]; then
    ./MyShell
    make clean
else
    echo "Error: The executable file does not exist."
fi
=======
make clean
make
./MyProject
>>>>>>> 24fc1e0669d480527a1bebe48b8246f8b6bded7b
