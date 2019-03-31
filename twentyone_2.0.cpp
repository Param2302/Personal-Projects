/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Param Patel
 * USC email: parampat@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

//bug-enter integar while exiting

//doubling down - where exactly in the game is option offered
//do you see dealer's first card or the second card?
//card counting
//blakcjack expert table

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <queue>
#include <string>

using namespace std;

struct card {

char suit;
string type;
int value;

};

class hand {

public:

  hand();
  void printHand();
  int getBestScore();
  deque<card> hand_cards;
  double bet;
  bool finished;

};

class player {

public:
  player();
  deque<hand> hands_vec;
  double account;
};

class deck {

public:

    deck();
    void shuffle();
    deque<card> deck_cards;

};

void player_plays(player&,player&, int , int , deck& );

deck::deck(){}

hand::hand(){}

void deck::shuffle(){

  //8 52-card decks shuffled

  int numDecks=8;

  deck_cards.resize(52*numDecks);

  for(int j=0; j<=(numDecks-1)*52; j=j+52)
  {
  for(int i=0; i<52; i++)
  {
    if(i<13)
    {deck_cards[i+j].suit='H';}
    else if(i<26)
    {deck_cards[i+j].suit='S';}
    else if(i<39)
    {deck_cards[i+j].suit='D';}
    else if(i<52)
    {deck_cards[i+j].suit='C';}

    if(i%13<=8)
    {
      deck_cards[i+j].type=to_string(2+i%13);
      deck_cards[i+j].value=i%13+2;
    }

    if(i%13==9)
    {
      deck_cards[i+j].type="J";
      deck_cards[i+j].value=10;
    }

    if(i%13==10)
    {
      deck_cards[i+j].type="Q";
      deck_cards[i+j].value=10;
    }

    if(i%13==11)
    {
      deck_cards[i+j].type="K";
      deck_cards[i+j].value=10;
    }

    if(i%13==12)
    {
      deck_cards[i+j].type="A";
      deck_cards[i+j].value=11;
    }

    }
  }

  for(int i=numDecks*52-1; i>0; i--)
  {
      int j=rand()%(i+1);
      card interim=deck_cards[j];
      deck_cards[j]=deck_cards[i];
      deck_cards[i]=interim;

  }

}

player::player(){}

void hand::printHand(){

for(int i=0; i<(int)hand_cards.size();i++)
{
  cout<<hand_cards[i].type<<"-"<<hand_cards[i].suit<<" ";
}
  cout<<endl;
}

int hand::getBestScore(){

  int total=0;
  for(int i=0; i<(int)hand_cards.size();i++)
  {
    total+=hand_cards[i].value;
  }
  return total;

}

void split(player& d,player& p, int player_number, int hand_number, deck& cards_deck)
{

    cout<< "Would Player "<<player_number<<" like to split?"<< endl;
    cout<<"Note that spiltting would duplicate original bet for each hand"<<endl;
    cout<<"Type 'y' to split and 'n' to continue with same hand:"<<endl;
    char split_choice;
    cin>>split_choice;

    while ((split_choice!='y'&&split_choice!='n')||(cin.fail()))
    {
      cout<<"Enter valid instruction"<<endl;
      cout<<"Type 'y' to split and 'n' to continue with same hand:"<<endl;
      cin.clear();
      cin.ignore(10000, '\n');
      cin>>split_choice;
      cout<<endl;
    }

    if(split_choice=='n')
    {return;}

      hand temp_hand;

      temp_hand.hand_cards.push_back(p.hands_vec[hand_number].hand_cards[1]);
      p.hands_vec[hand_number].hand_cards.pop_back();

      p.hands_vec[hand_number].hand_cards.push_back(cards_deck.deck_cards.front());
      cards_deck.deck_cards.pop_front();

      temp_hand.hand_cards.push_back(cards_deck.deck_cards.front());
      cards_deck.deck_cards.pop_front();

      p.hands_vec.push_back(temp_hand);
      p.hands_vec.back().bet=p.hands_vec[hand_number].bet;
      p.hands_vec.back().finished=false;

      player_plays(d, p, player_number, hand_number, cards_deck);
      player_plays(d, p, player_number, (int)p.hands_vec.size()-1, cards_deck);

      return;

}

