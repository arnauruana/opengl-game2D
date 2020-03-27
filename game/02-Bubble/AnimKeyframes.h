#ifndef _ANIMATION_KEYFRAMES
#define _ANIMATION_KEYFRAMES


#include <vector>


// AnimKeyframes contains all information related to a single animation.
// These are the animation speed measured by millisecsPerKeyframe
// and texture coordinates for all keyframes.


struct AnimKeyframes
{
	float millisecsPerKeyframe;
	std::vector<glm::vec2> keyframeDispl;
};


#endif // _ANIMATION_KEYFRAMES