
/*Implementation file for class Songlist*/

#include "SongList.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

SongList::SongList()
{
	first = NULL;
	last = NULL;
	count = 0; //set size to 0, so we know there are no elements in our list

}

SongList::SongList(const char fileName[])
{
first = NULL;
last = NULL;
count = 0;


loadSongs(fileName); //accesses the SongList class member function loadSongs with the fileName parameter
}


/*Destructor. It releases the memory allocated for the array.*/
SongList::~SongList() //we set this destructor so that when we finish with our array, it will deallocate the memory the array occupied, so we don't get any memory leaks
{
	Node * current = first;

	while (first != NULL)
	{
		current = first->next;
		delete first; //delete the node pointed to by head. The destructor for Song is invoked automatically
		first = current;
	}
}

/*DESTRUCTOR NOTES:

The destructor deallocates the memory occupied by the nodes of a list
when the class object goes out of scope. Because memory is allocated
dynamically, resetting the pointers first and last does not deallocate
the memory occupied by the noes in the list. We must traverse the list,
starting at the first node, and delete each node in the list. The list
can be destroyed by calling the function destroyList. Therefore, the
definition of the destructor is:

template <class Type>
linkedListType<Type>::~linkedListType()
{
destroyList();
}
*/

/* Reads the entries from the file and adds them to the list.
in: fileName*/
void SongList::loadSongs(const char fileName[])
{
	ifstream in;
	char title[MAX_CHAR]; //declares local variables for us to store the contents of the file into
	char artist[MAX_CHAR];
	char duration[MAX_CHAR];
	char album[MAX_CHAR];
	int index = 0;


	Song aSong; //declares a variable of type Song (it has access to all member objects of class Song)

	in.open(fileName);
	if (!in)
	{
		in.clear();
		cerr << endl << "Failed to open filename '" << fileName << "' for input!" << endl << endl;
		exit(1);
	}

	in.getline(title, MAX_CHAR, ';'); //stores the contents of filename "in" into local variable "title," up until the deliminator ';' which tells the getline to stop reading.
	aSong.setTitle(title); //Takes the line (that we just read from "in" file and stored into our local "title" variable), and passes it as a parameter to the Song member function "setTitle()"
	/*remember, setTitle checks to see if Song member var is empty, if not, empties it, then sets the member pointer this->title = new char[strlen(title) +1] .. so it allocates a memory space just big enough to hold the passed in "title" length (+1 to be null-terminated)
	and then it copies the contents of the passed in "title" to the member var "this->title" -- strcpy(this->title, title);*/
	while (!in.eof()) //while there's more to be read from the input file, the above process repeats for each encapsulated element of the Song class
	{
		
		in.getline(artist, MAX_CHAR, ';');
		aSong.setArtist(artist);
		in.getline(duration, MAX_CHAR, ';');
		aSong.setDuration(duration);
		in.getline(album, MAX_CHAR, '\n');

		aSong.setAlbum(album);
		index++;
		addSong(aSong);
		in.getline(title, MAX_CHAR, ';');		//start the next record
		aSong.setTitle(title);
	}
	in.close();
}

/*This function returns the size of the list.
return: size*/
int SongList::getSize() const
{
return count;
}


/* Searches the list for an entry with passed in artist.
in: artist
out: match
return: true if a match is found and match will be returned through parameter.
false if a match can not be found and match contains garbage.*/
bool SongList::searchArtist(const char artist[], Song &match) const
{
	Node * current;
	char currentTitle[MAX_CHAR];
	char currentArtist[MAX_CHAR];
	char currentDuration[MAX_CHAR];
	char currentAlbum[MAX_CHAR];

	for (current = first; current != nullptr; current = current->next)
	{
		current->data.getTitle(currentTitle);
		current->data.getArtist(currentArtist);
		current->data.getDuration(currentDuration);
		current->data.getAlbum(currentAlbum);
		if (strcmp(artist, currentArtist) == 0)
		{
			match.setTitle(currentTitle);
			match.setArtist(currentArtist);
			match.setDuration(currentDuration);
			match.setAlbum(currentAlbum);
			cout << endl << currentTitle << endl << currentArtist << endl << currentDuration << endl << currentAlbum << endl << endl;
		}
	}
	if (!current)
	{
		return false;
	}
	else
	{
		return true;
	}
}



/* This function searches the list for an entry with passed in album.
in: album
out: match
return: true if a match is found and match will be returned through parameter.
false if a match can not be found and match contains garbage.*/
bool SongList::searchAlbum(const char album[], Song &match) const
{
	Node * current;
	char currentTitle[MAX_CHAR];
	char currentArtist[MAX_CHAR];
	char currentDuration[MAX_CHAR];
	char currentAlbum[MAX_CHAR];

	for (current = first; current != nullptr; current = current->next)
	{
		current->data.getTitle(currentTitle);
		current->data.getArtist(currentArtist);
		current->data.getDuration(currentDuration);
		current->data.getAlbum(currentAlbum);
//not getting past this point, even though album and currentAlbum are the SAME
//if i add a new song, not from the list, it can see it, and find it. 
		if (strcmp(album, currentAlbum) == 0)
		{
			match.setTitle(currentTitle);
			match.setArtist(currentArtist);
			match.setDuration(currentDuration);
			match.setAlbum(currentAlbum);

			cout << endl << currentTitle << endl << currentArtist << endl << currentDuration << endl << currentAlbum << endl << endl;
		}
	}
	if (!current)
	{
		return false;
	}
	else
	{
		return true;
	}

}

