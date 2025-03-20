#pragma once
#define MIN 65
#define MAX 85
#define MIN_SPEED 0.125
#define MAX_SPEED 0.1

#define RAND_COLOR sf::Color(rand()%256, rand()%256, rand()%256)
#define RAND_RADIUS(MIN, MAX) (MIN + rand()% (MAX-MIN+1))
#define RAND_SPEED (MIN_SPEED + static_cast<float>(rand()) / RAND_MAX * (MAX_SPEED - MIN_SPEED))