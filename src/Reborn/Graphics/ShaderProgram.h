#pragma once
#include "Platform.h"

namespace Reborn {
	class ShaderProgram {
	public:
		ShaderProgram() = default;
		ShaderProgram(const std::string& _vertexSource, const std::string& _fragmentSource) {
			vertexSource = _vertexSource;
			fragmentSource = _fragmentSource;
		};
		std::string vertexSource;
		std::string fragmentSource;
		UIntValue id = -1;
	};
}