#include "Animation.h"

//Base Class

const std::string CharacterAnim::PATH("res/anims/"), CharacterAnim::MANIFEST("~Manifest.txt"), CharacterAnim::FORMAT(".png");

CharacterAnim::CharacterAnim()
{
    loadTextures(PATH, MANIFEST, FORMAT);
}

void CharacterAnim::loadTextures(const std::string& path, const std::string& manifest, const std::string& format)
{
    std::ifstream textureManifest;
    std::string currentFileName, lastFileName = " ";
    static int animIndex = -1;
    AnimBound currentBound;
    sf::Texture tempTexture;

    if (textureBounds.empty()) {
        currentBound.first = 0;
    } else {
        currentBound.first = textureBounds.back().last + 1;
    }

    textureManifest.open((path + manifest).c_str());

    while (!textureManifest.eof()) {
        std::getline(textureManifest, currentFileName);
        tempTexture.loadFromFile(path + currentFileName + format);
        loadedTextures.push_back(tempTexture);
        if (currentFileName != "Stand_Left" && currentFileName != "Stand_Right") {
            currentFileName.resize(currentFileName.find_last_of('_'));
        }
        if (lastFileName != currentFileName && lastFileName != " ") {
            currentBound.last = animIndex;
            textureBounds.push_back(currentBound);
            currentBound.first = animIndex + 1;
        }
        lastFileName = currentFileName;
        animIndex++;
    }
    //Push Last Bounds Object In
    currentBound.last = animIndex;
    textureBounds.push_back(currentBound);

    textureManifest.close();
}

const std::vector<AnimBound>& CharacterAnim::getTextureBounds()
{
    return textureBounds;
}

const std::vector<sf::Texture>& CharacterAnim::getLoadedTextures()
{
    return loadedTextures;
}

//Derived Classes

const std::string PlayerAnim::PATH("res/anims/player/"), PlayerAnim::MANIFEST("~Manifest.txt"), PlayerAnim::FORMAT(".png");

PlayerAnim::PlayerAnim() : CharacterAnim()
{
    loadTextures(PATH, MANIFEST, FORMAT);
}
