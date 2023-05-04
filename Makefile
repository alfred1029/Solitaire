FLAGS = -std=c++11

checkInput.o: checkInput.cpp checkInput.h
	g++ $(FLAGS) -c $<

initTable.o: initTable.cpp initTable.h card.h
	g++ $(FLAGS) -c $<

guiTemp.o: guiTemp.cpp guiTemp.h card.h
	g++ $(FLAGS) -c $<

move.o: move.cpp move.h card.h
	g++ $(FLAGS) -c $<

main.o: main.cpp initTable.h
	g++ $(FLAGS) -c $<

main: main.o initTable.o guiTemp.o move.o checkInput.o
	g++ $(FLAGS) $^ -g -o $@

clean:
	rm -f main main.o initTable.o guiTemp.o move.o checkInput.o

.PHONY: clean