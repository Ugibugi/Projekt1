#include "uResourceManager.h"
#include <SDL_image.h>

using namespace utl;
std::unordered_map<std::string, std::shared_ptr<uResource_base>> uResourceManager::_resources;
//SDL_Surface* uResourceManager::loadImage(std::string name)

