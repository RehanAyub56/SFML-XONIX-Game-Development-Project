#include <SFML/Graphics.hpp>
#include <time.h>
#include<sstream>
#include<cmath>
#include<fstream>
#include<iomanip>
#include"menu.hpp"
#include"level.hpp"

using namespace sf;

const int M = 25;
const int N = 40;

int grid[M][N] = {0};
int ts = 18; //tile size

struct Enemy
{
int x,y,x2,y2,dx,dy;
   float radius=100;
    float angle=3.14/3;
    float centerX = 400; 
    float centerY = 400; 

  Enemy()
   {
    x=y=300;
    dx=4-rand()%8;
    dy=4-rand()%8;
   }

  void move(){ 
    x+=dx; if (grid[y/ts][x/ts]==1) {dx=-dx; x+=dx;}
    y+=dy; if (grid[y/ts][x/ts]==1) {dy=-dy; y+=dy;}
    
   }
  
   
};

void drop(int y,int x)
{
  if (grid[y][x]==0) grid[y][x]=-1;
  if (grid[y-1][x]==0) drop(y-1,x);
  if (grid[y+1][x]==0) drop(y+1,x);
  if (grid[y][x-1]==0) drop(y,x-1);
  if (grid[y][x+1]==0) drop(y,x+1);
}

int fillCapturedArea(int grid[M][N]){
    bool changed=true;

    while (changed){
        changed = false;
        for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
        if((i==0 || j==0 || i==M-1 || j==N-1) && grid[i][j]==0){ 
          grid[i][j]=-1;
          changed=true;
      }
     else if(grid[i][j]==0 && ((i>0 && grid[i-1][j]==-1) || (i<M-1 && grid[i+1][j]==-1) ||(j > 0 && grid[i][j-1]==-1) || (j<N-1 && grid[i][j+1]==-1))){
                    grid[i][j]=-1;
                    changed=true;
                }
            }
        }
    }
    int captured=0;
    for (int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]==0){
                grid[i][j]=1;
                captured++;
            }
            else if(grid[i][j]==-1){
                grid[i][j]=0;
            }
        }
        }
    return captured;
}

int fillCapturedAreaAndCompare(int grid[M][N]) {
    int oldGrid[M][N];
    for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
            oldGrid[i][j]=grid[i][j];
    fillCapturedArea(grid);
    int captured=0;
    for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
            if (oldGrid[i][j]==0 && grid[i][j]==1)
                captured++;

    return captured;
}

struct ScoreEntry {
    int score;
    float timeTaken;
};

const int MAX_SCORES = 5;

int loadScores(const char* filename, ScoreEntry scores[]) {
    std::ifstream file(filename);
    int count = 0;
    if(!file.is_open()) return 0;
    while(count<MAX_SCORES && file>>scores[count].score>>scores[count].timeTaken){
        count++;
    }
file.close();
    return count;
}
void saveScores(const char* filename,ScoreEntry scores[],int count){
    std::ofstream file(filename);
    for(int i=0;i<count;i++){
        file<<scores[i].score<<" " <<scores[i].timeTaken<<"\n";
    }
    file.close();
}

void insertScore(ScoreEntry scores[],int& count,int newScore,float timeTaken){
    if(count<MAX_SCORES){
        scores[count].score=newScore;
        scores[count].timeTaken=timeTaken;
        count++;
    }else if(newScore>scores[count-1].score || (newScore==scores[count-1].score && timeTaken<scores[count-1].timeTaken)){
        scores[count-1].score=newScore;
        scores[count-1].timeTaken=timeTaken;
    }
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(scores[j].score<scores[j+1].score || (scores[j].score==scores[j+1].score && scores[j].timeTaken>scores[j+1].timeTaken)){
                ScoreEntry temp=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }
        }  }
}



