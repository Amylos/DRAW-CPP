/*
 * CStriangle.cpp
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#include <CStriangle.h>

CStriangle::CStriangle():CShape(),m_toolType(TOOL_UNDEFINED) {}

CStriangle::~CStriangle() {}

CStriangle::CStriangle(SDL_Rect frame,SDL_Color color): CShape(frame, color), m_toolType(TOOL_TRIANGLE) {}

void CStriangle::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r,  m_color.g,  m_color.b,  m_color.a);
	CUtil::RenderDrawTriangle(pRenderer,m_rFrame, m_rFrame.w);
}

void*CStriangle::WriteInFile(FILE*fd){

	fwrite(&m_rFrame,sizeof(SDL_Rect),1,fd);
	fwrite(&m_color,sizeof(SDL_Color),1,fd);
	fwrite(&m_toolType,sizeof(int),1,fd);
	return nullptr;
}
int CStriangle::GetType(){
	 return m_toolType;
}
