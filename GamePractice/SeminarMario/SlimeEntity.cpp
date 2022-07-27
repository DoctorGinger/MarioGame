#include "SlimeEntity.h"
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;
//@i
EntityPtr createSlime(std::string const& animationFolder)
{
	//fs::path root = animationFolder;
	//auto slimeFolder = root / "SlimeOrange";
	auto slime_state = CreateSlimeEnemy(animationFolder);
	EntityPtr slime(new Entity(slime_state));
	
	return slime;
}

EntityStatePtr CreateSlimeEnemy(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr nonCollidingPhysicsPtr =
		make_shared<NonCollidingPhysicsDecorator>(
			make_shared<FixedWidgetPhysics>());

	return make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}