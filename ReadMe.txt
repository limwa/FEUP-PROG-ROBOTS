T03_G03
GROUP MEMBERS:
- 202004260 Mariana de Matos Lourenço Lobão
- 202008169 André Costa Lima
PROGRAM DEVELOPMENT STATE:
- Every objective was acomplished.
- Some improvements were made in reading and storing the names of the players in the "winners" files. Since the length method in a C++ string returns the number of bytes in the string and not the number of UTF8 characters, we had to make our own function to count them, in order to support names with non-ASCII characters (like á, è, é, à, ó, ã, etc.).
MAIN DIFFICULTIES:
- Storing the names in the "winners" files: we were getting the names misaligned in the "winners" files, since the length method of a string does not work well with non-ASCII characters.
