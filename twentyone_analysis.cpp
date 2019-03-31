/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Param Patel
 * USC email: parampat@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

//betting strategies (doubling in losses)
//card counting
//blakcjack expert table

// Add other #includes if you need
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

class player {

public:

  player();
  void printHand();
  int getBestScore();
  deque<card> hand_cards;
  double account;
  double bet;
  bool finished;

};

class deck {

public:

    deck();
    void shuffle();
    deque<card> deck_cards;

};

deck::deck(){}

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

void player::printHand(){

for(int i=0; i<(int)hand_cards.size();i++)
{
  cout<<hand_cards[i].type<<"-"<<hand_cards[i].suit<<" ";
}
  cout<<endl;
}

int player::getBestScore(){

  int total=0;
  for(int i=0; i<(int)hand_cards.size();i++)
  {
    total+=hand_cards[i].value;
  }
  return total;

}

void player_plays(player& d,player& p, int player_number, deck& cards_deck)
{
/*
  cout<<endl<<"Player "<<player_number<<": ";
  p.printHand();
  cout<<p.getBestScore()<<endl;
*/
  if (p.getBestScore()==21)
  {
    //cout<< "Player "<<player_number<<" gets Blackjack!"<< endl;
    p.finished=true;
    return;
  }

//cout<<"Type 'h' to hit and 's' to stay:"<<endl;

//char hit_stay='h';

//cin>> hit_stay;
/*
      while (hit_stay!='h'&&hit_stay!='s')
      {
        cout<<"Enter valid instruction"<<endl;
        cout<<"Type 'h' to hit and 's' to stay:"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cin>>hit_stay;
        cout<<endl;
      }

      if(hit_stay=='s')
      {
        p.finished=true;
        return;
      }
*/
    while (p.getBestScore()<15)
    {

      p.hand_cards.push_back(cards_deck.deck_cards.front());
      cards_deck.deck_cards.pop_front();

      //cout<<endl<<"Player "<<player_number<<": ";
    //  p.printHand();

      if (p.getBestScore()>21)
          {
          //same logic as in the case of the dealer
          //if value of cards go above 21, the hand
          //is checked for aces and the ace is considered
          //worth 1 if it is found
            for(int n=0;n<(int)p.hand_cards.size();n++)
            {
                if(p.hand_cards[n].value==11)
                {
                    p.hand_cards[n].value=1;
                    break;
                }
            }
          }

        }


        //temp
        p.finished=true;
        //

      //cout<<p.getBestScore()<<endl;

       if (p.getBestScore()>21)
       {
          //cout<< "Player "<<player_number<<" busts"<< endl;
          p.finished=true;
          return;
      }

      if (p.getBestScore()==21)
      {
        //cout<< "Player "<<player_number<<" hits twenty-one"<< endl;
        p.finished=true;
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
      if(players_vec[i]->finished==false)
      {
        player_plays(d, *players_vec[i], i+1, cards_deck);
        if(players_vec[i]->finished==false){all_finished=false;}
      }

    }
  }
}

