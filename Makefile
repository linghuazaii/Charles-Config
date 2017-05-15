cc=g++
cppflags=-g 
INCLUDE=-I./depend/json-c/include
LINK=-L./depend/json-c/lib \
	 -ljson-c
SRC=./src/charles_config.o ./src/main.o
TAR=./bin/test

all : $(TAR)

$(TAR) : $(SRC)
	$(cc) $^ -o $@ $(LINK)

%.o : %.cpp
	$(cc) $(INCLUDE) $^ -c -o $@ $(cppflags) 

clean:
	-rm -f $(SRC) $(TAR)
