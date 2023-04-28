FLAGS = -std=c++11

initTable.o: initTable.cpp initTable.h card.h
	g++ $(FLAGS) -c $<

guiTemp.o: guiTemp.cpp guiTemp.h card.h
	g++ $(FLAGS) -c $<

move.o: move.cpp move.h card.h
	g++ $(FLAGS) -c $<

main.o: main.cpp initTable.h
	g++ $(FLAGS) -c $<

main: main.o initTable.o guiTemp.o move.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o initTable.o guiTemp.o move.o

.PHONY: clean