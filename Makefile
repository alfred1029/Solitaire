FLAGS = -g -std=c++11 -lncurses

checkInput.o: checkInput.cpp checkInput.h redoUndo.h
	g++ $(FLAGS) -c $<

initTable.o: initTable.cpp initTable.h card.h
	g++ $(FLAGS) -c $<

gui.o: gui.cpp gui.h card.h
	g++ $(FLAGS) -c $<

guiTemp.o: guiTemp.cpp guiTemp.h card.h
	g++ $(FLAGS) -c $<

move.o: move.cpp move.h card.h
	g++ $(FLAGS) -c $<

redoUndo.o: redoUndo.cpp redoUndo.h card.h
	g++ $(FLAGS) -c $<
	
checkWin.o: checkWin.cpp checkWin.h card.h
	g++ $(FLAGS) -c $<
	
leaderboard.o: leaderboard.cpp leaderboard.h card.h
	g++ $(FLAGS) -c $<

main.o: main.cpp initTable.h
	g++ $(FLAGS) -c $<

main: main.o initTable.o guiTemp.o move.o checkInput.o redoUndo.o checkWin.o leaderboard.o gui.o
	g++ $(FLAGS) $^ -o $@ -lncurses

clean:
	$(command) *.o *.exe main

run: clean main
	./main

.PHONY: clean