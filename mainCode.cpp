#include<SFML/Graphics.hpp> //this library provides functions and classes for creating shapes, handling textures etc
using namespace sf;         //compiles using sf namespace, allows using SFML function without sf::
int main(){
  VideoMode vm(1920, 1080);   //VideoMode ---> class, vm ---> Object
  RenderWindow window(vm,"TIMBER MAN GAME", Style::Fullscreen);   //RenderWindow ---> class, window ---> Object

  View view(FloatRect(0,0,1920,1080));   // 'view' object controls what portion of the screen is visible
  //FloatRect ---> a recatangle with top-left corner at (0,0) and size 1920x1080
  window.setView(view);  // setView ---> sets the window to display the created view

  
  //---Associating image to the background---
  Texture textureBackground;   // Texture ---> class(stores image)
  textureBackground.loadFromFile("graphics/background.png"); //loadFromFile ---> Loads an image from file into object 'textureBackground'
  Sprite spriteBackground;     //Sprite ---> class(sets the image) 
  spriteBackground.setTexture(textureBackground);   //setTexture ---> assigns the image
  spriteBackground.setPosition(0,0);  // setPosition ---> sets the position of sprite(display) to top-left corner

  
  //---Associating image to the tree---
  Texture textureTree;
  textureTree.loadFromFile("graphics/tree.png");
  Sprite spriteTree;
  spriteTree.setTexture(textureTree);
  spriteTree.setPosition(810,0);

  
  //---Associating image to the bee---
  Texture textureBee;
  textureBee.loadFromFile("graphics/bee.png");
  Sprite spriteBee;
  spriteBee.setTexture(textureBee);
  spriteBee.setPosition(0, 800);

  bool beeActive=false;  //determines if the bee is moving
  float beeSpeed=0.0f;   //hols the bee's movement speed 

  
  //---Associating image to the clouds---
  Texture textureCloud;
  textureCloud.loadFromFile("graphics/cloud.png");
  Sprite spriteCloud1, spriteCloud2, spriteCloud3;
  spriteCloud1.setTexture(textureCloud);
  spriteCloud2.setTexture(textureCloud);
  spriteCloud3.setTexture(textureCloud);
  spriteCloud1.setPosition(0,0);
  spriteCloud2.setPosition(0,150);
  spriteCloud2.setScale(0.5,0.5);   //scales down(size) of cloud 2
  spriteCloud3.setPosition(0,300);

  bool cloud1Active=false;
  float cloud1Speed=0.0f;
  
  bool cloud2Active=false;
  float cloud2Speed=0.0f;
  
  bool cloud3Active=false;
  float cloud3Speed=0.0f;

  
  Clock clock;   //Clock ---> class, used for contolling movement speeds and animations, keeps track of time


  //---timeBar code ---
  RectangleShape timeBar;     //timeBar---> Object
  float timeBarStartWidth=400;
  float timeBarHeight=80;
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920/2)-200, 980);

  //---starting timer, showing remaining time---
  Time gameTimeTotal;
  float timeRemaining=6.0f;
  float timeBarWidthPerSecond= timeBarStartWidth/timeRemaining;
  
  bool paused=true;
  int score=0;
  
  Text messageText;
  Text scoreText;
  
  Font font;   // font ---> Object
  font.loadFromFile("font/KOMIKAP_.ttf");
  //setting font
  messageText.setFont(font);
  scoreText.setFont(font);
  //setting text
  messageText.setString("Press Enter to start!!");  //setString---> function inside text class
  scoreText.setString("Score=0");
  //setting size
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);
  //setting color
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);
  
  FloatRect textRect=messageText.getLocalBounds();
  messageText.setOrigin(textRect.left+textRect.width/2.0f, textRect.top+textRect.height/2.0f);
  messageText.setPosition(960, 540);
  scoreText.setPosition(10,10);

  //---gaming loop section---
  //keeping the window open
  while(window.isOpen()){
  
    Event event;
    while(window.pollEvent(event)){
      if(event.type==Event::Closed){  
        window.close();
      }
    }
  
    if(Keyboard::isKeyPressed(Keyboard::Escape)){    //KeyPressed ---> Function, i.e closes the window if Escape key is pressed
      window.close();
    }  
    if(Keyboard::isKeyPressed(Keyboard::Return)){
      paused=false;
      score=0;
    }
  
    Time dt=clock.restart();    //dt is an object of class "Time"
  
    if(!paused){
      timeRemaining-=dt.asSeconds();  //timeremaining--->6
      timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));
      //if this game is running on 60fps, frame time =1/60=0.016=dt.asSecond. TimeRemaining=6=>6-0.016=5.99. timebar/remainingtime=400/6=66.6.
      //Whenever we press enter, width 400 is reduced to 66.6*5.99=398.5
      if (timeRemaining<=0.0f){
        paused=true;
      }
    }
  
    //---for bee---
    if(!beeActive){
      srand((int)time(0));             //srand for generating within a 'fraction of second'
      beeSpeed=(rand() % 200)+200;     //rand for generating within a 'range'
      float height=(rand() % 500)+500;
      spriteBee.setPosition(2000,height);
      beeActive=true;
    }
    else{
      spriteBee.setPosition(spriteBee.getPosition().x-(beeSpeed*dt.asSeconds()), spriteBee.getPosition().y);
      if(spriteBee.getPosition().x<-100){
        beeActive=false;
      }
    }
  
    //---for cloud 1---
    if(!cloud1Active){
      srand((int)time(0));            
      cloud1Speed=(rand() % 90)+90;    
      float height=(rand() % 500)+500;
      spriteCloud1.setPosition(-100,0);
      cloud1Active=true;
    }
    else{
      spriteCloud1.setPosition(spriteCloud1.getPosition().x+(cloud1Speed*dt.asSeconds()), spriteCloud1.getPosition().y);
      if(spriteCloud1.getPosition().x>2000){
      cloud1Active=false;
      }
    }
  
    //---for cloud 2---
    if(!cloud2Active){
      srand((int)time(0));            
      cloud2Speed=(rand() % 50)+50;    
      float height=(rand() % 500)+500;
      spriteCloud2.setPosition(-100,150);
      cloud2Active=true;
    }
    else{
      spriteCloud2.setPosition(spriteCloud2.getPosition().x+(cloud2Speed*dt.asSeconds()), spriteCloud2.getPosition().y);
      if(spriteCloud2.getPosition().x>2000){
        cloud2Active=false;
      }
    }
  
    //---for cloud 3---
    if(!cloud3Active){
      srand((int)time(0));            
      cloud3Speed=(rand() % 120)+120;    
      float height=(rand() % 500)+500;
      spriteCloud3.setPosition(-100,300);
      cloud3Active=true;
    }
    else{
      spriteCloud3.setPosition(spriteCloud3.getPosition().x+(cloud3Speed*dt.asSeconds()), spriteCloud3.getPosition().y);
      if(spriteCloud3.getPosition().x>2000){
        cloud3Active=false;
      }
    }
  
  
  
    window.clear();  //clears the screeen before drawing the next frame
  
    window.draw(spriteBackground);
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);
    window.draw(spriteTree);
    window.draw(spriteBee);
    window.draw(timeBar);
    window.draw(messageText);
    window.draw(scoreText);
    window.display();  //displays new frame
    }
  return 0;
}


