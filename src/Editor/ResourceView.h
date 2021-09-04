#include <Reborn.h>

using namespace Reborn;

bool showResourceView = false;

void drawResourceView() {
	ImGui::Begin("Resource View", &showResourceView);
	ResourceManager& resourceManager = Application::get()->resourceManager();
	if (ImGui::BeginTable("Resources", 3)) {
		const auto& resources = resourceManager.getAllResources();
		int id = 0;
		for (auto& resource : resources) {
			ImGui::PushID(id);
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(resource.second->getTypeStr());
			ImGui::TableSetColumnIndex(1);
			ImGui::Text(resource.first.c_str());
			if (ImGui::TableSetColumnIndex(2)) {
				if (ImGui::SmallButton("Reload")) {
					resourceManager.reloadResource(resource.first);
				}
			}
			ImGui::PopID();
			id++;
		}
		ImGui::EndTable();
	}
	ImGui::End();
}