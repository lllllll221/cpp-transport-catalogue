#pragma once

#include <cstddef>
#include <unordered_map>

#include <transport_catalogue.pb.h>
#include <map_renderer.pb.h>
#include "request_handler.h"
#include "domain.h"
#include "svg.h"

namespace serialization {

    struct ColorSetter {
		transport_catalogue_serialize::Color& proto_color;
		void operator()(std::monostate) const;
		void operator()(const std::string& color) const;
		void operator()(const svg::Rgb& color) const;
		void operator()(const svg::Rgba& color) const;
    };

	class Serializer {
	public:
		explicit Serializer(
			const std::string& file_name,
			transport_catalogue::request_handler::RequestHandler& handler,
            transport_catalogue::TransportCatalogue& db,
			transport_catalogue::renderer::MapRenderer& renderer,
			transport_catalogue::transport_router::TransportRouter& router
		);
		void SerializeTransportCatalogue() const;
		void DeserializeTransportCatalogue();
	private:
		transport_catalogue::request_handler::RequestHandler& handler_;
		transport_catalogue::TransportCatalogue& db_;
		transport_catalogue::renderer::MapRenderer& renderer_;
        transport_catalogue::transport_router::TransportRouter& router_;
		std::string file_name_;

		static void SetProtoStop(
			transport_catalogue_serialize::Stop& proto_stop,
			const transport_catalogue::domain::Stop& stop,
			const std::size_t id
		);
		static void SetProtoBus(
			transport_catalogue_serialize::Bus& proto_bus,
			const transport_catalogue::domain::Bus& bus,
			const std::unordered_map<std::string_view, std::size_t>& stop_name_to_id,
			const std::size_t id
		);
        static void SetColor(svg::Color& color, const transport_catalogue_serialize::Color& proto_color);
        static transport_catalogue::renderer::RenderSettings GetRenderSettings(const transport_catalogue_serialize::RenderSettings& proto_settings);

		transport_catalogue_serialize::TransportCatalogue GetProtoTransportCatalogue() const;

        transport_catalogue_serialize::RenderSettings GetProtoRenderSettings() const;

        transport_catalogue_serialize::TransportRouter GetProtoRouter(
            const std::unordered_map<std::string_view, std::size_t>& stop_name_to_id,
            const std::unordered_map<std::string_view, std::size_t>& bus_name_to_id
        ) const;
	};

}
