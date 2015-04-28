#include "Chess.h"
#include <string>
#include <iostream>
#include <queue>
using namespace std;
Chess::Chess()
{
/*
Function prototype:
Chess::Chess()

Function description:
This just sets the private variables, beginning and ending, equal to NULL

Example:

Chess* NewGame = new Chess();
NewGame->newSpace(std::string)

*/
    beginning = NULL;
    ending = NULL;
    //cout<<"made constructor"<<endl;
}

Chess::~Chess()
{
    //there is no destructor
}

boardSpace* Chess::newSpace(std::string placement)
{
    /*
Function prototype:
Chess::newSpace(std::string)

Function description:
The newSpace function takes in a board spot indicator and creates a new boardSpace struct. It also initializes all the pointers to the other spots to NULL.

Example:
boardSpace* temp = NewGame->newSpace(std::string)



*/

    boardSpace* newSpot = new boardSpace;
    newSpot->boardSpot = placement;
    newSpot->name = "_";
    newSpot->occupied = false;
    newSpot->team = "NULL";
    newSpot->up = NULL;
    newSpot->down = NULL;
    newSpot->left = NULL;
    newSpot->right = NULL;
    newSpot->upLeft = NULL;
    newSpot->upRight = NULL;
    newSpot->downLeft = NULL;
    newSpot->downRight = NULL;
    //this returns the new struct
    return newSpot;
}

