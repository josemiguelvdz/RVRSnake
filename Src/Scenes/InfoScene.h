#pragma once
#include <string>
#include <unordered_map>

typedef std::string SceneName, EntityName, ComponentName;
typedef std::unordered_map<EntityName, ComponentName> InfoEntity;