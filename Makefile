CStackRunner:  CStack.o Factory.o main.o
	wg++ -fno-elide-constructors -std=c++11 Factory.o CStack.o main.o -fopenmp

main.o: main.cpp CStack.h Factory.h
	wg++ -fno-elide-constructors -std=c++11 main.cpp -c -fopenmp

CStack.o: CStack.cpp CStack.h Factory.h
	wg++ -fno-elide-constructors -std=c++11 CStack.cpp -c -fopenmp

Factory.o: Factory.cpp Factory.h CStack.h
	wg++ -fno-elide-constructors -std=c++11 Factory.cpp -c -fopenmp

clean:
	rm -f *.o
	rm -f *.out
	rm -f file*