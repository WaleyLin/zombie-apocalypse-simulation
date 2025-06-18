
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <time.h>
using namespace std;

//function which includes what happens in the beginning of the apocalypse
void start_of_apocalypse(int **array_zombie, char **array_states, int random_i, int random_j, int width, int height){
  random_i = (rand() % width); // create a random coord to place a zombie
  random_j = (rand() % height);
  cout << "Zombie of strength 5 spawned at coordinate (" << random_i << ", " << random_j << ")" << endl;
  array_zombie[random_i][random_j] = 5; // set the zombie to 5 power and a normal zombie
  array_states[random_i][random_j] = '#';
  cout << "The apocalypse has started!" << endl;
  cout << "\n";
  cout << " . = Human" << endl
       << " * = Infected" << endl
       << " # = Bitey Zombie" << endl
       << " O = Berserker Zombie" << endl;
  cout << "\n";
  cout << "Day: 0" << endl;
  cout << "Number of Zombies: 1" << endl;
}
//function to print when either zombie or humans reach the MAX population
void end_of_apocalypse(int result){
  if (result == 1){
    cout << "=====================" << endl;
    cout << "Humans have survived!" << endl;
    cout << "====================="<< endl;
  }
  else if(result == 0){
    cout << "========================"<< endl;
    cout << "Zombies have taken over!" << endl;
    cout << "========================"<< endl;
  }
else{
  cout << "============================================================================================================================================================="<< endl;
  cout << "After 10,000 days, humans realize they will have to constantly live with the fear of zombies infecting them, but until then, there are still some humans left" << endl;
  cout << "============================================================================================================================================================="<< endl;
}
}
//function that prints map when called
void print_map(char **array_states, int width, int height){
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      cout << array_states[i][j] << " ";
    }
    cout << endl;
  }
}
//function that generates a random number and if the number is higher than bite chance, return the power of zombie, else return 0 which makes them a human
int bite(int zombie_strength, float p_of_bite){
  float random = (double)rand() / (double)RAND_MAX;
  float bite_chance = zombie_strength;
  bite_chance = bite_chance * p_of_bite;
  bite_chance = bite_chance / 10;
  float power = 0;
  if (random < bite_chance){ // bite is successful, return power
    if (random < .1){//if the random is less than .1 it will return power as a 0 therefore for just this case, we will round to 1 power instead of 0.
      random = .1;
    }
    power = floor(random * 10);
    return power;
  }
  else{ // if the bite is unsuccessful, return 0
    return 0;
  }
}
// Use this function to determine if a zombie is going to be a Bitey Zombie or a Berserk Zombie.
bool is_berserker(float p_of_berserk){ 
  float random = (double)rand() / (double)RAND_MAX;
  if (random <= p_of_berserk){//if random number generated is higher than p_berserk than they are berserk
    return true; // Return true if the trial passes,
  }
  else{//else they are just a normal
    return false; // and false if trial fails
  }
}
int run(int** a1, char** a2, int** a3, int width, int height, float p_of_bite, float p_of_berserk, int zombies, int humans, int iterations, int MAX, int max_strength_of_zombie){
    // create a loop to run until either everyone is either zombie or human
    while (zombies < MAX && humans < MAX && iterations < 10000){
    cout << "Day: ";
    cout << iterations << endl;
    iterations++;
    // start the apocalypse
    for (int i = 0; i < width; i++){
      for (int j = 0; j < height; j++){
        if (a2[i][j] == '*'){ // infected
          if (a3[i][j] == 0){
            bool temp = is_berserker(p_of_berserk);
            if (temp == true){
              a2[i][j] = 'O';
              zombies++;
              //cout << "* to O " << endl;
            }
            else if (temp == false){
              a2[i][j] = '#'; // else if becomes a normal zombie
              //cout << "* to #" << endl;
              zombies++;
            }
          }
          else{
            a3[i][j] = 0;
          }
        }
        else if (a2[i][j] == '#'){ // zombie
          int length = 0;
          int neighbor_x[4] = {0, 0, 0, 0};//create two arrays to hold the x and y of a human that is next to zombie
          int neighbor_y[4] = {0, 0, 0, 0};
          if ((i + 1) >= 0 && j >= 0 && i + 1 <= width - 1 && j <= height - 1){ // east
            if (a2[i + 1][j] == '.' && a2[i + 1][j] != '#'){
              neighbor_x[length] = (i + 1);
              neighbor_y[length] = j;
              length++;
            }
          }
          if (i >= 0 && (j + 1) >= 0 && i < width - 1 && j + 1 <= height - 1){ // south
            if (a2[i][j + 1] == '.' && a2[i][j + 1] != '*' && a2[i][j + 1] != '#' && a2[i][j + 1] != 'O'){
              neighbor_x[length] = i;
              neighbor_y[length] = (j + 1);
              length++;
            }
          }
          if ((i - 1) >= 0 && j >= 0 && i - 1 <= width - 1 && j <= height - 1){ // west
            if (a2[i - 1][j] == '.'){
              neighbor_x[length] = i - 1;
              neighbor_y[length] = j;
              length++;
            }
          }
          if (i >= 0 && (j - 1) >= 0 && i <= width - 1 && j - 1 <= height - 1){ // north
            if (a2[i][j - 1] == '.'){
              neighbor_x[length] = i;
              neighbor_y[length] = j - 1;
              length++;
            }
          }
          if (length != 0){//if everyone is a zombie dont run the rest
            int randomNumber = (rand() % length); //generate a random number to pick a random human
            int victim_x = neighbor_x[randomNumber];//set the human to the respected x and y
            int victim_y = neighbor_y[randomNumber];

            int strength = a1[i][j];
            int power = bite(strength, p_of_bite);//when the bite function returns and its above 0 that means that the victim is not a zombie
            if (power > 0){//set victim strengh to power and make infected
              a1[victim_x][victim_y] = power;
              a2[victim_x][victim_y] = '*';
              a3[victim_x][victim_y] = 1;
              humans--;
            } // else it means the power was 0 and so it was not successful.
            
          }
        }
        else if (a2[i][j] == 'O'){ // berserker
          int length = 0;
          int neighbor_x[4] = {0, 0, 0, 0};//create two arrays to hold the x and y of a human that is next to zombie
          int neighbor_y[4] = {0, 0, 0, 0};
          if ((i + 1) >= 0 && j >= 0 && i + 1 <= width - 1 && j <= height - 1){ // east
            if (a2[i + 1][j] == '.' && a2[i + 1][j] != '#'){
              neighbor_x[length] = (i + 1);
              neighbor_y[length] = j;
              length++;
            }
          }
          if (i >= 0 && (j + 1) >= 0 && i < width - 1 && j + 1 <= height - 1){ // south
            if (a2[i][j + 1] == '.' && a2[i][j + 1] != '*' && a2[i][j + 1] != '#' && a2[i][j + 1] != 'O'){
              neighbor_x[length] = i;
              neighbor_y[length] = (j + 1);
              length++;
            }
          }
          if ((i - 1) >= 0 && j >= 0 && i - 1 <= width - 1 && j <= height - 1){ // west
            if (a2[i - 1][j] == '.'){
              neighbor_x[length] = i - 1;
              neighbor_y[length] = j;
              length++;
            }
          }
          if (i >= 0 && (j - 1) >= 0 && i <= width - 1 && j - 1 <= height - 1){ // north
            if (a2[i][j - 1] == '.'){
              neighbor_x[length] = i;
              neighbor_y[length] = j - 1;
              length++;
            }
          }
          if (length != 0){//if everyone is a zombie dont run the rest
            if (length == 4){
              (length = 3);//100% of the time, there will only be 3 humans around a berserker zombie and it will never be 4
            }//so it will just bite everyone around them basically
            for(int w = 0; w < length; w++){
            int victim_x = neighbor_x[w];//set the human to the respected x and y
            int victim_y = neighbor_y[w];

            int strength = a1[i][j];
            int power = bite(strength, p_of_bite);//when the bite function returns and its above 0 that means that the victim is not a zombie
            if (power > 0){//set victim strengh to power and make infected
              a1[victim_x][victim_y] = power;
              a2[victim_x][victim_y] = '*';
              a3[victim_x][victim_y] = 1;
              humans--;
            }
            } // else it means the power was 0 and so it was not successful.
          }
        } // closes berserker
      }   // closes j loop
    }     // closes i loop
    // end of the day
    for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      if (a2[i][j] != '.' && a2[i][j] != '*'){
        a1[i][j] += 1; // increase power
            if (a1[i][j] >= max_strength_of_zombie){ // if strength = 10, set to human
              a2[i][j] = '.';
              a1[i][j] = 0;
              //cout << "# to ." << endl;
              humans++;
              zombies--;
            }
      }
      a3[i][j] = 0;
    }
  }
    cout << "Number of Zombies: ";
    cout << zombies << endl;
    print_map(a2, width, height);
    cout << "\n";
  }
  if(iterations < 9999){
    if (zombies > humans){
    return 0;
  }
  else{
    return 1;
  }
  }
  else {
    return 3;
  }
}
int main(int argc, char **argv){
  srand(time(0));//generates random "different" numbers
  int width = 0;
  int height = 0;
  float p_of_bite = 0;
  float p_of_berserk = 0;
  int iterations = 1; 
  int random_i = 0;
  int random_j = 0;
  int max_strength_of_zombie = 10;
  cout << "   ==========================" << endl <<
          "   Welcome to the apocalypse!" << endl <<
          "   ==========================" << endl <<
          "Enter map width between 4 and 40: ";
  cin >> height;
  while (height > 40 || height < 4){//all these while statements are to make sure number are in bounds
    cout << "Number was not between 4-40. Try again" << endl
         << "Enter map width between 4 and 40: ";
    cin >> height;
  }
  cout << "Enter map height between 4 and 40: ";
  cin >> width;
  while (width > 40 || width < 4){
    cout << "Number was not between 4-40. Try again" << endl
         << "Enter map height between 4 and 40: ";
    cin >> width;
  }
  cout << "Enter zombie bite accuracy (a float between 0-1): ";
  cin >> p_of_bite;
  while (p_of_bite > 1 || p_of_bite < 0){
    cout << "Number was not between 0-1. Try again" << endl
         << "Enter zombie bite accuracy (a float between 0-1): ";
    cin >> p_of_bite;
  }
  cout << "Enter berserker probability (a float between 0-1): ";
  cin >> p_of_berserk;
  while (p_of_berserk > 1 || p_of_berserk < 0){
    cout << "Number was not between 0-1. Try again" << endl
         << "Enter berserker probability (a float between 0-1): ";
    cin >> p_of_berserk;
  }
  cout << "For the assignment, the number was 10 but I noticed if the strength was higher" << endl;
  cout << "it would end faster" << endl;
  cout << "Enter max strength zombies can be until they turn back to humans (1-100): " << endl;
    cin >> max_strength_of_zombie;
  while (max_strength_of_zombie < 1 || max_strength_of_zombie > 100){
    cout << "Number was not between 0-100. Try again" << endl
         << "max_strength_of_zombie";
    cin >> max_strength_of_zombie;
  }
  cout << "\n";

  int MAX = height * width; //creates a MAX to use so when either humans or zombies reaches this, the while loop breaks.
  int zombies = 1;//start with one zombie
  int humans = MAX-1; //there will start one zombie and everyone will be human

//a1 will be the power of each entity
  int **a1 = new int *[width];
  for (int i = 0; i < width; i++){
    a1[i] = new int[height];
  }
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      a1[i][j] = 0;
    }
  }
//a2 will be the state of each entity
  char **a2 = new char *[width];
  for (int i = 0; i < width; i++){
    a2[i] = new char[height];
  }

  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++)
    {
      a2[i][j] = '.';
    }
  }
  //a3 will be used to track if a zombie got infected day of or after
  int **a3 = new int *[width];
  for (int i = 0; i < width; i++){
    a3[i] = new int[height];
  }
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      a3[i][j] = 0;
    }
  }
  
  start_of_apocalypse(a1, a2, random_i, random_j, width, height); // starts the apocalypse by making a random human a zombie
  print_map(a2, width, height);// prints map with iteration 0 with one zombie
  int result = run(a1, a2, a3, width, height, p_of_bite, p_of_berserk, zombies, humans, iterations, MAX, max_strength_of_zombie);//this runs until either everyone is a zombie or human
  //after it takes the result into end of apocalypse and displays the surviving side
  end_of_apocalypse(result);//runs when out of while loop
}