/* createBoard function

Function Prototype:
void Chess::createBoard(std::string, std::string);

Function Description:
This method is written to illustrate all possible moves that a pawn can make. The function allows
pawns to move one space forward (at all times) and attack on diagonal moves.

Example:
string team1 = "Zach";
string team2 = "Blaine";
Chess *NewGame = new Chess();
NewGame->createBoard(team1, team2);

Pre-condition: This function requires two pre-conditions to be met. Both are the names of the teams that will
be playing. This will also be used to set each one of the chess pieces to one of the teams.
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the pawn will either have moved forward one space or it will
attack an enemy piece in a diagonal move. Pointers and struct attributes will be updated after each successive
move.
*/
void Chess::createBoard(std::string Team1, std::string Team2)
{

    int index = 2;
    beginning = newSpace("0");
    ending = newSpace("65");
    boardSpace* temp = new boardSpace;
    temp = newSpace("a1");
    beginning->right = temp;
    temp->left = beginning;
    boardSpace* temp2 = new boardSpace;
    for(int j = 2; j < 65; j++)
    {
        if(2 <= index && index <= 8)
        {
            std::string b =std::to_string(j);
            temp2 = newSpace("a"+b);
        }
        if(9 <= index && index <= 16)
        {
            std::string b =std::to_string(j-8);
            temp2 = newSpace("b"+b);
        }
        if(17 <= index && index <= 24)
        {
            std::string b =std::to_string(j-16);
            temp2 = newSpace("c"+b);
        }
        if(25 <= index && index <= 32)
        {
            std::string b =std::to_string(j-24);
            temp2 = newSpace("d"+b);
        }
        if(33 <= index && index <= 40)
        {
            std::string b =std::to_string(j-32);
            temp2 = newSpace("e"+b);
        }
        if(41 <= index && index <= 48)
        {
            std::string b =std::to_string(j-40);
            temp2 = newSpace("f"+b);
        }
        if(49 <= index && index <= 56)
        {
            std::string b =std::to_string(j-48);
            temp2 = newSpace("g"+b);
        }
        if(57 <= index && index <= 64)
        {
            std::string b =std::to_string(j-56);
            temp2 = newSpace("h"+b);
        }
        index++;
        temp->right = temp2;
        temp2->left = temp;
        temp = temp2;
    }
    temp->right = ending;
    ending->left = temp;
    boardSpace* temp3 = beginning->right;
    boardSpace* DOWN = beginning->right;
    boardSpace* DOWNRIGHT = new boardSpace;
    boardSpace* DOWNLEFT = new boardSpace;

    //set up the down left, down right, and down spots;

    while(DOWN->boardSpot != "b1")
    {
        DOWN = DOWN->right;
    }
    DOWNLEFT = DOWN->left;
    DOWNRIGHT = DOWN->right;
    while(temp3->boardSpot != "h1")
    {
        //cout<<1<<endl;
        temp3->down = DOWN;
        if(temp3->boardSpot != "a8" && temp3->boardSpot != "b8" && temp3->boardSpot != "c8" && temp3->boardSpot != "d8" &&
           temp3->boardSpot != "e8" && temp3->boardSpot != "f8" && temp3->boardSpot != "g8")
        {
            temp3->downRight = DOWNRIGHT;
        }
        if(temp3->boardSpot != "a1" && temp3->boardSpot != "b1" && temp3->boardSpot != "c1" && temp3->boardSpot != "d1" &&
           temp3->boardSpot != "e1" && temp3->boardSpot != "f1" && temp3->boardSpot != "g1")
        {
            temp3->downLeft = DOWNLEFT;
        }
        temp3 = temp3->right;
        DOWN = DOWN->right;
        DOWNRIGHT= DOWNRIGHT->right;
        DOWNLEFT = DOWNLEFT->right;
    }

    //setup of up right, up left, and up

    temp3 = beginning->right;
    while(temp3->boardSpot != "b1")
    {
        temp3 = temp3->right;
    }
    boardSpace* UP = beginning->right;
    boardSpace* UPRIGHT = UP->right;
    boardSpace* UPLEFT = UP->left;

    while(temp3->boardSpot != "65")
    {
        temp3->up = UP;
        if(temp3->boardSpot != "h8" && temp3->boardSpot != "b8" && temp3->boardSpot != "c8" && temp3->boardSpot != "d8" &&
           temp3->boardSpot != "e8" && temp3->boardSpot != "f8" && temp3->boardSpot != "g8")
        {
            temp3->upRight = UPRIGHT;
        }
        if(temp3->boardSpot != "h1" && temp3->boardSpot != "b1" && temp3->boardSpot != "c1" && temp3->boardSpot != "d1" &&
           temp3->boardSpot != "e1" && temp3->boardSpot != "f1" && temp3->boardSpot != "g1")
        {
            temp3->upLeft = UPLEFT;
        }
        temp3 = temp3->right;
        UP = UP->right;
        UPRIGHT= UPRIGHT->right;
        UPLEFT = UPLEFT->right;
    }
    //set the horizontal boarders
    temp = beginning->right;
    temp = temp->down;
    while(temp != NULL)
    {
        temp->left = NULL;
        temp = temp->down;
    }
    temp = ending->left;
    temp = temp->up;
    while(temp != NULL)
    {
        temp->right = NULL;
        temp = temp->up;
    }

    //set Team 2 pieces
    temp = beginning->right;
    while(temp != NULL)
    {
        temp->team = Team2;
        temp->occupied = true;
        if(temp->boardSpot == "a1" || temp->boardSpot == "a8")
        {
            temp->name = "R";
        }
        if(temp->boardSpot == "a2" || temp->boardSpot == "a7")
        {
            temp->name = "N";
        }
        if(temp->boardSpot == "a3" || temp->boardSpot == "a6")
        {
            temp->name = "B";
            temp->team = Team2;
        }
        if(temp->boardSpot == "a4")
        {
            temp->name = "Q";
            temp->team = Team2;
        }
        if(temp->boardSpot == "a5")
        {
            temp->name = "K";
            temp->team = Team2;
        }
        temp = temp->right;
    }
    //set Team 2 pawns
    temp = beginning->right->down;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team2;
        temp->name = "P";
        temp = temp->right;
    }

    //set Team 1 pieces
    temp = ending->left;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team1;
        if(temp->boardSpot == "h1" || temp->boardSpot == "h8")
        {
            temp->name = "5";
        }
        if(temp->boardSpot == "h2" || temp->boardSpot == "h7")
        {
            temp->name = "6";
        }
        if(temp->boardSpot == "h3" || temp->boardSpot == "h6")
        {
            temp->name = "7";
        }
        if(temp->boardSpot == "h4")
        {
            temp->name = "8";
        }
        if(temp->boardSpot == "h5")
        {
            temp->name = "9";
        }
        temp = temp->left;
    }
    //set Team 1 pawns
    temp = ending->left->up;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team1;
        temp->name = "1";
        temp = temp->left;
    }



}

