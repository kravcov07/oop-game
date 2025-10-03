#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();
    bool isOccupied() const;
    void setOccupied(bool occupied);

private:
    bool occupied_;
};

#endif