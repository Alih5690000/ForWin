wcc main.c -o main \
    -ISDL2/x86/include \
    -LSDL2/x86/lib \
    -lmingw32 -lSDL2main -lSDL2 -mwindows