void Chess::team1Board(std::string Team1, std::string Team2)
{

    /*
    The team1Board function prints out the board so that the Pieces for Team 1 are at the bottom; as to simulate
    the viewpoint of someone playing an actual game of chess.
    */
    cout<<endl<<"K & 9 = King, Q & 8 = Queen, B & 7 = Bishop"<<endl;
    cout<<"N & 6 = Knight, R & 5 = Rook, P & 1 = Pawn"<<endl<<endl;;
    //cout<<"in queue"<<endl;
    std::queue<boardSpace*> T1;
    std::queue<string> Letters;
    std::queue<int> Numbers;
    Letters.push("a");
    Letters.push("a");
    Letters.push("b");
    Letters.push("b");
    Letters.push("c");
    Letters.push("c");
    Letters.push("d");
    Letters.push("d");
    Letters.push("e");
    Letters.push("e");
    Letters.push("f");
    Letters.push("f");
    Letters.push("g");
    Letters.push("g");
    Letters.push("h");
    Letters.push("h");
    for(int h = 1; h < 9; h++)
    {
        Numbers.push(h);
    }
    for(int h = 1; h < 9; h++)
    {
        Numbers.push(h);
    }
    cout<<"             Team2: "<<Team2<<endl;
    boardSpace *temp = beginning->right;
    int j = 0;
    cout<<"        ";//A
    cout<<"    ";
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }
    cout<<"        ";//A
    cout<<"    "<<endl;
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    while(temp != NULL)
    {
        //cout<<2<<endl;
        T1.push(temp);
        temp = temp->down;
    }
    while(!T1.empty())
    {
        //cout<<"in queue"<<endl;
        cout<<"        ";//A
        boardSpace *X = T1.front();
        cout<<Letters.front()<<" |";
        Letters.pop();
        //cout<<"something"<<endl;
        T1.pop();
        while(X != NULL && X != ending)
        {
            cout<<" "<<X->name;
            X = X->right;
        }
        cout<<" ";
        cout<<"| "<<Letters.front()<<endl;
        Letters.pop();
    }
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    cout<<"    ";
    cout<<"        ";//A
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }
    cout<<"    "<<endl;
    cout<<"             Team1: "<<Team1<<endl;
}

void Chess::team2Board(std::string Team1, std::string Team2)
{
    /*
    The team1Board function prints out the board so that the Pieces for Team 1 are at the bottom; as to simulate
    the viewpoint of someone playing an actual game of chess.
    */
    cout<<endl<<"K & 9 = King, Q & 8 = Queen, B & 7 = Bishop"<<endl;
    cout<<"N & 6 = Knight, R & 5 = Rook, P & 1 = Pawn"<<endl<<endl;;
    //cout<<"in queue"<<endl;
    std::queue<boardSpace*> T1;
    std::queue<string> Letters;
    std::queue<int> Numbers;
    Letters.push("h");
    Letters.push("h");
    Letters.push("g");
    Letters.push("g");
    Letters.push("f");
    Letters.push("f");
    Letters.push("e");
    Letters.push("e");
    Letters.push("d");
    Letters.push("d");
    Letters.push("c");
    Letters.push("c");
    Letters.push("b");
    Letters.push("b");
    Letters.push("a");
    Letters.push("a");
    for(int h = 8; h > 0; h--)
    {
        Numbers.push(h);
    }
    for(int h = 8; h > 0; h--)
    {
        Numbers.push(h);
    }
    cout<<"             Team1: "<<Team1<<endl;
    boardSpace *temp = ending->left;
    int j = 0;
    cout<<"        ";//A
    cout<<"    ";
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }
    cout<<"        ";//A
    cout<<"    "<<endl;
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    while(temp != NULL)
    {
        //cout<<2<<endl;
        T1.push(temp);
        temp = temp->up;
    }
    while(!T1.empty())
    {
        //cout<<"in queue"<<endl;
        cout<<"        ";//A
        boardSpace *X = T1.front();
        cout<<Letters.front()<<" |";
        Letters.pop();
        //cout<<"something"<<endl;
        T1.pop();
        while(X != NULL && X != beginning)
        {
            cout<<" "<<X->name;
            X = X->left;
        }
        cout<<" ";
        cout<<"| "<<Letters.front()<<endl;
        Letters.pop();
    }
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    cout<<"    ";
    cout<<"        ";//A
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }
    cout<<"    "<<endl;
    cout<<"             Team2: "<<Team2<<endl;
}

