gcc main.c -o main \
    -ISDL2/x86/include \
    -LSDL2/x86/lib \
    -lSDL2main -lSDL2 -mwindows