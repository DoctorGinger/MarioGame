#include "Animation.h"
#include <opencv2/opencv.hpp>

// before you start: open SeminarMario project properties, go to 
// Debugging -> Environment
// set the following value:
// PATH=$(PATH);../OpenCV_451/bin
// hit Ctrl + F5 and see a walking lady. that's our hero!
// press Esc to exit.
// read carefully the comments below - it contains explanations and instructions.
// and do the exercises.



//approximatly
// 1.
// draws an animation of our hero that ducks in place, and stays down till you 
// press the 'w' key. (if (key == 'w'))
void duck() {
	Animation animation(R"(../Animations/Hero/duckDown)");
	Animation animation_stay(R"(../Animations/Hero/duckStay)");
	Animation animation_stand(R"(../Animations/Hero/standAfterDuck)");
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	for (int i = 0; i < animation.numFrames(); i++)
	{
		Frame const& frame = animation.getFrame(i);
		cv::Mat canvas = background.clone();
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 3 / 4);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		int key = cv::waitKey(100);


	}
	bool isToExit = false;
	while (false == isToExit)
	{
		//for (int i = 0; i < animation_stay.numFrames(); i++)
		//{
		Frame const& frame = animation_stay.getFrame(0);
		cv::Mat canvas = background.clone();
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 3 / 4);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		int key = cv::waitKey(100);

		if (key == 'w') // if you pressed ESC key
		{
			isToExit = true;
		}


	}
	for (int i = 0; i < animation_stand.numFrames(); i++)
	{
		Frame const& frame = animation_stand.getFrame(i);
		cv::Mat canvas = background.clone();
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 3 / 4);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		int key = cv::waitKey(100);


	}



}

// 2.
// draws an animation of our hero that walks to the right, and ACTUALLLY MOVES RIGHT
// with a constant speed, of (1/10)*(image width) per 100 milliseconds (=0.1 second).
void walkRight() {
	int go = 0;
	Animation animation(R"(../Animations/Hero/runRight)");

	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);

	// Draw
	bool isToExit = false;
	while (false == isToExit)
	{
		for (int i = 0; i < animation.numFrames(); i++)
		{
			if( go<42  ){
			go++;
			}
			Frame const& frame = animation.getFrame(i);

			cv::Mat canvas = background.clone();
			cv::Point topLeft(canvas.size().width / 2 + (canvas.size().width / 100) * go, canvas.size().height * 3 / 4);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			int key = cv::waitKey(100);
			if (key == 'd') {

				isToExit = true;
			}
		}

	}






}

// 3.
// draw our hero jumps up and right, and stays standing after jump finishes.
void jumpRight() {
	Animation animation(R"(../Animations/Hero/jump)");
	//Animation animation1(R"(../Animations/Hero/runRight)");

	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);

	// Draw


	for (int i = 0; i < animation.numFrames(); i++)
	{
		Frame const& frame = animation.getFrame(i);

		cv::Mat canvas = background.clone();
		cv::Point topLeft(canvas.size().width / 2 * 1.1, canvas.size().height * 0.6);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		int key = cv::waitKey(30);

	}
	for (int i = animation.numFrames() - 1; i >= 0; i--)
	{
		Frame const& frame = animation.getFrame(i);

		cv::Mat canvas = background.clone();
		cv::Point topLeft(canvas.size().width / 2 * 1.17, canvas.size().height * 0.75);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		int key = cv::waitKey(100);

	}
}

void stop() {
	Animation animation(R"(../Animations/Hero/idle)");
	//Animation animation1(R"(../Animations/Hero/runRight)");

	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);


	bool isToExit = false;
	while (false == isToExit)
	{
		for (int i = 0; i < animation.numFrames(); i++)
		{
			//if( frame.image.size().width)

			Frame const& frame = animation.getFrame(i);

			cv::Mat canvas = background.clone();
			cv::Point topLeft(canvas.size().width / 2 , canvas.size().height * 3 / 4);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			int key = cv::waitKey(100);
			if (key != 'a') {

				isToExit = true;
			}
		}


	}
}
	// 4.
	// write a main() that:
	// when user presses 'd' - hero walks right
	// when user presses 's' - hero ducks
	// when user presses 'w' - hero jumps
	// when user presses 'a' - hero stops (if it was walking right before)

	// 5.
	// in walkRight - when hero reaches the canvas boundery - don't let it go outside of image.
	// force the hero x coordinate to be such that we'll see her.
	// hint: you can get hero image cv::Mat with frame.image

	// 6.
	// do the same with jumpRight




	int main1()
	{

		// Animation is a class we wrote for saving you the handling with the 
		// details of image processing and focusing on code design. iyH we'll get 
		// to it in the image processing course.
		Animation animation(R"(../Animations/Hero/runRight)");

		// OpenCV is a popular image processing and computer vision library.
		// it is not part of the C++ language, but it's written in C++.
		// in this project we integrated it for you.
		// The class that represents an image in OpenCV is Mat (i.e. Matrix),
		// and it's defined inside namespace cv. So the full name is cv::Mat.
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);

		// Draw
		bool isToExit = false;
		while (false == isToExit)
		{
			for (int i = 0; i < animation.numFrames(); i++)
			{
				Frame const& frame = animation.getFrame(i);
				// create a copy of the original backgrount - not to "dirty" it.
				cv::Mat canvas = background.clone();
				// the point of the canvas where we would like to place the top left corner 
				// of our frame. NOTE: the y axis on the screen goes from top to bottom.
				cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 3 / 4);
				drawFrame(frame, canvas, topLeft);
				// show what we've got (use BOTH of the following two commands):
				cv::imshow("test", canvas);
				// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
				// (you MUST call it after cv::imshow. will discuss why in image processing).
				int key = cv::waitKey(100);

				switch (key)
				{
				case 's':duck(); break;
				case 'w':jumpRight(); break;
				case 'd':walkRight(); break;
				case 'a':stop(); break;
				case 27:isToExit = true; break;
				default:
					break;
				}




			}
		}


		return 0;
	}
