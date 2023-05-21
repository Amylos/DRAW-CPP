/*
 * CShape.cpp
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#include "CShape.h"

CShape::CShape(): CArea(),m_toolType(TOOL_UNDEFINED) {}

CShape::~CShape() {}

CShape::CShape(SDL_Rect frame, SDL_Color color):
		CArea(frame.x, frame.y, frame.w, frame.h, color),
		m_toolType(TOOL_UNDEFINED)
{}

void*CShape::WriteInFile(FILE*fd){
	fwrite(&m_rFrame,sizeof(SDL_Rect),1,fd);
	fwrite(&m_color,sizeof(SDL_Color),1,fd);
	SDL_Log("WriteInFile");
	return nullptr;
}
void*CShape::IsAt(SDL_Point*pAt){
	if((CShape*)SDL_PointInRect(pAt, &m_rFrame)){
		return this;
	}
	return nullptr;
}

int CShape::GetType(){
	 return m_toolType;
}

void CShape::Drag(SDL_Point*pAt){

	m_rFrame.x += pAt->x;
	m_rFrame.y += pAt->y;
}


SDL_Rect CShape::GetFrame(){
	return m_rFrame;
}
SDL_Color CShape::GetColor(){
	return m_color;
}

int CShape::GetiVertexes(){
	return 0;
}

SDL_Point*CShape::GetpVertexes(){
	return nullptr;
}


