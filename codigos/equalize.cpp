#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, imggrayscale, imgequalize;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat hist, histN;
  int nbins = 128;
  int flag = 0;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;

  Mat histImg(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat histImgN(histh, histw, CV_8UC1, Scalar(0,0,0));

  while(1){
    cap >> image;
    cvtColor(image, imggrayscale, CV_BGR2GRAY);
    equalizeHist(imggrayscale,imgequalize);

    calcHist(&imggrayscale, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&imgequalize, 1, 0, Mat(), histN, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(histN, histN, 0, histImgN.rows, NORM_MINMAX, -1, Mat());

    histImg.setTo(Scalar(0));
    histImgN.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImg,
           Point(i, histh),
           Point(i, histh-cvRound(hist.at<float>(i))),
           Scalar(255, 255, 255), 1, 8, 0);
    }
    for(int j = 0; j<nbins; j++){
      line(histImgN,
           Point(j, histh),
           Point(j, histh-cvRound(histN.at<float>(j))),
           Scalar(255, 255, 255), 1, 8, 0);
    }
    histImgN.copyTo(imgequalize(Rect(0, 0       ,nbins, histh)));
    histImg.copyTo(imggrayscale(Rect(0, 0       ,nbins, histh)));

    if(flag == 0){
    imshow("normal", imggrayscale);
    waitKey();
    flag = 1;
    imshow("equalizada", imgequalize);
    }
    if(flag == 1){
    imshow("normal", imggrayscale);
    imshow("equalizada", imgequalize);
    }

    if(waitKey(30) >= 0) break;
  }
  return 0;
}
