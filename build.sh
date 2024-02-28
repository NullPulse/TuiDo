cd src
g++ -c main.cpp
g++ -o TuiDo -lncurses main.o
mv TuiDo ..
rm main.o
cd ..
