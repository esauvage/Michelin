This short software tries to find the best path between 2 nodes of an oriented graph with Dijkstra's algorithm. To test it, you should have agcc. For Windows users, please use MinGW. In MinGW's installation tool, please select g++ and the dev-utils.

To compile the project, simply call : make all (for MinGW users, it's mingw32-make.exe). You'll obtain 2 executable files, "michelin" and "test".
Test wil perform some unit tests.
Michelin is the main program. it takes 3 arguments :
-i Entry node
-o End node
-m Metric for estimating the cost : you can choose between distance_km or co2_g