#include <iostream>
#include <fstream>  // used to read file
#include <string>   // to use string functions
#include <iomanip>  // used for formatting output

using namespace std;

// GLOBAL CONSTANT VARIABLES
const int NUMBER_OF_BOWLERS = 10;   // change according to how many players are in the file.
const int GAME_ROUNDS = 5;          // change according to how many scores per player are in the file.

// STRUCTURE TO STORE BOWLER DATA
struct BowlerData
{
    string bowlerName;
    int bowlerScores[GAME_ROUNDS];
    int bowlerScoreAvg;
};

// FUNCTION PROTOTYPES - anything that won't be modified will be passed as constant.
void welcomeMessage();
// initialize all member variables to default values(i.e., "Name" and 0's)
void initialize(BowlerData bowlers[]);
// read file data into an array of the structure
bool GetBowlingData(const string FILE_NAME, BowlerData bowlers[]);
// calculate the avg score for each bowler
void GetAverageScore(BowlerData bowlers[]);
// finds the highest score avg
void BowlerHighestAverage(const BowlerData bowlers[]);
// output result in a formated table
void PrettyPrintResults(const BowlerData bowlers[]);

// MAIN
int main()
{
    // An array of instance's of bowlerData for each bowler in the file
    BowlerData bowlers[NUMBER_OF_BOWLERS];

    // CONSTANT VARIABLE - change the file name here
    const string FILE_NAME = "BowlingScores.txt";

    // CALL FUNCTIONS
    initialize(bowlers);
    welcomeMessage();

    bool isDataStored;
    isDataStored = GetBowlingData(FILE_NAME, bowlers);  // returns true or false.
    
    if (isDataStored)
    {
        GetAverageScore(bowlers);
        PrettyPrintResults(bowlers);
        BowlerHighestAverage(bowlers);
    }
    else
    {
        cout << " [!] Existing program...\n" << endl;
        system("pause");
        return 1;
    }

    cout << endl;
    system("pause");
    return 0;
}
// WELCOME MESSAGE
void welcomeMessage()
{
    const string TITLE = " BOWLING LEAGUE ";
    // The welcome message length will always fit according
    // to how many games(scores per player) are there.
    const int LENGTH = 18 + (12 * GAME_ROUNDS) + 8;
    const int HALF_LENGTH = (LENGTH - TITLE.length()) / 2;
    const char SYMBOLE = '=';
    // Output program header 
    cout << '\n' << setfill(SYMBOLE) << setw(LENGTH) << '\n';
    cout << setw(HALF_LENGTH) << "" << TITLE << setw(HALF_LENGTH) << '\n';
    cout << setw(LENGTH) << '\n' << setfill(' ') << endl;
}
// INITIALIZE - A function to initialize all member variables to default values(i.e., "Name" and 0's)
void initialize(BowlerData bowlers[])
{
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        bowlers[i].bowlerName = "Bowler " + to_string(i + 1);
        for (int j = 0; j < GAME_ROUNDS; j++)
        {
            bowlers[i].bowlerScores[j] = 0;
        }
        bowlers[i].bowlerScoreAvg = 0;
    }
}
// READ AND STORE DATA INTO AN ARRAY OF STRUCTURES
bool GetBowlingData(const string FILE_NAME, BowlerData bowlers[])
{
    ifstream inFile;
    inFile.open(FILE_NAME.c_str());

    if (!inFile)
    {
        cout << " [!] ERROR: Can't open file name \"" << FILE_NAME << "\"" << endl;
        return false;
    }
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        inFile >> bowlers[i].bowlerName;

        for (int j = 0; j < GAME_ROUNDS; j++)
            inFile >> bowlers[i].bowlerScores[j];
    }
    inFile.close();

    return true;
}
// CALCULATE THE AVERAGE BOWLING SCORE
void GetAverageScore(BowlerData bowlers[])
{
    int sum = 0;
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        for (int j = 0; j < GAME_ROUNDS; j++)
            sum = sum + bowlers[i].bowlerScores[j];

        bowlers[i].bowlerScoreAvg = sum / GAME_ROUNDS;

        sum = 0;
    }
}
// HIGHEST AVERAGE
void BowlerHighestAverage(const BowlerData bowlers[])
{
    int highestIndex = 0;
    // Iterates through each average bowler score, compare the highestIndex
    // value to the first element and update the highestIndex, repeat until
    // the end of the array.
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
        if (bowlers[i].bowlerScoreAvg > bowlers[highestIndex].bowlerScoreAvg)
            highestIndex = i;
    // Output
    cout << " [+] " << bowlers[highestIndex].bowlerName << " had the highest score average: " << bowlers[highestIndex].bowlerScoreAvg << endl;
}
// OUTPUT RESULTS
void PrettyPrintResults(const BowlerData bowlers[])
{
    // Initialize variables - Modify table formatting here
    const string NAME_HEADER = "NAME";
    const string GAME_HEADERS = "GAME";
    const string AVERAGE_HEADER = "AVERAGE";

    const int S_WIDTH = 12;              // width of scores rows 
    const int N_WIDTH2 = S_WIDTH - 1;    // width of name rows

    // A very flexible line separator will always fit according to the table's rows.
    // If there are more or fewer GAME_ROUNDS(rows), the line will always fit accordingly.
    const string LINE_SEPARATOR = ' ' + string(N_WIDTH2 + (S_WIDTH * GAME_ROUNDS) + S_WIDTH, '-');

    // ROW HEADERS - print formated row header (NAME - GAME 1 ... GAME N - AVERAGE) 
    cout << " " << left << setw(N_WIDTH2) << NAME_HEADER;
    for (int i = 0; i < GAME_ROUNDS; i++)
        cout << right << setw(S_WIDTH) << GAME_HEADERS + ' ' + to_string(i + 1);
    cout << right << setw(S_WIDTH) << AVERAGE_HEADER << endl;

    cout << LINE_SEPARATOR << endl;
    // FILL ROWS AND COLUMNS
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        // prints the names of bowlers to the first column
        cout << " " << left << setw(N_WIDTH2) << bowlers[i].bowlerName;
        // prints the scores of each bowler
        for (int j = 0; j < GAME_ROUNDS; j++)
            cout << right << setw(S_WIDTH) << bowlers[i].bowlerScores[j];
        // prints the average score of each bowler
        cout << right << setw(S_WIDTH) << bowlers[i].bowlerScoreAvg << endl;
    }
    cout << LINE_SEPARATOR << endl;
}