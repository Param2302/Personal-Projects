/*
Betting element
Total score tally
Total betting result balance
Srand(time(0))
No. of players?
*/




#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;


/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

int dealer_wins;
int player_wins;
int Ties;

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  for(int i=0; i<52; i++)
  {
      cards[i]=i;
  }
  

  for(int i=51; i>0; i--)
  {
      int j=rand()%(i+1);
      int interim=cards[j];
      cards[j]=cards[i];
      cards[i]=interim;
      
  }


}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */

//id%13 results in an output where
//every thirteen cards in ascending order
// refer to 0 to 12

//id/13 results in an output where
//cards are divided into four quarters
//first 13 cards give 0
//second set of 13 cards give 1
//and so on

//id/16 is meant for aces whose values
//have been changed to 1
//explanation for the same 
//will be provided further

void printCard(int id)
{
 if (id<=51)
 {
  cout<< type[(id)%13]<< "-"<< suit[id/13];
 }
    else
    {
        cout<< type[(id/16)%13]<< "-"<< suit[(id/16)/13];
    }
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */

//aces whose value has been changed to 1
//have had their ids changed to over 51
//so this function simpy returns 1 for them
//change in id value occurs further

int cardValue(int id)
{
    if (id>51)
    {return 1;}
    else
    return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  for(int i=0;i<numCards;i++)
  {
      printCard(hand[i]);
      cout<<" ";
  }

    cout<<endl;

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int total_score=0;
  for(int i= 0; i<numCards; i++)
  {
      total_score=total_score+cardValue(hand[i]);
  }
    return total_score;
}

//this large set of instructions would be used mutliple
//times so making a function for the same was ideal
//this refers to when the player either has a hand
//worth 21 or the player has decided to stay
//after which the dealer keeps playing until
//the dealer's hand is worth at least 17


void dealer_plays(int dhand[9],int dhand_size,int phand[9],
                  int phand_size,int cards[52],int card_counter)
{ 
while(getBestScore(dhand,dhand_size)<17)
              {
                  dhand[dhand_size]=cards[card_counter];
                  card_counter++;
                  dhand_size++;

                  if (getBestScore(dhand,dhand_size)>21)
                  {
                    /*
                    checks if any cards are aces
                    and if they are, it multiplies 
                    the id of that particular card by an arbitrary
                    number, in this case 16
                    so that this new id number is always more than 51
                    which allows printCard and cardValue functions
                    to distinguish between aces with value reduced to 1
                    and aces with value as 11
                    */ 
                    for(int n=0;n<dhand_size;n++)
                    {
                        if
                            (dhand[n]==12||dhand[n]==25
                             ||dhand[n]==38||dhand[n]==51)
                        {
                            dhand[n]=dhand[n]*16;
                            break;
                        }
                    }
                  }   
                  

              }
                  if (getBestScore(dhand,dhand_size)>21)
                  {  /* cout<<"Dealer: ";
                      printHand(dhand,dhand_size);
                      cout<< "Dealer busts"<< endl;
                      cout<< "Win "<< getBestScore(phand,phand_size)<< " ";
                      cout<< getBestScore(dhand,dhand_size);
                      */
                      player_wins++;

                  }

                      if (getBestScore(dhand,dhand_size)
                               ==getBestScore(phand,phand_size)&&getBestScore(phand,phand_size)<=21)
                      {  /* cout<<"Dealer: ";
                          printHand(dhand,dhand_size);
                          cout<< "Tie "<< getBestScore(phand,phand_size)<< " ";
                          cout<< getBestScore(dhand,dhand_size);
                          */
                           Ties++;
                      }

                    //additional and operator to ensure 
                    //the function is not executed even when
                    //dealer is busted
                   if (getBestScore(dhand,dhand_size)
                       >getBestScore(phand,phand_size)
                       &&getBestScore(dhand,dhand_size)
                       <=21)
                          {
                            /* cout<<"Dealer: ";
                             printHand(dhand,dhand_size);
                             cout<<"Lose "<<getBestScore(phand,phand_size)<<" ";
                             cout<< getBestScore(dhand,dhand_size);
                             */
                               dealer_wins++;
                          }
                   if (getBestScore(dhand,dhand_size)
                       <getBestScore(phand,phand_size)&&getBestScore(phand,phand_size)<=21)
                           {
                             /* cout<<"Dealer: ";
                              printHand(dhand,dhand_size);
                              cout<<"Win "<<getBestScore(phand,phand_size)<<" ";
                              cout<< getBestScore(dhand,dhand_size);
                              */
                           player_wins++;
                           }

}





/**
 * Main program logic for the game of 21
 */
int main()
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  
  srand(time(0));
    
  int num_sim;
  int num_game;
  int sim_counter=0;
  double player_win_result=0;
  double dealer_win_result=0;
  double Ties_result=0;
    
  cout<< "How many games must be played?"<<endl;
  cin>> num_game;
  cout<< "Hom many simulations must be done?"<<endl;
  cin>> num_sim;

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  //do while loop because body of loop
  //has to be executed at least once

  for(int cond=1;cond<=21;cond++)
  {
  player_win_result=0;
  dealer_win_result=0;
  Ties_result=0;
    
  for(int s=0;s<num_sim;s++)
  {
      player_wins=0;
      dealer_wins=0;
      Ties=0;
      sim_counter=0;
  do
  {
   bool already_21=false;
   sim_counter++;
   shuffle(cards);
      
   //cards are distributed in alternating order
   //with the player given the first card
      
   phand[0]=cards[0];
   dhand[0]=cards[1];
   phand[1]=cards[2];
   dhand[1]=cards[3];   
      
      int card_counter=4;    
      //keeps check on which card is to be distributed next
      int phand_size=2;      
      //keeps check on number of cards with player
      int dhand_size=2;      
      //keeps check on number of cards with dealer
    /*
   cout<<"Dealer: ? ";
       printCard(dhand[1]);
       cout<<endl;
   cout<<"Player: ";
       printHand(phand,phand_size);
      */
      //if player already has cards worth 21
      //dealer must begin playing
      
      if (getBestScore(phand,phand_size)==21)
      {
          dealer_plays(dhand,dhand_size,phand,
                       phand_size,cards,card_counter);
          already_21=true;
      }
      
      //only if player's cards are not worth 21
      //does the player get the option
      //to hit or to stay
      
      else
      {
      /*
   cout<<"Type 'h' to hit and 's' to stay:"<<endl;
      
   char hit_stay;
      
   cin>> hit_stay;
          
          if (hit_stay!='h'&&hit_stay!='s')
          {
              return 0;
          }
      */
      while (getBestScore(phand,phand_size)<cond)
      {
          phand[phand_size]=cards[card_counter];
          card_counter++;
          phand_size++;
          /*
          cout<<"Player: ";
          printHand(phand,phand_size);
          */
          if (getBestScore(phand,phand_size)>21)
              {
              //same logic as in the case of the dealer
              //if value of cards go above 21, the hand
              //is checked for aces and the ace is considered
              //worth 1 if it is found
                for(int n=0;n<phand_size;n++)
                {
                    if(phand[n]==12||phand[n]==25
                       ||phand[n]==38||phand[n]==51)
                    {
                        phand[n]=phand[n]*16;
                        break;
                    }
                }
              }   
          
          //if value of cards is 21 or above
          //while loop is exited
          //otherwise player continues to get
          //option to hit or to stay
          
           if (getBestScore(phand,phand_size)>21)   
           {           
              /*cout<< "Player busts"<< endl;
              cout<< "Lose "<< getBestScore(phand, phand_size)<< " ";
              cout<< getBestScore(dhand, dhand_size);
              */
              dealer_wins++;
              
              break;
          }
          
         
          /*
          else
          {
              cout<<"Type 'h' to hit and 's' to stay:"<<endl;
              cin>> hit_stay;
              if (hit_stay!='h'&&hit_stay!='s')
          {
              return 0;
          }
              */
          }
          
         
          
      }
          //dealer does not play if player has busted
          if (getBestScore(phand,phand_size)<=21&&already_21==false)
            {
              dealer_plays(dhand,dhand_size,phand,
                           phand_size,cards,card_counter);
              
            }
      
      

  }
  while (sim_counter<num_game);


    player_win_result=player_win_result+((double)player_wins/(double)num_game*100);
    dealer_win_result=dealer_win_result+((double)dealer_wins/(double)num_game*100);
    Ties_result=Ties_result+((double)Ties/(double)num_game*100);
    
    
}
    double player_percentage=player_win_result/num_sim;
    double dealer_percentage=dealer_win_result/num_sim;
    double Ties_percentage=Ties_result/num_sim;
   
   
    cout<< "Percentage of total wins in favour of player when player hits until ";
     cout<< cond;
      cout<<" is "<<endl;
   cout<<player_percentage/(dealer_percentage+player_percentage)*100<<endl<<endl;
      
   cout<< "Player win percentage is "<< player_percentage<<endl;
   cout<< "Dealer win percentage is "<< dealer_percentage<< endl;
   cout<< "Tie percentage is "<< Ties_percentage<< endl<<endl;
   //cout<< "Percentage of total wins in favour of player ";
   //cout<<player_percentage/(dealer_percentage+player_percentage)*100<<endl<<endl;
    
      
  }  
    return 0;
}
