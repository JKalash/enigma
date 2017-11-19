OBJS = main.o enigma.o plugboard.o reflector.o rotor.o
CXX = g++
DEBUG = -g
CXXFLAGS = -Wall $(DEBUG) -std=c++11
LDFLAGS = -pthread

enigma: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm enigma main.o enigma.o plugboard.o reflector.o rotor.o