int main()
{


MenuContext ctx;
setup_menu(ctx);

init_menu(ctx);
run_menu(ctx);

 
 
  
    srand(time(0));

    RenderWindow window(VideoMode(N*ts, M*ts), "Xonix Game!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    t4.loadFromFile("images/powerup.png");
    
    Sprite sTile(t1), sGameover(t2), sEnemy(t3),power(t4);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);
    Clock clock,c;
   int capturedTiles = 0;
   int occurance=0;
   int power_up=0;
   int newlyCaptured;
    
    int enemyCount=0;
   
    
  if(ctx.position==4){
     window.close();
    }
 

    
    else{
    enemyCount = 4;
    }
    cleanup_menu(ctx);
   
    Enemy a[10];


    bool Game=true;
    int x=0, y=0, dx=5, dy=5,x2=50,y2=0,dx2=0,dy2=0,score1=0,score2=0;
    float timer=0, delay=0.07;
    float timer1 = 0, timer2 = 0;
    sf::Text timetext;
    sf:: Font font;
    if(!font.loadFromFile("images/airstrike.ttf")){
    std::cout<<"Error in font Loading \n";
    }
    
   
   timetext.setFont(font);
   timetext.setCharacterSize(20);
   timetext.setFillColor(sf::Color::White);
   timetext.setPosition(570,-5);
   timetext.setOutlineColor(sf::Color::Black);
   timetext.setOutlineThickness(4);
   bool switchToCircular = false;
   
   sf::Text endScoreText;
endScoreText.setFont(font);
endScoreText.setPosition(100, 300);
   
   sf::Text counter,counter2;
   sf::Text powerUpText;
    sf:: Font font2,font3;
    if(!font2.loadFromFile("images/airstrike.ttf")){
    std::cout<<"Error in font Loading \n";
    }
     if(!font3.loadFromFile("images/airstrike.ttf")){
    std::cout<<"Error in font Loading \n";
    }
     bool player1alive = true;
    bool player2alive = true;
    std::string winner = "";
    
   
   counter.setFont(font2);
   counter.setCharacterSize(20);
   counter.setFillColor(sf::Color::White);
   counter.setPosition(70,-5);
   counter.setOutlineColor(sf::Color::Black);
   counter.setOutlineThickness(4);
   
   counter2.setFont(font2);
   counter2.setCharacterSize(20);
   counter2.setFillColor(sf::Color::White);
   counter2.setPosition(390,-5);
   counter2.setOutlineColor(sf::Color::Black);
   counter2.setOutlineThickness(4);
   
   powerUpText.setFont(font3);    
   powerUpText.setCharacterSize(20);
   powerUpText.setPosition(220,-5);
   powerUpText.setOutlineColor(sf::Color::Black);
   powerUpText.setOutlineThickness(4); 
 
 
    endScoreText.setCharacterSize(24);
    endScoreText.setFillColor(sf::Color::White);
    endScoreText.setOutlineColor(sf::Color::Black);
    endScoreText.setOutlineThickness(3);
    endScoreText.setPosition(150, 220);
   
   power.setPosition(170,-5);
   power.setScale(0.25f,0.25f); 
   

   
   float lastincreasedtime=0;
   int move=0,tilesThisMove = 0;

   int points=0;
   int captured_in_move=0,captured_in_move2=0;
bool isConstructing = false; 
bool wasConstructing = false;
bool powerUsed = false;
float powerStartTime = 0;
int capturedTiles2,isConstructing2 = false,wasConstructing2 = false,tilesThisMove2,move2=0;


  
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;
      sf::Clock enemySpawnClock;
       enemyCount = 2; 
      
    while (window.isOpen()){
    // starting enemy count

    
    if (ctx.position == 2) {
    if (ctx.difficulty_level == 1) {
        enemyCount = 2;
    }
    else if (ctx.difficulty_level == 2) {
        enemyCount = 4;
    }
    else if (ctx.difficulty_level == 3) {
        enemyCount = 6;
    }
    else if (ctx.difficulty_level == 4) {
        if (enemySpawnClock.getElapsedTime().asSeconds() >= 20) {
            enemyCount+=2;
            enemySpawnClock.restart();
         
        }
    }
}
    
     if (!player1alive) {
        dx = 0;  // Stop Player 1's horizontal movement
        dy = 0;  // Stop Player 1's vertical movement
    }
     if (!player2alive) {
        dx2 = 0;  // Stop Player 2's horizontal movement
        dy2 = 0;  // Stop Player 2's vertical movement
    }
    
    static bool scoreSaved = false;
if (!Game && !scoreSaved) {
    ScoreEntry scores[MAX_SCORES];
    int scoreCount = loadScores("scoreboard.txt", scores);

    insertScore(scores, scoreCount, points, c.getElapsedTime().asSeconds());
    saveScores("scoreboard.txt", scores, scoreCount);

    scoreSaved = true;
}
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        timer+=time;
        timer1 += time;
       timer2 += time;
        
        float time1=c.getElapsedTime().asSeconds();
        std::ostringstream ss;
        ss<<"Time  :  "<<std::fixed<<std::setprecision(0)<<time1;
        timetext.setString(ss.str());

        


        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed)
             if (e.key.code==Keyboard::Escape)
               {
                for (int i=1;i<M-1;i++)
                 for (int j=1;j<N-1;j++)
                   grid[i][j]=0;

                x=10;y=0;
                Game=true;
               }
               
     if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    sf::FloatRect powerBounds = power.getGlobalBounds();

    if (powerBounds.contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
        if (power_up > 0 && !powerUsed) {
            powerUsed = true;
            powerStartTime = c.getElapsedTime().asSeconds();
            power_up--;
        }
    }
}


               
        }
        
 if(ctx.playernumber!=2){

        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;}
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;}
       
        if (!Game) continue;
        
 if (timer>delay){
         x+=dx;
         y+=dy;
         
         
         if (x<0) x=0; if (x>N-1) x=N-1;
         if (y<0) y=0; if (y>M-1) y=M-1;        
        if (grid[y][x] == 2) {
        Game = false;
    }

    if (grid[y][x]==0){
        grid[y][x]=2;

        
        capturedTiles++;
        tilesThisMove++; 
        isConstructing=true;
    }else{ 
        isConstructing = false;
    }
    if (isConstructing && !wasConstructing){
        move++;

    }
         timer=0;
        }
       
       
    
        std::ostringstream st;
        st<<"Moves :  "<<move;
        counter.setString(st.str());
      
       
        
