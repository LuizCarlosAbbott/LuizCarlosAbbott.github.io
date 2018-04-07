#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  int p1x = 0;
  int p1y = 0;
  int p2x = 0;
  int p2y = 0;


  image= imread("pernapato.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu imagem" << endl;

  cout << "Altura da imagem: " << image.size().height << endl;
  cout << "Largura da imagem: " << image.size().width << endl;

  cout << "Digite as coordenadas do ponto P1(x,y)" << endl << "X: ";
  cin >> p1x;
  cout << endl << "Y: ";
  cin >> p1y;
  cout << endl;

  while(p1x > image.size().width || p1y > image.size().height){
  cout << "Digite as coordenadas do ponto P1(x,y)" << endl << "X: ";
  cin >> p1x;
  cout << endl << "Y: ";
  cin >> p1y;
  cout << endl;
  }
  
  cout << "Digite as coordenadas do ponto P2(x,y)" << endl << "X: ";
  cin >> p2x;
  cout << endl << "Y: ";
  cin >> p2y;
  cout << endl;

  while(p2x > image.size().width || p2y > image.size().height){
  cout << "Digite as coordenadas do ponto P2(x,y)" << endl << "X: ";
  cin >> p2x;
  cout << endl << "Y: ";
  cin >> p2y;
  cout << endl;
  }

  if(p1x > p2x){
  int aux;
  aux = p1x;
  p1x = p2x;
  p2x = aux;
  }

  if(p1y > p2y){
  int aux;
  aux = p1x;
  p1y = p2y;
  p2y = aux;
  }

  for(int i= p1y;i<p2y;i++){
    for(int j=p1x;j<p2x;j++){
      image.at<uchar>(i,j)=255 - image.at<uchar>(i,j);
    }
  }
  namedWindow("janela", WINDOW_AUTOSIZE);
  imshow("janela", image);  
  waitKey();
  return 0;
}
