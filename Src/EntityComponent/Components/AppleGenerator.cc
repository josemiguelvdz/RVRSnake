#include "AppleGenerator.h"
#include "../Entity.h"

#include "../../Render/Window.h"
#include "../../Utils/SDLUtils.h"
#include "../../Utils/Texture.h"
#include "../../Utils/Timer.h"

AppleGenerator::AppleGenerator() : mName("appleGenerator"), mAppleWidth(32), mAppleHeight(32), 
mMaxAppleNumber(3), mTimeToRespawn(2.f)
{
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

    if(mAppleTimer->getRawSeconds() > mTimeToRespawn && mApples.size() < mMaxAppleNumber){
        mTimeToRespawn = 7;
        Apple newApple = Apple();

        // TODO: OBTAIN BOARD INFO
        newApple.posX = sdlutils().rand().nextInt(0, 22);
        newApple.posY = sdlutils().rand().nextInt(0, 22);

        mApples.push_back(newApple);

        // Reset timer
        mAppleTimer->reset();

        std::cout << "Apple generated in: " << newApple.posX << " " << newApple.posY << "\n";
    }
}

void AppleGenerator::render()
{
    // Render the apples
    for(int i = 0; i < mApples.size(); i++){
        auto appleTexture = &sdlutils().images().at("appleTemp");
        SDL_Rect appleTexBox = { mApples[i].posX * mAppleWidth, mApples[i].posY * mAppleWidth, mAppleWidth, mAppleHeight };
        appleTexture->render(appleTexBox);
    }
}