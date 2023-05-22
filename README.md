# Hangman

Gillian Yeomans, London, UK
<br><br>

### 🎥 Video Demo:
<https://www.youtube.com/watch?v=nNvgrqX1QYA>
<br><br>

### 📸 Screenshots:
Game won
<br>
<img src="https://i.imgur.com/xbmaoDY.jpeg" width="200" />
<br><br>
Game lost
<br>
<img src="https://i.imgur.com/UgDLz2I.jpeg)" width="200" />

<br><br>
### 📝 Description:
I chose to make the classic game [Hangman](https://en.wikipedia.org/wiki/Hangman_(game)) for my CS50 final project.  I chose to make it as a command line program using C.  I chose C because I am already a web developer and wanted to improve my knowledge of a lower level programming language.
<br><br>
### 👩‍💻 Development process:
Originally I wrote everything in one file, `hangman.c`.  Nearer the end of the project, I refactored the code a bit to move functions besides `main` to `helpers.c`.  I also put the array of strings which contain the hangman ASCII art into the helpers file.  This was to clean up `main` and make it easier to follow its logic at a high level.
edit: didn't copy this locally. the command to compile is `clang hangman.c helpers.c -o hangman -lcs50` and I think you had to download and install the CS50 library too

I found a list of English words at https://www.curlewcommunications.uk/index.html and downloaded this to `wordlist.txt`.  I did some cleaning up of the list, to remove:
* words shorter than 3 letters
* words with hyphens
* words with apostrophes
* removing carriage returns

I largely did this with the `grep` command.

I developed the project on my local machine and used the command `clang hangman.c helpers.c -o hangman -lcs50` to compile the program.  Now that I have uploaded it to the CS50 Codespace I have added a `Makefile` so that it can be compiled by running `make hangman`.

I couldn't figure out how to use `valgrind` on my Mac, but I found it has a similar program `leaks`.  Running `leaks -atExit -- ./hangman` did not reveal any memory leaks.

For most of the project I used the vim text editor, which I am not very fluent with.  It was good practice, but at the end I switched to VSCode which I find a lot easier to use!
<br><br>
### 😖 Difficulties:
I found the array and memory management stuff quite tricky - I got better and it felt more intuitive as I went on, but it is definitely still something I haven't fully got my head around.  I think a couple of the things I did were probably a bit hacky.  It was good practice though, and I ran into some new things like difficulty in returning a pointer from a helpers function (`load_and_choose_word`) because of how the program would normally release memory of locally declared variables.  I forgot about `strlen` for a while and originally had a lot more for loops that stopped when they found `array[i]` was `'\0'`.

I learnt about 'array decay' (maybe that was mentioned in lectures and I'd forgotten).  My original hardcoded testing word was only 4 letters which meant I didn't notice for a long time that when I was calculating sizeof(word_to_guess) when it was passed into a function, it would always return 8.  This became apparent when I started seeing weird bugs when I was using longer words from the wordlist.

I had a moment of confusion when I moved from my one hardcoded word to actually choosing something at random from `wordlist.txt`, and every single time the program chose 'corvette'.  [A weaker man might be moved to reexamine his faith](https://www.youtube.com/watch?v=gOwLEVQGbrM).  Some research revealed that I needed to seed `rand()` with a different value each time to get a different result.

<br><br>
### 📈 Proposed Improvements:
I did not add any error handling to the code other than some simple input validation 👀

The validation doesn't stop the user inputting non-letter characters, like punctuation

I think the visual display and spacing of what's output to the terminal could be improved further.  I did use colours a little bit but was wary to go overboard with them.  I feel like I didn't find a perfect way to 'separate' each round - I could have printed even more new lines but it felt a bit hacky.

I feel like my dictionary-loading function is pretty ropey.  I set semi-arbitrary numbers for the lengths of the `words` array.  I checked that the numbers I used were enough - `wc` reveals there are just under 75,000 words in the file and 'antidisestablishmentarianism' is the longest word (29 letters).  I could have used those specific lower numbers but I thought rounding up might be a bit more flexible in case the wordlist changed.  Ideally I would do something which only allocates the space needed per word, instead of an arbitrary 40 each time, but I also thought this is probably fine since it's not really a huge amount of memory.

Although I went back and cleaned up the code a bit, I think I could refactor the logic some more to make it sharper.

One further development I think would be nice is to also print the dictionary definition of the word at the end.  As I played the game to test it, I often found I had no idea what the word meant because the wordlist includes some unusual vocabulary (e.g. parallelepiped, bleb).