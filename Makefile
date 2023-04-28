initTable.o: initTable.cpp initTable.h card.h
	g++ -c $<

guiTemp.o: guiTemp.cpp guiTemp.h card.h
	g++ -c $<

main.o: main.cpp initTable.h
	g++ -c $<

main: main.o initTable.o guiTemp.o
	g++ $^ -o $@

clean:
	rm -f main main.o initTable.o guiTemp.o

.PHONY: clean