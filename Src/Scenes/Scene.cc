#include "Scene.h"
#include "../EntityComponent/Entity.h"

#include <iostream>
#include <algorithm>

Scene::Scene(const SceneName name) : mName(name)
{
    std::cout << " > Scene ( " << mName << " ) created." << std::endl;
}

Scene::~Scene() {
	mNewEntities.clear();
	mNewGlobalEntities.clear();
	mEntities.clear();

    std::cout << " >>> Scene ( " << mName << " ) deleted..." << std::endl;
}

std::shared_ptr<Entity> Scene::addEntity(const EntityName name) {
	auto e = std::make_shared<Entity>(this, name);
	if (e != nullptr) {
		mNewEntities.push_back(e);
	}
	return e;
}

bool Scene::removeEntity(const EntityName& name) {
	auto it = mEntities.find(name);
	if (it != mEntities.end()) {
		it->second->destroy();
		return true;
	}

	it = MGlobalEntities.find(name);
	if (it != MGlobalEntities.end()) {
		it->second->destroy();
		return true;
	}

	return false;
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities() const {
	std::vector<std::shared_ptr<Entity>> entities;
	entities.reserve(mEntities.size());
	for (auto& kv : mEntities) {
		entities.push_back(kv.second);
	}
	for (auto& kv : MGlobalEntities) {
		entities.push_back(kv.second);
	}
	return entities;
}

std::shared_ptr<Entity> Scene::findEntity(const EntityName& name) const {
	auto it = mEntities.find(name);
	if (it != mEntities.end() && it->second->isActive()) {
		return it->second;
	}
	it = MGlobalEntities.find(name);
	if (it != MGlobalEntities.end() && it->second->isActive()) {
		return it->second;
	}
	return std::shared_ptr<Entity>(nullptr);
}

const EntityName Scene::getName() const
{
	return mName;
}

void Scene::setName(const SceneName name)
{
	mName = name;
}

bool Scene::renameEntity(const EntityName& oldName, const EntityName& newName) {
	auto it = mEntities.find(oldName);
	auto dst = mEntities.find(newName);
	if (it != mEntities.end() && oldName != newName && dst == mEntities.end()) {
		it->second->setName(newName);
		mEntities.emplace(newName, std::move(it->second));
		mEntities.erase(it);
		return true;
	}

	it = MGlobalEntities.find(oldName);
	dst = MGlobalEntities.find(newName);
	if (it != MGlobalEntities.end() && oldName != newName && dst == MGlobalEntities.end()) {
		it->second->setName(newName);
		MGlobalEntities.emplace(newName, std::move(it->second));
		MGlobalEntities.erase(it);
		return true;
	}

	return false;
}

void Scene::start() {
	for (const auto& kv : mEntities)
		kv.second->start();
}

void Scene::update(const double& dt) {
	for (const auto& kv : MGlobalEntities)
		kv.second->update(dt);

	for (const auto& kv : mEntities) {
		kv.second->update(dt);
	}
}

bool cmpCondition(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
	return a.get()->getDepth() < b.get()->getDepth();
}

void Scene::render() {
	// Before rendering, order all entities (Z-COORD)
	// std::sort(MGlobalEntities.begin(), MGlobalEntities.end(), cmpCondition);
	for (const auto& kv : MGlobalEntities)
		mRenderEntities.push_back(kv.second);

	for (const auto& kv : mEntities)
		mRenderEntities.push_back(kv.second);
	

	std::sort(mRenderEntities.begin(), mRenderEntities.end(), cmpCondition);

	for (const auto& re : mRenderEntities){
		re.get()->render();
	}

	mRenderEntities.clear();
}

void Scene::refresh() {
	// std::erase_if(mEntities, [](const auto& kv) {
	// 	return !kv.second->isActive();
	// });

	// std::erase_if(MGlobalEntities, [](const auto& kv) {
	// 	return !kv.second->isActive();
	// });
}

void Scene::processNewEntities()
{
	for (auto& entityPtr : mNewGlobalEntities) {
		MGlobalEntities.emplace(entityPtr->getName(), entityPtr);
		mEntities.erase(entityPtr->getName());
	}

	mNewGlobalEntities.clear();

	for (auto& entityPtr : mNewEntities)
		mEntities.emplace(entityPtr->getName(), entityPtr);

	for (auto& entityPtr : mNewGlobalEntities)
		entityPtr->start();

	
	for (auto& entityPtr : mNewEntities)
		entityPtr->start();


	mNewEntities.clear();
}

bool Scene::promoteToGlobal(Entity* entity)
{
	auto it = mEntities.find(entity->getName());
	if (it == mEntities.end())
		return false;
	mNewGlobalEntities.push_back(it->second);
	return true;
}

void Scene::DeleteGlobalEntities()
{
	MGlobalEntities.clear();
}

Scene::EntitiesMap Scene::MGlobalEntities;