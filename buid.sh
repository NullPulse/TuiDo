cd src
g++ -c main.cpp
g++ -o TuiDo -lncurses $1.o
mv TuiDo ..
rm main.o
cd ..
