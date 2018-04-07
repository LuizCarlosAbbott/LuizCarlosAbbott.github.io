#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image, imageaux;

  image= imread("pernapato.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu pernapato.png" << endl;

  imageaux= imread("pernapato.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!imageaux.data)
    cout << "nao abriu pernapato.png aux" << endl;

  for(int i=0;i<(image.size().height)/2;i++){
    for(int j=0;j<(image.size().width)/2;j++){
      image.at<uchar>(i,j) = imageaux.at<uchar>(i + (image.size().height)/2, j + (image.size().width)/2);
    }
  }
  for(int i=(image.size().height)/2;i<(image.size().height);i++){
    for(int j=(image.size().width)/2;j<(image.size().width);j++){
      image.at<uchar>(i,j) = imageaux.at<uchar>(i - (image.size().height)/2, j - (image.size().width)/2);
    }
  }
  for(int i=0;i<(image.size().height)/2;i++){
    for(int j=(image.size().width)/2;j<(image.size().width);j++){
      image.at<uchar>(i,j) = imageaux.at<uchar>(i + (image.size().height)/2, j - (image.size().width)/2);
    }
  }
  for(int i=(image.size().height)/2;i<(image.size().height);i++){
    for(int j=0;j<(image.size().width)/2;j++){
      image.at<uchar>(i,j) = imageaux.at<uchar>(i - (image.size().height)/2, j + (image.size().width)/2);
    }
  }
  
  namedWindow("janela", WINDOW_AUTOSIZE);

  imshow("janela", image);  
  waitKey();
  return 0;
}
