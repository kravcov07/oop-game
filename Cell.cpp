#include "Cell.hpp"

Cell::Cell()
    : occupied_(false) {}

bool Cell::isOccupied() const { return occupied_; }

void Cell::setOccupied(bool occupied) {
    occupied_ = occupied;
}