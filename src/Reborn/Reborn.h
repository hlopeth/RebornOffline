#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include <bitset>
#include <utility>

#include <thirdParty/imgui/imgui.h>
#include <thirdParty/imgui/imgui_internal.h>

#include "Core.h"

#include "Components/Transform3DComponent.h"
#include "Components/ImGuiComponent.h"

#include "Event/ApplicationShouldCloseEvent.h"
#include "Event/KeyPressedEvent.h"

#include "EntryPoint.h"
