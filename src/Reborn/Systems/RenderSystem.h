#pragma once
#include <Platform.h>
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Utils.h>

#ifdef REBORN_OPENGL
#include <Graphics/Platform/OpenGL/GLRenderer.h>
#endif // REBORN_OPENGL

namespace Reborn {
	class RenderSystem : public EntitySystem {
	public:
		RenderSystem(EntityManager& _entityManager): entityManager(_entityManager) {
			setRequirements<Transform3DComponent, RenderComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

#ifdef REBORN_OPENGL
		void process(GLRenderer& renderer) {			
			const Matrix4& proj = renderer.getCamera().getViewProjection();

			for (Entity entity : getManagedEntities()) {
				auto& transform3DComponent = entityManager.getComponent<Transform3DComponent>(entity);
				auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
				//auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(cameraControllerEntity);
				//const Matrix4& model = transform3DComponent.getModelMatrix();
				const Matrix4 world = transform3DComponent.world;
				Matrix4 mvp = proj * world;

				for (int i = 0; i < renderComponent.VAOs.size(); i++) {
					renderComponent.materials[i].setParameter(RB_MATPARAM_MODEL_TO_CLIP, mvp);
					renderComponent.materials[i].setParameter(RB_MATPARAM_MODEL_TO_WORLD, world);
					renderComponent.materials[i].setParameter(RB_MATPARAM_LIGHT_COLOR, Vector3(1.f));
					renderComponent.materials[i].setParameter(RB_MATPARAM_AMBIENT, Vector3(0.f));
					renderComponent.materials[i].setParameter(RB_MATPARAM_OUTLINED, 1.f);
					setupMaterial(renderer, renderComponent.materials[i]);// renderComponent.materials[i].setup(renderer);
					renderer.drawVAO(renderComponent.VAOs[i]);
				}
			}
		};
#endif // REBORN_OPENGL

	private:


#ifdef REBORN_OPENGL
		void setupMaterial(GLRenderer& renderer, const Material& material) const
		{
			using Reborn::MaterialParameter;

			const GLShaderProgram& glProgram = static_cast<const GLShaderProgram&>(*material.getProgram());
			renderer.useProgram(glProgram);

			const MaterialParameters& parameters = material.getParameters();
			for (auto it = parameters.begin(); it != parameters.end(); it++)
			{
				const MaterialParameter& param = it->second;
				const char* paramName = it->first.c_str();
				switch (param.type)
				{
				case MaterialParameter::Type::Float:
					renderer.setUniform(glProgram, paramName, param.value.fValue);
					break;
				case MaterialParameter::Type::Int:
					renderer.setUniform(glProgram, paramName, param.value.iValue);
					break;
				case MaterialParameter::Type::tVector2:
					renderer.setUniform(glProgram, paramName, param.value.vec2Value);
					break;
				case MaterialParameter::Type::tVector3:
					renderer.setUniform(glProgram, paramName, param.value.vec3Value);
					break;
				case MaterialParameter::Type::tVector4:
					renderer.setUniform(glProgram, paramName, param.value.vec4Value);
					break;
				case MaterialParameter::Type::tMatrix2:
					renderer.setUniform(glProgram, paramName, param.value.mat2Value);
					break;
				case MaterialParameter::Type::tMatrix3:
					renderer.setUniform(glProgram, paramName, param.value.mat3Value);
					break;
				case MaterialParameter::Type::tMatrix4:
					renderer.setUniform(glProgram, paramName, param.value.mat4Value);
					break;
				case MaterialParameter::Type::Undefined:
					LOG_ERROR << "file " << __FILE__ << " line " << __LINE__ << ": Undefined material parameter type";
					break;
				default:
					LOG_ERROR << "file " << __FILE__ << " line " << __LINE__ << ": This shouldn't happend";
					break;
				}
			}
		}
#endif // REBORN_OPENGL

		EntityManager& entityManager;
	};
}