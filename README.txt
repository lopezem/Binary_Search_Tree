	The purpose of the project is to read from an input text file, and for every word 

that was in the text file, each individual word was printed out into another output

text file with the word in the first column and the line number in which it occurred

in the following columns (i.e. the	3	5	7, which means “the” was 

repeated in lines 3, 5, and 7). The way to implement such an algorithm, is by 

utilizing a binary search tree. A binary search tree is a linked list in which there 

is a root node and on the left side of the root node (its left child node) the value 

of it is less than the root node. The right side of the root node (its right child node) 

the value of it is greater than the root node, and so on and so forth. In the case of 

the given text file, the binary search tree was to be implemented in such a way that 

the first word of the text file was to be the root node (in given sample case it was 

“set”) and was to be sorted into a binary tree alphabetically.