void player_plays(player& d,player& p, int player_number, int hand_number, deck& cards_deck)
{

  cout<<endl<<"Player "<<player_number;
  if(p.hands_vec.size()>1){
                            cout<<" Hand "<<hand_number+1;
                          }
cout<<": ";

  p.hands_vec[hand_number].printHand();
  cout<<p.hands_vec[hand_number].getBestScore()<<endl;

  if (p.hands_vec[hand_number].getBestScore()==21)
  {
    cout<< "Player "<<player_number<<" gets Blackjack!";
    if(p.hands_vec.size()>1){cout<<" with Hand "<<hand_number+1;}
    cout<< endl;
    p.hands_vec[hand_number].finished=true;
    return;
  }

  if (p.hands_vec[hand_number].hand_cards[0].type==p.hands_vec[hand_number].hand_cards[1].type)
  {
    split(d,p,player_number,hand_number,cards_deck);
    return;
  }


cout<<"Type ";
if(p.hands_vec[hand_number].hand_cards.size()==2)
{cout<<"'d' to double your bet and hit, ";}
cout<<"'h' to hit and 's' to stay:"<<endl;

char hit_stay;

cin>> hit_stay;

      while ((hit_stay!='h'&&hit_stay!='s'&&hit_stay!='d')||(cin.fail()))
      {
        cout<<"Enter valid instruction"<<endl;
        cout<<"Type ";
        if(p.hands_vec[hand_number].hand_cards.size()==1)
        {cout<<"'d' to double your bet and hit, ";}
        cout<<"'h' to hit and 's' to stay:"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cin>>hit_stay;
        cout<<endl;
      }

      if(hit_stay=='s')
      {
        p.hands_vec[hand_number].finished=true;
        return;
      }

      if(hit_stay=='d')
      {
        p.hands_vec[hand_number].bet*=2;
      }

      p.hands_vec[hand_number].hand_cards.push_back(cards_deck.deck_cards.front());
      cards_deck.deck_cards.pop_front();

      cout<<endl<<"Player "<<player_number;
      if(p.hands_vec.size()>1){
                                cout<<" Hand "<<hand_number+1;
                              }
      cout<<": ";
      p.hands_vec[hand_number].printHand();

      if (p.hands_vec[hand_number].getBestScore()>21)
          {
          //same logic as in the case of the dealer
          //if value of cards go above 21, the hand
          //is checked for aces and the ace is considered
          //worth 1 if it is found
            for(int n=0;n<(int)p.hands_vec[hand_number].hand_cards.size();n++)
            {
                if(p.hands_vec[hand_number].hand_cards[n].value==11)
                {
                    p.hands_vec[hand_number].hand_cards[n].value=1;
                    break;
                }
            }
          }

      cout<<p.hands_vec[hand_number].getBestScore()<<endl;

       if (p.hands_vec[hand_number].getBestScore()>21)
       {
         if(p.hands_vec.size()>1){cout<<"Hand "<<hand_number+1<<" of ";}
          cout<< "Player "<<player_number<<" busts"<< endl;
          p.hands_vec[hand_number].finished=true;
          return;
      }

      if (p.hands_vec[hand_number].getBestScore()==21)
      {
        cout<< "Player "<<player_number<<" hits twenty-one";
        if(p.hands_vec.size()>1){cout<<" with Hand "<<hand_number+1;}
        cout<< endl;
        p.hands_vec[hand_number].finished=true;
        return;
      }

      return;

}

void players_play(player& d,vector<player*>& players_vec, deck& cards_deck)
{
  bool all_finished=false;

  while(all_finished==false)
  {
    all_finished=true;
    for(int i=0; i<(int)players_vec.size(); i++)
    {
      int initial_size=(int)players_vec[i]->hands_vec.size();
      for(int j=0; j<initial_size; j++)
      {
        if(players_vec[i]->hands_vec[j].finished==false)
        {
          player_plays(d, *players_vec[i], i+1, j, cards_deck);
        }
      }
      for(int j=0; j<initial_size; j++)
      {
          if(players_vec[i]->hands_vec[j].finished==false){all_finished=false;}
      }
    }
  }
}

