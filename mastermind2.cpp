#include <iostream>
#include <string>

using namespace std;

/*string getInput(const string &question) {
    string input;
    cout << question;
    cin.ignore();
    getline(cin, input);
    return input;
}*/

bool isValidGame(const string &game) {
    if (game.length() != 4) {
        return false;
    }

    string ValidColors = "RGBPYM";
    for (int i = 0; i < 4; ++i) {
        if (ValidColors.find(game[i]) == string::npos) {
            return false;
        }
        for (int j = i + 1; j < 4; ++j) {
            if (game[i] == game[j]) {
                return false;
            }
        }
    }
    return true;
}

string calcFeedback(const string &secretGame, const string &guessGame) {
    string feedback;
    for (int i = 0; i < 4; i++) {
        if (secretGame[i] == guessGame[i]) {
            feedback = feedback + 'R';
        } else if (secretGame.find(guessGame[i]) != string::npos) {
            feedback = feedback + 'W';
        }
    }
    return feedback;
}

int main() {
    string p1, p2;
    cout << "Please enter the names of the players: ";
    cin >> p1 >> p2;
    cout << "Welcome " << p1 << " and " << p2 << endl;
    cout << endl;

    int run_nums;
    do {
        cout << "Please enter the number of runs: ";
        cin >> run_nums;
        if (run_nums <= 0 || run_nums % 2 != 0) {
            cout << "Invalid number of runs!" << endl;
        }
    } while (run_nums <= 0 || run_nums % 2 != 0);

    int p1score = 0, p2score = 0;

    for (int run = 1; run <= run_nums; run++) {
        string secretGame, guessGame;
        string code_maker, code_breaker;
        if (run % 2 != 0) {
            code_maker = p1;
            code_breaker = p2;
        } else {
            code_maker = p2;
            code_breaker = p1;
        }
        cout << code_maker << ", it is your turn to select the secret!" << endl;
        cout << "Valid colors: R - Red, G - Green, B - Blue, P - Purple, Y - Yellow, M - Magenta \n";
        do{
              cout << code_maker << ", please enter your secret: ";
            cin>> secretGame;
        	//secretGame = getInput("Valid colors: R - Red, G - Green, B - Blue, P - Purple, Y - Yellow, M - Magenta \n" + code_maker + ", please enter your secret: ");
        	if(!isValidGame(secretGame)){
        		cout<<"Invalid secret!"<<endl;
			}
		  }while (!isValidGame(secretGame));

        for (int chance = 1; chance <= 6; chance++) {
            cout << code_breaker << ", please enter your guess: ";

            bool validGuess = false;
            do {
            	cin>>guessGame;
                //guessGame = getInput("");
                if (!isValidGame(guessGame)) {
                    cout << "Invalid guess! "<<endl;
                    cout<<code_breaker<<" , please enter your guess:";
                } else {
                    validGuess = true;
                }
            } while (!validGuess);

            if (secretGame == guessGame) {
                cout << code_breaker << ", you won this run!" << endl;
                if (code_breaker == p1) {
                    ++p1score;
                } else {
                    ++p2score;
                }
                break;
            } else {
                string feedback = calcFeedback(secretGame, guessGame);
                cout << feedback << endl;
                if (chance == 6) {
                    cout << code_breaker << ", you're out of chances, you lost this run!" << endl;
                    if (code_maker == p1) {
                        ++p1score;
                    } else {
                        ++p2score;
                    }
                }
            }
        }
    }

    cout << "The game has ended!" << endl;
    cout << p1 << ": " << p1score << "-" << p2 << ": " << p2score << endl;

    if (p1score == p2score) {
        cout << p1 << " and " << p2 << ", there is a tie!" << endl;
    } else {
        if (p1score > p2score) {
            cout << "Congrats " << p1 << ", you have won the game!" << endl;
        } else {
            cout << "Congrats " << p2 << ", you have won the game!" << endl;
        }
    }
    return 0;
}

