# URLs-scanner-from-HTML-file

### This is a C++ program for extracting the scheme and domain name part of all the URLs present in the given HTML files or text files.

The "main.cpp" is the only file necessary for running the program, the rest of the files are just input files that can be given as input for the code, and sample images are also provided for better understanding.

The code will take a file with the extension (.html or .txt) as input and scans all the links present in the file and classifies the links into a referred link or not. If the link in Html code was present in "" this tag implies that the URL was referred not only mentioned.

_Referred links are those which are linked from the given HTML code._
_Note there can few links which are not referred to but only just mentioned in the given HTML code or file._

The code will generate an output text file with all the referred links that are scanned from the given input file.

The regex header file is used to run a regular expression in C++ for extracting URL links and unordered_maps for storing the extracted data.
