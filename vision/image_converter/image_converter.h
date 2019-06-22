#include "nodehandle.h"

class Coord
{
  public:
    Coord(int x_, int y_) : x(x_), y(y_) {}
    Coord operator+(const Coord &addon) const { return Coord(x + addon.x, y + addon.y); }
    int get_x() const { return x; }
    int get_y() const { return y; }

  private:
    int x, y;
};
class Vision : protected NodeHandle
{
  public:
    Vision(string topic);
    ~Vision();
    cv::Mat get_source();

  private:
    ros::NodeHandle nh;
    ros::Subscriber image_sub;
    //void imageCb(const sensor_msgs::CompressedImageConstPtr &msg);
    void imageCb(const sensor_msgs::ImageConstPtr& msg);
    cv::Mat CutFrame(Mat frame, int upx, int upy, int downx, int downy);
    cv::Mat DrawMonior(Mat frame, Object ball, Color index);
    double Rate();
    double FrameRate;
    cv::Mat source;
    cv::Mat monitor;
    cv::Mat mask;

    Object ColorMoldel(Color index);
    Object SearchObject(Mat mask);
    bool is_white(Mat &img, const Coord &c) { return img.data[3 * (c.get_y() * img.cols + c.get_x())] == 255; }
    Mat convertTo3Channels(const Mat &binImg);
};
