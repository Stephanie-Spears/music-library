all:
	g++ -g UserInterface.h UserInterface.cpp Main.cpp Song.h Song.cpp SongList.h SongList.cpp InputTools.cpp InputTools.h -o proj5

clean:
	rm  proj5
