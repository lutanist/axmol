// SevenHearts (EternalClash) custom extensions for spine::SkeletonAnimation.
// Included inside the class definition via #ifdef SH_SPINE_CUSTOM_METHODS.
// Keep this file separate so upstream spine-axmol merges don't conflict.

public:
	// setAnimation overloads (EC engine added 4/5-arg variants)
	spTrackEntry* setAnimation(int trackIndex, const std::string& name, bool loop, float delay) { auto e = setAnimation(trackIndex, name, loop); if (e) e->delay = delay; return e; }
	spTrackEntry* setAnimation(int trackIndex, const std::string& name, bool loop, float delay, bool) { return setAnimation(trackIndex, name, loop, delay); }

	// Animation state queries
	bool isEndedAnimation();
	bool isEndAni() { return isEndedAnimation(); }
	float getAniTime();
	float getPreAniTime();
	void setAniTime(float time);
	const std::string getAniName();
	float getCurrentAniDuration();
	bool isCheckImpackTime(float time);

	// Update helpers
	void updateSelf(float dt);
	void updateSelf(float dt, bool force);
	void initUpdateSelfTime();
	void capture() {}

	// Pause/resume
	void pauseSpineAnimation();
	void pauseSpineAnimation(bool withChildren);
	void resumeSpineAnimation();

	// Fade
	void startFadeIn(float duration);
	void startFadeOut(float duration);

	// Flip
	void setSkeletonFlipX(bool flip);
	void setSkeletonFlipY(bool flip);
	bool isSkeletonFlipX();

	// Bone helpers
	ax::Point getBonePos(const std::string& boneName);
	ax::Vec2 getBoneWorldPos(const std::string& boneName);
	ax::Vec2 getBoneLocalPos(const std::string& boneName);
	float getBoneWorldRotation(const std::string& boneName);

	// Skeleton data
	spSkeletonData* findSpSkeletonData() { return _skeleton ? _skeleton->data : nullptr; }

	// Blend
	using SkeletonRenderer::setBlendFunc;
	void setBlendMode(int mode) {}
	void setBlended(bool blended) {}

	// Skeleton data reference counting (matches original EC engine customization)
	// Game code sets these callbacks to hook into SkeletonDataResourceManager/CharacterResourceManager.
	typedef void (*SkeletonDataRefCountCallback)(spSkeletonData* data);
	static SkeletonDataRefCountCallback s_increaseRefCountCallback;
	static SkeletonDataRefCountCallback s_decreaseRefCountCallback;
	static void setRefCountCallbacks(SkeletonDataRefCountCallback increase, SkeletonDataRefCountCallback decrease);

	// Listener convenience
	void setCompleteListener(std::nullptr_t) { _completeListener = nullptr; }
	void setEndListener(std::nullptr_t) { _endListener = nullptr; }
	void setEventListener(const std::function<void(int, const std::string&)>& listener);
	void setDefaultMix(float duration);
