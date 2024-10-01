






FLAGS := -m64 -std=c++17 -g -ftemplate-backtrace-limit=0

all: cereal_test


cereal_test: ./cereal_test.cpp ./data.h serialize.o ./serialize.h 
	$(CXX) ./cereal_test.cpp serialize.o -o cereal_test -I ./ -I ../include/ $(FLAGS)


serialize.o: ./data.h ./serializers.h ./serialize.cpp ./serialize.h
	$(CXX) -c ./serialize.cpp -o serialize.o -I ./ -I ../include/ $(FLAGS)


clean:
	rm -rf serialize.o cereal_test
