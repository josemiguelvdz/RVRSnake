#pragma once

#ifndef __SCENES_SCENE
#define __SCENES_SCENE

#include "InfoScene.h"
#include <memory>
#include <initializer_list>
#include <vector>

class Entity;

/**
A Scene is a collection of Entities that exist in the same spatial context,
so they can interact with each other.
A scene calls the start and update methods of all of its Entities.
*/
class Scene {
public:
    /**
    Build the foundation of the Scene.
    @param String name to identify it.
    */
    Scene(const SceneName name);

    /**
    Clears all Entity maps.
    */
    virtual ~Scene();

    /**
    Prepares a new entity to be safely add to the scene.
    This assumes that the name is a unique identifier.
    @param String name to identify the new entity.
    @return Created new entity.
    */
    std::shared_ptr<Entity> addEntity(const EntityName name);

    /**
    Prepares an entity to be safely remove from the scene.
    This assumes that the name is a unique identifier.
    @param String name to identify the entity to be remove.
    @returns Whether the operation is successful.
    */
    bool removeEntity(const EntityName& name);

    /**
    Get a vector of all entities in the scene.
    @return Vector of Entity pointers.
    */
    std::vector<std::shared_ptr<Entity>> getEntities() const;

    /**
    Finds and returns an entity in the scene with the given name.
    If no entity with the given name is found
    or if it's deactivated, returns nullptr.
    This assumes that the name is a unique identifier.
    Returns first found entity with matching name if there are multiple.
    @param String name of the entity to be found.
    @return Entity with the given name, or nullptr if not found.
    */
    std::shared_ptr<Entity> findEntity(const EntityName& name) const;

    /**
    Get the scene name.
    @return String name.
    */
    const EntityName getName() const;

    /**
    Set the scene name to the new one.
    @param String name.
    */
    void setName(const SceneName name);

    /**
    Rename an entity.
    @param String oldName to be changed.
    @param String newName to be set.
    @returns True if succesfully renamed.
    */
    bool renameEntity(const EntityName& oldName, const EntityName& newName);

    /**
    This is only ever called once, as the scene is instantiated.
    */
    virtual void start();

    /**
    Calls the update function of all entities (and thus, 
    all components within them). 
    
    @param dt Seconds that have passed since last update.
    */
    void update(const double& dt);

    void render();

    /**
    Safely deletes deactivated entities from map.
    */
    void refresh();

    /**
    Adds new entities in buffer to map, once the current loop iteration is finished.
    */
    void processNewEntities();

    /**
    Makes this entity global so it won't be deleted on changeScenes.
    @param entity The entity to be promoted.
    @returns True if succesfully promoted.
    */
    bool promoteToGlobal(Entity* entity);

    /**
    Clears Global Entities map.
    */
    static void DeleteGlobalEntities();

protected:
    SceneName mName;
    std::vector<std::shared_ptr<Entity>> mNewEntities, mNewGlobalEntities;

    typedef std::unordered_map<EntityName, std::shared_ptr<Entity>> EntitiesMap;
    EntitiesMap mEntities;

    std::vector<std::shared_ptr<Entity>> mRenderEntities;

    //Entities that are not deleted between scenes.
    static EntitiesMap MGlobalEntities;
};

#endif