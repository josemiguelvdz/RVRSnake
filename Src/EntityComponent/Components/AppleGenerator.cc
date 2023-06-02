#include "AppleGenerator.h"
#include "../Entity.h"

#include "../../Render/Window.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"
#include "../../Utils/Timer.h"

AppleGenerator::AppleGenerator() : mAppleWidth(32), mAppleHeight(32), 
mMaxAppleNumber(3), mTimeToRespawn(2.f)
{
    setName("applegenerator");
}


AppleGenerator::~AppleGenerator()
{
    delete mAppleTimer;
}

void AppleGenerator::start()
{
    // Init virtual timer
    mAppleTimer = new Timer();
    mAppleTimer->pause();
}

void AppleGenerator::update(const double& dt)
{
    // Update virtual timer to generate Apples in random positions not occuppied by board
    mAppleTimer->update(dt);
    mAppleTimer->resume();

    //Erase eaten apples
    for(auto apple = mApples.begin(); apple != mApples.end();) {
        if(apple->eaten)
            apple = mApples.erase(apple);
        else
            apple++;
    }

    if(mAppleTimer->getRawSeconds() > mTimeToRespawn && mApples.size() < mMaxAppleNumber){
        mTimeToRespawn = 7;
        Apple newApple = Apple();

        // TODO: OBTAIN BOARD INFO
        newApple.posX = sdlutils().rand().nextInt(0, 21);
        newApple.posY = sdlutils().rand().nextInt(0, 21);
        newApple.eaten = false;

        mApples.push_back(newApple);

        // Reset timer
        mAppleTimer->reset();

        //std::cout << "Apple generated in: " << newApple.posX << " " << newApple.posY << "\n";
    }
}

void AppleGenerator::render()
{
    // Render the apples
    for(int i = 0; i < mApples.size(); i++){
        if(mApples[i].eaten)
            continue;

        auto appleTexture = &sdlutils().images().at("apple");
        SDL_Rect appleTexBox = { mApples[i].posX * mAppleWidth, mApples[i].posY * mAppleWidth, mAppleWidth, mAppleHeight };
        appleTexture->render(appleTexBox);
    }
}

vector<Apple>& AppleGenerator::getApples(){
    return mApples;
}