# Virtual-Drawing-Pad
After running this code you will be able to draw on your laptop screen using internal or extenal camera.
It involves concept like object detection using thresholding, centroid identification, area calculation, contour detection etc.

In order to run the code type in ubuntu terminal
" $ g++ -ggdb `pkg-config --cflags opencv` -o `basename draw5.cpp .cpp` draw5.cpp `pkg-config --libs opencv` "
" $ ./draw5 "
(Note: code is tested in ubuntu 14.04 with opencv2.4.9) 

