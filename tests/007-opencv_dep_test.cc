#include <opencv2/opencv.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Presence of OpenCV", "[single-file]")
{
    // Creating a simple matrix and checking its type
    cv::Mat testImage = cv::Mat::zeros(100, 100, CV_8UC3);
    
    // Checking weather the matrix was created or not
    REQUIRE(testImage.data != nullptr);
    
    REQUIRE(testImage.rows == 100);
    REQUIRE(testImage.cols == 100);
    
    // Displaying type of matrix created
    std::cout << "OpenCV Mat type: " << testImage.type() << std::endl; 
    REQUIRE(testImage.type() == CV_8UC3); //should be 16 for CV_8UC3
    
    // Testing if OpenCV properly access its version
    std::string version = cv::getVersionString();
    std::cout << "OpenCV version: " << version << std::endl;
    
    REQUIRE(!version.empty());
}
