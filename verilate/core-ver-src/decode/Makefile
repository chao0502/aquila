all:
	g++ -c InstEntry.cpp
	g++ -c instforms.cpp
	g++ -c IntRegs.cpp
	g++ -c DecodedInst.cpp
	g++ -c decode.cpp
	g++ -c FpRegs.cpp
	g++ InstEntry.o instforms.o IntRegs.o DecodedInst.o decode.o FpRegs.o decode
clean:
	rm -f *.o decode