#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include <bitset>
#include <utility>
#include <string>

#include <thirdParty/imgui/imgui.h>
#include <thirdParty/imgui/imgui_internal.h>

#include "Core.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

#include "Components/Transform3DComponent.h"
#include "Components/ImGuiComponent.h"
#include "Components/RenderComponent.h"

#include "Event/ApplicationShouldCloseEvent.h"
#include "Event/KeyPressedEvent.h"

#include "Resources/TextResource.h"

#include "EntryPoint.h"
