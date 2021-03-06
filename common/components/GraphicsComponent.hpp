#pragma once

#include <string>
#include "Point.hpp"

namespace kengine {
    class GraphicsComponent : public putils::Reflectible<GraphicsComponent> {
    public:
        GraphicsComponent(const std::string & appearance = "") {
			if (!appearance.empty())
				addLayer("main", appearance);
        }

        bool repeated = false;

		struct Layer : public putils::Reflectible<Layer>, public putils::Serializable<Layer> {
			Layer(const std::string & name = "", const std::string & appearance = "",
				const putils::Rect3f & boundingBox = { {}, { 1, 1, 1 } }, float yaw = 0)
				: name(name), appearance(appearance), boundingBox(boundingBox), yaw(yaw)
			{}

			std::string name;
			std::string appearance;
			putils::Rect3f boundingBox = { {}, { 1, 1, 1 } };
			float yaw = 0;
			bool mirrored = false;

			pmeta_get_class_name(GraphicsComponentLayer);
			pmeta_get_attributes(
				pmeta_reflectible_attribute(&Layer::name),
				pmeta_reflectible_attribute(&Layer::appearance),
				pmeta_reflectible_attribute(&Layer::boundingBox),
				pmeta_reflectible_attribute(&Layer::yaw)
			);
			pmeta_get_methods();
			pmeta_get_parents();
		};

		std::vector<Layer> layers;

		Layer & addLayer(const std::string & name, const std::string & appearance) {
			layers.emplace_back(name, appearance);
			return layers.back();
		}

		void removeLayer(const std::string & name) {
			const auto it = std::find_if(layers.begin(), layers.end(), [&name](auto && layer) { return layer.name == name; });
			if (it != layers.end())
				layers.erase(it);
		}

		bool hasLayer(const std::string & name) const {
			return std::find_if(layers.begin(), layers.end(), [&name](auto && layer) { return layer.name == name; }) != layers.end();
		}

		Layer & getLayer(const std::string & name) {
			const auto it = std::find_if(layers.begin(), layers.end(), [&name](auto && layer) { return layer.name == name; });
			return *it;
		}

        /*
         * Reflectible
         */

    public:
        pmeta_get_class_name(GraphicsComponent);
        pmeta_get_attributes(
                pmeta_reflectible_attribute(&GraphicsComponent::repeated),
                pmeta_reflectible_attribute(&GraphicsComponent::layers)
        );
		pmeta_get_methods(
			pmeta_reflectible_attribute(&GraphicsComponent::addLayer),
			pmeta_reflectible_attribute(&GraphicsComponent::removeLayer),
			pmeta_reflectible_attribute(&GraphicsComponent::getLayer),
			pmeta_reflectible_attribute(&GraphicsComponent::hasLayer)
		);
		pmeta_get_parents();
    };
}
