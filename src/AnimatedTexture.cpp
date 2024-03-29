#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w,
                                 int h, int framCount, float animationSpeed,
                                 ANIM_DIR animationDir)
    : Texture(filename, x, y, w, h) {
  mTimer = Timer::Instance();

  mStartX = x;
  mStartY = y;

  mFrameCount = framCount;
  mAnimationSpeed = animationSpeed;
  mTimePerFrame = mAnimationSpeed / mFrameCount;
  mAnimationTimer = 0.0f;
  mAnimationDirection = animationDir;
  mAnimationDone = false;
  mWrapMode = loop;
}

AnimatedTexture::~AnimatedTexture() {}

void AnimatedTexture::ChangeAnimation(int x, int y, int frameCount) {
  mStartX = x;
  mStartY = y;
  mFrameCount = frameCount;
  mTimePerFrame = mAnimationSpeed / mFrameCount;
}

void AnimatedTexture::WrapMode(WRAP_MODE mode) { mWrapMode = mode; }

void AnimatedTexture::Update() {
  if (!mAnimationDone) {
    mAnimationTimer += mTimer->DeltaTime();
    if (mAnimationTimer >= mAnimationSpeed) {
      if (mWrapMode == loop) {
        mAnimationTimer -= mAnimationSpeed;
      } else {
        mAnimationDone = true;
        mAnimationTimer = mAnimationSpeed - mTimePerFrame;
      }
    }
    if (mAnimationDirection == horizontal) {
      mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
    } else {
      mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
    }
  }
}