@echo off
img2gb tilemap --output-c-file="./src/%1Map.c" --output-header-file="./src/%1Map.h" "./img/breakout-tileset.png" "./imgRepos/%1.png"