if(time1-lastincreasedtime>20){
        for (int i=0;i<enemyCount;i++) {
        a[i].dx *= 1.5;
        a[i].dy *= 1.5;
}
lastincreasedtime=time1;
}
float currentTime=c.getElapsedTime().asSeconds();
float elapsedGameTime = c.getElapsedTime().asSeconds();

if(powerUsed){
    float currentTime =c.getElapsedTime().asSeconds();
    if(currentTime-powerStartTime<=3.0f){
    }else{
        powerUsed=false;
    }
}else{
      for(int i=0;i<enemyCount;i++){
        a[i].move();
}
}



        if (grid[y][x]==1){
           dx=dy=0;
  
           for (int i=0;i<enemyCount;i++)
                drop(a[i].y/ts, a[i].x/ts);
                 newlyCaptured = fillCapturedAreaAndCompare(grid);
if (newlyCaptured > 0) {
        std::cout << "Captured this round: " << newlyCaptured << "\n";
        
    }
           for (int i=0;i<M;i++)
             for (int j=0;j<N;j++)
              if (grid[i][j]==2) grid[i][j]=1;
              
              captured_in_move=tilesThisMove;
            tilesThisMove = 0;
          }
           wasConstructing = isConstructing;
          if(newlyCaptured<=10){
          points=points+newlyCaptured;
          }
          else if(newlyCaptured>10 && occurance<=3){
          points=points+newlyCaptured*2;
          occurance++;
          }
          else if(newlyCaptured>5 && occurance>3 && occurance<=5){
          points=points+newlyCaptured*2;
          occurance++;
          }
          else if(newlyCaptured>5 && occurance>5){
          points=points+newlyCaptured*4;
          occurance++;
          }
          static int lastPowerUpScore = 70;

          if(points>=50 && power_up==0){
              power_up++;
          }
          if(points>=70 && points<100 && power_up==1){
              power_up++;
          }
          if(points>=lastPowerUpScore+30){
              power_up++;
              lastPowerUpScore+=30;
          }
      
          std::ostringstream pu;
