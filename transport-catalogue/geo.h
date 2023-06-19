#pragma once

#include <cmath>

//namespace transport_catalogue {

namespace geo {

struct Coordinates {
    Coordinates() = default;
    Coordinates(double lt, double lg)
        : lat(lt), lng(lg) {}

    double lat; // Широта
    double lng; // Долгота

    bool operator==(const Coordinates& other) const {
        return lat == other.lat && lng == other.lng;
    }
    bool operator!=(const Coordinates& other) const {
        return !(*this == other);
    }
};

double ComputeDistance(Coordinates from, Coordinates to);

}//namespace geo