void dealer_plays(player& d,vector<player*>& players_vec, deck& cards_deck)
{
while(d.hands_vec[0].getBestScore()<=16)
              {
                  d.hands_vec[0].hand_cards.push_back(cards_deck.deck_cards.front());
                  cards_deck.deck_cards.pop_front();

                  if (d.hands_vec[0].getBestScore()>21)
                  {
                    /*
                    checks if any cards are aces
                    */
                    for(int n=0;n<(int)d.hands_vec[0].hand_cards.size();n++)
                    {
                        if(d.hands_vec[0].hand_cards[n].value==11)
                        {
                            d.hands_vec[0].hand_cards[n].value=1;
                            break;
                        }
                    }

                  }


              }

              cout<<"Dealer: ";
              d.hands_vec[0].printHand();
              cout<<d.hands_vec[0].getBestScore()<<endl<<endl;

                  if (d.hands_vec[0].getBestScore()>21)
                  {
                      cout<< "Dealer busts "<<d.hands_vec[0].getBestScore()<<endl;

                      for(int i=0; i<(int)players_vec.size(); i++)
                      {
                        for(int j=0; j<(int)players_vec[i]->hands_vec.size(); j++)
                        {
                          if(players_vec[i]->hands_vec[j].getBestScore()<=21)
                          {
                            cout<<"Player "<<i+1<<" wins";
                            if(players_vec[i]->hands_vec.size()>1)
                            {
                              cout<<" with Hand "<<j+1;
                            }
                              cout<<" "<<players_vec[i]->hands_vec[j].getBestScore()<<endl;
                              players_vec[i]->account+=players_vec[i]->hands_vec[j].bet;
                          }
                          else
                          {
                            cout<<"Player "<<i+1<<" loses";
                            if(players_vec[i]->hands_vec.size()>1)
                            {
                              cout<<" with Hand "<<j+1;
                            }
                            cout<<" "<<players_vec[i]->hands_vec[j].getBestScore()<<endl;
                            players_vec[i]->account-=players_vec[i]->hands_vec[j].bet;
                          }
                        }
                      }


                    return;
                  }

                  for(int i=0; i<(int)players_vec.size(); i++)
                  {
                    for(int j=0; j<(int)players_vec[i]->hands_vec.size(); j++)
                    {
                      if(d.hands_vec[0].getBestScore()==players_vec[i]->hands_vec[j].getBestScore())
                      {cout<<"Player "<<i+1<<" ties";
                      if(players_vec[i]->hands_vec.size()>1)
                      {
                        cout<<" with Hand "<<j+1;
                      }
                      cout<<" "<<players_vec[i]->hands_vec[j].getBestScore()<<endl;}

                      if ((d.hands_vec[0].getBestScore()>players_vec[i]->hands_vec[j].getBestScore())||(21<players_vec[i]->hands_vec[j].getBestScore()))
                      {
                        cout<<"Player "<<i+1<<" loses";
                        if(players_vec[i]->hands_vec.size()>1)
                        {
                          cout<<" with Hand "<<j+1;
                        }
                        cout<<" "<<players_vec[i]->hands_vec[j].getBestScore()<<endl;
                        players_vec[i]->account-=players_vec[i]->hands_vec[j].bet;
                      }

                      if ((d.hands_vec[0].getBestScore()<players_vec[i]->hands_vec[j].getBestScore())&&(players_vec[i]->hands_vec[j].getBestScore()<=21))
                      {
                        cout<<"Player "<<i+1<<" wins";
                        if(players_vec[i]->hands_vec.size()>1)
                        {
                          cout<<" with Hand "<<j+1;
                        }
                        cout<<" "<<players_vec[i]->hands_vec[j].getBestScore()<<endl;
                        players_vec[i]->account+=players_vec[i]->hands_vec[j].bet;
                      }
                    }
                  }

}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(!(argc==1)){
    cout << "Error - Please enter correct arguments." << endl;
    return 1;
  }

  srand(time(0));

  int numPlayers;
  cout<<"Enter number of players"<<endl;
  cin>>numPlayers;
  cout<<endl;

  while(cin.fail()||numPlayers<1)
  {
    cout<<"Enter valid input"<<endl;
    cout<<"Enter number of players"<<endl;
    cin.clear();
    cin.ignore(10000, '\n');
    cin>>numPlayers;
    cout<<endl;
  }

  deck cards;
  player dealer;

  vector<player*> players;
  players.resize(numPlayers);
  dealer.hands_vec.resize(1);

  for(int i=0; i<numPlayers; i++)
  {
    players[i]=new player;
  }

  char repeat;
  while(1)
  {

   cards.shuffle();
   dealer.hands_vec[0].hand_cards.clear();

   for(int i=0; i<numPlayers; i++)
   {
     for(int j=0; j<(int)players[i]->hands_vec.size(); j++)
     {
       players[i]->hands_vec[j].hand_cards.clear();
       players[i]->hands_vec[j].finished=false;
     }
       players[i]->hands_vec.clear();
       players[i]->hands_vec.resize(1);
   }

   for(int i=0; i<numPlayers; i++)
   {
     cout<<"Enter bet for player "<<i+1<<endl;
     cin>>players[i]->hands_vec[0].bet;
     cout<<endl;

     while(cin.fail()||players[i]->hands_vec[0].bet<=0)
     {
       cout<<"Enter valid input as bet for player "<<i+1<<endl;
       cin.clear();
       cin.ignore(10000, '\n');
       cin>>players[i]->hands_vec[0].bet;
       cout<<endl;
     }
   }

   for(int i=0; i<numPlayers; i++)
   {
     players[i]->hands_vec[0].hand_cards.push_back(cards.deck_cards.front());
     cards.deck_cards.pop_front();
   }

   dealer.hands_vec[0].hand_cards.push_back(cards.deck_cards.front());
   cards.deck_cards.pop_front();

   for(int i=0; i<numPlayers; i++)
   {
     players[i]->hands_vec[0].hand_cards.push_back(cards.deck_cards.front());
     cards.deck_cards.pop_front();
   }

   dealer.hands_vec[0].hand_cards.push_back(cards.deck_cards.front());
   cards.deck_cards.pop_front();

   cout<<"Dealer: ? ";
       cout<< dealer.hands_vec[0].hand_cards[1].type<<"-"<<dealer.hands_vec[0].hand_cards[1].suit;
       cout<<endl<<endl;

       for(int i=0; i<numPlayers; i++)
       {
         cout<<"Player "<<i+1<<": ";
         players[i]->hands_vec[0].printHand();
         cout<<endl;
       }

       players_play(dealer,players,cards);
       cout<<endl;

          //dealer does not play if all players have busted
          bool all_bust=true;
          for(int i=0; i<numPlayers; i++)
          {
            for(int j=0; i<(int)players[i]->hands_vec.size(); j++)
            {
              if(players[i]->hands_vec[j].getBestScore()<=21)
              {all_bust=false; break;}
            }
          }
          if(all_bust==true)
          {
            cout<<"All players busted";
            for(int i=0; i<numPlayers; i++)
            {
              for(int j=0; i<(int)players[i]->hands_vec.size(); j++)
              {
                players[i]->account-=players[i]->hands_vec[j].bet;
              }
            }
          }
          else
            {
              dealer_plays(dealer, players, cards);
            }



  cout<< endl<< endl;
  cout<< "To view betting account records input 'a'"<<endl;
  cout<< "To play again input 'y'"<< endl;
  cout<< "To conclude game input anything else"<<endl;
  cin>> repeat;
  if(repeat=='y'){cout<<endl;continue;}
  if(repeat=='a')
  {
    cout<<endl<<"Betting account records for all players:"<<endl;
    for(int i=0; i<numPlayers; i++)
    {
      if(players[i]->account>0)
      {cout<<"Player "<<i+1<<": +"<<players[i]->account<<endl;}
      else
      {cout<<"Player "<<i+1<<": "<<players[i]->account<<endl;}
    }
    cout<<endl;

    cout<< "To play again input 'y'"<< endl;
    cout<< "To end game input anything else"<<endl;
    cin>> repeat;
    if(repeat=='y'){cout<<endl;continue;}
  }
  if((repeat!='y'&&repeat!='a')||(cin.fail()))
  {
    cout<<endl<<"If you are sure you want to end the game, input'e'"<<endl;
    cout<< "To continue game input anything else"<<endl;
    cin>> repeat;
    if(repeat!='e'){cout<<endl;continue;}
    else
    {
      cout<<endl<<"Final betting account records for all players:"<<endl;
      for(int i=0; i<numPlayers; i++)
      {
        if(players[i]->account>0)
        {cout<<"Player "<<i+1<<": +"<<players[i]->account<<endl;}
        else
        {cout<<"Player "<<i+1<<": "<<players[i]->account<<endl;}
      }
      cout<<endl<<endl;
      break;
    }
  }
  }

  for(int i=0; i<numPlayers; i++)
  {
    delete players[i];
  }

  return 0;
}
