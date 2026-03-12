x86_64-w64-mingw32-gcc main.c -o main \
    -ISDL2/x86/include \
    -LSDL2/x86/lib \
    -lSDL2main -lSDL2 -mwindows