#include <iostream>
#include <windows.h>
#include <vector>
#include <random>

using namespace std;

int cards[4][13] = {
                    {1,2,3,4,5,6,7,8,9,10,10,10,10},
                    {1,2,3,4,5,6,7,8,9,10,10,10,10},
                    {1,2,3,4,5,6,7,8,9,10,10,10,10},
                    {1,2,3,4,5,6,7,8,9,10,10,10,10}
                };
int player_count=0;
int npc_count=0;
int npc_cards[999];
int player_cards[999];
int game_sum=0;
int check_sum=0;

void npc_draw() {
   srand(time(NULL));
    int x_axis, y_axis;
    bool allowed=false;
    y_axis=rand()%4;
    x_axis=rand()%13;
     while (allowed==false) {
        if (cards[y_axis][x_axis]!=0) {
            allowed=true;
        }
        else {
            y_axis=rand()%4;
            x_axis=rand()%13;
        }
    }
    npc_cards[npc_count]=cards[y_axis][x_axis];
    npc_count++;
    cards[y_axis][x_axis]=0;
}

void player_draw() {
    srand(time(NULL));
    int x_axis, y_axis;
    bool allowed=false;
    y_axis=rand()%4;
    x_axis=rand()%13;
    while (allowed==false) {
        if (cards[y_axis][x_axis]!=0) {
            allowed=true;
        }
        else {
            y_axis=rand()%4;
            x_axis=rand()%13;
        }
    }
    player_cards[player_count]=cards[y_axis][x_axis];
    player_count++;
    cards[y_axis][x_axis]=0;
    cout << "The current cards you have are : ";
    for (int i=0; i<player_count; i++) {
        cout << player_cards[i] << " ";
    }
    cout << endl;
}

void check_num() {
    cout << "NPC's cards are : ";
    for (int i=0; i<npc_count; i++) {
        cout << npc_cards[i] << " ";
    }
    cout << endl;
    cout << "NPC : " << game_sum << endl;
    cout << "You : " << check_sum << endl;
    if ((game_sum>check_sum && game_sum<=21) || (game_sum<check_sum && game_sum>21) || (game_sum<=21 && check_sum>21)) {
        cout << "NPC wins!";
    }
    else if ((check_sum>game_sum && check_sum<=21) || (check_sum<game_sum && check_sum>21) || (check_sum<=21 && game_sum>21)) {
        cout << "You win!";
    }
    else if (check_sum==game_sum) {
        cout << "It's a draw!";
    }
}

void check_npc() {
    game_sum=0;
    for (int i=0; i<npc_count; i++) {
        game_sum=game_sum+npc_cards[i];
        if ((npc_cards[i]==1 && 21-game_sum>=10) && (game_sum<21)) {
            game_sum=game_sum+10;
        }
    }
}

void CheckNPC21() {
    for (int i=0; i<npc_count; i++) {
        if (npc_cards[i]==1 && game_sum>21) {
            game_sum=game_sum-10;
            break;
        }
    }
}

void CheckPlayer21() {
    for (int i=0; i<player_count; i++) {
        if (player_cards[i]==1 && check_sum>21) {
            check_sum=check_sum-10;
            break;
        }
    }
}

void CheckPlayerSum() {
    check_sum=0;
    for (int i=0; i<player_count; i++) {
        check_sum=check_sum+player_cards[i];
        if ((player_cards[i]==1 && 21-check_sum>=10) && (check_sum<21)) {
            check_sum=check_sum+10;
        }
    }
}

int main() {
    srand(time(NULL));
    string choice, game_choice="Draw";
    bool npc_choice=false, npc_stat=false;
    cout << "Welcome to 21! Would you like to play (Yes/No)? ";
    cin >> choice;
    if (choice=="Yes") {
        while (npc_stat==false) {
            npc_draw();
            check_npc();
            CheckNPC21();
            if (game_sum>=17) {
                npc_stat=true;
            }
        }
        while (game_choice=="Draw") {
            player_draw();
            CheckPlayerSum();
            CheckPlayer21();
            if (check_sum>=21) {
                break;
            }
            cout << "Do you want to draw or stand (Draw/Stand)? ";
            cin >> game_choice;
            Sleep(1500);
        }
        check_num();
    }
    else if (choice=="No") {
        cout << "You're welcome to play at any moment!";
    }
            return 0;
}