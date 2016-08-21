#pragma once

#include <string>

// Normalized sequence of space separated words in lower case.
// ToDo: there is no synactic way to ensure the sequence is actually noramlized
// ToDo: it might be more efficient to represent sequence of words as a 
// deque of strings and provide a proper hash for it
using WordsSequence = std::string;
