#include "Entity.h"
// #include "Components/Component.h"
#include <iostream>

Entity::Entity(Scene* scene, const EntityName name) :
    mActive(true),
    mName(name),
    mScene(scene)
{
    std::cout << " > Entity ( " << mName << " ) created." << std::endl;
}

Entity::Entity(const EntityName name) :
    mActive(true),
    mName(name),
    mScene(nullptr)
{
    std::cout << " > Entity " << mName << " created.";
}

Entity::~Entity() {
    // for (auto &c : mComponents)
    //     componentsFactory().destroy(c.first, c.second);

    // mComponents.clear();
    std::cout << " >>> Entity ( " << mName << " ) deleted..." << std::endl;
}

// Component* Entity::addComponent(const ComponentName& componentName, Parameters& params) {
//     // Component* c = componentsFactory().create(componentName, params);

//     // if (!hasComponent(componentName)) {

//     //     mComponents.insert({ componentName, c });
//     //     c->setEntity(this);
//     // }
//     return c;
// }

// bool Entity::removeComponent(const ComponentName& componentName)
// {
//     // if (hasComponent(componentName)) {
//     //     componentsFactory().destroy(componentName, mComponents.find(componentName)->second);
//     //     mComponents.erase(componentName);
//     //     return true;
//     // }

//     return false;
// }

// bool Entity::hasComponent(const ComponentName& name)
// {
//     return mComponents.find(name) != mComponents.end();
// }

bool Entity::isActive() const
{
    return mActive;
}

void Entity::destroy()
{
    mActive = false;
}

EntityName Entity::getName() const
{
    return mName;
}

void Entity::setName(const EntityName name)
{
    mName = name;
}

Scene* Entity::getScene() const
{
    return mScene;
}

void Entity::setScene(Scene* scene)
{
    mScene = scene;
}

void Entity::start()
{
    // for (auto c : mComponents) {
    //     if (c.second->enabled)
    //         c.second->start();
    // };
}

void Entity::update(float dt) {
    // if (!mActive) return;
    // for (auto c : mComponents) {
    //     if(c.second->enabled)
    //         c.second->update(dt);
    // };
}

void Entity::lateUpdate(float dt) {
    // if (!mActive) return;
    // for (auto c : mComponents) {
    //     if (c.second->enabled)
    //         c.second->lateUpdate(dt);
    // };
}

void Entity::onCollisionEnter(Entity* other)
{
    // for (auto &c : mComponents) {
    //     if(c.second->enabled && c.first != "collider")
    //         c.second->onCollisionEnter(other);
    // }
}

void Entity::onCollisionStay(Entity* other)
{
    // for (auto &c : mComponents ) {
    //     if (c.second->enabled  && c.first != "collider")
    //         c.second->onCollisionStay(other);
    // }
}

void Entity::onCollisionExit(Entity* other)
{
    // for (auto &c : mComponents) {
    //     if (c.second->enabled && c.first != "collider")
    //         c.second->onCollisionExit(other);
    // }
}