pu <<power_up;
powerUpText.setString(pu.str());
          
          
 for (int i=0;i<enemyCount;i++)
 if  (grid[a[i].y/ts][a[i].x/ts]==2) Game=false;
       

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2){
            sTile.setTextureRect(IntRect(54,0,ts,ts));
            }
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
          
         }
   
      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);
      window.draw(counter); 
      window.draw(power);
      window.draw(powerUpText);
      
      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }
window.draw(timetext);
      if (!Game) {
      window.draw(sGameover);
std::ostringstream finalScoreStream;
    finalScoreStream << "Score: " << points << "\n";
    finalScoreStream << "Time: " << std::fixed << std::setprecision(1) << time1 << "s\n";
    finalScoreStream << "Moves: " << move << "\n";
endScoreText.setString(finalScoreStream.str());
    window.draw(endScoreText);

}

       window.display();
       }
       
    
    
    // Player 2 Start 
    
    
    
     if (ctx.playernumber == 2 && ctx.position==1) {
        // Handle Player 1 movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
        if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

        // Handle Player 2 movement
        if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
        if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
        if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
        if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }

        if (!Game) continue;

        if (timer1 > delay) {
    x += dx;
    y += dy;
    if (x < 0) x = 0; if (x > N - 1) x = N - 1;
    if (y < 0) y = 0; if (y > M - 1) y = M - 1;

    if (grid[y][x] == 3) player1alive = false; // Touching player 2's trail
    if (grid[y][x] == 0) {
        grid[y][x] = 2;
        capturedTiles++;
        tilesThisMove++;
        isConstructing = true;
    } else {
        isConstructing = false;
    }

    if (isConstructing && !wasConstructing) {
        move++;
    }

    timer1 = 0;
}

if (timer2 > delay) {
    x2 += dx2;
    y2 += dy2;
    if (x2 < 0) x2 = 0; if (x2 > N - 1) x2 = N - 1;
    if (y2 < 0) y2 = 0; if (y2 > M - 1) y2 = M - 1;

    if (grid[y2][x2] == 2) player2alive = false; // Touching player 1's trail
    if (grid[y2][x2] == 0) {
        grid[y2][x2] = 3;
        capturedTiles2++;
        tilesThisMove2++;
        isConstructing2 = true;
    } else {
        isConstructing2 = false;
    }

    if (isConstructing2 && !wasConstructing2) {
        move2++;
    }

    timer2 = 0;
}


bool p1_constructing = (grid[y][x] == 0);
bool p2_constructing = (grid[y2][x2] == 0);

// Both players collide while constructing → both die
if (x == x2 && y == y2 && p1_constructing && p2_constructing) {
    player1alive = false;
    player2alive = false;
}

// One touches the other while only one is constructing
if (x == x2 && y == y2) {
    if (p1_constructing && !p2_constructing) {
        player1alive = false;
    } else if (!p1_constructing && p2_constructing) {
        player2alive = false;
    }
}

if (!player1alive || !player2alive) {
    Game = false;
}
        
         std::ostringstream st;
        st<<"Moves :  "<<move;
        counter.setString(st.str());
        
         std::ostringstream st2;
        st2<<"Moves :  "<<move2;
        counter2.setString(st2.str());
        if (enemyCount > 10) enemyCount = 10;
        
