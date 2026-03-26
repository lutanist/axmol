// SevenHearts (EternalClash) custom extensions for spine::SkeletonAnimation.
// Included inside SkeletonAnimation.cpp via #ifdef EC_SEVENHEARTS_EXTENSIONS.
// Keep this file separate so upstream spine-axmol merges don't conflict.

bool SkeletonAnimation::isEndedAnimation() {
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (!entry) return true;
	if (entry->loop) return false;
	return entry->trackTime >= entry->animationEnd - entry->animationStart;
}

float SkeletonAnimation::getAniTime() {
	return _curAniTime;
}

float SkeletonAnimation::getPreAniTime() {
	return _preAniTime;
}

void SkeletonAnimation::setAniTime(float time) {
	_curAniTime = time;
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (entry) entry->trackTime = time;
}

const std::string SkeletonAnimation::getAniName() {
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (entry && entry->animation) return entry->animation->name;
	return "";
}

float SkeletonAnimation::getCurrentAniDuration() {
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (entry && entry->animation) return entry->animation->duration;
	return 0.f;
}

bool SkeletonAnimation::isCheckImpackTime(float time) {
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (!entry) return false;
	return _preAniTime < time && _curAniTime >= time;
}

void SkeletonAnimation::updateSelf(float dt) {
	_preAniTime = _curAniTime;
	spTrackEntry* entry = spAnimationState_getCurrent(_state, 0);
	if (entry) _curAniTime = entry->trackTime;
}

void SkeletonAnimation::updateSelf(float dt, bool force) {
	updateSelf(dt);
}

void SkeletonAnimation::initUpdateSelfTime() {
	_preAniTime = 0.f;
	_curAniTime = 0.f;
}

void SkeletonAnimation::pauseSpineAnimation() {
	_isPaused = true;
	setTimeScale(0.f);
}

void SkeletonAnimation::pauseSpineAnimation(bool withChildren) {
	pauseSpineAnimation();
}

void SkeletonAnimation::resumeSpineAnimation() {
	_isPaused = false;
	setTimeScale(1.f);
}

void SkeletonAnimation::startFadeIn(float duration) {
	setOpacity(0);
	runAction(ax::FadeTo::create(duration, 255));
}

void SkeletonAnimation::startFadeOut(float duration) {
	runAction(ax::FadeOut::create(duration));
}

void SkeletonAnimation::setSkeletonFlipX(bool flip) {
	_skeleton->flipX = flip ? 1 : 0;
}

void SkeletonAnimation::setSkeletonFlipY(bool flip) {
	_skeleton->flipY = flip ? 1 : 0;
}

bool SkeletonAnimation::isSkeletonFlipX() {
	return _skeleton->flipX != 0;
}

ax::Point SkeletonAnimation::getBonePos(const std::string& boneName) {
	spBone* bone = findBone(boneName);
	if (!bone) return ax::Point::ZERO;
	return ax::Point(bone->worldX, bone->worldY);
}

ax::Vec2 SkeletonAnimation::getBoneWorldPos(const std::string& boneName) {
	spBone* bone = findBone(boneName);
	if (!bone) return ax::Vec2::ZERO;
	return ax::Vec2(bone->worldX, bone->worldY);
}

ax::Vec2 SkeletonAnimation::getBoneLocalPos(const std::string& boneName) {
	spBone* bone = findBone(boneName);
	if (!bone) return ax::Vec2::ZERO;
	return ax::Vec2(bone->x, bone->y);
}

float SkeletonAnimation::getBoneWorldRotation(const std::string& boneName) {
	spBone* bone = findBone(boneName);
	if (!bone) return 0.f;
	return spBone_getWorldRotationX(bone);
}

void SkeletonAnimation::setEventListener(const std::function<void(int, const std::string&)>& listener) {
	_eventListener = [listener](spTrackEntry* entry, spEvent* event) {
		if (listener && event) {
			listener(entry->trackIndex, event->data->name);
		}
	};
}

void SkeletonAnimation::setDefaultMix(float duration) {
	if (_state && _state->data) {
		_state->data->defaultMix = duration;
	}
}
