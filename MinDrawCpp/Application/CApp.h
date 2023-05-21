/*
 * CApp.h
 *
 *  Created on: 2022
 *      Author: Garnier
 */

#ifndef CAPP_H_
#define CAPP_H_

#include<iostream>
#include<cassert>
#include<cstring>
#include<ctime>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CContainer.h>

#include<CArea.h>
#include<CToolBox.h>
#include<CCanvas.h>

#include<CTool.h>
#include<CTtriangle.h>
#include<CTcircle.h>
#include<CTrectangle.h>
#include<CTpolygon.h>
#include<CTcolorChart.h>

#include<CShape.h>
#include<CSrectangle.h>
#include<CStriangle.h>
#include<CScircle.h>
#include<CSpolygon.h>


class CApp{
private:
	Uint32			m_uStatus;
	SDL_Rect		m_rFrame;
	char*			m_pTitle;
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;
	SDL_Color		m_colorBackground;
	SDL_TimerID		m_timerID;
	CToolBox		m_toolbox{0,0,APP_TOOLBOX_WIDTH,APP_TOOLBOX_HEIGHT,APP_TOOLBOX_COLOR_BACKGROUND};
	CCanvas			m_canvas{APP_CANVAS_X,APP_CANVAS_Y,APP_CANVAS_WIDTH,APP_CANVAS_HEIGHT,APP_CANVAS_COLOR_BACKGROUND};

	CTool*			m_pSelectedTool;
	SDL_Point		m_ptStart;
	SDL_Point		m_ptEnd;
	SDL_Color		m_SelectedColor;

	SDL_Point*      m_pVertexes;
	int             m_iVertexesNumber;
	int             m_iVertexesCapacity;

	CShape*			m_ShapeOnMouse;


private:
	CApp();

public:
	CApp(const char* pTitle, int iWidth, int iHeight, SDL_Color color);
	~CApp();

private:
	void Draw() const;
	int Run();
	static Uint32 TimerCallback(Uint32 interval, void*);
	void MouseMotion(SDL_MouseMotionEvent*pEvent);
	SDL_Point SetRightWay(SDL_Point Start,SDL_Point End);
};



#endif /* CAPP_H_ */
