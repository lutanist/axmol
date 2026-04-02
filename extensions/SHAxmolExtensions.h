#pragma once
// ============================================================
// SevenHearts axmol 엔진 수정 — 마스터 스위치
// 원본 cocos2d-x 3.17에서 EC_ 매크로로 수정했던 기능들을
// axmol 2.11.3에서 재구현.
//
// 개별 플래그는 CMakeLists.txt에서 정의됨:
//   spine/CMakeLists.txt      → SH_SPINE_ATLAS_SPRITEFRAME_CACHE
//                                SH_SPINE_CUSTOM_METHODS
//   cocostudio/CMakeLists.txt → SH_CSB_HD_SCALE
//                                SH_CSB_CASCADE_COMPAT
// ============================================================
#ifdef SH_AXMOL_EXTENSIONS

// --- Spine ---

// Spine atlas region을 SpriteFrameCache에 자동 등록.
// 원본: Atlas.c에서 _spAtlasPage_addSpriteFrame() 직접 호출.
// 게임 코드가 Sprite::createWithSpriteFrameName()으로
// Spine atlas 내 이미지를 직접 참조하기 때문에 필요.
// #define SH_SPINE_ATLAS_SPRITEFRAME_CACHE  -- defined in CMake

// SkeletonAnimation 커스텀 메서드 (isEndedAnimation, getBonePos,
// setSkeletonFlipX, pauseSpineAnimation 등 20+개).
// 원본: cocos2d-x Spine extension에 직접 추가되어 있었음.
// 구현: SkeletonAnimationEC.inl (선언) / .inc (정의)
// #define SH_SPINE_CUSTOM_METHODS  -- defined in CMake

// --- CocoStudio ---

// .csb 파일이 HD 해상도(~960×640)로 제작되어 있어
// 디자인 좌표계(480×320)에 맞추기 위해 position/size에
// 1.0/contentScaleFactor 스케일 적용.
// 원본: EC_20160617_SSD_UPGRADE_COCOSSTUDIO_VERSION,
//       10개 Reader 파일 79곳에 * 0.5f 하드코딩.
// 영향: NodeReader, WidgetReader, ButtonReader, ImageViewReader,
//       TextReader, TextFieldReader, LayoutReader,
//       ScrollViewReader, PageViewReader
// #define SH_CSB_HD_SCALE  -- defined in CMake

// cascadeColorEnabled / cascadeOpacityEnabled를 .csb 데이터
// 대신 항상 true로 설정 (원본 cocos2d-x 동작 호환).
// axmol은 .csb에서 읽지만, 원본은 무조건 true였음.
// #define SH_CSB_CASCADE_COMPAT  -- defined in CMake

#endif // SH_AXMOL_EXTENSIONS
