#ifndef __PROGRESSVIEW_H__
#define __PROGRESSVIEW_H__
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
	typedef enum ProgressIdenType
	{
		PROGRESS_ADD,
		PROGRESS_SUB,
	};

	class ProgressView : public CCLayer
	{
	public:
		ProgressView();
		~ProgressView();

		static ProgressView *createProgress(const char *pFileName);

		void initLayer();
		void update(float dt);
		void setProgressValue(float fNum ,int num , ProgressIdenType type, bool flag);
	private:

		cocos2d::CCProgressTimer *m_pProgressTimer;

		CCSize m_MaxSize;

		float m_curValue;
		float m_DesValue;
		int m_iNum;
		ProgressIdenType iType;
	};
#endif