/* createBoard function

Function Prototype:
void Chess::createBoard(std::string, std::string);

Function Description:
This method is written to illustrate all possible moves that a pawn can make. The function allows
pawns to move one space forward (at all times) and attack on diagonal moves.

Example:
string team1 = "Zach";
string team2 = "Blaine";
Chess *NewGame = new Chess();
NewGame->createBoard(team1, team2);

Pre-condition: This function requires two pre-conditions to be met. Both are the names of the teams that will
be playing. This will also be used to set each one of the chess pieces to one of the teams.
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the pawn will either have moved forward one space or it will
attack an enemy piece in a diagonal move. Pointers and struct attributes will be updated after each successive
move.
*/

void Chess::PlayerTurn(std::string Team1, std::string Team2)
{
    /*
        ZACH
    */
    int teamCounter = 1;
    std::string Winner;
    std::string answer;
    while(teamCounter != 3)
    {
        if(teamCounter == 1)
        {
            bool turnIsOver = false;
            while(turnIsOver == false)
            {
            team1Board(Team1,Team2);
            cout<<endl<<"It is "<<Team1<<"'s turn."<<endl;
            cout<<"What piece do you want to move: ";
            cin >> ws;
            getline(cin, answer);
            //cout<<SearchSpot(answer)->team<<endl;
            boardSpace* temp = SearchSpot(answer);

            //cout<<temp->name<<" "<<temp->team<<" "<<temp->occupied<<endl;
            if(temp != NULL && temp->occupied != false && temp->team  == Team1)
            {
                if(temp->name == "1")
                {
                    //cout<<"Pawn"<<endl;

                    turnIsOver = Pawn(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "5")
                {
                    //cout<<"Rook"<<endl;

                    turnIsOver = Rook(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "6")
                {
                    turnIsOver = Knight(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "7")
                {
                    turnIsOver = Bishop(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "8")
                {
                    turnIsOver = Queen(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "9")
                {
                    turnIsOver = King(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else
                {
                    cout<<"Not a valid choice!"<<endl<<"What piece do you want to move: ";
                }

            }
            }

        }
        if(teamCounter == 3)
        {
            Winner = Team1;
            break;
        }
        if(teamCounter == 2)
        {
            bool turnIsOver = false;
            while(turnIsOver == false)
            {
            team2Board(Team1,Team2);
            cout<<endl<<"It is "<<Team2<<"'s turn."<<endl;
            cout<<"What piece do you want to move: ";
            cin >> ws;
            getline(cin, answer);
            boardSpace* temp = SearchSpot(answer);
            if(temp != NULL && temp->occupied != false && temp->team  == Team2)
            {
                if(temp->name == "P")
                {
                    turnIsOver =Pawn(Team2, temp, 2);

                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "R")
                {
                    turnIsOver = Rook(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "N")
                {
                    turnIsOver = Knight(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "B")
                {
                    turnIsOver = Bishop(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "Q")
                {
                    turnIsOver = Queen(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "K")
                {
                    turnIsOver = King(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else
                {
                    cout<<"Not a valid choice!"<<endl<<"What piece do you want to move: ";
                }
            }
            }

        }
        if(teamCounter == 3)
        {
            Winner = Team2;
            break;
        }

    }
    cout<<"The Winner is "<<Winner<<"!";
}

/* SearchSpot Comment Block
Function Prototype:
boardSpace* Chess::SearchSpot(std::string SPOT);

Function Description:
This function is written to search through the board and find the piece that the player wants to move. It will pass this board space
into the appropriate piece function.

Example:
Chess *NewGame = new Chess();
NewGame->SearchSpot(b1);

Pre-condition: This function requires one pre-condition. It will take in the string of the spot where the player piece resides.However,
as with most of our functions it requires that the beginning and ending pointers be set to NULL. This is done in the constructor.

Post-condition: Once this function has run through, the function will return the boardSpace of the spot where the player piece resides.
It will pass this boardSpace into the piece function of the player's choosing and proceed with the appropriate moves.
*/
boardSpace* Chess::SearchSpot(std::string SPOT)
{
    //Initialize checkers.
    std::string tempWord;
    bool theEnd = false;

    boardSpace* temp = beginning->right;

    //Start the search process
    while(temp != NULL)
    {
        tempWord = temp->boardSpot;

        //Check the first character of the input.
        if(SPOT[0] == tempWord[0])
        {
            while(temp != NULL)
            {
                //If you have found the spot, return it.
                if(temp->boardSpot == SPOT)
                {
                    return temp;
                }
                //Otherwise keep moving right.
                else
                {
                    temp = temp->right;
                }
            }
            //Set the bool if it was not found.
            if(temp == NULL)
            {
                theEnd = true;
            }
        }

        //Jump out of the while loop and tell the user that the space was not found.
        if(theEnd == true)
        {
            break;
        }
        else
        {
            temp = temp->down;
        }
    }
    cout<<"Invalid Space"<<endl;
    //Return the space. To be used later.
    return temp;
}

/* checkForKing Comment Block
Function Prototype:
bool Chess::checkForKing(std::string KING);

Function Description:
This function is written to search through the board and see if there is a king still on the board who belong's to the opposite team. If there
is a king on the board, then the game will proceed. However, if a king is not found on the board, then the game will end and declare the
appropriate winner. This is essentially the check mate function.

Example:
Chess *NewGame = new Chess();
NewGame->checkForKing(K);

Pre-condition: This function requires one pre-condition. It will take in the string, which will be the first character of the piece that the
player chooses to move. As with most of our functions, it requires that the beginning and ending pointers be set to NULL. This is done
in the constructor.

Post-condition: Once this function has run through, the function will return a bool that says whether or not the opposite team's king is on
the board. It will pass this bool into the player turn function which will determine if the game should end on that player's turn or not.
*/
bool Chess::checkForKing(std::string KING)
{
    //Set initializers.
    bool found = false;
    boardSpace*temp = beginning->right;
    queue<boardSpace*> A;

    //Search down the board while pushing onto the queue.
    while(temp != NULL)
    {
        A.push(temp);
        temp = temp->down;
    }

    //Search inside the queue to see if the King is found. If not, keep searching.
    while(!A.empty())
    {
        boardSpace *X = A.front();
        A.pop();

        while(X != NULL && X != ending)
        {
            if(X->name == KING)
            {
                found = true;
                break;
            }
            else
            {
                X = X->right;
            }
        }

        if(found == true)
        {
            break;
        }
    }

    //Return the resulting bool.
    return found;
}
bool Chess::Pawn(std::string Team, boardSpace* currentSpace , int teamCount)
{

}
/* Rook Piece function

Function Prototype:
void Chess::createBoard(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Rook can move. The function checks the preset pointers
of left, right, up, and down for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Rook(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Rook(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upClear = false;
    bool rightClear = false;
    bool leftClear = false;
    bool downClear = false;

    bool turnComplete = true;
    //for team 1 check the available spots
    if(teamCount == 1)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->left != NULL && currentSpace->left != beginning)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->right != NULL && currentSpace->right != ending)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                downClear = true;
            }
        }
        if(upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        //cout available moves
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" ⇐,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or ⇓.";
        }
        cout<<endl<<"Press";
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or 2 for ⇓.";
        }
        //takes in direction
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        //takes in number of spaces
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->left != NULL && currentSpace->left != beginning)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->right != NULL && currentSpace->right != ending)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        if(upClear == false && downClear == false && rightClear == false && leftClear == false )
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" ⇐,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or ⇓.";
        }
        cout<<endl<<"Press";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or 2 for ⇓.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
bool Chess::Knight(std::string Team, boardSpace* currentSpace , int teamCount)
{

}
/* Bishop Piece function

Function Prototype:
void Chess::Bishop(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Bishop can move. The function checks the preset pointers
of upleft, upright, downright, and downleft for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Bishop(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Bishop(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upRightClear = false;
    bool upLeftClear = false;
    bool downRightClear = false;
    bool downLeftClear = false;

    bool turnComplete = true;

    if(teamCount == 1)
    {
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Bishop?"<<endl;

        cout<<"You may move";
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }
        cout<<endl<<"Press";
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }
        cout<<endl<<"Press";
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

}
/* Queen Piece function

Function Prototype:
void Chess::Queen(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Queen can move. The function checks the preset pointers
of left, upleft, up, upright,right, downright, down, and downleft for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Queen(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Queen(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upRightClear = false;
    bool upLeftClear = false;
    bool downRightClear = false;
    bool downLeftClear = false;
    bool upClear = false;
    bool rightClear = false;
    bool leftClear = false;
    bool downClear = false;

    bool turnComplete = true;

    if(teamCount == 1)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false
           && upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Queen?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        cout<<endl<<"Press";

        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false
           && upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true&& currentSpace->right != ending)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        cout<<endl<<"Press";

        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
bool Chess::King(std::string Team, boardSpace* currentSpace , int teamCount)
{

}

/* Pawn Switch Out function

Function Prototype:
void Chess::PawnSwitchOut(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function is activated when a pawn of team A reaches the end of tean B's side. This allows team A to change their
pawn to a Queen, Bishop, Rook, or Knight.

Example:

NewGame->PawnSwitchOut(team1, (a5)spot, 1);

Pre-condition:
We need to know the pawns team name, the spot that it has reached, and the team number.

Post-condition: The piece will become the chosen piece
*/
void Chess::PawnSwitchOut(boardSpace* pawnSpot,std::string Team1, int teamCount)
{
    //ZACH
    char X = pawnSpot->boardSpot[0];
    //if it has reached the a row or the h row.
    if((X == 'a' && teamCount == 1) || (X == 'h' && teamCount == 2))
    {
        cout<<endl<<"You made a pawn to the other end!"<<endl;
        cout<<"What do you want to change your pawn too?"<<endl;
        bool changed = false;
        while(changed == false)
        {
            cout<<"Press 1 for Queen, 2 for Bishop, 3 for Knight, 4 for Rook"<<endl;
            string input;
            cin>>ws;
            getline(cin, input);
            int Input = stoi(input);
            if(teamCount == 1)
            {
                if(Input == 1)
                {
                    pawnSpot->name = "8";
                    changed = true;
                }
                if(Input == 2)
                {
                    pawnSpot->name = "7";
                    changed = true;
                }
                if(Input == 3)
                {
                    pawnSpot->name = "6";
                    changed = true;
                }
                if(Input == 4)
                {
                    pawnSpot->name = "5";
                    changed = true;
                }
                if(changed != true)
                {
                    cout<<"Not a valid option."<<endl;
                }
            }
            else if(teamCount == 2)
            {
                if(Input == 1)
                {
                    pawnSpot->name = "Q";
                    changed = true;
                }
                if(Input == 2)
                {
                    pawnSpot->name = "B";
                    changed = true;
                }
                if(Input == 3)
                {
                    pawnSpot->name = "N";
                    changed = true;
                }
                if(Input == 4)
                {
                    pawnSpot->name = "R";
                    changed = true;
                }
                if(changed != true)
                {
                    cout<<"Not a valid option."<<endl;
                }
            }


        }
    }
}
