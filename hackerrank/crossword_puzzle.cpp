#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int N = 10;

struct Direction {
    int h;
    int v;
    Direction(int h, int v) : h(h), v(v) {}
    Direction invert() const {
        return Direction(-h, -v);
    }
    Direction flip() const {
        return Direction(v, h);
    }
};

struct Position {
    int row;
    int column;
    Position(int row, int column)
        : row(row), column(column) {}
    Position operator+(const Direction& direction) const {
        return Position(row + direction.v, column + direction.h);
    }
    bool inbounds() const {
        if (row >= 0 && row < N) {
            if (column >= 0 && column < N) {
                return true;
            }
        }
        return false;
    }
};

struct Location {
    Position position;
    Direction direction;
    unsigned int size;
    Location(const Position& position, const Direction& direction, unsigned int size)
        : position(position), direction(direction), size(size) {}
};


bool hasOther(const Position& currPos, const Direction& currDir, const vector<string>& crossword) {
    const Direction flipped = currDir.flip();
    const Position pos1 = currPos + flipped;
    const Position pos2 = currPos + flipped.invert();
    if (pos1.inbounds() && crossword[pos1.row][pos1.column] == '-') return true;
    if (pos2.inbounds() && crossword[pos2.row][pos2.column] == '-') return true;
    return false;
}

char& at(vector<string>& crossword, const Position& position) {
    return crossword[position.row][position.column];
}

bool put(vector<string>& cross, vector<Location>& locations, vector<string>& words, unsigned int currWordIndex) {
    if (currWordIndex >= words.size()) return true;
    const string& currWord = words[currWordIndex];
    for (unsigned int locationIndex = 0; locationIndex < locations.size(); locationIndex++) {
        if (locations[locationIndex].size != currWord.size()) continue;

        // try put
        const Location& currLocation = locations[locationIndex];
        vector<Position> placedPositions;
        Position currPosition = currLocation.position;
        bool placementSuccessful = true;
        for (char c : currWord) {
            char& crossLetter = at(cross, currPosition);
            if (crossLetter == '*') {
                crossLetter = c;
                placedPositions.push_back(currPosition);
            } else if (crossLetter == c) { // other's letter => just skip
            } else {
                // logic error (not '*') or taken by another unfit letter
                // unput
                for (auto& position : placedPositions) at(cross, position) = '*';
                placementSuccessful = false;
                break;
            }
            currPosition = currPosition + currLocation.direction;
        }
        if (!placementSuccessful) continue;

        if (put(cross, locations, words, currWordIndex + 1)) return true;

        // No luck at this place => unput
        for (auto& position : placedPositions) at(cross, position) = '*';
    }
    return false;
}


vector<string> crosswordPuzzle(vector<string>& crossword, const string& words_unsplit) {
    vector<Location> locations;
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int column = 0; column < N; column++) {
            if (crossword[row][column] == '-') {
                /* std::cout << "Found at " << row << " " << column << std::endl; */
                const Direction currDir = [&](){
                    if (row < N - 1 && crossword[row + 1][column] == '-') {
                        return Direction(0, +1);
                    } else {
                        return Direction(+1, 0);
                    }
                }();
                Position currPos(row, column);
                unsigned int size = 0;
                while (currPos.inbounds() && at(crossword, currPos) == '-') {
                    size++;
                    if (!hasOther(currPos, currDir, crossword)) {
                        at(crossword, currPos) = '*'; // taken
                        /* std::cout << "     marked " << std::endl; */
                    }
                    currPos = currPos + currDir;
                }
                locations.emplace_back(Position(row, column), currDir, size); // starting Position
            }
        }
    }

    vector<string> words;
    {
        unsigned int last = 0;
        unsigned int i = 0;
        while (i != words_unsplit.size()) {
            if (words_unsplit[i] == ';') {
                words.push_back(words_unsplit.substr(last, i - last));
                last = i + 1;
            }
            i++;
        }
        words.push_back(words_unsplit.substr(last, i - last));
    }

    put(crossword, locations, words, 0);
    return crossword;
}

int main() {
    std::vector<std::string> crossword;
    crossword.emplace_back("+-++++++++");
    crossword.emplace_back("+-++-+++++");
    crossword.emplace_back("+-------++");
    crossword.emplace_back("+-++-+++++");
    crossword.emplace_back("+-++-+++++");
    crossword.emplace_back("+-++-+++++");
    crossword.emplace_back("++++-+++++");
    crossword.emplace_back("++++-+++++");
    crossword.emplace_back("++++++++++");
    crossword.emplace_back("----------");
    std::string words("CALIFORNIA;NIGERIA;CANADA;TELAVIV");
    for (auto& str : crosswordPuzzle(crossword, words)) {
        std::cout << str << std::endl;
    }
}
