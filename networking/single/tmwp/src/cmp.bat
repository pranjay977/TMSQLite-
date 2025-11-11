g++ -std=c++0x -c wrapper.cpp tmwp7.cpp -I ..\include
ar rcs abbm.lib *.o
move abbm.lib ..\lib