if(time1-lastincreasedtime>20){
        for (int i=0;i<enemyCount;i++) {
        a[i].dx *= 1.5;
        a[i].dy *= 1.5;
}
lastincreasedtime=time1;
}
        
        // Handle enemies and grid updates for both players
        for(int i=0;i<enemyCount;i++){
     
        a[i].move();
    
}

        if (grid[y][x] == 1) {
            dx = dy =0;

            for (int i = 0; i < enemyCount; i++)
                drop(a[i].y / ts, a[i].x / ts); // This represents the clash of enemy with player1
                

            for (int i = 0; i < M; i++){
                for (int j = 0; j < N; j++){
                    if (grid[i][j] == -1) 
                    grid[i][j] = 0;
                    else grid[i][j] = 1;
                    
        }
        
      }  

}

  if (grid[y][x]==1){
           dx=dy=0;
  
           for (int i=0;i<enemyCount;i++)
                drop(a[i].y/ts, a[i].x/ts);
                 newlyCaptured = fillCapturedAreaAndCompare(grid);
if (newlyCaptured > 0) {
        std::cout << "Captured this round: " << newlyCaptured << "\n";
        
    }
           for (int i=0;i<M;i++)
             for (int j=0;j<N;j++)
              if (grid[i][j]==2) grid[i][j]=1;
              
              captured_in_move=tilesThisMove;
            tilesThisMove = 0;
          }
           wasConstructing = isConstructing;
           if (grid[y2][x2] == 1) {
    dx2 = dy2 = 0;

    for (int i = 0; i < enemyCount; i++)
        drop(a[i].y / ts, a[i].x / ts);
    newlyCaptured = fillCapturedAreaAndCompare(grid);


    captured_in_move2 = tilesThisMove2;
    tilesThisMove2 = 0;
}
wasConstructing2 = isConstructing2;
          if(newlyCaptured<=10){
          points=points+newlyCaptured;
          }
          else if(newlyCaptured>10 && occurance<=3){
          points=points+newlyCaptured*2;
          occurance++;
          }
          else if(newlyCaptured>5 && occurance>3 && occurance<=5){
          points=points+newlyCaptured*2;
          occurance++;
          }
          else if(newlyCaptured>5 && occurance>5){
          points=points+newlyCaptured*4;
          occurance++;
          }
          static int lastPowerUpScore = 70;

          if(points>=50 && power_up==0){
              power_up++;
          }
          if(points>=70 && points<100 && power_up==1){
              power_up++;
          }
          if(points>=lastPowerUpScore+30){
              power_up++;
              lastPowerUpScore+=30;
          }
          std::ostringstream pu;
pu <<power_up;
powerUpText.setString(pu.str());

        for (int i = 0; i < enemyCount; i++) {     
   if (grid[a[i].y / ts][a[i].x / ts] == 2) Game = false;
              // Check direct collisions between enemies and players
        float distance1 = sqrt(pow(a[i].x - x*ts, 2) + pow(a[i].y - y*ts, 2));
        float distance2 = sqrt(pow(a[i].x - x2*ts, 2) + pow(a[i].y - y2*ts, 2));
        
        if (distance1 < ts) player1alive = false;
        if (distance2 < ts) player2alive = false;
        
        }
         if (!player1alive && !player2alive) {
        Game = false;
        winner = "Draw";
    } else if (!player1alive) {
        Game = false;
        winner = "Player 2 Wins!";
    } else if (!player2alive) {
        Game = false;
        winner = "Player 1 Wins!";
    }
    //for Player 1 and Player 2
        window.clear();

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j * ts, i * ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x * ts, y * ts);
        window.draw(sTile);

        sTile.setTextureRect(IntRect(54, 0, ts, ts));
        sTile.setPosition(x2 * ts, y2 * ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {  //Issue in this part
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        window.draw(timetext);
        window.draw(counter);
        window.draw(counter2);
        window.draw(power);
        window.draw(powerUpText);
      
        if (!Game){
        window.draw(sGameover);
         

    std::ostringstream finalScoreStream;
    finalScoreStream << "Score: " << points << "\n";
    finalScoreStream << "Time: " << std::fixed << std::setprecision(1) << time1 << "s\n";
    finalScoreStream << "Moves: " << move << "\n";

    endScoreText.setString(finalScoreStream.str());
    window.draw(endScoreText);
  
}
        window.display();
    }
    
    
    }
    

    
    return 0;
}
