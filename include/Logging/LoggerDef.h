#pragma once

#include <format>

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

}

// make LogLayer std::format compatible

template <>
struct std::formatter<ke::LogLayer>
{
	constexpr auto parse(format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const ke::LogLayer& layer, std::format_context& ctx) const
	{
		std::string name;

		switch (layer)
		{
		case ke::LogLayer::Debug:
			name = "DEBUG";
			break;
		case ke::LogLayer::Info:
			name = "INFO";
			break;
		case ke::LogLayer::Warning:
			name = "WARNING";
			break;
		case ke::LogLayer::Error:
			name = "ERROR";
			break;
		case ke::LogLayer::Critical:
			name = "CRITICAL";
			break;
		case ke::LogLayer::Off:
			name = "OFF";
			break;
		default:
			name = "Unknown";
			break;
		}

		return std::format_to(ctx.out(), "{}", name);
	}
};