**Dumitru Bianca Stefania**
**312CA**

## Homework #2 - Data Structures - The Library of HashBabel

## General description and notes:

-The program is meant to operate some database-like structures: books,
    a library and a users' database. All of them are represented in 
    memory as hashtables, making acces to any element fast and easy.

    * The library is a hashtable that is mapping each book name to 
        the specific book data structure.
    * A book is a data structure that contains details related to the book and 
        also a hashtable mapping all the definitions present in the book.
    * The users' hashtable is mapping a user name to the specific details of a 
        user, such as the number of points he has or the book he borrowed

- All the elements in the hashtables are dinamically alocated in memory,
using malloc(), realloc() and free() functions from the stdlib.h library.

- I defined 2 data structures: "book_t" and "user_t", used for storing the 
    elements related to a specific book/user inside a hashtable.

- Both the hashtable for the library and for the users are created at the 
    beginning of the program.

## Commands:
- There are 11 possible commands that can be recieved from input:

1) ADD_BOOK book_name no_def
    - check if the book is already in the library. if yes, free its memory 
        and eliminate it from the library
	- allocate dinamically the necessary memory for the new book
	- read the key-value pairs for the definitions and stores them inside 
        the book hashtable
	- adds the new book inside the library hashtable

2) GET_BOOK book_name
	- find the book in the library hashtable
    - print details of the book

3) RMV_BOOK book_name
	- find the book in the library hashtable
    - free book's memory eliminate it from the library

4) ADD_DEF book_name key value
	- find the book in the library hashtable
    - add the key-value definition pair inside the book hashtable

5) GET_DEF book_name key
	- find the book in the library hashtable 
    - find the definition with given key in the book hashtable
    - print the associated value to the key from the book hashtable

6) RMV_DEF book_name key
	- find the book in the library hashtable
    - free entry from the book hashtable, corresponding to the key

7) ADD_USER user_name
    - allocate dinamically the necessary memory for the new user
	- add the user inside the users hashtable

8) BORROW user_name book_name promised_days
	- make a user borrow a certain book
    - mark the book as borrowed
    - mark the user as having borrowed the given book

9) RETURN user_name book_name actual_days rating
	- make a user return a certain book
    - update user's points based on the no of days he kept the book
    - mark the book as not borrowed and update its rating
    - mark the user as having no book borrowed

10) LOST user_name book_name
    - make a user loose a certain book
    - free book's memory eliminate it from the library
    - decrease 50 points from the user's points
    - mark the user as having no book borrowed
	
11) EXIT
    - print the ranking for the books based on their rating, 
        no of purchases and names
    - print the ranking for the books based on their no of points and names
    - free the memory for all the books inside the library and the library itself
	- free the memory for the users' hashtable
	- stop the program
