#include <opencv2/highgui.hpp>
#include <iostream>

cv::Mat BGR2HSV(cv::Mat& image)
{
    cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_32FC3);

    for (int i = 0; i < image.rows; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            float r = image.at<cv::Vec3b>(i, j)[2] * 1.0 / 255;
            float g = image.at<cv::Vec3b>(i, j)[1] * 1.0 / 255;
            float b = image.at<cv::Vec3b>(i, j)[0] * 1.0 / 255;

            float max = fmax(r, fmax(g, b));
            float min = fmin(r, fmin(g, b));

            float h;
            if (max == min)
                h = 0;
            else if (min == b)
                h = 60 * (g - r) / (max - min) + 60;
            else if (min == r)
                h = 60 * (b - g) / (max - min) + 180;
            else if (min == g)
                h = 60 * (r - b) / (max - min) + 300;

            float s = max - min;
            float v = max;

            out.at<cv::Vec3f>(i, j)[0] = h;
            out.at<cv::Vec3f>(i, j)[1] = s;
            out.at<cv::Vec3f>(i, j)[2] = v;
        }
    }

    return out;
}

cv::Mat inverseHue(cv::Mat image) 
{
    for (int i = 0; i < image.rows; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            image.at<cv::Vec3f>(i, j)[0] = 
                fmod(image.at<cv::Vec3f>(i, j)[0] + 180, 360);
        }
    }
    
    return image;
}

cv::Mat HSV2BGR(cv::Mat& image)
{
    cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);

    for (int i = 0; i < image.rows; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            float h = image.at<cv::Vec3f>(i, j)[0];
            float s = image.at<cv::Vec3f>(i, j)[1];
            float v = image.at<cv::Vec3f>(i, j)[2];

            float c = s;
            float h_ = h / 60;
            float x = c * (1 - fabs(fmod(h_, 2) - 1));

            float r = v - c;
            float g = v - c;
            float b = v - c;

            if (h_ < 1)
            {
                r += c;
                g += x;
            }
            else if (h_ < 2)
            {
                r += x;
                g += c;
            }
            else if (h_ < 3)
            {
                g += c;
                b += x;
            }
            else if (h_ < 4)
            {
                g += x;
                b += c;
            }
            else if (h_ < 5)
            {
                r += x;
                b += c;
            }
            else if (h_ < 6)
            {
                r += c;
                b += x;
            }

            out.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(b * 255);
            out.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(g * 255);
            out.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(r * 255);
        }
    }

    return out;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {   
        std::cerr << "Params is error!" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat hsvimage = BGR2HSV(image);
    cv::Mat inversehueimage = inverseHue(hsvimage);
    cv::Mat bgrimage = HSV2BGR(inversehueimage);

    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("ImageHSV", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("ImageInverseHue", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("ImageBGR", cv::WINDOW_AUTOSIZE);

    cv::imshow("Image", image);
    cv::imshow("ImageHSV", hsvimage);
    cv::imshow("ImageInverseHue", inversehueimage);
    cv::imshow("ImageBGR", bgrimage);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return EXIT_SUCCESS;
}