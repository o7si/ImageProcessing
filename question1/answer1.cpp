#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Params is error!" << std::endl;        
        return EXIT_FAILURE;
    }
    
    cv::Mat image = cv::imread(argv[1]);
    cv::Mat copyimage = image.clone();

    for (int i = 0; i < copyimage.rows; ++ i) 
    {
        for (int j = 0; j < copyimage.cols; ++ j)
        {
            // BGR -> RGB
            int blue  = copyimage.at<cv::Vec3b>(i, j)[0];
            int green = copyimage.at<cv::Vec3b>(i, j)[1];
            int red   = copyimage.at<cv::Vec3b>(i, j)[2];

            copyimage.at<cv::Vec3b>(i, j)[0] = red;
            copyimage.at<cv::Vec3b>(i, j)[1] = green;
            copyimage.at<cv::Vec3b>(i, j)[2] = blue;
        }
    }

    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", image);

    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", copyimage);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return EXIT_SUCCESS;
}