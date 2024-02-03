#pragma once
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "line.hpp"
#include<vector>
//this is a VECTOR to hold all the lines being created//
extern std::vector<Line> lines;

//-------LINE GENERATOR-------------//

void generateLines();
void generateObstacles(sf::Sprite ob[]);
void generateLife(sf::Sprite lifee);
#endif // GENERATOR_HPP
