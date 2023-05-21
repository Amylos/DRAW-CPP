/*
 * CToolBox.cpp
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */


#include<CToolBox.h>

CToolBox::CToolBox(): CArea(),
		m_rHand(SDL_Rect{}),
		m_uStatus(0)
{}

CToolBox::~CToolBox(){}

CToolBox::CToolBox(int iLocX,int iLocY,int iWidth, int iHeight, SDL_Color color):

	CArea(iLocX, iLocY, iWidth, iHeight, color),
	m_rHand(SDL_Rect{iLocX,iLocY,iWidth,APP_TOOLBOX_HAND_HEIGHT}),
	m_uStatus(0)
{}


void CToolBox::Draw(SDL_Renderer*pRenderer) const{

	CArea::Draw(pRenderer);
	SDL_SetRenderDrawColor(pRenderer,APP_TOOLBOX_COLOR_HEAD.r,APP_TOOLBOX_COLOR_HEAD.g, APP_TOOLBOX_COLOR_HEAD.b,APP_TOOLBOX_COLOR_HEAD.a);
	SDL_RenderFillRect(pRenderer, &m_rHand);

	m_tools.Parse((t_ptfVV)CToolBox::ToolDrawMethod, pRenderer);
}


CTool*CToolBox::AddTool(CTool*pTool){
	size_t n = m_tools.Card();

	pTool->SetFrame(SDL_Rect{m_rFrame.x +APP_TOOLBOX_PADDING,
		m_rFrame.y + int(APP_TOOLBOX_HAND_HEIGHT + APP_TOOLBOX_PADDING+n*(APP_TOOL_HEIGHT+APP_TOOLBOX_PADDING)),
		m_rFrame.w - 2*APP_TOOLBOX_PADDING,
		m_rFrame.w - 2*APP_TOOLBOX_PADDING});

	return (CTool*)m_tools.Pushback(pTool);
}

int CToolBox::MouseMotion(SDL_MouseMotionEvent*pEvent){
	SDL_Point pt{pEvent->x,pEvent->y};
	if((pEvent->state == SDL_BUTTON_LEFT) && SDL_PointInRect(&pt, &m_rHand)){
		m_rFrame.x += pEvent->xrel;
		m_rFrame.y += pEvent->yrel;
		m_rHand.x += pEvent->xrel;
		m_rHand.y += pEvent->yrel;

	SDL_Rect r{m_rFrame.x + APP_TOOLBOX_PADDING, m_rFrame.y  +APP_TOOLBOX_PADDING + APP_TOOLBOX_HAND_HEIGHT, APP_TOOLBOX_PADDING+ APP_TOOL_HEIGHT,0};
		m_tools.Parse((t_ptfVV)CToolBox::ToolMoveMethod, &r);
		return 1;
	}
	return 0;
}


CTool*CToolBox::ToolDeleteMethod(CTool*pTool){
	delete pTool;
	return nullptr;
}

CTool*CToolBox::ToolDrawMethod(CTool*pTool, SDL_Renderer*pRenderer){
	pTool->Draw(pRenderer);
	return nullptr;
}

void*CToolBox::ToolMoveMethod(CTool*pTool, SDL_Rect*frame){
	pTool->Move(frame);
	return nullptr;
}


/*********** WORK  ***********/

SDL_Rect CToolBox::GetLocation()const{ /* useless for now */
	return m_rFrame;
}

int CToolBox::MouseOnToolBox(SDL_Point Point)const{ /* could be good to change */

	if(SDL_PointInRect(&Point, &m_rFrame)){
		return 1;
	}
	return 0;
}


CTool*CToolBox::ToolAt(SDL_Point Point){

	return (CTool*)m_tools.Parse((t_ptfVV)CTool::IsAtMethod, &Point);
}
