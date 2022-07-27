#include "Graphics.h"
#include <algorithm>

using namespace cv;
using namespace std;

//////////////////////////////////////////////////

SingleAnimationGraphics::SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic)
    :_animation(animPtr), _currFrameIdx(0)
    , _isCyclic(isCyclic)
{    
}


cv::Mat SingleAnimationGraphics::getCollisionMask()
{
    return _animation->getFrame(_currFrameIdx).mask;
}

void SingleAnimationGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    drawFrame(_animation->getFrame(_currFrameIdx), canvas, topLeft);
}

void SingleAnimationGraphics::reset(int code)
{
    _currFrameIdx = 0;
}

bool SingleAnimationGraphics::update()
{
    bool hasFinished = (_currFrameIdx == _animation->numFrames() - 1);
    if (_isCyclic)
        _currFrameIdx = (_currFrameIdx + 1) % _animation->numFrames();
    else 
        _currFrameIdx = min<int>(_currFrameIdx + 1, (int)_animation->numFrames() - 1);

    return hasFinished;
}
///////////////////////////////////////////////////
LivesGraphics::LivesGraphics(Frame const& singleLife):_singleLife(singleLife), _livesCount(4)
{
 }

cv::Mat LivesGraphics::getCollisionMask() {

   return cv::Mat();
}

void LivesGraphics:: draw(cv::Mat& canvas, cv::Point const& topLeft) {
   
    drawFrame(_singleLife, canvas, topLeft);

 }

void LivesGraphics::reset(int code ) {

    _livesCount = code;
}
//@i 
bool LivesGraphics::update() {

    return false;

}
//////////////////////////////////////////////////

void exampleOfPutText()
{
    Mat image = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
    string text = "score: ";
    int score = 465;
    string moreText = to_string(score);
    text = text + moreText;
    Point topLeft(50, 50);
    int fontFace = FONT_HERSHEY_SIMPLEX; // normal size sans - serif font
    // other options for fontFace:
    FONT_HERSHEY_PLAIN;// small size sans - serif font
    FONT_HERSHEY_DUPLEX;// normal size sans - serif font(more complex than FONT_HERSHEY_SIMPLEX)
    FONT_HERSHEY_COMPLEX; // normal size serif font
    FONT_HERSHEY_TRIPLEX; //normal size serif font(more complex than FONT_HERSHEY_COMPLEX)
    FONT_HERSHEY_COMPLEX_SMALL; //smaller version of FONT_HERSHEY_COMPLEX
    FONT_HERSHEY_SCRIPT_SIMPLEX; //hand - writing style font
    FONT_HERSHEY_SCRIPT_COMPLEX;// more complex variant of FONT_HERSHEY_SCRIPT_SIMPLEX
    double fontScale = 2; // Font scale factor that is multiplied by the font-specific base size.
    Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255); 
    int thickness = 2;
    int lineType = FILLED;
    // other options for line type:
    LINE_4; LINE_8; LINE_AA;

    // finally:
    putText(image, text, topLeft, fontFace, fontScale, color, thickness, lineType);
    
    imshow("test", image);
    waitKey();//waiting forever till some key is hit.
}
/////////////////////////////////////////////////
ScoresGraphics::ScoresGraphics(float fontScale, int score, int fontFace) {
   
    _fontScale = fontScale;
    _score = score;
    _fontFace = fontFace;
}
cv::Mat ScoresGraphics::getCollisionMask() {

    return cv::Mat();
}
void ScoresGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft) {
    string text = "score: ";
    int score = _score;
    string moreText = to_string(score);
    text = text + moreText;
    Scalar color(/*Blue between 0...255 =*/130,/*Green between 0...255 =*/200,/*Red between 0...255 =*/255);
    int thickness = 2;
    int lineType = LINE_4;
    putText(canvas, text, topLeft, _fontFace,  _fontScale, color, thickness, lineType);
}

void ScoresGraphics::reset(int code) {

    _score = code;

}
bool ScoresGraphics::update() {

    return false;

}
