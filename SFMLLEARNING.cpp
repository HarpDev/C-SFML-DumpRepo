#include <sstream>
#include <SFML/Graphics.hpp>



using namespace sf;

//function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//where is the player/branch?
//Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


int main()
{
    VideoMode vm(1920, 1080);

    RenderWindow window(vm, "Timber!!!", Style::Default);
    bool paused = true;
    bool gameover = false;
    //draw score
    int score = 0;
    
    Text MessageText;
    Text scoreText;

    //choose font
    Font font;
    font.loadFromFile("Font/CONSOLA.ttf");

    MessageText.setFont(font);
    scoreText.setFont(font);


    MessageText.setString("Press ENTER to start!");
    scoreText.setString("Score = 0");

    MessageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    //Colors For Text Instances

    MessageText.setFillColor(Color::Black);
    scoreText.setFillColor(Color::Green);

    FloatRect textRect = MessageText.getLocalBounds();

    MessageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);


    MessageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);


   


    //Prepare the 6 branches
    Texture textureBranch;
    
    textureBranch.loadFromFile("graphics/branchTest.png");

    for (int i = 0; i < NUM_BRANCHES; i++){
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        
        //set to center, then spin around randomly without changing pos
        branches[i].setOrigin(220, 20);
    
        
    }
    

    //preparing the player 
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
   
    side playerSide = side::LEFT;

    //gravestone 
    Texture textureGraveStone;
    textureGraveStone.loadFromFile("graphics/TBHStaticIdle.png");
    Sprite spriteGravestone;
    spriteGravestone.setTexture(textureGraveStone);
    spriteGravestone.setPosition(600, 860);


    //axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    //Line axe up with tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;


    //falling log 
    Texture fallingLogTexture;
    fallingLogTexture.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(fallingLogTexture);
    spriteLog.setPosition(810, 720);

    //logVariables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    
     
    Texture textureBackround;
    //load graphic onto texture
    textureBackround.loadFromFile("Graphics/forest.jpg");

    //Create sprite for texture
    Sprite spriteBackround;

    //Attach texture to sprite
    spriteBackround.setTexture(textureBackround);

    //Set backround to cover screen
    spriteBackround.setPosition(0, 0);


    //rendering tree
    Texture textureTree;

    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    


    //rendering bee
    Texture textureBee;

    textureBee.loadFromFile("graphics/Bee.png");//currently set to spong bop
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0,800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    int currentPosition = spriteBee.getPosition().x;

    //Cloud shizz

    //3 sprites from 1 texture
    Texture textureCloud;

    //load 1 new texture
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud0;
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    spriteCloud0.setTexture(textureCloud);
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    bool cloud0Active = true;
    bool cloud1Active = true;
    bool cloud2Active = true;

        spriteCloud0.setPosition(800, 100);
        spriteCloud1.setPosition(300, 250);
        spriteCloud2.setPosition(0, 500);

        float cloudSpeed0 = 80.0f;
        float cloudSpeed1 = 100.0f;
        float cloudSpeed2 = 200.0f;

        Clock clock;

        //Time bar
        RectangleShape timeBar;
        float timeBarStartWidth = 400;
        float timeBarHeight = 80;
        timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
        timeBar.setFillColor(Color::Red);
        timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

        Time gameTimeTotal;
        float timeRemaining = 6.0f;
        float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
        

       

        updateBranches(1);
        updateBranches(2);
        updateBranches(3);
        updateBranches(4);
        updateBranches(5);
      




        //control player input
        bool acceptInput = false;


        //Lives
        int TotalLives = 3;
        int currentLives = 0;


        
    while (window.isOpen())
    {
       // score++;//temp
        /***********************
            Player Input
        ************************/
        
        Event event;
        //detecting if key has been released
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                //listen for key presses again
                acceptInput = true;

                //hide axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }

        }

        //Exit Application
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        /***********************

            Update the Scene
        ************************/
        
        // Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            // Reset the time, score, and health
            score = 0;
            timeRemaining = 6;
            currentLives = TotalLives;
            // Make all the branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }

            // Make sure the gravestone is hidden
            spriteGravestone.setPosition(675, 2000);

            // Move the player into position
            spritePlayer.setPosition(580, 720);

            acceptInput = true;


        }
        //wrap player controls
        //to make sure we are
        //understanding input
        if (acceptInput) {
            //Handling pressing right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                //make sure player is on the righthand side of the screen
                playerSide = side::RIGHT;
                score++;

                //add to amount of time remaining 
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);

                //update branches
                updateBranches(score);

                //Set log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;

                acceptInput = false;
            }
            // handle pressing left cursor key
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                //make sure player is on the righthand side of the screen
                playerSide = side::LEFT;
                score++;

                //add to amount of time remaining 
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);

                //update branches
                updateBranches(score);

                //Set log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;
            }
        }
        
        
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            if (!gameover) {
                paused = false;
            }
            //pause does not work if gameover state is entered
        }

        if (!paused && !gameover) {




            currentPosition += 200 / 5000;
            Time dt = clock.restart();

            //subtract current time remaining
            timeRemaining -= dt.asSeconds();
            //size up the time bar 
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)//if time bar runs out, remove bar and display "game over" message to player.
            {
                paused = true;//pauses game

                MessageText.setString("womp womp");//changes message to display a "game over" message
                gameover = true;
                FloatRect textRect = MessageText.getLocalBounds();//resizing text to match game over state
                MessageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                MessageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

            }

           
                MessageText.setString("");//remove text 4 starting game

            

            if (!beeActive)
            {

                //fastBee
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                //beeheight
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);

                beeActive = true;
            }
            else
            {

                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
                //when bee reaches end of stream, reset.
                if (spriteBee.getPosition().x < -200) {
                    beeActive = false;
                }
            }
            //cloud0
            if (!cloud0Active)
            {

                srand((int)time(0));
                cloudSpeed0 = (rand() % 200) + 50;



                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteCloud0.setPosition(2000, height + 100);

                cloud0Active = true;
            }
            else
            {

                spriteCloud0.setPosition(
                    spriteCloud0.getPosition().x - (cloudSpeed0 * dt.asSeconds()), spriteCloud0.getPosition().y);
                //when bee reaches end of stream, reset.
                if (spriteCloud0.getPosition().x < -800) {
                    cloud0Active = false;
                }
            }

            //cloud0
            if (!cloud1Active)
            {


                srand((int)time(0));
                cloudSpeed1 = (rand() % 200) + 50;



                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteCloud1.setPosition(2000, height + 100);

                cloud1Active = true;
            }
            else
            {

                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x - (cloudSpeed1 * dt.asSeconds()), spriteCloud1.getPosition().y);
                //when bee reaches end of stream, reset.
                if (spriteCloud1.getPosition().x < -800) {
                    cloud1Active = false;
                }
            }
            if (!cloud2Active)
            {


                srand((int)time(0));
                cloudSpeed2 = (rand() % 200) + 50;



                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteCloud2.setPosition(2000, height + 100);

                cloud2Active = true;
            }
            else
            {

                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x - (cloudSpeed2 * dt.asSeconds()), spriteCloud2.getPosition().y);
                //when bee reaches end of stream, reset. 
                if (spriteCloud2.getPosition().x < -800) {
                    cloud2Active = false;
                }
            }

            std::stringstream ss;
            ss << "Score =  " << score;
            scoreText.setString(ss.str());

            // update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++)
            {

                float height = i * 150;

                if (branchPositions[i] == side::LEFT)
                {
                    // Move the sprite to the left side
                    branches[i].setPosition(610, height);
                    // Flip the sprite round the other way
                    branches[i].setOrigin(220, 40);
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    // Move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // Set the sprite rotation to normal
                    branches[i].setOrigin(220, 40);
                    branches[i].setRotation(0);

                }
                else
                {
                    // Hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
            // Handle a flying log				
            if (logActive)
            {

                spriteLog.setPosition(
                    spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

                // Has the insect reached the right hand edge of the screen?
                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new cloud next frame
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
            // has the player been squished by a branch?
            if (branchPositions[5] == playerSide)
            {
                // death
                paused = true;
                acceptInput = false;

                // Draw the gravestone
                spriteGravestone.setPosition(525, 760);

                // hide the player
                spritePlayer.setPosition(2000, 660);

                // Change the text of the message
                MessageText.setString("SQUISHED!!");

                // Center it on the screen
                FloatRect textRect = MessageText.getLocalBounds();

                MessageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);

                MessageText.setPosition(1920 / 2.0f,
                    1080 / 2.0f);

                // Play the death sound
                //death.play();


            }
        }
        /***********************
            Draw the Scene
        ************************/

        //clear everything from the last frame
        window.clear();
        
       

        //Draw game scene here
        window.draw(spriteBackround);
        //window.draw(spriteBee);

        window.draw(spriteTree);

        window.draw(spritePlayer);

        window.draw(spriteAxe);

        window.draw(spriteLog);

        window.draw(spriteGravestone);

        
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }
        //Everything that the clouds should cover go above this comment.
        window.draw(scoreText);
        window.draw(MessageText);
        window.draw(spriteCloud0);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(timeBar);
        
        
        //Show Everything we just drew
        window.display();
        
        if (paused) {
            window.draw(MessageText);
            
        }
        else
        {
            //disable messageText
        }


    }
    return 0;
} 



// Function definition
void updateBranches(int seed)
{
    // Move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT or NONE
    srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;

    case 1:
        branchPositions[0] = side::RIGHT;
        break;

    default:
        branchPositions[0] = side::NONE;
        break;
    }


}