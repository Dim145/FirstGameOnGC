@echo off

if "%2" == "base"      img2gb tileset --output-c-file="./src/%1.c" --output-header-file="./src/%1.h" %3 --output-image="./img/%1.png" %4 --deduplicate "./imgRepos/%1.png"
if "%2" == "duplicate" img2gb tileset --output-c-file="./src/%1.c" --output-header-file="./src/%1.h" --output-image="./img/%1.png" %3 %4 "./imgRepos/%1.png"
if "%2" == "sprite816" img2gb tileset --output-c-file="./src/%1.c" --output-header-file="./src/%1.h" --output-image="./img/%1.png" %3 --sprite8x16 %4 "./imgRepos/%1.png"