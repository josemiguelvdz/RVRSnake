/**
This undefined class interface that is meant to be the root 
for any behavior designed as a component.
*/

#pragma once

#ifndef __ENTITYCOMPONENT_COMPONENT
#define __ENTITYCOMPONENT_COMPONENT

#include <string>

class Entity;

/**
Components define Entities behaviour by defining
start and update methods.
*/
class Component {
public:

    bool enabled = true;

    /**
    Build the foundation of the Component.
    */
    Component();

    /**
    This method is meant to be the definition
    of the dynamic memory that has to be safely delete.
    */
    virtual ~Component();

    /**
    Set the associated entity to the component.
    @param Entity to which it belongs.

    This method is meant to be use at the same time as start,
    because it's not recomended to switch the entity at execution.
    */
    void setEntity(Entity* e);

    /**
    Get the entity associated reference.
    @return Reference to the entity.
    */
    Entity* getEntity();

    /**
    This method is only ever called once.
    This must be called at the instantiation of the script.
    */
    virtual void start();

    /**
    This method is meant to be the definition 
    of those updates that has to be processed
    at the begining of the game cycle.

    Almost all the logic updates.

    @param dt Seconds that have passed since last update.
    */
    virtual void update(const double& dt);

    /**
    This method is meant to be the definition 
    of those updates that has to be processed
    at the end of the game cycle.

    For example: render and collisions.

    @param dt Seconds that have passed since last update.
    */
    virtual void lateUpdate(const double& dt);

    /**
    Executed when a collision starts.
    @param other Entity that collides with this entity.
    */
    virtual void onCollisionEnter(Entity* other);
    /**
    Executed when a collision starts and every frame it lasts.
    @param other Entity that collides with this entity.
    */
    virtual void onCollisionStay(Entity* other);
    /**
    Executed when a collision ends.
    @param other Entity that collides with this entity.
    */
    virtual void onCollisionExit(Entity* other);

    /**
	 Set name to mesh (renderMesh in rendermanager array).
		@param name: name for map and for entity that attached in node
	*/

	void setName(std::string name);

	/**
	Set it is static entity or not
	*/
	std::string getName();

protected:
    Entity* mEntity;

    std::string mName;
};

#endif