#pragma once

#ifndef __ENTITYCOMPONENT_ENTITY
#define __ENTITYCOMPONENT_ENTITY

#include "../Scenes/InfoScene.h"
#include <vector>
#include <map>

class Scene;
class Component;

/**
An Entity is anything that exists in a scene.
An Entity by itself doesnŽt do anything - its behaviour is defined by the Components 
it possesses, which are stored in its mComponents map.
An Entity has a name, a reference to the scene it exists in, and can be active or not.
*/
class Entity {
    friend Scene;

public:
    /**
    Build the foundation of the Entity.
    @param Scene to which it belongs.
    @param String name to identify it.
    */
    Entity(Scene* scene, const EntityName name);

    /**
    Build the foundation of the Entity.
    @param String name to identify it.
    */
    Entity(const EntityName name);

    /**
    Delete all the components added to the entity.
    */
    virtual ~Entity();

    bool addComponent(Component* component);

    /**
    Remove completely a typed component.
    */
    bool removeComponent(const ComponentName& componentName);
    
    /**
    Get the reference a suggested component.
    @param Component's key name in this Entity's map
    @return Reference to the component. Nullptr if it does not exist.
    */
    template<typename T>
    inline T* getComponent(const ComponentName& componentName) {
        if (!hasComponent(componentName))
            return nullptr;

        return static_cast<T*>(mComponents.find(componentName)->second);
    };

    /**
    // Check if the component has already been added.
    // @param Component's key name in this Entity's map
    // @return Boolean confirmation.
    // */
    bool hasComponent(const ComponentName& name);

    /**
    Check if the entity is active.
    @return Boolean confirmation.
    */
    bool isActive() const;

    /**
    Set the entity activity to false.
    This will cause to be safely delete by the scene.
    */
    void destroy();

    /**
    Get the entity name.
    @return String name.
    */
    EntityName getName() const;

    /**
    Set the entity name to the new one.
    @param name New name.
    */
    void setName(const EntityName name);

    /**
    Get the associated scene of the entity.
    @return Scene to which it belongs.
    */
    Scene* getScene() const;

    /**
    Set the associated scene for the entity.
    @param Scene to which it belongs.
    */
    void setScene(Scene* scene);

    void start();

    /**
    Run all the added components update method.
    @param dt Seconds that have passed since last update.
    */
    void update(float dt);

    void render();


    /**
    This function is called when the object collides with another object
    */
    void onCollisionEnter(Entity* other);


    /**
    This function is called every frame while the object is colliding with another object
    */
    void onCollisionStay(Entity* other);

    /**
    This function is called when the object stops colliding with another object
    */
    void onCollisionExit(Entity* other);

    int getDepth();
    void setDepth(int newPosZ);

private:
    bool mActive;
    int mPosZ;

    std::string mName;
    Scene* mScene;
    std::map<ComponentName, Component*> mComponents;
};

#endif