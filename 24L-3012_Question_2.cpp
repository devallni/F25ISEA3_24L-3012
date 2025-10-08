#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

/**
 * @brief Reads all words from a text file into a vector.
 *
 * The file should contain one word per line.
 *
 * @param filename The name of the text file.
 * @return A vector containing all words read from the file.
 */
vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file \"" << filename << "\".\n";
        exit(1);
    }

    while (getline(file, word)) {
        if (!word.empty())
            words.push_back(word);
    }

    file.close();
    return words;
}

/**
 * @brief Converts an uppercase English alphabet character to lowercase.
 *
 * @param ch The input character.
 * @return The lowercase version of the character, if applicable.
 */
char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch + ('a' - 'A');
    return ch;
}

/**
 * @brief Displays the current state of the guessed word.
 *
 * @param guessedWord A string showing correctly guessed letters and underscores for missing ones.
 */
void displayWord(const string& guessedWord) {
    for (char c : guessedWord)
        cout << c << ' ';
    cout << endl;
}

/**
 * @brief Checks if the guessed letter exists in the word and updates guessedWord.
 *
 * @param word The actual word to guess.
 * @param guessedWord The current visible progress of the word.
 * @param guess The guessed character.
 * @return true if the guess was correct, false otherwise.
 */
bool processGuess(const string& word, string& guessedWord, char guess) {
    bool found = false;
    for (size_t i = 0; i < word.length(); ++i) {
        if (toLower(word[i]) == guess) {
            guessedWord[i] = word[i];
            found = true;
        }
    }
    return found;
}

/**
 * @brief The main Hangman game loop.
 *
 * Randomly selects a word from a text file and allows the user to guess letters.
 * The player can make up to 7 mistakes before losing.
 *
 * @return int Exit status (0 for normal termination).
 */
int main() {
    srand(time(0));
    vector<string> words = loadWordsFromFile("words.txt");

    if (words.empty()) {
        cout << "No words found in the file.\n";
        return 0;
    }

    string word = words[rand() % words.size()];
    string guessedWord(word.length(), '_');
    int remainingMistakes = 7;
    vector<char> usedLetters;

    cout << "              HANGMAN GAME                 \n\n";
    cout << "You have 7 chances. Guess the letters!\n\n";

    while (remainingMistakes > 0 && guessedWord != word) {
        cout << "Word: ";
        displayWord(guessedWord);
        cout << "Used letters: ";
        for (char c : usedLetters) cout << c << ' ';
        cout << "\nRemaining mistakes: " << remainingMistakes << "\n";
        cout << "Enter a letter: ";

        char guess;
        cin >> guess;
        guess = toLower(guess);

        // check if already guessed
        bool alreadyUsed = false;
        for (char c : usedLetters)
            if (c == guess)
                alreadyUsed = true;

        if (alreadyUsed) {
            cout << "You already guessed that letter!\n\n";
            continue;
        }

        usedLetters.push_back(guess);

        if (processGuess(word, guessedWord, guess)) {
            cout << "Correct!\n\n";
        }
        else {
            remainingMistakes--;
            cout << "Wrong! Remaining mistakes: " << remainingMistakes << "\n\n";
        }
    }

    if (guessedWord == word) {
        cout << "Congratulations! You guessed the word: " << word << "\n";
    }
    else {
        cout << "Game over! The correct word was: " << word << "\n";
    }

    return 0;
}