/*Prints all the entries to the standard output.*/
void SongList::printAll() const
{
	Node * current;

	int index = 0;
	
	char title[MAX_CHAR];
	char artist[MAX_CHAR];
	char duration[MAX_CHAR];
	char album[MAX_CHAR];

	for (current = first; current; current = current->next)
	{
		
		current->data.getTitle(title);
		current->data.getArtist(artist);
		current->data.getDuration(duration);
		current->data.getAlbum(album);

		cout << "Index: " << index << endl;
		
		index++;
		cout << "Title: " << title << endl << "Artist: " << artist << endl << "Duration: " << duration << endl << "Album: " << album << endl << endl;
	}
}

/* Saves the list to the external file.
in: fileName*/
void SongList::saveSongs(const char fileName[]) const
{
ofstream out;
Node * current;
char title[MAX_CHAR];
char artist[MAX_CHAR];
char duration[MAX_CHAR];
char album[MAX_CHAR];

out.open(fileName);
if (!out)
{
out.clear();
cerr << endl << "Failed to open filename '" << fileName << "' for output." << endl << endl;
exit(1);
}

for (current = first; current; current = current->next)
{
current->data.getTitle(title);
current->data.getArtist(artist);
current->data.getDuration(duration);
current->data.getAlbum(album);

out << title << ';' << artist << ';' << duration << ';' << album << endl; //Basically what we're pushing to the file "out"
}

out.close();
}

/* This function adds a song entry ordered by title.
in: aSong*/
void SongList::addSortedSong(const Song &aSong)
{

	char title[MAX_CHAR];
	char currentTitle[MAX_CHAR];


	aSong.getTitle(title);

	Node * newNode = new Node(aSong);

	Node * back = nullptr;
	Node * current = first;

	while (current)
	{
		current->data.getTitle(currentTitle);
		if (strcmp(title, currentTitle) < 0)
		{
			break;
		}
		back = current;
		current = current->next;

	}

	newNode->next = current;

	if (!back)
	{
		first = newNode;
	}
	else
	{
		back->next = newNode;
	}
	count++;
}

/* This function adds a song to the beginning of the list.
in: aSong*/
void SongList::addSong(const Song &aSong)
{
	addSortedSong(aSong);

}

/* This function returns the Song object at the specified position through parameter
in: index
out: aSong
return: true if the entry exists, false if illegal index is passed in*/
bool SongList::get(int index, Song &deleteSong, Song& aSong) const
{
	char title[MAX_CHAR];

	if (index < 0 || index >= count)
	{
		cout << "Index not found. " << endl;
		return false;
	}

	//traverse to the position
	Node * current = first;

	if (first == nullptr)
	{
		cout << "List is empty." << endl;
		return false;
	}
	else
	{

		for (int i = 0; i < index; i++) //stops at the index we want to delete
		{
			current = current->next;
		}
		current->data.getTitle(title);
		current->data.setTitle(title);

		Node * currentNode;
		char currentTitle[MAX_CHAR];

		for (currentNode = first; currentNode != nullptr; currentNode = currentNode->next)
		{

			currentNode->data.getTitle(currentTitle); //going through the currentNode and assigning it data
			if (strcmp(currentTitle, title) == 0)
			{
			//?	delete currentNode;
			//?	delete current;
				return true;
			}
		}

		return false;
	}
}

/* This function removes a passed in song from the list.
in: aSong*/
void SongList::removeSong(int index, Song& deleteSong, Song& aSong)
{
	Song song;
	Node * current;
	Node * trailCurrent;
	bool found;
	int currentIndex = 0;


	current = first;
	found = false;


	if (get(index, deleteSong, song) == true)
	{
		while (current != nullptr && !found) //while current's next link isn't empty
		{
			if  (currentIndex == index)	//if the currentIndex equals the index we want to delete
			{
				
				found = true; //jumps out of while loop
			}
			else //if item wasn't found at "currentIndex" keep traversing the list. 
			{ //this only executes if the item we want to delete isn't in the first node. so we know there is more than one node, so we can update the traversers
				trailCurrent = current; //set the prev node to the current node
				current = current->next; //set the current node to point to the next node
				currentIndex++;
			}
		}

		if (current == nullptr) //if current is empty
		{
			cout << "List has been initialized empty. Cannot delete from an empty list." << endl;
		}
		else
		{
			if (currentIndex == index) //if the item to be deleted is found at our current traversing address (currentIndex, or current->data == deleteItem)
			{
				if (first == current) //if the item to be deleted is in the first node
				{
					cout << "Item to be deleted is the first in the list." << endl;
					first = first->next; //set the new "first" node to the address of the next node. (ie. remove the first node)
					if (first == nullptr) //if the updated first now points to an empty node
					{
						last = nullptr; //update the last pointer to empty.
					}
					delete current; //delete our traverser
				}
				else //if item to be deleted isn't in the first node
				{
					cout << "Item to be deleted isn't the first item in the list" << endl;
					trailCurrent->next = current->next; //copies current's next into trailCurrent's next
				//	if (current == last) 
					if (index == (count-1))//if the item we want to delete is in the last node ? why doesn't the book's example if(current==last) work?
					{
						cout << "Item to be deleted is the last in the list." << endl;
						last = trailCurrent; //set the last address to the "one before last" node?
					}
					delete current;
				}
				count--;
			}
			else //if the list isn't empty, but the item to be deleted isn't in it.
			{
				cout << "List is not empty, but item to be deleted was not found." << endl;
			}
		}
	}

}
