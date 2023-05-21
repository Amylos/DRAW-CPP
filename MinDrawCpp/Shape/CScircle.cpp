/*
 * CScircle.cpp
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#include <CScircle.h>

CScircle::CScircle(): CShape(),m_toolType(TOOL_UNDEFINED) {}

CScircle::~CScircle(){}

CScircle::CScircle(SDL_Rect frame, SDL_Color color): CShape(frame, color),m_toolType(TOOL_CIRCLE){}

void CScircle::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	CUtil::RenderDrawCircle(pRenderer,SDL_Point{m_rFrame.x + m_rFrame.w/2,m_rFrame.y + m_rFrame.h/2}, m_rFrame.w/2);
}

void*CScircle::WriteInFile(FILE*fd){

	fwrite(&m_rFrame,sizeof(SDL_Rect),1,fd);
	fwrite(&m_color,sizeof(SDL_Color),1,fd);
	fwrite(&m_toolType,sizeof(int),1,fd);
	SDL_Log("WriteInFile");
	return nullptr;
}

int CScircle::GetType(){
	 return m_toolType;
}
