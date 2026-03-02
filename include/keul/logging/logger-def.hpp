#pragma once

#include <format>

#include "../string/string-lib.hpp"

namespace ke
{
	/**
	 * @brief Log layers, placed in order. All layers below the specified layer will be logged.
	 */
	enum class LogLayer : uint8_t
	{
		Debug	 = 0,		/// [Debug + Info + Warning + Error + Critical] will be logged
		Info	 = 1,		/// [Info + Warning + Error + Critical] will be logged
		Warning	 = 2,		/// [Warning + Error + Critical] will be logged
		Error	 = 3,		/// [Error + Critical] will be logged
		Critical = 4,		/// [Critical] will be logged
		Off		 = 5		/// Nothing will be logged
	};


	namespace _internal
	{
		inline std::string _log_layer_to_string(const ke::LogLayer layer)
		{
			const static std::map<ke::LogLayer, std::string> s_log_layer_to_string = {
				{ke::LogLayer::Info, 		"Info"},
				{ke::LogLayer::Debug, 		"Debug"},
				{ke::LogLayer::Warning, 	"Warning"},
				{ke::LogLayer::Error, 		"Error"},
				{ke::LogLayer::Critical, 	"Critical"},
				{ke::LogLayer::Off, 		"Off"},
			};

			return s_log_layer_to_string.at(layer);
		}
	}

}

// make LogLayer std::format compatible

template <>
struct std::formatter<ke::LogLayer> : std::formatter<std::string>
{
	auto format(const ke::LogLayer& layer, std::format_context& ctx) const
	{
		std::string name = ke::to_upper(ke::_internal::_log_layer_to_string(layer));

		return std::format_to(ctx.out(), "{}", name);
	}
};