void dealer_plays(player& d,vector<player*>& players_vec, deck& cards_deck, double& betting_value, double& base_bet, double& max_bet)
{
while(d.getBestScore()<=16)
              {
                  d.hand_cards.push_back(cards_deck.deck_cards.front());
                  cards_deck.deck_cards.pop_front();

                  if (d.getBestScore()>21)
                  {
                    /*
                    checks if any cards are aces
                    */
                    for(int n=0;n<(int)d.hand_cards.size();n++)
                    {
                        if(d.hand_cards[n].value==11)
                        {
                            d.hand_cards[n].value=1;
                            break;
                        }
                    }

                  }


              }

              //cout<<"Dealer: ";
              //d.printHand();
              //cout<<d.getBestScore()<<endl<<endl;

                  if (d.getBestScore()>21)
                  {
                      //cout<< "Dealer busts "<<d.getBestScore()<<endl;

                      for(int i=0; i<(int)players_vec.size(); i++)
                      {
                        if((*players_vec[i]).getBestScore()<=21)
                        {//cout<<"Player "<<i+1<<" wins "<<(*players_vec[i]).getBestScore()<<endl;
                          players_vec[i]->account+=players_vec[i]->bet;
                          betting_value=base_bet;
                        }
                        else
                        {//cout<<"Player "<<i+1<<" loses "<<(*players_vec[i]).getBestScore()<<endl;
                          players_vec[i]->account-=players_vec[i]->bet;
                          betting_value*=2;
                          if(betting_value>max_bet){max_bet=betting_value;}
                        }
                      }


                    return;
                  }

                  for(int i=0; i<(int)players_vec.size(); i++)
                  {
                    //if(d.getBestScore()==(*players_vec[i]).getBestScore())
                    //{cout<<"Player "<<i+1<<" ties "<<(*players_vec[i]).getBestScore()<<endl;}

                    if ((d.getBestScore()>(*players_vec[i]).getBestScore())||(21<(*players_vec[i]).getBestScore()))
                    {//cout<<"Player "<<i+1<<" loses "<<(*players_vec[i]).getBestScore()<<endl;
                      players_vec[i]->account-=players_vec[i]->bet;
                      betting_value*=2;
                      if(betting_value>max_bet){max_bet=betting_value;}
                    }

                    if ((d.getBestScore()<(*players_vec[i]).getBestScore())&&((*players_vec[i]).getBestScore()<=21))
                    {//cout<<"Player "<<i+1<<" wins "<<(*players_vec[i]).getBestScore()<<endl;
                      players_vec[i]->account+=players_vec[i]->bet;
                      betting_value=base_bet;
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

  double base_bet=5;
  int numGames=100;

  double betting_value=base_bet;
  double max_bet=0;

  int numPlayers;
  numPlayers=1;

  /*
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
  */
  deck cards;
  player dealer;

  vector<player*> players;
  players.resize(numPlayers);

  for(int i=0; i<numPlayers; i++)
  {
    players[i]=new player;
  }

  //char repeat;
  for(int j=0; j<numGames; j++)
  {
   cards.shuffle();
   dealer.hand_cards.clear();

   for(int i=0; i<numPlayers; i++)
   {
     (*players[i]).hand_cards.clear();
     players[i]->finished=false;
   }

   for(int i=0; i<numPlayers; i++)
   {
     /*
     cout<<"Enter bet for player "<<i+1<<endl;
     cin>>players[i]->bet;
     cout<<endl;

     while(cin.fail()||players[i]->bet<=0)
     {
       cout<<"Enter valid input as bet for player "<<i+1<<endl;
       cin.clear();
       cin.ignore(10000, '\n');
       cin>>players[i]->bet;
       cout<<endl;
     }
     */
     players[i]->bet=betting_value;
   }

   for(int i=0; i<numPlayers; i++)
   {
     (*players[i]).hand_cards.push_back(cards.deck_cards.front());
     cards.deck_cards.pop_front();
   }

   dealer.hand_cards.push_back(cards.deck_cards.front());
   cards.deck_cards.pop_front();

   for(int i=0; i<numPlayers; i++)
   {
     (*players[i]).hand_cards.push_back(cards.deck_cards.front());
     cards.deck_cards.pop_front();
   }

   dealer.hand_cards.push_back(cards.deck_cards.front());
   cards.deck_cards.pop_front();
/*
   cout<<"Dealer: ? ";
       cout<< dealer.hand_cards[1].type<<"-"<<dealer.hand_cards[1].suit;
       cout<<endl<<endl;

       for(int i=0; i<numPlayers; i++)
       {
         cout<<"Player "<<i+1<<": ";
         (*players[i]).printHand();
         cout<<endl;
       }
*/
       players_play(dealer,players,cards);
  //     cout<<endl;

          //dealer does not play if all players have busted
          bool all_bust=true;
          for(int i=0; i<numPlayers; i++)
          {
            if((*players[i]).getBestScore()<=21)
            {all_bust=false; break;}
          }
          if(all_bust==true)
          {
            //cout<<"All players busted";
            for(int i=0; i<numPlayers; i++)
            {
              players[i]->account-=players[i]->bet;
              betting_value*=2;
              if(betting_value>max_bet){max_bet=betting_value;}
            }
          }
          else
            {
              dealer_plays(dealer, players, cards, betting_value, base_bet, max_bet);
            }


/*
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
    cout<< "To conclude game input anything else"<<endl;
    cin>> repeat;
    if(repeat=='y'){cout<<endl;continue;}
  }
  if((repeat!='y'&&repeat!='a')||(cin.fail()))
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
  */
  }

  cout<<endl<<"Final betting account records for all players:"<<endl;
  for(int i=0; i<numPlayers; i++)
  {
    if(players[i]->account>0)
    {cout<<"Player "<<i+1<<": +"<<players[i]->account<<endl;}
    else
    {cout<<"Player "<<i+1<<": "<<players[i]->account<<endl;}
  }
  cout<<"Maximum bet: "<<max_bet;
  cout<<endl<<endl;

  for(int i=0; i<numPlayers; i++)
  {
    delete players[i];
  }

  return 0;
}
