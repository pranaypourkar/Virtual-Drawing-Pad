// latest
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;

 int main()
 {
    
VideoCapture cap(0); //capture the video from laptop web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

namedWindow("m1",CV_WINDOW_AUTOSIZE);
namedWindow("m2",CV_WINDOW_AUTOSIZE);
namedWindow("m3",CV_WINDOW_AUTOSIZE);
namedWindow("m4",CV_WINDOW_AUTOSIZE);

 Mat img1,img2,img3;


 
 //Create trackbars in "window1" window
// This below function will create a bars on Control window using that you can change value 

 int LowH = 0;
 int HighH = 179;

 int LowS = 0; 
 int HighS = 255;

 int LowV = 0;
 int HighV = 255;

 int xl=0;
 int xh=255;

 cvCreateTrackbar("LowH", "m1", &LowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "m1", &HighH, 179);

 cvCreateTrackbar("LowS", "m1", &LowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "m1", &HighS, 255);

 cvCreateTrackbar("LowV", "m1", &LowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "m1", &HighV, 255);

cvCreateTrackbar("xl", "m1", &xl, 255); 
 cvCreateTrackbar("xh", "m1", &xh, 255);



int posx,posy;
int j=0;
int lastx,lasty;
//Mat result1(img2.size(),CV_8UC3,Scalar(255,255,255));

Mat result1(700,700,CV_8UC3,Scalar(255,255,255));

while (true)
    {
       

        bool bSuccess = cap.read(img1); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
//change color space to hsv
cvtColor(img1,img2,COLOR_BGR2HSV);

//to threshold an hsv image
 inRange(img2, Scalar(76,123,LowV), Scalar(HighH, HighS, HighV), img2);

//morphological opening or closing
  erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  //dilate( src, dst,getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

//findContours function:
//shows contours on black image
vector<vector<Point> > contours;
findContours(img2, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); 

if(contours.size()==0)
{
//cout<<"no object detected";
}
else
{
//cout<<"object detected"<<contours.size();
}

// Draw black contours on a white image
Mat result(img2.size(),CV_8U,Scalar(255)); // 255 white
drawContours(result,contours,-1,Scalar(0), 2); // 2 thickness

// -1 draw all contours
// 0 black lines on white
 // 0 black



/// Get the moments
vector<Moments> mu( contours.size());
for( int i = 0; i < contours.size(); i++ )
{ 
mu[i] = moments( contours[i], false );
} 



/// Get the mass centers:
vector<Point2f> mc( contours.size());
for( int i = 0; i < contours.size(); i++ )
{ 
mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00);

if((contourArea(contours[i])>=20000)&&(j==0))
{
 lastx=mu[i].m10/mu[i].m00;
 lasty=mu[i].m01/mu[i].m00;
j++;
}


//contour area
if((contourArea(contours[i])>=20000)&&(j>0)) //trial and error method
{
  
 if(j>1)
  {
   lastx=posx;
   lasty=posy;
  }
  posx= mu[i].m10/mu[i].m00;
  posy= mu[i].m01/mu[i].m00;
j++;
}

//Draw a  line from the previous point to the current point
   	 line(result1, Point(posx, posy), Point(lastx, lasty), Scalar(255,0,0), 10,8);
   	


circle(result,Point( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00),2,Scalar(xl),5); // draw black dot
//result.at<uchar>( mu[1].m10/mu[1].m00 , mu[1].m01/mu[1].m00,1)=150;
// pixel change shows segmentation error
imshow("m4",result1);
// position of mass center converted to integer
}



imshow("m3",result);
imshow("m1",img1);
//imshow("m2",img2);



if(waitKey(3)==27)
{
break;
}
}
return 0;
}
